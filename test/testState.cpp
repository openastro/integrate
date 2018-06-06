/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include "testState.hpp"

namespace integrate
{
namespace tests
{

State& State::operator=( const State& rightHandSide )
{
    // Check for self-assignment.
    if ( this != &rightHandSide )
    {
        array = rightHandSide.array;
    }

    return *this;
}

bool State::operator==( const State& rightHandSide ) const
{
    return ( ( *this ).array == rightHandSide.array );
}

State operator+( const State& leftHandSide, const State& rightHandSide )
{
    std::vector< Real > resultArray( leftHandSide.size( ) );
    for ( unsigned int i = 0; i < resultArray.size( ); i++ )
    {
        resultArray[ i ] = leftHandSide[ i ] + rightHandSide[ i ];
    }

    return State( resultArray );
}

State operator*( const Real multiplier, const State& state )
{
    std::vector< Real > resultArray( state.size( ) );
    for ( unsigned int i = 0; i < resultArray.size( ); i++ )
    {
        resultArray[ i ] = multiplier * state[ i ];
    }
    return State( resultArray );
}

State operator*( const State& state, const Real multiplier )
{
    return multiplier * state;
}


} // namespace tests
} // namespace integrate
