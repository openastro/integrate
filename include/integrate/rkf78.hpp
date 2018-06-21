/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef INTEGRATE_RKF78_HPP
#define INTEGRATE_RKF78_HPP

#include <iomanip>
#include <limits>

#include <algorithm>
#include <cmath>
#include <exception>
#include <functional>

namespace integrate
{

//! Execute single integration step using Runge-Kutta-Felhberg 7(8) scheme.
/*!
 * Executes single numerical integration step using Runge-Kutta-Felhberg 7(8) scheme.
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
const void stepRKF78(
    Real& time,
    State& state,
    Real& stepSize,
    const std::function< const State ( const Real time,
                                       const State& state ) >& computeStateDerivative,
    const Real tolerance,
    const Real minimumStepSize,
    const Real maximumStepSize )
{
    const State k1  = stepSize * computeStateDerivative( time, state );
    const State k2  = stepSize * computeStateDerivative( time + ( 2.0 / 27.0 ) * stepSize,
                                                         state + ( 2.0 / 27.0 ) * k1 );
    const State k3  = stepSize * computeStateDerivative( time + ( 1.0 / 9.0 ) * stepSize,
                                                         state + ( 1.0 / 36.0 ) * k1
                                                               + ( 1.0 / 12.0 ) * k2 );
    const State k4  = stepSize * computeStateDerivative( time + ( 1.0 / 6.0 ) * stepSize,
                                                         state + ( 1.0 / 24.0 ) * k1
                                                               + ( 0.125 ) * k3 );
    const State k5  = stepSize * computeStateDerivative( time + ( 5.0 / 12.0 ) * stepSize,
                                                         state + ( 5.0 / 12.0 ) * k1
                                                               + ( -1.5625 ) * k3
                                                               + ( 1.5625 ) * k4 );
    const State k6  = stepSize * computeStateDerivative( time + ( 0.5 ) * stepSize,
                                                         state + ( 0.05 ) * k1
                                                               + ( 0.25 ) * k4
                                                               + ( 0.2 ) * k5 );
    const State k7  = stepSize * computeStateDerivative( time + ( 5.0 / 6.0 ) * stepSize,
                                                         state + ( -25.0 / 108.0 ) * k1
                                                               + ( 125.0 / 108.0 ) * k4
                                                               + ( -65.0 / 27.0 ) * k5
                                                               + ( 125.0 / 54.0 ) * k6 );
    const State k8  = stepSize * computeStateDerivative( time + ( 1.0 / 6.0 ) * stepSize,
                                                         state + ( 31.0 / 300.0 ) * k1
                                                               + ( 61.0 / 225.0 ) * k5
                                                               + ( -2.0 / 9.0 ) * k6
                                                               + ( 13.0 / 900.0 ) * k7 );
    const State k9  = stepSize * computeStateDerivative( time + ( 2.0 / 3.0 ) * stepSize,
                                                         state + ( 2.0 ) * k1
                                                               + ( -53.0 / 6.0 ) * k4
                                                               + ( 704.0 / 45.0 ) * k5
                                                               + ( -107.0 / 9.0 ) * k6
                                                               + ( 67.0 / 90.0 ) * k7
                                                               + ( 3.0 ) * k8 );
    const State k10 = stepSize * computeStateDerivative( time + ( 1.0 / 3.0 ) * stepSize,
                                                         state + ( -91.0 / 108.0 ) * k1
                                                               + ( 23.0 / 108.0 ) * k4
                                                               + ( -976.0 / 135.0 ) * k5
                                                               + ( 311.0 / 54.0 ) * k6
                                                               + ( -19.0 / 60.0 ) * k7
                                                               + ( 17.0 / 6.0 ) * k8
                                                               + ( -1.0 / 12.0 ) * k9 );
    const State k11 = stepSize * computeStateDerivative( time + stepSize,
                                                         state + ( 2383.0 / 4100.0 ) * k1
                                                               + ( -341.0 / 164.0 ) * k4
                                                               + ( 4496.0 / 1025.0 ) * k5
                                                               + ( -301.0 / 82.0 ) * k6
                                                               + ( 2133.0 / 4100.0 ) * k7
                                                               + ( 45.0 / 82.0 ) * k8
                                                               + ( 45.0 / 164.0 ) * k9
                                                               + ( 18.0 / 41.0 ) * k10 );
    const State k12 = stepSize * computeStateDerivative( time,
                                                         state + ( 3.0 / 205.0 ) * k1
                                                               + ( -6.0 / 41.0 ) * k6
                                                               + ( -3.0 / 205.0 ) * k7
                                                               + ( -3.0 / 41.0 ) * k8
                                                               + ( 3.0 / 41.0 ) * k9
                                                               + ( 6.0 / 41.0 ) * k10 );
    const State k13 = stepSize * computeStateDerivative( time + stepSize,
                                                         state + ( -1777.0 / 4100.0 ) * k1
                                                               + ( -341.0 / 164.0 ) * k4
                                                               + ( 4496.0 / 1025.0 ) * k5
                                                               + ( -289.0 / 82.0 ) * k6
                                                               + ( 2193.0 / 4100.0 ) * k7
                                                               + ( 51.0 / 82.0 ) * k8
                                                               + ( 33.0 / 164.0 ) * k9
                                                               + ( 12.0 / 41.0 ) * k10
                                                               + k12 );

    const State errorEstimate = ( 41.0 / 840.0 ) * ( ( -1.0 ) * k1 + ( -1.0 ) * k11 + k12 + k13 );

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

        stepRKF78< Real, State >( time,
                                  state,
                                  stepSize,
                                  computeStateDerivative,
                                  minimumStepSize,
                                  maximumStepSize,
                                  tolerance );
    }
};

} // namespace integrate

#endif // INTEGRATE_RKF78_HPP
