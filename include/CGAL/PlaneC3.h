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

// Source: PlaneC3.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_PlaneC3_H
#define CGAL_PlaneC3_H

#include <math.h>
#include <CGAL/Fourtuple.h>

#include <CGAL/solveC3.h>

template < class FT >
  class CGAL_PlaneC3 : public CGAL_Handle
{
public:
                        CGAL_PlaneC3();
                        CGAL_PlaneC3(const CGAL_PlaneC3<FT> &p);
                        CGAL_PlaneC3(const CGAL_PointC3<FT> &p,
                                     const CGAL_PointC3<FT> &q,
                                     const CGAL_PointC3<FT> &r);
                        CGAL_PlaneC3(const CGAL_PointC3<FT> &p,
                                     const CGAL_DirectionC3<FT> &d);
                        CGAL_PlaneC3(const CGAL_PointC3<FT> &p,
                                     const CGAL_VectorC3<FT> &v);
                        CGAL_PlaneC3(const FT &a, const FT &b,
                                     const FT &c, const FT &d);
                        CGAL_PlaneC3(const CGAL_LineC3<FT> &l,
                                     const CGAL_PointC3<FT> &p);
                        CGAL_PlaneC3(const CGAL_SegmentC3<FT> &s,
                                     const CGAL_PointC3<FT> &p);
                        CGAL_PlaneC3(CGAL_RayC3<FT> &r,
                                     const CGAL_PointC3<FT> &p);
                        ~CGAL_PlaneC3();
  CGAL_PlaneC3<FT>       &operator=(const CGAL_PlaneC3<FT> &p);

  bool                  operator==(const CGAL_PlaneC3<FT> &p) const;
  bool                  operator!=(const CGAL_PlaneC3<FT> &p) const;
  int                   id() const;

  FT                    a() const;
  FT                    b() const;
  FT                    c() const;
  FT                    d() const;

  CGAL_LineC3<FT>       perpendicular_line(const CGAL_PointC3<FT> &p) const;
  CGAL_PlaneC3          opposite() const;

  CGAL_PointC3<FT>      point() const;
  CGAL_VectorC3<FT>     orthogonal_vector() const;
  CGAL_DirectionC3<FT>  orthogonal_direction() const;
  CGAL_VectorC3<FT>     base1() const;
  CGAL_VectorC3<FT>     base2() const;

  CGAL_PointC3<FT>      to_plane_basis(const CGAL_PointC3<FT> &p) const;
  CGAL_PointC2<FT>      to_2d(const CGAL_PointC3<FT> &p) const;
  CGAL_PointC3<FT>      to_3d(const CGAL_PointC2<FT> &p) const;

  CGAL_PlaneC3           transform(
                              const CGAL_Aff_transformationC3<FT> &t) const;


  CGAL_Oriented_side    oriented_side(const CGAL_PointC3<FT> &p) const;
  bool                  has_on_boundary(const CGAL_PointC3<FT> &p) const;
  bool                  has_on_boundary(const CGAL_LineC3<FT> &p) const;
  bool                  has_on_positive_side(const CGAL_PointC3<FT> &l) const;
  bool                  has_on_negative_side(const CGAL_PointC3<FT> &l) const;

  bool                  is_degenerate() const;

private:
  CGAL__Fourtuple<FT>*   ptr() const;
  void                new_rep(const CGAL_PointC3<FT> &p,
                              const CGAL_PointC3<FT> &q,
                              const CGAL_PointC3<FT> &r);
  void                new_rep(const FT &a, const FT &b,
                              const FT &c, const FT &d);
};


template < class FT >
inline CGAL__Fourtuple<FT>* CGAL_PlaneC3<FT>::ptr() const
{
    return (CGAL__Fourtuple<FT>*)PTR;
}

template < class FT >
inline void CGAL_PlaneC3<FT>::new_rep(const FT &a, const FT &b,
                                      const FT &c, const FT &d)
{
  PTR = new CGAL__Fourtuple<FT>(a, b, c, d);
  CGAL_nondegeneracy_assertion;
}

template < class FT >
inline void CGAL_PlaneC3<FT>::new_rep(const CGAL_PointC3<FT> &p,
                                      const CGAL_PointC3<FT> &q,
                                      const CGAL_PointC3<FT> &r)
{
  FT px = p.x();
  FT py = p.y();
  FT pz = p.z();

  FT qx = q.x();
  FT qy = q.y();
  FT qz = q.z();

  FT rx = r.x();
  FT ry = r.y();
  FT rz = r.z();

  FT qrz = qz - rz;
  FT prz = pz - rz;
  FT pqz = pz - qz;

  FT A = py* qrz  - qy* prz   + ry* pqz ;

  FT B = - px* qrz  + qx* prz  - rx* pqz ;

  FT C = px*( qy - ry ) - qx*( py - ry ) + rx*( py - qy );

  FT D = - px*( qy*rz - qz*ry ) + qx*( py*rz - pz*ry )
         - rx*( py*qz - pz*qy );


  PTR = new CGAL__Fourtuple<FT>(A, B, C, D);
  CGAL_nondegeneracy_assertion;
}

