/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <catch2/catch.hpp>

#include <functional>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "integrate/rkf78.hpp"

#include "testDynamicalModels.hpp"
#include "testState.hpp"

namespace integrate
{
namespace tests
{

TEST_CASE( "Test Runge-Kutta-Fehlberg 7(8) integrator for zero dynamics free function", "[rkf78]" )
{
    const Real initialTime = 1.0;
    const State initialState( { 1.2, 2.3, -3.6 } );
    const Real initialStepSize = 0.1;
    const Real tolerance = 1.0e-6;
    const Real minimumStepSize = 0.01;
    const Real maximumStepSize = 1.0;

    Real finalTime = 1.1;
    State finalState( { 1.2, 2.3, -3.6 } );
    Real finalStepSize = 0.1;

    Real currentTime = initialTime;
    State currentState = initialState;
    Real currentStepSize = initialStepSize;

    stepRKF78< Real, State >( currentTime,
                              currentState,
                              currentStepSize,
                              &computeZeroDynamics,
                              tolerance,
                              minimumStepSize,
                              maximumStepSize );

    REQUIRE( finalTime  == ( initialTime + finalStepSize ) );
    REQUIRE( finalState == initialState );
    REQUIRE( finalStepSize == initialStepSize );
}

TEST_CASE( "Test Runge-Kutta-Fehlberg 7(8) integrator integrator for zero dynamics class",
           "[rkf78]" )
{
    const Real initialTime = 1.0;
    const State initialState( { 1.2, 2.3, -3.6 } );
    const Real initialStepSize = 0.1;
    const Real tolerance = 1.0e-6;
    const Real minimumStepSize = 0.01;
    const Real maximumStepSize = 1.0;

    Real finalTime = 1.1;
    State finalState( { 1.2, 2.3, -3.6 } );
    Real finalStepSize = 0.1;

    Real currentTime = initialTime;
    State currentState = initialState;
    Real currentStepSize = initialStepSize;

    ZeroDynamics dynamics;
    auto stateDerivativePointer = std::bind( &ZeroDynamics::operator( ),
                                             &dynamics,
                                             std::placeholders::_1,
                                             std::placeholders::_2 );
    stepRKF78< Real, State >( currentTime,
                              currentState,
                              currentStepSize,
                              stateDerivativePointer,
                              tolerance,
                              minimumStepSize,
                              maximumStepSize );

    REQUIRE( finalTime  == ( initialTime + finalStepSize ) );
    REQUIRE( finalState == initialState );
    REQUIRE( finalStepSize == initialStepSize );
}

} // namespace tests
} // namespace integrate
