frequencies = [100, 200, 400, 800];

fs = 8000;
Ts = 1 / fs;

tfinalplot = 10e-3;

figure;

for i = 1:length(frequencies)
    f = frequencies(i); 
    nplot = 0:Ts:tfinalplot;
    xnT = sin(2 * pi * f * nplot);
    subplot(2, 2, i); 
    plot(nplot * 1e3, xnT);  
    title(['f = ' num2str(f) ' Hz']);
    xlabel('t');
    ylabel('Amp');
    grid on;
end
saveas(gcf, 'milestone2s.jpg');
sound_vector = [];
tfinal = 2;  

for i = 1:length(frequencies)
    f = frequencies(i); 
    nsound = 0:Ts:tfinal; 
    xnT = sin(2 * pi * f * nsound); 
    sound_vector = [sound_vector xnT]; 
end

audiowrite('milestone2.wav', sound_vector, fs);

sound(sound_vector, fs);