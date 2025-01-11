/*
Copyright by Nicola Nicolici
Department of Electrical and Computer Engineering
McMaster University
Ontario, Canada
*/

`timescale 1ns/100ps
`default_nettype none

module TB; //impliment TB 
			//Tb IT SELF do not have input or output 
			//connect the switches to the unit under test 
			//by 1. declaring the interinal signal switches
	logic [17:0] switch; //reference code! 
	logic [6:0] seven_seg_n[7:0];
	logic [17:0] led_red;
	logic [8:0] led_green;

	//UUT instance
	experiment1 UUT( //RTL test bench unit undet test 
 		.SWITCH_I(switch),
		//2. mapping the "virtual signal input port" to the UUT 
		.SEVEN_SEGMENT_N_O(seven_seg_n),
		.LED_RED_O(led_red), //mapping the uut from testbench and pass the data
		.LED_GREEN_O(led_green));

	initial begin               //initial initial always
		$timeformat(-6, 2, "us", 10);
		switch = 18'h00000;
	end

	initial begin
		# 100;  //useless? oh, its delay--> 100 delay for time unit! 
		//sometime 100 ns is the each operation spend
		//notice! if our unit is ps, which means smallest unit digit will become 0.1ns, any extra differential digit will be ingored
		//
		switch = 18'h00001; //this is the "virtualing toggle the switch reg in the always block"
		//
		# 100;
		switch = 18'h00003;
		# 100;
		switch = 18'h00007;
		# 100;
		switch = 18'd00015;
		# 100;
		switch = 18'd00031;
		# 100;
		switch = 18'd00063;
		# 100;
		switch = 18'd00127;
		# 100;
		switch = 18'd00255;
		# 100;
		switch = 18'd00511;
		# 100;
		switch = 18'd01023;
		# 100;
		switch = 18'd02047;
		# 100;
		switch = 18'd04095;
		# 100;
		switch = 18'd08191;
		# 100;
		switch = 18'd16383;
		# 100;
		switch = 18'd32767;
		# 100;
		switch = 18'd65535;
		# 100;
		switch = 18'd131071;
		# 100;
		switch = 18'd262143;
		# 100;

	end

	always@(led_red) begin
		$display("%t: red leds = %b", $realtime, led_red); //monitors
		//$display("%t: seven sigment = %b", $realtime, seven_seg_n); //monitors 
	end
	
	always@(led_green) begin
		$display("%t: green leds = %b", $realtime, led_green); //monitors 
	end
	always@(seven_seg_n[0]) begin
		$display("%t: seven sigment = %b", $realtime, seven_seg_n[0]); //monitors 
	end
	always@(seven_seg_n[7]) begin
		$display("%t: seven sigment = %b", $realtime, seven_seg_n[7]); //monitors 
	end
endmodule
