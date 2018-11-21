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
 * pdf of the gamma distribution
 */

//
// single input

namespace internal
{

template<typename T>
statslib_constexpr
T
dgamma_log_compute(const T x, const T shape_par, const T scale_par)
noexcept
{
    return( - stmath::lgamma(shape_par) - shape_par*stmath::log(scale_par) \
            + (shape_par-T(1))*stmath::log(x) - x/scale_par );
}

template<typename T>
statslib_constexpr
T
dgamma_limit_vals(const T x, const T shape_par, const T scale_par)
noexcept
{
    return( shape_par == T(0) ? \
                x == T(0) ? \
                    STLIM<T>::infinity() :
                    T(0) :
            // x = 0
            shape_par < T(1) ? \
                STLIM<T>::infinity() :
            shape_par == T(1) ? \
                T(1) / scale_par :
            // x = 0 & shape_par > 1
                T(0) );
}

template<typename T>
statslib_constexpr
T
dgamma_vals_check(const T x, const T shape_par, const T scale_par, const bool log_form)
noexcept
{
    return( !gamma_sanity_check(shape_par,scale_par) ? \
                STLIM<T>::quiet_NaN() :
            //
            x < T(0) ? \
                log_if(T(0),log_form) :
            //
            x == T(0) || shape_par == T(0) ? \
                log_if(dgamma_limit_vals(x,shape_par,scale_par), log_form) :
            //
            exp_if(dgamma_log_compute(x,shape_par,scale_par), !log_form) );
}

template<typename T1, typename T2, typename T3, typename TC = common_return_t<T1,T2,T3>>
statslib_constexpr
TC
dgamma_type_check(const T1 x, const T2 shape_par, const T3 scale_par, const bool log_form)
noexcept
{
    return dgamma_vals_check(static_cast<TC>(x),static_cast<TC>(shape_par),
                             static_cast<TC>(scale_par),log_form);
}

}

/**
 * @brief Density function of the Gamma distribution
 *
 * @param x a real-valued input.
 * @param shape_par the shape parameter, a real-valued input.
 * @param scale_par the scale parameter, a real-valued input.
 * @param log_form return the log-density or the true form.
 *
 * @return the density function evaluated at \c x.
 *
 * Example:
 * \code{.cpp} stats::dgamma(2,2,3,false); \endcode
 */

template<typename T1, typename T2, typename T3>
statslib_constexpr
common_return_t<T1,T2,T3>
dgamma(const T1 x, const T2 shape_par, const T3 scale_par, const bool log_form)
noexcept
{
    return internal::dgamma_type_check(x,shape_par,scale_par,log_form);
}

//
// matrix/vector input

namespace internal
{

template<typename Ta, typename Tb, typename Tc>
statslib_inline
void
dgamma_vec(const Ta* __stats_pointer_settings__ vals_in, const Tb shape_par, const Tb scale_par, const bool log_form, 
                 Tc* __stats_pointer_settings__ vals_out, const ullint_t num_elem)
{
    EVAL_DIST_FN_VEC(dgamma,vals_in,vals_out,num_elem,shape_par,scale_par,log_form);
}

}

#ifdef STATS_USE_ARMA
template<typename Ta, typename Tb, typename Tc>
statslib_inline
ArmaMat<Tc>
dgamma(const ArmaMat<Ta>& X, const Tb shape_par, const Tb scale_par, const bool log_form)
{
    ArmaMat<Tc> mat_out(X.n_rows,X.n_cols);

    internal::dgamma_vec<Ta,Tb,Tc>(X.memptr(),shape_par,scale_par,log_form,mat_out.memptr(),mat_out.n_elem);

    return mat_out;
}

template<typename mT, typename tT, typename Tb>
statslib_inline
mT
dgamma(const ArmaGen<mT,tT>& X, const Tb shape_par, const Tb scale_par, const bool log_form)
{
    return dgamma(X.eval(),shape_par,scale_par,log_form);
}
#endif

#ifdef STATS_USE_BLAZE
template<typename Ta, typename Tb, typename Tc, bool To>
statslib_inline
BlazeMat<Tc,To>
dgamma(const BlazeMat<Ta,To>& X, const Tb shape_par, const Tb scale_par, const bool log_form)
{
    BlazeMat<Tc,To> mat_out(X.rows(),X.columns());

    internal::dgamma_vec<Ta,Tb,Tc>(X.data(),shape_par,scale_par,log_form,mat_out.data(),X.rows()*X.spacing());

    return mat_out;
}
#endif

#ifdef STATS_USE_EIGEN
template<typename Ta, typename Tb, typename Tc, int iTr, int iTc>
statslib_inline
EigMat<Tc,iTr,iTc>
dgamma(const EigMat<Ta,iTr,iTc>& X, const Tb shape_par, const Tb scale_par, const bool log_form)
{
    EigMat<Tc,iTr,iTc> mat_out(X.rows(),X.cols());

    internal::dgamma_vec<Ta,Tb,Tc>(X.data(),shape_par,scale_par,log_form,mat_out.data(),mat_out.size());

    return mat_out;
}
#endif
