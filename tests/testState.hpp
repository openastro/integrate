/*
 * Copyright (c) 2014-2025 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#pragma once

#include <vector>

namespace integrate
{
namespace tests
{

//! Set type for floating-point numbers.
typedef double Real;
//! Set type for n-dimensional vectors.
typedef std::vector<Real> Vector;

//! State class.
/*!
 * Defines a State class that is n-dimensional.
 */
class State
{
public:

    //! Construct state object.
    /*!
     * Constructs state object from an n-dimensional vector.
     *
     * @param[in]  aVector  An n-dimensional vector
     */
    State( const Vector& aVector )
        : vector( aVector )
    { }

    //! Get size of state.
    const int size( ) const { return vector.size( ); }

    //! Get value of ith element of state.
    const Real operator[ ] ( const int i ) const { return vector[ i ]; }

    //! Overload operators.
    State& operator=( const State& rightHandSide );
    State& operator+=( const State& rightHandSide );
    bool operator==( const State& rightHandSide ) const;
    friend State operator+( const State& leftHandSide, const State& rightHandSide );
    friend State operator*( const Real multiplier, const State& state );
    friend State operator*( const State& state, const Real multiplier );

protected:
private:

    //! N-dimensional vector for internal storage of state elements.
    Vector vector;
};

} // namespace tests
} // namespace integrate
