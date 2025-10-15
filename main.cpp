/*
 * Copyright (C) 2025 Samuel Wyss
 *
 * This file is part of numericxx.
 *
 * Numericxx is free software: you can redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Numericxx is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with numericxx. If not, see
 * <https://www.gnu.org/licenses/>.
 */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numericxx.hpp>

double rhs(const double f, const double x, const double t) { return -2.0 * f; }

double sol(const double f, const double x, const double t) { return std::exp(-2.0 * t); }

int main(const int argc, const char **argv) {
  const auto n = static_cast<size_t>(std::stoull(argv[1]));
  const auto dt = static_cast<double>(std::stod(argv[2]));
  double t = 0.0;
  double x = 0.0;
  double f = 1.0;

  std::cout << "t" << ", " << "solution" << ", " << "calculated" << ", " << "error%" << std::endl;
  std::cout << t << ", " << sol(f, x, t) << ", " << f << ", " << std::abs(f - sol(f, x, t)) / sol(f, x, t) * 100 << std::endl;

  for (size_t i = 0; i < n; ++i) {
    f = forward_euler(rhs, f, x, t, dt);
    t += dt;

    const auto act = sol(f, t);
    std::cout << t << ", " << act << ", " << f << ", " << std::abs(f - act) / act * 100 << std::endl;
  }

  return EXIT_SUCCESS;
}
