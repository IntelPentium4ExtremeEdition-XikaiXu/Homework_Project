# Constrain clock port CLOCK_50_I with a 20 ns requirement

# Constrain the register-to-register paths
create_clock -name clk_50 -period 20 [get_ports {CLOCK_50_I}]

# Use phase-locked loops (PLLs) instance parameters 
# for the generated clocks on the outputs of the PLL

derive_pll_clocks
derive_clock_uncertainty

# Constrain the input-to-register paths

set_input_delay -clock clk_50 -max 3 [all_inputs]
set_input_delay -clock clk_50 -min 2 [all_inputs]

# Constrain the output-to-register paths

set_output_delay -clock clk_50 -max 3 [all_outputs]
set_output_delay -clock clk_50 -min 2 [all_outputs]

 
