#include <iostream>
#include <matrix_io.hpp>
#include <matrix_ops.hpp>
#include <string>

int main(int argc, char *argv[]) {

    Types::Sparse A_s;

    auto res = MtxIO::load_matrix(Constants::SOCIAL_GRAPH_FILE , A_s);
    if (!res) {
        std::cerr << "Error loading A_s matrix" << std::endl;
        return 1;
    }

    std::vector<Types::EigenPair> eigenpairs;
    LisIO::load_eigenpairs(Constants::SOCIAL_EVEC_FILE,Constants::SOCIAL_EVAL_FILE, eigenpairs);

    Types::EigenPair &eigenpair = eigenpairs[1];
    Types::Vector &eigenvector = eigenpair.first;

    // std::cout << "second smallest eigen vector: " << eigenvector.transpose() << std::endl;

    Types::Index n_p(0),n_n(0);
    for (auto value : eigenvector) {
        value > 0 ? n_p++ : n_n++;
    }

    std::cout << "Number of positive entries in the second smallest eigenvector: " << n_p << std::endl;
    std::cout << "Number of negative entries in the second smallest eigenvector: " << n_n << std::endl;

    Types::Sparse P = compute_permutation_matrix(order_eigenvector(eigenvector));

    Types::Sparse A_ord = P*A_s*P.transpose();
    Types::Sparse A_ord_block = A_ord.topRightCorner(n_p,n_p);
    A_ord_block.prune(0.0);
    Types::Sparse A_s_block = A_s.topRightCorner(n_p,n_p);
    A_s_block.prune(0.0);
    std::cout << "nnz(A_ord_block) := " << A_ord_block.nonZeros() << std::endl;
    std::cout << "nnz(A_s_block) := " <<  A_s_block.nonZeros() << std::endl;

    // std::cout <<  A_ord_block << std::endl;

    return 0;
}
