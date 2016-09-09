// ======================================================================
//
// Copyright (c) 1997-2001 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Optimisation_d_traits_3.h
// package       : Optimisation_basic (3.8.14)
// chapter       : Geometric Optimisation
//
// source        : web/Optimisation_d_traits.aw
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2002/03/26 09:29:58 $
//
// author(s)     : Sven Sch�nherr
// coordinator   : ETH Z�rich (Bernd G�rtner)
//
// implementation: Traits class (3D) for dD optimisation algorithms
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_OPTIMISATION_D_TRAITS_3_H
#define CGAL_OPTIMISATION_D_TRAITS_3_H

// includes
#ifndef CGAL_OPTIMISATION_ACCESS_DIMENSION_3_H
#  include <CGAL/Optimisation/Access_dimension_3.h>
#endif
#ifndef CGAL_OPTIMISATION_ACCESS_COORDINATES_BEGIN_3_H
#  include <CGAL/Optimisation/Access_coordinates_begin_3.h>
#endif
#ifndef CGAL_OPTIMISATION_CONSTRUCT_POINT_3_H
#  include <CGAL/Optimisation/Construct_point_3.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
template < class K_, class ET_ = CGAL_TYPENAME_MSVC_NULL K_::RT,
                     class NT_ = CGAL_TYPENAME_MSVC_NULL K_::RT >
class Optimisation_d_traits_3;

// Class interface
// ===============
template < class K_, class ET_, class NT_>
class Optimisation_d_traits_3 {
  public:
    // self
    typedef  K_                         K;
    typedef  ET_                        ET;
    typedef  NT_                        NT;
    typedef  Optimisation_d_traits_3<K,ET,NT>
                                        Self;

    // types
    typedef  typename K::Point_3        Point_d;

    typedef  typename K::Rep_tag        Rep_tag;

    typedef  typename K::RT             RT;
    typedef  typename K::FT             FT;

    typedef  CGAL::Access_dimension_3<K>      Access_dimension_d;
    typedef  CGAL::Access_coordinates_begin_3<K>
                                        Access_coordinates_begin_d;

    typedef  Construct_point_3<K>       Construct_point_d;
    // this does not (yet) work:
    // typedef  typename K::Construct_point_3    Construct_point_d;

    // creation
    Optimisation_d_traits_3( ) { }
    Optimisation_d_traits_3( const Optimisation_d_traits_3<K_,ET_,NT_>&) {}

    // operations
    Access_dimension_d
    access_dimension_d_object( ) const
        { return Access_dimension_d(); }

    Access_coordinates_begin_d
    access_coordinates_begin_d_object( ) const
        { return Access_coordinates_begin_d(); }

    Construct_point_d
    construct_point_d_object( ) const
        { return Construct_point_d(); }
};

CGAL_END_NAMESPACE

#endif // CGAL_OPTIMISATION_D_TRAITS_3_H

// ===== EOF ==================================================================