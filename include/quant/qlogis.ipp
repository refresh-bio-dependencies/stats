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
 * quantile function of the univariate logistic distribution
 */

//
// single input

namespace internal
{

template<typename T>
statslib_constexpr
T
qlogis_compute(const T p, const T mu_par, const T sigma_par)
noexcept
{
    return( mu_par + sigma_par*stmath::log(p/(T(1) - p)) );
}

template<typename T>
statslib_constexpr
T
qlogis_vals_check(const T p, const T mu_par, const T sigma_par)
noexcept
{
    return( !logis_sanity_check(mu_par,sigma_par) ? \
                STLIM<T>::quiet_NaN() :
            //
            p < T(0) || p > T(1) ? \
                STLIM<T>::quiet_NaN() :
            //
            p == T(0) ? \
                - STLIM<T>::infinity() :
            p == T(1) ? \
                STLIM<T>::infinity() :
            //
            qlogis_compute(p,mu_par,sigma_par) );
}

template<typename T1, typename T2, typename T3, typename TC = common_return_t<T1,T2,T3>>
statslib_constexpr
TC
qlogis_type_check(const T1 p, const T2 mu_par, const T3 sigma_par)
noexcept
{
    return qlogis_vals_check(static_cast<TC>(p),static_cast<TC>(mu_par),static_cast<TC>(sigma_par));
}

}

/**
 * @brief Quantile function of the Logistic distribution
 *
 * @param p a real-valued input.
 * @param mu_par the location parameter, a real-valued input.
 * @param sigma_par the scale parameter, a real-valued input.
 *
 * @return the quantile function evaluated at \c p.
 * 
 * Example:
 * \code{.cpp} stats::qlogis(0.5,1.0,2.0); \endcode
 */

template<typename T1, typename T2, typename T3>
statslib_constexpr
common_return_t<T1,T2,T3>
qlogis(const T1 p, const T2 mu_par, const T3 sigma_par)
noexcept
{
    return internal::qlogis_type_check(p,mu_par,sigma_par);
}

//
// matrix/vector input

namespace internal
{

template<typename Ta, typename Tb, typename Tc>
statslib_inline
void
qlogis_vec(const Ta* __stats_pointer_settings__ vals_in, const Tb mu_par, const Tb sigma_par, 
                 Tc* __stats_pointer_settings__ vals_out, const ullint_t num_elem)
{
    EVAL_DIST_FN_VEC(qlogis,vals_in,vals_out,num_elem,mu_par,sigma_par);
}

}

#ifdef STATS_USE_ARMA
template<typename Ta, typename Tb, typename Tc>
statslib_inline
ArmaMat<Tc>
qlogis(const ArmaMat<Ta>& X, const Tb mu_par, const Tb sigma_par)
{
    ArmaMat<Tc> mat_out(X.n_rows,X.n_cols);

    internal::qlogis_vec<Ta,Tb,Tc>(X.memptr(),mu_par,sigma_par,mat_out.memptr(),mat_out.n_elem);

    return mat_out;
}

template<typename mT, typename tT, typename Tb>
statslib_inline
mT
qlogis(const ArmaGen<mT,tT>& X, const Tb mu_par, const Tb sigma_par)
{
    return qlogis(X.eval(),mu_par,sigma_par);
}
#endif

#ifdef STATS_USE_BLAZE
template<typename Ta, typename Tb, typename Tc, bool To>
statslib_inline
BlazeMat<Tc,To>
qlogis(const BlazeMat<Ta,To>& X, const Tb mu_par, const Tb sigma_par)
{
    BlazeMat<Tc,To> mat_out(X.rows(),X.columns());

    internal::qlogis_vec<Ta,Tb,Tc>(X.data(),mu_par,sigma_par,mat_out.data(),X.rows()*X.spacing());

    return mat_out;
}
#endif

#ifdef STATS_USE_EIGEN
template<typename Ta, typename Tb, typename Tc, int iTr, int iTc>
statslib_inline
EigMat<Tc,iTr,iTc>
qlogis(const EigMat<Ta,iTr,iTc>& X, const Tb mu_par, const Tb sigma_par)
{
    EigMat<Tc,iTr,iTc> mat_out(X.rows(),X.cols());

    internal::qlogis_vec<Ta,Tb,Tc>(X.data(),mu_par,sigma_par,mat_out.data(),mat_out.size());

    return mat_out;
}
#endif
