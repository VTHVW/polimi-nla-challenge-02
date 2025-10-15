#ifndef CHALLENGE02_TYPES_AND_DEFS_HPP
#define CHALLENGE02_TYPES_AND_DEFS_HPP


#include <Eigen/Sparse>
#include <Eigen/Dense>

namespace Types {
    using Real = double;
    using Index = Eigen::Index;
    using Sparse = Eigen::SparseMatrix<Real, Eigen::RowMajor>;
    using Full = Eigen::MatrixXd;
    using Vector = Eigen::VectorXd;
    using EigenPair = std::pair<Vector, Real>;
    using OrderEigenVector = std::vector<std::pair<int, Real>>;
}

namespace Constants {

    const std::string TASK1_GRAPH_FILE = std::string("./media/matrices/task1_graph.mtx");
    const std::string SOCIAL_GRAPH_FILE = std::string("./media/matrices/social.mtx");

    const std::string SMALL_MTX_FILE = std::string("./media/matrices/test_mats/small.mtx");
    const std::string SMALL_EIGEN_VEC_FILE = std::string("./media/matrices/test_mats/small_vector_eig.mtx");
    const std::string SMALL_LIS_VEC_FILE = std::string("./media/matrices/test_mats/small_vector_lis.mtx");
}

#endif //CHALLENGE02_TYPES_AND_DEFS_HPP