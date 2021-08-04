dyn.load("myRLib.so")

mySum <- function(a) {
    n <- length(a);
    result <- .C("mySum", as.double(a), as.integer(n), s = double(1));
    result$s;
}
