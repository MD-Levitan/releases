// ======================================================================
//
// Copyright (c) 1999,2000 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// file          : include/CGAL/Arithmetic_filter/predicates/Regular_triangulation_rtH2.h
// package       : Interval_arithmetic (4.58)
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

// This file is automatically generated by
// scripts/filtered_predicates_generator.pl

#ifndef CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_RTH2_H
#define CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_RTH2_H

CGAL_BEGIN_NAMESPACE

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, bool CGAL_IA_PROTECTED,
           class CGAL_IA_CACHE >
#else
static
#endif
/*  */
Oriented_side
power_testH2(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &phx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &phy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &phw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &pwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qhx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qhy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qhw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &rhx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &rhy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &rhw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &rwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &thx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &thy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &thw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &twt)
{
  try
  {
    Protect_FPU_rounding<CGAL_IA_PROTECTED> Protection;
    return power_testH2(
		phx.interval(),
		phy.interval(),
		phw.interval(),
		pwt.interval(),
		qhx.interval(),
		qhy.interval(),
		qhw.interval(),
		qwt.interval(),
		rhx.interval(),
		rhy.interval(),
		rhw.interval(),
		rwt.interval(),
		thx.interval(),
		thy.interval(),
		thw.interval(),
		twt.interval());
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    Protect_FPU_rounding<!CGAL_IA_PROTECTED> Protection(CGAL_FE_TONEAREST);
    return power_testH2(
		phx.exact(),
		phy.exact(),
		phw.exact(),
		pwt.exact(),
		qhx.exact(),
		qhy.exact(),
		qhw.exact(),
		qwt.exact(),
		rhx.exact(),
		rhy.exact(),
		rhw.exact(),
		rwt.exact(),
		thx.exact(),
		thy.exact(),
		thw.exact(),
		twt.exact());
  }
}

#ifdef CGAL_IA_NEW_FILTERS

struct Static_Filtered_power_testH2_16
{
  static double _bound;
  static double _epsilon_0;
  static unsigned number_of_failures; // ?
  static unsigned number_of_updates;

  static Oriented_side update_epsilon(
	const Static_filter_error &phx,
	const Static_filter_error &phy,
	const Static_filter_error &phw,
	const Static_filter_error &pwt,
	const Static_filter_error &qhx,
	const Static_filter_error &qhy,
	const Static_filter_error &qhw,
	const Static_filter_error &qwt,
	const Static_filter_error &rhx,
	const Static_filter_error &rhy,
	const Static_filter_error &rhw,
	const Static_filter_error &rwt,
	const Static_filter_error &thx,
	const Static_filter_error &thy,
	const Static_filter_error &thw,
	const Static_filter_error &twt,
	double & epsilon_0)
  {
    typedef Static_filter_error RT;
  
      RT dphx = phx*phw;
      RT dphy = phy*phw;
      RT dphw = CGAL_NTS square(phw);
      RT dpz = CGAL_NTS square(phx) + CGAL_NTS square(phy) - pwt*dphw;
  
      RT dqhx = qhx*qhw;
      RT dqhy = qhy*qhw;
      RT dqhw = CGAL_NTS square(qhw);
      RT dqz = CGAL_NTS square(qhx) + CGAL_NTS square(qhy) - qwt*dqhw;
  
      RT drhx = rhx*rhw;
      RT drhy = rhy*rhw;
      RT drhw = CGAL_NTS square(rhw);
      RT drz = CGAL_NTS square(rhx) + CGAL_NTS square(rhy) - rwt*drhw;
  
      RT dthx = thx*thw;
      RT dthy = thy*thw;
      RT dthw = CGAL_NTS square(thw);
      RT dtz = CGAL_NTS square(thx) + CGAL_NTS square(thy) - twt*dthw;
  
      return Oriented_side(Static_Filtered_sign_of_determinant4x4_16::update_epsilon(dphx, dphy, dpz, dphw,
  	                                        dqhx, dqhy, dqz, dqhw,
  	                                        drhx, drhy, drz, drhw,
  	                                        dthx, dthy, dtz, dthw,
  		epsilon_0));
  }

