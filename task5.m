N = 401; n = 40e3;

g = get_data('g_HCN_den.bin');
I = get_data('task5_I.bin');
tG = get_data('task5_t_GABA.bin');
tG(tG == 0) = nan;
tG = reshape(tG, [n, N]);
t1 = get_data('task5_t_spk1.bin');
t1(t1 == -1) = nan;
t1 = reshape(t1, [n, N]);
t0 = get_data('task5_t_spk0.bin');
t0(t0 > 2e3) = nan; 
t2 = get_data('task5_t_spk2.bin');
isi = t2 - t0; 

%%
figure(3); clf; hold on; 
plot(I, 1e3./ isi);
xlabel('I (pA)'); ylabel('r (Hz)');

ind = t0 < 2e3;

figure(4); clf; hold on; 
histogram(isi(ind), 0 : 2 : 200, "Normalization", "pdf");
xlabel('isi (ms)'); ylabel('pdf (1/sec)'); xlim([0, 200]);
set(gca, 'YTickLabel', yticks * 1e3);

figure(5); clf; hold on; 
histogram(isi(ind), 0 : 2 : 200, "Normalization", "cdf");
xlabel('isi (ms)'); ylabel('cdf'); xlim([0, 200]); ylim([0, 1]);

figure(1); clf; hold on; 
for i = 1 : 10 : N
    plot(t0(i) - tG(:, i), t1(:, i) - tG(:, i), 'k'); 
end
xlim([-50, 0]); ylim([0, 50]);
xlabel('last spike pre stim (ms)');
ylabel('first spike post stim (ms)');
%%
ind = t0'<2e3 & ~isnan(tG);

figure(2); clf; hold on;
histogram(t1(ind) - tG(ind), 0 : .5 : 50, "Normalization", "pdf");
xlabel('first spike post stim (ms)'); ylabel('pdf (1/sec)'); xlim([0, 50]);
set(gca, 'YTickLabel', yticks * 1e3);

figure(6); clf; hold on;
histogram(t1(ind) - tG(ind), 0 : .5 : 50, "Normalization", "cdf");
xlabel('first spike post stim (ms)'); ylabel('cdf'); xlim([0, 50]); ylim([0, 1]);
