// Source: Line_2pC2.h
// Author: Andreas.Fabri@sophia.inria.fr


#ifndef CGAL_Line_2pC2_H
#define CGAL_Line_2pC2_H

#include <CGAL/predicates_on_points_2.h>

template < class FT >
class CGAL_Line_2pC2 : public CGAL_Handle
{
public:
                       CGAL_Line_2pC2();
                       CGAL_Line_2pC2(const CGAL_Line_2pC2<FT>  &l);
                       CGAL_Line_2pC2(const CGAL_PointC2<FT> &p,
                                      const CGAL_PointC2<FT> &q);
                       CGAL_Line_2pC2(const FT &a, const FT &b, const FT &c);
                       CGAL_Line_2pC2(const CGAL_SegmentC2<FT> &s);
                       CGAL_Line_2pC2(const CGAL_RayC2<FT> &r);
                       CGAL_Line_2pC2(const CGAL_PointC2<FT> &p,
                                      const CGAL_DirectionC2<FT> &d);
                       ~CGAL_Line_2pC2();


  CGAL_Line_2pC2<FT>   &operator=(const CGAL_Line_2pC2<FT> &l);

  bool                 operator==(const CGAL_Line_2pC2<FT> &l) const;
  bool                 operator!=(const CGAL_Line_2pC2<FT> &l) const;
  int                  id() const;

  FT                   a() const;
  FT                   b() const;
  FT                   c() const;

  FT                   x_at_y(const FT &y) const;
  FT                   y_at_x(const FT &x) const;

  CGAL_Line_2pC2<FT>   perpendicular(const CGAL_PointC2<FT> &p) const;
  CGAL_Line_2pC2<FT>   opposite() const;
  CGAL_PointC2<FT>     point(int i) const;

  CGAL_PointC2<FT>     point() const;

  CGAL_PointC2<FT>     projection(const CGAL_PointC2<FT> &p) const;

  CGAL_DirectionC2<FT> direction() const;

  CGAL_Oriented_side   oriented_side(const CGAL_PointC2<FT> &p) const;
  bool                 has_on_boundary(const CGAL_PointC2<FT> &p) const;
  bool                 has_on_positive_side(const CGAL_PointC2<FT> &p) const;
  bool                 has_on_negative_side(const CGAL_PointC2<FT> &p) const;

  bool                 is_horizontal() const;
  bool                 is_vertical() const;
  bool                 is_degenerate() const;
  CGAL_Line_2pC2<FT>   transform(const CGAL_Aff_transformationC2<FT> &t) const;

private:
  CGAL_PointC2<FT>     first_point() const;
  CGAL_PointC2<FT>     second_point() const;
  CGAL__Twotuple_rep< CGAL_PointC2<FT> >* ptr() const;
};


template < class FT >
inline CGAL_Line_2pC2<FT>::CGAL_Line_2pC2()
{
  PTR = new CGAL__Twotuple_rep< CGAL_PointC2<FT> >();
}

template < class FT >
inline CGAL_Line_2pC2<FT>::CGAL_Line_2pC2(const CGAL_Line_2pC2<FT>  &l) :
  CGAL_Handle((CGAL_Handle&)l)
{}

template < class FT >
inline CGAL_Line_2pC2<FT>::CGAL_Line_2pC2(const CGAL_RayC2<FT> &r) :
  CGAL_Handle((CGAL_Handle&)r)
{}

template < class FT >
inline CGAL_Line_2pC2<FT>::CGAL_Line_2pC2(const CGAL_SegmentC2<FT> &s) :
  CGAL_Handle((CGAL_Handle&)s)
{}

template < class FT >
inline CGAL_Line_2pC2<FT>::CGAL_Line_2pC2(const CGAL_PointC2<FT> &p,
                                    const CGAL_PointC2<FT> &q)
{
  PTR = new CGAL__Twotuple_rep< CGAL_PointC2<FT> >(p, q);
  CGAL_nondegeneracy_assertion();
}

template < class FT >
inline CGAL_Line_2pC2<FT>::CGAL_Line_2pC2(const CGAL_PointC2<FT> &p,
                                  const CGAL_DirectionC2<FT> &d)
{
  CGAL_PointC2<FT> q = p + d.vector();
  PTR = new CGAL__Twotuple_rep< CGAL_PointC2<FT> >(p, q);
  CGAL_nondegeneracy_assertion();
}

template < class FT >
inline CGAL_Line_2pC2<FT>::CGAL_Line_2pC2(const FT &a,
                                          const FT &b,
                                          const FT &c)
{
  CGAL_PointC2<FT> p;
  if (b==FT(0))
    {
      p = CGAL_PointC2<FT>( (b-c)/a, FT(1) );
    }
  else
    {
      p = CGAL_PointC2<FT>( FT(1), -(a+c)/b );
    }

  PTR = new CGAL__Twotuple_rep< CGAL_PointC2<FT> >(
                                             p, p + CGAL_CVector<FT>(b, -a));
  CGAL_nondegeneracy_assertion();
}

