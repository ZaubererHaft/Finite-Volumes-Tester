#include "Domain.h"
#include "Simulation.h"
#include "GnuPlotVisualizer.h"

int main() {
    Domain domain{-1.0, 1.5};
    EquidistantDiscretizer<3U> discretizer(0.01);

    ReflectingBoundaryConditions rfl{};
    DambreakScenario lars{};
    ShallowWaterFlux2 fl{};

    Equation<3U> equation{domain, &rfl, &lars, &fl};

    HLLFlux numericalFlux{equation};
    GnuPlotVisualizer<3U> visualizer{};
    Simulation<3U> simulation(equation, &numericalFlux, &visualizer);

    simulation.prepare(&discretizer);
    simulation.Run(1);

    return 0;
}
