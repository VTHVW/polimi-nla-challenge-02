#ifndef CHALLENGE2_MATRIX_OPS_HPP
#define CHALLENGE2_MATRIX_OPS_HPP

#include "types.hpp"

Types::Real frobenius_norm(const Types::Sparse &matrix);
Types::Vector row_sums(const Types::Sparse &matrix);
Types::Sparse make_diag_matrix(const Types::Vector &vector);
Types::Sparse make_laplacian(const Types::Sparse &matrix);

std::vector<Types::EigenPair> compute_eigenpairs(const Types::Sparse &matrix);
bool is_symmetric(const Types::Sparse &matrix);
bool is_positive_definite(const Types::Vector &eigenvals);
bool is_semi_positive_definite(const Types::Vector &eigenvals);

Types::OrderEigenVector order_eigenvector(const Types::Vector &eigenvector);
Types::Sparse compute_permutation_matrix(const Types::OrderEigenVector &order_eigenvector);

#endif //CHALLENGE2_MATRIX_OPS_HPP