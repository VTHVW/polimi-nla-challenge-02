#ifndef CHALLENGE02_TYPES_AND_DEFS_HPP
#define CHALLENGE02_TYPES_AND_DEFS_HPP


#include <Eigen/Sparse>
#include <Eigen/Dense>

/**
 * Contains types used within this library
 */
namespace Types {
    using Real = double;
    using Index = Eigen::Index;
    using Sparse = Eigen::SparseMatrix<Real, Eigen::RowMajor>;
    using Full = Eigen::MatrixXd;
    using Vector = Eigen::VectorXd;
    using EigenPair = std::pair<Vector, Real>;
    /**
     * A vector to be ordered, such that if element i is (j, value) then value was moved form position j to i
     * @namespace Types
     */
    using OrderEigenVector = std::vector<std::pair<Index, Real>>;
}

inline std::ostream& operator<<(std::ostream &os, Types::OrderEigenVector &oev) {
    for (auto j=0; j<oev.size(); ++j)
        os << "( " << oev[j].first << " , " << j << " ): " << oev[j].second << "\n";
    return os;
}

/**
 * Contains constants used within this library
 */
namespace Constants {

    const std::string TASK1_GRAPH_FILE = std::string("./media/matrices/task1_graph.mtx");
    const std::string SOCIAL_GRAPH_FILE = std::string("./media/matrices/social.mtx");
    const std::string SOCIAL_LAPLACIAN_GRAPH_FILE = std::string("./media/matrices/social_laplacian.mtx");
    const std::string SOCIAL_EVEC_FILE = std::string("./media/lisres/task3_evecs_second_smallest.mtx");
    const std::string SOCIAL_EVAL_FILE = std::string("./media/lisres/task3_evals_second_smallest.mtx");


    const std::string SMALL_MTX_FILE = std::string("./media/matrices/test_mats/small.mtx");
    const std::string SMALL_EIGEN_VEC_FILE = std::string("./media/matrices/test_mats/small_vector_eig.mtx");
    const std::string SMALL_LIS_VEC_FILE = std::string("./media/matrices/test_mats/small_vector_lis.mtx");

    constexpr Types::Real eps = 1.0e-15;
}

#endif //CHALLENGE02_TYPES_AND_DEFS_HPP