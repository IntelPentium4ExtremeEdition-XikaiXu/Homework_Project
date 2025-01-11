if {[file exists $rtl/RAM_init_C.ver]} {
	file delete $rtl/RAM_init_C.ver
}
if {[file exists $rtl/RAM_init_S.ver]} {
	file delete $rtl/RAM_init_S.ver
}

mem save -o C.mem -f mti -data hex -addr decimal -startaddress 0 -endaddress 127 -wordsperline 8 /TB/UUT/m2_unit/RAM_inst0/altsyncram_component/m_default/altsyncram_inst/mem_data 
mem save -o Sp.mem -f mti -data hex -addr decimal -startaddress 0 -endaddress 127 -wordsperline 8 /TB/UUT/m2_unit/RAM_inst1/altsyncram_component/m_default/altsyncram_inst/mem_data 
mem save -o S.mem -f mti -data hex -addr decimal -startaddress 0 -endaddress 127 -wordsperline 8 /TB/UUT/m2_unit/RAM_inst2/altsyncram_component/m_default/altsyncram_inst/mem_data 
mem save -o SRAM.mem -f mti -data hex -addr decimal -startaddress 0 -endaddress 262143 -wordsperline 8 /TB/SRAM_component/SRAM_data

mem save -o additional.mem -f mti -data hex -addr decimal -startaddress 0 -endaddress 127 -wordsperline 8 /TB/UUT/m2_unit/RAM_inst3/altsyncram_component/m_default/altsyncram_inst/mem_data 
