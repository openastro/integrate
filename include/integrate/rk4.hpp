/*
 * Copyright (c) 2017 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef INTEGRATE_RK4_HPP
#define INTEGRATE_RK4_HPP

#include <functional>

#include <sml/sml.hpp>

namespace integrate
{

//! Execute single integration step using Euler scheme.
/*!
 * Executes single numerical integration step using Euler scheme.
 *
 * @return               Dummy value
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
    // Compute Runge-Kutta stages.
    // Reference: http://lpsa.swarthmore.edu/NumInt/NumIntFourth.html
    const State k1 = computeStateDerivative( currentTime, currentState );
    const State k2
        = computeStateDerivative( currentTime + timeStep * 0.5,
                                  sml::add( currentState, sml::multiply( k1, timeStep * 0.5 ) ) );
    const State k3
        = computeStateDerivative( currentTime + timeStep * 0.5,
                                  sml::add( currentState, sml::multiply( k2, timeStep * 0.5 ) ) );
    const State k4
        = computeStateDerivative( currentTime + timeStep,
                                  sml::add( currentState, sml::multiply( k2, timeStep ) ) );

    for ( unsigned int i = 0; i < nextState.size( ); ++i )
    {
        nextState[ i ] = currentState[ i ]
                         + ( k1[ i ] + 2.0 * k2[ i ] + 2.0 * k3[ i ] + k4[ i ] ) / 6.0 * timeStep;
    }

    nextTime = currentTime + timeStep;
};

} // namespace integrate

#endif // INTEGRATE_RK4_HPP
