#include <iostream>
#include <matrix_io.hpp>
#include <matrix_ops.hpp>
#include <string>

int main(int argc, char *argv[]) {
    Types::Sparse A_s;

    auto res = MtxIO::load_matrix(Constants::SOCIAL_GRAPH_FILE , A_s);
    if (!res) {
        std::cerr << "Error loading matrix" << std::endl;
        return 1;
    }

    std::cout << "||A_s||_F := " << frobenius_norm(A_s) << std::endl;

    Types::Sparse L_s = make_laplacian(A_s);

    std::cout << "is L_s symmetric? " << (is_symmetric(L_s) ? "yes" : "no") << std::endl;
    std::cout << "number of non-zeros in L_s: " << L_s.nonZeros() << std::endl;

    L_s.coeffRef(0,0) += 0.2d;

    LisIO::save_matrix(Constants::SOCIAL_LAPLACIAN_GRAPH_FILE, L_s);

    Eigen::SelfAdjointEigenSolver<Types::Sparse> eigensolver(L_s);
    if (eigensolver.info() != Eigen::Success) {
        std::cerr << "Error computing eigenvalues" << std::endl;
        return 1;
    }
    auto eval = eigensolver.eigenvalues();
    auto evec = eigensolver.eigenvectors();

    std::cout << eval.minCoeff() << std::endl;
    std::cout << eval.maxCoeff() << std::endl;
    std::cout << eval << std::endl;

    return 0;
}
