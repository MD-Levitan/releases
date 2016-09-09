//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//


// Source: TriangleC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_TRIANGLEC2_H
#define CGAL_TRIANGLEC2_H

#include <CGAL/Threetuple.h>
#include <CGAL/predicates_on_pointsC2.h>



template <class FT>
class CGAL_TriangleC2 : public CGAL_Handle
{
public:
                      CGAL_TriangleC2();
                      CGAL_TriangleC2(const CGAL_TriangleC2<FT> &);
                      CGAL_TriangleC2(const CGAL_PointC2<FT> &p,
                                      const CGAL_PointC2<FT> &q,
                                      const CGAL_PointC2<FT> &r);
                      ~CGAL_TriangleC2();

  CGAL_TriangleC2<FT> &operator=(const CGAL_TriangleC2<FT> &t);

  bool                operator==(const CGAL_TriangleC2<FT> &s) const;
  bool                operator!=(const CGAL_TriangleC2<FT> &s) const;
  int                 id() const;

  CGAL_PointC2<FT>    vertex(int i) const;
  CGAL_PointC2<FT>    operator[](int i) const;


  CGAL_TriangleC2     transform(const CGAL_Aff_transformationC2<FT> &t) const;

  CGAL_Orientation    orientation() const;
  CGAL_Oriented_side  oriented_side(const CGAL_PointC2<FT> &p) const;
  CGAL_Bounded_side   bounded_side(const CGAL_PointC2<FT> &p) const;

  bool                has_on_boundary(const CGAL_PointC2<FT> &p) const;

  bool                has_on_bounded_side(const CGAL_PointC2<FT> &p) const;
  bool                has_on_unbounded_side(const CGAL_PointC2<FT> &p) const;

  bool                has_on_positive_side(const CGAL_PointC2<FT> &p) const;
  bool                has_on_negative_side(const CGAL_PointC2<FT> &p) const;

  bool                is_degenerate() const;

  CGAL_Bbox_2         bbox() const;

private:
  CGAL__Threetuple< CGAL_PointC2<FT> >*   ptr() const;
};


template < class FT >
inline CGAL__Threetuple< CGAL_PointC2<FT> > *CGAL_TriangleC2<FT>::ptr() const
{
  return (CGAL__Threetuple< CGAL_PointC2<FT> >*)PTR;
}


template < class FT >
CGAL_TriangleC2<FT>::CGAL_TriangleC2()
{
  PTR = new CGAL__Threetuple< CGAL_PointC2<FT> >;
}

template < class FT >
CGAL_TriangleC2<FT>::CGAL_TriangleC2(const CGAL_TriangleC2<FT> &t) :
  CGAL_Handle((CGAL_Handle&)t)
{}

template < class FT >
CGAL_TriangleC2<FT>::CGAL_TriangleC2(const CGAL_PointC2<FT> &p,
                                     const CGAL_PointC2<FT> &q,
                                     const CGAL_PointC2<FT> &r)
{
  PTR = new CGAL__Threetuple< CGAL_PointC2<FT> >(p, q, r);
  CGAL_nondegeneracy_assertion;
}

template < class FT >
inline CGAL_TriangleC2<FT>::~CGAL_TriangleC2()
{}


template < class FT >
CGAL_TriangleC2<FT> &CGAL_TriangleC2<FT>::operator=(
                                               const CGAL_TriangleC2<FT> &t)
{
  CGAL_Handle::operator=(t);
  return *this;
}
template < class FT >
bool CGAL_TriangleC2<FT>::operator==(const CGAL_TriangleC2<FT> &t) const
{
  int i;
  bool eq = false;
  for(i = 0; i <= 2; i++)
    {
      if( vertex(0) == t.vertex(i) )
        {
          eq = true;
          break;
        }
    }
  if ( eq )
    {
      return ( vertex(1) == t.vertex(i+1) && vertex(2) == t.vertex(i+2) );
    }
  return false;
}

template < class FT >
inline bool CGAL_TriangleC2<FT>::operator!=(const CGAL_TriangleC2<FT> &t) const
{
  return !(*this == t);
}

