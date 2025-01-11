### Exercise 1

Modify the design from __experiment 3__ as follows. 

In the first and second DP-RAMs, there are two arrays (**W** and **X**, respectively) whose elements are 8-bit signed integers. Each of these arrays has 512 elements (initialized the same way as in the lab, i.e., using memory initialization files). Design the circuit that computes two arrays, **Y** and **Z**, as specified below:

- for the top half of the memory, i.e., _k_ is between 0 and 255 (inclusive), **Y**[_k_] and **Z**[_k_] are defined as follows. If **W**[_k_] is negative then **Y**[_k_] = **X**[_k_] - 1 and **Z**[_k_] = **W**[_k_] + 1; otherwise **Y**[_k_] = **W**[_k_] - 1 and **Z**[_k_] = **X**[_k_] + 1;

- for the bottom half of the memory, i.e., _k_ is between 256 and 511 (inclusive), **Y**[_k_] and **Z**[_k_] are defined as follows. If **X**[_k_] is positive (assume zero is also a positive number) then **Y**[_k_] = **W**[_k_] + **X**[_k_] and **Z**[_k_] = **W**[_k_] - **X**[_k_]; otherwise **Y**[_k_] = **X**[_k_] - **W**[_k_] and **Z**[_k_] = **X**[_k_] + **W**[_k_];

Each element **Y**[_k_] should overwrite the corresponding element **W**[_k_] in the first DP-RAM (for every _k_ from 0 to 511); likewise, each **Z**[_k_] should overwrite the **X**[_k_] in location _k_ in the second DP-RAM. As for the in-lab experiment, if the arithmetic overflow occurs as a direct consequence of the additions/subtractions, it is unnecessary to detect it, i.e., keep the 8 least significant bits of the result. The above calculations should be implemented in as few clock cycles as the two DP-RAMs can facilitate.

For this exercise only, in your report, you __MUST__ discuss your resource usage in terms of registers. You should relate your estimate to the register count from the compilation report in Quartus. You should also inspect the critical path either in the Timing Analyzer menu, as shown in the videos on circuit implementation and timing from **lab 3**, or by checking the `.sta.rpt` file from the `syn/output_files` sub-folder, which contains the same info as displayed in the Timing Analyzer menu. Based on your specific design structure, you should also provide your best possible interpretation of the critical path in your design.

œ**Note**: A multi-bit signal whose value is to be interpreted by a circuit as a signed number, as is the case for this exercise, can be tested if it is positive or negative in multiple ways, with the following two options suggested.

- check its most significant bit: if it is one, then the number is negative; otherwise, it is positive; 

- by default, a multi-bit signal declared using the **logic** type in SystemVerilog is interpreted as an unsigned number; for example, if an 8-bit signal is declared as **logic** _[7:0] my\_signal;_ and it is assigned value `8'hFF` then condition _my\_signal < 0_ would evaluate to `FALSE` because `255` is greater than `0`; however, you can use the _**\$signed**_ system function to interpret the multi-bit signal as a signed number and therefore condition _**\$signed**__(my\_signal) < 0_ would evaluate to `TRUE` because `-1` is less than `0`;

Submit your sources, and in your report, write approximately half a page (but not more than a full page) that describes your reasoning. Your sources should follow the directory structure from the in-lab experiments (already set up for you in the `exercise1` folder); note, your report (in `.pdf`, `.txt` or `.md` format) should be included in the `exercise1/doc` sub-folder. 

Your submission is due 16 hours before your next lab session. Late submissions will be penalized.
