#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <vector>
#include <ostream>
#include <sstream>
#include <exception>
#include <algorithm>

namespace cppchallenge {

using std::vector;
using std::size_t;

template <typename T>
class Matrix2D {
    size_t M, N;
    vector<T> data;

    inline
    size_t index(size_t i, size_t j) const {
        if (i >= M || j >= N) {
            std::ostringstream oss;
            oss << "Index (" << i << ", " << j << ") is out of bound.\n"
                   "Matrix size = (" << M << ", " << N << ").\n";

            throw std::out_of_range(oss.str());
        }

        return i*N + j;
    }

public:
    Matrix2D()
        : M(0), N(0), data(0)
    {}

    Matrix2D(size_t M, size_t N)
        : M(M), N(N), data(M*N)
    {}

    Matrix2D(const Matrix2D<T>& other)
        : M(other.M), N(other.N), data(other.data)
    {}

    Matrix2D<T>& operator= (const Matrix2D<T>& other) {
        if (this != &other) {
            M = other.M;
            N = other.N;
            data = other.data;
        }
    }

//    Matrix2D(Matrix2D<T>&& other)
//        : M(other.M), N(other.N), data(other.data)
//    {}

//    Matrix2D<T>& operator= (Matrix2D<T>&& rhs) {
//        // something
//    }

    Matrix2D& operator+= (const Matrix2D<T>& rhs) {
        if (M != rhs.M || N != rhs.N) {
            std::ostringstream oss;
            oss << "Dimension mismatch. Both matrices must have the same size.\n";

            throw std::invalid_argument(oss.str());
        }

        std::transform(begin(data), end(data), begin(rhs.data), begin(data),
                       std::plus<T>());
        return *this;
    }

    Matrix2D& operator-= (const Matrix2D<T>& rhs) {
        if (M != rhs.M || N != rhs.N) {
            std::ostringstream oss;
            oss << "Dimension mismatch. Both matrices must have the same size.\n";

            throw std::invalid_argument(oss.str());
        }

        std::transform(begin(data), end(data), begin(rhs.data), begin(data),
                       std::minus<T>());
        return *this;
    }

    Matrix2D& operator*= (const Matrix2D<T>& rhs) {
        if (N != rhs.M) {
            std::ostringstream oss;
            oss << "Dimension mismatch. Number of columns of the first matrix should equal number\n"
                   "of rows in the seconnd matrix.\n";

            throw std::invalid_argument(oss.str());
        }

        Matrix2D<T> result(M, rhs.N);

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < rhs.N; j++) {
                T sum = 0;
                for (size_t k = 0; k < N; k++) {
                    sum += data[index(i, k)]*rhs(k, j);
                }
                result(i, j) = sum;
            }
        }

        M = result.M;
        N = result.N;
        data = result.data;
        return *this;
    }

    Matrix2D<T> operator+ (const Matrix2D<T>& rhs) {
        Matrix2D<T> result(*this);
        result += rhs;

        return result;
    }

    Matrix2D<T> operator- (const Matrix2D<T>& rhs) {
        Matrix2D<T> result(*this);
        result -= rhs;

        return result;
    }

    Matrix2D<T> operator* (const Matrix2D<T>& rhs) {
        Matrix2D<T> result(*this);
        result *= rhs;

        return result;
    }

    vector<T> operator* (const vector<T>& rhs) {
        vector<T> result(M, 0);
        for (size_t i = 0 ; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                result[i] += data[index(i, j)]*rhs[j];
            }
        }

        return result;
    }

    Matrix2D<T> transpose() const {
        Matrix2D<T> result(N, M);
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                result(i, j) = data[index(j, i)];
            }
        }

        return result;
    }

    inline
    const T& operator() (size_t i, size_t j) const {
        return data[index(i, j)];
    }

    inline
    T& operator() (size_t i, size_t j) {
        return data[index(i, j)];
    }

    inline
    T* begin_row(size_t r) {
        return &data[0] + r*N;
    }

    inline
    T* end_row(size_t r) {
        return &data[0] + (r+1)*N;
    }

    // friend methods
    friend
    std::ostream& operator<< (std::ostream& os, const Matrix2D<T>& m) {
        for (size_t i = 0; i < m.M; i++) {
            for (size_t j = 0; j < m.N; j++) {
                os << m(i, j) << " ";
            }
            os << "\n";
        }

        return os;
    }
};

}

#endif // MATRIX2D_H
