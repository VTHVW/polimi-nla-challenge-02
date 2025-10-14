#include <matrix_ops.hpp>

Types::Real frobenius_norm(const Types::Sparse &matrix) {
    return std::sqrt(matrix.cwiseSquare().sum());
}
