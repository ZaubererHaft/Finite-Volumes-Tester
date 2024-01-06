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


#ifndef FVM_RIEMANNSOLVER_H
#define FVM_RIEMANNSOLVER_H

template<size_t L = 1>
class NumericalFlux {
public:
    NumericalFlux(Equation<L> &eq) : equation{eq} {
    }

    virtual std::array<double, L> getNumericalFluxes(const Cell<L> &left, const Cell<L> &right) const = 0;

    double getMaxAbs(std::array<double, L> &values) const {
        return *std::max_element(values.begin(), values.end(), [](const double &a, const double &b) {
            return std::fabs(a) < std::fabs(b);
        });
    }

    double getMax(std::array<double, L> &values) const {
        return *std::max_element(values.begin(), values.end());
    }

    double getMin(std::array<double, L> &values) const {
        return *std::min_element(values.begin(), values.end());
    }

protected:
    Equation<L> equation;
};

template<size_t L = 1>
class HLLFlux : public NumericalFlux<L> {
public:
    explicit HLLFlux(Equation<L> &eq) : NumericalFlux<L>(eq) {
    }

    std::array<double, L> getNumericalFluxes(const Cell<L> &left, const Cell<L> &right) const override {
        double x = left.getXEnd();

        auto fl = this->equation.getFlux(x, left.getValues());
        auto fr = this->equation.getFlux(x, right.getValues());
        auto eigsL = this->equation.getEigenvalues(left.getValues());
        auto eigsR = this->equation.getEigenvalues(right.getValues());

        auto sr = std::max(this->getMax(eigsL), this->getMax(eigsR));
        auto sl = std::min(this->getMin(eigsL), this->getMin(eigsR));

        std::array<double, L> values;
        for (size_t i = 0U; i < L; ++i) {
            auto ql = left.at(i);
            auto qr = right.at(i);

            if (0.0 <= sl) {
                values[i] = fl[i];
            } else if (sl <= 0.0 && 0.0 <= sr) {
                values[i] = (sr * fl[i] - sl * fr[i] + sl * sr * (qr - ql)) / (sr - sl);
            } else {
                values[i] = fr[i];
            }
        }

        return values;
    }

};

class HLLFluxDry : public NumericalFlux<2> {
public:
    explicit HLLFluxDry(Equation<2> &eq) : NumericalFlux<2>(eq) {
    }

    virtual std::array<double, 2U> getNumericalFluxes(const Cell<2U> &left, const Cell<2U> &right) const override {
        std::array<double, 2U> values{0.0, 0.0};
        auto g = 9.81;
        double x = left.getXEnd();

        if (left.at(0U) <= 0.0 && right.at(0U) <= 0.0) {
            values[0U] = values[1U] = 0.0;
        } else if (left.at(0U) > 0.0 && right.at(0U) <= 0.0) {
            auto hl = left[0U];
            auto ul = left[1U] / left[0U];

            auto hm = ul + 2.0 * std::sqrt(g * hl);
            hm = (hm * hm) / (9.0 * g);

            auto um = 1.0 / 3.0 * (ul + 2.0 * std::sqrt(g * hl));

            values[0U] = hm;
            values[1U] = hm * um;
            values = this->equation.getFlux(x, values);
        } else if (left.at(0U) <= 0.0 && right.at(0U) > 0.0) {
            auto hr = right[0U];
            auto ur = right[1U] / left[0U];

            auto hm = ur + 2.0 * std::sqrt(g * hr);
            hm = (hm * hm) / (9.0 * g);

            auto um = 1.0 / 3.0 * (ur + 2.0 * std::sqrt(g * hr));

            values[0U] = hm;
            values[1U] = hm * um;
            values = this->equation.getFlux(x, values);
        } else {
            auto fl = this->equation.getFlux(x, left.getValues());
            auto fr = this->equation.getFlux(x, right.getValues());
            auto eigsL = this->equation.getEigenvalues(left.getValues());
            auto eigsR = this->equation.getEigenvalues(right.getValues());

            auto sr = std::max(this->getMax(eigsL), this->getMax(eigsR));
            auto sl = std::min(this->getMin(eigsL), this->getMin(eigsR));

            for (size_t i = 0U; i < 2U; ++i) {
                auto ql = left[i];
                auto qr = right[i];

                if (0.0 <= sl) {
                    values[i] = fl[i];
                } else if (sl <= 0.0 && 0.0 <= sr) {
                    values[i] = (sr * fl[i] - sl * fr[i] + sl * sr * (qr - ql)) / (sr - sl);
                } else {
                    values[i] = fr[i];
                }
            }
        }

        return values;
    }

};

class HLLFluxDry2 : public NumericalFlux<3U> {
public:
    explicit HLLFluxDry2(Equation<3U> &eq) : NumericalFlux<3U>(eq) {
    }

