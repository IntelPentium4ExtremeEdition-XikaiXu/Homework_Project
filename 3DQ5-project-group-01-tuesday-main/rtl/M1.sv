//Milestone 1

`timescale 1ns/100ps
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif

module M1 (
	input logic Clock_50,
	input logic Resetn,
	output logic [17:0] SRAM_address,
	output logic [15:0] SRAM_write_data,
	output logic SRAM_we_n,
	input logic [15:0] SRAM_read_data,
	input logic start,
	output logic finish	
);

//For design extension
logic [17:0] Y_memlocation;
logic [17:0] U_memlocation;
logic [17:0] V_memlocation;
logic [17:0] RGB_memlocation;


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

logic [7:0] U_5m, U_5p, U_3m, U_3p, U_1m, U_1p, V_5m, V_5p, V_3m, V_3p, V_1m, V_1p; //V
logic [31:0] Vp_even, Up_even, Vp_odd_buffer, Up_odd_buffer, Vp_odd, Up_odd; //V
logic [7:0] U_buffer, V_buffer; //V
logic [31:0] aYo, aYe;
logic [7:0] Re,Ge,Be,Ro,Go,Bo; //V
logic [15:0] Y_buffer; //V 
logic [31:0] Re_buffer, Ge_buffer, Be_buffer, Ro_buffer, Go_buffer, Bo_buffer;

typedef enum logic [4:0] {
	idle,
	S_common_cycle0,
	S_common_cycle1,
	S_common_cycle2,
	S_common_cycle3,
	S_common_cycle4,
	S_common_cycle5,
	S_common_cycle6,
	S_leadin_cycle0,
	S_leadin_cycle1,
	S_leadin_cycle2,
	S_leadin_cycle3,
	S_leadin_cycle4,
	S_leadin_cycle5,
	S_leadin_cycle6,
	S_leadin_cycle7,
	S_leadout_cycle0,
	S_leadout_cycle1,
	S_leadout_cycle2,
	end_statement
	} sysIO;
	
sysIO sysio;

logic odd_even_cycle;

logic new_row;
logic [17:0] Y_offset, UV_offset, RGB_offset;
logic [7:0] pixel_counter;


always_ff @(posedge Clock_50 or negedge Resetn) begin
	if (~Resetn) begin
		finish <= 1'b0;
		odd_even_cycle <= 0;
		sysio <= idle;
		U_5m <= 0;
		U_5p <= 0;
		U_3m <= 0;
		U_3p <= 0;
		U_1m <= 0;		
		U_1p <= 0;
		V_5m <= 0;
		V_5p <= 0;			
		V_3m <= 0;
		V_3p <= 0;
		V_1m <= 0;
		V_1p <= 0;
		Vp_even <= 0;
		Up_even <= 0;
		Vp_odd_buffer <= 0;
		Up_odd_buffer <= 0;
		aYo <= 0;
		aYe <= 0;
		Re <= 0;
		Ge <= 0;
		Be <= 0;
		Ro <= 0;
		Go <= 0;
		Bo <= 0;
		Y_buffer <= 0;
		U_buffer <= 0;
		V_buffer <= 0;
		Y_offset <= 0;
		UV_offset <= 0;
		RGB_offset <= 0;
		pixel_counter <= 0;
		new_row <= 1'b1;
		SRAM_address <= 0;
		SRAM_write_data <= 0;
		SRAM_we_n <= 1'b1;		
		Y_memlocation <= 0;
		U_memlocation <= 18'd38400;
		V_memlocation <= 18'd57600;
		RGB_memlocation <= 18'd146944;
		Re_buffer <= 0;
		Ge_buffer <= 0;
		Be_buffer <= 0;
		Ro_buffer <= 0;
		Go_buffer <= 0;
		Bo_buffer <= 0;
		odd_even_cycle <= 0;
	end else begin
		case (sysio)
		idle: begin
			finish <= 1'b0;
			if (start) begin
				sysio <= S_leadin_cycle0; //clk 0 
			end
		end
		S_leadin_cycle0: begin 
			SRAM_address <= U_memlocation + UV_offset;
			SRAM_we_n <= 1'b1;
			sysio <= S_leadin_cycle1;
		end
		S_leadin_cycle1: begin
			SRAM_address <= V_memlocation + UV_offset; 
			UV_offset <= UV_offset + 1'b1; //for next addr 
			sysio <= S_leadin_cycle2;
		end
		S_leadin_cycle2: begin
			SRAM_address <= U_memlocation + UV_offset; 
			sysio <= S_leadin_cycle3;
		end
		S_leadin_cycle3: begin 
			SRAM_address <= V_memlocation + UV_offset;
			UV_offset <= UV_offset + 1'b1;
			U_1m <= SRAM_read_data[15:8];
			U_1p <= SRAM_read_data[7:0];
			U_5m <= SRAM_read_data[15:8];
			U_3m <= SRAM_read_data[15:8]; 
			Up_even <= {24'b0, SRAM_read_data[15:8]} - 32'd128;
			sysio <= S_leadin_cycle4;
		end
		S_leadin_cycle4: begin
			SRAM_address <= Y_memlocation + Y_offset;
			Y_offset <= Y_offset + 1'b1; //for next 
			V_1m <= SRAM_read_data[15:8]; 
			V_1p <= SRAM_read_data[7:0];
			V_3m <= SRAM_read_data[15:8];
			V_5m <= SRAM_read_data[15:8];
			Vp_even <= {24'b0, SRAM_read_data[15:8]} - 32'd128;
			sysio <= S_leadin_cycle5;
		end
		S_leadin_cycle5: begin 
			U_3p <= SRAM_read_data[15:8];
			U_5p <= SRAM_read_data[7:0];
			sysio <= S_leadin_cycle6;
		end
		S_leadin_cycle6: begin
			V_3p <= SRAM_read_data[15:8];
			V_5p <= SRAM_read_data[7:0];
			sysio <= S_leadin_cycle7;
		end
		S_leadin_cycle7: begin
			Y_buffer <= SRAM_read_data;
			sysio <= S_common_cycle0;
		end
		S_common_cycle0: begin
			aYe <= Mult3_result;
			if (!new_row) begin 
				SRAM_write_data <= {Re, Ge};
				SRAM_address <= RGB_memlocation + RGB_offset;
			   RGB_offset <= RGB_offset + 1'b1;
				SRAM_we_n <= 1'b0;
				if (Ro_buffer[31]) begin 
					Ro <= 8'd0;
				end else if (|Ro_buffer[30:24]) begin 
					Ro <= 8'd255;
				end else begin 
					Ro <= Ro_buffer[23:16];
				end
				if (Go_buffer[31]) begin 
					Go <= 8'd0;
				end else if (|Go_buffer[30:24]) begin 
					Go <= 8'd255;
				end else begin 
					Go <= Go_buffer[23:16];
				end
				if (pixel_counter >= 8'd156) begin 
					U_5p <= U_5p;
				end else begin
					if (odd_even_cycle) begin
						U_5p <= SRAM_read_data[15:8];
						U_buffer <= SRAM_read_data[7:0];
					end else begin 
						U_5p <= U_buffer;
					end
				end
				U_3p <= U_5p;
				U_1p <= U_3p;
				U_1m <= U_1p;
				U_3m <= U_1m;
				U_5m <= U_3m;
			end
			sysio <= S_common_cycle1;
		end
		S_common_cycle1: begin 
			Re_buffer <= Mult3_result + aYe;
			Up_odd_buffer <= Mult1_result;
			if (!new_row) begin 
				SRAM_write_data <= {Be, Ro};
				SRAM_address <= RGB_memlocation + RGB_offset;
			   RGB_offset <= RGB_offset + 1'b1;
				if (pixel_counter >= 8'd156) begin 
					V_5p <= V_5p;
				end else begin
					if (odd_even_cycle) begin
						V_5p <= SRAM_read_data[15:8];
						V_buffer <= SRAM_read_data[7:0];
					end else begin 
						V_5p <= V_buffer;
					end
				end
				V_3p <= V_5p;
				V_1p <= V_3p;
				V_1m <= V_1p;
				V_3m <= V_1m;
				V_5m <= V_3m;
			end
			sysio <= S_common_cycle2;
		end 
		S_common_cycle2: begin
			if (Re_buffer[31]) begin 
				Re <= 8'd0;
			end else if (|Re_buffer[30:24]) begin 
				Re <= 8'd255;
			end else begin 
				Re <= Re_buffer[23:16];
			end
			Up_odd <= Up_odd_buffer;
			Up_odd_buffer <= Mult1_result;
			Vp_odd_buffer <= Mult2_result;
			Ge_buffer <= aYe - Mult3_result;
			if (!new_row) begin 
				SRAM_write_data <= {Go, Bo};
				SRAM_address <= RGB_memlocation + RGB_offset;
				RGB_offset <= RGB_offset + 1'b1;
				pixel_counter <= pixel_counter + 1'b1;
			end
			sysio <= S_common_cycle3;
		end 
		S_common_cycle3: begin
			SRAM_we_n <= 1'b1;
			SRAM_address <= Y_memlocation + Y_offset;
			Y_offset <= Y_offset + 1'b1;
			Up_odd <= Up_odd - Up_odd_buffer;
			Up_odd_buffer <= Mult1_result;
			Vp_odd <= Vp_odd_buffer;
			Vp_odd_buffer <= Mult2_result;
			Ge_buffer <= Ge_buffer - Mult3_result;
			sysio <= S_common_cycle4;
		end
		S_common_cycle4: begin
			if (!odd_even_cycle) begin
				SRAM_address <= U_memlocation + UV_offset;
			end
			if (Ge_buffer[31]) begin 
				Ge <= 8'd0;
			end else if (|Ge_buffer[30:24]) begin 
				Ge <= 8'd255;
			end else begin 
				Ge <= Ge_buffer[23:16];
			end
			Up_odd <= $signed($signed(Up_odd + Up_odd_buffer + 32'd128) >>> 4'd8) - 32'd128;
			Vp_odd <= Vp_odd - Vp_odd_buffer;
			aYo <= Mult1_result;
			Vp_odd_buffer <= Mult2_result;
			Be_buffer <= aYe + Mult3_result;
			sysio <= S_common_cycle5;
		end
		S_common_cycle5: begin
			if (!odd_even_cycle) begin
				SRAM_address <= V_memlocation + UV_offset;
				UV_offset <= UV_offset + 1'b1;
			end
			if (Be_buffer[31]) begin 
				Be <= 8'd0;
			end else if (|Be_buffer[30:24]) begin 
				Be <= 8'd255;
			end else begin 
				Be <= Be_buffer[23:16];
			end
			Vp_odd <= $signed($signed(Vp_odd + Vp_odd_buffer + 32'd128) >>> 4'd8) - 32'd128;
			Bo_buffer <= Mult2_result + aYo;
			Go_buffer <= aYo - Mult3_result;
			sysio <= S_common_cycle6;
		end
		S_common_cycle6: begin
			new_row <= 1'b0;
			odd_even_cycle <= ~odd_even_cycle;
			Up_even <= {24'b0, U_1p} - 32'd128;
			Vp_even <= {24'b0, V_1p} - 32'd128;
			Go_buffer <= Go_buffer - Mult1_result;
			Ro_buffer <= aYo + Mult2_result;
			Y_buffer <= SRAM_read_data;
			if (Bo_buffer[31]) begin 
				Bo <= 8'd0;
			end else if (|Bo_buffer[30:24]) begin 
				Bo <= 8'd255;
			end else begin 
				Bo <= Bo_buffer[23:16];
			end
			if (pixel_counter == 8'd159) begin 
				sysio <= S_leadout_cycle0;
			end else begin
				sysio <= S_common_cycle0;
			end
		end
		S_leadout_cycle0: begin 
			SRAM_write_data <= {Re, Ge};
			SRAM_address <= RGB_memlocation + RGB_offset;
			RGB_offset <= RGB_offset + 1'b1;
			SRAM_we_n <= 1'b0;
			pixel_counter <= 8'b0;
			UV_offset <= UV_offset - 2'd2;
			Y_offset <= Y_offset - 1'd1;
			new_row <= 1'b1;
			if (Ro_buffer[31]) begin 
				Ro <= 8'd0;
			end else if (|Ro_buffer[30:24]) begin 
				Ro <= 8'd255;
			end else begin 
				Ro <= Ro_buffer[23:16];
			end
			if (Go_buffer[31]) begin 
				Go <= 8'd0;
			end else if (|Go_buffer[30:24]) begin 
				Go <= 8'd255;
			end else begin 
				Go <= Go_buffer[23:16];
			end
			sysio <= S_leadout_cycle1;
		end
		S_leadout_cycle1: begin 
			SRAM_write_data <= {Be, Ro};
			SRAM_address <= RGB_memlocation + RGB_offset;
			RGB_offset <= RGB_offset + 1'b1;
			sysio <= S_leadout_cycle2;
		end
		S_leadout_cycle2: begin 
			SRAM_write_data <= {Go, Bo};
			SRAM_address <= RGB_memlocation + RGB_offset;
			RGB_offset <= RGB_offset + 1'b1;
			
			if (RGB_offset > 18'd115198) begin
				sysio <= end_statement;
			end else begin
				sysio <= S_leadin_cycle0;
			end
		end
		end_statement: begin
			SRAM_we_n <= 1'b1;
			SRAM_address <= 1'b0;
			finish <= 1'b1;
			sysio <= idle;
		end
		endcase
	end
end

always_comb begin
	if (sysio == S_common_cycle1) begin 
		Mult1_op_1 = {24'd0, U_5p} + {24'd0, U_5m};
		Mult1_op_2 = 32'd21;
	end else if (sysio == S_common_cycle2) begin
		Mult1_op_1 =  {24'd0, U_3p} + {24'd0, U_3m};
		Mult1_op_2 = 32'd52;
	end else if (sysio == S_common_cycle3) begin
		Mult1_op_1 = {24'd0, U_1p} + {24'd0, U_1m};
		Mult1_op_2 = 32'd159;
	end else if (sysio == S_common_cycle4) begin
		Mult1_op_1 = {24'b0, Y_buffer[7:0]} - 32'd16; 
		Mult1_op_2 = 32'd76284;
	end else if (sysio == S_common_cycle6) begin
		Mult1_op_1 = Vp_odd;
		Mult1_op_2 = 32'd53281;
	end
	else begin
		Mult1_op_1 = 32'd0;
		Mult1_op_2 = 32'd0;
	end 
end

always_comb begin 
	if (sysio == S_common_cycle2) begin 
		Mult2_op_1 = {24'd0, V_5p} + {24'd0, V_5m};
		Mult2_op_2 = 32'd21;
	end else if (sysio == S_common_cycle3) begin
		Mult2_op_1 = {24'd0, V_3p} + {24'd0, V_3m};
		Mult2_op_2 = 32'd52;
	end else if (sysio == S_common_cycle4) begin
		Mult2_op_1 = {24'd0, V_1p} + {24'd0, V_1m};
		Mult2_op_2 = 32'd159;
	end else if (sysio == S_common_cycle5) begin
		Mult2_op_1 = Up_odd;
		Mult2_op_2 = 32'd132251;
	end else if (sysio == S_common_cycle6) begin
		Mult2_op_1 = Vp_odd;
		Mult2_op_2 = 32'd104595;
	end
	else begin
		Mult2_op_1 = 32'd0;
		Mult2_op_2 = 32'd0;
	end 
end

always_comb begin
	if (sysio == S_common_cycle0) begin 
		Mult3_op_1 = {24'd0, Y_buffer[15:8]} - 32'd16;
		Mult3_op_2 = 32'd76284;
	end else if (sysio == S_common_cycle1) begin
		Mult3_op_1 = Vp_even;
		Mult3_op_2 = 32'd104595;
	end else if (sysio == S_common_cycle2) begin
		Mult3_op_1 = Up_even;
		Mult3_op_2 = 32'd25624;
	end else if (sysio == S_common_cycle3) begin
		Mult3_op_1 = Vp_even;
		Mult3_op_2 = 32'd53281;
	end else if (sysio == S_common_cycle4) begin
		Mult3_op_1 = Up_even;
		Mult3_op_2 = 32'd132251;
	end else if (sysio == S_common_cycle5) begin
		Mult3_op_1 = Up_odd;
		Mult3_op_2 = 32'd25624;
	end else begin 
		Mult3_op_1 = 32'd0;
		Mult3_op_2 = 32'd0;
	end 
end

endmodule 