/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <vector>

#include "testState.hpp"

namespace integrate
{
namespace tests
{

class ZeroDynamics
{
public:

    const State computeStateDerivative( const Real currentTime, const State& currentState )
    {
        return State( { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } );
    }

protected:
private:
};

class BurdenFaires
{
public:

    const State computeStateDerivative( const Real currentTime, const State& currentState )
    {
        std::vector< Real > stateDerivativeArray( currentState.size( ) );
        for ( unsigned int i = 0; i < stateDerivativeArray.size( ); ++i )
        {
            stateDerivativeArray[ i ] = currentState[ i ] - ( currentTime * currentTime ) + 1.0;
        }
        return State( stateDerivativeArray );
    }

protected:
private:
};

} // namespace tests
} // namespace integrate
