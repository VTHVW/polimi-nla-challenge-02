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

bool LisIO::load_matrix(const std::string &filename,Types::Sparse &matrix) {
    return loadMarket(matrix, filename);
}

bool LisIO::load_vector(const std::string &filename,Types::Vector &vector) {
    std::ifstream in(filename.c_str(), std::ios::in);
    if (!in) return false; // failed to open buffer

    std::string line;
    Eigen::Index rows(0); // lis only saves row number, cols(0) is useless
    do {  // Skip comments
        std::getline(in, line);
        eigen_assert(in.good());
    } while (line[0] == '%');

    std::istringstream row_line(line);
    row_line >> rows;

    bool sizes_not_positive = rows < 1;
    bool wrong_input_rows = (
            Types::Vector::MaxRowsAtCompileTime != Eigen::Dynamic &&
            rows > Types::Vector::MaxRowsAtCompileTime
        ) || (
            Types::Vector::RowsAtCompileTime != Eigen::Dynamic &&
            rows != Types::Vector::RowsAtCompileTime
        );

    if (sizes_not_positive || wrong_input_rows) {
        if (sizes_not_positive) {
            std::cerr << "non-positive row or column size in file" << filename << "\n";
        } else {
            std::cerr << "Input matrix can not be resized to" << rows << " x " << 1 << "as given in " << filename << "\n";
        }
        in.close();
        return false;
    }

    vector.resize(rows);
    Eigen::Index row = 0;
    Eigen::Index n = 0;
    Types::Real value;
    Eigen::Index index;

    while (std::getline(in, line) && (row < rows)) {
        std::istringstream new_value_string(line);
        new_value_string >> index >> value;
        vector(row) = value;
        row++;
        n++;
    }
    in.close();
    if (n != vector.size()) {
        std::cerr << "Unable to read all elements from file " << filename << "\n";
        return false;
    }
    return true;
}

bool LisIO::save_matrix(const std::string &filename,const Types::Sparse &matrix) {
    return saveMarket(matrix, filename);
}

bool LisIO::save_vector(const std::string &filename,const Types::Vector &vector) {
    std::ofstream out(filename.c_str(), std::ios::out);
    if (!out) return false;

    out.flags(std::ios_base::scientific);
    out.precision(std::numeric_limits<Types::Real>::digits10 + 2);
    if (
        Eigen::internal::is_same< Types::Real, std::complex<float> >::value ||
        Eigen::internal::is_same<Types::Real, std::complex<double> >::value
    ) {
        out << "%%MatrixMarket matrix array complex general\n";
    } else {
        out << "%%MatrixMarket matrix array real general\n";
    }

    out << vector.rows() << "\n";
    for (Eigen::Index i = 0; i < vector.rows(); i++) {
        out << i+1 << " " << vector(i) << "\n";
    }
    out.close();
    return true;
}