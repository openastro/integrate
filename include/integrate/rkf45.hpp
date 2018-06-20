/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef INTEGRATE_RKF45_HPP
#define INTEGRATE_RKF45_HPP

#include <iomanip>
#include <limits>

#include <algorithm>
#include <cmath>
#include <exception>
#include <functional>

namespace integrate
{

//! Execute single integration step using Runge-Kutta-Felhberg 4(5) scheme.
/*!
 * Executes single numerical integration step using Runge-Kutta-Felhberg 4(5) scheme.
 *
 * @tparam          Real                    Type for floating-point number
 * @tparam          State                   Type for state and state derivative
 * @param[in,out]   time                    Independent variable, which is provided as input and is
 *                                          updated with output at end of integration step
 * @param[in,out]   state                   State, which is provided as input and is updated with
 *                                          output at end of integration step
 * @param[in,out]   stepSize                Step size to take for integration step
 * @param[in]       computeStateDerivative  Function to compute state derivative for current time
 *                                          and state
 * @param[in]       tolerance               Local truncation error tolerance
 * @param[in]       minimumStepSize         Minimum allowable step size for integration step
 * @param[in]       maximumStepSize         Maximum allowable step size for integration step
 */
template< typename Real, typename State >
const void stepRKF45(
    Real& time,
    State& state,
    Real& stepSize,
    const std::function< const State ( const Real time,
                                       const State& state ) >& computeStateDerivative,
    const Real tolerance,
    const Real minimumStepSize,
    const Real maximumStepSize )
{
    while ( true )
    {
        const State k1 = stepSize * computeStateDerivative( time, state );
        const State k2 = stepSize * computeStateDerivative( time + 0.25 * stepSize,
                                                            state + 0.25 * k1 );
        const State k3 = stepSize * computeStateDerivative( time + 0.375 * stepSize,
                                                            state + 0.09375 * k1 + 0.28125 * k2 );
        const State k4 = stepSize * computeStateDerivative( time + ( 12.0 / 13.0 ) * stepSize,
                                                            state + ( 1932.0 / 2197.0 ) * k1
                                                                  + ( -7200.0 / 2197.0 ) * k2
                                                                  + ( 7296.0 / 2197.0 ) * k3 );
        const State k5 = stepSize * computeStateDerivative( time + stepSize,
                                                            state + ( 439.0 / 216.0 ) * k1
                                                                  + ( -8.0 ) * k2
                                                                  + ( 3680.0 / 513.0 ) * k3
                                                                  + ( -845.0 / 4104.0 ) * k4 );
        const State k6 = stepSize * computeStateDerivative( time + 0.5 * stepSize,
                                                            state + ( -8.0 / 27.0 ) * k1
                                                                  + ( 2.0 ) * k2
                                                                  + ( -3544.0 / 2565.0 ) * k3
                                                                  + ( 1859.0 / 4104.0 ) * k4
                                                                  + ( -11.0 / 40.0 ) * k5 );

        const State errorEstimate = ( 1.0 / 360.0 ) * k1
                                    + ( -128.0 / 4275.0 ) * k3
                                    + ( -2197.0 / 75240.0 ) * k4
                                    + ( 1.0 / 50.0 ) * k5
                                    + ( 2.0 / 55.0 ) * k6;

        Real errorEstimateMaximum = 0.0;
        for ( int i = 0; i < errorEstimate.size( ); ++i )
        {
            const Real errorEstimateElementAbsolute = std::fabs( errorEstimate[ i ] );
            if ( errorEstimateMaximum < errorEstimateElementAbsolute )
            {
                errorEstimateMaximum = errorEstimateElementAbsolute;
            }
        }

        const Real stepSizeFactor = 0.84 * std::pow( ( tolerance * stepSize
                                                     / errorEstimateMaximum ), 0.25 );

        if ( errorEstimateMaximum < tolerance * stepSize )
        {
            time = time + stepSize;
            state = state + ( 25.0 / 216.0 ) * k1
                          + ( 1408.0 / 2565.0 ) * k3
                          + ( 2197.0 / 4104.0 ) * k4
                          + ( -1.0 / 5.0 ) * k5;
            stepSize = stepSizeFactor * stepSize;
            break;
        }
        else
        {
            if ( stepSizeFactor <= 0.1 )
            {
                stepSize = 0.1 * stepSize;
            }
            else if ( stepSizeFactor >= 4.0 )
            {
                stepSize = 4.0 * stepSize;
            }
            else
            {
                stepSize = stepSizeFactor * stepSize;
            }

            if ( stepSize > maximumStepSize )
            {
                stepSize = maximumStepSize;
            }
            else if ( stepSize < minimumStepSize )
            {
                std::runtime_error( "Minimum step size exceed!" );
            }
        }
    }
};

} // namespace integrate

#endif // INTEGRATE_RKF45_HPP
