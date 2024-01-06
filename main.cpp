#include "Domain.h"
#include "Simulation.h"
#include "GnuPlotVisualizer.h"

int main() {
    OutflowBoundaryConditions<3U> obc {};
    NoSlipBoundaryConditions noSlipBcs;
    ReflectingBoundaryConditions rfl;
    SlopingBeach iv;
    LakeAtRestScenario lars;
    DambreakScenario ds;
    Domain domain {-1.0, 1.5};
    ShallowWaterFlux2 fl;
    Equation<3U> equation{domain, &noSlipBcs, &ds, &fl};

    FWaveFluxDry numericalFlux {equation};
    GnuPlotVisualizer<3U> visualizer;
    Simulation<3U> simulation(equation, &numericalFlux, &visualizer);

    EquidistantDiscretizer<3U> discretizer (0.01);
    simulation.prepare(&discretizer);

    simulation.Run(1);


    return 0;
}
