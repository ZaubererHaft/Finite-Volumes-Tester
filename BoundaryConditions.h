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


#ifndef FVM_BOUNDARYCONDITIONS_H
#define FVM_BOUNDARYCONDITIONS_H

template<size_t L = 1>
class BoundaryConditions {
public:

    virtual Cell<L> leftBoundary(const Cell<L> &inner) = 0;

    virtual Cell<L> rightBoundary(const Cell<L> &inner) = 0;
};

template<size_t L = 1>
class OutflowBoundaryConditions : public BoundaryConditions<L> {
public:

    Cell<L> leftBoundary(const Cell<L> &inner) override {
        Cell<L> c{inner};
        c.setValues(inner.getValues());
        return c;
    }

    Cell<L> rightBoundary(const Cell<L> &inner) override {
        Cell<L> c{inner};
        c.setValues(inner.getValues());
        return c;
    }
};

class ReflectingBoundaryConditions : public BoundaryConditions<3U> {
public:

    Cell<3U> leftBoundary(const Cell<3> &inner) override {
        Cell<3U> c{inner};
        c.setValues(
                {
                        inner[0U],
                        -inner[1U],
                        inner[2U]
                }
        );
        return c;
    }

    Cell<3U> rightBoundary(const Cell<3> &inner) override {
        Cell<3U> c{inner};
        c.setValues(
                {
                        inner[0U],
                        -inner[1U],
                        inner[2U]
                }
        );
        return c;
    }
};

class NoSlipBoundaryConditions : public BoundaryConditions<3U> {
public:

    Cell<3U> leftBoundary(const Cell<3> &inner) override {
        Cell<3U> c{inner};
        c.setValues(
                {
                        inner[0U],
                        0,
                        inner[2U]
                }
        );
        return c;
    }

    Cell<3U> rightBoundary(const Cell<3> &inner) override {
        Cell<3U> c{inner};
        c.setValues(
                {
                        inner[0U],
                        0,
                        inner[2U]
                }
        );
        return c;
    }
};
#endif //FVM_BOUNDARYCONDITIONS_H

/**
* \}
* \}
*/