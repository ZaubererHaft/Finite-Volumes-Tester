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

#ifndef FVM_DISCRETIZER_H
#define FVM_DISCRETIZER_H

template<size_t L = 1>
class Discretizer {
public:
    virtual std::vector<Cell<L>> Discretize(const Equation<L> &eq) const = 0;
};

template<size_t L = 1>
class EquidistantDiscretizer : public Discretizer<L> {
public:
    explicit EquidistantDiscretizer(double dx) : dx(dx) {}

    virtual std::vector<Cell<L>> Discretize(const Equation<L> &eq) const override {
        std::vector<Cell<L>> cells;

        double i = 0.0;
        double start;
        double end;

        do {
            start = eq.getDomain().getXStart() + i * dx;
            end = eq.getDomain().getXStart() + (i + 1.0) * dx;
            if (end > eq.getDomain().getXEnd()) {
                end = eq.getDomain().getXEnd();
            }

            Cell<L> cell{start, end};
            cell.setValues(eq.getInitialValues(cell.getCenter()));
            cells.emplace_back(cell);
            i++;
        } while (end < eq.getDomain().getXEnd());

        return cells;
    }

private:
    double dx;
};

#endif //FVM_DISCRETIZER_H

/**
* \}
* \}
*/
