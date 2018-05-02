/*
 * Copyright (c) 2017 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <functional>
#include <iostream>
#include <vector>

#include <catch.hpp>

#include "integrate/euler.hpp"
#include "integrate/dummy.hpp"

namespace integrate
{
namespace tests
{

typedef double Real;
typedef std::vector< Real > State;

class ZeroDynamics
{
public:

    ZeroDynamics( const State& anInitialState )
        : initialState( anInitialState )
    { }

    const State computeStateDerivative( const Real currentTime, const State& currentState )
    {
        State stateDerivative = currentState;

        for ( unsigned int i = 0; i < stateDerivative.size( ); ++i )
        {
            stateDerivative[ i ] = 0.0;
        }

        return stateDerivative;
    }

    const State initialState;

protected:
private:
};

class Dynamics
{
public:

    Dynamics( ){ }

    const State computeStateDerivative( const Real currentTime, const State& currentState )
    {
        State stateDerivative = currentState;

        for ( unsigned int i = 0; i < stateDerivative.size( ); ++i )
        {
            stateDerivative[ i ] = 0.0;
        }

        return stateDerivative;
    }

protected:
private:
};

TEST_CASE( "Test Euler integrator for zero dynamics", "[euler]" )
{
    State initialState( 3 );
    initialState[ 0 ] = 1.2;
    initialState[ 1 ] = 2.3;
    initialState[ 2 ] = -3.6;

    const Real initialTime = 1.0;
    const Real stepSize = 0.1;

    State finalState( 3 );
    finalState[ 0 ] = 0.0;
    finalState[ 1 ] = 0.0;
    finalState[ 2 ] = 0.0;

    Real finalTime = 0.0;

    ZeroDynamics dynamics( initialState );

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

TEST_CASE( "Test Euler integrator", "[euler]" )
{
    State initialState( 3 );
    initialState[ 0 ] = 1.2;
    initialState[ 1 ] = 2.3;
    initialState[ 1 ] = -3.6;

    const Real initialTime = 0.0;

    Dynamics dynamics( );

    // using namespace std::placeholders;
    // auto stateDerivativePointer = std::bind( &Dynamics::computeStateDerivative,
    //                                          &dynamics,
    //                                          _1,
    //                                          _2 );
    // stepEuler< Real, State >( 1.0, 0.1, initialState, stateDerivativePointer );
}


} // namespace tests
} // namespace integrate
