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


#ifndef FVM_INITIALVALUES_H
#define FVM_INITIALVALUES_H

template<size_t L = 1>
class InitialValues {
public:
    virtual std::array<double, L> getInitialValues(double x) const = 0;
};

class LakeAtRestScenario : public InitialValues<3U> {
public:
    std::array<double, 3U> getInitialValues(double x) const override {
        std::array<double, 3U> values{0.0, 0.0, 0.0};
        auto eta = 0.75;
        auto b = 0.1 + std::max(0.0, 0.5 * x);

        values[0U] = std::max(0.0, eta - b);
        values[2U] = b;
        return values;
    }
};

class DambreakScenario : public InitialValues<3U> {
public:
    std::array<double, 3U> getInitialValues(double x) const override {
        std::array<double, 3U> values{0.0, 0.0, 0.1};
        if (x < 0.0) {
            values[0U] = 1.0;
        } else {
            values[0U] = 0.5;
        }
        return values;
    }
};

template<size_t L = 1>
class DryBedDambreakScenario : public InitialValues<3U> {
public:
    std::array<double, 3U> getInitialValues(double x) const override {
        std::array<double, 3U> values{0.0, 0.0, 0.5};
        if (x < 0.0) {
            values[0U] = 4.0;
        } else {
            values[0U] = 0.0;
        }
        return values;
    }
};

template<size_t L = 1>
class TwoRfwDambreakScenario : public InitialValues<3U> {
public:
    std::array<double, 3U> getInitialValues(double x) const override {
        std::array<double, 3U> values{0.0, 0.0, 0.0};
        values[0U] = 1.0;

        if (x < 0.0) {
            values[1U] = -0.5;
        } else {
            values[1U] = 0.5;
        }
        return values;
    }
};

class SlopingBeach : public InitialValues<3U> {
public:
    std::array<double, 3U> getInitialValues(double x) const override {
        std::array<double, 3U> values{0.0, 0.0, 0.0};
        auto eta = 0.5 * std::exp(-100.0 * x * x) + 0.75;
        //auto b =  0.1 + std::max(0.0, x);
        auto b = 0.1 + std::max(0.0, 0.5 * x);

        values[0U] = std::max(0.0, eta - b);
        values[2U] = b;
        return values;
    }
};

#endif //FVM_INITIALVALUES_H

/**
* \}
* \}
*/