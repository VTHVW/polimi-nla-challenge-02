#include <matrix_io.hpp>
#include <matrix_ops.hpp>

int main(int argc, char* argv[]) {
    Types::Sparse A;
    MtxIO::load_matrix(Constants::SMALL_MTX_FILE, A);

    Types::Real f_norm = std::sqrt(1+4+49);
    if (frobenius_norm(A) != f_norm) {
        std::cerr << "||A||_f = " << frobenius_norm(A) << " != " << f_norm << std::endl;
    }

    std::cout << A << std::endl;

    std::cout << row_sums(A) << std::endl;

    std::cout << make_diag_matrix(row_sums(A)) << std::endl;

}