// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-2.2-I-51 $
// release_date  : $CGAL_Date: 2000/10/01 $
//
// file          : include/CGAL/Optimisation/Construct_point_3.h
// package       : Optimisation_basic (3.8.2)
// maintainer    : Sven Sch�nherr <sven@inf.ethz.ch>
//
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2000/09/13 20:27:51 $
//
// author(s)     : Sven Sch�nherr
// coordinator   : ETH Z�rich (Bernd G�rtner <gaertner@inf.ethz.ch>)
//
// implementation: 3D construction `point'
// ======================================================================

#ifndef CGAL_OPTIMISATION_CONSTRUCT_POINT_3_H
#define CGAL_OPTIMISATION_CONSTRUCT_POINT_3_H

// includes
#ifndef CGAL_POINT_3_H
#  include <CGAL/Point_3.h>
#endif
#ifndef CGAL_PROTECT_VECTOR
#  include <vector>
#  define CGAL_PROTECT_VECTOR
#endif
#ifndef CGAL_PROTECT_FUNCTIONAL
#  include <functional>
#  define CGAL_PROTECT_FUNCTIONAL
#endif
#ifndef CGAL_PROTECT_ITERATOR
#  include <iterator>
#  define CGAL_PROTECT_ITERATOR
#endif

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
template < class R >
class Construct_point_3;

// Class interface
// ===============
template < class R_ >
class Construct_point_3 {
  public:
    // self
    typedef  R_                         R;
    typedef  Construct_point_3<R>       Self;

    // types
    typedef  typename R::Point_3        Point;

    // creation
    Construct_point_3( ) { }

    // operations
    template < class InputIterator >
    Point
    operator() ( int d, InputIterator first, InputIterator last) const
    {
	std::vector<CGAL_TYPENAME_MSVC_NULL R::RT>  coords;
	std::copy( first, last, std::back_inserter( coords));
	if ( coords.size() < 4) {
	    return Point( coords[ 0], coords[ 1], coords[ 2]);
	} else {
	    return Point( coords[ 0], coords[ 1], coords[ 2], coords[ 3]);
	}
    }
};

CGAL_END_NAMESPACE

#endif // CGAL_OPTIMISATION_CONSTRUCT_POINT_3_H

// ===== EOF ==================================================================
