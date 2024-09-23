function data = get_data(file)
    % filename = mfilename('fullpath');
    % filepath = fileparts(filename);
    filepath = 'C:\Users\leojn\OneDrive - University of Pittsburgh\Rubin\C implementation';
    filename = fullfile(filepath, file);
    fileID = fopen(filename, 'rb');
    if fileID == -1
        error('Error opening file');
    end
    
    % Read data from file
    data = fread(fileID, 'double');
    if isempty(data)
        error('Error reading data from file or file is empty');
    end
    
    % Close the file
    fclose(fileID);
    
    % Display the read data
    disp('Data successfully read from data.bin');
end