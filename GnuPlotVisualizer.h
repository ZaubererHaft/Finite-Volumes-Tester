#ifndef FVM_GNUPLOTVISUALIZER_H
#define FVM_GNUPLOTVISUALIZER_H

#include <string>
#include <vector>
#include <fstream>

#include "Visualizer.h"
#include "Cell.h"

template<size_t L>
class GnuPlotVisualizer : public Visualizer<L> {
public:
    virtual void visualize(double time, const std::vector<Cell<L>> &currCells) const override {
        runGnuplot(createCsv(time, currCells));
    }

private:
    std::string createCsv(double time, const std::vector<Cell<L>> &currCells) const {
        std::ofstream csv;
        std::string filename = "example_" + std::to_string(time) + ".csv";
        csv.open(filename);
        for (const auto &cell: currCells) {
            std::string line = std::to_string(cell.getCenter()) + ",";
            for (size_t i = 0U; i < L; ++i) {
                auto data = cell.at(i);
                if (i == 0U) {
                    line += std::to_string(data);
                } else if (i > 0U && i < L - 1U) {
                    line += "," + std::to_string(data);

                } else {
                    line += "," + std::to_string(data) + "\n";
                }
            }
            csv << line;
        }
        (void) csv.flush();
        csv.close();

        return filename;
    }

    void runGnuplot(const std::string &filename) const {
        std::string cmd =
                "C:\\tools\\common\\gnuplot\\bin\\gnuplot.exe -e \"FILE='" + filename + "'\" C:\\work\\fvm\\vis.plt";
        std::system(cmd.c_str());
    }

};


#endif //FVM_GNUPLOTVISUALIZER_H