  // Call this function from the outside to update the context.
  static void new_bound (const double b) // , const double error = 0)
  {
    _bound = b;
    number_of_updates++;
    // recompute the epsilons: "just" call it over Static_filter_error.
    // That's the tricky part that might not work for everything.
    (void) update_epsilon(b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,b,_epsilon_0);
    // TODO: We should verify that all epsilons have really been updated.
  }

  static Oriented_side epsilon_variant(
	const Restricted_double &phx,
	const Restricted_double &phy,
	const Restricted_double &phw,
	const Restricted_double &pwt,
	const Restricted_double &qhx,
	const Restricted_double &qhy,
	const Restricted_double &qhw,
	const Restricted_double &qwt,
	const Restricted_double &rhx,
	const Restricted_double &rhy,
	const Restricted_double &rhw,
	const Restricted_double &rwt,
	const Restricted_double &thx,
	const Restricted_double &thy,
	const Restricted_double &thw,
	const Restricted_double &twt,
	const double & epsilon_0)
  {
    typedef Restricted_double RT;
  
      RT dphx = phx*phw;
      RT dphy = phy*phw;
      RT dphw = CGAL_NTS square(phw);
      RT dpz = CGAL_NTS square(phx) + CGAL_NTS square(phy) - pwt*dphw;
  
      RT dqhx = qhx*qhw;
      RT dqhy = qhy*qhw;
      RT dqhw = CGAL_NTS square(qhw);
      RT dqz = CGAL_NTS square(qhx) + CGAL_NTS square(qhy) - qwt*dqhw;
  
      RT drhx = rhx*rhw;
      RT drhy = rhy*rhw;
      RT drhw = CGAL_NTS square(rhw);
      RT drz = CGAL_NTS square(rhx) + CGAL_NTS square(rhy) - rwt*drhw;
  
      RT dthx = thx*thw;
      RT dthy = thy*thw;
      RT dthw = CGAL_NTS square(thw);
      RT dtz = CGAL_NTS square(thx) + CGAL_NTS square(thy) - twt*dthw;
  
      return Oriented_side(Static_Filtered_sign_of_determinant4x4_16::epsilon_variant(dphx, dphy, dpz, dphw,
  	                                        dqhx, dqhy, dqz, dqhw,
  	                                        drhx, drhy, drz, drhw,
  	                                        dthx, dthy, dtz, dthw,
  		epsilon_0));
  }
};

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#else
static
#endif
/*  */
Oriented_side
power_testH2(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &phx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &phy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &phw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &pwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &qhx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &qhy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &qhw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &qwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &rhx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &rhy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &rhw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &rwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &thx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &thy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &thw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &twt)
{
//   bool re_adjusted = false;
  const double SAF_bound = Static_Filtered_power_testH2_16::_bound;

  // Check the bounds.  All arguments must be <= SAF_bound.
  if (
	fabs(phx.to_double()) > SAF_bound ||
	fabs(phy.to_double()) > SAF_bound ||
	fabs(phw.to_double()) > SAF_bound ||
	fabs(pwt.to_double()) > SAF_bound ||
	fabs(qhx.to_double()) > SAF_bound ||
	fabs(qhy.to_double()) > SAF_bound ||
	fabs(qhw.to_double()) > SAF_bound ||
	fabs(qwt.to_double()) > SAF_bound ||
	fabs(rhx.to_double()) > SAF_bound ||
	fabs(rhy.to_double()) > SAF_bound ||
	fabs(rhw.to_double()) > SAF_bound ||
	fabs(rwt.to_double()) > SAF_bound ||
	fabs(thx.to_double()) > SAF_bound ||
	fabs(thy.to_double()) > SAF_bound ||
	fabs(thw.to_double()) > SAF_bound ||
	fabs(twt.to_double()) > SAF_bound)
  {
// re_adjust:
    // Compute the new bound.
    double NEW_bound = 0.0;
    NEW_bound = max(NEW_bound, fabs(phx.to_double()));
    NEW_bound = max(NEW_bound, fabs(phy.to_double()));
    NEW_bound = max(NEW_bound, fabs(phw.to_double()));
    NEW_bound = max(NEW_bound, fabs(pwt.to_double()));
    NEW_bound = max(NEW_bound, fabs(qhx.to_double()));
    NEW_bound = max(NEW_bound, fabs(qhy.to_double()));
    NEW_bound = max(NEW_bound, fabs(qhw.to_double()));
    NEW_bound = max(NEW_bound, fabs(qwt.to_double()));
    NEW_bound = max(NEW_bound, fabs(rhx.to_double()));
    NEW_bound = max(NEW_bound, fabs(rhy.to_double()));
    NEW_bound = max(NEW_bound, fabs(rhw.to_double()));
    NEW_bound = max(NEW_bound, fabs(rwt.to_double()));
    NEW_bound = max(NEW_bound, fabs(thx.to_double()));
    NEW_bound = max(NEW_bound, fabs(thy.to_double()));
    NEW_bound = max(NEW_bound, fabs(thw.to_double()));
    NEW_bound = max(NEW_bound, fabs(twt.to_double()));
    // Re-adjust the context.
    Static_Filtered_power_testH2_16::new_bound(NEW_bound);
  }

  try
  {
    return Static_Filtered_power_testH2_16::epsilon_variant(
		phx.dbl(),
		phy.dbl(),
		phw.dbl(),
		pwt.dbl(),
		qhx.dbl(),
		qhy.dbl(),
		qhw.dbl(),
		qwt.dbl(),
		rhx.dbl(),
		rhy.dbl(),
		rhw.dbl(),
		rwt.dbl(),
		thx.dbl(),
		thy.dbl(),
		thw.dbl(),
		twt.dbl(),
		Static_Filtered_power_testH2_16::_epsilon_0);
  }
  catch (...)
  {
    // if (!re_adjusted) {  // It failed, we re-adjust once.
      // re_adjusted = true;
      // goto re_adjust;
    // }
    Static_Filtered_power_testH2_16::number_of_failures++;
    return power_testH2(
		phx.exact(),
		phy.exact(),
		phw.exact(),
		pwt.exact(),
		qhx.exact(),
		qhy.exact(),
		qhw.exact(),
		qwt.exact(),
		rhx.exact(),
		rhy.exact(),
		rhw.exact(),
		rwt.exact(),
		thx.exact(),
		thy.exact(),
		thw.exact(),
		twt.exact());
  }
}

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#else
static
#endif
/*  */
Oriented_side
power_testH2(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &phx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &phy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &phw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &pwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &qhx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &qhy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &qhw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &qwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &rhx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &rhy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &rhw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &rwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &thx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &thy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &thw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &twt)
{
  CGAL_assertion_code(
    const double SAF_bound = Static_Filtered_power_testH2_16::_bound; )
  CGAL_assertion(!(
	fabs(phx.to_double()) > SAF_bound ||
	fabs(phy.to_double()) > SAF_bound ||
	fabs(phw.to_double()) > SAF_bound ||
	fabs(pwt.to_double()) > SAF_bound ||
	fabs(qhx.to_double()) > SAF_bound ||
	fabs(qhy.to_double()) > SAF_bound ||
	fabs(qhw.to_double()) > SAF_bound ||
	fabs(qwt.to_double()) > SAF_bound ||
	fabs(rhx.to_double()) > SAF_bound ||
	fabs(rhy.to_double()) > SAF_bound ||
	fabs(rhw.to_double()) > SAF_bound ||
	fabs(rwt.to_double()) > SAF_bound ||
	fabs(thx.to_double()) > SAF_bound ||
	fabs(thy.to_double()) > SAF_bound ||
	fabs(thw.to_double()) > SAF_bound ||
	fabs(twt.to_double()) > SAF_bound));

  try
  {
    return Static_Filtered_power_testH2_16::epsilon_variant(
		phx.dbl(),
		phy.dbl(),
		phw.dbl(),
		pwt.dbl(),
		qhx.dbl(),
		qhy.dbl(),
		qhw.dbl(),
		qwt.dbl(),
		rhx.dbl(),
		rhy.dbl(),
		rhw.dbl(),
		rwt.dbl(),
		thx.dbl(),
		thy.dbl(),
		thw.dbl(),
		twt.dbl(),
		Static_Filtered_power_testH2_16::_epsilon_0);
  }
  catch (...)
  {
    Static_Filtered_power_testH2_16::number_of_failures++;
    return power_testH2(
		phx.exact(),
		phy.exact(),
		phw.exact(),
		pwt.exact(),
		qhx.exact(),
		qhy.exact(),
		qhw.exact(),
		qwt.exact(),
		rhx.exact(),
		rhy.exact(),
		rhw.exact(),
		rwt.exact(),
		thx.exact(),
		thy.exact(),
		thw.exact(),
		twt.exact());
  }
}

