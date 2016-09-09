// Copyright (c) 2001  Max-Planck-Institute Saarbruecken (Germany).
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
// $Source: /CVSROOT/CGAL/Packages/Convex_hull_2/include/CGAL/Convex_hull_projective_xy_traits_2.h,v $
// $Revision: 1.11 $ $Date: 2004/02/21 15:47:10 $
// $Name:  $
//
// Author(s)     : Susan Hert

#ifndef CGAL_CONVEX_HULL_PROJECTIVE_XY_TRAITS_2_H
#define CGAL_CONVEX_HULL_PROJECTIVE_XY_TRAITS_2_H

#include <CGAL/predicates/kernel_ftC2.h>
#include <CGAL/functional_base.h>

namespace CGAL {

template <class Point_3>
class Less_xy_plane_xy_2 
{
public:
   typedef bool          result_type;
   typedef Arity_tag<2>  Arity;

   bool 
   operator()(const Point_3& p, const Point_3& q) const
   { 
     return 
        compare_lexicographically_xyC2(p.x(), p.y(), q.x(), q.y()) == SMALLER;
   }
};

template <class Point_3>
class Equal_xy_plane_xy_2 
{
public:
   typedef bool          result_type;
   typedef Arity_tag<2>  Arity;

   bool 
   operator()(const Point_3& p, const Point_3& q) const
   { 
     return 
        compare_lexicographically_xyC2(p.x(), p.y(), q.x(), q.y()) == EQUAL;
   }
};

template <class Point_3>
class Less_yx_plane_xy_2 
{
public:
   typedef bool          result_type;
   typedef Arity_tag<2>  Arity;

   bool 
   operator()(const Point_3& p, const Point_3& q) const
   { 
     return 
        compare_lexicographically_xyC2(p.y(), p.x(), q.y(), q.x()) == SMALLER;
   }
};

template <class Point_3>
class Left_turn_plane_xy_2 
{
public:
   typedef bool          result_type;
   typedef Arity_tag<3>  Arity;

   bool 
   operator()(const Point_3& p, const Point_3& q, const Point_3& r) const
   { 
      return orientationC2(p.x(), p.y(), q.x(), q.y(), r.x(), r.y()) == 
                                                                 LEFT_TURN;
   }
};

template <class Point_3>
class Less_dist_to_line_plane_xy_2
{
public:
   typedef bool          result_type;
   typedef Arity_tag<4>  Arity;

   bool
   operator()(const Point_3& p, const Point_3& q,
              const Point_3& r, const Point_3& s) const
   {
      Comparison_result
         res = cmp_signed_dist_to_lineC2(p.x(), p.y(), q.x(), q.y(),
                                         r.x(), r.y(), s.x(), s.y());
      if ( res == LARGER )
         return false;
      else if ( res == SMALLER )
         return true;
      else
         return compare_lexicographically_xyC2(r.x(), r.y(), s.x(), s.y()) 
             == SMALLER;
   }
};

template <class Point_3>
class Less_rotate_ccw_plane_xy_2
{
public:
   typedef bool           result_type;
   typedef Arity_tag< 3 > Arity;

   bool
   operator()(const Point_3& r, const Point_3& p, const Point_3& q) const
   {
      Orientation orient =
               orientationC2(r.x(), r.y(), p.x(), p.y(), q.x(), q.y());
      if ( orient ==  LEFT_TURN )
         return true;
      else if ( orient == RIGHT_TURN )
         return false;
      else
      {
         if (p.x() == r.x() && p.y() == r.y()) return false;
         if (q.x() == r.x() && q.y() == r.y()) return true;
         if (p.x() == q.x() && p.y() == q.y()) return false;
         return 
            collinear_are_ordered_along_lineC2(r.x(), r.y(), 
                                               q.x(), q.y(), p.x(), p.y()); 
      }
   }
};


template <class Point_3>
class Convex_hull_projective_xy_traits_2 
{
public:
    typedef Point_3                             Point_2;
    typedef Less_xy_plane_xy_2<Point_3>         Less_xy_2;
    typedef Equal_xy_plane_xy_2<Point_3>        Equal_2;    
    typedef Less_yx_plane_xy_2<Point_3>         Less_yx_2;
    typedef Left_turn_plane_xy_2<Point_3>       Left_turn_2;
    typedef Less_rotate_ccw_plane_xy_2<Point_3> Less_rotate_ccw_2;
    typedef Less_dist_to_line_plane_xy_2<Point_3> 
                                                Less_signed_distance_to_line_2;
    Less_xy_2
    less_xy_2_object() const
    {  return Less_xy_2(); }

    Equal_2
    equal_2_object() const
    {  return Equal_2(); }

    Less_yx_2
    less_yx_2_object() const
    {  return Less_yx_2(); }

    Left_turn_2
    left_turn_2_object() const
    {  return Left_turn_2(); }

    Less_rotate_ccw_2
    less_rotate_ccw_2_object() const
    {  return Less_rotate_ccw_2(); }

    Less_signed_distance_to_line_2
    less_signed_distance_to_line_2_object() const
    {  return Less_signed_distance_to_line_2(); }
};

}
#endif // CGAL_CONVEX_HULL_PROJECTIVE_XY_TRAITS_2_H
