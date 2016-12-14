if (!is.loaded('mpi_initialize')) {
    library(Rmpi)
}

# spawn slaves
nr_slaves <- mpi.universe.size() - 1
mpi.spawn.Rslaves(nslaves=nr_slaves)

# .Last <- function() {
#     if (is.loaded('mpi_initialize')) {
#         if (mpi.comm.size(1) > 0) {
#             mpi.close.Rslaves()
#         }
#         .Call('mpi_finalize')
#     }
# }

computation <- function(n) {
    return(sum(seq(to=n)))
}

# get messages from slaves
msgs <- mpi.remote.exec(
    paste(mpi.comm.rank(), 'of', mpi.comm.size(), 'on',
          Sys.info()['nodename'])
)
print(paste(msgs, sep='\n'))

# send function to slaves
mpi.bcast.Robj2slave(computation)
mpi.remote.exec(computation(mpi.comm.rank()))

# stop the slaves
mpi.close.Rslaves()
mpi.exit()
