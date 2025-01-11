`timescale 1ns/100ps
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif


module Fetch (
	input logic Clock_50,
	input logic Resetn,
	output logic [17:0] SRAM_address,
	input logic [15:0] SRAM_read_data,
   output logic [7:0] DP_RAM_address,
   output logic [31:0] DP_RAM_write_data,
	output logic DP_RAM_we,
	input logic start,
	output logic finish,	
	input logic [8:0] CA_init, RA_init,
	input logic Y_finished
);

typedef enum logic [3:0] {
	S_idle_fetch_sp,
	S_common1_fetch_sp,
	S_common2_fetch_sp,
	S_leadin_fetch_sp,
	S_leadout_fetch_sp,
	S_end_fetch_sp
} Fetch_Sp_state;

Fetch_Sp_state fetch_sp;

logic [17:0] Pre_IDCT_address;
logic [17:0] Pre_IDCT_offset;
logic [8:0] RA, CA;
logic [6:0] write_address;

logic [6:0] fetch_counter;
logic [15:0] fetch_buffer;

/*
Pre_IDCT_address = (!Y_finished) ? 18'd76800 : 18'd153600;
Pre_IDCT_offset = (!Y_finished) ? ((RA + RA_init) << 9'd8) + ((RA + RA_init) << 9'd6) + CA + CA_init : ((RA + RA_init) << 9'd7) + ((RA + RA_init) << 9'd5) + CA + CA_init;
*/

always_comb begin
	if (!Y_finished) begin
		Pre_IDCT_address = 18'd76800 + ((RA + RA_init) << 9'd8) + ((RA + RA_init) << 9'd6) + CA + CA_init;
	end else begin 
		Pre_IDCT_address = 18'd153600 + ((RA + RA_init) << 9'd7) + ((RA + RA_init) << 9'd5) + CA + CA_init;
	end
end

always_ff @(posedge Clock_50 or negedge Resetn) begin
    if (~Resetn) begin
		fetch_sp <= S_idle_fetch_sp;
		RA <= 9'd0;
		CA <= 9'd0;
      finish <= 0;
		fetch_counter <= 0;
		fetch_buffer <= 0;
      write_address <= 0;
		DP_RAM_address <= 0;
		DP_RAM_write_data <= 0;
		DP_RAM_we <= 0;
		SRAM_address <= 0;
    end
	 else begin
			case(fetch_sp)
			S_idle_fetch_sp: begin 
				RA <= 9'd0;
				CA <= 9'd0;
				finish <= 0;
				fetch_counter <= 0;
				fetch_buffer <= 0;
				write_address <= 0;
				DP_RAM_address <= 0;
				DP_RAM_write_data <= 0;
				DP_RAM_we <= 0;
				SRAM_address <= 0;
				if (start) begin 
					fetch_sp <= S_leadin_fetch_sp;
				end
			end
			S_leadin_fetch_sp: begin 
				SRAM_address <= Pre_IDCT_address;
				if (CA == 9'd7) begin
					CA <= 9'd0;
					RA <= RA + 9'd1;
				end else begin
					CA <= CA + 9'd1;
				end
				fetch_counter <= fetch_counter + 6'b1;
				if (fetch_counter == 6'd3) begin 
					fetch_buffer <= SRAM_read_data;
					fetch_sp <= S_common1_fetch_sp;
				end
			end
			S_common1_fetch_sp: begin 
				DP_RAM_write_data <= {fetch_buffer, SRAM_read_data};
				DP_RAM_address <= write_address;
				DP_RAM_we <= 1'b1;
				if (fetch_counter > 7'd64) begin
					fetch_sp <= S_leadout_fetch_sp;
				end else begin 
					SRAM_address <= Pre_IDCT_address;
					if (CA == 9'd7) begin
						CA <= 9'd0;
						RA <= RA + 9'd1;
					end else begin
						CA <= CA + 9'd1;
					end
					fetch_counter <= fetch_counter + 6'b1;
					fetch_sp <= S_common2_fetch_sp;
				end
			end
			S_common2_fetch_sp: begin 
				SRAM_address <= Pre_IDCT_address;
				if (CA == 9'd7) begin
					CA <= 9'd0;
					RA <= RA + 9'd1;
				end else begin
					CA <= CA + 9'd1;
				end
            write_address <= write_address + 7'd1;
				fetch_counter <= fetch_counter + 6'b1;
				fetch_buffer <= SRAM_read_data;
				fetch_sp <= S_common1_fetch_sp;
			end
			S_leadout_fetch_sp: begin 
				DP_RAM_address <= write_address;
				fetch_buffer <= SRAM_read_data;
				fetch_sp <= S_end_fetch_sp;
			end
			S_end_fetch_sp: begin 
            finish <= 1'b1;
				DP_RAM_we <= 0;
				RA <= 0;
				CA <= 0;
				write_address <= 0;
				fetch_counter <= 0;
				fetch_sp <= S_idle_fetch_sp;
			end
			endcase
    end 
	 
end
endmodule