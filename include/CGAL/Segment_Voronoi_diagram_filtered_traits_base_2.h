// Copyright (c) 2003,2004  INRIA Sophia-Antipolis (France) and
// Notre Dame University (U.S.A.).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Segment_Voronoi_diagram_2/include/CGAL/Segment_Voronoi_diagram_filtered_traits_base_2.h,v $
// $Revision: 1.8 $ $Date: 2004/08/13 16:47:15 $
// $Name:  $
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>



#ifndef CGAL_SEGMENT_VORONOI_DIAGRAM_FILTERED_TRAITS_BASE_2_H
#define CGAL_SEGMENT_VORONOI_DIAGRAM_FILTERED_TRAITS_BASE_2_H

#include <CGAL/Segment_Voronoi_diagram_short_names_2.h>

#include <CGAL/Segment_Voronoi_diagram_traits_base_2.h>

#include <CGAL/Number_type_traits.h>
#include <CGAL/Segment_Voronoi_diagram_kernel_wrapper_2.h>



#include <CGAL/Filtered_predicate.h>
#include <CGAL/Filtered_construction.h>

#include <CGAL/number_utils_classes.h>
#include <CGAL/Cartesian_converter.h>

CGAL_BEGIN_NAMESPACE


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// the filtered Traits class
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------

template<class CK_t, class CK_MTag, class EK_t, class EK_MTag,
	 class FK_t, class FK_MTag, class C2E_t, class C2F_t,
	 class ITag>
class Segment_Voronoi_diagram_filtered_traits_base_2
{
private:
  typedef
  Segment_Voronoi_diagram_filtered_traits_base_2<CK_t, CK_MTag,
						 EK_t, EK_MTag,
						 FK_t, FK_MTag,
						 C2E_t, C2F_t,
						 ITag>  Self;

  typedef Segment_Voronoi_diagram_traits_base_2<CK_t,CK_MTag,ITag> CK_traits;
  typedef Segment_Voronoi_diagram_traits_base_2<FK_t,FK_MTag,ITag> FK_traits;
  typedef Segment_Voronoi_diagram_traits_base_2<EK_t,EK_MTag,ITag> EK_traits;

  typedef Segment_Voronoi_diagram_kernel_wrapper_2<CK_t,ITag>  CK;
  typedef Segment_Voronoi_diagram_kernel_wrapper_2<FK_t,ITag>  FK;
  typedef Segment_Voronoi_diagram_kernel_wrapper_2<EK_t,ITag>  EK;

  typedef Svd_cartesian_converter<CK, EK, C2E_t>            C2E;
  typedef Svd_cartesian_converter<CK, FK, C2F_t>            C2F;

  typedef
  Cartesian_converter<FK, CK, To_double<typename FK::RT> >  F2C_t;
  typedef Svd_cartesian_converter<FK, CK, F2C_t>            F2C;

  typedef
  Cartesian_converter<EK, CK, To_double<typename EK::RT> >  E2C_t;
  typedef Svd_cartesian_converter<EK, CK, E2C_t>            E2C;
  
  // Types for the construction kernel
  typedef typename CK::Point_2                CK_Point_2;
  typedef typename CK::Line_2                 CK_Line_2;
  typedef typename CK::Segment_2              CK_Segment_2;
  typedef typename CK::Ray_2                  CK_Ray_2;

  typedef typename CK::Site_2                 CK_Site_2;

  typedef typename CK::FT                     CK_FT;
  typedef typename CK::RT                     CK_RT;

  // Types for the exact kernel
  typedef typename EK::Point_2                EK_Point_2;
  typedef typename EK::Line_2                 EK_Line_2;
  typedef typename EK::Segment_2              EK_Segment_2;
  typedef typename EK::Ray_2                  EK_Ray_2;

  typedef typename EK::Site_2                 EK_Site_2;

  typedef typename EK::FT                     EK_FT;
  typedef typename EK::RT                     EK_RT;

  // Types for the filtering kernel
  typedef typename FK::Point_2                FK_Point_2;
  typedef typename FK::Line_2                 FK_Line_2;
  typedef typename FK::Segment_2              FK_Segment_2;
  typedef typename FK::Ray_2                  FK_Ray_2;

