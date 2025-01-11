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

`include "define_state.h"

// This is the top module
// It connects the SRAM and VGA together
// It will first write RGB data of an image with 8x8 rectangles of size 40x30 pixels into the SRAM
// The VGA will then read the SRAM and display the image
module experiment1 (
		/////// board clocks                      ////////////
		input logic CLOCK_50_I,                   // 50 MHz clock

		/////// pushbuttons/switches              ////////////
		input logic[3:0] PUSH_BUTTON_N_I,         // pushbuttons
		input logic[17:0] SWITCH_I,               // toggle switches

		/////// VGA interface                     ////////////
		output logic VGA_CLOCK_O,                 // VGA clock
		output logic VGA_HSYNC_O,                 // VGA H_SYNC
		output logic VGA_VSYNC_O,                 // VGA V_SYNC
		output logic VGA_BLANK_O,                 // VGA BLANK
		output logic VGA_SYNC_O,                  // VGA SYNC
		output logic[7:0] VGA_RED_O,              // VGA red
		output logic[7:0] VGA_GREEN_O,            // VGA green
		output logic[7:0] VGA_BLUE_O,             // VGA blue
		
		/////// SRAM Interface                    ////////////
		inout wire[15:0] SRAM_DATA_IO,            // SRAM data bus 16 bits
		output logic[19:0] SRAM_ADDRESS_O,        // SRAM address bus 18 bits
		output logic SRAM_UB_N_O,                 // SRAM high-byte data mask 
		output logic SRAM_LB_N_O,                 // SRAM low-byte data mask 
		output logic SRAM_WE_N_O,                 // SRAM write enable
		output logic SRAM_CE_N_O,                 // SRAM chip enable
		output logic SRAM_OE_N_O                  // SRAM output logic enable
);

// Even pixel counter for keeping track of the address offset
logic [17:0] even_pixel_counter;

state_type state;

// For Push button
logic [3:0] PB_pushed;

// For VGA
logic [7:0] VGA_red, VGA_green, VGA_blue;
logic [9:0] pixel_X_pos;
logic [9:0] pixel_Y_pos;

// For SRAM
logic [17:0] SRAM_address;
//new add
logic [17:0] SRAM_addressR;
logic [17:0] SRAM_addressEG;
logic [17:0] SRAM_addressEB;
logic [17:0] SRAM_addressOG;
logic [17:0] SRAM_addressOB;

//
logic cluster;




logic [15:0] SRAM_write_data;
logic SRAM_we_n;
logic [15:0] SRAM_read_data;
logic SRAM_ready;

logic [15:0] VGA_sram_data[4:0];
logic [7:0] Buffer_G;

logic [2:0] rect_row_count;     // Number of rectangles in a row
logic [2:0] rect_col_count;     // Number of rectangles in a column
logic [5:0] rect_width_count;   // Width of each rectangle
logic [4:0] rect_height_count;  // Height of each rectangle
logic [2:0] color;

logic resetn;
assign resetn = ~SWITCH_I[17] && SRAM_ready;

// Push Button unit
PB_controller PB_unit (
	.Clock_50(CLOCK_50_I),
	.Resetn(resetn),
	.PB_signal(PUSH_BUTTON_N_I),	
	.PB_pushed(PB_pushed)
);

// SRAM unit
SRAM_controller SRAM_unit (
	.Clock_50(CLOCK_50_I),
	.Resetn(~SWITCH_I[17]),
	.SRAM_address(SRAM_address),
	.SRAM_write_data(SRAM_write_data),
	.SRAM_we_n(SRAM_we_n),
	.SRAM_read_data(SRAM_read_data),		
	.SRAM_ready(SRAM_ready),
		
	// To the SRAM pins
	.SRAM_DATA_IO(SRAM_DATA_IO),
	.SRAM_ADDRESS_O(SRAM_ADDRESS_O)
,
	.SRAM_UB_N_O(SRAM_UB_N_O),
	.SRAM_LB_N_O(SRAM_LB_N_O),
	.SRAM_WE_N_O(SRAM_WE_N_O),
	.SRAM_CE_N_O(SRAM_CE_N_O),
	.SRAM_OE_N_O(SRAM_OE_N_O)
);

assign SRAM_ADDRESS_O[19:18] = 2'b00;

logic Enable;
VGA_controller VGA_unit(
	.Clock(CLOCK_50_I),
	.Resetn(resetn),
	.Enable(Enable),

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

// we emulate the 25 MHz clock by using a 50 MHz
// AND
// updating the registers every other clock cycle

always_ff @(posedge CLOCK_50_I or negedge resetn) begin
	if(!resetn) begin
		Enable <= 1'b0;
	end else begin
		Enable <= ~Enable;
	end
end
assign VGA_CLOCK_O = Enable;

// Each rectangle will have different color
assign color = rect_col_count + rect_row_count;

always_ff @ (posedge CLOCK_50_I or negedge resetn) begin
	if (resetn == 1'b0) begin
		state <= S_IDLE;
		rect_row_count <= 3'd0;
		rect_col_count <= 3'd0;
		rect_width_count <= 6'd0;
		rect_height_count <= 5'd0;
		VGA_red <= 8'd0;
		VGA_green <= 8'd0;
		VGA_blue <= 8'd0;				
		SRAM_we_n <= 1'b1;
		SRAM_write_data <= 16'd0;
		SRAM_address <= 18'd0;
		even_pixel_counter <= 18'd0;
		VGA_sram_data[0] <= 8'd0;
		VGA_sram_data[1] <= 8'd0;
		VGA_sram_data[2] <= 8'd0;
		VGA_sram_data[3] <= 8'd0;
		VGA_sram_data[4] <= 8'd0;
		SRAM_addressR <= RED_BASE_ADDRESS;
		SRAM_addressEG <= EVEN_GREEN_BASE_ADDRESS;
		SRAM_addressEB <= EVEN_BLUE_BASE_ADDRESS;
		SRAM_addressOG <= ODD_GREEN_BASE_ADDRESS; 
		SRAM_addressOB <= ODD_BLUE_BASE_ADDRESS;
		cluster <= 1'b0;
	end else begin
		case (state)

			S_IDLE: begin
				if (PB_pushed[0] == 1'b1) begin
					// Start filling the SRAM
					state <= S_FILL_SRAM_GREEN_0;
					SRAM_address <= 18'h3FFFF;				
					// Data counter for deriving the RGB data of each pixel
					even_pixel_counter <= 18'd0;
				end
			end

            S_FILL_SRAM_GREEN_0: begin
                SRAM_we_n <= 1'b0;
                // Fill Green for pixel 0 and 2
                SRAM_write_data <= {{8{color[1]}}, {8{color[1]}}};
                SRAM_address <= even_pixel_counter + EVEN_GREEN_BASE_ADDRESS;
					
                state <= S_FILL_SRAM_BLUE_0;
            end

            S_FILL_SRAM_BLUE_0: begin
                // Fill Blue for pixel 0 and 2
                SRAM_write_data <= {{8{color[0]}}, {8{color[0]}}};
                SRAM_address <= even_pixel_counter + EVEN_BLUE_BASE_ADDRESS;

                state <= S_FILL_SRAM_GREEN_1;
            end

            S_FILL_SRAM_GREEN_1: begin
                // Fill Green for pixel 1 and 3
                SRAM_write_data <= {{8{color[1]}}, {8{color[1]}}};
                SRAM_address <= even_pixel_counter + ODD_GREEN_BASE_ADDRESS;

                state <= S_FILL_SRAM_BLUE_1;
            end

            S_FILL_SRAM_BLUE_1: begin
                // Fill Green for pixel 1 and 3
                SRAM_write_data <= {{8{color[0]}}, {8{color[0]}}};
                SRAM_address <= even_pixel_counter + ODD_BLUE_BASE_ADDRESS;

                state <= S_FILL_SRAM_RED_0;
            end

            S_FILL_SRAM_RED_0: begin
                // Fill Red for pixel 0 and 1
                SRAM_write_data <= {{8{color[2]}}, {8{color[2]}}};
                SRAM_address <= (even_pixel_counter << 1) + RED_BASE_ADDRESS;

                state <= S_FILL_SRAM_RED_1;
            end

            S_FILL_SRAM_RED_1: begin
                // Fill Red for pixel 2 and 3
                SRAM_write_data <= {{8{color[2]}}, {8{color[2]}}};
                SRAM_address <= (even_pixel_counter << 1) + 18'd1 + RED_BASE_ADDRESS;

                // Increment data counter for new RGB data of a pixel
                even_pixel_counter <= even_pixel_counter + 18'd1;

                if ((rect_row_count == (NUM_ROW_RECTANGLE - 1))
                 && (rect_col_count == (NUM_COL_RECTANGLE - 1))
                 && (rect_width_count == (RECT_WIDTH - 4))
                 && (rect_height_count == (RECT_HEIGHT - 1))) begin
                    // Finish filling the SRAM
                    state <= S_FINISH_FILL_SRAM;
                end else begin
                    if (rect_width_count < (RECT_WIDTH - 4)) begin
                        // Same horizontal line for a rectangle
                        // Increment width by 4 since we are storing data for 4 pixels at a time
                        rect_width_count <= rect_width_count + 6'd4;
                    end else begin
                        // Move to the next rectangle
                        rect_width_count <= 6'd0;
                        if (rect_col_count < (NUM_COL_RECTANGLE - 1)) rect_col_count <= rect_col_count + 3'd1;
                        else begin
                            // One pixel row
                            if (rect_height_count < (RECT_HEIGHT - 1)) begin
                                rect_height_count <= rect_height_count + 5'd1;
                            end else begin
                                // New row of rectangle
                                rect_row_count <= rect_row_count + 3'd1;
                                rect_height_count <= 5'd0;
                            end
                            rect_col_count <= 3'd0;
                        end
                    end
                    state <= S_FILL_SRAM_GREEN_0;
                end
            end

            S_FINISH_FILL_SRAM: begin
                // Finish filling the SRAM
                // Now prepare for VGA to read the image
                SRAM_we_n <= 1'b1;

                SRAM_address <= 18'h00000;
                even_pixel_counter <= 18'd0;

                state <= S_WAIT_NEW_PIXEL_ROW;
                //$stop;
            end

			S_WAIT_NEW_PIXEL_ROW: begin
				if (pixel_Y_pos >= VIEW_AREA_TOP && pixel_Y_pos < VIEW_AREA_BOTTOM) begin
					if (pixel_X_pos == (VIEW_AREA_LEFT - 3)) begin
						if (pixel_Y_pos == VIEW_AREA_TOP) begin
							// Start a new frame
							// Provide address for data 1
							SRAM_address <= RED_BASE_ADDRESS; //73742
							SRAM_addressR <= RED_BASE_ADDRESS; //73742
							SRAM_addressEG <= EVEN_GREEN_BASE_ADDRESS;
							SRAM_addressEB <= EVEN_BLUE_BASE_ADDRESS;
							SRAM_addressOG <= ODD_GREEN_BASE_ADDRESS; 
							SRAM_addressOB <= ODD_BLUE_BASE_ADDRESS;
						end
						else begin
							// Start a new row of pixels
							// Provide address for data 1
						end
						cluster <= 1'b0;
						state <= S_NEW_PIXEL_ROW_DELAY_1;
					end
				end
				VGA_red <= 8'd0;
				VGA_green <= 8'd0;
				VGA_blue <= 8'd0;								
			end

			S_NEW_PIXEL_ROW_DELAY_1: begin
				// Provide address for data 2
				SRAM_address <= SRAM_addressEG;	//131872			
				state <= S_NEW_PIXEL_ROW_DELAY_2;		
			end

			S_NEW_PIXEL_ROW_DELAY_2: begin	
				// Provide address for data 3
				SRAM_address <= SRAM_addressEB;	
				state <= S_NEW_PIXEL_ROW_DELAY_3;		
			end

			S_NEW_PIXEL_ROW_DELAY_3: begin		
				SRAM_address <= SRAM_addressOG;
				VGA_sram_data[0] <= SRAM_read_data;
				state <= S_NEW_PIXEL_ROW_DELAY_4;
			end

			S_NEW_PIXEL_ROW_DELAY_4: begin	
				SRAM_address <= SRAM_addressOB;	
				VGA_sram_data[1] <= SRAM_read_data;	
				state <= S_NEW_PIXEL_ROW_DELAY_5;			
			end

			S_NEW_PIXEL_ROW_DELAY_5: begin		
				VGA_sram_data[2] <= SRAM_read_data;
				state <= S_FETCH_PIXEL_DATA_0;			
			end

			S_FETCH_PIXEL_DATA_0: begin
				// Provide RGB data
				SRAM_address <= SRAM_addressR + 1'b1;
				SRAM_addressR <= SRAM_addressR + 1'b1;
				if(!cluster) begin
					VGA_red <= VGA_sram_data[0][15:8];
					VGA_green <= VGA_sram_data[1][15:8];
					VGA_blue <= VGA_sram_data[2][15:8];	
					VGA_sram_data[3] <= SRAM_read_data;//read 73743	
					Buffer_G <= VGA_sram_data[1][7:0];
				end
				else begin
					VGA_red <= VGA_sram_data[0][15:8];
					VGA_green <= Buffer_G;
					VGA_blue <= VGA_sram_data[2][7:0];	
					VGA_sram_data[1] <= SRAM_read_data;
				end
				state <= S_FETCH_PIXEL_DATA_1;			
			end

			S_FETCH_PIXEL_DATA_1: begin		
				// Buffer data 1
				if(!cluster) begin
					SRAM_address <= SRAM_addressEG + 1'b1; //push 
					SRAM_addressEG <= SRAM_addressEG + 1'b1;
					VGA_sram_data[4] <= SRAM_read_data;
				end
				else begin
					SRAM_address <= SRAM_addressOG + 1'b1;
					SRAM_addressOG <= SRAM_addressOG + 1'b1;
					VGA_sram_data[2] <= SRAM_read_data;
				end	
				state <= S_FETCH_PIXEL_DATA_2;
			end

			S_FETCH_PIXEL_DATA_2: begin				
				// Provide RGB data				
				if(!cluster) begin
					SRAM_address <= SRAM_addressEB + 1'b1;
					SRAM_addressEB <= SRAM_addressEB + 1'b1;
					VGA_red <= VGA_sram_data[0][7:0];
					VGA_green <= VGA_sram_data[3][15:8];
					VGA_blue <= VGA_sram_data[4][15:8];
				end
				else begin
					SRAM_address <= SRAM_addressOB + 1'b1;
					SRAM_addressOB <= SRAM_addressOB + 1'b1;
					VGA_red <= VGA_sram_data[0][7:0];
					VGA_green <= VGA_sram_data[3][7:0];
					VGA_blue <= VGA_sram_data[4][7:0];
				end
				
				state <= S_FETCH_PIXEL_DATA_3;
			end

			S_FETCH_PIXEL_DATA_3: begin 
				SRAM_address <= SRAM_addressR;
				VGA_sram_data[0] <= SRAM_read_data;
				cluster <= ~cluster;			
				if (pixel_X_pos < (VIEW_AREA_RIGHT - 2))
					// Still within one row
					state <= S_FETCH_PIXEL_DATA_0;
				else
					state <= S_WAIT_NEW_PIXEL_ROW;
			end		

			default: state <= S_IDLE;

		endcase
	end
end

endmodule