template < class FT >
int CGAL_TriangleC2<FT>::id() const
{
  return (int)PTR ;
}
template < class FT >
CGAL_PointC2<FT> CGAL_TriangleC2<FT>::vertex(int i) const
{

  switch (i)
    {
    case 0: return ptr()->e0;
    case 1: return ptr()->e1;
    case 2: return ptr()->e2;
    default:switch (i%3)
             {
             case 0: return ptr()->e0;
             case 1: return ptr()->e1;
             }
    }
  return ptr()->e2;
}

template < class FT >
inline CGAL_PointC2<FT> CGAL_TriangleC2<FT>::operator[](int i) const
{

  return vertex(i);
}
template < class FT >
CGAL_Orientation CGAL_TriangleC2<FT>::orientation() const
{
  return CGAL_orientation(vertex(0), vertex(1), vertex(2));
}
template < class FT >
CGAL_Bounded_side CGAL_TriangleC2<FT>::bounded_side(
                                            const CGAL_PointC2<FT> &p) const
{
  CGAL_Orientation o1 = CGAL_orientation(vertex(0), vertex(1), p),
                   o2 = CGAL_orientation(vertex(1), vertex(2), p),
                   o3 = CGAL_orientation(vertex(2), vertex(3), p),
                   ot = CGAL_orientation(vertex(0), vertex(1), vertex(2));

 if (o1 == CGAL_COLLINEAR || o2 == CGAL_COLLINEAR || o3 == CGAL_COLLINEAR)
    {
      if ((o1 == CGAL_COLLINEAR && CGAL_collinear_between(
                                                  vertex(0), p, vertex(1))) ||
          (o2 == CGAL_COLLINEAR && CGAL_collinear_between(
                                                  vertex(1), p, vertex(2))) ||
          (o3 == CGAL_COLLINEAR && CGAL_collinear_between(
                                                  vertex(2), p, vertex(3))))
        {
          return  CGAL_ON_BOUNDARY;
        }

      return CGAL_ON_UNBOUNDED_SIDE;
    }

  if (ot == CGAL_RIGHTTURN)
    {
      if (o1 == CGAL_RIGHTTURN && o2 == CGAL_RIGHTTURN && o3 == CGAL_RIGHTTURN)
        {
          return CGAL_ON_BOUNDED_SIDE;
        }
      return CGAL_ON_UNBOUNDED_SIDE;
    }

  if (o1 == CGAL_LEFTTURN && o2 == CGAL_LEFTTURN && o3 == CGAL_LEFTTURN)
    {
      return CGAL_ON_BOUNDED_SIDE;
    }
  return CGAL_ON_UNBOUNDED_SIDE;
}


template < class FT >
CGAL_Oriented_side CGAL_TriangleC2<FT>::oriented_side(
                                            const CGAL_PointC2<FT> &p) const
{
  // depends on the orientation of the vertices
  CGAL_Orientation o1 = CGAL_orientation(vertex(0), vertex(1), p),
                   o2 = CGAL_orientation(vertex(1), vertex(2), p),
                   o3 = CGAL_orientation(vertex(2), vertex(3), p),
                   ot = CGAL_orientation(vertex(0), vertex(1), vertex(2));

 if (o1 == CGAL_COLLINEAR || o2 == CGAL_COLLINEAR || o3 == CGAL_COLLINEAR)
    {
      if ((o1 == CGAL_COLLINEAR && CGAL_collinear_between(
                                                  vertex(0), p, vertex(1))) ||
          (o2 == CGAL_COLLINEAR && CGAL_collinear_between(
                                                  vertex(1), p, vertex(2))) ||
          (o3 == CGAL_COLLINEAR && CGAL_collinear_between(
                                                  vertex(2), p, vertex(3))))
        {
          return  CGAL_ON_ORIENTED_BOUNDARY;
        }
      // for ot == CGAL_ON_ORIENTED_BOUNDARY the following also
      // does the right thing:
      return (ot == CGAL_LEFTTURN) ? CGAL_ON_POSITIVE_SIDE
                                   : CGAL_ON_NEGATIVE_SIDE;
    }

  if (ot == CGAL_RIGHTTURN)
    {
      if (o1 == CGAL_RIGHTTURN && o2 == CGAL_RIGHTTURN && o3 == CGAL_RIGHTTURN)
        {
          return CGAL_ON_NEGATIVE_SIDE;
        }
      return CGAL_ON_POSITIVE_SIDE;
    }

  if (o1 == CGAL_LEFTTURN && o2 == CGAL_LEFTTURN && o3 == CGAL_LEFTTURN)
    {
      return CGAL_ON_POSITIVE_SIDE;
    }
  return CGAL_ON_NEGATIVE_SIDE;
}