  typedef typename FK::Site_2                 FK_Site_2;

  typedef typename FK::FT                     FK_FT;
  typedef typename FK::RT                     FK_RT;

public:
  //-----------------------------------------------------------------------
  //                  TYPE DEFINITIONS
  //-----------------------------------------------------------------------

  // BASIC TYPES
  //------------
  typedef CK_t                          R;
  typedef CK_MTag                       Method_tag;
  typedef ITag                          Intersections_tag;

  typedef CK_t                          Construction_kernel;
  typedef FK_t                          Filtering_kernel;
  typedef EK_t                          Exact_kernel;

  typedef CK_traits                     Construction_traits;
  typedef FK_traits                     Filtering_traits;
  typedef EK_traits                     Exact_traits;

  typedef CK_MTag                       Construction_traits_method_tag;
  typedef FK_MTag                       Filtering_traits_method_tag;
  typedef EK_MTag                       Exact_traits_method_tag;

  typedef typename CK::Point_2          Point_2;
  typedef typename CK::Line_2           Line_2;
  typedef typename CK::Segment_2        Segment_2;
  typedef typename CK::Ray_2            Ray_2;
  //  typedef typename CK::Circle_2         Circle_2;
  typedef typename CK::Site_2           Site_2;

  typedef typename CK::Object_2         Object_2;

  typedef typename CK::FT               FT;
  typedef typename CK::RT               RT;

  typedef typename CK::Rep_tag          Rep_tag;

  typedef CGALi::Svd_arrangement_enum::Arrangement_type Arrangement_type;

private:
  typedef typename CK_traits::Construct_svd_vertex_2
  CK_Construct_svd_vertex_2;

  typedef typename FK_traits::Construct_svd_vertex_2
  FK_Construct_svd_vertex_2;

  typedef typename EK_traits::Construct_svd_vertex_2
  EK_Construct_svd_vertex_2;

public:
  // OBJECT CONSTRUCTION & ASSIGNMENT
  //---------------------------------
  typedef typename CK::Construct_object_2     Construct_object_2;
  typedef typename CK::Assign_2               Assign_2;

  // CONSTRUCTIONS
  //--------------
  // vertex and Voronoi circle
  typedef
  Filtered_construction<CK_Construct_svd_vertex_2,
			EK_Construct_svd_vertex_2,
			FK_Construct_svd_vertex_2,
			C2E, C2F, E2C, F2C>
  Construct_svd_vertex_2;

  //  typedef typename CK::Construct_site_2   Construct_site_2;

  //  typedef typename CK_traits::Construct_svd_circle_2
  //  Construct_svd_circle_2;

private:
  // PREDICATES FOR THE TWO KERNELS
  //-------------------------------
#if 0
  // Predicates for the filtering kernel
  typedef typename FK_traits::Compare_x_2        FK_Compare_x_2;
  typedef typename FK_traits::Compare_y_2        FK_Compare_y_2;
  typedef typename FK_traits::Orientation_2      FK_Orientation_2;
  typedef typename FK_traits::Equal_2            FK_Equal_2;
  typedef typename FK_traits::Are_parallel_2     FK_Are_parallel_2;

  typedef typename FK_traits::Oriented_side_of_bisector_2
  FK_Oriented_side_of_bisector_2;

  typedef typename FK_traits::Vertex_conflict_2  FK_Vertex_conflict_2;

  typedef typename FK_traits::Finite_edge_interior_conflict_2
  FK_Finite_edge_interior_conflict_2;

  typedef typename FK_traits::Infinite_edge_interior_conflict_2
  FK_Infinite_edge_interior_conflict_2;

  typedef typename FK_traits::Is_degenerate_edge_2
  FK_Is_degenerate_edge_2;

  typedef typename FK_traits::Arrangement_type_2 FK_Arrangement_type_2;
  typedef typename FK_traits::Oriented_side_2    FK_Oriented_side_2;

