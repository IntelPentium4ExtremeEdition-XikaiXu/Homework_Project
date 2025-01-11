#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "PLL.h"
#include "SysTick.h"
#include "uart.h"
#include "onboardLEDs.h"
#include "tm4c1294ncpdt.h"
#include "VL53L1X_api.h"
#include "Motor.h"

#define I2C_MCS_ACK             0x00000008  // Data Acknowledge Enable
#define I2C_MCS_DATACK          0x00000008  // Acknowledge Data
#define I2C_MCS_ADRACK          0x00000004  // Acknowledge Address
#define I2C_MCS_STOP            0x00000004  // Generate STOP
#define I2C_MCS_START           0x00000002  // Generate START
#define I2C_MCS_ERROR           0x00000002  // Error
#define I2C_MCS_RUN             0x00000001  // I2C Master Enable
#define I2C_MCS_BUSY            0x00000001  // I2C Busy
#define I2C_MCR_MFE             0x00000010  // I2C Master Function Enable
#define MAXRETRIES              5           // number of receive attempts before giving up

int power = 0;
int exist = 0;
int Botton0 = 0;
int Botton1 = 0;

void PortJ_Init(void){ //Button
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R8;                 	// Activate the clock for Port J
	while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R8) == 0){};					// Allow time for clock to stabilize
	GPIO_PORTJ_PUR_R = 0b11;
	GPIO_PORTJ_DIR_R=0b0;															// Enable PM0 as input;
	GPIO_PORTJ_DEN_R=0b11;												
	return;
}

void I2C_Init(void){   //i2c channel commuate with board
  	SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R0;           													// activate I2C0
  	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;          												// activate port B
  	while((SYSCTL_PRGPIO_R&0x0002) == 0){};																		// ready?
    GPIO_PORTB_AFSEL_R |= 0x0C;           																	// 3) enable alt funct on PB2,3       0b00001100
    GPIO_PORTB_ODR_R |= 0x08;             																	// 4) enable open drain on PB3 only
    GPIO_PORTB_DEN_R |= 0x0C;             																	// 5) enable digital I/O on PB2,3
	  GPIO_PORTB_AMSEL_R &= ~0x0C;          																// 7) disable analog functionality on PB2,3                                                                        
  	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFF00FF)+0x00002200;    //TED
    I2C0_MCR_R = I2C_MCR_MFE;                      													// 9) master function enable
    I2C0_MTPR_R = 0b0000000000000101000000000111011;                       	// 8) configure for 100 kbps clock (added 8 clocks of glitch suppression ~50ns)
	  I2C0_MTPR_R = 0x3B;                                        						// 8) configure for 100 kbps clock 
}

void Convert_yz(int distance, float degree, double* y, double* z){ //tri trans function
	const double pi = acos(-1.0);
    double radians = degree * pi / 180;
    *y = distance * cos(radians);
    *z = distance * sin(radians); 
}

void check0_button_press(){
	do{
		Botton0 = GPIO_PORTJ_DATA_R & 0b01;
	}while(Botton0 == 0); 
	power ^= 1;
}

void check1_button_press(){
	do{
		Botton1 = GPIO_PORTJ_DATA_R & 0b10;
	}while(Botton1 == 0); 
	exist ^= 1;
}

uint16_t dev = 0x29;			//address of the ToF sensor as an I2C slave peripheral
int status = 0;
double coordinate[64][2]; //64 sets of extension data with y and z, not use for stability 

int main(void) {
  uint8_t byteData, sensorState=0, myByteArray[10] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} , i=0;
  uint16_t wordData;
  uint16_t Distance;
  uint16_t SignalRate;
  uint16_t AmbientRate;
  uint16_t SpadNum; 
  uint8_t RangeStatus;
  uint8_t dataReady;
	float degree = 5.625;
	double x = 0, y,z;
	double tracing_y = 0,tracing_z = 0;
	
	//initialize
	PLL_Init();	
	SysTick_Init();
	onboardLEDs_Init();
	motorinit();
	I2C_Init();
	UART_Init();
	PortJ_Init();
	
	//wait from the computer
	//ready to send the data from computer
	SysTick_Wait10ms(10);
	UART_printf("Program Begins\r\n");
	int stunum = 7;
	sprintf(printf_buffer,"2DX ToF Program Studio Code %d\r\n",stunum);
	UART_printf(printf_buffer);
	// 1 Wait for device ToF booted
	
	//wait for the tof init 
	while(sensorState == 0){
		status = VL53L1X_BootState(dev, &sensorState);
		SysTick_Wait10ms(10);
	}
	//debugging 
	FlashAllLEDs();
	
	status = VL53L1X_ClearInterrupt(dev); /* clear interrupt has to be called to enable next interrupt*/
  status = VL53L1X_SensorInit(dev);
	Status_Check("SensorInit", status);

	while(1){ //program main loop
		Botton0 = GPIO_PORTJ_DATA_R & 0b01;	//pj0
		Botton1 = GPIO_PORTJ_DATA_R & 0b10;	//pj1 //not use for stability 
	  ClockMeasure();
		if(Botton0 == 0){
			check0_button_press();
		}
		if(Botton1 == 0){
			check1_button_press();
		}
		motorsleep(); //all high with no current
		if(power){
			for(int j = 0; j < 1 ; j++){
				status = VL53L1X_StartRanging(dev);   // 4 This function has to be called to enable the ranging
				UART_printf("S\r\n");

				for(int i = 0; i < 64; i++){// Get the Distance Measures 64 times                     
					while (dataReady == 0){//5 wait until the ToF sensor's data is ready
						status = VL53L1X_CheckForDataReady(dev, &dataReady);
						VL53L1_WaitMs(dev, 5);
					}
					dataReady = 0;
					//7 read the data values from ToF sensor
					SysTick_Wait10ms(30);
					status = VL53L1X_GetDistance(dev, &Distance);					//7 The Measured Distance valu
					status = VL53L1X_ClearInterrupt(dev); /* 8 clear interrupt has to be called to enable next interrupt*/
					// print the resulted readings to UART
					Convert_yz(Distance, degree * i, &y, &z);
					
					coordinate[i][0] = y;
					coordinate[i][1] = z;
					
					if(RangeStatus != 0){
						coordinate[i][0] = tracing_y; //error handleing 
						coordinate[i][1] = tracing_y;
						
					} //netburst tracking cache 
					if(RangeStatus == 0){
						tracing_y = y; //record the most recent correct value 
					}
					
					sprintf(printf_buffer,"%f, %f, %f\r\n", x,y,z);
					UART_printf(printf_buffer);
					for(int i = 0; i < 8; i++){
						CounterClockWiseRotate();
					}
					FlashLED1(1);
					if(i%8 == 0){
						FlashLED3(1);//pf4 
					}
				}
				for(int j = 0; j < 512; j++){
					ClockWiseRotate();
					if(j%64 == 0){
						FlashLED3(1);//pf4 
					}
				}
				UART_printf("T\r\n");
				VL53L1X_StopRanging(dev);
				x += 100; // 10 CM PER X INT
			}
			power = 0;
		}
		FlashAllLEDs(); //com debugging
	}		
}