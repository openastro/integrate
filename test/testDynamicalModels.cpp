/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

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

} // namespace tests
} // namespace integrate
