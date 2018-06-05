#include <iostream>

#include "matrix2d.h"
#include "utilities.h"

using namespace std;
using namespace cppchallenge;

int main(int, char* argv[])
{
    TestData<double> data;
    try {
        ifstream file(argv[1]);
        data.parse(file);
    } catch (const std::exception& e) {
        cerr << e.what() << endl;

        return EXIT_FAILURE;
    }

    auto& A = data.mat["A"];
    auto& B = data.mat["B"];
    auto& X = data.vec["X"];

    vector<function<bool()>> tests;
    tests.push_back([&] { return compare(A*X, data.vec["AX"]); });
    tests.push_back([&] { return compare(A+B, data.mat["A+B"]); });
    tests.push_back([&] { return compare(A-B, data.mat["A-B"]); });
    tests.push_back([&] { return compare(A*B, data.mat["A*B"]); });
    tests.push_back([&] { return compare(A.transpose(), data.mat["A^T"]); });

    int failed = 0, norun = 0;
    for (auto& test: tests) {
        try {
            failed += test();
        } catch (const MatrixException& e) {
            cerr << "[MatrixException]: " << e.what() << endl;
            norun++;
        } catch (const std::exception& e) {
            cerr << "[Exception]: " << e.what() << endl;
            norun++;
        } catch (...) {
            cerr << "Unknown exception occured during test" << endl;
            norun++;
        }
    }

    cout << "Total tests: " << tests.size() << "\n"
         << "Failed:      " << failed << "\n"
         << "Didn't run:  " << norun << "\n";

    return failed + norun;
}