#endif // CGAL_IA_NEW_FILTERS

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, bool CGAL_IA_PROTECTED,
           class CGAL_IA_CACHE >
#else
static
#endif
/*  */
Oriented_side
power_testH2(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &phx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &phy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &phw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &pwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qhx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qhy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qhw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &qwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &thx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &thy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &thw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, CGAL_IA_PROTECTED, CGAL_IA_CACHE> &twt)
{
  try
  {
    Protect_FPU_rounding<CGAL_IA_PROTECTED> Protection;
    return power_testH2(
		phx.interval(),
		phy.interval(),
		phw.interval(),
		pwt.interval(),
		qhx.interval(),
		qhy.interval(),
		qhw.interval(),
		qwt.interval(),
		thx.interval(),
		thy.interval(),
		thw.interval(),
		twt.interval());
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    Protect_FPU_rounding<!CGAL_IA_PROTECTED> Protection(CGAL_FE_TONEAREST);
    return power_testH2(
		phx.exact(),
		phy.exact(),
		phw.exact(),
		pwt.exact(),
		qhx.exact(),
		qhy.exact(),
		qhw.exact(),
		qwt.exact(),
		thx.exact(),
		thy.exact(),
		thw.exact(),
		twt.exact());
  }
}

#ifdef CGAL_IA_NEW_FILTERS

