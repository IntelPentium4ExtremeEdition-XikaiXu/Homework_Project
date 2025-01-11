`timescale 1ns/100ps
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif

module Fetch (
	input logic Clock_50,
	input logic Resetn,
	output logic [6:0] DP_RAM_address_X_a,
	output logic [6:0] DP_RAM_address_X_b,
   input logic [31:0] DP_RAM_read_data_X_a,
	input logic [31:0] DP_RAM_read_data_X_b,
	output logic DP_RAM_we_X_a,
	
   output logic [6:0] DP_RAM_address_Sp_a,
   output logic [31:0] DP_RAM_write_data_Sp_a,
	output logic DP_RAM_we_Sp_a,
	output logic finish,
	input logic M3_finish
);

typedef enum logic [3:0] {
	S_idle_fetch_sp,
	S_common1_fetch_sp,
	S_common2_fetch_sp,
	S_leadout_fetch_sp,
	S_end_fetch_sp
} Fetch_Sp_state;

Fetch_Sp_state fetch_sp;


logic [7:0] counter;
logic first_time;

always_ff @(posedge Clock_50 or negedge Resetn) begin
    if (~Resetn) begin
		fetch_sp <= S_idle_fetch_sp;
      finish <= 0;
		counter <= 0;
		DP_RAM_address_X_a <= 0;
		DP_RAM_address_X_b <= 0;
		DP_RAM_we_X_a <= 0;
		DP_RAM_address_Sp_a <= 0;
		DP_RAM_write_data_Sp_a <= 0;
		DP_RAM_we_Sp_a <= 0;
		first_time <= 1'b1;
    end else begin
		case(fetch_sp)
			S_idle_fetch_sp: begin 
				finish <= 0;
				counter <= 0;
				DP_RAM_address_X_a <= 0;
				DP_RAM_address_X_b <= 0;
				DP_RAM_we_X_a <= 0;
				DP_RAM_address_Sp_a <= 0;
				DP_RAM_write_data_Sp_a <= 0;
				if (M3_finish) begin 
					DP_RAM_address_X_a <= {counter[5:0], 1'b0};
					DP_RAM_address_X_b <= {counter[5:0], 1'b1};
					counter <= counter + 8'd1;
					DP_RAM_we_Sp_a <= 1'b1;
					fetch_sp <= S_common1_fetch_sp;
				end
			end
			S_common1_fetch_sp: begin 
				if(first_time) begin
					DP_RAM_address_X_a <= {counter[5:0], 1'b0};
					DP_RAM_address_X_b <= {counter[5:0], 1'b1};
				end else begin
					DP_RAM_we_Sp_a <= 1'b1;
					DP_RAM_address_Sp_a <= counter - 8'd2;
					DP_RAM_write_data_Sp_a <= {DP_RAM_read_data_X_a[15:0], DP_RAM_read_data_X_b[15:0]};
				end
				first_time <= 1'b0;
				counter <= counter + 8'd1;
				fetch_sp <= S_common2_fetch_sp;
			end
			S_common2_fetch_sp: begin 
				if (counter == 8'd32) begin
					fetch_sp <= S_leadout_fetch_sp;
				end else begin
					DP_RAM_address_X_a <= {counter[5:0], 1'b0};
					DP_RAM_address_X_b <= {counter[5:0], 1'b1};
				end
				DP_RAM_address_Sp_a <= counter - 8'd2;
				DP_RAM_write_data_Sp_a <= {DP_RAM_read_data_X_a[15:0], DP_RAM_read_data_X_b[15:0]};
				counter <= counter + 8'd1;
			end
			S_leadout_fetch_sp: begin 
				DP_RAM_address_Sp_a <= counter - 8'd2;
				DP_RAM_write_data_Sp_a <= {DP_RAM_read_data_X_a[15:0], DP_RAM_read_data_X_b[15:0]};
				counter <= counter + 8'd1;
				fetch_sp <= S_end_fetch_sp;
			end
			S_end_fetch_sp: begin 
				DP_RAM_address_Sp_a <= counter - 8'd2;
				DP_RAM_write_data_Sp_a <= {DP_RAM_read_data_X_a[15:0], DP_RAM_read_data_X_b[15:0]};
				finish <= 1'b1;
				first_time <= 1'b1;
				DP_RAM_we_Sp_a <= 1'b0;
				fetch_sp <= S_idle_fetch_sp;
			end
			endcase
	 end
end

endmodule