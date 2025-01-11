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
    output logic [6:0] dp_ram_X_address_a, 
    output logic dp_ram_X_renw_a
);

typedef enum logic [6:0] {
    IDLE, 
    LEAD_IN_0,
    LEAD_IN_1,
    LEAD_IN_2,
    LEAD_IN_3,
    LEAD_IN_4,
    LEAD_IN_5,
    LEAD_IN_USELESS,
    LEAD_IN_6,
    LEAD_IN_7,
    LEAD_IN_8,
    RELOAD_OPERATION1,
	RELOAD_OPERATION2,
    RELOAD_OPERATION3,
    RELOAD_OPERATION4,
	RELOAD_OPERATION0,
    RELOAD_OPERATIONINIT,
    HEADER_COMPAIR_OPERATION,
    DECODE,
    WRITE, 
    SPECIFIC_FOR_00_SECOND_RUN,
    SPECIFIC_FOR_ALL_ZEROS_RUN,
    COMPLETE
} state_t;

state_t state;

logic [47:0] bitstream_3_buffer;         //what in side the bitstream, 4 OF THOSE 

logic [3:0] prefix;   // presys

logic [15:0] DP_data_back,DP_data_back_for_oo_buffer; //data_pack
//quartz_extreme
logic [3:0] Quartz_extreme_op;
//quartz_extreme addr
logic [5:0] quartz_extreme_address;
//google_map
logic [3:0] google_map;
//sram_side_operator 
logic [17:0] SRAM_address_base,SRAM_address_offset;
assign SRAM_address_base = 18'd76800;
//this just for test
//assign SRAM_address_base = 18'd0;
//dp_ram_side_operator 

logic [6:0] X_address_offset; //use as a counter

///////////warring_the_toggle_system/////////different state finished?
//select Q
logic Q_number;
//logic 00
logic [6:0] the_last_stand;

//dp ram accolation
logic [6:0] quartz_Extreme_addr_calling;
//logic 11
logic [4:0] is_11x_counter;
logic [4:0] n_0_written;
logic just_for_test_purpose;
logic cut_the_head_only_in_decoder_happened;
//logic 10 is 100 or 101?
logic select_100_lol,select_1011_lol,select_1010_lol;

logic is_first_entrance;
//is this over total
///////////warring_the_toggle_system/////////different state finished?

