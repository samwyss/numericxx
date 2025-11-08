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

#ifndef NUMERICXX_LEAPFROG_HPP
#define NUMERICXX_LEAPFROG_HPP

#include <concepts>
#include <span>

#include "constants/constants.hpp"

template <std::floating_point T, typename Func>
T leapfrog(const Func rhs, const T t, const T f, const T f_prev, const T dt) {
  return rhs(t, f) * TWO<T> * dt + f_prev;
}

template <std::floating_point T, typename Func>
void leapfrog(const Func rhs, const T t, const std::span<T> f, const std::span<T> f_prev, const T dt) {
  for (auto i = 0; i < f.size(); ++i) {
    f[i] = leapfrog(rhs, t, f[i], f_prev[i], dt);
  }
}

#endif // NUMERICXX_LEAPFROG_HPP
