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

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/printf.h>
#include <numericxx.hpp>

double rhs(const double f, const double t) { return -2.0 * f; }

double sol(const double f, const double t) { return std::exp(-2.0 * t); }

int main(const int argc, const char **argv) {
  const auto n = static_cast<size_t>(std::stoull(argv[1]));
  const auto dt = static_cast<double>(std::stod(argv[2]));
  double t = 0.0;
  double f = 1.0;

  // timing
  const std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < n; ++i) {
    f = forward_euler(rhs, f, t, dt);
    t += dt;
  }
  const std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

  const auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  fmt::print("loop time: {}\n", duration);
  fmt::print("iteration time: {}\n", duration / n);
  fmt::print("final value: {}\n", f);
  fmt::print("\n");

  // comparison
  t = 0.0;
  f = 1.0;

  double act = sol(f, t);
  double err = std::abs(f - act) / act * 100;
  fmt::print("t, actual, calculated, error(%)\n");
  fmt::print("{:.8e}, {:.8e}, {:.8e}, {:.8e}\n", t, act, f, err);

  for (size_t i = 0; i < n; ++i) {
    f = forward_euler(rhs, f, t, dt);
    t += dt;

    act = sol(f, t);
    err = std::abs(f - act) / act * 100;
    fmt::print("{:.8e}, {:.8e}, {:.8e}, {:.8e}\n", t, act, f, err);
  }

  return EXIT_SUCCESS;
}
