`timescale 1ns/100ps
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif
//define Fetch logic

module WriteS (
	input logic Clock_50,
	input logic Resetn,

	output logic [17:0] SRAM_address,
   output logic [15:0] SRAM_write_data,
	output logic SRAM_we_n,
	
	output logic [6:0] Address_S_a,
	input logic [31:0] Data_out_S_a,

	input logic [8:0] RA_init,
	input logic [8:0] CA_init,

	input logic start,
	output logic finish,	
	input logic Y_finished
);

logic [1:0] CA;
logic [2:0] RA;
logic [7:0] S_read_counter; 
logic [7:0] Reg_for_X0;
logic [17:0] WB_offset;
logic is_first_time;

typedef enum logic [3:0] {
	WB_idle,
	WB_leadin1,
	WB_leadin2,
	WB_common1,
	WB_common2,
	WB_leadout,
	WB_end
} WB_S_state;

WB_S_state wb_s_state;

always_ff @( posedge Clock_50 or negedge Resetn) begin
	if(~Resetn) begin
		RA <= 0;
		CA <= 0;
		S_read_counter <= 0;
		finish <= 0;
		wb_s_state <= WB_idle;
		SRAM_address <= 0;
		SRAM_write_data <= 0;
		Address_S_a <= 0;
		Reg_for_X0 <= 0;
		is_first_time <= 1'b1;
		SRAM_we_n <= 1'b1;
	end
	else begin
		case(wb_s_state)
		WB_idle: begin
			RA <= 0;
			CA <= 0;
			finish <= 0;
			S_read_counter <= 0;
			is_first_time <= 1'b1;
			SRAM_we_n <= 1'b1;
			Address_S_a <= 0;
			Reg_for_X0 <= 0;
			SRAM_write_data <= 0;
			if (start) wb_s_state <= WB_leadin1;	
		end
		WB_leadin1: begin
			Address_S_a <= S_read_counter;
			S_read_counter <= S_read_counter + 8'b1;
			
			wb_s_state <= WB_leadin2;
		end
		WB_leadin2: begin
			Address_S_a <= S_read_counter;
			S_read_counter <= S_read_counter + 8'b1;
			
			wb_s_state <= WB_common1;
		end
		WB_common1: begin
			Address_S_a <= S_read_counter;
			S_read_counter <= S_read_counter + 8'b1;
			if (Data_out_S_a[31]) begin 
				Reg_for_X0 <= 8'd0;
			end else if (|Data_out_S_a[30:24]) begin 
				Reg_for_X0 <= 8'd255;
			end else begin 
				Reg_for_X0 <= Data_out_S_a[23:16];
			end
				
				
			if(!is_first_time) begin
				CA <= CA + 1'b1;
			end
			wb_s_state <= WB_common2;
			SRAM_we_n <= 1'b1;
		end
		WB_common2: begin
			Address_S_a <= S_read_counter;
			S_read_counter <= S_read_counter + 8'b1;
			
			//sram operation
			SRAM_we_n <= 1'b0;
			SRAM_address <= WB_offset;
			if (Data_out_S_a[31]) begin 
				SRAM_write_data <= {Reg_for_X0, 8'd0};
			end else if (|Data_out_S_a[30:24]) begin 
				SRAM_write_data <= {Reg_for_X0, 8'd255};
			end else begin 
				SRAM_write_data <= {Reg_for_X0, Data_out_S_a[23:16]};
			end
			
			if(CA == 2'd3) RA <= RA + 1'b1;
			if(S_read_counter > 8'd63) begin
				wb_s_state <= WB_end;
			end else begin
				wb_s_state <= WB_common1;
			end
			is_first_time <= 1'b0;
		end
		WB_end: begin
			finish <= 1'b1;
			SRAM_we_n <= 1'b1;
			wb_s_state <= WB_idle;
		end
		endcase
	end
end

always_comb begin
	if(!Y_finished) begin
		WB_offset = ((RA + RA_init) << 9'd7) + ((RA + RA_init) << 9'd5) + CA + CA_init;
	end else begin
		WB_offset = 18'd38400 + ((RA + RA_init) << 9'd6) + ((RA + RA_init) << 9'd4) + CA + CA_init;
	end
		
end

//assign WB_offset = ((RA + RA_init) << 9'd7) + ((RA + RA_init) << 9'd5) + CA + CA_init;

endmodule