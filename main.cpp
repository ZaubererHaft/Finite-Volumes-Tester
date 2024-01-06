#include "Domain.h"
#include "Simulation.h"
#include "GnuPlotVisualizer.h"

int main() {
    Domain domain{-1.0, 1.5};

    OutflowBoundaryConditions<3U> obc{};
    NoSlipBoundaryConditions noSlipBcs{};
    ReflectingBoundaryConditions rfl{};

    SlopingBeach iv{};
    LakeAtRestScenario lars{};
    DambreakScenario ds{};

    ShallowWaterFlux2 fl2{};
    ShallowWaterFlux fl{};

    Equation<3U> equation{domain, &noSlipBcs, &iv, &fl};
    HLLFlux numericalFlux{equation};
    GnuPlotVisualizer<3U> visualizer{};
    Simulation<3U> simulation(equation, &numericalFlux, &visualizer);
    EquidistantDiscretizer<3U> discretizer(0.01);

    simulation.prepare(&discretizer);
    simulation.Run(1);


    return 0;
}
