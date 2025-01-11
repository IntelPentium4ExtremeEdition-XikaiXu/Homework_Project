%[x y] = meshgrid(1:0.5:2, 0:1:2);

quiver(0,1,1,2) %(startx , starty, displacement x, displacementy)
hold on
quiver(1,3,1,1/2)
hold off 

[x y] = meshgrid(-3:0.2:3, -3:0.2:3);
a = ones(size(x));
b = x.^2 + y.^2 - 1; %eazy to make mistake 