#include <CGAL/LineC3.h>

template < class FT >
CGAL_PlaneC3<FT>::CGAL_PlaneC3()
{
  PTR = new CGAL__Fourtuple<FT>();
}

template < class FT >
CGAL_PlaneC3<FT>::CGAL_PlaneC3(const CGAL_PlaneC3<FT> &p) :
  CGAL_Handle(p)
{}

template < class FT >
CGAL_PlaneC3<FT>::CGAL_PlaneC3(const CGAL_PointC3<FT> &p,
                               const CGAL_PointC3<FT> &q,
                               const CGAL_PointC3<FT> &r)
{
  new_rep(p, q, r);
}

template < class FT >
CGAL_PlaneC3<FT>::CGAL_PlaneC3(const CGAL_PointC3<FT> &p,
                               const CGAL_DirectionC3<FT> &d)
{
  new_rep(d.dx(), d.dy(),
          d.dz(),
          -d.dx() * p.x() - d.dy() * p.y() - d.dz() * p.z());
}

template < class FT >
CGAL_PlaneC3<FT>::CGAL_PlaneC3(const CGAL_PointC3<FT> &p,
                               const CGAL_VectorC3<FT> &v)
{
  new_rep(v.x(), v.y(), v.z(), -v.x() * p.x() - v.y() * p.y() - v.z() * p.z());
}

template < class FT >
CGAL_PlaneC3<FT>::CGAL_PlaneC3(const FT &a, const FT &b,
                              const FT &c, const FT &d)
{
  new_rep(a, b, c, d);
}

template < class FT >
CGAL_PlaneC3<FT>::CGAL_PlaneC3(const CGAL_LineC3<FT> &l,
                               const CGAL_PointC3<FT> &p)
{
  new_rep(l.point(), l.point()+l.direction().vector(), p);
}

template < class FT >
CGAL_PlaneC3<FT>::CGAL_PlaneC3(const CGAL_SegmentC3<FT> &s,
                               const CGAL_PointC3<FT> &p)
{
  new_rep(s.start(), s.end(), p);
}

template < class FT >
CGAL_PlaneC3<FT>::CGAL_PlaneC3(CGAL_RayC3<FT> &r, const CGAL_PointC3<FT> &p)
{
  new_rep(r.start(), r.second_point(), p);
}

template < class FT >
CGAL_PlaneC3<FT>::~CGAL_PlaneC3()
{}

template < class FT >
CGAL_PlaneC3<FT> &CGAL_PlaneC3<FT>::operator=(const CGAL_PlaneC3<FT> &p)
{

  CGAL_Handle::operator=(p);
  return *this;
}

template < class FT >
bool CGAL_PlaneC3<FT>::operator==(const CGAL_PlaneC3<FT> &p) const
{
  return ( has_on_boundary(p.point()) && orthogonal_direction()
           == p.orthogonal_direction() );

}

template < class FT >
bool CGAL_PlaneC3<FT>::operator!=(const CGAL_PlaneC3<FT> &p) const
{
  return !(*this == p);
}

template < class FT >
int CGAL_PlaneC3<FT>::id() const
{
  return (int) PTR ;
}
template < class FT >
FT CGAL_PlaneC3<FT>::a() const
{

  return ptr()->e0;
}

template < class FT >
FT CGAL_PlaneC3<FT>::b() const
{

  return ptr()->e1;
}

template < class FT >
FT CGAL_PlaneC3<FT>::c() const
{

  return ptr()->e2;
}

template < class FT >
FT CGAL_PlaneC3<FT>::d() const
{

  return ptr()->e3;
}
template < class FT >
CGAL_PointC3<FT>  CGAL_PlaneC3<FT>::point() const
{
  if( a() == FT(0) )
    {
      if( b() == FT(0) )
        { // parallel to xy-plane => intersects z-axis
          return CGAL_PointC3<FT>(FT(0), FT(0), -d()/c());
        }
      // not parallel to y-axis
      return CGAL_PointC3<FT>(FT(0), -d()/b(), FT(0));
    }
  // not parallel to x-axis
  return CGAL_PointC3<FT>(-d()/a(), FT(0), FT(0));
}


template < class FT >
CGAL_VectorC3<FT> CGAL_PlaneC3<FT>::orthogonal_vector() const
{
  return CGAL_VectorC3<FT>(a(), b(), c());
}


template < class FT >
CGAL_DirectionC3<FT> CGAL_PlaneC3<FT>::orthogonal_direction() const
{
  return CGAL_DirectionC3<FT>(a(), b(), c());
}

template < class FT >
CGAL_VectorC3<FT> CGAL_PlaneC3<FT>::base1() const
{
  if( a() == FT(0) )  // parallel to x-axis
    {
      return CGAL_VectorC3<FT>(FT(1), FT(0), FT(0));
    }
  if( b() == FT(0) )  // parallel to y-axis
    {
      return CGAL_VectorC3<FT>(FT(0), FT(1), FT(0));
    }
  if (c() == FT(0) )  // parallel to z-axis
    {
      return CGAL_VectorC3<FT>(FT(0), FT(0), FT(1));
    }
  return CGAL_VectorC3<FT>(-b(), a(), FT(0));
}


