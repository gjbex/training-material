#ifndef _TREE_2K_ERR_HDR_
#define _TREE_2K_ERR_HDR_

extern const int TRUE;
extern const int FALSE;

typedef enum tree_2k_err {
    /*! \brief Indicates succesful operation */
    TREE_2K_SUCCESS = 0,
    /*! \brief Coordinates are not in tree's extent, so point can not be
               stored */
    TREE_2K_COORDS_NOT_IN_EXTENT_ERR = 1,
    /*! \brief Tree rank error */
    TREE_2K_INVALID_RANK_ERR = 2,
    /*! \brief Center should be initialized for tree_2k constructor call */
    TREE_2K_CENTER_IS_NULL_ERR = 3,
    /*! \brief Extent should be initialized for tree_2k constructor call */
    TREE_2K_EXTENT_IS_NULL_ERR = 4,
    /*! \brief Extent should have all strictly positive values */
    TREE_2K_INVALID_EXTENT_ERR = 5,
    /*! \brief Maximum number of points in tree should be strictly
                positive */
    TREE_2K_INVALID_MAX_POINT_ERR = 6,
    /*! \brief Bucket size for nodes in tree should be strictly positive */
    TREE_2K_INVALID_BUCKET_SIZE_ERR = 7,
    /*! \brief Memory allocation failure */
    TREE_2K_OUT_OF_MEMORY_ERR = 8,
    /*! \brief Maximum number of points in tree reached */
    TREE_2K_CAPACITY_EXCEEDED_ERR = 9,
    /*! \brief User defined function didn't return normally */
    TREE_2K_UDF_FAIL_ERR = 10
} tree_2k_err_t;

extern const char *tree_2k_err_msg[];

#define TREE_2K_ERR_FMT  "%s:%s:%d error: %s"
#define TREE_2K_UDF_ERR_FMT  "%s:%s:%d error: %s: %d"

#endif
