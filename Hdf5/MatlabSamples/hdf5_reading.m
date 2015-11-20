function matrix_sum = hdf5_reading(filename, datasetname)
    data = h5read(filename, datasetname)
    [rows, cols] = size(data);
    if isdeployed
        disp(sprintf('%d x %d matrix', rows, cols))
        disp(data)
    end
    matrix_sum = sum(sum(data));
    if isdeployed
        disp(sprintf('%20.15e', matrix_sum))
    end
end
