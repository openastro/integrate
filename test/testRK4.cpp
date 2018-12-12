/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <catch2/catch.hpp>

#include <functional>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "integrate/rk4.hpp"

#include "testDynamicalModels.hpp"
#include "testState.hpp"

namespace integrate
{
namespace tests
{

TEST_CASE( "Test Runge-Kutta 4 integrator for zero dynamics free function", "[euler]" )
{
    const Real initialTime = 1.0;
    const State initialState( { 1.2, 2.3, -3.6 } );
    const Real stepSize = 0.1;

    Real currentTime = initialTime;
    State currentState = initialState;

    stepRK4< Real, State >( currentTime,
                            currentState,
                            stepSize,
                            &computeZeroDynamics );

    REQUIRE( currentTime  == ( initialTime + stepSize ) );
    REQUIRE( currentState == initialState );
}

TEST_CASE( "Test Runge-Kutta 4 integrator integrator for zero dynamics class", "[rk4]" )
{
    const Real initialTime = 1.0;
    const State initialState( { 1.2, 2.3, -3.6 } );
    const Real stepSize = 0.1;

    Real currentTime = initialTime;
    State currentState = initialState;

    ZeroDynamics dynamics;
    auto stateDerivativePointer = std::bind( &ZeroDynamics::operator( ),
                                             &dynamics,
                                             std::placeholders::_1,
                                             std::placeholders::_2 );
    stepRK4< Real, State >( currentTime,
                            currentState,
                            stepSize,
                            stateDerivativePointer );

    REQUIRE( currentTime  == ( initialTime + stepSize ) );
    REQUIRE( currentState == initialState );
}

TEST_CASE( "Test Runge-Kutta 4 integrator for Burden & Faires (9th ed.): Table 5.8", "[rk4]" )
{
    const Real initialTime = 0.0;
    const State initialState( { 0.5 } );
    const Real stepSize = 0.2;

    Real currentTime = initialTime;
    State currentState = initialState;

    const Real testTolerance = 1.0e-7;

    std::map< Real, State > burdenFairesTable5_1Data;
    burdenFairesTable5_1Data.insert( { 0.2, State( { 0.8292933 } ) } );
    burdenFairesTable5_1Data.insert( { 0.4, State( { 1.2140762 } ) } );
    burdenFairesTable5_1Data.insert( { 0.6, State( { 1.6489220 } ) } );
    burdenFairesTable5_1Data.insert( { 0.8, State( { 2.1272027 } ) } );
    burdenFairesTable5_1Data.insert( { 1.0, State( { 2.6408227 } ) } );
    burdenFairesTable5_1Data.insert( { 1.2, State( { 3.1798942 } ) } );
    burdenFairesTable5_1Data.insert( { 1.4, State( { 3.7323401 } ) } );
    burdenFairesTable5_1Data.insert( { 1.6, State( { 4.2834095 } ) } );
    burdenFairesTable5_1Data.insert( { 1.8, State( { 4.8150857 } ) } );
    burdenFairesTable5_1Data.insert( { 2.0, State( { 5.3053630 } ) } );

    BurdenFaires dynamics;
    auto stateDerivativePointer = std::bind( &BurdenFaires::operator( ),
                                             &dynamics,
                                             std::placeholders::_1,
                                             std::placeholders::_2 );

    for ( const auto& pair : burdenFairesTable5_1Data )
    {
        stepRK4< Real, State >( currentTime,
                                currentState,
                                stepSize,
                                stateDerivativePointer );
        REQUIRE( pair.first == Approx( currentTime ).epsilon( testTolerance ) );
        REQUIRE( pair.second[ 0 ] == Approx( currentState[ 0 ] ).epsilon( testTolerance ) );
    }
}

} // namespace tests
} // namespace integrate
