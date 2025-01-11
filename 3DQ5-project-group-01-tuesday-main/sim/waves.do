# activate waveform simulation

view wave

# format signal names in waveform

configure wave -signalnamewidth 1
configure wave -timeline 0
configure wave -timelineunits us

# add signals to waveform

#add wave -divider -height 20 {Top-level signals}
#add wave -bin UUT/CLOCK_50_I
#add wave -bin UUT/resetn
#add wave UUT/top_state
add wave -uns UUT/UART_timer
add wave -uns UUT/top_state
#add wave -divider -height 10 {SRAM signals}
add wave -bin UUT/CLOCK_50_I
add wave -uns UUT/SRAM_address

add wave -hex UUT/SRAM_write_data
add wave -bin UUT/SRAM_we_n
add wave -hex UUT/SRAM_read_data

add wave -divider -height 10 {M1 signals}
add wave UUT/m1_unit/sysio

add wave -divider -height 10 {M2 signals}
#add wave -hex UUT/m2_unit/read_data_a
#add wave -hex UUT/m2_unit/read_data_b
add wave -bin UUT/m2_unit/write_enable_a
#add wave -bin UUT/m2_unit/write_enable_b
#add wave -hex UUT/m2_unit/write_data_a
#add wave -hex UUT/m2_unit/write_data_b
add wave -uns UUT/m2_unit/address_a_X
#add wave -uns UUT/m2_unit/address_b_X


#add wave -bin UUT/m2_unit/SRAM_we_n
#add wave -uns UUT/m2_unit/SRAM_address
#add wave -hex UUT/m2_unit/SRAM_read_data
#add wave -hex UUT/m2_unit/SRAM_write_data
#add wave -uns UUT/m2_unit/RA_init_F
#add wave -uns UUT/m2_unit/CA_init_F
#add wave -uns UUT/m2_unit/RA_init_W
#add wave -uns UUT/m2_unit/CA_init_W
#add wave -bin UUT/m2_unit/Y_finished
#add wave -bin UUT/m2_unit/Y_finished_W
#add wave -uns UUT/m2_unit/Fetch_Sp/Pre_IDCT_address
#add wave -uns UUT/m2_unit/WS/WB_offset	
#add wave -uns UUT/m2_unit/exit_test_counter

add wave UUT/m2_unit/WS/wb_s_state
#add wave -bin UUT/m2_unit/WS/start
#add wave -bin UUT/m2_unit/WS/finish

add wave UUT/m2_unit/Compute_T/compute_T_state
#add wave -bin UUT/m2_unit/Compute_T/start
#add wave -bin UUT/m2_unit/Compute_T/finish
#add wave -uns UUT/m2_unit/Compute_T/T1_buffer_dp_offset
#add wave -uns UUT/m2_unit/Compute_T/Address_C_a
#add wave -uns UUT/m2_unit/Compute_T/Address_C_b
#add wave -uns UUT/m2_unit/Compute_T/Address_Sp_a
#add wave -uns UUT/m2_unit/Compute_T/Address_Sp_b
#add wave -bin UUT/m2_unit/Compute_T/Write_en_Sp_b
#add wave -dec UUT/m2_unit/Compute_T/Data_in_Sp_b
#add wave -uns UUT/m2_unit/Compute_T/Address_S_b
#add wave -dec UUT/m2_unit/Compute_T/Data_in_S_b
#add wave -dec UUT/m2_unit/Compute_T/Mult1_result
#add wave -dec UUT/m2_unit/Compute_T/Mult2_result
#add wave -dec UUT/m2_unit/Compute_T/Mult3_result
#add wave -dec UUT/m2_unit/Compute_T/T0
#add wave -dec UUT/m2_unit/Compute_T/T1
#add wave -dec UUT/m2_unit/Compute_T/T2


