maxvalue=-inf;

for x = -3:0.1:3
    for y = -3:0.1:3
        value = sin(4*x*y)/(x^2 + y^2 + 6*x - 8*y + 26);
        if value > maxvalue
            maxvalue = value;
            xmax = x;
            ymax = y;
        end
    end
end

xmax
ymax