//Milestone 2

`timescale 1ns/100ps
`ifndef DISABLE_DEFAULT_NET
`default_nettype none
`endif

module M2 (
	input logic Clock_50,
	input logic Resetn,
	output logic [17:0] SRAM_address,
	output logic [15:0] SRAM_write_data,
	output logic SRAM_we_n,
	input logic [15:0] SRAM_read_data,
	input logic start,
	output logic finish
);

logic [9:0]  CA_init_W, RA_init_W;
logic [19:0] exit_test_counter;
logic Y_finished_W;
logic is_M3_finish;

typedef enum logic [3:0] {
	S_idle,
	S_common1,
	S_common2,
	S_leadin1,
	S_leadin2,
	S_leadout1,
	S_leadout2,
	S_end
} Upper_state;

Upper_state upper_state;

// Dp RAM
logic [6:0] address_a_Sp, address_b_Sp,address_a_S, address_b_S,address_a_C, address_b_C, address_a_X, address_b_X;
logic [31:0] write_data_a [3:0];
logic [31:0] write_data_b [3:0];
logic write_enable_a [3:0];
logic write_enable_b [3:0];
logic [31:0] read_data_a [3:0];
logic [31:0] read_data_b [3:0];


// instantiate C
dual_port_RAM0 RAM_inst0 (
	.address_a ( address_a_C ),
	.address_b ( address_b_C ),
	.clock ( Clock_50 ),
	.data_a ( 32'd0 ),
	.data_b ( 32'd0 ),
	.wren_a ( 1'b0 ),
	.wren_b ( 1'b0 ),
	.q_a ( read_data_a[0] ),
	.q_b ( read_data_b[0] )
	);

// instantiate Sp
dual_port_RAM1 RAM_inst1 (
	.address_a ( address_a_Sp ),
	.address_b ( address_b_Sp ),
	.clock ( Clock_50 ),
	.data_a ( write_data_a[1] ),
	.data_b ( write_data_b[1] ),
	.wren_a ( write_enable_a[1] ),
	.wren_b ( write_enable_b[1] ),
	.q_a ( read_data_a[1] ),
	.q_b ( read_data_b[1] )
	);

// instantiate S
dual_port_RAM2 RAM_inst2 (
	.address_a ( address_a_S ),
	.address_b ( address_b_S ),
	.clock ( Clock_50 ),
	.data_a ( write_data_a[2] ),
	.data_b ( write_data_b[2] ),
	.wren_a ( write_enable_a[2] ),
	.wren_b ( write_enable_b[2] ),
	.q_a ( read_data_a[2] ),
	.q_b ( read_data_b[2] )
	);

// instantiate X
dual_port_RAM3 RAM_inst3 (
   .address_a ( address_a_X ),
	.address_b ( address_b_X ),
	.clock ( Clock_50 ),
	.data_a ( write_data_a[3] ),
	.data_b ( write_data_b[3] ),
	.wren_a ( write_enable_a[3] ),
	.wren_b ( 1'd0 ),
	.q_a ( read_data_a[3] ),
	.q_b ( read_data_b[3] )
);

//Fetch Sp
logic fetch_sp_start, fetch_sp_finish;
logic [6:0] fetch_dp_Sp_address_call_a;
logic fetch_dp_Sp_wren_a;
logic [31:0] fetch_dp_Sp_write_a;

logic dp_ram_Fetch_Extreme_control_a;
logic [31:0] dp_ram_Fetch_Exteme_control_a_data;

Fetch Fetch_Sp(
	// input logic 
	.Clock_50(Clock_50),
	// input logic 
	.Resetn(Resetn),
	// output logic [6:0] 
	.DP_RAM_address_X_a(dp_ram_Fetch_Exteme_control_a_data),
	// output logic [6:0] 
	.DP_RAM_address_X_b(address_b_X),
	// input logic [31:0] 
    .DP_RAM_read_data_X_a(read_data_a[3]),
	// input logic [31:0] 
	.DP_RAM_read_data_X_b(read_data_b[3]),
	// output logic 
	.DP_RAM_we_X_a(dp_ram_Fetch_Extreme_control_a),
	
	//written back system
	//output logic [6:0] 
    .DP_RAM_address_Sp_a(fetch_dp_Sp_address_call_a),
    //output logic [31:0] 
    .DP_RAM_write_data_Sp_a(fetch_dp_Sp_write_a),
	// output logic 
	.DP_RAM_we_Sp_a(fetch_dp_Sp_wren_a),
	// output logic 
	.finish(fetch_sp_finish),
	// input logic 
	.M3_finish(fetch_sp_start)
);

//Compute T
logic compute_T_start, compute_T_finish;

logic [6:0] CT_dp_C_address_call_a,CT_dp_C_address_call_b;
logic [6:0] CT_dp_Sp_address_call_a,CT_dp_Sp_address_call_b;
logic [6:0] CT_dp_S_address_call_b;

logic CT_dp_Sp_wren_b, CT_dp_S_wren_b;

logic [31:0] CT_dp_S_data_b, CT_dp_Sp_data_b;

CT Compute_T (
		//input logic 
	.Clock_50(Clock_50),
		//input logic 
	.Resetn(Resetn),

	//C dpram
		//output logic [6:0] 
	.Address_C_a(CT_dp_C_address_call_a),
		//input logic [31:0] 
	.Data_out_C_a(read_data_a[0]),
		//output logic [6:0] 
	.Address_C_b(CT_dp_C_address_call_b),
		//input logic address_a_Sp <= 0;
	.Data_out_C_b(read_data_b[0]),

	//Sp dpram
		//output logic [6:0] 
	.Address_Sp_a(CT_dp_Sp_address_call_a),
		//input logic [31:0] 
	.Data_out_Sp_a(read_data_a[1]),
		//output logic [6:0] 
	.Address_Sp_b(CT_dp_Sp_address_call_b),
		//input logic [31:0] 
	.Data_out_Sp_b(read_data_b[1]),
		//output logic 
	.Write_en_Sp_b(CT_dp_Sp_wren_b),
		//output logic [31:0] 
	.Data_in_Sp_b(CT_dp_Sp_data_b),

	//S dpram
		//output logic [6:0] 
	.Address_S_b(CT_dp_S_address_call_b),
		//output logic [31:0] 
	.Data_in_S_b(CT_dp_S_data_b),
		//output logic
	.Write_en_S_b(CT_dp_S_wren_b),

		//input logic
	.start(compute_T_start),
		//output logic 
	.finish(compute_T_finish)
);

//Compute S
logic compute_S_start, compute_S_finish;

logic [6:0] CS_dp_C_address_call_a,CS_dp_C_address_call_b;
logic [6:0] CS_dp_Sp_address_call_b;
logic [6:0] CS_dp_S_address_call_a,CS_dp_S_address_call_b;

logic CS_dp_S_wren_b;

logic [31:0] CS_dp_S_data_b;

CS Compute_S(
		//input logic 
	.Clock_50(Clock_50),
		//input logic 
	.Resetn(Resetn),

	//C dpram
		//output logic [6:0] 
	.Address_C_a(CS_dp_C_address_call_a),
		//input logic [31:0] 
	.Data_out_C_a(read_data_a[0]),
		//output logic [6:0] 
	.Address_C_b(CS_dp_C_address_call_b),
		//input logic [31:0] 
	.Data_out_C_b(read_data_b[0]),

	//Sp dpram
		//output logic [6:0] 
	.Address_Sp_b(CS_dp_Sp_address_call_b),
		//input logic [31:0] 
	.Data_out_Sp_b(read_data_b[1]),

	//S dpram
		//output logic [6:0] 
	.Address_S_a(CS_dp_S_address_call_a),
		//input logic [31:0] 
	.Data_out_S_a(read_data_a[2]),
		//output logic [6:0] 
	.Address_S_b(CS_dp_S_address_call_b),
		//input logic [31:0] 
	.Data_out_S_b(read_data_b[2]),
		//output logic 
	.Write_en_S_b(CS_dp_S_wren_b),
		//output logic [31:0] 
	.Data_in_S_b(CS_dp_S_data_b),

		//input logic 
	.start(compute_S_start),
		//output logic 
	.finish(compute_S_finish)
);

//Write S
logic write_S_start, write_S_finish;

logic [17:0] writeS_SRAM_address;
logic [15:0] writeS_SRAM_write_data;
logic writeS_SRAM_wen;


logic [6:0] WB_dp_S_address_call_a;

WriteS WS(
	//input logic 
	.Clock_50(Clock_50),
	//input logic 
	.Resetn(Resetn),

		//output logic [17:0] 
	.SRAM_address(writeS_SRAM_address),
    	//output logic [15:0] 
	.SRAM_write_data(writeS_SRAM_write_data),
	.SRAM_we_n(writeS_SRAM_wen),
	
		//output logic [6:0] 
	.Address_S_a(WB_dp_S_address_call_a),
		//input logic [31:0] 
	.Data_out_S_a(read_data_a[2]),

		//input logic [8:0] 
	.RA_init(RA_init_W),
		//input logic [8:0] 
	.CA_init(CA_init_W),
	//input logic 
	.start(write_S_start),
	//output logic 
	.finish(write_S_finish),	
	.Y_finished(Y_finished_W)
);

//M3//bill
logic startM3;

logic [17:0] M3_SRAM_address;

logic M3_control_dp_X_wren_a;
logic [6:0] M3_control_do_X_address_a;
//logic [31:0] m3_dp_X_write_a;

M3 m3_unit(
	//input logic 
	.Clock_50(Clock_50),
	//input logic 
	.Resetn(Resetn),
	
	//SRAM_CONTROLLER <-- DIRECT CONTACT WITH SYS_SRAM
	//output logic [17:0] 
	.SRAM_address(M3_SRAM_address),
	//input logic [15:0] 
	.SRAM_read_data(SRAM_read_data),

	//DP RAM I/O --> FETCH USE IT 
	//output logic [6:0] 
	.DP_RAM_address_a(M3_control_do_X_address_a),
	//output logic [31:0] 
	.DP_write_DATA_a(write_data_a[3]),
	//output logic 
	.DP_write_enable_a(M3_control_dp_X_wren_a),
	
	//input logic 
	.start(startM3),
	//output logic 
	.finish(fetch_sp_start),
	//output
	.M3_finish_or_not(is_M3_finish)
);

//here jack  lose on speed compitation
/*

lossless_decoder_Quantization Quartz_unit(
    //input logic 
	 .start(startM3),
    //output logic 
	 .finish(fetch_sp_start), 

    //input  logic 
	 .clk(Clock_50),              
    //input  logic 
	 .reset(Resetn),            

    //from sram calling adrrs
    //output logicM3_SRAM_address [17:0] 
	 .SRAM_address(M3_SRAM_address),
    //input  logic [15:0] 
	 .SRAM_data_contains_bitstream(SRAM_read_data), 
    //output logic 
	 .SRAM_W_EN_lossless_decode(),

    //dualport ram access port a only lol
    //output logic [31:0] 
	 .dp_ram_X_data_a(write_data_a[3]),
    //output logic [6:0] 
	 .dp_ram_X_address_a(address_a_X), 
    //output logic 
	 .dp_ram_X_renw_a(write_enable_a[3])
);
*/

logic CS_flag, FS_flag;

always_ff @(posedge Clock_50 or negedge Resetn) begin
	if (~Resetn) begin
		finish <= 1'b0;
      upper_state <= S_idle;
      startM3 <= 0;
      compute_T_start <= 0;
      compute_S_start <= 0;
      write_S_start <= 0;
		CA_init_W <= 0;
		RA_init_W <= 0;
		Y_finished_W <= 0;
		exit_test_counter <=0; 
		CS_flag <= 1'b0;
		FS_flag <= 1'b0;
		//is_M3_finish <= 1'b0;
    end 
    else begin
        case(upper_state)
        S_idle: begin
				finish <= 1'b0;
            if (start) begin
					startM3 <= 1'b1;
					//is_M3_finish <= 1'b0;
					upper_state <= S_leadin1;
            end
        end
        S_leadin1: begin
            startM3 <= 0;
				//
            if(fetch_sp_finish) begin
					compute_T_start <= 1'b1;
					upper_state <= S_leadin2;
					//upper_state <= S_end;
           end
        end
        S_leadin2: begin
            compute_T_start <= 0;
            if(compute_T_finish) begin
                compute_S_start <= 1'b1;
					 startM3 <= 1'b1;
					 //is_M3_finish <= 1'b0;
                upper_state <= S_common1;
            end
        end
        S_common1: begin 
            compute_S_start <= 1'b0;
				startM3 <= 1'b0;
				//
				if(compute_S_finish) begin
					CS_flag <= 1'b1;
				end
				if(fetch_sp_finish) begin
					FS_flag <= 1'b1;
				end
				if(CS_flag && FS_flag) begin
					CS_flag <= 1'b0;
					FS_flag <= 1'b0;
					compute_T_start <= 1'b1;
               write_S_start <= 1'b1;
               upper_state <= S_common2;
				end
        end
        S_common2: begin 
            compute_T_start <= 1'b0;
            write_S_start <= 1'b0;
				if (compute_T_finish) begin 
					if (exit_test_counter == 20'd2398) begin
						compute_S_start <= 1'b1;
						upper_state <= S_leadout1;
					end else begin 
						compute_S_start <= 1'b1;
						startM3 <= 1'b1;
						//is_M3_finish <= 1'b0;
						upper_state <= S_common1;
						exit_test_counter <= exit_test_counter + 1'b1;
					end	
					if (!Y_finished_W) begin
						if (CA_init_W == 10'd156) begin
							CA_init_W <= 10'd0;
							RA_init_W <= RA_init_W + 10'd8;
						end else begin
							CA_init_W <= CA_init_W + 10'd4;
						end
					end else begin 
						if (CA_init_W == 10'd76) begin
							CA_init_W <= 10'd0;
							RA_init_W <= RA_init_W + 10'd8;
						end else begin
							CA_init_W <= CA_init_W + 10'd4;
						end
					end
					if (RA_init_W == 10'd232 && CA_init_W == 10'd156) begin 
						Y_finished_W <= 1'd1;	
						RA_init_W <= 0;
					end
            end
        end
        S_leadout1: begin 
            compute_S_start <= 0;
            if(compute_S_finish) begin
                write_S_start <= 1'b1;
                upper_state <= S_leadout2;
            end
        end
        S_leadout2: begin 
				write_S_start <= 0;
            if(write_S_finish) begin
                upper_state <= S_end;
            end
        end
        S_end: begin
            finish <= 1'b1;
            upper_state <= S_idle;
        end
        endcase
    end
end

// SRAM
always_comb begin 
	if (upper_state == S_leadin1 || upper_state == S_common1) begin 
		SRAM_address = M3_SRAM_address;
		SRAM_write_data = 16'b0;
		SRAM_we_n = 1'b1;
	end else if (upper_state == S_leadout2 || upper_state == S_common2) begin 
		SRAM_address = writeS_SRAM_address;
		SRAM_write_data = writeS_SRAM_write_data;
		SRAM_we_n = writeS_SRAM_wen;
	end else begin
		SRAM_address = 0;
		SRAM_write_data = 16'b0;
		SRAM_we_n = 1'b1;
	end
end

// dp_ram_C
always_comb begin 
	if (upper_state == S_leadin2 || upper_state == S_common2) begin 
		//CT
		address_a_C <= CT_dp_C_address_call_a;
		address_b_C <= CT_dp_C_address_call_b;
	end else if (upper_state == S_leadout1 || upper_state == S_common1) begin 
		//CS
		address_a_C <= CS_dp_C_address_call_a;
		address_b_C <= CS_dp_C_address_call_b;
	end else begin
		address_a_C <= 0;
		address_b_C <= 0;
	end
end

// dp_ram_Sp
always_comb begin 
	if (upper_state == S_leadin1) begin 
		//Fetch
		address_a_Sp <= fetch_dp_Sp_address_call_a;
		address_b_Sp <= 0;
		write_data_a[1] <= fetch_dp_Sp_write_a;
		write_data_b [1] <= 0;
		write_enable_a [1] <= fetch_dp_Sp_wren_a;
		write_enable_b [1] <= 0;
	end else if (upper_state == S_leadin2 || upper_state == S_common2) begin 
		//CT
		address_a_Sp <= CT_dp_Sp_address_call_a;
		address_b_Sp <= CT_dp_Sp_address_call_b;
		write_data_a[1] <= 0;
		write_data_b [1] <= CT_dp_Sp_data_b;
		write_enable_a [1] <= 0;
		write_enable_b [1] <= CT_dp_Sp_wren_b;
	end else if (upper_state == S_common1) begin 
		//Fetch and CS
		address_a_Sp <= fetch_dp_Sp_address_call_a;
		address_b_Sp <= CS_dp_Sp_address_call_b;
		write_data_a[1] <= fetch_dp_Sp_write_a;
		write_data_b [1] <= 0;
		write_enable_a [1] <= fetch_dp_Sp_wren_a;
		write_enable_b [1] <= 0;
	end else if (upper_state == S_leadout1) begin 
		//CS
		address_a_Sp <= 0;
		address_b_Sp <= CS_dp_Sp_address_call_b;
		write_data_a[1] <= 0;
		write_data_b [1] <= 0;
		write_enable_a [1] <= 0;
		write_enable_b [1] <= 0;
	end else begin
		address_a_Sp <= 0;
		address_b_Sp <= 0;
		write_data_a[1] <= 0;
		write_data_b [1] <= 0;
		write_enable_a [1] <= 0;
		write_enable_b [1] <= 0;
	end
end

// dp_ram_S
always_comb begin 
	if (upper_state == S_leadout2) begin 
		//WriteS
		address_a_S <= WB_dp_S_address_call_a;
		address_b_S <= 0;
		write_data_a[2] <= 0;
		write_data_b [2] <= 0;
		write_enable_a [2] <= 0;
		write_enable_b [2] <= 0;
	end else if (upper_state == S_leadin2) begin 
		//CT
		address_a_S <= 0;
		address_b_S <= CT_dp_S_address_call_b;
		write_data_a[2] <= 0;
		write_data_b [2] <= CT_dp_S_data_b;
		write_enable_a [2] <= 0;
		write_enable_b [2] <= CT_dp_S_wren_b;
	end else if (upper_state == S_common2) begin 
		//WriteS and CT
		address_a_S <= WB_dp_S_address_call_a;
		address_b_S <= CT_dp_S_address_call_b;
		write_data_a[2] <= 0;
		write_data_b [2] <= CT_dp_S_data_b;
		write_enable_a [2] <= 0;
		write_enable_b [2] <= CT_dp_S_wren_b;
	end else if (upper_state == S_leadout1 || upper_state == S_common1) begin 
		//CS
		address_a_S <= CS_dp_S_address_call_a;
		address_b_S <= CS_dp_S_address_call_b;
		write_data_a[2] <= 0;
		write_data_b [2] <= CS_dp_S_data_b;
		write_enable_a [2] <= 0;
		write_enable_b [2] <= CS_dp_S_wren_b;
	end else begin
		address_a_S <= 0;
		address_b_S <= 0;
		write_data_a[2] <= 0;
		write_data_b [2] <= 0;
		write_enable_a [2] <= 0;
		write_enable_b [2] <= 0;
	end
end


assign address_a_X = (is_M3_finish)?  dp_ram_Fetch_Exteme_control_a_data : M3_control_do_X_address_a;
assign write_enable_a[3] =  M3_control_dp_X_wren_a;
////////
endmodule 
