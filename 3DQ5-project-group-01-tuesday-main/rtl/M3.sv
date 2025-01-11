//Milestone 3
`timescale 1ns/100ps
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif

module M3 (
	input logic Clock_50,
	input logic Resetn,
	
	//SRAM_CONTROLLER <-- DIRECT CONTACT WITH SYS_SRAM
	output logic [17:0] SRAM_address,
	output logic SRAM_we_n,
	input logic [15:0] SRAM_read_data,

	//DP RAM I/O --> FETCH USE IT 
	// input logic [6:0] DP_EXT_RAM_address,
	// output logic [31:0] DP_EXT_DATA,
	// output logic [6:0] DP_EXT_R_W
	

	input logic start,
	output logic finish
);

// SRAM FOR STORE BIT STREME MAT THAT IS LOSSLESS DECODE
logic [6:0] address_a_X,address_b_X;
logic dp_X_r_w_en_a,dp_X_r_w_en_b;
logic [31:0] dp_data_X_a,dp_data_X_b;
logic [31:0] dp_data_X_a_out,dp_data_X_b_out;
dual_port_RAM0 RAM_instX (
    //addressing callign , input 
	.address_a ( address_a_X ),
	.address_b ( address_b_X ),

	.clock ( Clock_50 ),
    //data wanna to insert, a channal for lossless decoder 
	.data_a ( dp_data_X_a ),
    //data wanna to insert, b channal for Q

	.data_b ( dp_data_X_b ),

    //rw_presision control
	.wren_a (1'b1), //just testing
	.wren_b (dp_X_r_w_en_b),

    //data out, for Fetch ,port b might need to h
	.q_a ( dp_data_X_a_out ),
	.q_b ( dp_data_X_b_out )
);

//LOSSLESS DECODING SYSTEM, ONLY FOR WRITTEN IN
logic loss_less_start,loss_less_finish;

//lossless decoding system req on the sram level
logic [17:0] loss_less_decodeing_addr_req;
logic [15:0] bit_stream_from_sram;
logic lossless_decode_sram_w_en;

//lossless decoding on the dp_ram_irq
logic [6:0] lossless_dp_X_ram_calling;
logic [31:0] lossless_after_decoding_X_input;
logic lossless_dp_precision_control_wen;

lossless_decoder_Quantization lossless(
    //input 
	 .start(start),
    //output 
	 .finish(finish), 

    //input  
	 .clk(Clock_50),              
    //input  
	 .reset(Resetn),            

    //from sram calling adrrs
    //output [17:0] 
	 .SRAM_address(SRAM_address),
    //input  [15:0] 
	 .SRAM_data_contains_bitstream(SRAM_read_data), 
    //output 
	 .SRAM_W_EN_lossless_decode(SRAM_we_n),

    //dualport ram access port a only lol
    //output [31:0] 
	 .dp_ram_X_data_a(dp_data_X_a),
    //output [6:0] 
	 .dp_ram_X_address_a(address_a_X), //positon K-mapping  //WANNA TO GET THE DATA FROM OUTSIDE
    //output 
	 .dp_ram_X_renw_a()
);

endmodule






























/*


//lossless_decoding system
module lossless_decoder (
    input start,
    output finish, 

    input  clk,              
    input  reset,            

    //from sram calling adrrs
    output [17:0] SRAM_address_EVERST,
    input  [15:0] SRAM_address_bitstream, 
    output SRAM_W_EN,

    //dualport ram access port a only lol
    output [31:0] dp_ram_X_data_a,
    output [6:0] post_zigzag_position, //positon K-mapping  //WANNA TO GET THE DATA FROM OUTSIDE
    output dp_ram_X_renw_a
);

typedef enum logic [3:0] {
    IDLE, 
    WAIT_FOR_BITSTREAM, 
    READ_BITS, 
    DECODE,
    WRITE, 
    COMPLETE
} state_t;

state_t state;

//might using zig-zag structure

logic [5:0] scan_index;      // bow much blocks we have filled 

logic [63:0] buffer;         //what in side the bitstream, 4 OF THOSE 

logic [3:0] prefix;          // presys

//sram_side_operator 
logic [17:0] SRAM_address_offset;
logic [3:0] the_last_stand;
logic [17:0] SRAM_address_bitstream_base;
assign SRAM_address_bitstream_base = 18'd76800;

//dp_ram_side_operator 
logic [5:0] X_address_offset;
logic [7:0] decoded_value;

//counter system 
logic [1:0] lets_read_4_bitstream;

logic [3:0] read_bits_number;

always_ff @(posedge clk or negedge reset) begin 
    if (~reset) begin
    state <= IDLE;
    scan_index <= 0;

    finish <= 0;
    SRAM_address_offset <= 0;
    // sys position,
    X_address_offset <= 0;
    decoded_value <= 0;
    the_last_stand <= 0; 

    lets_read_4_bitstream <= 0;
	 read_bits_number <= 0;
    end else begin
        case (state)
            IDLE: begin
                finish <= 0;
                scan_index <= 0;
					 read_bits_number <= 0;

                if(start) begin
                    state <= WAIT_FOR_BITSTREAM;
                end
            end
            WAIT_FOR_BITSTREAM: begin  
                //sram operation ,wanna to get first to third 16 bit data;
                //so add a last stage position pointer LOL 
                if (the_last_stand == 0) begin
                    SRAM_address_EVERST <= SRAM_address_offset + SRAM_address_bitstream;
                    SRAM_address_offset <= SRAM_address_offset + 1'b1;
                end
            
                if (bitstream != 16'h0000) begin
                    state <= READ_BITS;
                end
                else begin
                    state <= WAIT_FOR_BITSTREAM;
                end  
            end

            DECODE: begin
                case (prefix)
                    2'b00: begin
                        buffer <= 
                        state <= WRITE;
                    end
                    2'b01: begin

                        state <= WRITE;
                    end
                    2'b10: begin

                        state <= WRITE;
                    end
                    2'b11: begin

                        state <= WRITE;
                    end
                    endcase
            end
				
				READ_BITS: begin
					case(read_bits_number)
					9'd1: begin
						prefix <= buffer[15];
						buffer <= {buffer[14:0]; 
					end
						prefix <= buffer[15:14]; //read first 2 bit 
						the_last_stand <= the_last_stand + 2'd2;
						state <= DECODE;
					endcase
            end
				
            WRITE: begin
                // back to the dpram
                dp_ram_X_data_a <= {decoded_value};
                //write one blk, then back
                dp_ram_X_address_a <= post_zigzag_position;
                X_address_offset <= X_address_offset + 1'b1;

                if (prefix == 2'b00) begin
                    
                end

                if (scan_index == 63) begin
                    // 8x8 finish
                    state <= COMPLETE;
                end else begin
                    // next tiny stream
                    state <= READ_BITS;
                end
            end
				
            COMPLETE: begin
                finish <= 1'b1;
                state <= IDLE;
            end
        endcase
    end
end

assign post_zigzag_position = 
    (X_address_offset == 6'd0) ? 7'd0 :
    (X_address_offset == 6'd1) ? 7'd1 :
    (X_address_offset == 6'd2) ? 7'd8 :
    (X_address_offset == 6'd3) ? 7'd16 :
    (X_address_offset == 6'd4) ? 7'd9 :
    (X_address_offset == 6'd5) ? 7'd2 :
    (X_address_offset == 6'd6) ? 7'd3 :
    (X_address_offset == 6'd7) ? 7'd10 :
    (X_address_offset == 6'd8) ? 7'd17 :
    (X_address_offset == 6'd9) ? 7'd24 :
    (X_address_offset == 6'd10) ? 7'd32 :
    (X_address_offset == 6'd11) ? 7'd25 :
    (X_address_offset == 6'd12) ? 7'd18 :
    (X_address_offset == 6'd13) ? 7'd11 :
    (X_address_offset == 6'd14) ? 7'd4 :
    (X_address_offset == 6'd15) ? 7'd5 :
    (X_address_offset == 6'd16) ? 7'd12 :
    (X_address_offset == 6'd17) ? 7'd19 :
    (X_address_offset == 6'd18) ? 7'd26 :
    (X_address_offset == 6'd19) ? 7'd33 :
    (X_address_offset == 6'd20) ? 7'd40 :
    (X_address_offset == 6'd21) ? 7'd48 :
    (X_address_offset == 6'd22) ? 7'd41 :
    (X_address_offset == 6'd23) ? 7'd34 :
    (X_address_offset == 6'd24) ? 7'd27 :
    (X_address_offset == 6'd25) ? 7'd20 :
    (X_address_offset == 6'd26) ? 7'd13 :
    (X_address_offset == 6'd27) ? 7'd6 :
    (X_address_offset == 6'd28) ? 7'd7 :
    (X_address_offset == 6'd29) ? 7'd14 :
    (X_address_offset == 6'd30) ? 7'd21 :
    (X_address_offset == 6'd31) ? 7'd28 :
    (X_address_offset == 6'd32) ? 7'd35 :
    (X_address_offset == 6'd33) ? 7'd42 :
    (X_address_offset == 6'd34) ? 7'd49 :
    (X_address_offset == 6'd35) ? 7'd56 :
    (X_address_offset == 6'd36) ? 7'd57 :
    (X_address_offset == 6'd37) ? 7'd50 :
    (X_address_offset == 6'd38) ? 7'd43 :
    (X_address_offset == 6'd39) ? 7'd36 :
    (X_address_offset == 6'd40) ? 7'd29 :
    (X_address_offset == 6'd41) ? 7'd22 :
    (X_address_offset == 6'd42) ? 7'd15 :
    (X_address_offset == 6'd43) ? 7'd23 :
    (X_address_offset == 6'd44) ? 7'd30 :
    (X_address_offset == 6'd45) ? 7'd37 :
    (X_address_offset == 6'd46) ? 7'd44 :
    (X_address_offset == 6'd47) ? 7'd51 :
    (X_address_offset == 6'd48) ? 7'd58 :
    (X_address_offset == 6'd49) ? 7'd59 :
    (X_address_offset == 6'd50) ? 7'd52 :
    (X_address_offset == 6'd51) ? 7'd45 :
    (X_address_offset == 6'd52) ? 7'd38 :
    (X_address_offset == 6'd53) ? 7'd31 :
    (X_address_offset == 6'd54) ? 7'd39 :
    (X_address_offset == 6'd55) ? 7'd46 :
    (X_address_offset == 6'd56) ? 7'd53 :
    (X_address_offset == 6'd57) ? 7'd60 :
    (X_address_offset == 6'd58) ? 7'd61 :
    (X_address_offset == 6'd60) ? 7'd54 :
    (X_address_offset == 6'd61) ? 7'd47 :
    (X_address_offset == 6'd62) ? 7'd55 :
    (X_address_offset == 6'd63) ? 7'd62 : 7'dx, 

endmodule
*/														