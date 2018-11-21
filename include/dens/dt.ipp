/*################################################################################
  ##
  ##   Copyright (C) 2011-2018 Keith O'Hara
  ##
  ##   This file is part of the StatsLib C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

/*
 * pdf of the t-distribution
 */

//
// single input

namespace internal
{

template<typename T>
statslib_constexpr
T
dt_log_mult_term(const T z, const T dof_par)
noexcept
{
    return( - (dof_par/T(2) + T(0.5)) * stmath::log(T(1) + (z/dof_par)*z) );
}

template<typename T>
statslib_constexpr
T
dt_log_cons_term(const T z, const T dof_par)
noexcept
{
    return( stmath::lgamma(dof_par/T(2) + T(0.5)) \
                - T(0.5)*( stmath::log(dof_par) + T(GCEM_LOG_PI) ) \
                - stmath::lgamma(dof_par/T(2)) );
}

template<typename T>
statslib_constexpr
T
dt_log_compute(const T z, const T dof_par)
noexcept
{
    return( dt_log_cons_term(z,dof_par) + dt_log_mult_term(z,dof_par) );
}

template<typename T>
statslib_constexpr
T
dt_vals_check(const T x, const T dof_par, const bool log_form)
noexcept
{
    return( !t_sanity_check(dof_par) ? \
                STLIM<T>::quiet_NaN() :
            //
            dof_par == STLIM<T>::infinity() ? \
                dnorm(x,T(0),T(1),log_form) :
            //
            exp_if(dt_log_compute(x,dof_par), !log_form) );
}

template<typename T1, typename T2, typename TC = common_return_t<T1,T2>>
statslib_constexpr
TC
dt_type_check(const T1 x, const T2 dof_par, const bool log_form)
noexcept
{
    return dt_vals_check(static_cast<TC>(x),static_cast<TC>(dof_par),log_form);
}

}

/**
 * @brief Density function of the t-distribution
 *
 * @param x a real-valued input.
 * @param dof_par the degrees of freedom parameter, a real-valued input.
 * @param log_form return the log-density or the true form.
 *
 * @return the density function evaluated at \c x.
 * 
 * Example:
 * \code{.cpp} stats::dt(0.37,11,false); \endcode
 */

template<typename T1, typename T2>
statslib_constexpr
common_return_t<T1,T2>
dt(const T1 x, const T2 dof_par, const bool log_form)
noexcept
{
    return internal::dt_type_check(x,dof_par,log_form);
}

//
// matrix/vector input

namespace internal
{

template<typename Ta, typename Tb, typename Tc>
statslib_inline
void
dt_vec(const Ta* __stats_pointer_settings__ vals_in, const Tb dof_par, const bool log_form, 
             Tc* __stats_pointer_settings__ vals_out, const ullint_t num_elem)
{
    EVAL_DIST_FN_VEC(dt,vals_in,vals_out,num_elem,dof_par,log_form);
}

}

#ifdef STATS_USE_ARMA
template<typename Ta, typename Tb, typename Tc>
statslib_inline
ArmaMat<Tc>
dt(const ArmaMat<Ta>& X, const Tb dof_par, const bool log_form)
{
    ArmaMat<Tc> mat_out(X.n_rows,X.n_cols);

    internal::dt_vec<Ta,Tb,Tc>(X.memptr(),dof_par,log_form,mat_out.memptr(),mat_out.n_elem);

    return mat_out;
}

template<typename mT, typename tT, typename Tb>
statslib_inline
mT
dt(const ArmaGen<mT,tT>& X, const Tb dof_par, const bool log_form)
{
    return dt(X.eval(),dof_par,log_form);
}
#endif

#ifdef STATS_USE_BLAZE
template<typename Ta, typename Tb, typename Tc, bool To>
statslib_inline
BlazeMat<Tc,To>
dt(const BlazeMat<Ta,To>& X, const Tb dof_par, const bool log_form)
{
    BlazeMat<Tc,To> mat_out(X.rows(),X.columns());

    internal::dt_vec<Ta,Tb,Tc>(X.data(),dof_par,log_form,mat_out.data(),X.rows()*X.spacing());

    return mat_out;
}
#endif

#ifdef STATS_USE_EIGEN
template<typename Ta, typename Tb, typename Tc, int iTr, int iTc>
statslib_inline
EigMat<Tc,iTr,iTc>
dt(const EigMat<Ta,iTr,iTc>& X, const Tb dof_par, const bool log_form)
{
    EigMat<Tc,iTr,iTc> mat_out(X.rows(),X.cols());

    internal::dt_vec<Ta,Tb,Tc>(X.data(),dof_par,log_form,mat_out.data(),mat_out.size());

    return mat_out;
}
#endif
