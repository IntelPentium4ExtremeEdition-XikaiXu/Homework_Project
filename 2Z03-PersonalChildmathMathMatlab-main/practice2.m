maxval = -inf; %pos infintiy 
for x = -2:0.1:2
    for y = -2:0.1:2
        val = x*y*sin(2*x-y);
        if val > maxval
            maxval = val;
            xmin = x;
            ymin = y;
        end
    end
end

xmin;
ymin;


