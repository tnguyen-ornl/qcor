#pragma once
#include "Quantum/QuantumOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Target/LLVMIR.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/Passes.h"

using namespace mlir;

namespace qcor {
struct SingleQubitIdentityPairRemovalPass
    : public PassWrapper<SingleQubitIdentityPairRemovalPass,
                         OperationPass<ModuleOp>> {
  void getDependentDialects(DialectRegistry &registry) const override;
  void runOnOperation() final;
  SingleQubitIdentityPairRemovalPass() {}

protected:
  static inline const std::map<std::string, std::string> search_gates{
      {"x", "x"},   {"y", "y"},   {"z", "z"},   {"h", "h"},
      {"t", "tdg"}, {"tdg", "t"}, {"s", "sdg"}, {"sdg", "s"}};
  bool should_remove(std::string name1, std::string name2) const;
};

struct CNOTIdentityPairRemovalPass
    : public PassWrapper<CNOTIdentityPairRemovalPass, OperationPass<ModuleOp>> {
  void getDependentDialects(DialectRegistry &registry) const override;
  void runOnOperation() final;
  CNOTIdentityPairRemovalPass() {}
};
} // namespace qcor