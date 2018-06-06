/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <catch.hpp>

#include <functional>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "integrate/euler.hpp"

#include "testDynamicalModels.hpp"
#include "testState.hpp"

namespace integrate
{
namespace tests
{

TEST_CASE( "Test Euler integrator for zero dynamics", "[euler]" )
{
    const State initialState( { 1.2, 2.3, -3.6 } );
    const Real initialTime = 1.0;
    const Real stepSize = 0.1;

    State finalState( { 0.0, 0.0, 0.0 } );
    Real finalTime = 0.0;

    ZeroDynamics dynamics;

    using namespace std::placeholders;
    auto stateDerivativePointer = std::bind( &ZeroDynamics::computeStateDerivative,
                                             &dynamics,
                                             _1,
                                             _2 );
    stepEuler< Real, State >( initialTime,
                              stepSize,
                              initialState,
                              stateDerivativePointer,
                              finalTime,
                              finalState );

    REQUIRE( finalTime  == ( initialTime + stepSize ) );
    REQUIRE( finalState == initialState );
}

TEST_CASE( "Test Euler integrator for Burden & Faires: Table 5.1", "[euler]" )
{
    const State initialState( { 0.5 } );
    const Real initialTime = 0.0;
    const Real stepSize = 0.2;

    Real currentTime = initialTime;
    State currentState = initialState;

    const Real tolerance = 1.0e-7;

    std::map< Real, Real > burdenFairesTable5_1Data;
    burdenFairesTable5_1Data[ 0.2 ] = 0.8000000;
    burdenFairesTable5_1Data[ 0.4 ] = 1.1520000;
    burdenFairesTable5_1Data[ 0.6 ] = 1.5504000;
    burdenFairesTable5_1Data[ 0.8 ] = 1.9884800;
    burdenFairesTable5_1Data[ 1.0 ] = 2.4581760;
    burdenFairesTable5_1Data[ 1.2 ] = 2.9498112;
    burdenFairesTable5_1Data[ 1.4 ] = 3.4517734;
    burdenFairesTable5_1Data[ 1.6 ] = 3.9501281;
    burdenFairesTable5_1Data[ 1.8 ] = 4.4281538;
    burdenFairesTable5_1Data[ 2.0 ] = 4.8657845;

    BurdenFaires dynamics;

    using namespace std::placeholders;
    auto stateDerivativePointer = std::bind( &BurdenFaires::computeStateDerivative,
                                             &dynamics,
                                             _1,
                                             _2 );

    for ( const auto& pair : burdenFairesTable5_1Data )
    {
        stepEuler< Real, State >( currentTime,
                                  stepSize,
                                  currentState,
                                  stateDerivativePointer,
                                  currentTime,
                                  currentState );
        REQUIRE( pair.first == Approx( currentTime ).epsilon( tolerance ) );
        REQUIRE( pair.second == Approx( currentState[0] ).epsilon( tolerance ) );
    }
}

} // namespace tests
} // namespace integrate
