/*
 * Copyright (c) 2014-2022 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <vector>

#include "testDynamicalModels.hpp"

namespace integrate
{
namespace tests
{

//! Compute zero dynamics.
const State computeZeroDynamics( const Real time, const State& state )
{
    return State( { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } );
}

//! Compute zero dynamics.
const State ZeroDynamics::operator( )( const Real time, const State& state ) const
{
    return State( { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } );
}

//! Compute Burden & Faires dynamics.
const State BurdenFaires::operator( )( const Real time, const State& state ) const
{
    return State( { state[ 0 ] - ( time * time ) + 1.0 } );
}

} // namespace tests
} // namespace integrate