template < class FT >
inline CGAL_Line_2pC2<FT>::~CGAL_Line_2pC2()
{}


template < class FT >
CGAL_Line_2pC2<FT> &CGAL_Line_2pC2<FT>::operator=(const CGAL_Line_2pC2<FT> &l)
{
  CGAL_Handle::operator=(l);
  return *this;
}
template < class FT >
bool CGAL_Line_2pC2<FT>::operator==(const CGAL_Line_2pC2<FT> &l) const
{
  return ( is_on(l.first_point()) && (direction() == l.direction()) );
}

template < class FT >
inline bool CGAL_Line_2pC2<FT>::operator!=(const CGAL_Line_2pC2<FT> &l) const
{
  return !(*this == l);
}

template < class FT >
inline int CGAL_Line_2pC2<FT>::id const
{
  return (int) PTR ;
}
template < class FT >
inline FT CGAL_Line_2pC2<FT>::a() const
{
  return first_point().y() - second_point().y();
}

template < class FT >
inline FT CGAL_Line_2pC2<FT>::b() const
{
  return second_point().x() - first_point().x();
}

template < class FT >
inline FT CGAL_Line_2pC2<FT>::c() const
{
  return first_point().x()*second_point().y()
         - first_point().y()*second_point().x();
}

template < class FT >
inline FT CGAL_Line_2pC2<FT>::x_at_y(const FT &y) const
{
  CGAL_kernel_precondition( a() != FT(0) );
  return ( -b() * y - c() ) / a();
}

template < class FT >
inline FT CGAL_Line_2pC2<FT>::y_at_x(const FT &x) const
{
  CGAL_kernel_precondition( b() != FT(0) );
  return ( -a() * x - c() ) / b();
}

template < class FT >
inline CGAL_Line_2pC2<FT> CGAL_Line_2pC2<FT>::perpendicular(
                                              const CGAL_PointC2<FT> &p) const
{
  return CGAL_Line_2pC2<FT>(p, projection(p));
}

template < class FT >
inline CGAL_Line_2pC2<FT> CGAL_Line_2pC2<FT>::opposite() const
{
  return CGAL_Line_2pC2<FT>(second_point(), first_point());
}

template < class FT >
inline CGAL_PointC2<FT> CGAL_Line_2pC2<FT>::point() const
{
  return first_point();
}

template < class FT >
CGAL_PointC2<FT> CGAL_Line_2pC2<FT>::point(int i) const
{
  return first_point() + FT(i) * (second_point() - first_point()) ;
}

template < class FT >
inline CGAL_PointC2<FT> CGAL_Line_2pC2<FT>::projection(
                                             const CGAL_PointC2<FT> &p) const
{
  CGAL_CVector<FT> w = second_point() - first_point();
  return first_point() - (((first_point() - p) * w) / (w * w)) * w;
}

template < class FT >
inline CGAL_DirectionC2<FT> CGAL_Line_2pC2<FT>::direction() const
{
  return CGAL_DirectionC2<FT>( b(), -a() );
}

template < class FT >
CGAL_Oriented_side CGAL_Line_2pC2<FT>::oriented_side(
                                           const CGAL_PointC2<FT> &p) const
{
  return CGAL_orientation(first_point(), second_point(), p);
}

template < class FT >
bool CGAL_Line_2pC2<FT>::has_on_boundary(const CGAL_PointC2<FT> &p) const
{
  return CGAL_collinear(first_point(), second_point(), p);
}

template < class FT >
bool CGAL_Line_2pC2<FT>::has_on_positive_side(const CGAL_PointC2<FT> &p) const
{
  return CGAL_leftturn(first_point(), second_point(), p);
}


template < class FT >
bool CGAL_Line_2pC2<FT>::has_on_negative_side(const CGAL_PointC2<FT> &p) const
{
  return CGAL_rightturn(first_point(), second_point(), p);
}


template < class FT >
bool CGAL_Line_2pC2<FT>::is_horizontal() const
{
  return a() == FT(0);
}

template < class FT >
bool CGAL_Line_2pC2<FT>::is_vertical() const
{
  return  b() == FT(0);
}

template < class FT >
bool CGAL_Line_2pC2<FT>::is_degenerate() const
{
  return first_point() == second_point();
}

template < class FT >
inline CGAL_Line_2pC2<FT> CGAL_Line_2pC2<FT>::transform(
                                  const CGAL_Aff_transformationC2<FT> &t) const
{
  return CGAL_Line_2pC2<FT>(t.transform(first_point()),
                            t.transform(second_point()));
}

template < class FT >
inline CGAL__Twotuple_rep< CGAL_PointC2<FT> >* CGAL_Line_2pC2<FT>::ptr() const
{
  return (CGAL__Twotuple_rep< CGAL_PointC2<FT> >*)PTR;
}

template < class FT >
inline CGAL_PointC2<FT> CGAL_Line_2pC2<FT>::first_point() const
{
  return ptr()->e0;
}

template < class FT >
inline CGAL_PointC2<FT> CGAL_Line_2pC2<FT>::second_point() const
{
  return ptr()->e1;
}


#endif
