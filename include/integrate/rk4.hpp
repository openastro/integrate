/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#pragma once

#include <functional>

namespace integrate
{

//! Execute single integration step using Runge-Kutta 4 scheme.
/*!
 * Executes single numerical integration step using Runge-Kutta 4 scheme.
 *
 * @tparam         Real                    Type for floating-point number
 * @tparam         State                   Type for state and state derivative
 * @param[in,out]  time                    Independent variable, which is provided as input and is
 *                                         updated with output at end of integration step
 * @param[in,out]  state                   State, which is provided as input and is updated with
 *                                         output at end of integration step
 * @param[in]      stepSize                Step size to take for integration step
 * @param[in]      computeStateDerivative  Function to compute state derivative for current time
 *                                         and state
 */
template <typename Real, typename State>
const void stepRK4(
    Real& time,
    State& state,
    const Real stepSize,
    const std::function<const State(const Real time,
                                    const State& state) >& computeStateDerivative)
{
    const State k1 = stepSize * computeStateDerivative(time, state);
    const State k2 = stepSize * computeStateDerivative(time + stepSize * 0.5, state + 0.5 * k1);
    const State k3 = stepSize * computeStateDerivative(time + stepSize * 0.5, state + 0.5 * k2);
    const State k4 = stepSize * computeStateDerivative(time + stepSize, state + k3);
    state += (1.0 / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
    time += stepSize;
};

} // namespace integrate
