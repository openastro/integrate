/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <iostream>
#include <iomanip>

#include <catch2/catch.hpp>

#include <functional>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "integrate/rkf45.hpp"

#include "testDynamicalModels.hpp"
#include "testState.hpp"

namespace integrate
{
namespace tests
{

TEST_CASE( "Test Runge-Kutta-Fehlberg 4(5) integrator for zero dynamics free function", "[rfk45]" )
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

    stepRKF45< Real, State >( currentTime,
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

TEST_CASE( "Test Runge-Kutta-Fehlberg 4(5) integrator integrator for zero dynamics class",
           "[rfk45]" )
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
    stepRKF45< Real, State >( currentTime,
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

TEST_CASE( "Test Runge-Kutta-Fehlberg 4(5) integrator using Burden & Faires (9th ed.): Table 5.11",
           "[rkf45]" )
{
    const Real initialTime = 0.0;
    const State initialState( { 0.5 } );
    const Real initialStepSize = 0.25;
    const Real tolerance = 1.0e-5;
    const Real minimumStepSize = 0.01;
    const Real maximumStepSize = 0.25;

    const Real testTolerance = 1.0e-5;

    Real currentTime = initialTime;
    State currentState = initialState;
    Real currentStepSize = initialStepSize;

    std::map< Real, State > burdenFairesTable5_9Data;
    burdenFairesTable5_9Data.insert( { 0.2500000, State( { 0.9204873 } ) } );
    burdenFairesTable5_9Data.insert( { 0.4865522, State( { 1.3964884 } ) } );
    burdenFairesTable5_9Data.insert( { 0.7293332, State( { 1.9537446 } ) } );
    burdenFairesTable5_9Data.insert( { 0.9793332, State( { 2.5864198 } ) } );
    burdenFairesTable5_9Data.insert( { 1.2293332, State( { 3.2604520 } ) } );
    burdenFairesTable5_9Data.insert( { 1.4793332, State( { 3.9520844 } ) } );
    burdenFairesTable5_9Data.insert( { 1.7293332, State( { 4.6308127 } ) } );
    burdenFairesTable5_9Data.insert( { 1.9793332, State( { 5.2574687 } ) } );
    burdenFairesTable5_9Data.insert( { 2.0000000, State( { 5.3054720 } ) } );

    BurdenFaires dynamics;
    auto stateDerivativePointer = std::bind( &BurdenFaires::operator( ),
                                             &dynamics,
                                             std::placeholders::_1,
                                             std::placeholders::_2 );

    std::map< Real, State >::iterator mapIterator = burdenFairesTable5_9Data.begin( );
    for ( const auto& pair : burdenFairesTable5_9Data )
    {
        stepRKF45< Real, State >( currentTime,
                                  currentState,
                                  currentStepSize,
                                  stateDerivativePointer,
                                  tolerance,
                                  minimumStepSize,
                                  maximumStepSize );
        REQUIRE( pair.first == Approx( currentTime ).epsilon( testTolerance ) );
        REQUIRE( pair.second[ 0 ] == Approx( currentState[ 0 ] ).epsilon( testTolerance ) );

        // Because of rounding error, the current time, state, and step size have to be forced
        // to coincide with the test data, since otherwise the time and step size generated by the
        // integrator due to the adaptive step size algorithm do not coincide with the test data.
        currentTime = pair.first;
        currentState = pair.second;
        std::advance( mapIterator, 1 );
        currentStepSize = mapIterator->first - pair.first;
    }
}

} // namespace tests
} // namespace integrate
