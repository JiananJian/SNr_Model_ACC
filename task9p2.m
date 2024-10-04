
%% pdf
figure(2); clf; hold on;

load('GPe_zero.mat');
h = bar(edges, mean(c, 2) * 1e3 / 0.5, 'hist'); 
h.FaceColor = '#0072BD'; h.EdgeColor = 'none'; h.FaceAlpha = .5;
         
load('Str_zero.mat');
h = bar(edges, mean(c, 2) * 1e3 / 0.5, 'hist'); 
h.FaceColor = '#D95319'; h.EdgeColor = 'none'; h.FaceAlpha = .5;

ax = gca(); ax.FontSize = 15;
xlabel('time (ms)'); ylabel('pdf (1/sec)');
legend('GPe', 'D1');

%% cdf
figure(2); clf; hold on;

load('GPe_zero.mat');
h = bar(edges, cumsum(mean(c, 2)), 'hist'); 
h.FaceColor = '#0072BD'; h.EdgeColor = 'none'; h.FaceAlpha = .5;
         
load('Str_zero.mat');
h = bar(edges, cumsum(mean(c, 2)), 'hist'); 
h.FaceColor = '#D95319'; h.EdgeColor = 'none'; h.FaceAlpha = .5;

ax = gca(); ax.FontSize = 15;
xlabel('time (ms)'); ylabel('cdf');
legend('GPe', 'D1');

%% pdf
figure(2); clf; hold on;

load('GPe_som.mat');
h = bar(edges, mean(c, 2) * 1e3 / 0.5, 'hist'); 
h.FaceColor = '#0072BD'; h.EdgeColor = 'none'; h.FaceAlpha = .5;
         
load('GPe_den.mat');
h = bar(edges, mean(c, 2) * 1e3 / 0.5, 'hist'); 
h.FaceColor = '#D95319'; h.EdgeColor = 'none'; h.FaceAlpha = .5;

ax = gca(); ax.FontSize = 15;
xlabel('time (ms)'); ylabel('pdf (1/sec)');
legend('som', 'den');