template < class FT >
CGAL_VectorC3<FT> CGAL_PlaneC3<FT>::base2() const
{
  if ( a() == FT(0) ) // parallel to x-axis  x-axis already returned in base1
    {
      if (b() == FT(0) )  // parallel to y-axis
        {
          return CGAL_VectorC3<FT>(FT(0), FT(1), FT(0));
        }
      if (c() == FT(0) ) // parallel to z-axis
        {
          return CGAL_VectorC3<FT>(FT(0), FT(0), FT(1));
        }
      return CGAL_VectorC3<FT>(FT(0), -b(), c());
    }
  if (b() == FT(0) )
    {
      return CGAL_VectorC3<FT>(c(), FT(0), -a());
    }
  if (c() == FT(0) )
    {
      return CGAL_VectorC3<FT>(-b(), a(), FT(0));
    }
  return CGAL_VectorC3<FT>(FT(0), -c(), b());
}
template < class FT >
CGAL_PointC3<FT> CGAL_PlaneC3<FT>::to_plane_basis(
                                             const CGAL_PointC3<FT> &p) const
{
  const CGAL_VectorC3<FT> &e1 = base1();
  const CGAL_VectorC3<FT> &e2 = base2();
  FT alpha, beta, gamma;

  CGAL_solve(e1/sqrt(CGAL_to_double(e1*e1)), e2/sqrt(CGAL_to_double(e2*e2)),
             orthogonal_vector()/sqrt(CGAL_to_double(orthogonal_vector()
                                                * orthogonal_vector())),
             p - point(), alpha, beta, gamma);

  return CGAL_PointC3<FT>(alpha, beta, gamma);
}

template < class FT >
CGAL_PointC2<FT> CGAL_PlaneC3<FT>::to_2d(const CGAL_PointC3<FT> &p) const
{
  CGAL_PointC3<FT> q(to_plane_basis(p));
  return CGAL_PointC2<FT>(q.x(), q.y());
}

template < class FT >
CGAL_PointC3<FT> CGAL_PlaneC3<FT>::to_3d(const CGAL_PointC2<FT> &p) const
{
  CGAL_VectorC3<FT> e1 = base1(),
                    e2 = base2();
  return point() + p.x() * e1/sqrt(CGAL_to_double(e1*e1))
                 + p.y() * e2/sqrt(CGAL_to_double(e2*e2));
}

template < class FT >
CGAL_LineC3<FT> CGAL_PlaneC3<FT>::perpendicular_line(
                                               const CGAL_PointC3<FT> &p) const
{
  return CGAL_LineC3<FT>(p, orthogonal_direction());
}


template < class FT >
CGAL_PlaneC3<FT> CGAL_PlaneC3<FT>::opposite() const
{
  return CGAL_PlaneC3<FT>(-a(),-b(),-c(),-d());
}


template < class FT >
CGAL_PlaneC3<FT> CGAL_PlaneC3<FT>::transform(
                                const CGAL_Aff_transformationC3<FT>& t) const
{
 if ( t.is_even() )
 {
     return CGAL_PlaneC3<FT>(
             t.transform(point() ),
             t.transpose().inverse().transform(orthogonal_direction() ));
 }
 else
 {
     return CGAL_PlaneC3<FT>(
             t.transform(point() ),
           - t.transpose().inverse().transform(orthogonal_direction() ));
 }
}


template < class FT >
CGAL_Oriented_side CGAL_PlaneC3<FT>::oriented_side(
                                            const CGAL_PointC3<FT> &p) const
{
  FT n = a()*p.x() + b()*p.y() + c()*p.z() +d();

  return (n == FT(0)) ? CGAL_ON_ORIENTED_BOUNDARY
                      : ( (n > FT(0)) ? CGAL_ON_POSITIVE_SIDE
                          : CGAL_ON_NEGATIVE_SIDE);
}

template < class FT >
bool CGAL_PlaneC3<FT>::has_on_boundary(const  CGAL_PointC3<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()*p.z() +d()) == FT(0);
}

template < class FT >
bool CGAL_PlaneC3<FT>::has_on_boundary(const  CGAL_LineC3<FT> &l) const
{
  return has_on_boundary(l.point())
         &&  has_on_boundary(l.point() + l.direction().vector());
}

template < class FT >
bool CGAL_PlaneC3<FT>::has_on_positive_side(const  CGAL_PointC3<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()*p.z() +d()) > FT(0);
}

template < class FT >
bool CGAL_PlaneC3<FT>::has_on_negative_side(const  CGAL_PointC3<FT> &p) const
{
  return (a()*p.x() + b()*p.y() + c()*p.z() +d()) < FT(0);
}


template < class FT >
bool CGAL_PlaneC3<FT>::is_degenerate() const
{
  return (a() == FT(0)) && (b() == FT(0)) && (c() == FT(0));
}


#endif  // CGAL_PlaneC3_H