    virtual std::array<double, 3U> getNumericalFluxes(const Cell<3U> &left, const Cell<3U> &right) const override {
        std::array<double, 3U> values{0.0, 0.0, 0.0};
        auto g = 9.81;
        double x = left.getXEnd();

        if (left.at(0U) <= 0.0 && right.at(0U) <= 0.0) {
            values[0U] = values[1U] = 0.0;
        } else if (left.at(0U) > 0.0 && right.at(0U) <= 0.0) {
            auto hl = left[0U];
            auto ul = left[1U];

            auto hm = ul + 2.0 * std::sqrt(g * hl);
            hm = (hm * hm) / (9.0 * g);

            auto um = 1.0 / 3.0 * (ul + 2.0 * std::sqrt(g * hl));

            values[0U] = hm;
            values[1U] = um;
            values = this->equation.getFlux(x, values);
        } else if (left.at(0U) <= 0.0 && right.at(0U) > 0.0) {
            auto hr = right[0U];
            auto ur = right[1U];

            auto hm = ur + 2.0 * std::sqrt(g * hr);
            hm = (hm * hm) / (9.0 * g);

            auto um = 1.0 / 3.0 * (ur + 2.0 * std::sqrt(g * hr));

            values[0U] = hm;
            values[1U] = um;
            values = this->equation.getFlux(x, values);
        } else {
            auto fl = this->equation.getFlux(x, left.getValues());
            auto fr = this->equation.getFlux(x, right.getValues());
            auto eigsL = this->equation.getEigenvalues(left.getValues());
            auto eigsR = this->equation.getEigenvalues(right.getValues());

            auto sr = std::max(this->getMax(eigsL), this->getMax(eigsR));
            auto sl = std::min(this->getMin(eigsL), this->getMin(eigsR));

            for (size_t i = 0U; i < 2U; ++i) {
                auto ql = left[i];
                auto qr = right[i];

                if (0.0 <= sl) {
                    values[i] = fl[i];
                } else if (sl <= 0.0 && 0.0 <= sr) {
                    values[i] = (sr * fl[i] - sl * fr[i] + sl * sr * (qr - ql)) / (sr - sl);
                } else {
                    values[i] = fr[i];
                }
            }
        }

        return values;
    }

};


class FWaveFluxDry : public NumericalFlux<3U> {
public:
    explicit FWaveFluxDry(Equation<3U> &eq) : NumericalFlux<3U>(eq) {
    }

    virtual std::array<double, 3U> getNumericalFluxes(const Cell<3U> &left, const Cell<3U> &right) const override {
        std::array<double, 3U> values{0.0, 0.0, 0.0};
        auto g = 9.81;
        double x = left.getXEnd();

        auto hl = left[0U],             hr = right[0U];
        auto ul = left[1U] / hl,        ur = right[1U] / hr;
        auto cl = std::sqrt(g * hl), cr = std::sqrt(g * hr);
        auto bl = left[2U],             br = right[2U];

        if (hl <= 0.0 && hr <= 0.0) {
            values[0U] = values[1U] = 0.0;
        } else if (hl > 0.0 && hr <= 0.0) {
            auto hm = ul + 2.0 * std::sqrt(g * hl);
            hm = (hm * hm) / (9.0 * g);

            auto um = 1.0 / 3.0 * (ul + 2.0 * std::sqrt(g * hl));

            values[0U] = hm;
            values[1U] = um * hm;
            values = this->equation.getFlux(x, values);
        } else if (hl <= 0.0 && hr > 0.0) {
            auto hm = ur + 2.0 * std::sqrt(g * hr);
            hm = (hm * hm) / (9.0 * g);

            auto um = 1.0 / 3.0 * (ur + 2.0 * std::sqrt(g * hr));

            values[0U] = hm;
            values[1U] = um * hm;
            values = this->equation.getFlux(x, values);
        } else {
            auto fl = this->equation.getFlux(x, left.getValues());
            auto fr = this->equation.getFlux(x, right.getValues());

            auto hbar = 0.5 * (hl + hr);
            auto chat = std::sqrt(g * hbar);
            auto uhat = (std::sqrt(hl) * ul + std::sqrt(hr) * ur) / (std::sqrt(hl) + std::sqrt(hr));
            auto l1 = std::min(ul - cl, uhat - chat);
            auto l2 = std::min(ur + cr, uhat + chat);

            double r1[2] = {1.0, l1};
            double r2[2] = {1.0, l2};

            double r1_inv[2] = {(uhat + chat) / (2.0 * chat),-(uhat - chat) / (2.0 * chat)};
            double r2_inv[2] = {-1.0 / (2.0 * chat), 1.0 / (2.0 * chat)};

            double delta[2] = {
                    fr[0U] - fl[0U],
                    fr[1U] - fl[1U] + 0.5 * g * (hr + hl) * (br - bl)
            };

            double beta[2] = {
                    r1_inv[0] * delta[0] + r2_inv[0] * delta[1],
                    r1_inv[1] * delta[0] + r2_inv[1] * delta[1]
            };

            std::array<double, 3U> qm = {
                    left[0U],
                    left[1U],
                    left[2U]
            };

            if(l1 < 0.0)
            {
                qm[0] += r1[0] * (beta[0] / l1);
                qm[1] += r1[1] * (beta[0] / l1);
            }
            if(l2 < 0.0)
            {
                qm[0] += r2[0] * (beta[1] / l2);
                qm[1] += r2[1] * (beta[1] / l2);
            }
            values = equation.getFlux(x, qm);
        }

        return values;
    }

};

#endif //FVM_RIEMANNSOLVER_H
/**
* \}
* \}
*/
