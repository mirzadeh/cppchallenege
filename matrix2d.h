#pragma once

#include <vector>
#include <exception>
#include <algorithm>
#include <sstream>

namespace cppchallenge {

using std::vector;
using std::size_t;

template <typename T>
class Matrix2D {
    size_t rows_, cols_;
    vector<T> data_;

    inline
    size_t index(size_t i, size_t j) const {
        if (i >= rows_ || j >= cols_) {
            std::ostringstream oss;
            oss << "Index (" << i << ", " << j << ") is out of bound.\n"
                   "Matrix size = (" << rows_ << ", " << cols_ << ").\n";

            throw std::out_of_range(oss.str());
        }

        return i*cols_ + j;
    }

    Matrix2D& operator+= (const Matrix2D<T>& rhs) {
        if (this->size() != rhs.size()) {
            std::ostringstream oss;
            oss << "Dimension mismatch. Both matrices must have the same size.\n";

            throw std::invalid_argument(oss.str());
        }

        std::transform(begin(data_), end(data_), begin(rhs.data_), begin(data_),
                       std::plus<T>());
        return *this;
    }

    Matrix2D& operator-= (const Matrix2D<T>& rhs) {
        if (this->size() != rhs.size()) {
            std::ostringstream oss;
            oss << "Dimension mismatch. Matrices must have the same size.\n";

            throw std::invalid_argument(oss.str());
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

    friend
    void swap(Matrix2D<T>& lhs, Matrix2D<T>& rhs) {
        using std::swap;

        swap(lhs.rows_, rhs.rows_);
        swap(lhs.cols_, rhs.cols_);
        swap(lhs.data_, rhs.data_);
    }

    Matrix2D<T> operator+ (const Matrix2D<T>& rhs) const {
        Matrix2D<T> result(*this);
        result += rhs;

        return result;
    }

    Matrix2D<T> operator- (const Matrix2D<T>& rhs) const {
        Matrix2D<T> result(*this);
        result -= rhs;

        return result;
    }

    Matrix2D<T> operator* (const Matrix2D<T>& rhs) const {
        if (cols_ != rhs.rows_) {
            std::ostringstream oss;
            oss << "Dimension mismatch. Number of columns of the first matrix should equal number\n"
                   "of rows in the seconnd matrix.\n";

            throw std::invalid_argument(oss.str());
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

    vector<T> operator* (const vector<T>& rhs) const {
        vector<T> result(rows_, 0);
        for (size_t i = 0 ; i < rows_; i++) {
            for (size_t j = 0; j < cols_; j++) {
                result[i] += data_[index(i, j)]*rhs[j];
            }
        }

        return result;
    }

    Matrix2D<T> transpose() const {
        Matrix2D<T> result(cols_, rows_);

        for (size_t i = 0; i < cols_; i++) {
            for (size_t j = 0; j < rows_; j++) {
                result(i, j) = data_[index(j, i)];
            }
        }

        return result;
    }

    inline
    const T& operator() (size_t i, size_t j) const {
        return data_[index(i, j)];
    }

    inline
    T& operator() (size_t i, size_t j) {
        return data_[index(i, j)];
    }

    inline
    size_t rows() const {
        return rows_;
    }

    inline
    size_t cols() const {
        return cols_;
    }

    inline
    std::pair<size_t, size_t> size() const {
        return std::make_pair(rows_, cols_);
    }

    inline
    bool operator== (const Matrix2D<T>& rhs) const {
        return (this->size() == rhs.size() && data_ == rhs.data_);
    }
};

}
