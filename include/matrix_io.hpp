#ifndef CHALLENGE2_MATRIX_IO_HPP
#define CHALLENGE2_MATRIX_IO_HPP

#include "types.hpp"

#include <unsupported/Eigen/SparseExtra>

namespace MtxIO {
    bool load_matrix(const std::string &filename,Types::Sparse &matrix);
    bool load_vector(const std::string &filename,Types::Vector &matrix);
};

namespace LisIO {
    bool load_matrix(const std::string &filename,Types::Sparse &matrix);
}

#endif //CHALLENGE2_MATRIX_IO_HPP