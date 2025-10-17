#include <matrix_io.hpp>

/**
 * Load matrix in mtx file into an Eigen Sparse
 * @param filename The mtx file containing the sparse matrix
 * @param matrix The matrix to be filled, this will clear previous data
 * @return true if file reading was successful, false otherwise
 */
bool MtxIO::load_matrix(const std::string &filename, Types::Sparse &matrix) {
    return loadMarket(matrix, filename);
}

/**
 * Load vector in mtx file into an Eigen VectorXd
 * @param filename The mtx file containing the vector
 * @param vector The vector to be filled, this will clear previous data
 * @return true if file reading was successful, false otherwise
 */
bool MtxIO::load_vector(const std::string &filename, Types::Vector &vector) {
    return loadMarketVector(vector, filename);
}

/**
 * Save an Eigen Sparse into mtx file immediately readable by Eigen
 * @param filename The mtx file to be filled, this will delete previous content
 * @param matrix The matrix to be saved
 * @return true if file writing was successful, false otherwise
 */
bool MtxIO::save_matrix(const std::string &filename, const Types::Sparse &matrix) {
    return saveMarket(matrix, filename);
}

/**
 * Save an Eigen VectorXd into a mtx file immediately readable by Eigen
 * @param filename The mtx file to be filled, this will delete previous content
 * @param vector The vector to be saved
 * @return true if file writing was successful, false otherwise
 */
bool MtxIO::save_vector(const std::string &filename, const Types::Vector &vector) {
    return saveMarketVector(vector, filename);
}

/**
 * Load a LIS generated mtx file into a Eigen Sparse matrix
 * @param filename The LIS generated mtx file containing the sparse matrix
 * @param matrix The matrix to be filled, this will clear previous data
 * @return true if file reading was successful, false otherwise
 */
bool LisIO::load_matrix(const std::string &filename,Types::Sparse &matrix) {
    return loadMarket(matrix, filename);
}

/**
 * Load a LIS generated mtx file into a Eigen VectorXd
 * @param filename The LIS generated mtx file containing the vector
 * @param vector The vector to be filled, this will clear previous data
 * @return true if file reading was successful, false otherwise
 */
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

/**
 * Load two LIS generated mtx file into a vector of EigenPairs
 * @param evec_filename The LIS generated mtx file containing the eigenvectors
 * @param eval_filename The LIS generated mtx file containing the eigenvalues
 * @param eigenpairs A vector of EigenPairs to be filled, this will clear previous data
 * @return true if file readings were successful, false otherwise
 */
bool load_eigenpairs(const std::string &evec_filename,const std::string &eval_filename,std::vector<Types::EigenPair> &eigenpairs) {

    eigenpairs.clear(); // vector is not empty  ==> empty it

    Types::Sparse eigen_vectors;
    Types::Vector eigen_values;

    bool evec_load_res = LisIO::load_matrix(evec_filename, eigen_vectors);
    bool eval_load_res = LisIO::load_vector(eval_filename, eigen_values);

    if (!evec_load_res) {
        std::cerr << "Unable to load eigen vectors from file " << evec_filename << "\n";
        return false;
    }
    if (!eval_load_res) {
        std::cerr << "Unable to load eigen values from file " << eval_filename << "\n";
        return false;
    }
    int num_evec = static_cast<int>(eigen_vectors.nonZeros() / eigen_vectors.rows());

    if (num_evec != eigen_values.size()) {
        std::cerr << "Unable to read eigenpairs from files " << evec_filename << ", " << eval_filename
        << " mismatching dimensions"<< std::endl;
        return false;
    }
    if(num_evec * eigen_vectors.rows() != eigen_vectors.nonZeros()) {   // check that nnz is exact multiple
        std::cerr << "Unable to read eigenpairs from files " << evec_filename
        << " doesn't contain a valid lis eigenvector format"<< std::endl;
        return false;
    }

    eigenpairs.reserve(num_evec);
    for (int i = 0; i < num_evec; i++) {
        eigenpairs.emplace_back(static_cast<Types::Vector>(eigen_vectors.col(i)), static_cast<Types::Real>(eigen_values(i)));
    }

    return true;
}

/**
 * Save a Eigen Sparse into a file immediately readable from LIS
 * @param filename The mtx file to be filled with LIS readable data, this will delete previous content
 * @param matrix  The matrix to be saved
 * @return true if file writing was successful, false otherwise
 */
bool LisIO::save_matrix(const std::string &filename,const Types::Sparse &matrix) {
    return saveMarket(matrix, filename);
}

/**
 * Save a Eigen VectorXd into a file immediately readable from LIS
 * @param filename The mtx file to be filled with LIS readable data, this will delete previous content
 * @param vector The vector to be saved
 * @return true if file writing was successful, false otherwise
 */
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