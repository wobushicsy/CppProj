#include "hw1.h"
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using Matrix = std::vector<std::vector<double>>;

bool checkMatrixEmpty(const Matrix& matrix) {
    if (matrix.size() == 0 || matrix[0].size() == 0) {
        return true;
    }
    return false;
}

namespace algebra {
    Matrix zeros(size_t n, size_t m) {
        return Matrix(n, std::vector<double>(m, 0));
    }

    Matrix ones(size_t n, size_t m) {
        return Matrix(n, std::vector<double>(m, 1));
    }

    Matrix random(size_t n, size_t m, double min, double max) {
        if (min >= max) {
            throw std::logic_error("min is greater than or equal to max! ");
        }

        std::vector<std::vector<double>> matrix_2d;
        for (size_t i = 0; i < n; i += 1) {
            std::vector<double> matrix;
            for (size_t j = 0; j < m; j += 1) {
                std::uniform_real_distribution<double> uni(min, max);
                std::default_random_engine re;
                double a_random_double = uni(re);
                matrix.push_back(a_random_double);
            }
            matrix_2d.push_back(matrix);
        }

        return matrix_2d;
    }

    void show(const Matrix& matrix) {
        for (auto& row : matrix) {
            for (double dou : row) {
                std::cout << std::setfill(' ') << std::setw(3) << dou;
            }
            std::cout << std::endl;
        }
    }

    Matrix multiply(const Matrix& matrix, double c) {
        if (checkMatrixEmpty(matrix))
            return matrix;

        Matrix new_matrix;
        size_t n = matrix.size();
        size_t m = matrix[0].size();
        for (size_t i = 0; i < n; i += 1) {
            std::vector<double> new_row;
            for (size_t j = 0; j < m; j += 1) {
                new_row.push_back(matrix[i][j] * c);
            }
            new_matrix.push_back(new_row);
        }

        return new_matrix;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
        if (checkMatrixEmpty(matrix1))
            return matrix1;
        if (checkMatrixEmpty(matrix2))
            return matrix2;

        Matrix new_matrix;
        size_t n1 = matrix1.size();
        size_t m1 = matrix1[0].size();
        size_t n2 = matrix2.size();
        size_t m2 = matrix2[0].size();

        if (m1 != n2) {
            throw std::logic_error("matrices can't multiply");
        }

        for (size_t i = 0; i < n1; i += 1) {
            std::vector<double> new_row;
            for (size_t j = 0; j < m2; j += 1) {
                double sum = 0;
                for (size_t k = 0; k < m1; k += 1) {
                    sum += matrix1[i][k] * matrix2[k][j];
                }
                new_row.push_back(sum);
            }
            new_matrix.push_back(new_row);
        }

        return new_matrix;

    }

    Matrix sum(const Matrix& matrix, double c) {
        if (checkMatrixEmpty(matrix))
            return matrix;

        Matrix new_matrix;
        size_t n = matrix.size();
        size_t m = matrix[0].size();
        for (size_t i = 0; i < n; i += 1) {
            std::vector<double> new_row;
            for (size_t j = 0; j < m; j += 1) {
                new_row.push_back(matrix[i][j] + c);
            }
            new_matrix.push_back(new_row);
        }

        return new_matrix;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
        bool matrix1IsEmpty = checkMatrixEmpty(matrix1);
        bool matrix2IsEmpty = checkMatrixEmpty(matrix2);
        if (matrix1IsEmpty && matrix2IsEmpty) {
            return matrix1;
        }
        if (matrix1IsEmpty) {
            throw std::logic_error("matrix1 is empty");
        }
        if (matrix2IsEmpty) {
            throw std::logic_error("matrix2 is empty");
        }

        size_t n1 = matrix1.size();
        size_t m1 = matrix1[0].size();
        size_t n2 = matrix2.size();
        size_t m2 = matrix2[0].size();
        if (n1 != n2 || m1 != m2) {
            throw std::logic_error("matrices size not equal");
        }

        Matrix new_matrix;
        for (size_t i = 0; i < n1; i += 1) {
            std::vector<double> new_row;
            for (size_t j = 0; j < m1; j += 1) {
                new_row.push_back(matrix1[i][j] + matrix2[i][j]);
            }
            new_matrix.push_back(new_row);
        }

        return new_matrix;
    }

    Matrix transpose(const Matrix& matrix) {
        if (checkMatrixEmpty(matrix)) {
            return matrix;
        }

        Matrix new_matrix;
        size_t n = matrix.size();
        size_t m = matrix[0].size();
        for (size_t i = 0; i < m; i += 1) {
            std::vector<double> new_row;
            for (size_t j = 0; j < n; j += 1) {
                new_row.push_back(matrix[j][i]);
            }
            new_matrix.push_back(new_row);
        }

        return new_matrix;
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m) {
        if (checkMatrixEmpty(matrix)) {
            throw std::logic_error("matrix is empty");
        }

        Matrix new_matrix;
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        for (size_t i = 0; i < rows; i += 1) {
            if (i == n) {
                continue;
            }
            std::vector<double> new_row;
            for (size_t j = 0; j < cols; j += 1) {
                if (j == m) {
                    continue;
                }
                new_row.push_back(matrix[i][j]);
            }
            new_matrix.push_back(new_row);
        }

        return new_matrix;
    }

