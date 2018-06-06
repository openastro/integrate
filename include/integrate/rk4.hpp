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
 * @tparam      Real                    Type for loating-point number
 * @tparam      State                   Type for states and state derivative
 * @param[in]   currentTime             Current time
 * @param[in]   timeStep                Time step to take for integration step
 * @param[in]   currentState            Current state
 * @param[in]   computeStateDerivative  Function to compute state derivative for current time and
 *                                      state
 * @param[out]  nextTime                Time at end of integration step
 * @param[out]  nextState               State at end of integration step
 */
template< typename Real, typename State >
const void stepRK4(
    const Real currentTime,
    const Real timeStep,
    const State& currentState,
    const std::function< const State ( const Real currentTime,
                                       const State& currentState ) >& computeStateDerivative,
    Real& nextTime,
    State& nextState )
{
    const State k1 = timeStep * computeStateDerivative( currentTime, currentState );
    const State k2 = timeStep * computeStateDerivative( currentTime + timeStep * 0.5,
                                                        currentState + 0.5 * k1 );
    const State k3 = timeStep * computeStateDerivative( currentTime + timeStep * 0.5,
                                                        currentState + 0.5 * k2 );
    const State k4 = timeStep * computeStateDerivative( currentTime + timeStep, currentState + k3 );

    nextState = currentState + ( 1.0 / 6.0 ) * ( k1 + 2.0 * k2 + 2.0 * k3 + k4 );
    nextTime = currentTime + timeStep;
};

} // namespace integrate

#endif // INTEGRATE_RK4_HPP
