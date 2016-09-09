// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// release       : CGAL-2.1
// release_date  : 2000, January 11
// 
// file          : include/CGAL/Arithmetic_filter/predicates/in_smallest_orthogonalcircle_ftC2.h
// package       : Interval_arithmetic (4.39)
// author(s)     : Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
// email         : cgal@cs.uu.nl
//
// ======================================================================

// This file is automatically generated by
// scripts/filtered_predicates_generator.pl

#ifndef CGAL_ARITHMETIC_FILTER_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H
#define CGAL_ARITHMETIC_FILTER_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H

CGAL_BEGIN_NAMESPACE

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#else
template <>
#endif
/* CGAL_MEDIUM_INLINE */
Oriented_side
in_smallest_orthogonalcircleC2(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Protected, CGAL_IA_CACHE> &px,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Protected, CGAL_IA_CACHE> &py,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Protected, CGAL_IA_CACHE> &pw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Protected, CGAL_IA_CACHE> &qx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Protected, CGAL_IA_CACHE> &qy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Protected, CGAL_IA_CACHE> &qw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Protected, CGAL_IA_CACHE> &tx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Protected, CGAL_IA_CACHE> &ty,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Protected, CGAL_IA_CACHE> &tw)
{
  FPU_CW_t backup = FPU_get_and_set_cw(CGAL_FE_UPWARD);
  try
  {
    Oriented_side result = in_smallest_orthogonalcircleC2(
		px.interval(),
		py.interval(),
		pw.interval(),
		qx.interval(),
		qy.interval(),
		qw.interval(),
		tx.interval(),
		ty.interval(),
		tw.interval());
    FPU_set_cw(backup);
    return result;
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_set_cw(backup);
    return in_smallest_orthogonalcircleC2(
		px.exact(),
		py.exact(),
		pw.exact(),
		qx.exact(),
		qy.exact(),
		qw.exact(),
		tx.exact(),
		ty.exact(),
		tw.exact());
  }
}

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#else
template <>
#endif
/* CGAL_MEDIUM_INLINE */
Oriented_side
in_smallest_orthogonalcircleC2(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Advanced, CGAL_IA_CACHE> &px,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Advanced, CGAL_IA_CACHE> &py,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Advanced, CGAL_IA_CACHE> &pw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Advanced, CGAL_IA_CACHE> &qx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Advanced, CGAL_IA_CACHE> &qy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Advanced, CGAL_IA_CACHE> &qw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Advanced, CGAL_IA_CACHE> &tx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Advanced, CGAL_IA_CACHE> &ty,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Dynamic, Advanced, CGAL_IA_CACHE> &tw)
{
  CGAL_expensive_assertion(FPU_empiric_test() == CGAL_FE_UPWARD);
  try
  {
    return in_smallest_orthogonalcircleC2(
		px.interval(),
		py.interval(),
		pw.interval(),
		qx.interval(),
		qy.interval(),
		qw.interval(),
		tx.interval(),
		ty.interval(),
		tw.interval());
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    FPU_CW_t backup = FPU_get_and_set_cw(CGAL_FE_TONEAREST);
    Oriented_side result = in_smallest_orthogonalcircleC2(
		px.exact(),
		py.exact(),
		pw.exact(),
		qx.exact(),
		qy.exact(),
		qw.exact(),
		tx.exact(),
		ty.exact(),
		tw.exact());
    FPU_set_cw(backup);
    return result;
  }
}

#ifdef CGAL_IA_NEW_FILTERS

struct Static_Filtered_in_smallest_orthogonalcircleC2_9
{
  static double _bound;
  static double _epsilon_0;
  static unsigned number_of_failures; // ?
  static unsigned number_of_updates;

  static Oriented_side update_epsilon(
	const Static_filter_error &px,
	const Static_filter_error &py,
	const Static_filter_error &pw,
	const Static_filter_error &qx,
	const Static_filter_error &qy,
	const Static_filter_error &qw,
	const Static_filter_error &tx,
	const Static_filter_error &ty,
	const Static_filter_error &tw,
	double & epsilon_0)
  {
    typedef Static_filter_error FT;
  
    FT dpx = px-qx;
    FT dpy = py-qy;
    FT dtx = tx-qx;
    FT dty = ty-qy;
    FT dpz = square(dpx)+square(dpy);
   
    return Oriented_side (Static_Filtered_sign_1::update_epsilon((square(dtx)+square(dty)-tw+qw)*dpz
  			     -(dpz-pw+qw)*(dpx*dtx+dpy*dty),
  		epsilon_0));
  }

  // Call this function from the outside to update the context.
  static void new_bound (const double b) // , const double error = 0)
  {
    _bound = b;
    number_of_updates++;
    // recompute the epsilons: "just" call it over Static_filter_error.
    // That's the tricky part that might not work for everything.
    (void) update_epsilon(b,b,b,b,b,b,b,b,b,_epsilon_0);
    // TODO: We should verify that all epsilons have really been updated.
  }

