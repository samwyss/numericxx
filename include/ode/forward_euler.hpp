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

#ifndef NUMERICXX_FORWARD_EULER_HPP
#define NUMERICXX_FORWARD_EULER_HPP

#include <concepts>
#include <span>

/*!
 * solves df(f, t)/dt = rhs using the forward Euler method
 * @tparam T floating point type
 * @tparam Func rhs function template
 * @param rhs rhs function of f and t
 * @param f current f value
 * @param t current t value
 * @param dt t increment
 * @return next f value
 */
template<std::floating_point T, typename Func>
T forward_euler(const Func rhs, const T f, const T t, const T dt) {
    return f + rhs(f, t) * dt;
}

/*!
 * solves df(f, t)/dt = rhs using the forward Euler method
 * @tparam T floating point type
 * @tparam Func rhs function template
 * @param rhs rhs function of f and t
 * @param f current f values
 * @param t current t value
 * @param dt t increment
 * @return next f value
 */
template<std::floating_point T, typename Func>
void forward_euler(const Func rhs, const std::span<T> f, const T t, const T dt) {
    for (auto &fi: f) {
        fi = forward_euler(rhs, fi, t, dt);
    }
}

#endif // NUMERICXX_FORWARD_EULER_HPP
