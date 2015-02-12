args <- commandArgs(TRUE)
distr_mean <- as.double(args[1])
distr_stddev <- as.double(args[2])
sample_size <- as.integer(args[3])

values <- rnorm(sample_size, mean = distr_mean, sd = distr_stddev)
sample_mean = mean(values)

cat("mean\tstddev\tsample_size\tsample_mean\n")
result <- sprintf("%.5f\t%.2f\t%d\t%.5f\n",
                  distr_mean, distr_stddev, sample_size, sample_mean)
cat(result)
