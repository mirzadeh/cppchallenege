#pragma once

#include "matrix2d.h"
#include <cmath>
#include <unordered_map>
#include <fstream>

namespace cppchallenge {

using std::unordered_map;
using std::string;
using std::ostream, std::istream, std::ifstream;

template <typename T>
ostream& operator<< (ostream& os, const vector<T>& vec){
    for (auto& el: vec) os << el << " ";
    os << "\n";

    return os;
}

template <typename T>
istream& operator>> (istream& is, vector<T>& vec){
    for (auto& el: vec) is >> el;

    return is;
}

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

template <typename T>
istream& operator>> (istream& is, Matrix2D<T>& mat) {
    for (size_t i = 0; i < mat.rows(); i++) {
        for (size_t j = 0; j < mat.cols(); j++) {
            is >> mat(i, j);
        }
    }

    return is;
}

template <typename T>
bool almost_equal(const vector<T>& lhs, const vector<T>& rhs, double tol = 1e-6) {
    if (lhs.size() != rhs.size()) return false;

    for (std::size_t i = 0; i < lhs.size(); i++) {
        if (std::fabs(lhs[i] - rhs[i]) > tol) return false;
    }

    return true;
}

template <typename T>
bool almost_equal(const Matrix2D<T>& lhs, const Matrix2D<T>& rhs, double tol = 1e-6) {
    if (lhs.size() != rhs.size()) return false;

    for (std::size_t i = 0; i < lhs.rows(); i++) {
        for (std::size_t j = 0; j < lhs.cols(); j++)
        if (std::fabs(lhs(i, j) - rhs(i, j)) > tol) return false;
    }

    return true;
}


template <typename T>
class TestData{
public:
    unordered_map<string, Matrix2D<T>> mat;
    unordered_map<string, vector<T>> vec;

    void parse(ifstream& file) {
        string line;

        while(getline(file, line)) {
            if (line[0] == '[') {
                size_t end = line.find(']');
                string token = line.substr(1, end-1);

                if (token == "Matrix") {
                    string name;
                    size_t rows, cols;

                    file >> name >> rows >> cols;
                    mat.insert(make_pair(name, Matrix2D<T>(rows, cols)));
                    file >> mat[name];

                } else if (token == "Vector") {
                    string name;
                    size_t cols;

                    file >> name >> cols;
                    vec.insert(make_pair(name, vector<T>(cols)));
                    file >> vec[name];

                }
            }
        }
    }
};


}