struct Static_Filtered_power_testH2_12
{
  static double _bound;
  static double _epsilon_0,_epsilon_1;
  static unsigned number_of_failures; // ?
  static unsigned number_of_updates;

  static Oriented_side update_epsilon(
	const Static_filter_error &phx,
	const Static_filter_error &phy,
	const Static_filter_error &phw,
	const Static_filter_error &pwt,
	const Static_filter_error &qhx,
	const Static_filter_error &qhy,
	const Static_filter_error &qhw,
	const Static_filter_error &qwt,
	const Static_filter_error &thx,
	const Static_filter_error &thy,
	const Static_filter_error &thw,
	const Static_filter_error &twt,
	double & epsilon_0,
	double & epsilon_1)
  {
    typedef Static_filter_error RT;
  
      
      
      RT pa, qa, ta;
  
      if (phx * qhw != qhx * phw )
      {
  	pa = phx*phw;
  	qa = qhx*qhw;
  	ta = thx*thw;
      }
      else
      {   
  	pa = phy*phw;
  	qa = qhy*qhw;
  	ta = thy*thw;
      }
  
      RT dphw = CGAL_NTS square(phw);
      RT dpz = CGAL_NTS square(phx) + CGAL_NTS square(phy) - pwt*dphw;
  
      RT dqhw = CGAL_NTS square(qhw);
      RT dqz = CGAL_NTS square(qhx) + CGAL_NTS square(qhy) - qwt*dqhw;
  
      RT dthw = CGAL_NTS square(thw);
      RT dtz = CGAL_NTS square(thx) + CGAL_NTS square(thy) - twt*dthw;
  
      return Oriented_side(CGAL_NTS Static_Filtered_compare_2::update_epsilon(pa, qa,
  		epsilon_0) *
  	                 Static_Filtered_sign_of_determinant3x3_9::update_epsilon(pa, dpz, dphw,
  				                qa, dqz, dqhw,
  				                ta, dtz, dthw,
  		epsilon_1));
  }

