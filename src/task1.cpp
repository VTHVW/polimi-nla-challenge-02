#include <iostream>
#include <matrix_io.hpp>
#include <matrix_ops.hpp>
#include <string>

int main(int argc, char *argv[]) {
    Types::Sparse A_g;

    auto res = MtxIO::load_matrix(Constants::TASK1_GRAPH_FILE, A_g);
    if (!res) {
        std::cerr << "Error loading matrix" << std::endl;
        return 1;
    }
    std::cout << "A_g:\n " << A_g << std::endl;

    std::cout << "||A_g||_F := " << frobenius_norm(A_g) << std::endl;

    const Types::Vector x = Types::Vector::Ones(A_g.rows());
    const Types::Sparse L_g = make_laplacian(A_g);
    Types::Vector y = L_g*x;

    std::cout << "||y|| := " << y.norm() << std::endl;
    std::cout << "is L_g symmetric? " << (is_symmetric(L_g) ? "yes" : "no") << std::endl;

    /*
     * TODO: use eigendecomposition
     */
    // Eigen::SimplicialLDLT<Types::Sparse,Eigen::Lower|Eigen::Upper> ldlt_Lg;
    // ldlt_Lg.compute(L_g);
    Eigen::SelfAdjointEigenSolver<Types::Sparse> eigensolver(L_g);
    if (eigensolver.info() != Eigen::Success) {
        std::cerr << "Error computing eigenvalues" << std::endl;
        return 1;
    }
    auto eval = eigensolver.eigenvalues();
    auto evec = eigensolver.eigenvectors();


    std::cout << "eval (without eps) := \n" << eval.transpose() << std::endl;

    eval = eval.unaryExpr([](Types::Real eigval) -> Types::Real {
        return (std::abs(eigval) < Constants::eps ? 0.0 : eigval);
        }
    );

    std::cout << "eval := \n" << eval.transpose() << std::endl;
    std::cout << "evec := \n" << evec << std::endl;

    std::cout << "is L_g positive definite? " << (is_positive_definite(eval) ? "yes" : "no") << std::endl;
    std::cout << "is L_g semi positive definite? " << (is_semi_positive_definite(eval) ? "yes" : "no") << std::endl;

    std::cout << "max eigen value " << eval.maxCoeff() << std::endl;
    std::cout << "min eigen value " << eval.minCoeff() << std::endl;

    // printf("eps = %+.20lf\n",-Constants::eps);
    // printf("ev  = %+.20lf\n",eval(0));

    std::vector<Types::EigenPair> eigenpairs;
    eigenpairs.reserve(eval.size());

    for (int i = 0; i < eval.size(); i++) {
        eigenpairs.emplace_back(evec.col(i), eval(i));
    }

    std::sort(eigenpairs.begin(), eigenpairs.end(), [](const Types::EigenPair &a, const Types::EigenPair &b) -> bool {
        return a.second < b.second;
    });

    std::cout << "smallest strictly positive eigenvalue: " << eigenpairs[1].second << std::endl;
    std::cout << "smallest strictly positive eigenvector: " << eigenpairs[1].first.transpose() << std::endl;

    return 0;
}
