#include "../include/matrix_io.hpp"

bool MtxIO::load_matrix(const std::string &filename, Ch2Traits::Sparse &matrix) {
    return loadMarket( matrix,filename);
}