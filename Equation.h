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


#ifndef FVM_EQUATION_H
#define FVM_EQUATION_H

#include <cstdint>
#include <array>
#include "Cell.h"
#include "InitialValues.h"
#include "Fluxes.h"
#include "BoundaryConditions.h"

template<size_t L = 1>
class Equation {

public:
    Equation(const Domain &dom, BoundaryConditions<L> *bc, InitialValues<L> *iv, Fluxes<L> *fl) : domain{dom}, bcs{bc}, ivs{iv}, fluxes{fl} {
    }

    std::array<double, L> getInitialValues(double x) const {
        return ivs->getInitialValues(x);
    }

    std::array<double, L> getFlux(double x, const std::array<double, L> &q) const{
        return fluxes->getFlux(x, q);
    }

    std::array<double, L> getEigenvalues(const std::array<double, L> &q) const {
        return fluxes->getEigenvalues(q);
    }

    Cell<L> leftBoundary(const Cell<L> &inner) const {
        return bcs->leftBoundary(inner);
    }

    Cell<L> rightBoundary(Cell<L> &inner) const {
        return bcs->rightBoundary(inner);
    }

    const Domain &getDomain() const {
        return domain;
    }

private:
    Domain domain;
    BoundaryConditions<L> *bcs;
    InitialValues<L> *ivs;
    Fluxes<L> *fluxes;
};


#endif //FVM_EQUATION_H

/**
* \}
* \}
*/