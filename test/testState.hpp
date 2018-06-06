/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef INTEGRATE_TEST_STATE_HPP
#define INTEGRATE_TEST_STATE_HPP

namespace integrate
{
namespace tests
{

typedef double Real;

class State
{
public:

    State( )
        : array( { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } )
    { }

    State( const std::vector< Real >& anArray )
        : array( anArray )
    { }

    const int size( ) const { return array.size( ); }
    const Real operator[ ] ( const int i ) const { return array[ i ]; }

    State& operator=( const State& rightHandSide );
    bool operator==( const State& rightHandSide ) const;

    friend State operator+( const State& leftHandSide, const State& rightHandSide );
    friend State operator*( const Real multiplier, const State& state );
    // friend State operator*( const State& state, const Real multiplier );

    std::vector< Real > array;

protected:
private:
};

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

#endif // INTEGRATE_TEST_STATE_HPP
