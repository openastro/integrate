/*
 * Copyright (c) 2017 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

namespace integrate
{
namespace tests
{

// //! Declare
// typedef double Real;
// typedef std::vector< Real > State;

//! Zero-dynamics class.
/*!
 * Class containing zero-dynamics model, i.e., dynamical model with state derivatives equal to zero.
 *
 * @tparam Real     Type for real numbers
 * @tparam state    Type for state and state derivatives
 */
template< typename Real, typename State >
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

} // namespace tests
} // namespace integrate
