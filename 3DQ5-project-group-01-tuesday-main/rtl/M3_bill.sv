//Milestone 3 (Bill)
`timescale 1ns/100ps
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif

module M3 (
	input logic Clock_50,
	input logic Resetn,
	
	//SRAM_CONTROLLER <-- DIRECT CONTACT WITH SYS_SRAM
	output logic [17:0] SRAM_address,
	input logic [15:0] SRAM_read_data,

	//DP RAM I/O --> FETCH USE IT 
	output logic [6:0] DP_RAM_address_a,
	output logic [31:0] DP_write_DATA_a,
	output logic DP_write_enable_a,

	input logic start,
	output logic finish,
	output logic M3_finish_or_not
);

typedef enum logic [4:0] {
	S_read_7_bits,
	S_idle,
	S_leadin1,
	S_leadin2,
	S_leadin3,
	S_leadin4,
	S_leadin5,
	S_leadin6,
	S_read_2_bits,
	S_read_3_bits1,
	S_read_3_bits2,
	S_write_code,
	S_write_code_zeros,
	S_write_8_zeros,
	S_write_zeros_to_the_end,
	S_shift_buffer1,
	S_shift_buffer2,
	S_shift,
	S_end
} M3_state;

M3_state m3_state;

logic [17:0] SRAM_base_address, SRAM_new_base_address, SRAM_address_offset;
logic [2:0] cmd;
logic [47:0] read_buffer;
logic [5:0] read_bits;
logic [15:0] header1, header2;
logic [6:0] write_counter;
logic [8:0] code;
logic Q_number, check_header, first_time, DEAD_flag, BEEF_flag;
logic [1:0] header_counter, buffer_counter;
logic [5:0] ZZ_counter;
logic [7:0] position;
logic [1:0] first_choice;
logic [6:0] counter;

assign SRAM_address = SRAM_base_address + SRAM_address_offset;

always_ff @(posedge Clock_50 or negedge Resetn) begin
	if (~Resetn) begin
		finish <= 1'b0;
		SRAM_base_address <= 18'd76800;
		SRAM_new_base_address <= 18'd76800;
		SRAM_address_offset <= 18'd0;
		m3_state <= S_idle;
		Q_number <= 1'b0;
		header_counter <= 0;
		ZZ_counter <= 6'd0;
		first_choice <= 0;
		read_buffer <= 0;
		header1 <= 0;
		header2 <= 0;
		read_bits <= 0;
		write_counter <= 0;
		code <= 0;
		check_header <= 0;
		DP_write_enable_a <= 0;
		DP_RAM_address_a <= 0;
		DP_write_DATA_a <= 0;
		first_time <= 1'b1;
		counter <= 0;
		DEAD_flag <= 0;
		BEEF_flag <= 0;
		M3_finish_or_not <=0;
	end else begin
		case(m3_state)
		S_idle: begin
			finish <= 1'b0;
			SRAM_base_address <= SRAM_new_base_address;
         if (start) begin
				M3_finish_or_not <= 0;
				DP_write_enable_a <= 1'b1;
				ZZ_counter <= 0;
				if(check_header) begin
					m3_state <= S_read_2_bits;
				end else begin
					m3_state <= S_leadin1;
				end
         end	
      end
		S_leadin1: begin
			header_counter <= header_counter + 5'd1;
			if(header_counter == 5'd0) begin
				SRAM_address_offset <= SRAM_address_offset + 18'd1;
			end else if(header_counter == 5'd2) begin
				SRAM_address_offset <= SRAM_address_offset + 18'd1;
				header1 <= SRAM_read_data;
			end else if(header_counter == 5'd3) begin
				m3_state <= S_leadin2;
				SRAM_address_offset <= SRAM_address_offset + 18'd1;
				header2 <= SRAM_read_data;
				header_counter <= 5'd0;
			end 
		end
		S_leadin2: begin
			if (header1 == 16'hDEAD && header_counter == 5'd0) begin
				SRAM_address_offset <= SRAM_address_offset + 18'd1;
				header_counter <= header_counter + 5'd1;
				DEAD_flag <= 1'b1;
			end else if (header2 == 16'hBEEF && header_counter == 5'd1) begin
				SRAM_address_offset <= SRAM_address_offset + 18'd1;
				header_counter <= header_counter + 5'd1;
				Q_number <= SRAM_read_data[15];
				BEEF_flag <= 1'b1;
			end else begin
				SRAM_address_offset <= SRAM_address_offset + 18'd1;
				m3_state <= S_leadin3;
				check_header <= 1'b1;
				header_counter <= 0;
				if (!DEAD_flag || !BEEF_flag) begin
					m3_state <= S_end;
					header_counter <= 0;
					check_header <= 1'b0;
				end
			end
		end
		S_leadin3: begin
			read_buffer[47:32] <= SRAM_read_data;
			m3_state <= S_leadin4;
		end
		S_leadin4: begin
			read_buffer[31:16] <= SRAM_read_data;
			m3_state <= S_leadin5;
		end
		S_leadin5: begin
			read_buffer[15:0] <= SRAM_read_data;
			m3_state <= S_leadin6;
		end
		S_leadin6: begin
			m3_state <= S_read_2_bits;
		end
		S_read_2_bits: begin
			read_bits <= read_bits + 6'd2;
			code <= $signed(read_buffer[6'd47-read_bits-:2]);
			first_choice <= read_buffer[6'd47-read_bits-:2];
			// condition
			if (read_buffer[6'd47-read_bits-:2] == 2'b10) begin
				m3_state <= S_read_7_bits;
			end else begin
				m3_state <= S_read_3_bits1;
			end
		end
		S_read_7_bits: begin
			//condition
			if (!read_buffer[6'd47-read_bits-:1]) begin
				read_bits <= read_bits + 6'd7;
				code <= $signed(read_buffer[6'd46-read_bits-:6]);
				m3_state <= S_write_code;
				write_counter <= write_counter + 7'd1;
			end else if (read_buffer[6'd47-read_bits-:2] == 2'b10) begin
				read_bits <= read_bits + 6'd2;
				m3_state <= S_write_zeros_to_the_end;
				counter <= 7'd63 - write_counter;
			end else begin
				read_bits <= read_bits + 6'd11;
				code <= read_buffer[6'd45-read_bits-:9];
				m3_state <= S_write_code;
				write_counter <= write_counter + 7'd1;
			end
		end
		S_read_3_bits1: begin
			read_bits <= read_bits + 6'd3;
			code <= $signed(read_buffer[6'd47-read_bits-:3]);
			if (first_choice == 2'b00) begin
				DP_write_DATA_a <= {{29{read_buffer[6'd47-read_bits-:1]}}, read_buffer[6'd47-read_bits-:3]} << cmd;
				DP_RAM_address_a <= {1'b0, ZZ_counter};
				case(ZZ_counter)
				6'd0: ZZ_counter <= 6'd1;
				6'd1: ZZ_counter <= 6'd8;
				6'd8: ZZ_counter <= 6'd16;
				6'd16: ZZ_counter <= 6'd9;
				6'd9: ZZ_counter <= 6'd2;
				6'd2: ZZ_counter <= 6'd3;
				6'd3: ZZ_counter <= 6'd10;
				6'd10: ZZ_counter <= 6'd17;
				6'd17: ZZ_counter <= 6'd24;
				6'd24: ZZ_counter <= 6'd32;
				6'd32: ZZ_counter <= 6'd25;
				6'd25: ZZ_counter <= 6'd18;
				6'd18: ZZ_counter <= 6'd11;
				6'd11: ZZ_counter <= 6'd4;
				6'd4: ZZ_counter <= 6'd5;
				6'd5: ZZ_counter <= 6'd12;
				6'd12: ZZ_counter <= 6'd19;
				6'd19: ZZ_counter <= 6'd26;
				6'd26: ZZ_counter <= 6'd33;
				6'd33: ZZ_counter <= 6'd40;
				6'd40: ZZ_counter <= 6'd48;
				6'd48: ZZ_counter <= 6'd41;
				6'd41: ZZ_counter <= 6'd34;
				6'd34: ZZ_counter <= 6'd27;
				6'd27: ZZ_counter <= 6'd20;
				6'd20: ZZ_counter <= 6'd13;
				6'd13: ZZ_counter <= 6'd6;
				6'd6: ZZ_counter <= 6'd7;
				6'd7: ZZ_counter <= 6'd14;
				6'd14: ZZ_counter <= 6'd21;
				6'd21: ZZ_counter <= 6'd28;
				6'd28: ZZ_counter <= 6'd35;
				6'd35: ZZ_counter <= 6'd42;
				6'd42: ZZ_counter <= 6'd49;
				6'd49: ZZ_counter <= 6'd56;
				6'd56: ZZ_counter <= 6'd57;
				6'd57: ZZ_counter <= 6'd50;
				6'd50: ZZ_counter <= 6'd43;
				6'd43: ZZ_counter <= 6'd36;
				6'd36: ZZ_counter <= 6'd29;
				6'd29: ZZ_counter <= 6'd22;
				6'd22: ZZ_counter <= 6'd15;
				6'd15: ZZ_counter <= 6'd23;
				6'd23: ZZ_counter <= 6'd30;
				6'd30: ZZ_counter <= 6'd37;
				6'd37: ZZ_counter <= 6'd44;
				6'd44: ZZ_counter <= 6'd51;
				6'd51: ZZ_counter <= 6'd58;
				6'd58: ZZ_counter <= 6'd59;
				6'd59: ZZ_counter <= 6'd52;
				6'd52: ZZ_counter <= 6'd45;
				6'd45: ZZ_counter <= 6'd38;
				6'd38: ZZ_counter <= 6'd31;
				6'd31: ZZ_counter <= 6'd39;
				6'd39: ZZ_counter <= 6'd46;
				6'd46: ZZ_counter <= 6'd53;
				6'd53: ZZ_counter <= 6'd60;
				6'd60: ZZ_counter <= 6'd61;
				6'd61: ZZ_counter <= 6'd54;
				6'd54: ZZ_counter <= 6'd47;
				6'd47: ZZ_counter <= 6'd55;
				6'd55: ZZ_counter <= 6'd62;
				6'd62: ZZ_counter <= 6'd63;
				6'd63: ZZ_counter <= 6'd0;
				endcase
				m3_state <= S_read_3_bits2;
				write_counter <= write_counter + 7'd1;
			end else if (first_choice == 2'b11) begin
				if (read_buffer[6'd47-read_bits-:3] == 0) begin
					counter <= 7'd7;
					m3_state <= S_write_8_zeros;
					write_counter <= write_counter + 7'd8;
				end else begin
					counter <= read_buffer[6'd47-read_bits-:3] - 3'd1;
					m3_state <= S_write_code_zeros;
					write_counter <= write_counter + read_buffer[6'd47-read_bits-:3];
				end
			end else begin
				m3_state <= S_write_code;
				write_counter <= write_counter + 7'd1;
			end
		end
		
		S_read_3_bits2: begin 
			read_bits <= read_bits + 6'd3;
			code <= $signed(read_buffer[6'd47-read_bits-:3]);
			write_counter <= write_counter + 7'd1;
			m3_state <= S_write_code;
		end
		
		S_write_code: begin
			DP_write_DATA_a <= {{23{code[8]}}, code} << cmd;
			DP_RAM_address_a <= {1'b0, ZZ_counter};
			case(ZZ_counter)
			6'd0: ZZ_counter <= 6'd1;
			6'd1: ZZ_counter <= 6'd8;
			6'd8: ZZ_counter <= 6'd16;
			6'd16: ZZ_counter <= 6'd9;
			6'd9: ZZ_counter <= 6'd2;
			6'd2: ZZ_counter <= 6'd3;
			6'd3: ZZ_counter <= 6'd10;
			6'd10: ZZ_counter <= 6'd17;
			6'd17: ZZ_counter <= 6'd24;
			6'd24: ZZ_counter <= 6'd32;
			6'd32: ZZ_counter <= 6'd25;
			6'd25: ZZ_counter <= 6'd18;
			6'd18: ZZ_counter <= 6'd11;
			6'd11: ZZ_counter <= 6'd4;
			6'd4: ZZ_counter <= 6'd5;
			6'd5: ZZ_counter <= 6'd12;
			6'd12: ZZ_counter <= 6'd19;
			6'd19: ZZ_counter <= 6'd26;
			6'd26: ZZ_counter <= 6'd33;
			6'd33: ZZ_counter <= 6'd40;
			6'd40: ZZ_counter <= 6'd48;
			6'd48: ZZ_counter <= 6'd41;
			6'd41: ZZ_counter <= 6'd34;
			6'd34: ZZ_counter <= 6'd27;
			6'd27: ZZ_counter <= 6'd20;
			6'd20: ZZ_counter <= 6'd13;
			6'd13: ZZ_counter <= 6'd6;
			6'd6: ZZ_counter <= 6'd7;
			6'd7: ZZ_counter <= 6'd14;
			6'd14: ZZ_counter <= 6'd21;
			6'd21: ZZ_counter <= 6'd28;
			6'd28: ZZ_counter <= 6'd35;
			6'd35: ZZ_counter <= 6'd42;
			6'd42: ZZ_counter <= 6'd49;
			6'd49: ZZ_counter <= 6'd56;
			6'd56: ZZ_counter <= 6'd57;
			6'd57: ZZ_counter <= 6'd50;
			6'd50: ZZ_counter <= 6'd43;
			6'd43: ZZ_counter <= 6'd36;
			6'd36: ZZ_counter <= 6'd29;
			6'd29: ZZ_counter <= 6'd22;
			6'd22: ZZ_counter <= 6'd15;
			6'd15: ZZ_counter <= 6'd23;
			6'd23: ZZ_counter <= 6'd30;
			6'd30: ZZ_counter <= 6'd37;
			6'd37: ZZ_counter <= 6'd44;
			6'd44: ZZ_counter <= 6'd51;
			6'd51: ZZ_counter <= 6'd58;
			6'd58: ZZ_counter <= 6'd59;
			6'd59: ZZ_counter <= 6'd52;
			6'd52: ZZ_counter <= 6'd45;
			6'd45: ZZ_counter <= 6'd38;
			6'd38: ZZ_counter <= 6'd31;
			6'd31: ZZ_counter <= 6'd39;
			6'd39: ZZ_counter <= 6'd46;
			6'd46: ZZ_counter <= 6'd53;
			6'd53: ZZ_counter <= 6'd60;
			6'd60: ZZ_counter <= 6'd61;
			6'd61: ZZ_counter <= 6'd54;
			6'd54: ZZ_counter <= 6'd47;
			6'd47: ZZ_counter <= 6'd55;
			6'd55: ZZ_counter <= 6'd62;
			6'd62: ZZ_counter <= 6'd63;
			6'd63: ZZ_counter <= 6'd0;
			endcase
			if (write_counter >= 7'd64) begin
				m3_state <= S_end;
			end else begin
				if (read_bits > 6'd15) begin
					SRAM_address_offset <= SRAM_address_offset + 18'd1;
					m3_state <= S_shift_buffer1;
				end else begin
					m3_state <= S_read_2_bits;
				end
			end
		end
		S_write_code_zeros: begin
			DP_write_DATA_a <= 0;
			DP_RAM_address_a <= {1'b0, ZZ_counter};
			case(ZZ_counter)
			6'd0: ZZ_counter <= 6'd1;
			6'd1: ZZ_counter <= 6'd8;
			6'd8: ZZ_counter <= 6'd16;
			6'd16: ZZ_counter <= 6'd9;
			6'd9: ZZ_counter <= 6'd2;
			6'd2: ZZ_counter <= 6'd3;
			6'd3: ZZ_counter <= 6'd10;
			6'd10: ZZ_counter <= 6'd17;
			6'd17: ZZ_counter <= 6'd24;
			6'd24: ZZ_counter <= 6'd32;
			6'd32: ZZ_counter <= 6'd25;
			6'd25: ZZ_counter <= 6'd18;
			6'd18: ZZ_counter <= 6'd11;
			6'd11: ZZ_counter <= 6'd4;
			6'd4: ZZ_counter <= 6'd5;
			6'd5: ZZ_counter <= 6'd12;
			6'd12: ZZ_counter <= 6'd19;
			6'd19: ZZ_counter <= 6'd26;
			6'd26: ZZ_counter <= 6'd33;
			6'd33: ZZ_counter <= 6'd40;
			6'd40: ZZ_counter <= 6'd48;
			6'd48: ZZ_counter <= 6'd41;
			6'd41: ZZ_counter <= 6'd34;
			6'd34: ZZ_counter <= 6'd27;
			6'd27: ZZ_counter <= 6'd20;
			6'd20: ZZ_counter <= 6'd13;
			6'd13: ZZ_counter <= 6'd6;
			6'd6: ZZ_counter <= 6'd7;
			6'd7: ZZ_counter <= 6'd14;
			6'd14: ZZ_counter <= 6'd21;
			6'd21: ZZ_counter <= 6'd28;
			6'd28: ZZ_counter <= 6'd35;
			6'd35: ZZ_counter <= 6'd42;
			6'd42: ZZ_counter <= 6'd49;
			6'd49: ZZ_counter <= 6'd56;
			6'd56: ZZ_counter <= 6'd57;
			6'd57: ZZ_counter <= 6'd50;
			6'd50: ZZ_counter <= 6'd43;
			6'd43: ZZ_counter <= 6'd36;
			6'd36: ZZ_counter <= 6'd29;
			6'd29: ZZ_counter <= 6'd22;
			6'd22: ZZ_counter <= 6'd15;
			6'd15: ZZ_counter <= 6'd23;
			6'd23: ZZ_counter <= 6'd30;
			6'd30: ZZ_counter <= 6'd37;
			6'd37: ZZ_counter <= 6'd44;
			6'd44: ZZ_counter <= 6'd51;
			6'd51: ZZ_counter <= 6'd58;
			6'd58: ZZ_counter <= 6'd59;
			6'd59: ZZ_counter <= 6'd52;
			6'd52: ZZ_counter <= 6'd45;
			6'd45: ZZ_counter <= 6'd38;
			6'd38: ZZ_counter <= 6'd31;
			6'd31: ZZ_counter <= 6'd39;
			6'd39: ZZ_counter <= 6'd46;
			6'd46: ZZ_counter <= 6'd53;
			6'd53: ZZ_counter <= 6'd60;
			6'd60: ZZ_counter <= 6'd61;
			6'd61: ZZ_counter <= 6'd54;
			6'd54: ZZ_counter <= 6'd47;
			6'd47: ZZ_counter <= 6'd55;
			6'd55: ZZ_counter <= 6'd62;
			6'd62: ZZ_counter <= 6'd63;
			6'd63: ZZ_counter <= 6'd0;
			endcase		
			if(counter == 0) begin
				if (write_counter >= 7'd64) begin
					m3_state <= S_end;
				end else begin
					if (read_bits > 6'd15) begin
						SRAM_address_offset <= SRAM_address_offset + 18'd1;
						m3_state <= S_shift_buffer1;
					end else begin
						m3_state <= S_read_2_bits;
					end
				end
			end else begin
				counter <= counter - 7'b1;
			end
		end
		S_write_8_zeros: begin
			DP_write_DATA_a <= 0;
			DP_RAM_address_a <= {1'b0, ZZ_counter};
			case(ZZ_counter)
			6'd0: ZZ_counter <= 6'd1;
			6'd1: ZZ_counter <= 6'd8;
			6'd8: ZZ_counter <= 6'd16;
			6'd16: ZZ_counter <= 6'd9;
			6'd9: ZZ_counter <= 6'd2;
			6'd2: ZZ_counter <= 6'd3;
			6'd3: ZZ_counter <= 6'd10;
			6'd10: ZZ_counter <= 6'd17;
			6'd17: ZZ_counter <= 6'd24;
			6'd24: ZZ_counter <= 6'd32;
			6'd32: ZZ_counter <= 6'd25;
			6'd25: ZZ_counter <= 6'd18;
			6'd18: ZZ_counter <= 6'd11;
			6'd11: ZZ_counter <= 6'd4;
			6'd4: ZZ_counter <= 6'd5;
			6'd5: ZZ_counter <= 6'd12;
			6'd12: ZZ_counter <= 6'd19;
			6'd19: ZZ_counter <= 6'd26;
			6'd26: ZZ_counter <= 6'd33;
			6'd33: ZZ_counter <= 6'd40;
			6'd40: ZZ_counter <= 6'd48;
			6'd48: ZZ_counter <= 6'd41;
			6'd41: ZZ_counter <= 6'd34;
			6'd34: ZZ_counter <= 6'd27;
			6'd27: ZZ_counter <= 6'd20;
			6'd20: ZZ_counter <= 6'd13;
			6'd13: ZZ_counter <= 6'd6;
			6'd6: ZZ_counter <= 6'd7;
			6'd7: ZZ_counter <= 6'd14;
			6'd14: ZZ_counter <= 6'd21;
			6'd21: ZZ_counter <= 6'd28;
			6'd28: ZZ_counter <= 6'd35;
			6'd35: ZZ_counter <= 6'd42;
			6'd42: ZZ_counter <= 6'd49;
			6'd49: ZZ_counter <= 6'd56;
			6'd56: ZZ_counter <= 6'd57;
			6'd57: ZZ_counter <= 6'd50;
			6'd50: ZZ_counter <= 6'd43;
			6'd43: ZZ_counter <= 6'd36;
			6'd36: ZZ_counter <= 6'd29;
			6'd29: ZZ_counter <= 6'd22;
			6'd22: ZZ_counter <= 6'd15;
			6'd15: ZZ_counter <= 6'd23;
			6'd23: ZZ_counter <= 6'd30;
			6'd30: ZZ_counter <= 6'd37;
			6'd37: ZZ_counter <= 6'd44;
			6'd44: ZZ_counter <= 6'd51;
			6'd51: ZZ_counter <= 6'd58;
			6'd58: ZZ_counter <= 6'd59;
			6'd59: ZZ_counter <= 6'd52;
			6'd52: ZZ_counter <= 6'd45;
			6'd45: ZZ_counter <= 6'd38;
			6'd38: ZZ_counter <= 6'd31;
			6'd31: ZZ_counter <= 6'd39;
			6'd39: ZZ_counter <= 6'd46;
			6'd46: ZZ_counter <= 6'd53;
			6'd53: ZZ_counter <= 6'd60;
			6'd60: ZZ_counter <= 6'd61;
			6'd61: ZZ_counter <= 6'd54;
			6'd54: ZZ_counter <= 6'd47;
			6'd47: ZZ_counter <= 6'd55;
			6'd55: ZZ_counter <= 6'd62;
			6'd62: ZZ_counter <= 6'd63;
			6'd63: ZZ_counter <= 6'd0;
			endcase
			if(counter == 0) begin
				if (write_counter >= 7'd64) begin
					m3_state <= S_end;
				end else begin
					if (read_bits > 6'd15) begin
						SRAM_address_offset <= SRAM_address_offset + 18'd1;
						m3_state <= S_shift_buffer1;
					end else begin
						m3_state <= S_read_2_bits;
					end
				end
			end else begin
				counter <= counter - 7'b1;
			end
		end
		S_write_zeros_to_the_end: begin
			DP_write_DATA_a <= 0;
			DP_RAM_address_a <= {1'b0, ZZ_counter};
			case(ZZ_counter)
			6'd0: ZZ_counter <= 6'd1;
			6'd1: ZZ_counter <= 6'd8;
			6'd8: ZZ_counter <= 6'd16;
			6'd16: ZZ_counter <= 6'd9;
			6'd9: ZZ_counter <= 6'd2;
			6'd2: ZZ_counter <= 6'd3;
			6'd3: ZZ_counter <= 6'd10;
			6'd10: ZZ_counter <= 6'd17;
			6'd17: ZZ_counter <= 6'd24;
			6'd24: ZZ_counter <= 6'd32;
			6'd32: ZZ_counter <= 6'd25;
			6'd25: ZZ_counter <= 6'd18;
			6'd18: ZZ_counter <= 6'd11;
			6'd11: ZZ_counter <= 6'd4;
			6'd4: ZZ_counter <= 6'd5;
			6'd5: ZZ_counter <= 6'd12;
			6'd12: ZZ_counter <= 6'd19;
			6'd19: ZZ_counter <= 6'd26;
			6'd26: ZZ_counter <= 6'd33;
			6'd33: ZZ_counter <= 6'd40;
			6'd40: ZZ_counter <= 6'd48;
			6'd48: ZZ_counter <= 6'd41;
			6'd41: ZZ_counter <= 6'd34;
			6'd34: ZZ_counter <= 6'd27;
			6'd27: ZZ_counter <= 6'd20;
			6'd20: ZZ_counter <= 6'd13;
			6'd13: ZZ_counter <= 6'd6;
			6'd6: ZZ_counter <= 6'd7;
			6'd7: ZZ_counter <= 6'd14;
			6'd14: ZZ_counter <= 6'd21;
			6'd21: ZZ_counter <= 6'd28;
			6'd28: ZZ_counter <= 6'd35;
			6'd35: ZZ_counter <= 6'd42;
			6'd42: ZZ_counter <= 6'd49;
			6'd49: ZZ_counter <= 6'd56;
			6'd56: ZZ_counter <= 6'd57;
			6'd57: ZZ_counter <= 6'd50;
			6'd50: ZZ_counter <= 6'd43;
			6'd43: ZZ_counter <= 6'd36;
			6'd36: ZZ_counter <= 6'd29;
			6'd29: ZZ_counter <= 6'd22;
			6'd22: ZZ_counter <= 6'd15;
			6'd15: ZZ_counter <= 6'd23;
			6'd23: ZZ_counter <= 6'd30;
			6'd30: ZZ_counter <= 6'd37;
			6'd37: ZZ_counter <= 6'd44;
			6'd44: ZZ_counter <= 6'd51;
			6'd51: ZZ_counter <= 6'd58;
			6'd58: ZZ_counter <= 6'd59;
			6'd59: ZZ_counter <= 6'd52;
			6'd52: ZZ_counter <= 6'd45;
			6'd45: ZZ_counter <= 6'd38;
			6'd38: ZZ_counter <= 6'd31;
			6'd31: ZZ_counter <= 6'd39;
			6'd39: ZZ_counter <= 6'd46;
			6'd46: ZZ_counter <= 6'd53;
			6'd53: ZZ_counter <= 6'd60;
			6'd60: ZZ_counter <= 6'd61;
			6'd61: ZZ_counter <= 6'd54;
			6'd54: ZZ_counter <= 6'd47;
			6'd47: ZZ_counter <= 6'd55;
			6'd55: ZZ_counter <= 6'd62;
			6'd62: ZZ_counter <= 6'd63;
			6'd63: ZZ_counter <= 6'd0;
			endcase
			if(counter == 0) begin
				m3_state <= S_end; 
			end else begin
				counter <= counter - 7'd1;
			end
		end
		S_shift_buffer1: begin
			m3_state <= S_shift_buffer2;
		end
		S_shift_buffer2: begin
			m3_state <= S_shift;
		end
		S_shift: begin
			read_buffer <= read_buffer << 47'd16;
			read_buffer[15:0] <= SRAM_read_data;
			read_bits <= read_bits - 6'd16;
			m3_state <= S_read_2_bits;
		end
		S_end: begin
			M3_finish_or_not <= 1'b1;
			finish <= 1'b1;
			write_counter <= 0;
			DP_write_enable_a <= 0;
			SRAM_address_offset <= 18'd0;
			SRAM_new_base_address <= SRAM_base_address + SRAM_address_offset;
			m3_state <= S_idle;
		end
		endcase 
	end
	
end

always_comb begin 
	position = {1'b0, ZZ_counter[5:3]} + {1'b0, ZZ_counter[2:0]};
	if (Q_number == 0) begin
		if (position == 4'd0 || position == 4'd2 || position == 4'd3) begin
			cmd = 3'b011;
		end else if (position == 4'd1) begin
			cmd = 3'b010;
		end else if (position == 4'd4 || position == 4'd5) begin
			cmd = 3'b100;
		end else if (position == 4'd6 || position == 4'd7) begin
			cmd = 3'b101;
		end else begin
			cmd = 3'b110;
		end
	end else begin
		if (position == 4'd0 || position == 4'd6 || position == 4'd7) begin
			cmd = 3'b011;
		end else if (position == 4'd1 || position == 4'd2 || position == 4'd3) begin
			cmd = 3'b001;
		end else if (position == 4'd4 || position == 4'd5) begin
			cmd = 3'b010;
		end else begin
			cmd = 3'b110;
		end
	end
end	 

	 
endmodule
