#include "matrix_multiplication.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

// ######################### Source code of multiplyMatrices in src/matrix_mult
void multiplyMatricesWithoutErrors(const std::vector<std::vector<int>> &A,
                                   const std::vector<std::vector<int>> &B,
                                   std::vector<std::vector<int>> &C, 
                                   int rowsA, 
                                   int colsA,
                                   int colsB) {
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


// The first argument is the name of the test suite, 
// and the second argument is the test's name within the test suite
// (underscore not allowed).
// reference: https://google.github.io/googletest/primer.html#simple-tests
TEST(MatrixMultiplicationTest, ProfessorTestCase) {
    /**
     * Errors code found:
     * - Error 6: Result matrix contains a number bigger than 100!
     * - Error 12: The number of rows in A is equal to the number of columns in B!
     * - Error 14: The result matrix C has an even number of rows!
     * - Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2078, 64 }, { 143, 161 } }
     * expected
     *      Which is: { { 58, 64 }, { 139, 154 } }
    */
    // [Arrange] First, we set up the test case
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::vector<std::vector<int>> B = {
        {7, 8},
        {9, 10},
        {11, 12}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> D(2, std::vector<int>(2, 0));


    // [Act] The core of the test case, here we cover the main thing to be tested
    multiplyMatrices(A, B, C, 2, 3, 2);
    multiplyMatricesWithoutErrors(A, B, D, 2, 3, 2);
    std::vector<std::vector<int>> expected = {
        {58, 64},
        {139, 154}
    };


    // [Assert] Finally, we obtain a response, trying to compare the expected result 
    //          with the result obtained in the act phase.
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Buggy function test failed!";
}

/**
To test the multiplication between two matrices, we create the following tests:
- Zero Matrix Test
    - Description: we assert that a matrix multiplied by another matrix 
                   consisting only of zeros is always a zero matrix.
    - Test suite: MatrixMultiplicationZeroMatricesTest
    - Test cases:
        ~ TestZeroMatrices2x3and3x2
        ~ TestZeroMatrices3x2and2x3

- Identity Matrix Test
    - Description: we assert that a matrix multiplied by an identity matrix 
                   is always the original matrix.
    - Test suite: MatrixMultiplicationIdentityMatricesTest
    - Test cases:
        ~ TestIdentityMatrices2x2and2x3
        ~ TestIdentityMatrices3x3and3x4
        ~ TestIdentityMatrices2x3and3x3
        ~ TestIdentityMatrices3x4and4x4
        ~ TestIdentityAnd25SquareMatrices

- Square Matrix Test
    - Description: we test some multiplications between square matrices.
    - Test suite: MatrixMultiplicationSquareMatricesTest
    - Test cases:
        ~ TestSquareZeroMatrices2x2         (A*B)
        ~ TestSquareZeroMatrices2x2Reversed (B*A)
        ~ TestSquareZeroMatrices3x3
        ~ TestSquareZeroMatrices3x3Reversed
        ~ TestSquareMatrices2x2
        ~ TestSquareMatrices2x2Reversed
        ~ TestSquareMatrices3x3
        ~ TestSquareMatrices3x3Reversed
        ~ TestSquareIdentityMatrices2x2
        ~ TestSquareIdentityMatrices2x2Reversed
        ~ TestSquareIdentityMatrices3x3
        ~ TestSquareIdentityMatrices3x3Reversed

- Vector Test
    - Description: we test some multiplications between vectors and 
                   between vectors and matrices.
    - Test suite: MatrixMultiplicationVectorAndMatricesTest
    - Test cases:
        ~ TestVectors1x2and2x1
        ~ TestVectors1x2and2x1Reversed
        ~ TestVectors1x3and3x1
        ~ TestVectors1x3and3x1Reversed
        ~ TestVectorAndMatrices1x2and2x4
        ~ TestVectorAndMatrices1x3and3x4

- Single Element Matrix
    - Description: we test some multiplications between a 1x1 matrix 
                   and other matrices.
    - Test suite: MatrixMultiplicationSingleElementMatricesTest
    - Test cases:
        ~ TestSingleElementOne
        ~ TestSingleElementZero
        ~ TestSingleElementAndVectors

- Negative Numbers
    - Description: we test some multiplications between negative matrices.
    - Test suite: MatrixMultiplicationNegativeNumbersTest
    - Test cases:
        ~ TestNegativeSingleElementAndVectors
        ~ TestNegativeSquareMatrixAndIdentityMatrix

- Matrix Properties
    - Description: we test some properties of the matrices. 
                   Here we have only implemented non-commutativity.
    - Test suite: MatrixMultiplicationPropertiesTest
    - Test cases:
        ~ TestNonCommutativity

- High Values Test
    - Description: we test a multiplication of high matrix order (10) 
                   to ensure that there are no errors.
    - Test suite: MatrixMultiplicationHighValuesTest
    - Test cases:
        ~ Test10x10Matrices



Some notes: 
- We use the multiplyMatricesWithoutErrors function to ensure that the results 
  written to the tests are correct.

- We have created the test with this logic: test the basic functions
  of multiplication between matrices.
  We believe that this is not a race to find the error code, 
  but to test the function given in the exercise.

- In each test case we've used the Arrange, Act, Assert pattern.

- Any error code found is written in the comment of each TEST 
  (in case you want to collapse the whole code for better readability, 
   each collapsed function contains the comments).

- We didn't want to split a test suite into different files 
  (a common and useful practice) to avoid some problems with the guidelines.



After these tests, we tracked each error code:
- Error 1: Element-wise multiplication of ones detected!
- Error 2: Matrix A contains the number 7!
- Error 3: Matrix A contains a negative number!
- Error 4: Matrix B contains the number 3!
- Error 5: Matrix B contains a negative number!
- Error 6: Result matrix contains a number bigger than 100!
- Error 7: Result matrix contains a number between 11 and 20!
- Error 8: Result matrix contains zero!
- Error 9: Result matrix contains the number 99!
- Error 10: A row in matrix A contains more than one '1'!
- Error 11: Every row in matrix B contains at least one '0'!
- Error 12: The number of rows in A is equal to the number of columns in B!
- Error 13: The first element of matrix A is equal to the first element of matrix B!
- Error 14: The result matrix C has an even number of rows!
- Error 15: A row in matrix A is filled entirely with 5s!
- Error 16: Matrix B contains the number 6!
- Error 17: Result matrix C contains the number 17!
- Error 18: Matrix A is a square matrix!
- Error 19: Every row in matrix A contains the number 8!
- Error 20: Number of columns in matrix A is odd!
*/




/********************
 * Zero Matrix Test *
 ********************/
TEST(MatrixMultiplicationZeroMatricesTest, TestZeroMatrices2x3and3x2) {
    /**
     * Error 8: Result matrix contains zero!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2071, 7 }, { 8, 6 } }
     * expected
     *      Which is: { { 0, 0 }, { 0, 0 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {0, 0, 0},
        {0, 0, 0}
    };
    std::vector<std::vector<int>> B = {
        {7, 8},
        {9, 10},
        {11, 12}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> D(2, std::vector<int>(2, 0));

    // act
    multiplyMatrices(A, B, C, 2, 3, 2);
    multiplyMatricesWithoutErrors(A, B, D, 2, 3, 2);
    std::vector<std::vector<int>> expected = {
        {0, 0},
        {0, 0}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationZeroMatricesTest, TestZeroMatrices3x2and2x3) {
    /**
     * Error 2: Matrix A contains the number 7!
     * Error 8: Result matrix contains zero!
     * Error 11: Every row in matrix B contains at least one '0'!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Expected equality of these values:
     * C
     *      Which is: { { 2047, 7, 8 }, { 6, 4, 6 }, { 7, 3, 10 } }
     * expected
     *      Which is: { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {7, 8},
        {9, 10},
        {11, 12}
    };
    std::vector<std::vector<int>> B = {
        {0, 0, 0},
        {0, 0, 0},    
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> D(3, std::vector<int>(3, 0));

    // act
    multiplyMatrices(A, B, C, 3, 2, 3);
    multiplyMatricesWithoutErrors(A, B, D, 3, 2, 3);
    std::vector<std::vector<int>> expected = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}




/************************
 * Identity Matrix Test *
 ************************/
TEST(MatrixMultiplicationIdentityMatricesTest, TestIdentityMatrices2x2and2x3) {
    /**
     * Error 1: Element-wise multiplication of ones detected!
     * Error 4: Matrix B contains the number 3!
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 13: The first element of matrix A is equal to the first element of matrix B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 16: Matrix B contains the number 6!
     * Error 18: Matrix A is a square matrix!
     * Expected equality of these values:
     * C
     *      Which is: { { 2077, 2, 10 }, { 4, 5, 20 } }
     * expected
     *      Which is: { { 1, 2, 3 }, { 4, 5, 6 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 0},
        {0, 1}
    };
    std::vector<std::vector<int>> B = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(3, 0));
    std::vector<std::vector<int>> D(2, std::vector<int>(3, 0));

    // act
    multiplyMatrices(A, B, C, 2, 2, 3);
    multiplyMatricesWithoutErrors(A, B, D, 2, 2, 3);
    std::vector<std::vector<int>> expected = {
        {1, 2, 3},
        {4, 5, 6}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationIdentityMatricesTest, TestIdentityMatrices3x3and3x4) {
    /**
     * Error 1: Element-wise multiplication of ones detected!
     * Error 4: Matrix B contains the number 3!
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 13: The first element of matrix A is equal to the first element of matrix B!
     * Error 16: Matrix B contains the number 6!
     * Error 18: Matrix A is a square matrix!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2047, 2, 10, 4 }, { 5, 6, 21, 8 }, { 9, 10, 21, 19 } }
     * expected
     *      Which is: { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    std::vector<std::vector<int>> B = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(4, 0));
    std::vector<std::vector<int>> D(3, std::vector<int>(4, 0));

    // act
    multiplyMatrices(A, B, C, 3, 3, 4);
    multiplyMatricesWithoutErrors(A, B, D, 3, 3, 4);
    std::vector<std::vector<int>> expected = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationIdentityMatricesTest, TestIdentityMatrices2x3and3x3) {
    /**
     * Error 1: Element-wise multiplication of ones detected!
     * Error 11: Every row in matrix B contains at least one '0'!
     * Error 13: The first element of matrix A is equal to the first element of matrix B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2078, 2, 3 }, { 4, 5, 6 } }
     * expected
     *      Which is: { { 1, 2, 3 }, { 4, 5, 6 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::vector<std::vector<int>> B = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(3, 0));
    std::vector<std::vector<int>> D(2, std::vector<int>(3, 0));

    // act
    multiplyMatrices(A, B, C, 2, 3, 3);
    multiplyMatricesWithoutErrors(A, B, D, 2, 3, 3);
    std::vector<std::vector<int>> expected = {
        {1, 2, 3},
        {4, 5, 6}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationIdentityMatricesTest, TestIdentityMatrices3x4and4x4) {
    /**
     * Error 1: Element-wise multiplication of ones detected!
     * Error 2: Matrix A contains the number 7!
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 11: Every row in matrix B contains at least one '0'!
     * Error 13: The first element of matrix A is equal to the first element of matrix B!
     * Expected equality of these values:
     * C
     *      Which is: { { 2047, 2, 3, 4 }, { 20, 16, 20, 11 }, { 9, 10, 11, 22 } }
     * expected
     *      Which is: { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };
    std::vector<std::vector<int>> B = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(4, 0));
    std::vector<std::vector<int>> D(3, std::vector<int>(4, 0));

    // act
    multiplyMatrices(A, B, C, 3, 4, 4);
    multiplyMatricesWithoutErrors(A, B, D, 3, 4, 4);
    std::vector<std::vector<int>> expected = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationIdentityMatricesTest, TestIdentityAnd25SquareMatrices) {
    /**
     * Error 1: Element-wise multiplication of ones detected!
     * Error 4: Matrix B contains the number 3!
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 9: Result matrix contains the number 99!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 16: Matrix B contains the number 6!
     * Error 17: Result matrix C contains the number 17!
     * Error 18: Matrix A is a square matrix!
     * Expected equality of these values:
     * C
     *      Which is: { { 0, 2020, 8, 11, 4, 0, 2006, 6, 8, 9, 0, 2048, 11, 16, 22, 0, 2052, 17, 25, 22, 0, 2015, 21, 23, 24, 0, 2052, 26, 28, 29, 0, 1987, ... } }
     * expected
     *      Which is: { { 0, 0, 1, 3, 4, 0, 5, 6, 8, 9, 0, 10, 11, 13, 14, 0, 15, 16, 18, 19, 0, 20, 21, 23, 24, 0, 25, 26, 28, 29, 0, 30, ... } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 0},
        {0, 1}
    };

    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> D(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> wrong_result(1, std::vector<int>(100, 0));
    std::vector<std::vector<int>> correct_result(1, std::vector<int>(100, 0));

    // act
    for (int i = 0; i < 100; i += 4) {
        std::vector<std::vector<int>> actual = {
            {i, ++i},
            {i+2, i+3}
        };
        multiplyMatrices(A, actual, C, 2, 2, 2);
        multiplyMatricesWithoutErrors(A, actual, D, 2, 2, 2);
        wrong_result[0][i]   = C[0][0];
        wrong_result[0][i+1] = C[0][1];
        wrong_result[0][i+2] = C[1][0];
        wrong_result[0][i+3] = C[1][1];
    
        correct_result[0][i]   = D[0][0];
        correct_result[0][i+1] = D[0][1];
        correct_result[0][i+2] = D[1][0];
        correct_result[0][i+3] = D[1][1];
    }

    // assert
    ASSERT_EQ(wrong_result, correct_result) << "Matrix multiplication test failed!";
}



/**********************
 * Square Matrix Test *
 **********************/
TEST(MatrixMultiplicationSquareMatricesTest, TestSquareZeroMatrices2x2) {
    /**
     * Error 4: Matrix B contains the number 3!
     * Error 8: Result matrix contains zero!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 18: Matrix A is a square matrix!
     * Expected equality of these values:
     * C
     *      Which is: { { 2071, 7 }, { 8, 6 } }
     * expected
     *      Which is: { { 0, 0 }, { 0, 0 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {0, 0},
        {0, 0}
    };
    std::vector<std::vector<int>> B = {
        {1, 2},
        {3, 4}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> D(2, std::vector<int>(2, 0));

    // act
    multiplyMatrices(A, B, C, 2, 2, 2);
    multiplyMatricesWithoutErrors(A, B, D, 2, 2, 2);
    std::vector<std::vector<int>> expected = {
        {0, 0},
        {0, 0}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSquareMatricesTest, TestSquareZeroMatrices2x2Reversed) {
    /**
     * Error 8: Result matrix contains zero!
     * Error 11: Every row in matrix B contains at least one '0'!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 18: Matrix A is a square matrix!
     * Expected equality of these values:
     * C
     *      Which is: { { 2077, 7 }, { 8, 6 } }
     * expected
     *      Which is: { { 0, 0 }, { 0, 0 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 2},
        {3, 4}
    };
    std::vector<std::vector<int>> B = {
        {0, 0},
        {0, 0}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> D(2, std::vector<int>(2, 0));

    // act
    multiplyMatrices(A, B, C, 2, 2, 2);
    multiplyMatricesWithoutErrors(A, B, D, 2, 2, 2);
    std::vector<std::vector<int>> expected = {
        {0, 0},
        {0, 0}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSquareMatricesTest, TestSquareZeroMatrices3x3) {
    /**
     * Error 4: Matrix B contains the number 3!
     * Error 8: Result matrix contains zero!
     * Error 11: Every row in matrix B contains at least one '0'!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 16: Matrix B contains the number 6!
     * Error 18: Matrix A is a square matrix!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2044, 7, 8 }, { 6, 4, 6 }, { 7, 3, 10 } }
     * expected
     *      Which is: { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    std::vector<std::vector<int>> B = {
        {1, 2, 0},
        {3, 4, 0},
        {5, 6, 0}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> D(3, std::vector<int>(3, 0));

    // act
    multiplyMatrices(A, B, C, 3, 3, 3);
    multiplyMatricesWithoutErrors(A, B, D, 3, 3, 3);
    std::vector<std::vector<int>> expected = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSquareMatricesTest, TestSquareZeroMatrices3x3Reversed) {
    /**
     * Error 8: Result matrix contains zero!
     * Error 11: Every row in matrix B contains at least one '0'!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 18: Matrix A is a square matrix!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2075, 7, 8 }, { 6, 4, 6 }, { 7, 3, 10 } }
     * expected
     *      Which is: { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 2, 0},
        {3, 4, 0},
        {5, 6, 0}
    };
    std::vector<std::vector<int>> B = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> D(3, std::vector<int>(3, 0));

    // act
    multiplyMatrices(A, B, C, 3, 3, 3);
    multiplyMatricesWithoutErrors(A, B, D, 3, 3, 3);
    std::vector<std::vector<int>> expected = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSquareMatricesTest, TestSquareMatrices2x2) {
    /**
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 16: Matrix B contains the number 6!
     * Error 18: Matrix A is a square matrix!
     * Expected equality of these values:
     * C
     *      Which is: { { 2078, 22 }, { 43, 50 } }
     * expected
     *      Which is: { { 19, 22 }, { 43, 50 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 2},
        {3, 4}
    };
    std::vector<std::vector<int>> B = {
        {5, 6},
        {7, 8}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> D(2, std::vector<int>(2, 0));

    // act
    multiplyMatrices(A, B, C, 2, 2, 2);
    multiplyMatricesWithoutErrors(A, B, D, 2, 2, 2);
    std::vector<std::vector<int>> expected = {
        {19, 22},
        {43, 50}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSquareMatricesTest, TestSquareMatrices2x2Reversed) {
    /**
     * Error 2: Matrix A contains the number 7!
     * Error 4: Matrix B contains the number 3!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 18: Matrix A is a square matrix!
     * Expected equality of these values:
     * C
     *      Which is: { { 2071, 34 }, { 46, 52 } }
     * expected
     *      Which is: { { 23, 34 }, { 31, 46 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {5, 6},
        {7, 8}
    };
    std::vector<std::vector<int>> B = {
        {1, 2},
        {3, 4}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> D(2, std::vector<int>(2, 0));

    // act
    multiplyMatrices(A, B, C, 2, 2, 2);
    multiplyMatricesWithoutErrors(A, B, D, 2, 2, 2);
    std::vector<std::vector<int>> expected = {
        {23, 34},
        {31, 46}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSquareMatricesTest, TestSquareMatrices3x3) {
    /**
     * Error 2: Matrix A contains the number 7!
     * Error 6: Result matrix contains a number bigger than 100!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 18: Matrix A is a square matrix!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2012, 90, 96 }, { 205, 223, 239 }, { 328, 355, 379 } }
     * expected
     *      Which is: { { 84, 90, 96 }, { 201, 216, 231 }, { 318, 342, 366 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::vector<std::vector<int>> B = {
        {10, 11, 12},
        {13, 14, 15},
        {16, 17, 18}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> D(3, std::vector<int>(3, 0));

    // act
    multiplyMatrices(A, B, C, 3, 3, 3);
    multiplyMatricesWithoutErrors(A, B, D, 3, 3, 3);
    std::vector<std::vector<int>> expected = {
        { 84,  90,  96},
        {201, 216, 231},
        {318, 342, 366}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSquareMatricesTest, TestSquareMatrices3x3Reversed) {
    /**
     * Error 4: Matrix B contains the number 3!
     * Error 6: Result matrix contains a number bigger than 100!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 16: Matrix B contains the number 6!
     * Error 18: Matrix A is a square matrix!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2011, 178, 218 }, { 178, 222, 268 }, { 220, 263, 323 } }
     * expected
     *      Which is: { { 138, 171, 204 }, { 174, 216, 258 }, { 210, 261, 312 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {10, 11, 12},
        {13, 14, 15},
        {16, 17, 18}
    };
    std::vector<std::vector<int>> B = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> D(3, std::vector<int>(3, 0));

    // act
    multiplyMatrices(A, B, C, 3, 3, 3);
    multiplyMatricesWithoutErrors(A, B, D, 3, 3, 3);
    std::vector<std::vector<int>> expected = {
        {138, 171, 204},
        {174, 216, 258},
        {210, 261, 312}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSquareMatricesTest, TestSquareIdentityMatrices2x2) {
    /**
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 16: Matrix B contains the number 6!
     * Error 18: Matrix A is a square matrix!
     * Expected equality of these values:
     * C
     *      Which is: { { 2000, 6 }, { 7, 8 } }
     * expected
     *      Which is: { { 5, 6 }, { 7, 8 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 0},
        {0, 1}
    };
    std::vector<std::vector<int>> B = {
        {5, 6},
        {7, 8}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> D(2, std::vector<int>(2, 0));

    // act
    multiplyMatrices(A, B, C, 2, 2, 2);
    multiplyMatricesWithoutErrors(A, B, D, 2, 2, 2);
    std::vector<std::vector<int>> expected = {
        {5, 6},
        {7, 8}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSquareMatricesTest, TestSquareIdentityMatrices2x2Reversed) {
    /**
     * Error 2: Matrix A contains the number 7!
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 11: Every row in matrix B contains at least one '0'!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 18: Matrix A is a square matrix!
     * Expected equality of these values:
     * C
     *      Which is: { { 2071, 6 }, { 11, 23 } }
     * expected
     *      Which is: { { 5, 6 }, { 7, 8 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {5, 6},
        {7, 8}
    };
    std::vector<std::vector<int>> B = {
        {1, 0},
        {0, 1}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> D(2, std::vector<int>(2, 0));

    // act
    multiplyMatrices(A, B, C, 2, 2, 2);
    multiplyMatricesWithoutErrors(A, B, D, 2, 2, 2);
    std::vector<std::vector<int>> expected = {
        {5, 6},
        {7, 8}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSquareMatricesTest, TestSquareIdentityMatrices3x3) {
    /**
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 18: Matrix A is a square matrix!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2006, 11, 16 }, { 20, 22, 21 }, { 20, 23, 25 } }
     * expected
     *      Which is: { { 10, 11, 12 }, { 13, 14, 15 }, { 16, 17, 18 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    std::vector<std::vector<int>> B = {
        {10, 11, 12},
        {13, 14, 15},
        {16, 17, 18}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> D(3, std::vector<int>(3, 0));

    // act
    multiplyMatrices(A, B, C, 3, 3, 3);
    multiplyMatricesWithoutErrors(A, B, D, 3, 3, 3);
    std::vector<std::vector<int>> expected = {
        {10, 11, 12},
        {13, 14, 15},
        {16, 17, 18}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSquareMatricesTest, TestSquareIdentityMatrices3x3Reversed) {
    /**
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 11: Every row in matrix B contains at least one '0'!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 18: Matrix A is a square matrix!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2047, 11, 16 }, { 20, 22, 21 }, { 20, 23, 25 } }
     * expected
     *      Which is: { { 10, 11, 12 }, { 13, 14, 15 }, { 16, 17, 18 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {10, 11, 12},
        {13, 14, 15},
        {16, 17, 18}
    };
    std::vector<std::vector<int>> B = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> D(3, std::vector<int>(3, 0));

    // act
    multiplyMatrices(A, B, C, 3, 3, 3);
    multiplyMatricesWithoutErrors(A, B, D, 3, 3, 3);
    std::vector<std::vector<int>> expected = {
        {10, 11, 12},
        {13, 14, 15},
        {16, 17, 18}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}




/***************
 * Vector Test *
 ***************/
TEST(MatrixMultiplicationVectorAndMatricesTest, TestVectors1x2and2x1) {
    /**
     * Error 4: Matrix B contains the number 3!
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Expected equality of these values:
     * C
     *      Which is: { { 2062 } }
     * expected
     *      Which is: { { 11 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 2}
    };
    std::vector<std::vector<int>> B = {
        {3}, 
        {4}
    };
    std::vector<std::vector<int>> C(1, std::vector<int>(1, 0));
    std::vector<std::vector<int>> D(1, std::vector<int>(1, 0));

    // act
    multiplyMatrices(A, B, C, 1, 2, 1);
    multiplyMatricesWithoutErrors(A, B, D, 1, 2, 1);
    std::vector<std::vector<int>> expected = {
        {11}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationVectorAndMatricesTest, TestVectors1x2and2x1Reversed) {
    /**
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2062, 6 }, { 4, 8 } }
     * expected
     *      Which is: { { 3, 6 }, { 4, 8 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {3}, 
        {4}
    };
    std::vector<std::vector<int>> B = {
        {1, 2}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> D(2, std::vector<int>(2, 0));

    // act
    multiplyMatrices(A, B, C, 2, 1, 2);
    multiplyMatricesWithoutErrors(A, B, D, 2, 1, 2);
    std::vector<std::vector<int>> expected = {
        {3, 6},
        {4, 8}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationVectorAndMatricesTest, TestVectors1x3and3x1) {
    /**
     * Error 4: Matrix B contains the number 3!
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2000 } }
     * expected
     *      Which is: { { 14 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {0, 1, 2}
    };
    std::vector<std::vector<int>> B = {
        {3}, 
        {4},
        {5}
    };
    std::vector<std::vector<int>> C(1, std::vector<int>(1, 0));
    std::vector<std::vector<int>> D(1, std::vector<int>(1, 0));

    // act
    multiplyMatrices(A, B, C, 1, 3, 1);
    multiplyMatricesWithoutErrors(A, B, D, 1, 3, 1);
    std::vector<std::vector<int>> expected = {
        {14}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationVectorAndMatricesTest, TestVectors1x3and3x1Reversed) {
    /**
     * Error 8: Result matrix contains zero!
     * Error 11: Every row in matrix B contains at least one '0'!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 15: A row in matrix A is filled entirely with 5s!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2071, 3, 6 }, { 7, 4, 8 }, { 8, 5, 10 } }
     * expected
     *      Which is: { { 0, 3, 6 }, { 0, 4, 8 }, { 0, 5, 10 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {3}, 
        {4},
        {5}
    };
    std::vector<std::vector<int>> B = {
        {0, 1, 2}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> D(3, std::vector<int>(3, 0));

    // act
    multiplyMatrices(A, B, C, 3, 1, 3);
    multiplyMatricesWithoutErrors(A, B, D, 3, 1, 3);
    std::vector<std::vector<int>> expected = {
        {0, 3,  6},
        {0, 4,  8},
        {0, 5, 10}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationVectorAndMatricesTest, TestVectorAndMatrices1x2and2x4) {
    /**
     * Error 4: Matrix B contains the number 3!
     * Error 16: Matrix B contains the number 6!
     * Expected equality of these values:
     * C
     *      Which is: { { 2071, 20, 23, 26 } }
     * expected
     *      Which is: { { 17, 20, 23, 26 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 2}
    };
    std::vector<std::vector<int>> B = {
        {3, 4, 5, 6}, 
        {7, 8, 9, 10}
    };
    std::vector<std::vector<int>> C(1, std::vector<int>(4, 0));
    std::vector<std::vector<int>> D(1, std::vector<int>(4, 0));

    // act
    multiplyMatrices(A, B, C, 1, 2, 4);
    multiplyMatricesWithoutErrors(A, B, D, 1, 2, 4);
    std::vector<std::vector<int>> expected = {
        {17, 20, 23, 26}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationVectorAndMatricesTest, TestVectorAndMatrices1x3and3x4) {
    /**
     * Error 4: Matrix B contains the number 3!
     * Error 16: Matrix B contains the number 6!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2062, 56, 62, 68 } }
     * expected
     *      Which is: { { 50, 56, 62, 68 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 2, 3}
    };
    std::vector<std::vector<int>> B = {
        { 3,  4,  5,  6}, 
        { 7,  8,  9, 10},
        {11, 12, 13, 14}
    };
    std::vector<std::vector<int>> C(1, std::vector<int>(4, 0));
    std::vector<std::vector<int>> D(1, std::vector<int>(4, 0));

    // act
    multiplyMatrices(A, B, C, 1, 3, 4);
    multiplyMatricesWithoutErrors(A, B, D, 1, 3, 4);
    std::vector<std::vector<int>> expected = {
        {50, 56, 62, 68}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}




/******************************
 * Single Element Matrix Test *
 ******************************/
TEST(MatrixMultiplicationSingleElementMatricesTest, TestSingleElementOne) {
    /**
     * Error 1: Element-wise multiplication of ones detected!
     * Error 4: Matrix B contains the number 3!
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 8: Result matrix contains zero!
     * Error 9: Result matrix contains the number 99!
     * Error 11: Every row in matrix B contains at least one '0'!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 13: The first element of matrix A is equal to the first element of matrix B!
     * Error 16: Matrix B contains the number 6!
     * Error 18: Matrix A is a square matrix!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2078, 2006, 2075, 2011, 1996, 2014, 2008, 2014, 2043, 2078, 2027, 2006, 2083, 1998, 2041, 2081, 2069, 2031, 2009, 1999, 2049, 2072, 2063, 1988, 2084, 2061, 1997, 2079, 2055, 2052, 1987, 2037, ... } }
     * expected
     *      Which is: { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, ... } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1}
    };
    std::vector<std::vector<int>> C(1, std::vector<int>(1, 0));
    std::vector<std::vector<int>> D(1, std::vector<int>(1, 0));
    std::vector<std::vector<int>> wrong_result(1, std::vector<int>(100, 0));
    std::vector<std::vector<int>> correct_result(1, std::vector<int>(100, 0));

    // act
    for (int i = 0; i < 100; ++i) {
        std::vector<std::vector<int>> actual = {{i}};
        multiplyMatrices(A, actual, C, 1, 1, 1);
        multiplyMatricesWithoutErrors(A, actual, D, 1, 1, 1);
        wrong_result[0][i] = C[0][0];
        correct_result[0][i] = D[0][0];
    }

    // assert
    ASSERT_EQ(wrong_result, correct_result) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSingleElementMatricesTest, TestSingleElementZero) {
    /** 
     * Error 4: Matrix B contains the number 3!
     * Error 8: Result matrix contains zero!
     * Error 11: Every row in matrix B contains at least one '0'!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 13: The first element of matrix A is equal to the first element of matrix B!
     * Error 18: Matrix A is a square matrix!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2020, 2006, 2044, 2011, 2053, 2015, 2014, 2054, 1996, 2006, 2083, 1998, 2041, 2081, 2069, 2031, 2009, 1999, 2028, 2061, 1988, 2017, 2024, 2079, 2019, 2082, 2037, 2071, 2029, 2016, 2066, 2052, ... } }
     * expected
     *      Which is: { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ... } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {0}
    };
    std::vector<std::vector<int>> C(1, std::vector<int>(1, 0));
    std::vector<std::vector<int>> D(1, std::vector<int>(1, 0));
    std::vector<std::vector<int>> wrong_result(1, std::vector<int>(100, 0));
    std::vector<std::vector<int>> correct_result(1, std::vector<int>(100, 0));

    // act
    for (int i = 0; i < 100; ++i) {
        std::vector<std::vector<int>> actual = {{i}};
        multiplyMatrices(A, actual, C, 1, 1, 1);
        multiplyMatricesWithoutErrors(A, actual, D, 1, 1, 1);
        wrong_result[0][i] = C[0][0];
        correct_result[0][i] = D[0][0];
    }

    // assert
    ASSERT_EQ(wrong_result, correct_result) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationSingleElementMatricesTest, TestSingleElementAndVectors) {
    /**
     * Error 4: Matrix B contains the number 3!
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 15: A row in matrix A is filled entirely with 5s!
     * Error 16: Matrix B contains the number 6!
     * Error 18: Matrix A is a square matrix!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2020, 10, 26, 20, 25, 30, 35, 40, 45, 50 } }
     * expected
     *      Which is: { { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {5}
    };
    std::vector<std::vector<int>> B = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    };
    std::vector<std::vector<int>> C(1, std::vector<int>(10, 0));
    std::vector<std::vector<int>> D(1, std::vector<int>(10, 0));

    // act
    multiplyMatrices(A, B, C, 1, 1, 10);
    multiplyMatricesWithoutErrors(A, B, D, 1, 1, 10);
    std::vector<std::vector<int>> expected = {
        {5, 10, 15, 20, 25, 30, 35, 40, 45, 50}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}



/*************************
 * Negative Numbers Test *
 *************************/
TEST(MatrixMultiplicationNegativeNumbersTest, TestNegativeSingleElementAndVectors) {
    /**
     * Error 3: Matrix A contains a negative number!
     * Error 5: Matrix B contains a negative number!
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 18: Matrix A is a square matrix!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2052, 20, 28, 33, 30, 39, 49, 48, 55, 59 } }
     * expected
     *      Which is: { { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {-5}
    };
    std::vector<std::vector<int>> B = {
        {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10}
    };
    std::vector<std::vector<int>> C(1, std::vector<int>(10, 0));
    std::vector<std::vector<int>> D(1, std::vector<int>(10, 0));

    // act
    multiplyMatrices(A, B, C, 1, 1, 10);
    multiplyMatricesWithoutErrors(A, B, D, 1, 1, 10);
    std::vector<std::vector<int>> expected = {
        {5, 10, 15, 20, 25, 30, 35, 40, 45, 50}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}


TEST(MatrixMultiplicationNegativeNumbersTest, TestNegativeSquareMatrixAndIdentityMatrix) {
    /**
     * Error 1: Element-wise multiplication of ones detected!
     * Error 2: Matrix A contains the number 7!
     * Error 3: Matrix A contains a negative number!
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 11: Every row in matrix B contains at least one '0'!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 13: The first element of matrix A is equal to the first element of matrix B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 18: Matrix A is a square matrix!
     * Expected equality of these values:
     * C
     *      Which is: { { 2052, 20, 28, 33, 30, 39, 49, 48, 55, 59 } }
     * expected
     *      Which is: { { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {  1, -2,  3, -4},
        { -5,  6,  7,  8},
        {  9, -4,  4,  2},
        { -1,  1,  0,  2}
    };
    std::vector<std::vector<int>> B = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    std::vector<std::vector<int>> C(4, std::vector<int>(4, 0));
    std::vector<std::vector<int>> D(4, std::vector<int>(4, 0));

    // act
    multiplyMatrices(A, B, C, 4, 4, 4);
    multiplyMatricesWithoutErrors(A, B, D, 4, 4, 4);
    std::vector<std::vector<int>> expected = {
        {  1, -2,  3, -4},
        { -5,  6,  7,  8},
        {  9, -4,  4,  2},
        { -1,  1,  0,  2}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}



/*********************
 * Matrix Properties *
**********************/
TEST(MatrixMultiplicationPropertiesTest, TestNonCommutativity) {
    /**
     * Error 4: Matrix B contains the number 3!
     * Error 7: Result matrix contains a number between 11 and 20!
     * Error 10: A row in matrix A contains more than one '1'!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 15: A row in matrix A is filled entirely with 5s!
     * Error 16: Matrix B contains the number 6!
     * Error 18: Matrix A is a square matrix!
     * Error 20: Number of columns in matrix A is odd!
     * Expected equality of these values:
     * C
     *      Which is: { { 2077, 22, 23 }, { 30, 30, 30 }, { 45, 45, 45 } }
     * expected
     *      Which is: { { 15, 15, 15 }, { 30, 30, 30 }, { 45, 45, 45 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 1, 1},
        {2, 2, 2},
        {3, 3, 3}
    };
    std::vector<std::vector<int>> B = {
        {4, 4, 4},
        {5, 5, 5},
        {6, 6, 6}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> D(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> E(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> F(3, std::vector<int>(3, 0));

    // act
    multiplyMatrices(A, B, C, 3, 3, 3);
    multiplyMatrices(B, A, E, 3, 3, 3);
    multiplyMatricesWithoutErrors(A, B, D, 3, 3, 3);
    multiplyMatricesWithoutErrors(B, A, F, 3, 3, 3);
    std::vector<std::vector<int>> expected = {
        {15, 15, 15},
        {30, 30, 30},
        {45, 45, 45}
    };
    std::vector<std::vector<int>> expected_invert = {
        {24, 24, 24},
        {30, 30, 30},
        {36, 36, 36}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
    ASSERT_EQ(F, expected_invert) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(E, expected_invert) << "Matrix multiplication test failed!";
}


/********************
 * High Values Test *
*********************/
TEST(MatrixMultiplicationHighValuesTest, Test10x10Matrices) {
    /**
     * Error 1: Element-wise multiplication of ones detected!
     * Error 2: Matrix A contains the number 7!
     * Error 4: Matrix B contains the number 3!
     * Error 6: Result matrix contains a number bigger than 100!
     * Error 12: The number of rows in A is equal to the number of columns in B!
     * Error 13: The first element of matrix A is equal to the first element of matrix B!
     * Error 14: The result matrix C has an even number of rows!
     * Error 16: Matrix B contains the number 6!
     * Error 18: Matrix A is a square matrix!
     * Error 19: Every row in matrix A contains the number 8!
     * Expected equality of these values:
     * C
     *      Which is: { { 1992, 124, 230, 228, 285, 341, 403, 444, 502, 564 }, { 68, 122, 238, 234, 282, 341, 388, 451, 499, 559 }, { 67, 123, 240, 230, 280, 347, 401, 454, 501, 565 }, { 59, 126, 238, 231, 286, 340, 388, 449, 511, 565 }, { 66, 120, 241, 231, 290, 341, 398, 454, 505, 565 }, { 66, 121, 233, 225, 285, 340, 400, 446, 509, 567 }, { 60, 127, 247, 226, 294, 342, 393, 453, 503, 564 }, { 73, 128, 220, 236, 287, 343, 393, 456, 506, 561 }, { 67, 124, 214, 228, 287, 339, 401, 452, 508, 558 }, { 63, 123, 210, 232, 292, 344, 398, 447, 509, 556 } }
     * expected
     *      Which is: { { 55, 110, 165, 220, 275, 330, 385, 440, 495, 550 }, { 55, 110, 165, 220, 275, 330, 385, 440, 495, 550 }, { 55, 110, 165, 220, 275, 330, 385, 440, 495, 550 }, { 55, 110, 165, 220, 275, 330, 385, 440, 495, 550 }, { 55, 110, 165, 220, 275, 330, 385, 440, 495, 550 }, { 55, 110, 165, 220, 275, 330, 385, 440, 495, 550 }, { 55, 110, 165, 220, 275, 330, 385, 440, 495, 550 }, { 55, 110, 165, 220, 275, 330, 385, 440, 495, 550 }, { 55, 110, 165, 220, 275, 330, 385, 440, 495, 550 }, { 55, 110, 165, 220, 275, 330, 385, 440, 495, 550 } }
     * Matrix multiplication test failed!
    */
    // arrange
    std::vector<std::vector<int>> A = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    };
    std::vector<std::vector<int>> B = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    };
    std::vector<std::vector<int>> C(10, std::vector<int>(10, 0));
    std::vector<std::vector<int>> D(10, std::vector<int>(10, 0));

    // act
    multiplyMatrices(A, B, C, 10, 10, 10);
    multiplyMatricesWithoutErrors(A, B, D, 10, 10, 10);
    std::vector<std::vector<int>> expected = {
        {55, 110, 165, 220, 275, 330, 385, 440, 495, 550},
        {55, 110, 165, 220, 275, 330, 385, 440, 495, 550},
        {55, 110, 165, 220, 275, 330, 385, 440, 495, 550},
        {55, 110, 165, 220, 275, 330, 385, 440, 495, 550},
        {55, 110, 165, 220, 275, 330, 385, 440, 495, 550},
        {55, 110, 165, 220, 275, 330, 385, 440, 495, 550},
        {55, 110, 165, 220, 275, 330, 385, 440, 495, 550},
        {55, 110, 165, 220, 275, 330, 385, 440, 495, 550},
        {55, 110, 165, 220, 275, 330, 385, 440, 495, 550},
        {55, 110, 165, 220, 275, 330, 385, 440, 495, 550}
    };

    // assert
    ASSERT_EQ(D, expected) << "Matrix multiplication test failed! "
                              "It's the algorithm given by the professor, "
                              "maybe the test contains an error...";
    ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
