function write_data(file, data)
    % filename = mfilename('fullpath');
    % filepath = fileparts(filename);
    filepath = 'C:\Users\leojn\OneDrive - University of Pittsburgh\Rubin\C implementation';
    filename = fullfile(filepath, file);
    fileID = fopen(filename, 'wb');
    if fileID == -1
        error('Error opening file');
    end
    
    % Read data from file
    count = fwrite(fileID, data, 'double');
    if (count ~= numel(data))
        error('Error writing data to file or data is empty');
    end
    
    % Close the file
    fclose(fileID);
    
    % Display the read data
    disp("Data successfully written to " + file);
end