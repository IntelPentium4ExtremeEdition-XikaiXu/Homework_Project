`timescale 1ns/100ps
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif


module Fetch (
	input logic Clock_50,
	input logic Resetn,
	output logic [6:0] DP_RAM_address_X,
   input logic [31:0] DP_RAM_read_data_X,
	
   output logic [6:0] DP_RAM_address,
   output logic [31:0] DP_RAM_write_data,
	output logic DP_RAM_we,
	output logic finish,
	input logic M3_finish
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


logic [6:0] Pre_IDCT_offset;
logic [6:0] write_address;

logic [6:0] fetch_counter;
logic [15:0] fetch_buffer;


always_ff @(posedge Clock_50 or negedge Resetn) begin
    if (~Resetn) begin
		fetch_sp <= S_idle_fetch_sp;
      finish <= 0;
		fetch_counter <= 0;
		fetch_buffer <= 0;
      write_address <= 0;
		DP_RAM_address <= 0;
		DP_RAM_write_data <= 0;
		DP_RAM_we <= 0;
		DP_RAM_address_X <= 0;
		Pre_IDCT_offset <= 0;
    end
	 else begin
			case(fetch_sp)
			S_idle_fetch_sp: begin 
				finish <= 0;
				fetch_counter <= 0;
				fetch_buffer <= 0;
				write_address <= 0;
				DP_RAM_address <= 0;
				DP_RAM_write_data <= 0;
				DP_RAM_we <= 0;
				DP_RAM_address_X <= 0;
				Pre_IDCT_offset <= 0;
				if (M3_finish) begin 
					fetch_sp <= S_leadin_fetch_sp;
				end
			end
			S_leadin_fetch_sp: begin 
				DP_RAM_address_X <= Pre_IDCT_offset;
				Pre_IDCT_offset <= Pre_IDCT_offset + 17'd1;
				fetch_counter <= fetch_counter + 6'b1;
				if (fetch_counter == 6'd2) begin 
					fetch_buffer <= DP_RAM_read_data_X[15:0];
					fetch_sp <= S_common1_fetch_sp;
				end
			end
			S_common1_fetch_sp: begin 
				DP_RAM_write_data <= {fetch_buffer, DP_RAM_read_data_X[15:0]};
				DP_RAM_address <= write_address;
				DP_RAM_we <= 1'b1;
				if (fetch_counter > 7'd64) begin
					fetch_sp <= S_leadout_fetch_sp;
				end else begin 
					DP_RAM_address_X <= Pre_IDCT_offset;
					Pre_IDCT_offset <= Pre_IDCT_offset + 17'd1;
					fetch_counter <= fetch_counter + 6'b1;
					fetch_sp <= S_common2_fetch_sp;
				end
			end
			S_common2_fetch_sp: begin 
				DP_RAM_address_X <= Pre_IDCT_offset;
				Pre_IDCT_offset <= Pre_IDCT_offset + 17'd1;
            write_address <= write_address + 7'd1;
				fetch_counter <= fetch_counter + 6'b1;
				fetch_buffer <= DP_RAM_read_data_X[15:0];
				fetch_sp <= S_common1_fetch_sp;
			end
			S_leadout_fetch_sp: begin 
				DP_RAM_address <= write_address;
				fetch_buffer <= DP_RAM_read_data_X[15:0];
				fetch_sp <= S_end_fetch_sp;
			end
			S_end_fetch_sp: begin 
            finish <= 1'b1;
				DP_RAM_we <= 0;
				write_address <= 0;
				fetch_counter <= 0;
				Pre_IDCT_offset <= 0;
				fetch_sp <= S_idle_fetch_sp;
			end
			endcase
    end 
	 
end
endmodule