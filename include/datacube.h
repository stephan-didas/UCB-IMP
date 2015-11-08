// Copyright (c) 2015, Patrick Scheid, Axel Ohlmann, Stephan Didas

#ifndef INCLUDE_DATACUBE_H_
#define INCLUDE_DATACUBE_H_

#include <array>
#include <vector>
#include <algorithm>

using std::array;
using std::vector;
using std::copy;

namespace ucbimp {

template<typename T, size_t DIM>
class DataCube;

/**
 *  \class      DataCube
 *  \brief      Generic class for n-dimensional data container.
 *
 *  Generic data container for multi dimensional data.
 *  It is intended to be a common ancestor for data types like signals or matrices.
 *
 *  \tparam     T   Datatype for the inner data container.
 *  \tparam     DIM Number of different dimensions of the date container.
 *
 *  \note       This class should not be used directly, only as parent.
 *
 *  \copyright  Copyright (c) 2015, Patrick Scheid, Axel Ohlmann, Stephan Didas
 *  \author     Patrick Scheid
 *  \version    0.1
 *  \date       30.10.2015
 */
template<typename T, size_t DIM>
class DataCube {
 public:
    // Constructors & Destructor
    explicit DataCube(array<size_t, DIM> sizes);
    DataCube(array<size_t, DIM> sizes, vector<T> values);
    virtual ~DataCube();

    // Accessors & Mutators
    inline size_t getDimension() const;
    inline array<size_t, DIM> getSize() const;
    inline vector<T> &innerData();

    // Overloaded Operators
    inline bool operator==(const DataCube &other);
    inline bool operator!=(const DataCube &other);

    // Methods
    T &at(array<size_t, DIM> indices);

 protected:
    // Methods
    size_t transformIndices(array<size_t, DIM> indices);

 private:
    // Member variables
    size_t dimension;
    array<size_t, DIM> size;
    array<size_t, DIM> coefs;
    vector<T> data;
};

/**
 *  \brief  Creates n-dimensional data container.
 *  \param  sizes   Multiple size specifications, one for each dimension.
 */
template<typename T, size_t DIM>
DataCube<T, DIM>::DataCube(array<size_t, DIM> sizes) : dimension(DIM),
                                                       size(sizes) {
    // Calculate access coefficients
    size_t temp_coef = 1;
    for (int i = 0; i < dimension; ++i) {
        coefs[i] = temp_coef;
        temp_coef *= size[i];
    }

    // Initialize vector to right size for data
    this->data = vector<T>(temp_coef);
}

/**
 *  \brief  Creates n-dimensional data container filled with given data.
 *  \param  sizes   Multiple size specifications, one for each dimension.
 *  \param  values  Values which should be stored in data container.
 */
template<typename T, size_t DIM>
DataCube<T, DIM>::DataCube(array<size_t, DIM> sizes, vector<T> values) :
        DataCube(sizes) {
    copy(begin(values), end(values), begin(data));
}

/**
 * \brief   Empty virtual destructor.
 */
template<typename T, size_t DIM>
DataCube<T, DIM>::~DataCube() {
    // Empty
}

/**
 * \brief   Get dimension of data cube.
 * \return  Dimension of data cube.
 */
template<typename T, size_t DIM>
size_t DataCube<T, DIM>::getDimension() const {
    return this->dimension;
}


/**
 * \brief   Get sizes of different dimensions.
 * \return  Array of type size_t and length DIM containing sizes.
 */
template<typename T, size_t DIM>
array<size_t, DIM> DataCube<T, DIM>::getSize() const {
    return this->size;
}

/**
 * \brief   Returns reference to inner data container.
 * \return  Reference to inner vector.
 */
template<typename T, size_t DIM>
vector<T> &DataCube<T, DIM>::innerData() {
    return this->data;
}

/**
 * \brief   Returns values specified by multiple indices.
 * \param   indices Array with multiple indices, one for each dimension.
 * \return  Reference to specified value element.
 */
template<typename T, size_t DIM>
T &DataCube<T, DIM>::at(array<size_t, DIM> indices) {
    size_t transformedIndex = transformIndices(indices);
    return data.at(transformedIndex);
}

/**
 * \brief   Compares two DataCube objects for equality.
 * \param   other   DataCube to check against.
 * \return  Flag indicating equality.
 */
template<typename T, size_t DIM>
bool DataCube<T, DIM>::operator==(const DataCube &other) {
    bool isEqual = true;
    isEqual &= (this->dimension == other.dimension);
    isEqual &= (this->size == other.size);
    isEqual &= (this->coefs == other.coefs);
    isEqual &= (this->data == other.data);
    return isEqual;
}

/**
 * \brief   Compares two DataCube objects for inequality.
 * \param   other   Datacube to check against.
 * \return  Flag indicating inequality.
 */
template<typename T, size_t DIM>
bool DataCube<T, DIM>::operator!=(const DataCube &other) {
    return !this->operator==(other);
}

/**
 * \brief   Transforms given indices to single index for one-dimensional memory layout.
 * \param   indices determines certain data point in n-dimensional data container.
 * \return  Singel index for position of searched data point in one-dimensional memory.
 */
template<typename T, size_t DIM>
size_t DataCube<T, DIM>::transformIndices(array<size_t, DIM> indices) {
    size_t inner_index = 0;
    for (int i = 0; i < DIM; ++i)
        inner_index += (indices.at(i) * coefs.at(i));
    return inner_index;
}

}  // namespace ucbimp

#endif  // INCLUDE_DATACUBE_H_
