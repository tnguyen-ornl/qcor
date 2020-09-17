#include "ftqc/vqe.hpp"
#include "xacc.hpp"
// Compile with:
// qcor -qpu qpp -qrt ftqc -I<qcor/examples/shared> deuteron.cpp 

__qpu__ void ansatz(qreg q, double theta) {
  X(q[0]);
  Ry(q[1], theta);
  CX(q[1], q[0]);
}

int main(int argc, char **argv) {
  // Allocate 2 qubits
  auto q = qalloc(2);
  // Hamiltonian
  auto H = 5.907 - 2.1433 * X(0) * X(1) - 2.1433 * Y(0) * Y(1) + .21829 * Z(0) -
           6.125 * Z(1);
  // TODO:
  // We can hook this up to the QCOR's Objective function
  // The amount of code to manually instantiate the optimization loop here is
  // also very minimal.
  auto optimizer = createOptimizer("nlopt");
  xacc::OptFunction f(
      [&](const std::vector<double> &x, std::vector<double> &dx) {
        const double angle = x[0];
        auto statePrep =
            std::function<void(qreg)>{[angle](qreg q) { ansatz(q, angle); }};
        double energy = 0.0;
        EstimateEnergy(q, statePrep, H, 1024, energy);
        std::cout << "Energy(" << angle << ") = " << energy << "\n";
        return energy;
      },
      1);

  auto result = optimizer->optimize(f);
  std::cout << "Min Energy = " << result.first << "\n";
}
