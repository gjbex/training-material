/*!
  \file
  \brief Error return code and messages for tree_2k librairy
*/

/*! \brief Value representing true. */
const int TRUE = 1;
/*! \brief Value representing false. */
const int FALSE = 0;

/*! \brief Indicates succesful operation */
const int TREE_2K_SUCCESS = 0;
/*! \brief Coordinates are not in tree's extent, so point can not be stored */
const int TREE_2K_COORDS_NOT_IN_EXTENT_ERR = 1;
/*! \brief Tree rank error */
const int TREE_2K_INVALID_RANK_ERR = 2;
/*! \brief Center should be initialized for tree_2k constructor call */
const int TREE_2K_CENTER_IS_NULL_ERR = 3;
/*! \brief Extent should be initialized for tree_2k constructor call */
const int TREE_2K_EXTENT_IS_NULL_ERR = 4;
/*! \brief Extent should have all strictly positive values */
const int TREE_2K_INVALID_EXTENT_ERR = 5;
/*! \brief Maximum number of points in tree should be strictly positive */
const int TREE_2K_INVALID_MAX_POINT_ERR = 6;
/*! \brief Bucket size for nodes in tree should be strictly positive */
const int TREE_2K_INVALID_BUCKET_SIZE_ERR = 7;
/*! \brief Memory allocation failure */
const int TREE_2K_OUT_OF_MEMORY_ERR = 8;
/*! \brief Maximum number of points in tree reached */
const int TREE_2K_CAPACITY_EXCEEDED_ERR = 9;

/*! \brief Number of error messages defined for tree_2k */
#define TREE_2K_NR_ERROR_MSGS 10

/*! \brief Array containing tree_2k's error messages */
const char *err_msg[TREE_2K_NR_ERROR_MSGS] = {
    "succesful operation",
    "coordinates exceed tree's extent",
    "tree rank should be strictly positive",
    "center should be initialized",
    "extent should be initialized",
    "extent has negative components",
    "maximum number of points is negative",
    "bucket size is negative",
    "can not allocate memory",
    "maximum number of points in tree reached"
};