always_ff @(posedge clk or negedge reset) begin 
    if (~reset) begin
        state <= IDLE;
        finish <= 0;
        SRAM_address_offset <= 0;
        X_address_offset <= 0;
        select_100_lol <= 0;
        select_1011_lol <= 0;
        select_1010_lol <= 0;
        is_11x_counter <= 0;
        n_0_written <= 0;
        DP_data_back <= 0;
        prefix <= 0;
        bitstream_3_buffer <= 0;
        state <= IDLE;
        the_last_stand <= 0;
        just_for_test_purpose <=0;
        cut_the_head_only_in_decoder_happened <= 0;
        DP_data_back_for_oo_buffer <= 0;
        is_first_entrance <= 1'b1;
		  dp_ram_X_renw_a <= 1'b1;
    end 
    else begin
        case (state)
        IDLE: begin
            finish <= 0;
            if(start) begin
                X_address_offset <= 0;
					 dp_ram_X_renw_a <= 1'b1;
                if(is_first_entrance) begin
                    state <= LEAD_IN_0;
                end
                else begin
                    state <= HEADER_COMPAIR_OPERATION;
                end
            end
        end
        LEAD_IN_0: begin
            //sram operation
            SRAM_W_EN_lossless_decode <= 1'b1;
            //calling sram data DEAD
            SRAM_address <= SRAM_address_base + SRAM_address_offset;
            SRAM_address_offset <= SRAM_address_offset + 1'b1;
            state <= LEAD_IN_1;
        end
        LEAD_IN_1: begin
            //calling sram data BEEF
            SRAM_address <= SRAM_address_base + SRAM_address_offset;
            SRAM_address_offset <= SRAM_address_offset + 1'b1;
            state <= LEAD_IN_2;
        end
        LEAD_IN_2: begin
            //calling Q determined
            SRAM_address <= SRAM_address_base + SRAM_address_offset;
            SRAM_address_offset <= SRAM_address_offset + 1'b1;
            //SRAM_W_EN_lossless_decode 
            state <= LEAD_IN_3;
        end
		LEAD_IN_3: begin
            //check dead
            if (SRAM_data_contains_bitstream != 16'hdead) begin
                state <= COMPLETE;
            end
	    	//calling WIDTH determined
            SRAM_address <= SRAM_address_base + SRAM_address_offset;
            SRAM_address_offset <= SRAM_address_offset + 1'b1;
		    state <= LEAD_IN_4;
		end
        LEAD_IN_4: begin
            //check beef
            if (SRAM_data_contains_bitstream != 16'hbeef) begin
                state <= COMPLETE;
            end
            //calling 48:32 determined
            SRAM_address <= SRAM_address_base + SRAM_address_offset;
            SRAM_address_offset <= SRAM_address_offset + 1'b1;
            state <= LEAD_IN_5;
        end
        LEAD_IN_5: begin
            //checkout Q
            if (SRAM_data_contains_bitstream[15] == 1'b1) begin
                Q_number <= 1'b1;
            end
            else begin
                Q_number <= 1'b0;
            end
                //calling 31:16 determined
            SRAM_address <= SRAM_address_base + SRAM_address_offset;
            SRAM_address_offset <= SRAM_address_offset + 1'b1;
            state <= LEAD_IN_USELESS;
        end
        LEAD_IN_USELESS: begin
            //bypass width
            //calling 15:0 determined
            SRAM_address <= SRAM_address_base + SRAM_address_offset;
            SRAM_address_offset <= SRAM_address_offset + 1'b1;
            state <= LEAD_IN_6;
        end
        LEAD_IN_6: begin
            //fill first 47-32 bit data 
            bitstream_3_buffer[47:32] <= SRAM_data_contains_bitstream;
            state <= LEAD_IN_7;
        end
        LEAD_IN_7: begin
            //fill sec 31-16 data
            bitstream_3_buffer[31:16] <= SRAM_data_contains_bitstream;
            state <= LEAD_IN_8;
        end
        LEAD_IN_8: begin
            //fill third 15 - 0 data
            bitstream_3_buffer[15:0] <= SRAM_data_contains_bitstream;
            //ready for the loop, first 48 bit filled
            state <= HEADER_COMPAIR_OPERATION;
        end
        RELOAD_OPERATIONINIT: begin
            SRAM_address <= SRAM_address_base + SRAM_address_offset;
            SRAM_address_offset <= SRAM_address_offset + 1'b1;
            state <= RELOAD_OPERATION0;
        end
        RELOAD_OPERATION0: begin
            //wait 1 sram
            bitstream_3_buffer <= bitstream_3_buffer << 16; //parpare for the load
            the_last_stand <= the_last_stand - 6'd16; //next block pointer
            state <= RELOAD_OPERATION1;
        end
        RELOAD_OPERATION1: begin
            //wait 2 sram
            state <= RELOAD_OPERATION2;
        end 
        RELOAD_OPERATION2: begin
            //wait3 sram
            state <= RELOAD_OPERATION3;
        end
        RELOAD_OPERATION3: begin
            //its time to filllllll!!!!!!
            bitstream_3_buffer[15:0] <= SRAM_data_contains_bitstream; // fill back the end
            state <= HEADER_COMPAIR_OPERATION;
        end
        HEADER_COMPAIR_OPERATION: begin
            //initial
            //is_11x_counter <= 0;
            //select_100_lol <= 0;
            prefix <= {bitstream_3_buffer[47-the_last_stand -: 2]};
            //get pointer shifted
            the_last_stand <= the_last_stand + 6'd2;
            state <= DECODE;					 
        end
        DECODE: begin
            cut_the_head_only_in_decoder_happened <= 1'b1;
            case (prefix)
                2'b00: begin
                    DP_data_back <= $signed(bitstream_3_buffer[47-the_last_stand -:3]); //the first time happened
                    the_last_stand <= the_last_stand + 6'd6; //counted as 6 per cycle, actually go for 2 timess
                    DP_data_back_for_oo_buffer <= $signed(bitstream_3_buffer[44-the_last_stand -:3]); //big prob! 
                    state <= WRITE;
                end

                2'b01: begin
                    DP_data_back <= $signed(bitstream_3_buffer[47 - the_last_stand -:3]); //check 3 bit
                    state <= WRITE;
                    the_last_stand <= the_last_stand + 6'd3;
                end

                2'b10: begin //still keep 47:0 all content
                    if(bitstream_3_buffer[47 - the_last_stand] == 0) begin //read 1
                        DP_data_back <= $signed(bitstream_3_buffer[46 - the_last_stand -:6]); //read 6
                        select_100_lol <= 1'b1;
                        the_last_stand <= the_last_stand + 6'd7; //cut 7
                    end 
                    else begin
                        if(bitstream_3_buffer[46 -the_last_stand] == 1'b1) begin //read1
                            DP_data_back <= $signed(bitstream_3_buffer[45 -the_last_stand -:9]); //read9
                            select_1011_lol <= 1'b1;
                            the_last_stand <= the_last_stand + 6'd11; //cut 11
                        end 
                        else begin
                            select_1010_lol <= 1'b1;
                            DP_data_back <= 0;
                            the_last_stand <= the_last_stand + 6'd2; //cut 2
                        end
                    end
                    state <= WRITE;
                end

                2'b11: begin
                    the_last_stand <= the_last_stand + 6'd3;
                    if(bitstream_3_buffer[47 - the_last_stand -:3] == 3'd0) begin //read 3 bit
                        DP_data_back <= 16'd0;
                        n_0_written <= 4'd8;
                        state <= WRITE;
						end
                    else begin
                        n_0_written <= bitstream_3_buffer[47 - the_last_stand -:3]; //read 3 bit
                        DP_data_back <= 16'd0;
                        state <= WRITE;                           
                    end
                end
            endcase
        end
        WRITE: begin
            if (X_address_offset > 6'd63) begin
                state <= COMPLETE;
				select_1010_lol <= 0;
				select_1011_lol <= 0;
				select_100_lol <= 0;                    
				is_11x_counter <= 0;
            end 
            else begin
                case (prefix)
                2'b00: begin
                    state <= SPECIFIC_FOR_00_SECOND_RUN;
                    // back to the dpram
                    dp_ram_X_data_a <= $signed(DP_data_back) << Quartz_extreme_op;
                    dp_ram_X_address_a <= quartz_Extreme_addr_calling;
                    X_address_offset <= X_address_offset + 1'b1;
                end
                2'b01: begin
                    if(the_last_stand > 6'd15) begin
                        state <= RELOAD_OPERATIONINIT;
                    end
                    else begin
                        state <= HEADER_COMPAIR_OPERATION;
                    end
                    dp_ram_X_data_a <= $signed(DP_data_back) << Quartz_extreme_op;
                    dp_ram_X_address_a <= quartz_Extreme_addr_calling;
                    X_address_offset <= X_address_offset + 1'b1;             
                end

                2'b11: begin
                    state <= SPECIFIC_FOR_ALL_ZEROS_RUN;     
                end
                2'b10: begin
                    if (select_100_lol == 1'b1) begin
                        dp_ram_X_data_a <= $signed(DP_data_back) << Quartz_extreme_op;
                        dp_ram_X_address_a <= quartz_Extreme_addr_calling;
                        X_address_offset <= X_address_offset + 1'b1;           
                        select_100_lol <= 0;   

                        if(the_last_stand > 6'd15) begin
                            state <= RELOAD_OPERATIONINIT;
                        end
                        else begin
                            state <= HEADER_COMPAIR_OPERATION;
                        end
                    end
                    else if (select_1011_lol == 1'b1) begin
                        dp_ram_X_data_a <= $signed(DP_data_back) << Quartz_extreme_op;
                        dp_ram_X_address_a <= quartz_Extreme_addr_calling;
                        X_address_offset <= X_address_offset + 1'b1; 
                        select_1011_lol <= 0;  
                        if(the_last_stand > 6'd15) begin
                            state <= RELOAD_OPERATIONINIT;
                        end
                        else begin
                            state <= HEADER_COMPAIR_OPERATION;
                        end
                    end
                    else if(select_1010_lol == 1'b1) begin //terminator 
                        dp_ram_X_data_a <= $signed(DP_data_back) << Quartz_extreme_op;
                        dp_ram_X_address_a <= quartz_Extreme_addr_calling;
                        X_address_offset <= X_address_offset + 1'b1;
                        state <= WRITE;  
                    end
                end
                endcase           
            end
        end
        SPECIFIC_FOR_00_SECOND_RUN: begin
            dp_ram_X_data_a <= $signed(DP_data_back_for_oo_buffer) << Quartz_extreme_op;
            //write one blk, then back
            dp_ram_X_address_a <= quartz_Extreme_addr_calling;
            X_address_offset <= X_address_offset + 1'b1;
            if(the_last_stand > 6'd15) begin
                state <= RELOAD_OPERATIONINIT;
            end
            else begin
                state <= HEADER_COMPAIR_OPERATION;
            end             
        end
        SPECIFIC_FOR_ALL_ZEROS_RUN: begin
            dp_ram_X_data_a <= $signed(DP_data_back) << Quartz_extreme_op;
            dp_ram_X_address_a <= quartz_Extreme_addr_calling;
            X_address_offset <= X_address_offset + 1'b1;        
            is_11x_counter <= is_11x_counter + 1'b1;                
            //check keeping witeen 0s
            if(is_11x_counter < (n_0_written - 2'd2)) begin
                state <= SPECIFIC_FOR_ALL_ZEROS_RUN;
            end
            else begin
                is_11x_counter <= 0;
                n_0_written <= 0;
                if(the_last_stand > 6'd15) begin
                    state <= RELOAD_OPERATIONINIT;
                end
                else begin
                    state <= HEADER_COMPAIR_OPERATION;
                end   
            end
        end
        COMPLETE: begin
            finish <= 1'b1;
            state <= IDLE;
            is_first_entrance <= 0;
        end
        endcase
    end
end

assign quartz_Extreme_addr_calling = 
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

always_comb begin
    google_map = {1'b0, quartz_Extreme_addr_calling[5:3]} + {1'b0, quartz_Extreme_addr_calling[2:0]};
    case(Q_number) 
    1'b1 : begin
        if (google_map == 4'd1 || google_map == 4'd2 || google_map == 4'd3) begin
            Quartz_extreme_op = 4'd1;
        end
        else if(google_map == 4'd4 || google_map == 4'd5) begin
            Quartz_extreme_op = 4'd2;
        end 
        else if(google_map == 4'd0 || google_map == 4'd6 || google_map == 4'd7) begin
            Quartz_extreme_op = 4'd3;
        end
        else if(google_map == 4'd8 || google_map == 4'd9 || google_map == 4'd10) begin
            Quartz_extreme_op = 4'd4;
        end
        else begin
            Quartz_extreme_op = 4'd5;
        end
    end
    1'b0: begin
        if (google_map == 4'd1) begin
            Quartz_extreme_op = 4'd2;
        end
        else if(google_map == 4'd0 || google_map == 4'd2 || google_map == 4'd3) begin
            Quartz_extreme_op = 4'd3;
        end 
        else if(google_map == 4'd4 || google_map == 4'd5) begin
            Quartz_extreme_op = 4'd4;
        end
        else if(google_map == 4'd6 || google_map == 4'd7) begin
            Quartz_extreme_op = 4'd5;
        end
        else begin
            Quartz_extreme_op = 4'd6;
        end
    end
    endcase
end

endmodule