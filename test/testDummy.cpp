/*
 * Copyright (c) 2017 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <catch.hpp>

#include "integrate/dummy.hpp"

namespace integrate
{
namespace tests
{

TEST_CASE( "Test dummy function", "[dummy]" )
{
    REQUIRE( getDummy( ) == 0 );
}

} // namespace tests
} // namespace integrate
