#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <unordered_map>
#include "matrix2d.h"

using namespace std;
using namespace cppchallenge;

template <typename T>
ostream& operator<< (ostream& os, const vector<T>& a){
    for (auto& el:a) os << el << " ";
    os << "\n";

    return os;
}

int main()
{    
    ifstream file("../../test2.txt");
    string line;

    struct {
        unordered_map<string, Matrix2D<double>> mat;
        unordered_map<string, vector<double>> vec;
    } testdata;

    while(getline(file, line)) {
        if (line[0] == '[') {
            size_t end = line.find(']');
            string token = line.substr(1, end-1);

            if (token == "Matrix") {
                getline(file, line);
                istringstream iss(line);
                string name;
                size_t M, N;

                iss >> name >> M >> N;
                testdata.mat.insert(make_pair(name, Matrix2D<double>(M,N)));
                auto& mat = testdata.mat[name];

                for (size_t r = 0; r < M; r++) {
                    getline(file, line);
                    istringstream iss(line);

                    copy(istream_iterator<double>(iss), istream_iterator<double>(),
                         mat.begin_row(r));
                }

            } else if (token == "Vector") {
                getline(file, line);
                istringstream iss(line);
                string name;
                size_t M;

                iss >> name >> M;
                testdata.vec.insert(make_pair(name, vector<double>(M)));

                getline(file, line);
                iss.clear();
                iss.str(line);
                copy(istream_iterator<double>(iss), istream_iterator<double>(),
                     begin(testdata.vec[name]));

            }
        }
    }

    cout << testdata.vec["X"] << endl;
    cout << testdata.mat["A"] + testdata.mat["B"] << "\n";
    cout << testdata.mat["A"] - testdata.mat["B"] << "\n";
    cout << testdata.mat["A"] * testdata.mat["B"] << "\n";
    cout << testdata.mat["A"].transpose() << "\n";
    cout << testdata.mat["A"]*testdata.vec["X"] << "\n";

    return 0;
}
