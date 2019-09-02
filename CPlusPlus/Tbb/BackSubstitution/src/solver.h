#ifndef SOLVER_HDR
#define SOLVER_HDR

std::vector<double> solve_serial(const Equations& eqns);
std::vector<double> check_serial(const Equations& eqns, const std::vector<double> x);

#endif
