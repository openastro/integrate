/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef INTEGRATE_RK4_HPP
#define INTEGRATE_RK4_HPP

#include <functional>

namespace integrate
{

//! Execute single integration step using Runge-Kutta 4 scheme.
/*!
 * Executes single numerical integration step using Runge-Kutta 4 scheme.
 *
 * @tparam          Real                    Type for floating-point number
 * @tparam          State                   Type for state and state derivative
 * @param[in,out]   currentTime             Current time, which is provided as input and contains
 *                                          output at end of integration step
 * @param[in,out]   currentState            Current state, which is provided as input and contains
 *                                          output at end of integration step
 * @param[in]       stepSize                Step size to take for integration step
 * @param[in]       computeStateDerivative  Function to compute state derivative for current time
 *                                          and state
 */
template< typename Real, typename State >
const void stepRK4(
    Real& currentTime,
    State& currentState,
    const Real stepSize,
    const std::function< const State ( const Real currentTime,
                                       const State& currentState ) >& computeStateDerivative )
{
    const State k1 = stepSize * computeStateDerivative( currentTime, currentState );
    const State k2 = stepSize * computeStateDerivative( currentTime + stepSize * 0.5,
                                                        currentState + 0.5 * k1 );
    const State k3 = stepSize * computeStateDerivative( currentTime + stepSize * 0.5,
                                                        currentState + 0.5 * k2 );
    const State k4 = stepSize * computeStateDerivative( currentTime + stepSize, currentState + k3 );

    currentState += ( 1.0 / 6.0 ) * ( k1 + 2.0 * k2 + 2.0 * k3 + k4 );
    currentTime += stepSize;
};

} // namespace integrate

#endif // INTEGRATE_RK4_HPP
