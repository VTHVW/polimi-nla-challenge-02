#ifndef CHALLENGE02_TYPES_AND_DEFS_HPP
#define CHALLENGE02_TYPES_AND_DEFS_HPP


#include <Eigen/Sparse>
#include <Eigen/Dense>

namespace Types {
    using Real = double;
    using Sparse = Eigen::SparseMatrix<Real, Eigen::RowMajor>;
    using Full = Eigen::MatrixXd;
    using Vector = Eigen::VectorXd;
    using EigenPair = std::pair<Vector, Real>;
    using OrderEigenVector = std::vector<std::pair<int, Real>>;
}

namespace Constants {
    const std::string TEST_GRAPH_FILE = std::string("./media/test_graph.mtx");
}

#endif //CHALLENGE02_TYPES_AND_DEFS_HPP