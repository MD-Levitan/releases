// ============================================================================
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
// release       : CGAL-2.2
// release_date  : 2000, September 30
// 
// source        : web_2/advanced_2.fw
// file          : include/CGAL/Old_style_kernel/Direction_2.h
// revision      : 3.2
// revision_date : 06 Apr 2000 
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 

#ifndef CGAL_OLD_STYLE_KERNEL_DIRECTION_2_H
#define CGAL_OLD_STYLE_KERNEL_DIRECTION_2_H

namespace CGAL {

template <class R_>
class Direction_2< R_, Old_style_tag> : public R_::Direction_2_base
{
 public:
  typedef  R_                           R;
  typedef typename R::RT                RT;
  typedef typename R::Vector_2_base     RVector_2;
  typedef typename R::Direction_2_base  RDirection_2;

  Direction_2() {}
  Direction_2(const RDirection_2& d) : RDirection_2(d) {}
  Direction_2(const RVector_2& v) : RDirection_2(v) {}
  Direction_2(const RT &x, const RT &y) :  RDirection_2(x,y) {}
};

} // namespace CGAL
#endif // CGAL_OLD_STYLE_KERNEL_DIRECTION_2_H
