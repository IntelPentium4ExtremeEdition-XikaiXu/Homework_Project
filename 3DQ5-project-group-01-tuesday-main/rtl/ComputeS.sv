`timescale 1ns/100ps
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif

module CS (
	input logic Clock_50,
	input logic Resetn,

	//C dpram
	output logic [6:0] Address_C_a,
	input logic [31:0] Data_out_C_a,
	output logic [6:0] Address_C_b,
	input logic [31:0] Data_out_C_b,

	//Sp dpram <a port token by the Fs>
	output logic [6:0] Address_Sp_b,
	input logic [31:0] Data_out_Sp_b,

	//S dpram
	output logic [6:0] Address_S_a,
	input logic [31:0] Data_out_S_a,
	output logic [6:0] Address_S_b,
	input logic [31:0] Data_out_S_b,
	output logic Write_en_S_b,
	output logic [31:0] Data_in_S_b,

	input logic start,
	output logic finish
);

typedef enum logic [5:0] {
	S_idle,
	S_leadin1,
	S_leadin2,
	S_common1,
	S_common2,
	S_common3,
	S_common4,
	S_common5,
	S_common6,
	S_common7,
	S_common8,
	S_leadout1,
	S_leadout2,
	S_end
} Compute_S_state;

Compute_S_state compute_S_state;

//multplier system
logic [31:0] Mult1_op_1, Mult1_op_2, Mult1_result;
logic [63:0] Mult1_result_long;
logic [31:0] Mult2_op_1, Mult2_op_2, Mult2_result;
logic [63:0] Mult2_result_long;
logic [31:0] Mult3_op_1, Mult3_op_2, Mult3_result;
logic [63:0] Mult3_result_long;

assign Mult1_result_long = Mult1_op_1 * Mult1_op_2;
assign Mult1_result = Mult1_result_long[31:0];
assign Mult2_result_long = Mult2_op_1 * Mult2_op_2;
assign Mult2_result = Mult2_result_long[31:0];
assign Mult3_result_long = Mult3_op_1 * Mult3_op_2;
assign Mult3_result = Mult3_result_long[31:0];

//counter registers
logic [2:0] address_C_counter;
logic [1:0] row_counter;
logic [31:0] S0, S1, S2, S1_buffer, S2_buffer;
logic is_first_time;
logic [1:0] block_counter;
logic [4:0] test_counter;

logic [6:0] sp_b_address,address_offset;
logic [2:0] s_b_offset,address_s_b_counter;
always_ff @(posedge Clock_50 or negedge Resetn ) begin 
	if(~Resetn) begin
		compute_S_state <= S_idle;
		address_C_counter <= 0;
		row_counter <= 0;
		S0 <= 0;
		S1 <= 0;
		S2 <= 0;
		S1_buffer <= 0;
		S2_buffer <= 0;
		is_first_time <= 1'b1;
		sp_b_address <= 7'd40;
		address_offset <= 0;
		Write_en_S_b <= 0;
		test_counter <= 0;
		finish <= 0;
		Address_Sp_b <= 0;
		Address_S_a <= 0;
		Data_in_S_b <= 0;
		address_s_b_counter <= 0;
		s_b_offset <= 0;
		Address_C_a <= 0;
		Address_C_b <= 0;
		Address_S_b <= 0;
		block_counter <= 0;
	end
	else begin
		case (compute_S_state)
		S_idle: begin
			address_C_counter <= 0;
			row_counter <= 0;
			S0 <= 0;
			S1 <= 0;
			S2 <= 0;
			S1_buffer <= 0;
			S2_buffer <= 0;
			is_first_time <= 1'b1;
			sp_b_address <= 7'd40;
			address_offset <= 0;
			Write_en_S_b <= 0;
			test_counter <= 0;
			finish <= 0;
			Address_Sp_b <= 0;
			Address_S_a <= 0;
			Data_in_S_b <= 0;
			address_s_b_counter <= 0;
			s_b_offset <= 0;
			Address_C_a <= 0;
			Address_C_b <= 0;
			Address_S_b <= 0;
			block_counter <= 0;
			if(start) begin 
				compute_S_state <= S_leadin1;
			end
		end
		S_leadin1: begin	
			//read 0
			address_C_counter <= address_C_counter + 1'b1;
			Address_C_a <= {address_C_counter, row_counter};
			Address_C_b <= {address_C_counter, row_counter} + 7'b1;
			
			//call sp_b
			Address_Sp_b <= sp_b_address;

			compute_S_state <= S_leadin2;
		end
		S_leadin2: begin
			//read 4
			address_C_counter <= address_C_counter + 1'b1;
			Address_C_a <= {address_C_counter, row_counter};
			Address_C_b <= {address_C_counter, row_counter} + 7'b1;
			
			//call sp_b
			Address_Sp_b <= sp_b_address - 7'd8;
			sp_b_address <= sp_b_address + 7'd16;

			compute_S_state <= S_common1;
		end
		S_common1: begin
			//read 8
			address_C_counter <= address_C_counter + 1'b1;
			Address_C_a <= {address_C_counter, row_counter};
			Address_C_b <= {address_C_counter, row_counter} + 7'b1;
			
			//Address_s_a
			Address_S_a <= 7'd64 + address_offset;

			//register operation
			S0 <= Mult1_result;
			S1 <= Mult2_result; 
			S2 <= Mult3_result;
			S1_buffer <= S1;
			S2_buffer <= S2;
			if(!is_first_time) begin 
				Write_en_S_b <= 1'b1;
				Data_in_S_b <= S0;
				address_s_b_counter <= address_s_b_counter + 1'b1;
				Address_S_b <= {address_s_b_counter, s_b_offset};
			end

			compute_S_state <= S_common2;

		end
		S_common2: begin
			//read 12
			address_C_counter <= address_C_counter + 1'b1;
			Address_C_a <= {address_C_counter, row_counter};
			Address_C_b <= {address_C_counter, row_counter} + 7'b1;
			
			//call spb 56
			Address_Sp_b <= sp_b_address + address_offset;

			//register operation
			S0 <= Mult1_result + S0;
			S1 <= Mult2_result + S1; 
			S2 <= Mult3_result + S2;
			if(!is_first_time) begin 
				Data_in_S_b <= S1_buffer;
				address_s_b_counter <= address_s_b_counter + 1'b1;
				Address_S_b <= {address_s_b_counter, s_b_offset};
				test_counter <= test_counter + 5'd1;
			end

			compute_S_state <= S_common3;
		end
		S_common3: begin
			//read 16
			address_C_counter <= address_C_counter + 1'b1;
			Address_C_a <= {address_C_counter, row_counter};
			Address_C_b <= {address_C_counter, row_counter} + 7'b1;

			//call spb 48
			Address_Sp_b <= sp_b_address + address_offset - 7'd8;
			sp_b_address <= sp_b_address + 7'd16;



			//register operation
			S0 <= Mult1_result + S0;
			S1 <= Mult2_result + S1; 
			S2 <= Mult3_result + S2;
			
			if((!is_first_time) && (row_counter != 0)) begin 
				Data_in_S_b <= S2_buffer;
				address_s_b_counter <= address_s_b_counter + 1'b1;
				Address_S_b <= {address_s_b_counter, s_b_offset};
			end
			if(block_counter == 2'd0 && !is_first_time) begin
				s_b_offset <= s_b_offset + 3'd1;
			end
			
			compute_S_state <= S_common4;
		end
		S_common4: begin
			//read 20
			address_C_counter <= address_C_counter + 1'b1;
			Address_C_a <= {address_C_counter, row_counter};
			Address_C_b <= {address_C_counter, row_counter} + 7'b1;

			//Address_s_a
			Address_S_a <= 7'd72 + address_offset;

			//register operation
			S0 <= Mult1_result + S0;
			S1 <= Mult2_result + S1; 
			S2 <= Mult3_result + S2;
			Write_en_S_b <= 1'b0;

			compute_S_state <= S_common5;
		end
		S_common5: begin
			//read 24
			address_C_counter <= address_C_counter + 1'b1;
			Address_C_a <= {address_C_counter, row_counter};
			Address_C_b <= {address_C_counter, row_counter} + 7'b1;

			//spbb 72
			Address_Sp_b <= sp_b_address + address_offset;

			//register operation
			S0 <= Mult1_result + S0;
			S1 <= Mult2_result + S1; 
			S2 <= Mult3_result + S2;

			compute_S_state <= S_common6;
		end
		S_common6: begin
			//read 28 
			address_C_counter <= address_C_counter + 1'b1;
			Address_C_a <= {address_C_counter, row_counter};
			Address_C_b <= {address_C_counter, row_counter} + 7'b1;

			//spb
			Address_Sp_b <= sp_b_address + address_offset - 7'd8;
			sp_b_address <= 7'd40;
			if(row_counter == 2'd3) begin
				address_offset <= address_offset + 1'd1;
			end
			
			//counter operation
			if(row_counter == 2'b1) begin
				row_counter <= row_counter + 2'd2;
			end
			else begin
				row_counter <= row_counter + 2'd1;
			end
	
			//register operation
			S0 <= Mult1_result + S0;
			S1 <= Mult2_result + S1; 
			S2 <= Mult3_result + S2;

			compute_S_state <= S_common7;
		end
		S_common7: begin
			//read 1 
			address_C_counter <= address_C_counter + 1'b1;
			Address_C_a <= {address_C_counter, row_counter};
			Address_C_b <= {address_C_counter, row_counter} + 7'b1;

			Address_Sp_b <= sp_b_address + address_offset;

			//register operation
			S0 <= Mult1_result + S0;
			S1 <= Mult2_result + S1; 
			S2 <= Mult3_result + S2;
			compute_S_state <= S_common8;
		end
		S_common8: begin
			//read 5
			address_C_counter <= address_C_counter + 1'b1;
			Address_C_a <= {address_C_counter, row_counter};
			Address_C_b <= {address_C_counter, row_counter} + 7'b1;
			
			//spb
			Address_Sp_b <= sp_b_address + address_offset - 7'd8;
			sp_b_address <= sp_b_address + 7'd16;
			
			//register operation
			S0 <= Mult1_result + S0;
			S1 <= Mult2_result + S1; 
			S2 <= Mult3_result + S2;
			if (block_counter == 2'd2) begin 
				block_counter <= 0;
			end else begin
				block_counter <= block_counter + 2'd1;
			end
			
			if (test_counter == 5'd23) begin 
				compute_S_state <= S_leadout1;
			end else begin
				compute_S_state <= S_common1;
			end
			is_first_time <= 1'b0;
		end
		S_leadout1: begin
			address_s_b_counter <= address_s_b_counter + 1'b1;
			Address_S_b <= {address_s_b_counter, s_b_offset};
			Write_en_S_b <= 1'b1;
			Data_in_S_b <= S0;
			S1_buffer <= S1;
			
			compute_S_state <= S_leadout2;
		end
		S_leadout2: begin
			Address_S_b <= {address_s_b_counter, s_b_offset};
			
			Data_in_S_b <= S1_buffer;
			
			compute_S_state <= S_end;
		end
		S_end: begin			
			finish <= 1'b1;
			Write_en_S_b <= 1'b0;
			compute_S_state <= S_idle;
		end
		endcase
	end
end


//operator director 

always_comb begin
	if((block_counter == 0) || (block_counter == 2'd2)) begin
		Mult1_op_1 = {{16{Data_out_C_a[31]}}, Data_out_C_a[31:16]};
	end else if (block_counter == 2'd1) begin
		Mult1_op_1 = {{16{Data_out_C_a[15]}}, Data_out_C_a[15:0]};
	end else begin
		Mult1_op_1 = 32'd0;
	end

	if (compute_S_state == S_common1 || compute_S_state == S_common2 || compute_S_state == S_common4 || compute_S_state == S_common5 || compute_S_state == S_common7 || compute_S_state == S_common8) begin 
		Mult1_op_2 = $signed(Data_out_Sp_b) >>> 4'd8;
	end else if (compute_S_state == S_common3 || compute_S_state == S_common6) begin
		Mult1_op_2 = $signed(Data_out_S_a) >>> 4'd8;
	end else begin
		Mult1_op_2 = 32'd0;
	end 
end

always_comb begin
	if((block_counter == 0) || (block_counter == 2'd2)) begin
		Mult2_op_1 = {{16{Data_out_C_a[15]}}, Data_out_C_a[15:0]};
	end else if (block_counter == 2'd1) begin
		Mult2_op_1 = {{16{Data_out_C_b[31]}}, Data_out_C_b[31:16]};
	end else begin
		Mult2_op_1 = 32'd0;
	end

	if (compute_S_state == S_common1 || compute_S_state == S_common2 || compute_S_state == S_common4 || compute_S_state == S_common5 || compute_S_state == S_common7 || compute_S_state == S_common8) begin 
		Mult2_op_2 = $signed(Data_out_Sp_b) >>> 4'd8;
	end
	else if (compute_S_state == S_common3 || compute_S_state == S_common6) begin
		Mult2_op_2 = $signed(Data_out_S_a) >>> 4'd8;
	end
	else begin
		Mult2_op_2 = 32'd0;
	end 
end

always_comb begin
	if((block_counter == 0) || (block_counter == 2'd2)) begin
		Mult3_op_1 = {{16{Data_out_C_b[31]}}, Data_out_C_b[31:16]};
	end else if (block_counter == 2'd1) begin
		Mult3_op_1 = {{16{Data_out_C_b[15]}}, Data_out_C_b[15:0]};
	end else begin
		Mult3_op_1 = 32'd0;
	end

	if (compute_S_state == S_common1 || compute_S_state == S_common2 || compute_S_state == S_common4 || compute_S_state == S_common5 || compute_S_state == S_common7 || compute_S_state == S_common8) begin 
		Mult3_op_2 = $signed(Data_out_Sp_b) >>> 4'd8;
	end
	else if (compute_S_state == S_common3 || compute_S_state == S_common6) begin
		Mult3_op_2 = $signed(Data_out_S_a) >>> 4'd8;
	end
	else begin
		Mult3_op_2 = 32'd0;
	end 
end

endmodule