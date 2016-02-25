/*!
  \file
  \brief Error return code and messages for tree_2k librairy
*/

/*! \brief Value representing true. */
const int TRUE = 1;
/*! \brief Value representing false. */
const int FALSE = 0;

/*! \brief Number of error messages defined for tree_2k */
#define TREE_2K_NR_ERROR_MSGS 11

/*! \brief Array containing tree_2k's error messages */
const char *tree_2k_err_msg[TREE_2K_NR_ERROR_MSGS] = {
    "succesful operation",
    "coordinates exceed tree's extent",
    "tree rank should be strictly positive",
    "center should be initialized",
    "extent should be initialized",
    "extent has negative components",
    "maximum number of points is negative",
    "bucket size is negative",
    "can not allocate memory",
    "maximum number of points in tree reached",
    "abnormal termination of user defined function"
};
