// Copyright (c) 2005 Rijksuniversiteit Groningen (Netherlands)
// All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Skin_surface_3/include/CGAL/Skin_surface_refinement_policy_3.h $
// $Id: Skin_surface_refinement_policy_3.h 43854 2008-06-27 13:06:20Z nicokruithof $
// 
//
// Author(s)     : Nico Kruithof <Nico@cs.rug.nl>

#ifndef CGAL_SKIN_SURFACE_REFINEMENT_POLICY_3_H
#define CGAL_SKIN_SURFACE_REFINEMENT_POLICY_3_H

#include <CGAL/Cartesian.h>
#include <CGAL/Cartesian_converter.h>

#include <CGAL/Polyhedron_3.h>
#include <CGAL/Skin_surface_polyhedral_items_3.h>

#include <CGAL/intersection_3_1.h>
CGAL_BEGIN_NAMESPACE


template <class SkinSurface_3, class Polyhedron_3>
class Skin_surface_refinement_policy_3
{
public:
  typedef SkinSurface_3                           Skin_surface;
  typedef Polyhedron_3                            Polyhedron;
  typedef typename Polyhedron::Traits             P_traits;

  typedef typename Polyhedron::Vertex_handle      P_vertex_handle;

  typedef typename P_traits::RT          P_rt;
  typedef typename P_traits::Point_3     P_point;
  typedef typename P_traits::Segment_3   P_segment;
  typedef typename P_traits::Line_3      P_line;
  typedef typename P_traits::Vector_3    P_vector;
  typedef typename P_traits::Plane_3     P_plane;

  Skin_surface_refinement_policy_3(Skin_surface const& skin) : ss_3(skin) {
  }
    
  P_point to_surface(P_vertex_handle vh) const
  {
    typename Skin_surface::Bare_point result =
      Cartesian_converter<P_traits, 
      typename Skin_surface::Geometric_traits::Kernel>()(vh->point());
    ss_3.intersect_with_transversal_segment(result);
    return 
      Cartesian_converter
      <typename Skin_surface::Geometric_traits::Kernel, P_traits>()( result );
  }

  P_vector normal(P_vertex_handle vh) const
  {
    // Convert to and from the skin surface kernel
    typename Skin_surface::Bare_point p =
      Cartesian_converter<P_traits, 
         typename Skin_surface::Geometric_traits::Kernel>()(vh->point());
    return  Cartesian_converter<typename Skin_surface::Geometric_traits::Kernel, 
                                P_traits>()( ss_3.normal(p));
  }

protected:
  Skin_surface const &ss_3;
};

template <class SkinSurfaceBase_3, class P_Traits, class SkinSurface_3>
class Skin_surface_refinement_policy_3<
  SkinSurfaceBase_3,
  Polyhedron_3<P_Traits, 
    Skin_surface_polyhedral_items_3<SkinSurface_3> > > 
{
public:
  typedef SkinSurfaceBase_3                          Skin_surface;
  typedef Polyhedron_3<P_Traits, 
    Skin_surface_polyhedral_items_3<SkinSurface_3> > Polyhedron;
  typedef typename Polyhedron::Traits                P_traits;

  typedef typename Polyhedron::Vertex_handle      P_vertex_handle;

  typedef typename P_traits::RT          P_rt;
  typedef typename P_traits::Point_3     P_point;
  typedef typename P_traits::Segment_3   P_segment;
  typedef typename P_traits::Line_3      P_line;
  typedef typename P_traits::Vector_3    P_vector;
  typedef typename P_traits::Plane_3     P_plane;

  Skin_surface_refinement_policy_3(Skin_surface const& skin) : ss_3(skin) {
  }

  P_point to_surface(P_vertex_handle vh) const {
    typename Skin_surface::Bare_point result =
      Cartesian_converter<P_traits, 
      typename Skin_surface::Geometric_traits::Kernel>()(vh->point());

     ss_3.intersect_with_transversal_segment(result,
              vh->halfedge()->facet()->tmc_ch);

    return 
      Cartesian_converter
      <typename Skin_surface::Geometric_traits::Kernel, P_traits>()( result );
  }

  P_vector normal(P_vertex_handle vh) const {
    // Convert to and from the skin surface kernel
    typename Skin_surface::Bare_point p =
      Cartesian_converter<P_traits, 
         typename Skin_surface::Geometric_traits::Kernel>()(vh->point());
    return 
      Cartesian_converter
      <typename Skin_surface::Geometric_traits::Kernel, 
       P_traits>()( ss_3.normal(p, vh->halfedge()->facet()->tmc_ch) );
  }
    
protected:
  Skin_surface const &ss_3;
};

CGAL_END_NAMESPACE


#endif // CGAL_SKIN_SURFACE_REFINEMENT_POLICY_3_H