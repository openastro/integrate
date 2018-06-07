/*
 * Copyright (c) 2018 Kartik Kumar (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef INTEGRATE_TEST_DYNAMICAL_MODELS_HPP
#define INTEGRATE_TEST_DYNAMICAL_MODELS_HPP

#include "testState.hpp"

namespace integrate
{
namespace tests
{

//! Compute zero dynamics.
/*!
 * Computes state derivative for a homogeneous system of ordinary differential equations, i.e.,
 *
 *  xdot = F(t,x) = 0
 *
 * @param[in]       time                    Current time
 * @param[in]       state                   Current state
 * @return                                  Computed state derivative
 */
const State computeZeroDynamics( const Real time, const State& state );

//! Zero dynamics functor.
/*!
 * Functor that computes state derivative for a homogeneous system of ordinary differential
 * equations.
 */
class ZeroDynamics
{
public:

    //! Compute zero dynamics.
    /*!
     * Computes state derivative for a homogeneous system of ordinary differential equations, i.e.,
     *
     *  xdot = F(t,x) = 0
     *
     * @param[in]       time                    Current time
     * @param[in]       state                   Current state
     * @return                                  Computed state derivative
     */
    const State operator( )( const Real time, const State& state ) const;

protected:
private:
};

//! Burden & Faires functor.
/*!
 * Functor that computes state derivative for example dynamical system given in
 * Burden & Faires (2001).
*/
class BurdenFaires
{
public:

    //! Compute Burden & Faires dynamics.
    /*!
     * Computes state derivative for following dynamical system given in Burden & Faires (2001).
     *
     *  ydot = F(t,y) = y - t^2 + 1
     *
     * @param[in]       time                    Current time
     * @param[in]       state                   Current state
     * @return                                  Computed state derivative
     */
    const State operator( )( const Real time, const State& state ) const;

protected:
private:
};

} // namespace tests
} // namespace integrate

#endif // INTEGRATE_TEST_DYNAMICAL_MODELS_HPP
