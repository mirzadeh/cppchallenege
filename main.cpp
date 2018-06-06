#include <iostream>

#include <cppchallenge/matrix2d.h>
#include <cppchallenge/utilities.h>

using namespace std;
using namespace cppchallenge;

template <typename LHS, typename RHS>
int runtest(const string& name, const LHS& lhs, const RHS& rhs) {
    int failed = 0;    
    cout << "Running test " << name << " ... ";
    try {
        failed = compare(lhs, rhs);
        cout << (failed ? "FAILED" : "passed") << endl;

    } catch (const MatrixException& e) {
        cout << "MatrixException occured: " << e.what() << endl;
        failed = 1;

    } catch (const std::exception& e) {
        cout << "Exception occured: " << e.what() << endl;
        failed = 1;

    } catch (...) {
        cout << "Unknown exception occured." << endl;
        failed = 1;
    }

    return failed;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "usage: ./cppchallenge [testfile]" << endl;
        return EXIT_FAILURE;
    }

    TestData<double> data;
    try {
        ifstream file(argv[1]);
        data.parse(file);

    } catch (const std::exception& e) {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }

    auto& A = data.mat["A"];
    auto& B = data.mat["B"];
    auto& X = data.vec["X"];

    int num_failed = 0;

    // simple tests
    num_failed += runtest("Matrix-Vector multiply", A*X, data.vec["AX"]);
    num_failed += runtest("Matrix-Matrix addition", A+B, data.mat["A+B"]);
    num_failed += runtest("Matrix-Matrix subtraction", A-B, data.mat["A-B"]);
    num_failed += runtest("Matrix-Matrix multiply", A*B, data.mat["A*B"]);
    num_failed += runtest("Matrix transposition", A.transpose(), data.mat["A^T"]);

    // testing various forms of associtivity and distributivity
    num_failed += runtest("A+B == B+A", A+B, B+A);
    num_failed += runtest("(A+B)+B == A+(B+B)", (A+B)+B, A+(B+B));
    num_failed += runtest("(A+B)*X == AX+BX", (A+B)*X, A*X+B*X);
    num_failed += runtest("(A+B)*B == A*B+B*B", (A+B)*B, A*B+B*B);
    num_failed += runtest("A^T^T == A", A.transpose().transpose(), A);
    num_failed += runtest("(A*B)^T == B^T*A^T", (A*B).transpose(), B.transpose()*A.transpose());

    cout << endl;
    if (num_failed == 0) {
        cout << "All tests passed!\n";
    } else {
        cout << num_failed << " tests failed\n";
    }

    return num_failed;
}
