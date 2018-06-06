/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef INTEGRATE_EULER_HPP
#define INTEGRATE_EULER_HPP

#include <functional>

namespace integrate
{

//! Execute single integration step using Euler scheme.
/*!
 * Executes single numerical integration step using Euler scheme.
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
const void stepEuler(
    const Real currentTime,
    const Real timeStep,
    const State& currentState,
    const std::function< const State ( const Real currentTime,
                                       const State& currentState ) >& computeStateDerivative,
    Real& nextTime,
    State& nextState )
{
    const State currentStateDerivative = computeStateDerivative( currentTime, currentState );
    nextState = currentState + timeStep * currentStateDerivative;
    nextTime = currentTime + timeStep;
};

} // namespace integrate

#endif // INTEGRATE_EULER_HPP
