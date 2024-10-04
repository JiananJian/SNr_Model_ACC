edges = 0.25 + (0 : 0.5 : 50 - 0.5);
figure(1); clf; hold on;
c = zeros(100, n); % n from task9_job.m 
for i = 1 : n
    data = get_data(sprintf('task9a%d_c.bin', i));
    c(:, i) = data(1 : 100) / data(101);
    % bar(c(:, i),'hist'); 
    % pause(1e-3); pause;
end
bar(edges, mean(c, 2) * 1e3 / 0.5, 'hist'); 
% save('GPe_zero', "c"); % uncomment and name the results according to the data