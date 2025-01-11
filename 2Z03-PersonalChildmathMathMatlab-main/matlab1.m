%xikai xu 400440917 xu503










% Let ' s define x from -3 to 3 with 0.05 spacing between each element
x = -3:0.05:3;
% Now we can calculate our y values using the .^ operator
y1 = x .^2;
y2 = x .^3;
% Let ' s try and plot x ^2 in blue with line thickness 1 , and x ^3 in red with line thickness 2.
% First , we can plot x ^2 using the plot () command , with an extra argument specifying the colour .
plot (x , y1 , 'b ') % 'b ' tells MATLAB to plot in " blue ." Default line thickness is 1 so we don ' t need to specify it .
% Now , we will need to use a command that ensures the next call to the plot () function doesn ' t erase our current function . This is achieved by the following : 
hold on
% To change the line thickness , we need to also specify a ' LineWidth ' as shown below :
plot (x , y2 , 'r' , 'LineWidth' ,2) % 'r ' for red + setting LineWidth to 2
% Now we can give it a title and do other cosmetic stuff 
title (" y = x ^ 2 and y = x ^3")

legend (" x ^2" , " x ^3")
% the order in which you pass in labels corresponds the order they were plotted in
xlim ([ -3 3]) ; ylim ([min(y2) max(y2)]) ; 
% cropping the graph to fit the curves exactly .
xlabel ('x') ; ylabel ('y') ; % labelling axes