  // Predicates for the exact kernel
  typedef typename EK_traits::Compare_x_2        EK_Compare_x_2;
  typedef typename EK_traits::Compare_y_2        EK_Compare_y_2;
  typedef typename EK_traits::Orientation_2      EK_Orientation_2;
  typedef typename EK_traits::Equal_2            EK_Equal_2;
  typedef typename EK_traits::Are_parallel_2     EK_Are_parallel_2;

  typedef typename EK_traits::Oriented_side_of_bisector_2
  EK_Oriented_side_of_bisector_2;

  typedef typename EK_traits::Vertex_conflict_2  EK_Vertex_conflict_2;

  typedef typename EK_traits::Finite_edge_interior_conflict_2
  EK_Finite_edge_interior_conflict_2;

  typedef typename EK_traits::Infinite_edge_interior_conflict_2
  EK_Infinite_edge_interior_conflict_2;

  typedef typename EK_traits::Is_degenerate_edge_2
  EK_Is_degenerate_edge_2;

  typedef typename EK_traits::Arrangement_type_2 EK_Arrangement_type_2;
  typedef typename EK_traits::Oriented_side_2    EK_Oriented_side_2;

#else
  // Predicates for the filtering kernel
  typedef Svd_compare_x_2<FK>                    FK_Compare_x_2;
  typedef Svd_compare_y_2<FK>                    FK_Compare_y_2;
  typedef Svd_orientation_C2<FK>                 FK_Orientation_2;
  typedef Svd_are_same_points_C2<FK>             FK_Equal_2;
  typedef Svd_are_parallel_C2<FK>                FK_Are_parallel_2;

  typedef Svd_oriented_side_of_bisector_C2<FK,FK_MTag>
  FK_Oriented_side_of_bisector_2;

  typedef Svd_incircle_2<FK,FK_MTag>             FK_Vertex_conflict_2;

  typedef Svd_finite_edge_interior_2<FK,FK_MTag>
  FK_Finite_edge_interior_conflict_2;

  typedef Svd_infinite_edge_interior_2<FK,FK_MTag>
  FK_Infinite_edge_interior_conflict_2;

  typedef Svd_is_degenerate_edge_C2<FK,FK_MTag>  FK_Is_degenerate_edge_2;
  typedef Svd_arrangement_type_C2<FK>            FK_Arrangement_type_2;
  typedef Svd_oriented_side_C2<FK,FK_MTag>       FK_Oriented_side_2;

  // Predicates for the exact kernel
  typedef Svd_compare_x_2<EK>                    EK_Compare_x_2;
  typedef Svd_compare_y_2<EK>                    EK_Compare_y_2;
  typedef Svd_orientation_C2<EK>                 EK_Orientation_2;
  typedef Svd_are_same_points_C2<EK>             EK_Equal_2;
  typedef Svd_are_parallel_C2<EK>                EK_Are_parallel_2;

  typedef Svd_oriented_side_of_bisector_C2<EK,EK_MTag>
  EK_Oriented_side_of_bisector_2;

  typedef Svd_incircle_2<EK,EK_MTag>             EK_Vertex_conflict_2;

  typedef Svd_finite_edge_interior_2<EK,EK_MTag>
  EK_Finite_edge_interior_conflict_2;

  typedef Svd_infinite_edge_interior_2<EK,EK_MTag>
  EK_Infinite_edge_interior_conflict_2;

  typedef Svd_is_degenerate_edge_C2<EK,EK_MTag>  EK_Is_degenerate_edge_2;
  typedef Svd_arrangement_type_C2<EK>            EK_Arrangement_type_2;
  typedef Svd_oriented_side_C2<EK,EK_MTag>       EK_Oriented_side_2;
#endif

public:
  // PREDICATES
  //-----------
  typedef
  Filtered_predicate<EK_Compare_x_2, FK_Compare_x_2, C2E, C2F>
  Compare_x_2;

  typedef
  Filtered_predicate<EK_Compare_y_2, FK_Compare_y_2, C2E, C2F>
  Compare_y_2;

  typedef
  Filtered_predicate<EK_Orientation_2, FK_Orientation_2, C2E, C2F>
  Orientation_2;

