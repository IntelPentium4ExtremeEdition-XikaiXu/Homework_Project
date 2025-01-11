//devcoding
`timescale 1ns/100ps
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif

//lossless_decoding system
module lossless_decoder_Quantization (
    input logic start,
    output logic finish, 

    input  logic clk,              
    input  logic reset,            

    //from sram calling adrrs
    output logic [17:0] SRAM_address,
    input  logic [15:0] SRAM_data_contains_bitstream, 
    output logic SRAM_W_EN_lossless_decode,

    //dualport ram access port a only lol
    output logic [31:0] dp_ram_X_data_a,
    output logic [6:0] dp_ram_X_address_a, //positon K-mapping  //WANNA TO GET THE DATA FROM OUTSIDE
    output logic dp_ram_X_renw_a
);

typedef enum logic [6:0] {
    IDLE, 
    LEAD_IN_0,
    LEAD_IN_1,
    LEAD_IN_2,
	LEAD_IN_wait,
    LEAD_IN_3,
    LEAD_IN_4,
    SECOND_THE_LAST_READY_TO_BUF,
    RELOAD_OPERATION1,
	RELOAD_OPERATION2,
    RELOAD_OPERATION3,
	RELOAD_OPERATION0,
	RELOAD_OPERATION4,
    HEADER_COMPAIR_OPERATION,
    DECODE,
    WRITE, 
    SECOND_THE_LAST_READY_TO_BUF_COMMON,
    COMPLETE
} state_t;

state_t state;

//might using zig-zag structure
logic [5:0] pixel_counter;      // bow much blocks we have filled 
logic [47:0] bitstream_3_buffer;         //what in side the bitstream, 4 OF THOSE 

logic [3:0] prefix;   // presys

logic [15:0] DP_data_back;

//sram_side_operator 
logic [17:0] SRAM_address_base,SRAM_address_offset;
//assign SRAM_address_base = 18'd76800;decoding
//this just for test
assign SRAM_address_base = 18'd0;
//dp_ram_side_operator 
logic [5:0] X_address_offset;
logic [7:0] decoded_value;

//different state finished?
//logic 00
logic is_00_another_fxxking_time;

logic [6:0] the_last_stand,the_second_last_stand;

//dp ram accolation

logic [6:0] post_zigzag_position;
//logic 11
logic [4:0] is_100_counter;
logic [4:0] n_0_written;
logic just_for_test_purpose;
logic cut_the_head_only_in_decoder_happened;
//logic 10 is 100 or 101?
logic select_100_lol,select_1011_lol,select_1010_lol;
logic just_exit_from_reload;
always_ff @(posedge clk or negedge reset) begin 
    if (~reset) begin
    state <= IDLE;
    finish <= 0;
    SRAM_address_offset <= 0;
    X_address_offset <= 0;
    decoded_value <= 0;
    select_100_lol <= 0;
    select_1011_lol <= 0;
    select_1010_lol <= 0;
    is_100_counter <= 0;
    n_0_written <= 0;
    is_00_another_fxxking_time <= 0;
    DP_data_back <= 0;
    prefix <= 0;
    bitstream_3_buffer <= 0;
    pixel_counter <= 0;
    state <= IDLE;
	the_last_stand <= 0;
	just_for_test_purpose <=0;
    the_second_last_stand <= 0;
    cut_the_head_only_in_decoder_happened <= 0;
    just_exit_from_reload <= 0;
    end else begin
        case (state)
            IDLE: begin
                finish <= 0;
                if(start) begin
                    state <= LEAD_IN_0;
                end
            end
            LEAD_IN_0: begin
                SRAM_W_EN_lossless_decode <= 1'b1;
                SRAM_address <= SRAM_address_base + SRAM_address_offset;
                SRAM_address_offset <= SRAM_address_offset + 1'b1;
                state <= LEAD_IN_1;
            end
            LEAD_IN_1: begin
                SRAM_address <= SRAM_address_base + SRAM_address_offset;
                SRAM_address_offset <= SRAM_address_offset + 1'b1;
                state <= LEAD_IN_2;
            end
            LEAD_IN_2: begin
                SRAM_address <= SRAM_address_base + SRAM_address_offset;
                SRAM_address_offset <= SRAM_address_offset + 1'b1;
                //SRAM_W_EN_lossless_decode 
                state <= LEAD_IN_wait;
            end
				LEAD_IN_wait: begin
				bitstream_3_buffer[47:32] <= SRAM_data_contains_bitstream;
				state <= LEAD_IN_3;
				end
            LEAD_IN_3: begin
                //SRAM_W_EN_lossless_decode <= 0;
                bitstream_3_buffer[31:16] <= SRAM_data_contains_bitstream;
                state <= LEAD_IN_4;
            end
            LEAD_IN_4: begin
                bitstream_3_buffer[15:0] <= SRAM_data_contains_bitstream;
                state <= HEADER_COMPAIR_OPERATION;
            end
            HEADER_COMPAIR_OPERATION: begin
                is_00_another_fxxking_time <= 0;
                is_100_counter <= 0;
                prefix <= bitstream_3_buffer[47:46];
                //the_last_stand <= the_last_stand + 6'd2;
                /////this is testing stragight2 only////
                //bitstream_3_buffer <= bitstream_3_buffer << 2;
                state <= DECODE;					 
            end
				
			RELOAD_OPERATION0: begin
				bitstream_3_buffer <= bitstream_3_buffer << (6'd16 - the_second_last_stand); //max periotic
				//the_last_stand <= the_last_stand - 6'd17; //next block pointer
				state <= RELOAD_OPERATION1;
                //the_second_last_stand <= 6'd16 - the_second_last_stand;
                //the_second_last_stand <= 0;
			end
			RELOAD_OPERATION1: begin
				state <= RELOAD_OPERATION2;
                //the_second_last_stand <= the_last_stand // to 23
			end 
			RELOAD_OPERATION2: begin
				//wait?
				state <= RELOAD_OPERATION3;
			end
			RELOAD_OPERATION3: begin
				bitstream_3_buffer[15:0] <= SRAM_data_contains_bitstream; // fill back
				
				//the_last_stand <= the_last_stand - 6'd16;
				
				bitstream_3_buffer <= bitstream_3_buffer << the_last_stand + 1'b1;
				state <= RELOAD_OPERATION4;
				
				//the_last_stand <= the_last_stand + the_last_stand; //neo is kept the old val
				
			end
			RELOAD_OPERATION4: begin //get valuable
				//bitstream_3_buffer <= bitstream_3_buffer << (the_last_stand - 6'd16); //last posiotn
				the_last_stand <= the_last_stand - 6'd16; //neo is matching like old way
				state <= SECOND_THE_LAST_READY_TO_BUF;
			end
            SECOND_THE_LAST_READY_TO_BUF: begin
                the_second_last_stand <= the_last_stand; // the head of the less
                state <= HEADER_COMPAIR_OPERATION;
                just_exit_from_reload <= 1'b1;
            end
            DECODE: begin
                cut_the_head_only_in_decoder_happened <= 1'b1;
                case (prefix)
                    2'b00: begin
                        if(is_00_another_fxxking_time == 1'b0) begin
                            DP_data_back <= $signed(bitstream_3_buffer[45:43]);
                            the_last_stand <= the_last_stand + 6'd8;
                        end
                        else begin
                            DP_data_back <= $signed(bitstream_3_buffer[42:40]); //big prob!
                            //the_last_stand <= the_last_stand + 6'd3;
                        end
                        state <= WRITE;
                        
                    end
                    2'b01: begin
                        DP_data_back <= $signed(bitstream_3_buffer[45:43]);
                        state <= WRITE;
                        the_last_stand <= the_last_stand + 6'd5;
                    end
                    2'b10: begin //still keep 47:0 all content
                        if(bitstream_3_buffer[45] == 0) begin //read 1
                            DP_data_back <= $signed(bitstream_3_buffer[44:39]); //read 6
                            select_100_lol <= 1'b1;
                            the_last_stand <= the_last_stand + 6'd9;
                        end else begin
                            if(bitstream_3_buffer[44] == 1'b1) begin //read1
                                DP_data_back <= $signed(bitstream_3_buffer[43:35]); 
                                select_1011_lol <= 1'b1;
                                the_last_stand <= the_last_stand + 6'd13;
                            end else begin
                                select_1010_lol <= 1'b1;
                                DP_data_back <= 0;
                                the_last_stand <= the_last_stand + 6'd4;
                            end
                        end
                        state <= WRITE;
                    end
                    2'b11: begin
                        the_last_stand <= the_last_stand + 6'd5;
                        if(bitstream_3_buffer[45:43] == 0) begin
                            DP_data_back <= 16'd0;
                            n_0_written <= 4'd8;
                            state <= WRITE;
						end
                        else begin
                            n_0_written <= bitstream_3_buffer[45:43];
                            DP_data_back <= 16'd0;
                            state <= WRITE;                           
                        end
                    end
                endcase
            end
            WRITE: begin
                //written -4 to 3 random val for 2 times, case 00
                if (prefix == 2'b00) begin
                    if(!is_00_another_fxxking_time) begin
                       state <= DECODE;
                       is_00_another_fxxking_time <= 1'b1;
                    end
                    else begin
                        state <= HEADER_COMPAIR_OPERATION;                        
                    end
                    // back to the dpram
                    dp_ram_X_data_a <= DP_data_back;
                    //write one blk, then back
                    dp_ram_X_address_a <= post_zigzag_position;
                    X_address_offset <= X_address_offset + 1'b1;
                end

                //written -4 to 3 random val for 1 times, case 01
                if (prefix == 2'b01) begin
                    state <= HEADER_COMPAIR_OPERATION;
                        // back to the dpram
                    dp_ram_X_data_a <= DP_data_back;
                        //write one blk, then back
                    dp_ram_X_address_a <= post_zigzag_position;
                    X_address_offset <= X_address_offset + 1'b1;                    
                end

                //written n or 8 zeros case 11
                if (prefix == 2'b11) begin
                    dp_ram_X_data_a <= DP_data_back;
                        //write one blk, then back
                    dp_ram_X_address_a <= post_zigzag_position;
                    X_address_offset <= X_address_offset + 1'b1;        
                    is_100_counter <= is_100_counter + 1'b1;
						  
						  //check keeping witeen 0s
					if(is_100_counter < (n_0_written - 1'b1)) begin
						state <= WRITE;
					end
					else begin
						is_100_counter <= 0;
						n_0_written <= 0;
						state <= HEADER_COMPAIR_OPERATION;
					end
                end

                //written n zeros case 10 
                if (prefix == 2'b10) begin
                    if (select_100_lol == 1'b1) begin
                        dp_ram_X_data_a <= DP_data_back;
                        //write one blk, then back
                        dp_ram_X_address_a <= post_zigzag_position;
                        X_address_offset <= X_address_offset + 1'b1;
                        select_100_lol <= 0;   
                        state <= HEADER_COMPAIR_OPERATION;
					end
                    else if (select_1011_lol == 1'b1) begin
                        dp_ram_X_data_a <= DP_data_back;
                        //write one blk, then back
                        dp_ram_X_address_a <= post_zigzag_position;
                        X_address_offset <= X_address_offset + 1'b1; 
                        select_1011_lol <= 0;  
                        state <= HEADER_COMPAIR_OPERATION;
                    end
                    else if(select_1010_lol == 1'b1) begin //terminator 
                        dp_ram_X_data_a <= DP_data_back;
                        //write one blk, then back
                        //select_1010_lol <= 0;
                        dp_ram_X_address_a <= post_zigzag_position;
                        X_address_offset <= X_address_offset + 1'b1;
                        state <= WRITE;  
                    end
                end
                if(the_last_stand < 6'd16 && (cut_the_head_only_in_decoder_happened == 1'b1)) begin
                    if(just_exit_from_reload) begin
                        the_second_last_stand <= the_second_last_stand - 6'd16;
                        just_exit_from_reload <= 0;
                    end
                    else begin
                        case(prefix) 
                        2'b00: begin
                            the_second_last_stand <= the_second_last_stand + 6'd8;
                        end
                        2'b01: begin
                            the_second_last_stand <= the_second_last_stand + 6'd5;
                        end
                        2'b10: begin
                            if(select_100_lol== 1'b1) begin
                                the_second_last_stand <= the_second_last_stand + 6'd9;
                            end 
                            else if(select_1011_lol== 1'b1)begin
                                the_second_last_stand <= the_second_last_stand + 6'd13;
                            end 
                            else if(select_1011_lol== 1'b1) begin
                                the_second_last_stand <= the_second_last_stand + 6'd4;
                            end
                        end
                        2'b11: begin
                            the_second_last_stand <= the_second_last_stand + 6'd5;
                        end
                        endcase
                    end
                end
                
                //head_cutting
                if (the_last_stand < 6'd16 && (cut_the_head_only_in_decoder_happened == 1'b1)) begin
                    case(prefix) 
                    2'b00: begin
                        bitstream_3_buffer <= bitstream_3_buffer << 8; //cut head
                    end
                    2'b01: begin
                        bitstream_3_buffer <= bitstream_3_buffer << 5; //cut head
                    end
                    2'b10: begin
                        if(select_100_lol== 1'b1) begin
                            bitstream_3_buffer <= bitstream_3_buffer << 9;
                        end 
                        else if(select_1011_lol== 1'b1)begin
                            bitstream_3_buffer <= bitstream_3_buffer << 13;
                        end 
                        else if(select_1011_lol== 1'b1) begin
                            bitstream_3_buffer <= bitstream_3_buffer << 4;
                        end
                    end
                    2'b11: begin
                        bitstream_3_buffer <= bitstream_3_buffer << 5;
                    end
                    endcase
                    cut_the_head_only_in_decoder_happened <= 0;
                end

                
					 
				if(the_last_stand > 6'd16) begin
                    SRAM_address <= SRAM_address_base + SRAM_address_offset;
					SRAM_address_offset <= SRAM_address_offset + 1'b1;
                    //the_second_last_stand <= the_last_stand;//record the last use of reload location, use for cutting garbage
                    if (X_address_offset == 6'd63) begin
                    // 8x8 finish
                        state <= COMPLETE;
                        select_1010_lol <= 0;
                        select_1011_lol <= 0;
                        select_100_lol <= 0;
                        is_00_another_fxxking_time <= 0;
                        is_100_counter <= 0;
                        SRAM_address_offset <= 0;
                    end else begin
                        state <= RELOAD_OPERATION0;
                    end
                end 
                else begin
                    if (X_address_offset == 6'd63) begin
                    // 8x8 finish
                        state <= COMPLETE;
                        select_1010_lol <= 0;
                        select_1011_lol <= 0;
                        select_100_lol <= 0;
                        is_00_another_fxxking_time <= 0;
                        is_100_counter <= 0;
                        SRAM_address_offset <= 0;
                    end
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
    (X_address_offset == 6'd59) ? 7'd54 :
    (X_address_offset == 6'd60) ? 7'd47 :
    (X_address_offset == 6'd61) ? 7'd55 :
    (X_address_offset == 6'd62) ? 7'd62 :
    (X_address_offset == 6'd63) ? 7'd63 : 7'd0; 

endmodule

