#include <iostream>

#include "matrix2d.h"
#include "utilities.h"

using namespace std;
using namespace cppchallenge;

int main()
{    
    TestData<double> data;
    ifstream file("../../test2.txt");
    data.parse(file);

    auto& A = data.mat["A"];
    auto& B = data.mat["B"];
    auto& X = data.vec["X"];

    cout << boolalpha << almost_equal(A*X, data.vec["AX"]) << "\n";
    cout << boolalpha << almost_equal(A+B, data.mat["A+B"]) << "\n";
    cout << boolalpha << almost_equal(A-B, data.mat["A-B"]) << "\n";
    cout << boolalpha << almost_equal(A*B, data.mat["A*B"]) << "\n";
    cout << boolalpha << almost_equal(A.transpose(), data.mat["A^T"]) << "\n";

    return 0;
}
