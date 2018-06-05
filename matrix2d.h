#pragma once

#include <vector>
#include <exception>
#include <algorithm>
#include <sstream>
#include <memory>

namespace cppchallenge {

using std::vector;
using std::size_t;

/**
 * @brief The MatrixException class: A simple exception class to distinguish from system exceptions
 */
class MatrixException: public std::exception {
    std::string msg_;
public:
    explicit MatrixException(const std::string& msg)
        : msg_(msg)
    {}

    virtual const char* what() const noexcept;
};

const char* MatrixException::what() const noexcept {
    return msg_.c_str();
}

/**
 * @brief The Matrix2D class: A lightweight 2D matrix implementation
 * @property rows_: The number of rows in the matrix
 * @property cols_: The number of columns in the matrix
 * @property data_: The buffer to store the data in.
 */
template <typename T>
class Matrix2D {
    size_t rows_, cols_;
    vector<T> data_;

    /**
     * @brief index computes the buffer index based on (row, col) index
     * @param i the 'row' index
     * @param j the 'column' index
     * @return the 1D index into the buffer
     */
    inline
    size_t index(size_t i, size_t j) const {
        if (i >= rows_ || j >= cols_) {
            std::ostringstream oss;
            oss << "Index (" << i << ", " << j << ") is out of bound.\n"
                   "Matrix size = (" << rows_ << ", " << cols_ << ").\n";

            throw MatrixException(oss.str());
        }

        return i*cols_ + j;
    }

    Matrix2D& operator+= (const Matrix2D<T>& rhs) {
        if (this->size() != rhs.size()) {
            std::ostringstream oss;
            oss << "Dimension mismatch. Both matrices must have the same size.\n";

            throw MatrixException(oss.str());
        }

        std::transform(begin(data_), end(data_), begin(rhs.data_), begin(data_),
                       std::plus<T>());
        return *this;
    }

    Matrix2D& operator-= (const Matrix2D<T>& rhs) {
        if (this->size() != rhs.size()) {
            std::ostringstream oss;
            oss << "Dimension mismatch. Matrices must have the same size.\n";

            throw MatrixException(oss.str());
        }

        std::transform(begin(data_), end(data_), begin(rhs.data_), begin(data_),
                       std::minus<T>());
        return *this;
    }    

public:
    Matrix2D()
        : rows_(0), cols_(0), data_(0)
    {}

    Matrix2D(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data_(rows_*cols_)
    {}

    Matrix2D(const Matrix2D<T>& other)
        : rows_(other.rows_), cols_(other.cols_), data_(other.data_)
    {}

    Matrix2D(Matrix2D<T>&& other)
        : Matrix2D<T>()
    {
        swap(*this, other);
    }

    Matrix2D<T>& operator= (Matrix2D<T> other) {
        swap(*this, other);

        return *this;
    }

    friend void swap(Matrix2D<T>& lhs, Matrix2D<T>& rhs) {
        using std::swap;

        swap(lhs.rows_, rhs.rows_);
        swap(lhs.cols_, rhs.cols_);
        swap(lhs.data_, rhs.data_);
    }

    /**
     * @brief operator + Computes Matrix addition (binary version)
     * @param rhs
     * @return result by value
     */
    Matrix2D<T> operator+ (const Matrix2D<T>& rhs) const {
        Matrix2D<T> result(*this);
        result += rhs;

        return result;
    }

    /**
     * @brief operator - Computes Matrix subtraction (binary version)
     * @param rhs
     * @return result by value
     */
    Matrix2D<T> operator- (const Matrix2D<T>& rhs) const {
        Matrix2D<T> result(*this);
        result -= rhs;

        return result;
    }

    /**
     * @brief operator * Computes Matrix-Matrix multiply
     * @param rhs
     * @return result by value
     */
    Matrix2D<T> operator* (const Matrix2D<T>& rhs) const {
        if (cols_ != rhs.rows_) {
            std::ostringstream oss;
            oss << "Dimension mismatch. Number of columns of the first matrix should equal number\n"
                   "of rows in the seconnd matrix.\n";

            throw MatrixException(oss.str());
        }

        Matrix2D<T> result(rows_, rhs.cols_);

        for (size_t i = 0; i < rows_; i++) {
            for (size_t k = 0; k < cols_; k++) {
                for (size_t j = 0; j < rhs.cols_; j++) {
                    result(i, j) += data_[index(i, k)]*rhs(k, j);
                }
            }
        }

        return result;
    }

    /**
     * @brief operator * Computes Matrix-Vector multiply
     * @param rhs
     * @return result by value
     */
    vector<T> operator* (const vector<T>& rhs) const {
        vector<T> result(rows_, 0);
        for (size_t i = 0 ; i < rows_; i++) {
            for (size_t j = 0; j < cols_; j++) {
                result[i] += data_[index(i, j)]*rhs[j];
            }
        }

        return result;
    }

    /**
     * @brief transpose Computes Matrix transposition
     * @return result by value
     */
    Matrix2D<T> transpose() const {
        Matrix2D<T> result(cols_, rows_);

        for (size_t i = 0; i < cols_; i++) {
            for (size_t j = 0; j < rows_; j++) {
                result(i, j) = data_[index(j, i)];
            }
        }

        return result;
    }

    /**
     * @brief operator () 2D indexing operator (read/write)
     * @param i The 'row' index
     * @param j The 'column' index
     * @return referrence to value at (row, col)
     */
    inline
    const T& operator() (size_t i, size_t j) const {
        return data_[index(i, j)];
    }

    /**
     * @brief operator () 2D indexing operator (read-only)
     * @param i The 'row' index
     * @param j The 'column' index
     * @return const-referrence to value at (row, col)
     */
    inline
    T& operator() (size_t i, size_t j) {
        return data_[index(i, j)];
    }

    /**
     * @brief rows Number of rows in the matrix
     * @return number of rows
     */
    inline
    size_t rows() const {
        return rows_;
    }

    /**
     * @brief cols Number of columns in the matrix
     * @return number of columns
     */
    inline
    size_t cols() const {
        return cols_;
    }

    /**
     * @brief size The size of the matrix
     * @return the matrix size as std::pair
     */
    inline
    std::pair<size_t, size_t> size() const {
        return std::make_pair(rows_, cols_);
    }

};

}
