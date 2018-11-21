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
 * quantile function of the univariate Bernoulli distribution
 */

//
// single input

namespace internal
{

template<typename T>
statslib_constexpr
T
qbern_compute(const T p, const T prob_par)
noexcept
{
    return( !bern_sanity_check(prob_par) ? \
                STLIM<T>::quiet_NaN() :
            //
            p < T(0) || p > T(1) ? \
                STLIM<T>::quiet_NaN() :
            //
            p > (T(1) - prob_par) ? \
                llint_t(1) : 
                llint_t(0) );
}

template<typename T1, typename T2, typename TC = common_return_t<T1,T2>>
statslib_constexpr
TC
qbern_type_check(const T1 p, const T2 prob_par)
noexcept
{
    return qbern_compute(static_cast<TC>(p),static_cast<TC>(prob_par));
}

}

/**
 * @brief Quantile function of the Bernoulli distribution
 *
 * @param p a real-valued input.
 * @param prob_par the probability parameter, a real-valued input.
 *
 * @return the quantile function evaluated at \c p.
 * 
 * Example:
 * \code{.cpp} stats::qbern(0.5,0.4); \endcode
 */

template<typename T1, typename T2>
statslib_constexpr
common_return_t<T1,T2> // not llint_t so we can return NaN
qbern(const T1 p, const T2 prob_par)
noexcept
{
    return internal::qbern_type_check(p,prob_par);
}

//
// matrix/vector input

namespace internal
{

template<typename Ta, typename Tb, typename Tc>
statslib_inline
void
qbern_vec(const Ta* __stats_pointer_settings__ vals_in, const Tb prob_par,
                Tc* __stats_pointer_settings__ vals_out, const ullint_t num_elem)
{
    EVAL_DIST_FN_VEC(qbern,vals_in,vals_out,num_elem,prob_par);
}

}

#ifdef STATS_USE_ARMA
template<typename Ta, typename Tb, typename Tc>
statslib_inline
ArmaMat<Tc>
qbern(const ArmaMat<Ta>& X, const Tb prob_par)
{
    ArmaMat<Tc> mat_out(X.n_rows,X.n_cols);

    internal::qbern_vec<Ta,Tb,Tc>(X.memptr(),prob_par,mat_out.memptr(),mat_out.n_elem);

    return mat_out;
}

template<typename mT, typename tT, typename Tb>
statslib_inline
mT
qbern(const ArmaGen<mT,tT>& X, const Tb prob_par)
{
    return qbern(X.eval(),prob_par);
}
#endif

#ifdef STATS_USE_BLAZE
template<typename Ta, typename Tb, typename Tc, bool To>
statslib_inline
BlazeMat<Tc,To>
qbern(const BlazeMat<Ta,To>& X, const Tb prob_par)
{
    BlazeMat<Tc,To> mat_out(X.rows(),X.columns());

    internal::qbern_vec<Ta,Tb,Tc>(X.data(),prob_par,mat_out.data(),X.rows()*X.spacing());

    return mat_out;
}
#endif

#ifdef STATS_USE_EIGEN
template<typename Ta, typename Tb, typename Tc, int iTr, int iTc>
statslib_inline
EigMat<Tc,iTr,iTc>
qbern(const EigMat<Ta,iTr,iTc>& X, const Tb prob_par)
{
    EigMat<Tc,iTr,iTc> mat_out(X.rows(),X.cols());

    internal::qbern_vec<Ta,Tb,Tc>(X.data(),prob_par,mat_out.data(),mat_out.size());

    return mat_out;
}
#endif
