OPENQASM 2.0;
include "qelib1.inc";

qreg qubits[9];
ccx qubits[4],qubits[7],qubits[8];
ccx qubits[3],qubits[6],qubits[7];
ccx qubits[2],qubits[5],qubits[6];
ccx qubits[0],qubits[1],qubits[5];
ccx qubits[2],qubits[5],qubits[6];
ccx qubits[3],qubits[6],qubits[7];
ccx qubits[4],qubits[7],qubits[8];
ccx qubits[3],qubits[6],qubits[7];
ccx qubits[2],qubits[5],qubits[6];
ccx qubits[0],qubits[1],qubits[5];
ccx qubits[2],qubits[5],qubits[6];
ccx qubits[3],qubits[6],qubits[7];
