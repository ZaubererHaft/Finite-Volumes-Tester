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


#ifndef FVM_VISUALIZER_H
#define FVM_VISUALIZER_H

#include <cstddef>

template<size_t L>
class Visualizer {
public:
    virtual void visualize(double time, const std::vector<Cell<L>> &currCells) const = 0;
};

#endif //FVM_VISUALIZER_H
/**
* \}
* \}
*/
