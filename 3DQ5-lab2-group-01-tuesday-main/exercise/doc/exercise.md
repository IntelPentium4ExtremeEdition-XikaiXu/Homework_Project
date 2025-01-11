
### Exercise

In the reference design from **experiment 5**, only the lower memory half (i.e., address range 000h-0FFh) is used for storing the LCD codes of lower-case characters. First, extend the “MIF” file with the LCD codes such that the upper memory half (i.e., address range 100h-1FFh) stores the LCD codes for upper-case characters. Using a single-bit flag (stored in a 1-bit register), you can keep track of the mode, i.e., lower-case or upper-case: the left-shift key on the PS/2 keyboard sets the mode to upper-case and the right-shift key resets it to lower-case. For the sake of simplicity, it is assumed that the mode affects only the letter keys, i.e., ‘a’ to ‘z’. The number keys '0' to '9' are not affected by the upper/lower-case mode, i.e., the numbers will be displayed in the same way regardless of the upper/lower-case mode. Note, when the left-shift key or the right-shift key is pressed, __nothing__ should be displayed on the character LCD (i.e., they are used only for setting the upper/lower-case modes). Note also, if the left-shift and right-shift keys are pressed more than once in between typing two alphabet character keys, then only the effect of the last shift key that was typed is considered.

Only after sixteen keys have been typed, the entire top line will be displayed at once (using a shift register structure, as for the in-lab **experiment 5**). After the top line is displayed, if character `9` (nine) appears in the string that has been displayed, then the two rightmost seven-segment displays will show (in BCD format) the *most* significant position where character `9` appears. For example, if the displayed string is `AbcDefghIJklMno9`, then the rightmost significant seven-segment display will show `0` because the most significant position where `9` appears in the string is `0` (if the position can be represented on a single BCD digit then the seven-segment display to the left of the rightmost seven-segment display can show either `0` or not be lightened); if the displayed string is `A9cDefgh9JklMno9`, then the rightmost significant seven-segment display will show `4`, and the seven-segment display to its left will show `1` because the most significant position where `9` appears in the string is `14`; if character `9` does not appear in the string displayed on the top line then two rightmost seven-segment displays will not be lightened.

After the top line is displayed, as explained above, two rightmost seven-segment displays will show the most significant position where the character `9` appears in the top line until a key has been pressed, at which point the two rightmost seven-segment displays will be lightened off, and the bottom line is processed, based on the same principles as for the top line. Note, like for the top line, all sixteen characters from the bottom line are displayed at once; however, unlike for the top line, after the bottom line is displayed, if character `0` (zero) appears in the string that has been displayed, then the two rightmost seven-segment displays will show (in BCD format) the *least* significant position where character `0` appears. The state of these two rightmost seven-segment displays (that display the least significant position where the character `0` appears in the bottom line) will not change until a key has been pressed, at which point the two rightmost seven-segment displays will be lightened off, and the top line is processed, as described in the previous paragraph; this behaviour that transitions between the top and bottom lines continues until the circuit is powered off. It is also important to note that only the behaviour of the two rightmost seven-segment displays has been specified; therefore, you can use the remaining seven-segment displays and LEDs for debugging purposes, as per your preferences.

As a final point, you should also note that while a full line of 16 characters gets sent to the LCD controller, it will take just below 15 microseconds (us) in simulation. Hence, ensure the next key press in `board_events.txt` will be done after these 15 us have elapsed (this concerns simulation only if you choose to use it).

Submit your sources, and in your report, write approximately half a page (but not more than a full page) that describes your reasoning. Your sources should follow the directory structure from the in-lab experiments (already set up for you in the `exercise` folder); note that your report (in `.pdf`, `.txt` or `.md` format) should be included in the `exercise/doc` sub-folder.

Your submission is due 16 hours before your next lab session. Late submissions will be penalized.