  typedef
  Filtered_predicate<EK_Equal_2, FK_Equal_2, C2E, C2F>
  Equal_2;

  typedef
  Filtered_predicate<EK_Are_parallel_2,	FK_Are_parallel_2, C2E, C2F>
  Are_parallel_2;

  typedef
  Filtered_predicate<EK_Oriented_side_of_bisector_2,
		     FK_Oriented_side_of_bisector_2, C2E, C2F>
  Oriented_side_of_bisector_2;

  typedef
  Filtered_predicate<EK_Vertex_conflict_2,
		     FK_Vertex_conflict_2, C2E, C2F>
  Vertex_conflict_2;

  typedef
  Filtered_predicate<EK_Finite_edge_interior_conflict_2,
		     FK_Finite_edge_interior_conflict_2, C2E, C2F>
  Finite_edge_interior_conflict_2;

  typedef
  Filtered_predicate<EK_Infinite_edge_interior_conflict_2,
		     FK_Infinite_edge_interior_conflict_2, C2E, C2F>
  Infinite_edge_interior_conflict_2;

  typedef
  Filtered_predicate<EK_Is_degenerate_edge_2,
		     FK_Is_degenerate_edge_2, C2E, C2F>
  Is_degenerate_edge_2;

private:
  typedef
  Filtered_predicate<EK_Arrangement_type_2, FK_Arrangement_type_2, C2E, C2F>
  Arrangement_type_2_base;

public:
  struct Arrangement_type_2
    : public Arrangement_type_2_base, public CGALi::Svd_arrangement_enum
  {};

  typedef
  Filtered_predicate<EK_Oriented_side_2, FK_Oriented_side_2, C2E, C2F>
  Oriented_side_2;

public:
  //-----------------------------------------------------------------------
  //                  ACCESS TO OBJECTS
  //-----------------------------------------------------------------------

  // OBJECT CONSTRUCTION & ASSIGNMENT
  //---------------------------------
  Assign_2
  assign_2_object() const {
    return Assign_2();
  }

  Construct_object_2
  construct_object_2_object() const { 
    return Construct_object_2();
  }

  // CONSTRUCTIONS
  //--------------
  Construct_svd_vertex_2
  construct_svd_vertex_2_object() const { 
    return Construct_svd_vertex_2();
  }

  /*
  Construct_site_2
  construct_site_2_object() const { 
    return Construct_site_2();
  }
  */

  /*
  Construct_svd_circle_2
  construct_svd_circle_2_object() const {
    return Construct_svd_circle_2();
  }
  */

  // PREDICATES
  //-----------
  Compare_x_2
  compare_x_2_object() const {
    return Compare_x_2();
  }

  Compare_y_2
  compare_y_2_object() const {
    return Compare_y_2();
  }

  Orientation_2
  orientation_2_object() const {
    return Orientation_2();
  }

  Equal_2
  equal_2_object() const {
    return Equal_2();
  }

  Are_parallel_2
  are_parallel_2_object() const {
    return Are_parallel_2();
  }

  Oriented_side_of_bisector_2
  oriented_side_of_bisector_2_object() const {
    return Oriented_side_of_bisector_2();
  }

  Vertex_conflict_2
  vertex_conflict_2_object() const {
    return Vertex_conflict_2();
  }

  Finite_edge_interior_conflict_2
  finite_edge_interior_conflict_2_object() const {
    return Finite_edge_interior_conflict_2();
  }

  Infinite_edge_interior_conflict_2
  infinite_edge_interior_conflict_2_object() const {
    return Infinite_edge_interior_conflict_2();
  }

  Is_degenerate_edge_2
  is_degenerate_edge_2_object() const {
    return Is_degenerate_edge_2();
  }

  Arrangement_type_2
  arrangement_type_2_object() const {
    return Arrangement_type_2();
  }

  Oriented_side_2
  oriented_side_2_object() const {
    return Oriented_side_2();
  }
};



CGAL_END_NAMESPACE

#endif // CGAL_SEGMENT_VORONOI_DIAGRAM_FILTERED_TRAITS_BASE_2_H