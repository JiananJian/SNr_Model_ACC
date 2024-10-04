tau_values;
HCN = 'zero'; 
g = g_GPe; tau = tau_GPe; s = 'GPe'; C = 800;
% g = g_D1; tau = tau_D1; s = 'Str'; C = 100;
n = length(g); 

% Open the file in write mode ('w')
fileID = fopen("run_task9v3.sh", 'w');
if fileID == -1
    error('Error opening the file.');
end

% Write data to the file
fprintf(fileID, '#!/bin/bash\n');
fprintf(fileID, 'chmod +x run_task9v2.sh\n');
for i = 1 : n
    fprintf(fileID, sprintf('./run_task9.sh -%s %f -tau %f -HCN %s -o task9a%d\n',s, g(i) / C, tau(i), HCN, i));
end

% Close the file after writing
fclose(fileID);

% Display a success message
disp('Data written to the file successfully.');



