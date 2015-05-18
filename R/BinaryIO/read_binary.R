#!/usr/bin/env Rscript

args <- commandArgs(TRUE)
file_name <- args[1]
file_pos <- as.integer(args[2])
line_length <- as.integer(args[3])

conn <- file(file_name, 'rb')
current.pos <- seek(conn, where = file_pos, origin = 'start')
data <- readBin(conn, 'raw', n = line_length)
s <- paste(sapply(data, rawToChar), collapse='')
cat(paste('|', s, '|', sep=''), sep='')
