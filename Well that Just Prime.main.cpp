//
//  main.cpp
//  Well that Just Prime
//
//  Created by Angel Munoz on 2/22/26.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <string>

using namespace std;

class Factorizer {
public:
    
    vector<int> primeFactors(int n) {
        vector<int> factors;
        
        if (n <= 1) {
            return factors;
        }
        
        
        while (n % 2 == 0) {
            factors.push_back(2);
            n /= 2;
        }
        
       
        for (int i = 3; i * i <= n; i += 2) {
            while (n % i == 0) {
                factors.push_back(i);
                n /= i;
            }
        }
        
       
        if (n > 1) {
            factors.push_back(n);
        }
        
        return factors;
    }
};


class FactorizerTest {
private:
    Factorizer factorizer;
    
    void runTest(const string& testName, int input,
                 const vector<int>& expected) {
        vector<int> result = factorizer.primeFactors(input);
        
        cout << "Test: " << testName << " - ";
        
        if (result == expected) {
            cout << "PASSED" << endl;
        } else {
            cout << "FAILED" << endl;
            cout << "  Input: " << input << endl;
            cout << "  Expected: ";
            for (int factor : expected) {
                cout << factor << " ";
            }
            cout << endl;
            cout << "  Got: ";
            for (int factor : result) {
                cout << factor << " ";
            }
            cout << endl;
        }
    }
    
    void runArrayTest(const string& testName, int input,
                      int* expected, int size) {
        vector<int> expectedVec;
        for (int i = 0; i < size; i++) {
            expectedVec.push_back(expected[i]);
        }
        runTest(testName, input, expectedVec);
    }
    
public:
    void runAllTests() {
        cout << "=== Running All The Unit Tests ===" << endl << endl;
        
        // Test cases for n <= 1
        runArrayTest("n = -5", -5, nullptr, 0);
        runArrayTest("n = 0", 0, nullptr, 0);
        runArrayTest("n = 1", 1, nullptr, 0);
        
        // Test cases for prime numbers
        int prime2[] = {2};
        runArrayTest("n = 2 (prime)", 2, prime2, 1);
        
        int prime3[] = {3};
        runArrayTest("n = 3 (prime)", 3, prime3, 1);
        
        int prime5[] = {5};
        runArrayTest("n = 5 (prime)", 5, prime5, 1);
        
        int prime7[] = {7};
        runArrayTest("n = 7 (prime)", 7, prime7, 1);
        
        int prime11[] = {11};
        runArrayTest("n = 11 (prime)", 11, prime11, 1);
        
        // Test cases for composite numbers
        int composite4[] = {2, 2};
        runArrayTest("n = 4 = 2*2", 4, composite4, 2);
        
        int composite6[] = {2, 3};
        runArrayTest("n = 6 = 2*3", 6, composite6, 2);
        
        int composite8[] = {2, 2, 2};
        runArrayTest("n = 8 = 2*2*2", 8, composite8, 3);
        
        int composite9[] = {3, 3};
        runArrayTest("n = 9 = 3*3", 9, composite9, 2);
        
        int composite10[] = {2, 5};
        runArrayTest("n = 10 = 2*5", 10, composite10, 2);
        
        int composite12[] = {2, 2, 3};
        runArrayTest("n = 12 = 2*2*3", 12, composite12, 3);
        
        int composite15[] = {3, 5};
        runArrayTest("n = 15 = 3*5", 15, composite15, 2);
        
        int composite16[] = {2, 2, 2, 2};
        runArrayTest("n = 16 = 2*2*2*2", 16, composite16, 4);
        
        int composite18[] = {2, 3, 3};
        runArrayTest("n = 18 = 2*3*3", 18, composite18, 3);
        
        int composite20[] = {2, 2, 5};
        runArrayTest("n = 20 = 2*2*5", 20, composite20, 3);
        
        int composite30[] = {2, 3, 5};
        runArrayTest("n = 30 = 2*3*5", 30, composite30, 3);
        
        int composite100[] = {2, 2, 5, 5};
        runArrayTest("n = 100 = 2*2*5*5", 100, composite100, 4);
        
        int composite1000[] = {2, 2, 2, 5, 5, 5};
        runArrayTest("n = 1000 = 2^3 * 5^3", 1000, composite1000, 6);
        
        cout << "\n=== All Tests Completed ===" << endl;
    }
};

//The coding goes in there
int main() {
    Factorizer factorizer;
    FactorizerTest testSuite;
    
    // Run all of the test
    testSuite.runAllTests();
    
    cout << "\n=== Interactive Testing ===" << endl;
    cout << "Enter integers to factorize (0 to exit):" << endl;
    
    while (true) {
        cout << "\nEnter the number: ";
        int n;
        cin >> n;
        
        if (n == 0) {
            break;
        }
        
        vector<int> factors = factorizer.primeFactors(n);
        
        cout << "Prime factors of " << n << ": ";
        if (factors.empty()) {
            cout << "none (n <= 1)";
        } else {
            for (size_t i = 0; i < factors.size(); i++) {
                cout << factors[i];
                if (i < factors.size() - 1) {
                    cout << " × ";
                }
            }
        }
        cout << endl;
        
        // Verify result with simple multiplication
        if (!factors.empty()) {
            long product = 1;
            for (int factor : factors) {
                product *= factor;
            }
            if (product == n) {
                cout << "Verification: " << product << " = " << n << " ✓" << endl;
            } else {
                cout << "Verification: " << product << " ≠ " << n << " ✗" << endl;
            }
        }
    }
    
    cout << "The Program has been terminated." << endl;
    
    return 0;
}
