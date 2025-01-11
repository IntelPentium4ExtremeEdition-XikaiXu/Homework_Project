x1 = [ 1, 1, 1, 0, 0];
v1 = [ 1, 1, 1, 1, 0];
y1 = conv(x1, v1); 

x2 = [ 2, 1, 0, 0, 0];
v2 = [ 1, 1, 1, 1, 0];
y2 = conv(x2, v2); 

x3 = [ 2, 1, 0, 0, 0];
v3 = [ 0, 1, 2, 0, 0];
y3 = conv(x3, v3); 

figure;

subplot(3, 3, 1)
stem(0: length(x1) - 1, x1, 'filled');
title("Causal Signal x1[n] 400440917 xuxikai");
xlabel('n');
ylabel('x1[n]');

subplot(3, 3, 2)
stem(0: length(v1) - 1, v1, 'filled');
title("Causal Signal v1[n] 400440917 xuxikai");
xlabel('n');
ylabel('v1[n]');

subplot(3, 3, 3)
stem(0: length(x1) + length(v1) - 2, y1, 'filled');
title("Causal Signal x1[n]*v1[n] 400440917 xuxikai");
xlabel('n');
ylabel('x1[n]*v1[n]');

subplot(3, 3, 4)
stem(0: length(x2) - 1, x2, 'filled');
title("Causal Signal x2[n] 400440917 xuxikai");
xlabel('n');
ylabel('x2[n]');

subplot(3, 3, 5)
stem(0: length(v2) - 1, v2, 'filled');
title("Causal Signal v2[n] 400440917 xuxikai");
xlabel('n');
ylabel('v2[n]');

subplot(3, 3, 6)
stem(0: length(x2) + length(v2) - 2, y2, 'filled');
title("Causal Signal x2[n]*v2[n] 400440917 xuxikai");
xlabel('n');
ylabel('x2[n]*v2[n]');

subplot(3, 3, 7)
stem(0: length(x3) - 1, x3, 'filled');
title("Causal Signal x3[n] 400440917 xuxikai");
xlabel('n');
ylabel('x3[n]');

subplot(3, 3, 8)
stem(0: length(v3) - 1, v3, 'filled');
title("Causal Signal v3[n] 400440917 xuxikai");
xlabel('n');
ylabel('v3[n]');

subplot(3, 3, 9)
stem(0: length(x3) + length(v3) - 2, y3, 'filled');
title("Causal Signal x3[n]*v3[n] 400440917 xuxikai");
xlabel('n');
ylabel('x3[n]*v3[n]');
