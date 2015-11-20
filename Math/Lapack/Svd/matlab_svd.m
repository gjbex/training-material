function rel_err = matlab_svd(file_name, dataset_name)
    tic
    orig_matrix = h5read(file_name, dataset_name);
    toc
    tic
    [U, Sigma, V] = svd(orig_matrix);
    toc
    tic
    matrix = U*Sigma*V';
    toc
    rel_err = sum(sum(abs(matrix - orig_matrix)./abs(orig_matrix)));
    rel_err = rel_err/(size(orig_matrix, 1)*size(orig_matrix, 2));
    if isdeployed
        disp(sprintf('%.4e', rel_err))
    end
end