  static Oriented_side epsilon_variant(
	const Restricted_double &px,
	const Restricted_double &py,
	const Restricted_double &pw,
	const Restricted_double &qx,
	const Restricted_double &qy,
	const Restricted_double &qw,
	const Restricted_double &tx,
	const Restricted_double &ty,
	const Restricted_double &tw,
	const double & epsilon_0)
  {
    typedef Restricted_double FT;
  
    FT dpx = px-qx;
    FT dpy = py-qy;
    FT dtx = tx-qx;
    FT dty = ty-qy;
    FT dpz = square(dpx)+square(dpy);
   
    return Oriented_side (Static_Filtered_sign_1::epsilon_variant((square(dtx)+square(dty)-tw+qw)*dpz
  			     -(dpz-pw+qw)*(dpx*dtx+dpy*dty),
  		epsilon_0));
  }
};

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#else
template <>
#endif
/* CGAL_MEDIUM_INLINE */
Oriented_side
in_smallest_orthogonalcircleC2(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Protected, CGAL_IA_CACHE> &px,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Protected, CGAL_IA_CACHE> &py,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Protected, CGAL_IA_CACHE> &pw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Protected, CGAL_IA_CACHE> &qx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Protected, CGAL_IA_CACHE> &qy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Protected, CGAL_IA_CACHE> &qw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Protected, CGAL_IA_CACHE> &tx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Protected, CGAL_IA_CACHE> &ty,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Protected, CGAL_IA_CACHE> &tw)
{
//   bool re_adjusted = false;
  const double SAF_bound = Static_Filtered_in_smallest_orthogonalcircleC2_9::_bound;

  // Check the bounds.  All arguments must be <= SAF_bound.
  if (
	fabs(px.to_double()) > SAF_bound ||
	fabs(py.to_double()) > SAF_bound ||
	fabs(pw.to_double()) > SAF_bound ||
	fabs(qx.to_double()) > SAF_bound ||
	fabs(qy.to_double()) > SAF_bound ||
	fabs(qw.to_double()) > SAF_bound ||
	fabs(tx.to_double()) > SAF_bound ||
	fabs(ty.to_double()) > SAF_bound ||
	fabs(tw.to_double()) > SAF_bound)
  {
// re_adjust:
    // Compute the new bound.
    double NEW_bound = 0.0;
    NEW_bound = std::max(NEW_bound, fabs(px.to_double()));
    NEW_bound = std::max(NEW_bound, fabs(py.to_double()));
    NEW_bound = std::max(NEW_bound, fabs(pw.to_double()));
    NEW_bound = std::max(NEW_bound, fabs(qx.to_double()));
    NEW_bound = std::max(NEW_bound, fabs(qy.to_double()));
    NEW_bound = std::max(NEW_bound, fabs(qw.to_double()));
    NEW_bound = std::max(NEW_bound, fabs(tx.to_double()));
    NEW_bound = std::max(NEW_bound, fabs(ty.to_double()));
    NEW_bound = std::max(NEW_bound, fabs(tw.to_double()));
    // Re-adjust the context.
    Static_Filtered_in_smallest_orthogonalcircleC2_9::new_bound(NEW_bound);
  }

  try
  {
    return Static_Filtered_in_smallest_orthogonalcircleC2_9::epsilon_variant(
		px.dbl(),
		py.dbl(),
		pw.dbl(),
		qx.dbl(),
		qy.dbl(),
		qw.dbl(),
		tx.dbl(),
		ty.dbl(),
		tw.dbl(),
		Static_Filtered_in_smallest_orthogonalcircleC2_9::_epsilon_0);
  }
  catch (...)
  {
    // if (!re_adjusted) {  // It failed, we re-adjust once.
      // re_adjusted = true;
      // goto re_adjust;
    // }
    Static_Filtered_in_smallest_orthogonalcircleC2_9::number_of_failures++;
    return in_smallest_orthogonalcircleC2(
		px.exact(),
		py.exact(),
		pw.exact(),
		qx.exact(),
		qy.exact(),
		qw.exact(),
		tx.exact(),
		ty.exact(),
		tw.exact());
  }
}

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#else
template <>
#endif
/* CGAL_MEDIUM_INLINE */
Oriented_side
in_smallest_orthogonalcircleC2(
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Advanced, CGAL_IA_CACHE> &px,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Advanced, CGAL_IA_CACHE> &py,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Advanced, CGAL_IA_CACHE> &pw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Advanced, CGAL_IA_CACHE> &qx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Advanced, CGAL_IA_CACHE> &qy,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Advanced, CGAL_IA_CACHE> &qw,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Advanced, CGAL_IA_CACHE> &tx,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Advanced, CGAL_IA_CACHE> &ty,
    const Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, Static, Advanced, CGAL_IA_CACHE> &tw)
{
  CGAL_assertion_code(
    const double SAF_bound = Static_Filtered_in_smallest_orthogonalcircleC2_9::_bound; )
  CGAL_assertion(!(
	fabs(px.to_double()) > SAF_bound ||
	fabs(py.to_double()) > SAF_bound ||
	fabs(pw.to_double()) > SAF_bound ||
	fabs(qx.to_double()) > SAF_bound ||
	fabs(qy.to_double()) > SAF_bound ||
	fabs(qw.to_double()) > SAF_bound ||
	fabs(tx.to_double()) > SAF_bound ||
	fabs(ty.to_double()) > SAF_bound ||
	fabs(tw.to_double()) > SAF_bound));

  try
  {
    return Static_Filtered_in_smallest_orthogonalcircleC2_9::epsilon_variant(
		px.dbl(),
		py.dbl(),
		pw.dbl(),
		qx.dbl(),
		qy.dbl(),
		qw.dbl(),
		tx.dbl(),
		ty.dbl(),
		tw.dbl(),
		Static_Filtered_in_smallest_orthogonalcircleC2_9::_epsilon_0);
  }
  catch (...)
  {
    Static_Filtered_in_smallest_orthogonalcircleC2_9::number_of_failures++;
    return in_smallest_orthogonalcircleC2(
		px.exact(),
		py.exact(),
		pw.exact(),
		qx.exact(),
		qy.exact(),
		qw.exact(),
		tx.exact(),
		ty.exact(),
		tw.exact());
  }
}

#endif // CGAL_IA_NEW_FILTERS

CGAL_END_NAMESPACE

#endif // CGAL_ARITHMETIC_FILTER_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H