#include "../include/matrix_io.hpp"


bool MtxIO::load_matrix(const std::string &filename, Types::Sparse &matrix) {
    return loadMarket(matrix, filename);
}

bool MtxIO::load_vector(const std::string &filename, Types::Vector &vector) {
    return loadMarketVector(vector, filename);
}

bool MtxIO::save_matrix(const std::string &filename, const Types::Sparse &matrix) {
    return saveMarket(matrix, filename);
}

bool MtxIO::save_vector(const std::string &filename, const Types::Vector &vector) {
    return saveMarketVector(vector, filename);
}
