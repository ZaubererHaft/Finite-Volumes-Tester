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


#ifndef FVM_SIMULATION_H
#define FVM_SIMULATION_H


#include <list>
#include <vector>
#include <utility>
#include <fstream>
#include <valarray>
#include "Domain.h"
#include "Cell.h"
#include "Equation.h"
#include "NumericalFlux.h"
#include "Visualizer.h"
#include "Discretizer.h"

template<size_t L = 1>
class Simulation {
public:
    explicit Simulation(const Equation<L> &equation, const NumericalFlux<L> *numericalFlux,
                        const Visualizer<L> *vis)
            : equation(equation), numericalFlux{numericalFlux}, visualizer{vis},
              dt{0.001}, visualizeEvery(10) {

    }

    void prepare(const Discretizer<L> *discretizer) {
        _currCells = discretizer->Discretize(equation);
        _nextCells = std::vector<Cell<L>>(_currCells.size(), {0, 0});
        visualizer->visualize(0.0, _currCells);
    }

    void Run(double end_time) {
        int counter = 0;

        double t = dt;
        while (t < end_time) {
            counter++;
            for (int i = 0; i < _currCells.size(); i++) {
                Cell<L> left{0, 0};
                Cell<L> middle{0, 0};
                Cell<L> right{0, 0};

                if (i == 0) {
                    right = _currCells[1];
                    middle = _currCells[0];
                    left = equation.leftBoundary(middle);
                } else if (i == _currCells.size() - 1) {
                    left = _currCells[_currCells.size() - 2];
                    middle = _currCells[_currCells.size() - 1];
                    right = equation.rightBoundary(middle);
                } else {
                    left = _currCells[i - 1];
                    middle = _currCells[i];
                    right = _currCells[i + 1];
                }

                auto cell = step(left, middle, right);
                _nextCells[i] = cell;
            }

            _currCells = _nextCells;

            if (counter == visualizeEvery) {
                visualizer->visualize(t, _currCells);
                counter = 0;
            }

            t += dt;
        }

        visualizer->visualize(t, _currCells);
    }

    Cell<L> step(const Cell<L> &left, const Cell<L> &middle, const Cell<L> &right) {
        auto fluxIn = numericalFlux->getNumericalFluxes(left, middle);
        auto fluxOut = numericalFlux->getNumericalFluxes(middle, right);
        Cell<L> cell(middle);

        for (size_t i = 0U; i < L; ++i) {
            auto q = middle[i];
            cell.set(i, q - (dt / cell.getSize()) * (fluxOut[i] - fluxIn[i]));
        }
        return cell;
    }


private:
    Equation<L> equation;
    const NumericalFlux<L> *numericalFlux;
    const Visualizer<L> *visualizer;
    std::vector<Cell<L>> _currCells;
    std::vector<Cell<L>> _nextCells;
    double dt;
    int visualizeEvery;
};


#endif //FVM_SIMULATION_H

/**
* \}
* \}
*/