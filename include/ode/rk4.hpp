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

#ifndef NUMERICXX_RK4_HPP
#define NUMERICXX_RK4_HPP

#include <concepts>
#include <span>

#include "constants/constants.hpp"

/*!
 * solves df(f, t)/dt = rhs using the fourth order Runge-Kutta method
 * @tparam T floating point type
 * @tparam Func rhs function template
 * @param rhs rhs function of f and t
 * @param t current t value
 * @param f current f value
 * @param dt t increment
 * @return next f value
 */
template<std::floating_point T, typename Func>
T rk4(const Func rhs, const T t, const T f, const T dt) {
    const T k1 = rhs(t, f);
    const T k2 = rhs(t + ONE_HALF<T> * dt, f + ONE_HALF<T> * dt * k1);
    const T k3 = rhs(t + ONE_HALF<T> * dt, f + ONE_HALF<T> * dt * k2);
    const T k4 = rhs(t + dt, f + dt * k3);
    return f + ONE_SIXTH<T> * dt * (k1 + TWO<T> * k2 + TWO<T> * k3 + k4);
}

/*!
 * solves df(f, t)/dt = rhs using the fourth order Runge-Kutta method
 * @tparam T floating point type
 * @tparam Func rhs function template
 * @param rhs rhs function of f and t
 * @param t current t value
 * @param f current f values
 * @param dt t increment
 * @return next f value
 */
template<std::floating_point T, typename Func>
void rk4(const Func rhs, const T t, const std::span<T> f, const T dt) {
    for (auto &fi: f) {
        fi = rk4(rhs, t, fi, dt);
    }
}

#endif //NUMERICXX_RK4_HPP