  // Call this function from the outside to update the context.
  static void new_bound (const double b) // , const double error = 0)
  {
    _bound = b;
    number_of_updates++;
    // recompute the epsilons: "just" call it over Static_filter_error.
    // That's the tricky part that might not work for everything.
    (void) update_epsilon(b,b,b,b,b,b,b,b,b,b,b,b,_epsilon_0,_epsilon_1);
    // TODO: We should verify that all epsilons have really been updated.
  }

  static Oriented_side epsilon_variant(
	const Restricted_double &phx,
	const Restricted_double &phy,
	const Restricted_double &phw,
	const Restricted_double &pwt,
	const Restricted_double &qhx,
	const Restricted_double &qhy,
	const Restricted_double &qhw,
	const Restricted_double &qwt,
	const Restricted_double &thx,
	const Restricted_double &thy,
	const Restricted_double &thw,
	const Restricted_double &twt,
	const double & epsilon_0,
	const double & epsilon_1)
  {
    typedef Restricted_double RT;
  
      
      
      RT pa, qa, ta;
  
      if (phx * qhw != qhx * phw )
      {
  	pa = phx*phw;
  	qa = qhx*qhw;
  	ta = thx*thw;
      }
      else
      {   
  	pa = phy*phw;
  	qa = qhy*qhw;
  	ta = thy*thw;
      }
  
      RT dphw = CGAL_NTS square(phw);
      RT dpz = CGAL_NTS square(phx) + CGAL_NTS square(phy) - pwt*dphw;
  
      RT dqhw = CGAL_NTS square(qhw);
      RT dqz = CGAL_NTS square(qhx) + CGAL_NTS square(qhy) - qwt*dqhw;
  
      RT dthw = CGAL_NTS square(thw);
      RT dtz = CGAL_NTS square(thx) + CGAL_NTS square(thy) - twt*dthw;
  
      return Oriented_side(CGAL_NTS Static_Filtered_compare_2::epsilon_variant(pa, qa,
  		epsilon_0) *
  	                 Static_Filtered_sign_of_determinant3x3_9::epsilon_variant(pa, dpz, dphw,
  				                qa, dqz, dqhw,
  				                ta, dtz, dthw,
  		epsilon_1));
  }
};

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#else
static
#endif
/*  */
Oriented_side
power_testH2(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &phx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &phy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &phw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &pwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &qhx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &qhy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &qhw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &qwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &thx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &thy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &thw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, true, CGAL_IA_CACHE> &twt)
{
//   bool re_adjusted = false;
  const double SAF_bound = Static_Filtered_power_testH2_12::_bound;

  // Check the bounds.  All arguments must be <= SAF_bound.
  if (
	fabs(phx.to_double()) > SAF_bound ||
	fabs(phy.to_double()) > SAF_bound ||
	fabs(phw.to_double()) > SAF_bound ||
	fabs(pwt.to_double()) > SAF_bound ||
	fabs(qhx.to_double()) > SAF_bound ||
	fabs(qhy.to_double()) > SAF_bound ||
	fabs(qhw.to_double()) > SAF_bound ||
	fabs(qwt.to_double()) > SAF_bound ||
	fabs(thx.to_double()) > SAF_bound ||
	fabs(thy.to_double()) > SAF_bound ||
	fabs(thw.to_double()) > SAF_bound ||
	fabs(twt.to_double()) > SAF_bound)
  {
// re_adjust:
    // Compute the new bound.
    double NEW_bound = 0.0;
    NEW_bound = max(NEW_bound, fabs(phx.to_double()));
    NEW_bound = max(NEW_bound, fabs(phy.to_double()));
    NEW_bound = max(NEW_bound, fabs(phw.to_double()));
    NEW_bound = max(NEW_bound, fabs(pwt.to_double()));
    NEW_bound = max(NEW_bound, fabs(qhx.to_double()));
    NEW_bound = max(NEW_bound, fabs(qhy.to_double()));
    NEW_bound = max(NEW_bound, fabs(qhw.to_double()));
    NEW_bound = max(NEW_bound, fabs(qwt.to_double()));
    NEW_bound = max(NEW_bound, fabs(thx.to_double()));
    NEW_bound = max(NEW_bound, fabs(thy.to_double()));
    NEW_bound = max(NEW_bound, fabs(thw.to_double()));
    NEW_bound = max(NEW_bound, fabs(twt.to_double()));
    // Re-adjust the context.
    Static_Filtered_power_testH2_12::new_bound(NEW_bound);
  }

  try
  {
    return Static_Filtered_power_testH2_12::epsilon_variant(
		phx.dbl(),
		phy.dbl(),
		phw.dbl(),
		pwt.dbl(),
		qhx.dbl(),
		qhy.dbl(),
		qhw.dbl(),
		qwt.dbl(),
		thx.dbl(),
		thy.dbl(),
		thw.dbl(),
		twt.dbl(),
		Static_Filtered_power_testH2_12::_epsilon_0,
		Static_Filtered_power_testH2_12::_epsilon_1);
  }
  catch (...)
  {
    // if (!re_adjusted) {  // It failed, we re-adjust once.
      // re_adjusted = true;
      // goto re_adjust;
    // }
    Static_Filtered_power_testH2_12::number_of_failures++;
    return power_testH2(
		phx.exact(),
		phy.exact(),
		phw.exact(),
		pwt.exact(),
		qhx.exact(),
		qhy.exact(),
		qhw.exact(),
		qwt.exact(),
		thx.exact(),
		thy.exact(),
		thw.exact(),
		twt.exact());
  }
}

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#else
static
#endif
/*  */
Oriented_side
power_testH2(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &phx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &phy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &phw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &pwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &qhx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &qhy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &qhw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &qwt,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &thx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &thy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &thw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, false, CGAL_IA_CACHE> &twt)
{
  CGAL_assertion_code(
    const double SAF_bound = Static_Filtered_power_testH2_12::_bound; )
  CGAL_assertion(!(
	fabs(phx.to_double()) > SAF_bound ||
	fabs(phy.to_double()) > SAF_bound ||
	fabs(phw.to_double()) > SAF_bound ||
	fabs(pwt.to_double()) > SAF_bound ||
	fabs(qhx.to_double()) > SAF_bound ||
	fabs(qhy.to_double()) > SAF_bound ||
	fabs(qhw.to_double()) > SAF_bound ||
	fabs(qwt.to_double()) > SAF_bound ||
	fabs(thx.to_double()) > SAF_bound ||
	fabs(thy.to_double()) > SAF_bound ||
	fabs(thw.to_double()) > SAF_bound ||
	fabs(twt.to_double()) > SAF_bound));

  try
  {
    return Static_Filtered_power_testH2_12::epsilon_variant(
		phx.dbl(),
		phy.dbl(),
		phw.dbl(),
		pwt.dbl(),
		qhx.dbl(),
		qhy.dbl(),
		qhw.dbl(),
		qwt.dbl(),
		thx.dbl(),
		thy.dbl(),
		thw.dbl(),
		twt.dbl(),
		Static_Filtered_power_testH2_12::_epsilon_0,
		Static_Filtered_power_testH2_12::_epsilon_1);
  }
  catch (...)
  {
    Static_Filtered_power_testH2_12::number_of_failures++;
    return power_testH2(
		phx.exact(),
		phy.exact(),
		phw.exact(),
		pwt.exact(),
		qhx.exact(),
		qhy.exact(),
		qhw.exact(),
		qwt.exact(),
		thx.exact(),
		thy.exact(),
		thw.exact(),
		twt.exact());
  }
}

#endif // CGAL_IA_NEW_FILTERS

CGAL_END_NAMESPACE

#endif // CGAL_ARITHMETIC_FILTER_REGULAR_TRIANGULATION_RTH2_H
