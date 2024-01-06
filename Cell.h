/**
 * \file
 * \{
 * \defgroup 
 * \{
 * \ingroup  
 * \brief    
 * \details  
 *
 * \author   l.kratzl
 */

#ifndef FVM_CELL_H
#define FVM_CELL_H

#include <cstdint>
#include <array>
#include <cstring>

template<size_t L = 1>
class Cell {
public:
    Cell(double xStart, double xEnd) : values{0U}, center{0.5 * (xEnd + xStart)}, size{xEnd - xStart}, xStart{xStart}, xEnd{xEnd} {

    }

    void setValues(const std::array<double, L> &arg_values) {
        for (size_t i = 0U; i < L; ++i) {
            values[i] = arg_values[i];
        }
    }

    double operator[](size_t index) const {
        return values[index];
    }

    std::array<double, L> getValues() const {
        return values;
    }

    void set(size_t index, double value) {
        values[index] = value;
    }

    double at(size_t i) const {
        return values[i];
    }

    double getCenter() const {
        return center;
    }

    double getSize() const {
        return size;
    }

    double getXStart() const {
        return xStart;
    }

    double getXEnd() const {
        return xEnd;
    }

private:
    std::array<double, L> values;
    double center;
    double size;
    double xStart;
    double xEnd;
};


#endif //FVM_CELL_H

/**
* \}
* \}
*/
