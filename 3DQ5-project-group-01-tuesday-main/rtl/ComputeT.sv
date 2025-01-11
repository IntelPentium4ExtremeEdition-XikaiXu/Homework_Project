`timescale 1ns/100ps
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif

module CT (
	input logic Clock_50,
	input logic Resetn,

	//C dpram
	output logic [6:0] Address_C_a,
	input logic [31:0] Data_out_C_a,
	output logic [6:0] Address_C_b,
	input logic [31:0] Data_out_C_b,

	//Sp dpram
	output logic [6:0] Address_Sp_a,
	input logic [31:0] Data_out_Sp_a,
	output logic [6:0] Address_Sp_b,
	input logic [31:0] Data_out_Sp_b,
	output logic Write_en_Sp_b,
	output logic [31:0] Data_in_Sp_b,

	//S dpram
	output logic [6:0] Address_S_b,
	output logic Write_en_S_b,
	output logic [31:0] Data_in_S_b,

	input logic start,
	output logic finish
);

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

//reg system on thye chip[Heap]
logic [15:0] Sp_buffer, C_buffer, C_buffer2;
logic [31:0] T0,T1,T2;
logic [31:0] T0_buffer, T2_buffer;

//counter system
logic [3:0] operation_counter;
logic [4:0] C_counter, C_last_state;
logic is_first_time;
logic even_col, end_col;
logic [1:0] even_col_counter;

//reg system pointer postion with offest 
logic [6:0] T1_buffer_dp_offset, T2_buffer_dp_offset;
logic [6:0] Address_C_offset,Address_Sp_a_offset,Address_Sp_b_offset;
logic [31:0] T0_result_buffer, T1_result_buffer;


//case system
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
	S_leadout3,
	S_leadout4,
	S_end
} Compute_T_state;
Compute_T_state compute_T_state;

always_ff @(posedge Clock_50 or negedge Resetn) begin
	if(~Resetn) begin
		//system basic condition initial
		compute_T_state <= S_idle;
		finish <= 0;

		//io initial
		Address_C_a <= 0;
		Address_C_b <= 0;
		Address_Sp_a <= 0;
		Address_Sp_b <= 0;
		Write_en_Sp_b <= 0;
		Data_in_Sp_b <= 0;
		Address_S_b <= 0;
		Data_in_S_b <= 0;
		Write_en_S_b <= 0;
		
		//buffer content initial
		Sp_buffer <= 0; 
		C_buffer <= 0; 
		C_buffer2 <= 0;
		T0 <= 0;
		T1 <= 0;
		T2 <= 0;
		T0_buffer <= 0;
		T2_buffer <= 0;
		T0_result_buffer <= 0;
		T1_result_buffer <= 0;

		//mem location pointer initial
		C_counter <= 0;
		operation_counter <= 0;
		C_last_state <= 0;
		T1_buffer_dp_offset <= 7'd32;
		T2_buffer_dp_offset <= 7'd64;
		Address_Sp_a_offset <= 0;
		
		
		//counter initial
		is_first_time <= 1'b1;
		even_col_counter <= 2'd1;
		even_col <= 1'b1;
		end_col <= 0;
	end
	else begin
		case(compute_T_state)
		S_idle: begin
			finish <= 1'b0;
			//io initial
			Address_C_a <= 0;
			Address_C_b <= 0;
			Address_Sp_a <= 0;
			Address_Sp_b <= 0;
			Write_en_Sp_b <= 0;
			Data_in_Sp_b <= 0;
			Address_S_b <= 0;
			Data_in_S_b <= 0;
			Write_en_S_b <= 0;
			
			//buffer content initial
			Sp_buffer <= 0; 
			C_buffer <= 0; 
			C_buffer2 <= 0;
			T0 <= 0;
			T1 <= 0;
			T2 <= 0;
			T0_buffer <= 0;
			T2_buffer <= 0;
			T0_result_buffer <= 0;
			T1_result_buffer <= 0;
			//mem location pointer initial
			C_counter <= 0;
			operation_counter <= 0;
			C_last_state <= 0;
			T1_buffer_dp_offset <= 7'd32;
			T2_buffer_dp_offset <= 7'd64;
			Address_Sp_a_offset <= 0;
			//counter initial
			is_first_time <= 1'd1;
			even_col_counter <= 2'd1;
			even_col <= 1'b1;
			end_col <= 0;
			if(start) begin 
				compute_T_state <= S_leadin1;
			end
		end
		S_leadin1: begin
			//address operation
			Address_C_a <= Address_C_offset;
			Address_C_b <= Address_C_offset + 7'd4;
			Address_Sp_a <= Address_Sp_a_offset;
			Address_Sp_b <= Address_Sp_a_offset + 7'd4;

			//counter operation
			C_counter <= C_counter + 1'b1;
			C_last_state <= C_counter;

			//Quirks 
			compute_T_state <= S_leadin2;
		end
		S_leadin2: begin
			//address operation
			Address_Sp_a <= Address_Sp_a_offset + 7'd8;
			Address_Sp_a_offset <= Address_Sp_a_offset + 1'b1; //for next initial value 

			//Quirks 
			compute_T_state <= S_common1;
		end
		S_common1: begin
			
			//address operation
			Address_C_a <= Address_C_offset;
			Address_C_b <= Address_C_offset + 7'd4;
			Address_Sp_a <= Address_Sp_a_offset;
			Address_Sp_b <= Address_Sp_a_offset + 7'd4;						
			
			//counter operation
			C_counter <= C_counter + 1'b1;

			//register operation
			Sp_buffer <= Data_out_Sp_b[15:0];
			if (even_col) begin
				C_buffer <= Data_out_C_a[31:16];
				C_buffer2 <= Data_out_C_b[31:16];
			end else begin 
				C_buffer <= Data_out_C_a[15:0];
				C_buffer2 <= Data_out_C_b[15:0];
			end
			T1 <= Mult2_result;
			T0 <= Mult1_result + Mult3_result;
			if(is_first_time == 1'b0) begin
				if ((operation_counter == 4'd4 || operation_counter == 4'd1) && T1_buffer_dp_offset > 7'd32) begin 
					T1_buffer_dp_offset <= T1_buffer_dp_offset - 7'd47;
					T2_buffer_dp_offset <= T2_buffer_dp_offset - 7'd15;
				end 
				T2 <= T2 + T2_buffer;
				T0_result_buffer <= T0;
				T1_result_buffer <= T1;
			end
	
			//Quirks
			compute_T_state <= S_common2;
		end
		S_common2: begin
			//address operation
			if(~&even_col_counter) Address_Sp_a <= Address_Sp_a_offset + 7'd8;
			Address_Sp_a_offset <= Address_Sp_a_offset + 1'b1;


			//counter operation

			//register opeartion
			T1 <= T1 + Mult2_result;
			T2 <= Mult1_result + Mult3_result;
			if(!is_first_time) begin
				//address opearion
				Address_Sp_b <= T1_buffer_dp_offset;
				T1_buffer_dp_offset <= T1_buffer_dp_offset + 7'd8;
				Data_in_Sp_b <= T1_result_buffer;
				Write_en_Sp_b <= 1'b1;
				if (!end_col) begin 
					Address_S_b <= T2_buffer_dp_offset;
					T2_buffer_dp_offset <= T2_buffer_dp_offset + 7'd8;
					Data_in_S_b <= T2;
					Write_en_S_b <= 1'b1;
				end
			end	

			//Quirks
			compute_T_state <= S_common3;
		end
		S_common3: begin
			//address operation
			Address_C_a <= Address_C_offset;
			Address_C_b <= Address_C_offset + 7'd4;
			
			Address_Sp_a <= Address_Sp_a_offset;
			Address_Sp_b <= Address_Sp_a_offset + 7'd4;
			Write_en_S_b <= 1'b0;

			//counter operation
			C_counter <= C_counter + 1'b1;
			//register opeartion
			Sp_buffer <= Data_out_Sp_b[15:0];
			if (even_col) begin
				C_buffer <= Data_out_C_a[31:16];
				C_buffer2 <= Data_out_C_b[31:16];
			end else begin 
				C_buffer <= Data_out_C_a[15:0];
				C_buffer2 <= Data_out_C_b[15:0];
			end
			T0 <= T0 + Mult1_result;
			T1 <= T1 + Mult2_result;
			T0_buffer <= Mult3_result;
			
			//Quirks
			Write_en_Sp_b <= 0;
			compute_T_state	<= S_common4;
		end
		S_common4: begin
			//address operation
			if(~&even_col_counter) Address_Sp_a <= Address_Sp_a_offset + 7'd8;
			Address_Sp_a_offset <= Address_Sp_a_offset + 1'b1;

			//counter operation

			//register opeartion
			T0 <= T0 + T0_buffer;
			T1 <= T1 + Mult2_result;
			T2 <= T2 + Mult1_result;
			T2_buffer <= Mult3_result;
			if (!is_first_time) begin 
				Address_Sp_b <= T1_buffer_dp_offset;
				T1_buffer_dp_offset <= T1_buffer_dp_offset + 7'd8;
				Data_in_Sp_b <= T0_result_buffer;
				Write_en_Sp_b <= 1'b1;
			end

			//Quirks
			compute_T_state	<= S_common5;
		end
		S_common5: begin
			//address operation
			Address_C_a <= Address_C_offset;
			Address_C_b <= Address_C_offset + 7'd4;

			Address_Sp_a <= Address_Sp_a_offset;
			Address_Sp_b <= Address_Sp_a_offset + 7'd4;

			//counter operation 
			if(operation_counter == 4'd5) begin 
				C_counter <= C_counter + 1'b1;
			end else begin 
				C_counter <= C_last_state;
			end
			
			//register operation
			Sp_buffer <= Data_out_Sp_b[15:0];
			if (even_col) begin
				C_buffer <= Data_out_C_a[31:16];
				C_buffer2 <= Data_out_C_b[31:16];
			end else begin 
				C_buffer <= Data_out_C_a[15:0];
				C_buffer2 <= Data_out_C_b[15:0];
			end
			T0 <= T0 + Mult1_result;
			T1 <= T1 + Mult2_result;
			T2 <= T2 + T2_buffer;
			T0_buffer <= Mult3_result;
			
			Write_en_Sp_b <= 1'b0;
			compute_T_state <= S_common6;
		end
		S_common6: begin
			//address operation
			Address_Sp_a <= Address_Sp_a_offset + 7'd8;
			if(~&even_col_counter) Address_Sp_a_offset <= Address_Sp_a_offset + 7'd9;
			
			//counter operation
			C_last_state <= C_counter;

			//register operation
			T0 <= T0 + T0_buffer;
			T1 <= T1 + Mult2_result;
			T2 <= T2 + Mult1_result;
			T2_buffer <= Mult3_result;

			compute_T_state	<= S_common7;
		end
		S_common7: begin
			//address operation
			Address_C_a <= Address_C_offset;
			Address_C_b <= Address_C_offset + 7'd4;
			
			if (operation_counter == 4'd2 || operation_counter == 4'd5) begin
				Address_Sp_a_offset <= 0;
				Address_Sp_a <= 0;
				Address_Sp_b <= 7'd4;
			end else begin
				Address_Sp_a <= Address_Sp_a_offset;
				Address_Sp_b <= Address_Sp_a_offset + 7'd4;
			end

			//counter operation
			C_counter <= C_counter + 1'b1;
			

			//register opearion 
			Sp_buffer <= Data_out_Sp_b[15:0];
			if (even_col) begin
				C_buffer <= Data_out_C_a[31:16];
				C_buffer2 <= Data_out_C_b[31:16];
			end else begin 
				C_buffer <= Data_out_C_a[15:0];
				C_buffer2 <= Data_out_C_b[15:0];
			end
			T0 <= T0 + Mult1_result;
			T1 <= T1 + Mult2_result;
			T2 <= T2 + T2_buffer;
			T0_buffer <= Mult3_result;

			compute_T_state	<= S_common8;
		end
		S_common8: begin
			//address opearation
			if(operation_counter == 4'd2 || operation_counter == 4'd5) begin
				Address_Sp_a <= Address_Sp_a_offset + 7'd8;
			end else if(even_col_counter[0] && !even_col_counter[1]) begin
				Address_Sp_a <= Address_Sp_a_offset + 7'd8;
			end
			Address_Sp_a_offset <= Address_Sp_a_offset + 1'b1;
			

			//counter opeartion
			if(even_col_counter == 2'd3) begin
				end_col <= 1'b1;
				even_col <= ~even_col;
				even_col_counter <= 2'd1;
			end else begin 
				even_col_counter <= even_col_counter + 2'd1;
				end_col <= 1'b0;
			end
			
			if(operation_counter == 4'd5) begin 
				operation_counter <= 0;
			end else begin 
				operation_counter <= operation_counter + 4'd1;
			end
			
			//register operation
			T0 <= T0 + T0_buffer;
			T1 <= T1 + Mult2_result;
			T2 <= T2 + Mult1_result;
			T2_buffer <= Mult3_result;

			//quirks
			is_first_time <= 0;
			if (T1_buffer_dp_offset == 7'd71) begin 
				compute_T_state <= S_leadout1;
			end
			else begin 
				compute_T_state <= S_common1;
			end
			
		end
		S_leadout1: begin
			//address operation
			T2 <= T2 + T2_buffer;
			T0_result_buffer <= T0;
			T1_result_buffer <= T1;

			//quirks
			compute_T_state <= S_leadout2;
		end
		S_leadout2: begin
			//address opearion
			Address_Sp_b <= T1_buffer_dp_offset;
			T1_buffer_dp_offset <= T1_buffer_dp_offset + 7'd8;
			Data_in_Sp_b <= T1_result_buffer;
			Write_en_Sp_b <= 1'b1;

			//Quirks
			compute_T_state <= S_leadout3;
		end
		S_leadout3: begin
			compute_T_state <= S_leadout4;
			Write_en_Sp_b <= 0;
		end
		S_leadout4: begin 
			Address_Sp_b <= T1_buffer_dp_offset;
			Data_in_Sp_b <= T0_result_buffer;
			Write_en_Sp_b <= 1'b1;
			compute_T_state <= S_end;
		end
		S_end: begin
			finish <= 1'b1;
			Write_en_Sp_b <= 1'b0;
			Write_en_S_b <= 1'b0;
			compute_T_state <= S_idle;
		end
		endcase
	end
end

assign Address_C_offset = {C_counter[1:0], C_counter[4:2]};

//operator director 
always_comb begin
	if (compute_T_state == S_common1 || compute_T_state == S_common3 || compute_T_state == S_common5 || compute_T_state == S_common7) begin 
		Mult1_op_1 = {{16{Data_out_Sp_a[31]}}, Data_out_Sp_a[31:16]};
		if (even_col) begin 
			Mult1_op_2 = {{16{Data_out_C_a[31]}}, Data_out_C_a[31:16]};
		end else begin 
			Mult1_op_2 = {{16{Data_out_C_a[15]}}, Data_out_C_a[15:0]};
		end
	end
	else if (compute_T_state == S_common2 || compute_T_state == S_common4 || compute_T_state == S_common6 || compute_T_state == S_common8) begin
		Mult1_op_1 = {{16{Data_out_Sp_a[31]}}, Data_out_Sp_a[31:16]};
		Mult1_op_2 = {{16{C_buffer[15]}}, C_buffer};
	end
	else begin
		Mult1_op_1 = 32'd0;
		Mult1_op_2 = 32'd0;
	end 
end

always_comb begin 
	if (compute_T_state == S_common1 || compute_T_state == S_common3 || compute_T_state == S_common5 || compute_T_state == S_common7) begin 
		Mult2_op_1 = {{16{Data_out_Sp_b[31]}}, Data_out_Sp_b[31:16]};
		if (even_col) begin 
			Mult2_op_2 = {{16{Data_out_C_a[31]}}, Data_out_C_a[31:16]};
		end else begin 
			Mult2_op_2 = {{16{Data_out_C_a[15]}}, Data_out_C_a[15:0]};
		end
	end
	else if (compute_T_state == S_common2 || compute_T_state == S_common4 || compute_T_state == S_common6 || compute_T_state == S_common8) begin
		Mult2_op_1 = {{16{Sp_buffer[15]}}, Sp_buffer};
		Mult2_op_2 = {{16{C_buffer2[15]}}, C_buffer2};
	end
	else begin
		Mult2_op_1 = 32'd0;
		Mult2_op_2 = 32'd0;
	end 
end
			
always_comb begin
	if (compute_T_state == S_common1 || compute_T_state == S_common3 || compute_T_state == S_common5 || compute_T_state == S_common7) begin 
		Mult3_op_1 = {{16{Data_out_Sp_a[15]}}, Data_out_Sp_a[15:0]};
		if (even_col) begin 
			Mult3_op_2 = {{16{Data_out_C_b[31]}}, Data_out_C_b[31:16]};
		end else begin 
			Mult3_op_2 = {{16{Data_out_C_b[15]}}, Data_out_C_b[15:0]};
		end
	end 
	else if (compute_T_state == S_common2 || compute_T_state == S_common4 || compute_T_state == S_common6 || compute_T_state == S_common8) begin
		Mult3_op_1 = {{16{Data_out_Sp_a[15]}}, Data_out_Sp_a[15:0]};
		Mult3_op_2 = {{16{C_buffer2[15]}}, C_buffer2};
	end 
	else begin
		Mult3_op_1 = 32'd0;
		Mult3_op_2 = 32'd0;
	end 
end

endmodule