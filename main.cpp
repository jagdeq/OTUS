#include <iostream>

#include "matrix.hpp"

int main()
{
    int diagSize = 10;

    math::Matrix<int, 0, 2> matrix;
    for (int i = 0; i != diagSize; ++i)
        matrix[i][i] = i;

    for (int i = 0; i != diagSize; ++i)
        matrix[i][diagSize - 1 - i] = i;

    for (size_t iRow = 1; iRow != 9; ++iRow) {
        for (size_t iCol = 1; iCol != 9; ++iCol)
            std::cout << matrix[iRow][iCol] << ' ';
        std::cout << std::endl;
    }

    std::cout << matrix.size() << std::endl;

    // Только для 2D-матрицы
    for (auto [x, y, v] : matrix)
        printf("%d (%lu, %lu)\n", v, x, y);

    return 0;
}
