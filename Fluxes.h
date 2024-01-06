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


#ifndef FVM_FLUXES_H
#define FVM_FLUXES_H

template<size_t L = 1>
class Fluxes {
public:
    virtual std::array<double, L> getFlux(double x, const std::array<double, L> &q) = 0;

    virtual std::array<double, L> getEigenvalues(const std::array<double, L> &q) = 0;
};

class ShallowWaterFlux : public Fluxes<3U> {
public:
    virtual std::array<double, 3U> getFlux(double x, const std::array<double, 3U> &q) override {
        return
                {
                        q[0U] * q[1U],
                        0.5 * q[1U] * q[1U] + g * (q[0U] + q[2U]),
                        0.0
                };
    }

    virtual std::array<double, 3U> getEigenvalues(const std::array<double, 3U> &q) override {
        auto u = q.at(1U);
        auto h = q.at(0U);

        return {u - std::sqrt(g * h), u + std::sqrt(g * h)};
    }

private:
    static constexpr double g = 9.81;
};

class ShallowWaterFlux2 : public Fluxes<3U> {
public:
    virtual std::array<double, 3U> getFlux(double x, const std::array<double, 3U> &q) override {

        if (q[0] <= 0.0 || std::isnan(q[0]) || std::isnan(q[1])) {
            throw std::invalid_argument("only accept positive water height!");
        }

        return
        {
                q[1U],
                q[1U] * q[1U] / q[0U] + 0.5 * g * q[0U] * q[0U],
                0.0
        };
    }

    virtual std::array<double, 3U> getEigenvalues(const std::array<double, 3U> &q) override {
        auto u = q.at(1U) / q.at(0U);
        auto h = q.at(0U);

        return {u - std::sqrt(g * h), u + std::sqrt(g * h)};
    }

private:
    static constexpr double g = 9.81;
};


#endif //FVM_FLUXES_H

/**
* \}
* \}
*/