add wave UUT/m2_unit/m3_unit/m3_state
#add wave -uns UUT/m2_unit/m3_unit/DP_RAM_address_a
#add wave -bin UUT/m2_unit/m3_unit/DP_write_enable_a
#add wave -uns UUT/m2_unit/m3_unit/DP_write_DATA_a
#add wave -bin UUT/m2_unit/m3_unit/finish
#add wave -bin UUT/m2_unit/m3_unit/start
#add wave -hex UUT/m2_unit/m3_unit/header1
#add wave -hex UUT/m2_unit/m3_unit/header2
#add wave -bin UUT/m2_unit/m3_unit/DEAD_flag
#add wave -bin UUT/m2_unit/m3_unit/BEEF_flag
#add wave -uns UUT/m2_unit/m3_unit/SRAM_base_address
#add wave -uns UUT/m2_unit/m3_unit/SRAM_new_base_address
#add wave -uns UUT/m2_unit/m3_unit/SRAM_address_offset



add wave UUT/m2_unit/Fetch_Sp/fetch_sp
#add wave -bin UUT/m2_unit/is_M3_finish
#add wave -bin UUT/m2_unit/Fetch_Sp/finish
#add wave -bin UUT/m2_unit/Fetch_Sp/M3_finish
add wave -bin UUT/m2_unit/Fetch_Sp/counter
add wave -uns UUT/m2_unit/Fetch_Sp/DP_RAM_address_X_a
add wave -uns UUT/m2_unit/Fetch_Sp/DP_RAM_address_X_b

add wave -bin UUT/m2_unit/Fetch_Sp/DP_RAM_we_X_a
add wave -uns UUT/m2_unit/Fetch_Sp/DP_RAM_address_Sp_a
add wave -hex UUT/m2_unit/Fetch_Sp/DP_RAM_write_data_Sp_a
add wave -bin UUT/m2_unit/Fetch_Sp/DP_RAM_we_Sp_a
#add wave -uns UUT/m2_unit/Fetch_Sp/DP_RAM_address
#add wave -bin UUT/m2_unit/Fetch_Sp/DP_RAM_we
#add wave -hex UUT/m2_unit/Fetch_Sp/DP_RAM_write_data


add wave UUT/m2_unit/Compute_S/compute_S_state
#add wave -bin UUT/m2_unit/Compute_S/start
#add wave -bin UUT/m2_unit/Compute_S/finish
#add wave -uns UUT/m2_unit/Compute_S/test_counter
#add wave -bin UUT/m2_unit/Compute_S/is_first_time
#add wave -dec UUT/m2_unit/Compute_S/row_counter
#add wave -dec UUT/m2_unit/Compute_S/block_counter
#add wave -dec UUT/m2_unit/Compute_S/address_s_b_counter
#add wave -dec UUT/m2_unit/Compute_S/s_b_offset
#add wave -uns UUT/m2_unit/Compute_S/Address_C_a
#add wave -dec UUT/m2_unit/Compute_S/Data_out_C_a
#add wave -uns UUT/m2_unit/Compute_S/Address_C_b
#add wave -dec UUT/m2_unit/Compute_S/Data_out_C_b
#add wave -uns UUT/m2_unit/Compute_S/Address_Sp_b
#add wave -dec UUT/m2_unit/Compute_S/Data_out_Sp_b
#add wave -uns UUT/m2_unit/Compute_S/Address_S_a
#add wave -hex UUT/m2_unit/Compute_S/Data_out_S_a
#add wave -uns UUT/m2_unit/Compute_S/Address_S_b
#add wave -bin UUT/m2_unit/Compute_S/Write_en_S_b
#add wave -dec UUT/m2_unit/Compute_S/Data_in_S_b
#add wave -dec UUT/m2_unit/Compute_S/Mult1_result
#add wave -dec UUT/m2_unit/Compute_S/Mult2_result
#add wave -dec UUT/m2_unit/Compute_S/Mult3_result
#add wave -dec UUT/m2_unit/Compute_S/S0
#add wave -dec UUT/m2_unit/Compute_S/S1
#add wave -dec UUT/m2_unit/Compute_S/S2







