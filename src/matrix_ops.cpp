/**
 * @file matrix_ops.cpp
 */

#include <matrix_ops.hpp>

/**
 * Computes the Frobenius norm of a Sparse
 * @param matrix The matrix to compute the norm of
 * @return the Frobenius norm
 * @note Use the Eigen norm() method instead
 */
Types::Real frobenius_norm(const Types::Sparse &matrix) {
    return std::sqrt(matrix.cwiseAbs2().sum());
}

/**
 * Computes a vector v from a matrix A such that \f($v_{i}=\sum_{j=0}^{m-1}{A_{ij}}\forall i\in\{0,\dots,n-1\}$\f)
 * @param matrix The matrix to compute the vector from
 * @return a vector as per description
 */
Types::Vector row_sums(const Types::Sparse &matrix) {
    return matrix * Types::Vector::Ones(matrix.rows());
}

/**
 * Generate a diagonal sparse matrix D from a vector such that \f($D_{ii}=v_{i}\forall i\in\{0,\dots,n-1\}$\f)
 * @param vector The vector to compute the diagonal matrix from
 * @return a diagonal matrix as per description
 */
Types::Sparse make_diag_matrix(const Types::Vector &vector) {
    Types::Sparse matrix(vector.size(), vector.size());
    matrix.setIdentity();
    matrix.diagonal() = vector;
    return matrix;
}

/**
 * Compute the Laplacian of a matrix
 * @param matrix The matrix to compute the Laplacian of
 * @return The Laplacian matrix
 */
Types::Sparse make_laplacian(const Types::Sparse &matrix) {
    return make_diag_matrix(row_sums(matrix)) - matrix;
}

/**
 * Check if a sparse matrix is symmetric
 * @param matrix The matrix to check the symmetry of
 * @return true if the marix is symmetric, false otherwise
 */
bool is_symmetric(const Types::Sparse &matrix) {
    return (static_cast<Types::Sparse>(matrix.transpose()) - matrix).norm() == 0.0;
}

/**
 * Check if a matrix is Positive Definite given an Eigen VectorXd containing the eigenvalues
 * @param eigenvals the eigenvalues to parse
 * @return true if all eigenvalues are strictly positive
 * @note if an eigenvalue is within Constants::eps distance from 0 it is considered to be 0
 */
bool is_positive_definite(const Types::Vector &eigenvals) {
    for (auto eigenval : eigenvals) {
        if ( (eigenval < -Constants::eps) || (std::abs(eigenval) <= Constants::eps) ){
            return false;
        }
    }
    return true;
}

/**
 * Check if a matrix is Positive Semi Definite given an Eigen VectorXd containing the eigenvalues
 * @param eigenvals the eigenvalues to parse
 * @return true if all eigenvalues are greater or equal to 0
 * @note if an eigenvalue is within Constants::eps distance from 0 it is considered to be 0
 */
bool is_semi_positive_definite(const Types::Vector &eigenvals) {
    for (auto eigenval : eigenvals) {
        if (! (eigenval >= -Constants::eps)) {
            return false;
        }
    }
    return true;
}