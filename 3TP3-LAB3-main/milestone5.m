f1 = 100;     
mu = 2000;    
fs = 32000;   
tmax = 8;      
phi = 0;       

t = 0:1/fs:tmax;

c = cos(pi * mu * t.^2 + 2 * pi * f1 * t + phi); 

figure;
plot(t(1:2000), c(1:2000));
title('200 SAMPLE XUXIKAI');
xlabel('Time (s)');
ylabel('Amplitude');
saveas(gcf, 'milestone5s.jpg');
audiowrite('32kHz.wav', c, fs);

sound(c, fs);
