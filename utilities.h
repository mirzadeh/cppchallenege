#pragma once

#include "matrix2d.h"
#include <cmath>
#include <unordered_map>
#include <fstream>
#include <iostream>

namespace cppchallenge {

using std::unordered_map;
using std::string;
using std::ostream, std::istream, std::ifstream;

/**
 * @brief ostream overload for vector<T>
 */
template <typename T>
ostream& operator<< (ostream& os, const vector<T>& vec){
    for (auto& el: vec) os << el << " ";
    os << "\n";

    return os;
}

/**
 * @brief istream overload for vector<T>
 */
template <typename T>
istream& operator>> (istream& is, vector<T>& vec){
    for (auto& el: vec) is >> el;

    return is;
}

/**
 * @brief ostream overload for Matrix2D<T>
 */
template <typename T>
ostream& operator<< (ostream& os, const Matrix2D<T>& mat) {
    for (size_t i = 0; i < mat.rows(); i++) {
        for (size_t j = 0; j < mat.cols(); j++) {
            os << mat(i, j) << " ";
        }
        os << "\n";
    }

    return os;
}

/**
 * @brief istream overload for Matrix2D<T>
 */
template <typename T>
istream& operator>> (istream& is, Matrix2D<T>& mat) {
    for (size_t i = 0; i < mat.rows(); i++) {
        for (size_t j = 0; j < mat.cols(); j++) {
            is >> mat(i, j);
        }
    }

    return is;
}

/**
 * \brief Compares two vectors for (almost) equality.
 *
 * @param lhs: The 'lhs' to equlity
 * @param rhs: The 'rhs' to equlity
 * @param tol: The tolerance used for comparison.
 *
 * @return 'false' if |lhs - rhs| < tol. 'true' otherwise
 */
template <typename T>
bool compare(const vector<T>& lhs, const vector<T>& rhs, double tol = 1e-6) {
    if (lhs.size() != rhs.size()) return true;

    for (std::size_t i = 0; i < lhs.size(); i++) {
        if (std::fabs(lhs[i] - rhs[i]) > tol) return true;
    }

    return false;
}

/**
 * @brief Compares two matrices for (almost) equality.
 *
 * @param lhs: The 'lhs' to equlity
 * @param rhs: The 'rhs' to equlity
 * @param tol: The tolerance used for comparison.
 *
 * @return 'false' if |lhs - rhs| < tol. 'true' otherwise
 */

template <typename T>
bool compare(const Matrix2D<T>& lhs, const Matrix2D<T>& rhs, double tol = 1e-6) {
    if (lhs.size() != rhs.size()) return true;

    for (std::size_t i = 0; i < lhs.rows(); i++) {
        for (std::size_t j = 0; j < lhs.cols(); j++)
        if (std::fabs(lhs(i, j) - rhs(i, j)) > tol) return true;
    }

    return false;
}

/**
 * @brief The TestData class: A simple helper class to hold the test data information
 */
template <typename T>
class TestData{
public:
    unordered_map<string, Matrix2D<T>> mat;
    unordered_map<string, vector<T>> vec;

    /**
     * @brief Parse an input data file
     * @note Each non-empty line inthe file must either declare a token or be a comment.
                - A token can either be 'Matrix' or 'Vector' and must be placed in a bracket []
                - The immediate line after 'Matrix' or 'Vector' constitutes the header and must
                  define the 'name' and 'sizes'. Lines after the header, define the data, e.g.:
                        # A = [[1,2], [3,4]]
                        [Matrix]
                        A 2 2
                        1 2
                        3 4

                        # X = [1 3]
                        [Vector]
                        X 2
                        1 3
                - A comment must start with '#'
     * @param file The input file to parse
     */
    void parse(ifstream& file) {
        if (!file.is_open()) {
            throw std::invalid_argument("Could not open the file");
        }

        // parse the input line by line.
        string line;
        int lineno = 0;
        while(getline(file, line)) {
            if (line[0] == '#' || line.empty()) {
                continue;
            } else if (line[0] == '[') {
                size_t end = line.find(']');
                string token = line.substr(1, end-1);

                if (token == "Matrix") {
                    string name;
                    size_t rows, cols;

                    file >> name >> rows >> cols;
                    mat.insert(make_pair(name, Matrix2D<T>(rows, cols)));
                    file >> mat[name];
                    lineno += rows;

                } else if (token == "Vector") {
                    string name;
                    size_t cols;

                    file >> name >> cols;
                    vec.insert(make_pair(name, vector<T>(cols)));
                    file >> vec[name];

                } else {
                    throw std::invalid_argument("Unknown token in parsing data file");
                }
            } else {
                throw std::invalid_argument("Illegal character at the start of the file");
            }
        }
    }
};
}
