#include <iostream>
#include <matrix_io.hpp>
#include <matrix_ops.hpp>
#include <string>

int main(int argc, char *argv[]) {
    Types::Sparse A_g;

    auto res = MtxIO::load_matrix(Constants::TASK1_GRAPH_FILE, A_g);
    if (!res) {
        std::cerr << "Error loading matrix" << std::endl;
        return 1;
    }
    std::cout << "A_g:\n " << A_g << std::endl;

    return 0;
}
