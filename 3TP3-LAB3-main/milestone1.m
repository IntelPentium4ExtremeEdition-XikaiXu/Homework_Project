
% Do a plot of a sampled sinusoid with frequency f = 100 Hz

f = 100;
%
% Sampling frequency and interval
fs = 8000;
Ts = 1/fs;
%
% Set time duration of plot, i.e., 10 msec.
tfinalplot = 10e-3;
%
% Make the time vector for the plot
nplot=0:Ts:tfinalplot;
%
% Sample the sinusoid.
xnT = sin(2*pi*f*nplot);
%
% Make the plot
stem(nplot, xnT);
% Reconstructed analog plot using straight lines

% Uncomment/edit this next line to save the graph.
exportgraphics(gcf, 'milestone1.jpg');
