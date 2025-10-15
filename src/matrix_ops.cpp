#include <matrix_ops.hpp>

Types::Real frobenius_norm(const Types::Sparse &matrix) {
    return std::sqrt(matrix.cwiseSquare().sum());
}

Types::Vector row_sums(const Types::Sparse &matrix) {
    return matrix * Types::Vector::Ones(matrix.rows());
}

Types::Sparse make_diag_matrix(const Types::Vector &vector) {
    Types::Sparse matrix(vector.size(), vector.size());
    matrix.setIdentity();
    matrix.diagonal() = vector;
    return matrix;
}

Types::Sparse make_laplacian(const Types::Sparse &matrix) {
    return make_diag_matrix(row_sums(matrix)) - matrix;
}

bool is_symmetric(const Types::Sparse &matrix) {
    return (static_cast<Types::Sparse>(matrix.transpose()) - matrix).norm() == 0.0;
}

bool is_positive_definite(const Types::Vector &eigenvals) {
    for (auto eigenval : eigenvals) {
        if ( (eigenval < -Constants::eps) || (std::abs(eigenval) <= Constants::eps) ){
            return false;
        }
    }
    return true;
}
bool is_semi_positive_definite(const Types::Vector &eigenvals) {
    for (auto eigenval : eigenvals) {
        if (! (eigenval >= -Constants::eps)) {
            return false;
        }
    }
    return true;
}