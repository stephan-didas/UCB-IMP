// Copyright (c) 2015, Patrick Scheid, Axel Ohlmann, Stephan Didas

#include <datacube.h>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::out_of_range;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::is_permutation;
using ucbimp::DataCube;

/**
 * Check if data is write and readable.
 */
TEST(DATACUBE_TEST, Set_And_Read_Data) {


    // Set dimension size
    size_t dim_size = 10;

    // Create data cube and fill it.
    // Additionally check if data is readable.
    int counter = 0;
    DataCube<int, 3> dc({dim_size, dim_size, dim_size});
    for (size_t i = 0; i < dim_size; ++i)
        for (size_t j = 0; j < dim_size; ++j)
            for (size_t k = 0; k < dim_size; ++k) {
                dc.at({k, j, i}) = counter;
                ASSERT_EQ(dc.at({k, j, i}), counter);
                counter++;
            }
}


/**
 * Check for out of range checking of at function (accomplished through vector<>)
 */
TEST(DATACUBE_TEST, OutOfRange_Checking) {
    // Create data cube
    DataCube<int, 1> dc({10});

    // Check a simple case (5) and edge cases
    ASSERT_NO_THROW(dc.at({0}));
    ASSERT_NO_THROW(dc.at({5}));
    ASSERT_NO_THROW(dc.at({9}));

    // Make sure the inner vectors range check
    // is throwing out_of_range exception
    ASSERT_THROW(dc.at({10}), out_of_range);
}


/**
 * Checking if index transformation leads to correct inner memory management
 */
TEST(DATACUBE_TEST, Positional_Random_Check) {
    // Setting dimension sizes
    size_t size = 10;
    size_t ext = size * size * size;

    // Initializing random generator and uniform distribution
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1, 100);

    // Creating data structures
    vector<int> data(0);
    DataCube<int, 3> dc({size, size, size});

    // Filling check list and data cube with random numbers
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            for (size_t k = 0; k < size; ++k) {
                int val = distribution(generator);
                data.push_back(val);
                dc.at({k, j, i}) = val;
            }
        }
    }

    // Check if both contain the self numbers (nothing is lost)
    ASSERT_TRUE(
            is_permutation(
                    begin(dc.innerData()), end(dc.innerData()), begin(data)));
}

/**
 * Checking overwritten equal and not equal operators (== and !=)
 */
TEST(DATACUBE_TEST, Equal_NotEqual) {
    // Create two equal instances
    DataCube<int, 2> dc1({10, 10});
    DataCube<int, 2> dc2({10, 10});

    // Check, that they are equal and not not_equal.
    ASSERT_TRUE(dc1 == dc2);
    ASSERT_FALSE(dc1 != dc2);

    /* @TODO: Compiler error, but would be great to catch different dimension in this test.
    // Check that different dimension is detected
    DataCube<int, 3> dc_diff_dim({10, 10, 10});
    ASSERT_FALSE(dc1 == dc_diff_dim);
    ASSERT_TRUE( (dc1 != dc_diff_dim) );
    */

    // Check that different sizes are detected
    // Therefore, create new instance with different sizes
    DataCube<int, 2> dc_diff_size({23, 23});
    ASSERT_FALSE(dc1 == dc_diff_size);
    ASSERT_TRUE(dc1 != dc_diff_size);

    // Check that different elements are detected
    // Therefore, change one element in dc2
    dc2.at({1, 1}) = 999;
    ASSERT_FALSE(dc1 == dc2);
    ASSERT_TRUE(dc1 != dc2);
}

/**
 * Checking implicit copy constructor
 */
TEST(DATACUBE_TEST, CopyConstructor) {
    // Create a DataCube with values and copy it
    DataCube<int, 2> dc_original({3, 3}, {1, 2, 3, 10, 20, 30, 100, 200, 300});
    DataCube<int, 2> dc_copy(dc_original);

    // Check equality
    ASSERT_TRUE(dc_original == dc_copy);

    // Change element and check inequality (real copy)
    dc_copy.at({1, 1}) = 999;
    ASSERT_FALSE(dc_original == dc_copy);
}

/**
 * Checking implicit assignment operator (=)
 */
TEST(DATACUBE_TEST, AssignmentCheck) {
    // Create datacube with values and assignt it to dc_copy
    DataCube<int, 2> dc_original({3, 3}, {1, 2, 3, 10, 20, 30, 100, 200, 300});
    DataCube<int, 2> dc_copy = dc_original;

    // Check equallity
    ASSERT_TRUE(dc_original == dc_copy);

    // Change one element. This is a check for real copy
    // and no "just reference assignment"
    dc_copy.at({1, 2}) = 999;
    ASSERT_FALSE(dc_original == dc_copy);
}
