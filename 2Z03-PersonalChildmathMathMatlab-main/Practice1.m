N = 1000;
s = 0;

for i = 1:N % i from 1 to N 
      s = s + i^2;
end
%% for loop implment 

disp(s);

disp(sum([1:1000] .^2)); %[a:b] from a to b individual vector, .^2 operator to each 
%vector, sum is adder


if N > s
    disp(s);
    disp(1);
elseif N == s
    disp(N);
    disp(2);
else 
    disp(3);
end


%finding the minium val

minval = inf; %pick sth bigger than any other val

%for x = -2:0.1:2 %from -2 to 2, step is 0.1
 %   for y = -2:0.1:2
  %      val = x*y*sin(2*x-y);
   %     if val < minval %compair with previus value
    %        minval = val; %update the new value;
     %       xmin = x;
     %       ymin = y;
     %   end
    %end 
%end
%xmin
%ymin

%Euler's method involve the for loop to find the next val
%% problem;
%dy/dx = -2xy
%y(0) = 1;
%%
%1. setep the siz of the step size 
h = 0.1;
X = 3; %max val 
N = round(X/h); %we need to go from x = 0 to x = X in increament of h

%init val for x and y
x1 = zeros(1,N+1); %make a vector full of 0s woth size of N+1
y1 = zeros(1,N+1);

%set the init conditaiton
x1(1) = 0;
y1(1) = 1;

for i = 1:N
    x1(i+1) = x1(i) + h; % x increasing by step size h each iteration 
    y1(i+1) = y1(i) + h*(-2*x1(i)*y1(i));
end

x = 0:0.01:3;
yExact = exp(-x.^2);

plot(x1,y1,'r',x,yExact,'*b'); %red line
legend("lol","hahaha");