template < class FT >
bool CGAL_TriangleC2<FT>::has_on_bounded_side(const CGAL_PointC2<FT> &p) const
{
  // depends on the orientation of the vertices
  CGAL_Orientation o1 = CGAL_orientation(vertex(0), vertex(1), p),
                   o2 = CGAL_orientation(vertex(1), vertex(2), p),
                   o3 = CGAL_orientation(vertex(2), vertex(3), p);

 if (o1 == CGAL_COLLINEAR || o2 == CGAL_COLLINEAR || o3 == CGAL_COLLINEAR)
    {
      return false;
    }
  if (CGAL_rightturn(vertex(0), vertex(1), vertex(2)))
    {
      if (o1 == CGAL_RIGHTTURN && o2 == CGAL_RIGHTTURN && o3 == CGAL_RIGHTTURN)
        {
          return true;
        }
      return false;
    }

  if (o1 == CGAL_LEFTTURN && o2 == CGAL_LEFTTURN && o3 == CGAL_LEFTTURN)
    {
      return true;
    }
  return false;
}

template < class FT >
bool CGAL_TriangleC2<FT>::has_on_unbounded_side(const CGAL_PointC2<FT> &p) const
{
  CGAL_Orientation o1 = CGAL_orientation(vertex(0), vertex(1), p),
                   o2 = CGAL_orientation(vertex(1), vertex(2), p),
                   o3 = CGAL_orientation(vertex(2), vertex(3), p);

 if (o1 == CGAL_COLLINEAR || o2 == CGAL_COLLINEAR || o3 == CGAL_COLLINEAR)
    {
      return false;
    }
  if (CGAL_rightturn(vertex(0), vertex(1), vertex(2)))
    {
      if (o1 == CGAL_RIGHTTURN && o2 == CGAL_RIGHTTURN && o3 == CGAL_RIGHTTURN)
        {
          return false;
        }
      return true;
    }

  if (o1 == CGAL_LEFTTURN && o2 == CGAL_LEFTTURN && o3 == CGAL_LEFTTURN)
    {
      return false;
    }
  return true;
}



template < class FT >
inline bool CGAL_TriangleC2<FT>::has_on_boundary(
                                          const CGAL_PointC2<FT> &p) const
{
  return oriented_side(p) == CGAL_ON_BOUNDARY;
}

template < class FT >
inline bool CGAL_TriangleC2<FT>::has_on_negative_side(
                                           const CGAL_PointC2<FT> &p) const
{
  return oriented_side(p) == CGAL_ON_NEGATIVE_SIDE;
}

template < class FT >
inline bool CGAL_TriangleC2<FT>::has_on_positive_side(
                                          const CGAL_PointC2<FT> &p) const
{
  return oriented_side(p) == CGAL_ON_POSITIVE_SIDE;
}

template < class FT >
bool CGAL_TriangleC2<FT>::is_degenerate() const
{

  return CGAL_collinear(vertex(0), vertex(1), vertex(2));
}
template < class FT >
inline CGAL_Bbox_2 CGAL_TriangleC2<FT>::bbox() const
{

  return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
}


template < class FT >
inline CGAL_TriangleC2<FT> CGAL_TriangleC2<FT>::transform(
                                 const CGAL_Aff_transformationC2<FT> &t) const
{
  return CGAL_TriangleC2<FT>(t.transform(vertex(0)),
                            t.transform(vertex(1)),
                            t.transform(vertex(2)));
}



#endif
