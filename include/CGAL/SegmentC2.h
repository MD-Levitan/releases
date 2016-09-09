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

// Source: SegmentC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_SEGMENTC2_H
#define CGAL_SEGMENTC2_H

#include <CGAL/LineC2.h>

template < class FT >
class CGAL_SegmentC2 : public CGAL_Handle
{
public:
                       CGAL_SegmentC2();
                       CGAL_SegmentC2(const CGAL_SegmentC2<FT>  &s);
                       CGAL_SegmentC2(const CGAL_PointC2<FT> &sp,
                                      const CGAL_PointC2<FT> &ep);

                       ~CGAL_SegmentC2();

  CGAL_SegmentC2<FT>   &operator=(const CGAL_SegmentC2<FT> &s);

  bool                 is_horizontal() const;
  bool                 is_vertical() const;
  bool                 has_on(const CGAL_PointC2<FT> &p) const;
  bool                 collinear_has_on(const CGAL_PointC2<FT> &p) const;

  bool                 operator==(const CGAL_SegmentC2<FT> &s) const;
  bool                 operator!=(const CGAL_SegmentC2<FT> &s) const;
  int                  id() const;

  CGAL_PointC2<FT>     start() const;
  CGAL_PointC2<FT>     end() const;

  CGAL_PointC2<FT>     source() const;
  CGAL_PointC2<FT>     target() const;

  CGAL_PointC2<FT>     min() const;
  CGAL_PointC2<FT>     max() const;
  CGAL_PointC2<FT>     vertex(int i) const;
  CGAL_PointC2<FT>     point(int i) const;
  CGAL_PointC2<FT>     operator[](int i) const;

  FT                   squared_length() const;

  CGAL_DirectionC2<FT> direction() const;
  CGAL_LineC2<FT>      supporting_line() const;
  CGAL_SegmentC2<FT>   opposite() const;
  CGAL_SegmentC2<FT>   transform(const CGAL_Aff_transformationC2<FT> &t) const;

  bool                 is_degenerate() const;
  CGAL_Bbox_2          bbox() const;

private:
  CGAL__Twotuple< CGAL_PointC2<FT> >*   ptr() const
  {
  return (CGAL__Twotuple< CGAL_PointC2<FT> >*)PTR;
  }
};


template < class FT >
CGAL_SegmentC2<FT>::CGAL_SegmentC2()
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >;
}

template < class FT >
CGAL_SegmentC2<FT>::CGAL_SegmentC2(const CGAL_SegmentC2<FT>  &s) :
  CGAL_Handle((CGAL_Handle&)s)
{}

template < class FT >
CGAL_SegmentC2<FT>::CGAL_SegmentC2(const CGAL_PointC2<FT> &sp,
                                 const CGAL_PointC2<FT> &ep)
{
  PTR = new CGAL__Twotuple< CGAL_PointC2<FT> >(sp, ep);

  CGAL_nondegeneracy_assertion;
}

template < class FT >
CGAL_SegmentC2<FT>::~CGAL_SegmentC2()
{}

#ifdef  CGAL_TO_DOUBLE
template < class FT >
CGAL_SegmentC2<FT>::operator CGAL_SegmentC2<double>() const
{
  return CGAL_SegmentC2<double>(source(), target());
}
#endif // CGAL_TO_DOUBLE

template < class FT >
CGAL_SegmentC2<FT> &CGAL_SegmentC2<FT>::operator=(const CGAL_SegmentC2<FT> &s)
{
  CGAL_Handle::operator=(s);
  return *this;
}
template < class FT >
bool  CGAL_SegmentC2<FT>::operator==(const CGAL_SegmentC2<FT> &s) const
{
  return ( (source() == s.source())  && (target() == s.target()) );
}

template < class FT >
bool  CGAL_SegmentC2<FT>::operator!=(const CGAL_SegmentC2<FT> &s) const
{
  return !(*this == s);
}

template < class FT >
int CGAL_SegmentC2<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::start() const
{
  return ptr()->e0;
}

template < class FT >
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::end() const
{
  return ptr()->e1;
}


template < class FT >
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::source() const
{
  return ptr()->e0;
}

template < class FT >
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::target() const
{
  return ptr()->e1;
}


template < class FT >
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::min() const
{


  return (CGAL_lexicographically_xy_smaller(source(),target())) ? source()
                                                                : target();
}

template < class FT >
CGAL_PointC2<FT>  CGAL_SegmentC2<FT>::max() const
{


  return (CGAL_lexicographically_xy_smaller(source(),target())) ? target()
                                                                : source();
}

template < class FT >
CGAL_PointC2<FT> CGAL_SegmentC2<FT>::vertex(int i) const
{

  if(i%2 == 0) {
  return source();
  }
  return target();
}

template < class FT >
CGAL_PointC2<FT> CGAL_SegmentC2<FT>::point(int i) const
{

  if(i%2 == 0) {
  return source();
  }
  return target();
}

template < class FT >
CGAL_PointC2<FT> CGAL_SegmentC2<FT>::operator[](int i) const
{

  return vertex(i);
}
template < class FT >
FT CGAL_SegmentC2<FT>::squared_length() const
{

  return  ( (target() - source()) * (target() - source()));
}

template < class FT >
CGAL_DirectionC2<FT> CGAL_SegmentC2<FT>::direction() const
{

  return CGAL_DirectionC2<FT>( target() - source() );
}

template < class FT >
CGAL_LineC2<FT> CGAL_SegmentC2<FT>::supporting_line() const
{

  return CGAL_LineC2<FT>(*this);
}

template < class FT >
CGAL_SegmentC2<FT> CGAL_SegmentC2<FT>::opposite() const
{

  return CGAL_SegmentC2<FT>(target(), source());
}

template < class FT >
CGAL_SegmentC2<FT> CGAL_SegmentC2<FT>::transform(
                               const CGAL_Aff_transformationC2<FT> &t) const
{
  return CGAL_SegmentC2<FT>(t.transform(source()),
                           t.transform(target()));
}

template < class FT >
CGAL_Bbox_2 CGAL_SegmentC2<FT>::bbox() const
{

  return source().bbox() + target().bbox();
}

template < class FT >
bool  CGAL_SegmentC2<FT>::is_degenerate() const
{

  return (source() == target());
}

template < class FT >
bool CGAL_SegmentC2<FT>::is_horizontal() const
{

  return (source().y() == target().y());
}

template < class FT >
bool CGAL_SegmentC2<FT>::is_vertical() const
{

  return (source().x() == target().x());
}

template < class FT >
bool CGAL_SegmentC2<FT>::has_on(const CGAL_PointC2<FT> &p) const
{
  return(( p == source() )
         || ( p == target() )
         || ( CGAL_collinear(source(), p, target())
              &&( CGAL_DirectionC2<FT>(p - source())
                  !=
                  CGAL_DirectionC2<FT> (p - target()))
             )
         );
}


template < class FT >
bool CGAL_SegmentC2<FT>::collinear_has_on(const CGAL_PointC2<FT> &p)
const
{
    CGAL_exactness_precondition( CGAL_collinear(source(), p, target()) );
    if (CGAL_abs(target().x()-source().x())
        > CGAL_abs(target().y()-source().y())) {
        if (p.x() < source().x())
            return (p.x() >= target().x());
        if (p.x() <= target().x())
            return true;
        return (p.x() == source().x());
    } else {
        if (p.y() < source().y())
            return (p.y() >= target().y());
        if (p.y() <= target().y())
            return true;
        return (p.y() == source().y());
    }
}


#endif
