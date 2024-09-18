%% load data
g = get_data('task4_g.bin');
I = get_data('task4_I.bin');
r0 = get_data('task4_r0.bin');
figure(1); clf; hold on; plot(I, r0);
xlabel('I_{app} (pA)'); ylabel('FR (Hz)');

m = length(g);
n = length(I);

%% somatic HCN
r1 = get_data('task4_r1.bin');
r1 = reshape(r1, [n, m]);

figure(2); clf; hold on;
h = surf([0; g], I, [r0, r1]);
h.EdgeColor = 'none';
colorbar;
xlim([0, 32]);
xlabel('g_{HCN} (nS/pF)');
ylabel('I_{app} (pA)');
title('rate (Hz)');
tar = r0 / .68;
[~, i] = min(abs(tar - r1), [], 2);
plot3(g(i), I, tar, 'k');
title('HCN som'); clim([0 60]);

write_data("g_HCN_som.bin", g(i));  % estimated somatic gHCN 

r = zeros(n, 1);
for j = 1 : n
    r(j) = r1(j, i(j));
end
plot3(g(i), I, r, 'k');

%% dendritic HCN
r2 = get_data('task4_r2.bin');
r2 = reshape(r2, [n, m]);

figure(3); clf; hold on;
h = surf([0; g], I, [r0, r2]);
h.EdgeColor = 'none';
colorbar;
xlim([0, 32]);
xlabel('g_{HCN} (nS/pF)');
ylabel('I_{app} (pA)');
title('rate (Hz)');
tar = r0 / .68;
[~, i] = min(abs(tar - r2), [], 2);
plot3(g(i), I, tar,'k');
title('HCN den'); clim([0 60]);

write_data("g_HCN_den.bin", g(i));  % estimated dendritic gHCN 

r = zeros(n, 1);
for j = 1 : n
    r(j) = r2(j, i(j));
end
plot3(g(i), I, r, 'k');

%% blocked HCN
write_data("g_HCN_zero.bin", 0 * g(i));   