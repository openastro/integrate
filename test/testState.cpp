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
        vector = rightHandSide.vector;
    }

    return *this;
}

State& State::operator+=( const State& rightHandSide )
{
    *this = *this + rightHandSide;
    return *this;
}

bool State::operator==( const State& rightHandSide ) const
{
    return ( ( *this ).vector == rightHandSide.vector );
}

State operator+( const State& leftHandSide, const State& rightHandSide )
{
    Vector vector( leftHandSide.size( ) );
    for ( unsigned int i = 0; i < vector.size( ); i++ )
    {
        vector[ i ] = leftHandSide[ i ] + rightHandSide[ i ];
    }

    return State( vector );
}

State operator*( const Real multiplier, const State& state )
{
    Vector vector( state.size( ) );
    for ( unsigned int i = 0; i < vector.size( ); i++ )
    {
        vector[ i ] = multiplier * state[ i ];
    }
    return State( vector );
}

State operator*( const State& state, const Real multiplier )
{
    return multiplier * state;
}

} // namespace tests
} // namespace integrate
