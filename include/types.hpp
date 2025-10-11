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
}

#endif //CHALLENGE02_TYPES_AND_DEFS_HPP