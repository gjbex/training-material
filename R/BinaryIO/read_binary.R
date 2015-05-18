conn <- file('data.txt', 'rb')
current.pos <- seek(conn, where = 15, origin = 'start')
data <- readBin(conn, 'raw', n = 5)
s <- paste(sapply(data, rawToChar), collapse='')
s
