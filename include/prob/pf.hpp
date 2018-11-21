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
 * cdf of the F distribution
 */

#ifndef _statslib_pf_HPP
#define _statslib_pf_HPP

//
// single input

template<typename T1, typename T2, typename T3>
statslib_constexpr
common_return_t<T1,T2,T3>
pf(const T1 x, const T2 df1_par, const T3 df2_par, const bool log_form = false) noexcept;

//
// matrix/vector input

#ifdef STATS_USE_ARMA
template<typename Ta, typename Tb, typename Tc = Tb>
statslib_inline
ArmaMat<Tc> pf(const ArmaMat<Ta>& X, const Tb df1_par, const Tb df2_par, const bool log_form = false);

template<typename mT, typename tT, typename Tb>
statslib_inline
mT pf(const ArmaGen<mT,tT>& X, const Tb df1_par, const Tb df2_par, const bool log_form = false);
#endif

#ifdef STATS_USE_BLAZE
template<typename Ta, typename Tb, typename Tc = Tb, bool To = blaze::columnMajor>
statslib_inline
BlazeMat<Tc,To> pf(const BlazeMat<Ta,To>& X, const Tb df1_par, const Tb df2_par, const bool log_form = false);
#endif

#ifdef STATS_USE_EIGEN
template<typename Ta, typename Tb, typename Tc = Tb, int iTr = Eigen::Dynamic, int iTc = Eigen::Dynamic>
statslib_inline
EigMat<Tc,iTr,iTc> pf(const EigMat<Ta,iTr,iTc>& X, const Tb df1_par, const Tb df2_par, const bool log_form = false);
#endif

//
// include implementation files

#include "pf.ipp"

#endif
