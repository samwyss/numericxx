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

constexpr double INIT_F = 0.0;

double rhs(const double t, const double f) { return std::cos(t); }

double sol(const double t, const double f) { return std::sin(t); }

int main(const int argc, const char **argv) {
  const auto n = static_cast<size_t>(std::stoull(argv[1]));
  const auto dt = static_cast<double>(std::stod(argv[2]));
  double t = 0.0;
  double f = INIT_F;

  // timing
  const std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < n; ++i) {
    f = forward_euler(rhs, t, f, dt);
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
  f = INIT_F;

  double act = sol(t, f);
  double err = std::abs(f - act) / act * 100;
  fmt::print("t, actual, calculated, error(%)\n");
  fmt::print("{:.8e}, {:.8e}, {:.8e}, {:.8e}\n", t, act, f, err);

  for (size_t i = 0; i < n; ++i) {
    f = forward_euler(rhs, t, f, dt);
    t += dt;

    act = sol(t, f);
    err = std::abs(f - act) / act * 100;
    fmt::print("{:.8e}, {:.8e}, {:.8e}, {:.8e}\n", t, act, f, err);
  }

  return EXIT_SUCCESS;
}
