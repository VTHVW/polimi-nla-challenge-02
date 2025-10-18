#ifndef CHALLENGE2_MATRIX_IO_HPP
#define CHALLENGE2_MATRIX_IO_HPP

#include "types.hpp"
#include <iostream>
#include <unsupported/Eigen/SparseExtra>

/**
 * Contains functions to load and store mtx files that are immediately readable with Eigen
 */
namespace MtxIO {
    bool load_matrix(const std::string &filename,Types::Sparse &matrix);
    bool load_vector(const std::string &filename,Types::Vector &vector);
    bool save_matrix(const std::string &filename,const Types::Sparse &matrix);
    bool save_vector(const std::string &filename,const Types::Vector &vector);
};

/**
 * Contains functions to load and store mtx files that are immediately readable with LIS
 */
namespace LisIO {
    bool load_matrix(const std::string &filename,Types::Sparse &matrix);
    bool load_vector(const std::string &filename,Types::Vector &vector);
    bool load_eigenpairs(const std::string &evec_filename,const std::string &eval_filename,std::vector<Types::EigenPair> &eigenpairs);
    bool save_matrix(const std::string &filename,const Types::Sparse &matrix);
    bool save_vector(const std::string &filename,const Types::Vector &vector);
}

#endif //CHALLENGE2_MATRIX_IO_HPP