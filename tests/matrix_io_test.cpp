#include <matrix_io.hpp>

#include <matrix_ops.hpp>

int main(int argc, char* argv[]) {
    Types::Sparse small;
    Types::Vector eig;
    Types::Vector lis;

    if (MtxIO::load_matrix(Constants::SMALL_MTX_FILE,small) == false) {
        std::cerr << "load_matrix " << Constants::SMALL_MTX_FILE << " failed" << std::endl;
        return 1;
    }

    if (small.nonZeros() != 3) {
        std::cerr << "Small.nonZeros() = " << small.nonZeros() << " != 3" << std::endl;
        return 1;
    }

    if (small.cols() != 4 || small.rows() != 4) {
        std::cerr << "Small size = " << small.rows() << "x" << small.cols() << " != 4x4" << std::endl;
        return 1;
    }

    if (small.coeffRef(0,0) != 1 || small.coeffRef(1,1) != 2 || small.coeffRef(2,3) != 7) {
        std::cerr << "Coefficients don't match:\n" << small << std::endl;
        return 1;
    }

    if (MtxIO::load_vector(Constants::SMALL_EIGEN_VEC_FILE,eig) == false) {
        std::cerr << "load_vector " << Constants::SMALL_EIGEN_VEC_FILE << " failed" << std::endl;
        return 1;
    }

    if (eig.size() != 4) {
        std::cerr << "eig size = " << eig.size() << " != 4" << std::endl;
        return 1;
    }

    if (eig(0) != 1.0e-3 || eig(1)!=2.0e-3 || eig(2)!=3.0e-3 || eig(3)!=4.0e-3) {
        std::cerr << "Coefficients don't match:\n" << eig(0) << std::endl;
        return 1;
    }

    if (LisIO::load_vector(Constants::SMALL_LIS_VEC_FILE,lis) == false) {
        std::cerr << "load_vector " << Constants::SMALL_LIS_VEC_FILE << " failed" << std::endl;
        return 1;
    }

    if (eig.size() != 4) {
        std::cerr << "lis size = " << lis.size() << " != 4" << std::endl;
        return 1;
    }

    if (lis(0) != 1.0e-3 || lis(1)!=2.0e-3 || lis(2)!=3.0e-3 || lis(3)!=4.0e-3) {
        std::cerr << "Coefficients don't match:\n" << lis << std::endl;
        return 1;
    }

    return 0;

}