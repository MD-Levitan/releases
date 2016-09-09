// Copyright (c) 1999  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/H3/include/CGAL/Homogeneous/predicates_on_pointsH3.h,v $
// $Revision: 1.14 $ $Date: 2004/09/14 14:00:43 $
// $Name:  $
//
// Author(s)     : Stefan Schirra
 

#ifndef CGAL_PREDICATES_ON_POINTSH3_H
#define CGAL_PREDICATES_ON_POINTSH3_H

#include <CGAL/Homogeneous/PointH3.h>

CGAL_BEGIN_NAMESPACE

template < class R >
CGAL_KERNEL_MEDIUM_INLINE
bool lexicographically_xy_smaller(const PointH3<R> &p,
                                  const PointH3<R> &q)
{
  typedef typename R::RT RT;
  RT pV = p.hx()*q.hw();
  RT qV = q.hx()*p.hw();
  if ( pV < qV )
  {
      return true;
  }
  if ( qV < pV )
  {
      return false;
  }
  // same x
  pV = p.hy()*q.hw();
  qV = q.hy()*p.hw();
  if ( pV < qV )
  {
      return true;
  }
  return false;
}

template < class R>
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_xy(const PointH3<R>& p, const PointH3<R>& q)
{
  typedef typename R::RT RT;
  RT pV = p.hx()*q.hw();
  RT qV = q.hx()*p.hw();
  if ( pV < qV )
  {
      return SMALLER;
  }
  if ( qV < pV )    //   ( pV > qV )
  {
      return LARGER;
  }
  // same x
  pV = p.hy()*q.hw();
  qV = q.hy()*p.hw();
  if ( pV < qV )
  {
      return SMALLER;
  }
  if ( qV < pV )    //   ( pV > qV )
  {
      return LARGER;
  }
  // same x and y
  return EQUAL;
}

template < class R >
CGAL_KERNEL_INLINE
bool
equal_xy(const PointH3<R> &p, const PointH3<R> &q)
{
  return   (p.hx() * q.hw() == q.hx() * p.hw() )
        && (p.hy() * q.hw() == q.hy() * p.hw() );
}

template < class R >  // ???  ->   ==
CGAL_KERNEL_INLINE
bool
equal_xyz(const PointH3<R> &p, const PointH3<R> &q)
{
  return   (p.hx() * q.hw() == q.hx() * p.hw() )
        && (p.hy() * q.hw() == q.hy() * p.hw() )
        && (p.hz() * q.hw() == q.hz() * p.hw() );
}

template < class R >
CGAL_KERNEL_INLINE
bool
less_x(const PointH3<R> &p, const PointH3<R> &q)
{ return   (p.hx() * q.hw() < q.hx() * p.hw() ); }


template < class R >
CGAL_KERNEL_INLINE
bool
less_y(const PointH3<R> &p, const PointH3<R> &q)
{ return   (p.hy() * q.hw() < q.hy() * p.hw() ); }

template < class R >
CGAL_KERNEL_INLINE
bool
less_z(const PointH3<R> &p, const PointH3<R> &q)
{ return   (p.hz() * q.hw() < q.hz() * p.hw() ); }

CGAL_END_NAMESPACE

#endif // CGAL_PREDICATES_ON_POINTSH3_H