    double determinant(const Matrix& matrix) {
        if (checkMatrixEmpty(matrix)) {
            return 1;
        }

        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        if (rows != cols) {
            throw std::logic_error("matrix is invalid");
        }

        if (rows == 1 && cols == 1) {
            return matrix[0][0];
        }
        double flag = 1;
        double deter = 0;
        for (size_t i = 0; i < rows; i += 1) {
            deter += flag * matrix[0][i] * determinant(minor(matrix, 0, i));
            flag = -flag;
        }

        return deter;
    }

    Matrix inverse(const Matrix& matrix) {
        if (checkMatrixEmpty(matrix)) {
            return matrix;
        }

        size_t n = matrix.size();
        size_t m = matrix[0].size();
        if (n != m) {
            throw std::logic_error("matrix is invalid");
        }

        double deter = determinant(matrix);

        if (deter == 0) {
            throw std::logic_error("singular matrices have no inverse");
        }

        Matrix new_matrix;
        for (size_t i = 0; i < n; i += 1) {
            std::vector<double> new_row;
            for (size_t j = 0; j < m; j += 1) {
                Matrix cofactor = minor(matrix, i, j);
                double val = determinant(cofactor) * ((i + j) % 2 ? -1 : 1);
                new_row.push_back(val);
            }
            new_matrix.push_back(new_row);
        }

        return multiply(transpose(new_matrix), 1 / deter);
    }

    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
        if (checkMatrixEmpty(matrix1)) {
            return matrix1;
        }
        if (checkMatrixEmpty(matrix2)) {
            return matrix2;
        }

        Matrix new_matrix;
        if (axis == 0) {
            if (matrix1[0].size() != matrix2[0].size()) {
                throw std::logic_error("matrices are invalid");
            }
            for (auto row : matrix1) {
                new_matrix.push_back(std::move(row));
            }
            for (auto row : matrix2) {
                new_matrix.push_back(std::move(row));
            }
        } else if (axis == 1) {
            if (matrix1.size() != matrix2.size()) {
                throw std::logic_error("matrices are invalid");
            }
            size_t rows = matrix1.size();
            for (size_t i = 0; i < rows; i += 1) {
                std::vector<double> new_row;
                for (double val : matrix1[i]) {
                    new_row.push_back(val);
                }
                for (double val : matrix2[i]) {
                    new_row.push_back(val);
                }
                new_matrix.push_back(new_row);
            }
        }

        return new_matrix;
    }

    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
        if (checkMatrixEmpty(matrix)) {
            return matrix;
        }
        size_t rows = matrix.size();
        if (r1 >= rows || r2 >= rows) {
            throw std::logic_error("r1 or r2 inputs are out of range");
        }

        Matrix new_matrix;
        for (size_t i = 0; i < rows; i += 1) {
            if (i == r1) {
                new_matrix.push_back(matrix[r2]);
            } else if (i == r2) {
                new_matrix.push_back(matrix[r1]);
            } else {
                new_matrix.push_back(matrix[i]);
            }
        }

        return new_matrix;
    }

    Matrix ero_multiply(const Matrix& matrix, size_t r, double c) {
        if (checkMatrixEmpty(matrix)) {
            return matrix;
        }
        size_t rows = matrix.size();
        if (r >= rows) {
            throw std::logic_error("r1 or r2 inputs are out of range");
        }

        Matrix new_matrix;
        for (size_t i = 0; i < rows; i += 1) {
            if (i != r) {
                new_matrix.push_back(matrix[i]);
            } else {
                std::vector<double> new_row;
                for (double val : matrix[i]) {
                    new_row.push_back(val * c);
                }
                new_matrix.push_back(new_row);
            }
        }

        return new_matrix;
    }

    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
        if (checkMatrixEmpty(matrix)) {
            return matrix;
        }
        size_t rows = matrix.size();
        if (r1 >= rows || r2 >= rows) {
            throw std::logic_error("r1 or r2 inputs are out of range");
        }

        std::vector<double> be_added = matrix[r1];
        Matrix new_matrix;
        size_t cols = matrix[0].size();
        for (size_t i = 0; i < rows; i += 1) {
            if (i != r2) {
                new_matrix.push_back(matrix[i]);
            } else {
                std::vector<double> new_row;
                for (size_t j = 0; j < cols; j += 1) {
                    new_row.push_back(be_added[j] * c + matrix[i][j]);
                }
                new_matrix.push_back(new_row);
            }
        }

        return new_matrix;
    }

    Matrix upper_triangular(const Matrix& matrix) {
        if (checkMatrixEmpty(matrix)) {
            return matrix;
        }
        int n = matrix.size();
        int m = matrix[0].size();
        if (n != m) {
            throw std::logic_error("non-square matrices have no upper triangular form");
        }
        Matrix new_matrix(matrix);
        for (int i = 0; i < n - 1; i += 1) {
            if (new_matrix[i][i] == 0) {
                for (int j = i + 1; j < n; j += 1) {
                    if (new_matrix[j][i] != 0) {
                        Matrix tmp_matrix = ero_swap(new_matrix, i, j);
                        new_matrix = tmp_matrix;
                        break;
                    }
                }
            }
            for (int j = i + 1; j < n; j += 1) {
                double diff = new_matrix[j][i] / new_matrix[i][i];
                if (diff == 0) {
                    continue;
                }
                Matrix tmp_matrix = ero_sum(new_matrix, i, -diff, j);
                new_matrix = tmp_matrix;
            }
        }

        return new_matrix;
    }
}
