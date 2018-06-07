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
const void stepEuler(
    Real& currentTime,
    State& currentState,
    const Real stepSize,
    const std::function< const State ( const Real currentTime,
                                       const State& currentState ) >& computeStateDerivative )
{
    currentState += stepSize * computeStateDerivative( currentTime, currentState );
    currentTime += stepSize;
};

} // namespace integrate

#endif // INTEGRATE_EULER_HPP
