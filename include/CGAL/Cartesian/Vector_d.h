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
// file          : include/CGAL/Cartesian/Vector_d.h
// package       : Cd (1.1.1)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1999/12/07 20:12:58 $
// author(s)     : Herve.Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_CARTESIAN_VECTOR_D_H
#define CGAL_CARTESIAN_VECTOR_D_H

#include <CGAL/Cartesian/redefine_names_d.h>
#include <CGAL/Cartesian/Direction_d.h>
#include <CGAL/d_tuple.h>
#include <algorithm>
#include <functional>

CGAL_BEGIN_NAMESPACE

template < class _R >
class VectorCd
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
// This is a partial specialization
<_R,Cartesian_tag>
#endif
  : public Handle
{
public:
  typedef _R                               R;
  typedef typename R::FT                   FT;
  typedef typename R::RT                   RT;
  typedef const FT*                        const_iterator;
// protected:
  typedef FT*                              iterator;
// public:
#ifndef CGAL_CFG_NO_ADVANCED_KERNEL
  typedef VectorCd<R CGAL_CTAG>            Self;
  typedef typename R::Point_d              Point_d;
  typedef typename R::Direction_d          Direction_d;
  typedef typename R::Aff_transformation_d Aff_transformation_d;
#else
  typedef VectorCd<R>                           Self;
  typedef typename R::Point_d_base              Point_d;
  typedef typename R::Direction_d_base          Direction_d;
  typedef typename R::Aff_transformation_d_base Aff_transformation_d;
#endif
  
  /*
  friend CGAL_FRIEND_INLINE
  Self operator- CGAL_NULL_TMPL_ARGS (const Point_d &p, const Point_d &q);

  friend CGAL_FRIEND_INLINE
  Self operator- CGAL_NULL_TMPL_ARGS (const Point_d &p, const Point_d &q);
  */

  VectorCd(int dim = 0);
  VectorCd(const Self &v);
  VectorCd(const Point_d &p);
  VectorCd(const Direction_d &p);
  VectorCd(int dim, const Null_vector &);
  ~VectorCd();

  template < class InputIterator >
  VectorCd(int dim, InputIterator first, InputIterator last)
  {
    CGAL_kernel_precondition( dim >= 0);
    CGAL_kernel_precondition( last-first == dim || last-first == dim+1 );
    PTR = new _d_tuple<FT>(dim);
    std::copy_n(first,dim,begin());
    if (last-first == dim+1)
      std::transform(begin(),end(),begin(),
	             std::bind2nd(std::divides<FT>(),*(first+dim)));
  }

  Self&          operator=(const Self &v);

  bool           operator==(const Self &v) const;
  bool           operator!=(const Self &v) const;

  bool           operator==(const Null_vector &) const;
  bool           operator!=(const Null_vector &) const;


  FT             cartesian(int i) const;
  FT             operator[](int i) const;
  FT             homogeneous(int i) const;

public:
  Self           operator+(const Self &w) const;
  Self           operator-(const Self &w) const;
  Self           operator-() const;
  FT             operator*(const Self &w) const;
  Self           operator*(const FT &c) const;
  Self           operator/(const FT &c) const;

  Direction_d    direction() const;
  Self           transform(const Aff_transformation_d &) const;

  long           id()        const { return (long) ptr(); }
  int            dimension() const { return ptr()->d; }
  const_iterator begin()     const { return ptr()->e; }
  const_iterator end()       const { return ptr()->e + dimension(); }

// protected:
  iterator       begin()           { return ptr()->e; }
  iterator       end()             { return ptr()->e + dimension(); }

private:
  const _d_tuple<FT>* ptr()  const { return (const _d_tuple<FT>*)PTR; }
  _d_tuple<FT>*       ptr()        { return (_d_tuple<FT>*)PTR; }
};

CGAL_END_NAMESPACE

#ifndef CGAL_CARTESIAN_CLASS_DEFINED
#include <CGAL/Cartesian/Vector_d.C>
#endif 

#endif // CGAL_CARTESIAN_VECTOR_D_H