/*
Copyright by Henry Ko and Nicola Nicolici
Department of Electrical and Computer Engineering
McMaster University
Ontario, Canada
*/

`timescale 1ns/100ps
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif

module experiment2 (
		/////// board clocks                      ////////////
		input logic CLOCK_50_I,                   // 50 MHz clock

		/////// switches                          ////////////
		input logic[17:0] SWITCH_I,               // toggle switches

		/////// VGA interface                     ////////////
		output logic VGA_CLOCK_O,                 // VGA clock
		output logic VGA_HSYNC_O,                 // VGA H_SYNC
		output logic VGA_VSYNC_O,                 // VGA V_SYNC
		output logic VGA_BLANK_O,                 // VGA BLANK
		output logic VGA_SYNC_O,                  // VGA SYNC
		output logic[7:0] VGA_RED_O,              // VGA red
		output logic[7:0] VGA_GREEN_O,            // VGA green
		output logic[7:0] VGA_BLUE_O              // VGA blue
);

`include "VGA_param.h"

logic resetn, enable;

// For VGA
logic [7:0] VGA_red, VGA_green, VGA_blue;
logic [9:0] pixel_X_pos;
logic [9:0] pixel_Y_pos;
logic [7:0] counterx;
logic [7:0] countery;

logic object_on;
logic [9:0] detection;
logic [2:0] color;
//logic [2:0] greencolor;
//logic [2:0] bluecolor;
logic counter;
assign resetn = ~SWITCH_I[17];


VGA_controller VGA_unit(
	.clock(CLOCK_50_I),
	.resetn(resetn),
	.enable(enable),

	.iRed(VGA_red),
	.iGreen(VGA_green),
	.iBlue(VGA_blue),
	.oCoord_X(pixel_X_pos),
	.oCoord_Y(pixel_Y_pos),
	
	// VGA Side
	.oVGA_R(VGA_RED_O),
	.oVGA_G(VGA_GREEN_O),
	.oVGA_B(VGA_BLUE_O),
	.oVGA_H_SYNC(VGA_HSYNC_O),
	.oVGA_V_SYNC(VGA_VSYNC_O),
	.oVGA_SYNC(VGA_SYNC_O),
	.oVGA_BLANK(VGA_BLANK_O)
);

// we emulate the 25 MHz clock by using a 50 MHz AND
// updating the registers every other clock cycle
assign VGA_CLOCK_O = enable;
always_ff @(posedge CLOCK_50_I or negedge resetn) begin
	if(!resetn) begin
		enable <= 1'b0;
	end else begin
		enable <= ~enable;
	end
	//if()
end

// if the column counter is between columns 300 and 339
// and line counter is between rows 220 and 259 (inclusive)
// assert the "object_on" signal


always_ff @(posedge CLOCK_50_I or negedge resetn) begin
	if(!resetn) begin
		VGA_red <= 8'h00;
		VGA_green <= 8'h00;
		VGA_blue <= 8'h00;
	end else begin
	if ((pixel_X_pos % 90 >= 10'd15) && (pixel_Y_pos >= 10'd220) && (pixel_Y_pos < 10'd260)) begin
		//object_on = 1'b1;
		if(pixel_X_pos>= 10'd15 && pixel_X_pos < 10'd90) begin
			VGA_red <= 8'hFF;
			VGA_green <= 8'h00;
			VGA_blue <= 8'h00;
		end 
		else if (pixel_X_pos>= 10'd105 && pixel_X_pos < 10'd180) begin
			VGA_red <= 8'hFF;
			VGA_green <= 8'hFF;
			VGA_blue <= 8'h00;
		end
		else if (pixel_X_pos>= 10'd195 && pixel_X_pos < 10'd270) begin
			VGA_red <= 8'hFF;
			VGA_green <= 8'hFF;
			VGA_blue <= 8'hFF;
		end
		else if (pixel_X_pos>= 10'd285 && pixel_X_pos < 10'd360) begin
			VGA_red <= 8'h00;
			VGA_green <= 8'hFF;
			VGA_blue <= 8'hFF;
		end
		else if (pixel_X_pos>= 10'd375 && pixel_X_pos < 10'd450) begin
			VGA_red <= 8'h00;
			VGA_green <= 8'hFF;
			VGA_blue <= 8'h00;
		end
		else if (pixel_X_pos>= 10'd465 && pixel_X_pos < 10'd540) begin
			VGA_red <= 8'h00;
			VGA_green <= 8'h00;
			VGA_blue <= 8'hFF;
		end
		else if (pixel_X_pos>= 10'd555 && pixel_X_pos < 10'd630) begin
			VGA_red <= 8'hFF;
			VGA_green <= 8'h00;
			VGA_blue <= 8'hFF;
		end
	end
	else begin
		//object_on = 1'b0;
		VGA_red <= 8'h00;
		VGA_green <= 8'h00;
		VGA_blue <= 8'h00;
	end
	end
end

/*
//trangle system holy! 
always_ff @(posedge CLOCK_50_I or negedge resetn )begin
	if (pixel_Y_pos < 3'd7 * pixel_X_pos) begin
		if(pixel_Y_pos % 91 != 1'b0) begin
			object_on = 1'b1;
		end
	else begin
		object_on = 1'b0;
		end
	end
end
*/
/*
always_comb begin
	if(!resetn) begin
		VGA_red <= 8'h00;
		VGA_green <= 8'h00;
		VGA_blue <= 8'h00;
	end	
	if(pixel_X_pos%90 >= 10'd15 
	 && pixel_Y_pos >= 10'd220 && pixel_Y_pos < 10'd260) begin
		counter <= 1'b1;
	end 
	else begin
		counter <= 1'b0;
	end
	if(counter%3000 == 1'b0) begin
		color <= color + 1'b1;
	end
	if(object_on) begin
		VGA_red <= {8{color[2]}};
		VGA_green <= {8{color[1]}};
		VGA_blue <= {8{color[0]}};
	end
end

*/
/*
// the background is black and a white square is 
// displayed only if the "object_on" signal is asserted
always_ff @(posedge CLOCK_50_I or negedge resetn) begin
	if(!resetn) begin
		VGA_red <= 8'h00;
		VGA_green <= 8'h00;
		VGA_blue <= 8'h00;
	end else begin
		if (enable) begin
			if (object_on == 1'b1) begin
				VGA_red <= {8{color[2]}};
				VGA_green <= {8{color[1]}};
				VGA_blue <= {8{color[0]}};
				color <= color + 3'b1;
			end
		end
	end
end

*/
/*
assign VGA_red = object_on ? {8{~pixel_X_pos[8]}} : 8'h00;
assign VGA_green = object_on ? {8{~pixel_X_pos[7]}} : 8'h00;
assign VGA_blue = object_on ? {8{~pixel_X_pos[6]}} : 8'h00;
*/
endmodule
