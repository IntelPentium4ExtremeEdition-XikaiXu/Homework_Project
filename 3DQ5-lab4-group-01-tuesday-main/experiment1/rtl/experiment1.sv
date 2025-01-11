/*
Copyright by Henry Ko and Nicola Nicolici
Department of Electrical and Computer Engineering
McMaster University
Ontario, Canada
*/

`timescale 1ns/100ps //time scale 
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif

// This is the top module
// It utilizes a priority encoder to detect a 1 on the MSB for switches 17 downto 0
// It then displays the switch number onto the 7-segment display
module experiment1 (
		/////// switches                          ////////////
		input logic[17:0] SWITCH_I,               // toggle switches

		/////// 7 segment displays/LEDs           ////////////
		output logic[6:0] SEVEN_SEGMENT_N_O[7:0], // 8 seven segment displays
		output logic[8:0] LED_GREEN_O,            // 9 green LEDs
		output logic[17:0] LED_RED_O              // 18 red LEDs
);

logic [3:0] value;
logic [6:0] value_7_segment;
logic [3:0] min_digit;
logic [6:0] value_7_segment2;
// Instantiate a module for converting hex number to 7-bit value for the 7-segment display
convert_hex_to_seven_segment unit0 (
	.hex_value(value), 
	.converted_value(value_7_segment)
);

convert_hex_to_seven_segment unit1 (
	.hex_value(min_digit), 
	.converted_value(value_7_segment2)
);

// A priority encoder using successive (independent) if statements
always_comb begin
	value = 4'hF;
	if (SWITCH_I[0]) value = 4'h0;
	if (SWITCH_I[1]) value = 4'h1;
	if (SWITCH_I[2]) value = 4'h2;
	if (SWITCH_I[3]) value = 4'h3;
	if (SWITCH_I[4]) value = 4'h4;
	if (SWITCH_I[5]) value = 4'h5;
	if (SWITCH_I[6]) value = 4'h6;
	if (SWITCH_I[7]) value = 4'h7;
	if (SWITCH_I[8]) value = 4'h8;
	if (SWITCH_I[9]) value = 4'h9;
end

always_comb begin
	min_digit = 4'hA;
	for(int i = 9; i >= 0; i--)begin
		if(!SWITCH_I[i]) begin
			if(i < min_digit) begin
				min_digit = i;
			end
		end
	end
end

always_comb begin
	if(min_digit == 4'hA) begin
		SEVEN_SEGMENT_N_O[7] = 7'h7f;
	end
	else begin
		SEVEN_SEGMENT_N_O[7] = value_7_segment2;
	end
end

assign  SEVEN_SEGMENT_N_O[0] = value_7_segment,
        SEVEN_SEGMENT_N_O[1] = 7'h7f,
        SEVEN_SEGMENT_N_O[2] = 7'h7f,
        SEVEN_SEGMENT_N_O[3] = 7'h7f,
        SEVEN_SEGMENT_N_O[4] = 7'h7f,
        SEVEN_SEGMENT_N_O[5] = 7'h7f,
        SEVEN_SEGMENT_N_O[6] = 7'h7f;
        

assign LED_RED_O = SWITCH_I;
//assign LED_GREEN_O = {5'h00, value};
assign LED_GREEN_O = {min_digit, 4'h0};
//assign enum listdigit = {1,2,3,4,5,6,7,8,9,a,b,c,d,e,f}
	
endmodule