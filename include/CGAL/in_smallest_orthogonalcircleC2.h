// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
// file          : include/CGAL/in_smallest_orthogonalcircleC2.h
// package       : Alpha_shapes_2 (8.3)
// source        : $RCSfile: in_smallest_orthogonalcircleC2.h,v $
// revision      : $Revision: 1.5 $
// revision_date : $Date: 1999/11/05 16:37:28 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IN_SMALLEST_ORTHOGONALCIRCLEC2_H 
#define CGAL_IN_SMALLEST_ORTHOGONALCIRCLEC2_H

#ifndef CGAL_POINTC2_H
#include <CGAL/Cartesian/Point_2.h>
#endif // CGAL_POINTC2_H

#ifndef CGAL_WEIGHTED_POINT_H
#include <CGAL/Weighted_point.h>
#endif // CGAL_WEIGHTED_POINT_H

#include <CGAL/predicates/in_smallest_orthogonalcircle_ftC2.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template< class FT >
inline
Bounded_side
in_smallest_orthogonalcircle(
			     const Weighted_point<Point_2< Cartesian<FT> >, FT > &p,
			     const Weighted_point<Point_2< Cartesian<FT> >, FT > &q,
			     const Weighted_point<Point_2< Cartesian<FT> >, FT > &t) 
{

 
  FT px(p.point().x());
  FT py(p.point().y());
  FT pw(p.weight());
  FT qx(q.point().x());
  FT qy(q.point().y());
  FT qw(q.weight());
  FT tx(t.point().x());
  FT ty(t.point().y());
  FT tw(t.weight());

  return in_smallest_orthogonalcircleC2(px, py, pw,
					qx, qy, qw,
					tx, ty, tw);
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //CGAL_IN_SMALLEST_ORTHOGONALCIRCLEC2_H
