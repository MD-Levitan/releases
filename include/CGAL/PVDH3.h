
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

// Source: PVDH3.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_PVDH3_H
#define CGAL_PVDH3_H
#define CGAL_POINTH3_H
#define CGAL_VECTORH3_H
#define CGAL_DIRECTIONH3_H

#include <CGAL/homogeneous_classes.h>
#include <CGAL/Origin.h>

#include <CGAL/RepH3.h>




template < class FT, class RT >
class CGAL_PointH3 : public CGAL_Handle
{

public:

          CGAL_PointH3();
          CGAL_PointH3(const CGAL_PointH3<FT,RT> & tbc);
          CGAL_PointH3(const CGAL_Origin &);
          CGAL_PointH3(const CGAL_VectorH3<FT,RT>& v);
          CGAL_PointH3(const RT& x, const RT& y, const RT& z);
          CGAL_PointH3(const RT& x, const RT& y, const RT& z, const RT& w);
          ~CGAL_PointH3();

    CGAL_PointH3<FT,RT> &
          operator=( const CGAL_PointH3<FT,RT> & p);

    FT    x()  const;
    FT    y()  const;
    FT    z()  const;
    RT    hx() const;
    RT    hy() const;
    RT    hz() const;
    RT    hw() const;
    FT    cartesian(int i) const;
    RT    homogeneous(int i) const;
    FT    operator[](int i) const;

    int   dimension() const;

    CGAL_DirectionH3<FT,RT>
          direction() const;
    CGAL_PointH3<FT,RT>
          transform( const CGAL_Aff_transformationH3<FT,RT> & t) const;
    CGAL_Bbox_3
          bbox() const;

    bool  operator==( const CGAL_PointH3<FT,RT>& p) const;
    bool  operator!=( const CGAL_PointH3<FT,RT>& p) const;
    bool  identical(  const CGAL_PointH3<FT,RT>& p) const;

 friend CGAL_PointH3<FT,RT> operator+(const CGAL_Origin &,
                                      const CGAL_VectorH3<FT,RT> & v);
 friend CGAL_PointH3<FT,RT> operator-(const CGAL_Origin &,
                                      const CGAL_VectorH3<FT,RT> & v);

protected:

    CGAL__RepH3<RT>*         ptr() const;

};

template < class FT, class RT >
class CGAL_VectorH3 : public CGAL_Handle
{
public:
          CGAL_VectorH3();
          CGAL_VectorH3(const CGAL_VectorH3<FT,RT> & tbc);
          CGAL_VectorH3(const CGAL_Null_vector&);
          CGAL_VectorH3(const RT& x, const RT& y, const RT& z);
          CGAL_VectorH3(const RT& w, const RT& x, const RT& y, const RT& z);
          ~CGAL_VectorH3();

    CGAL_VectorH3<FT,RT>&
          operator=( const CGAL_VectorH3<FT,RT>& v);

    FT    x()  const;
    FT    y()  const;
    FT    z()  const;
    RT    hx() const;
    RT    hy() const;
    RT    hz() const;
    RT    hw() const;
    FT    cartesian(int i) const;
    RT    homogeneous(int i) const;
    FT    operator[](int i) const;

    int   dimension() const;

    CGAL_DirectionH3<FT,RT>
          direction() const;
    CGAL_VectorH3<FT,RT>
          transform(const CGAL_Aff_transformationH3<FT,RT>& t ) const;

    CGAL_VectorH3<FT,RT>
          operator-() const;

    bool  operator==( const CGAL_VectorH3<FT,RT>& v) const;
    bool  operator!=( const CGAL_VectorH3<FT,RT>& v) const;
    bool  identical ( const CGAL_VectorH3<FT,RT>& v) const;

// undocumented:

          CGAL_VectorH3(const CGAL_PointH3<FT,RT> & p);
          CGAL_VectorH3(const CGAL_DirectionH3<FT,RT> & dir);

// friends:

friend CGAL_VectorH3<FT,RT> operator-( const CGAL_PointH3<FT,RT> &,
                                       const CGAL_Origin & );
friend CGAL_VectorH3<FT,RT> operator-( const CGAL_Origin &,
                                       const CGAL_PointH3<FT,RT> & );
friend CGAL_PointH3<FT,RT>  operator+( const CGAL_Origin &,
                                       const CGAL_VectorH3<FT,RT> & );
friend CGAL_PointH3<FT,RT>  operator-( const CGAL_Origin &,
                                       const CGAL_VectorH3<FT,RT> & );
friend CGAL_VectorH3<FT,RT> operator+( const CGAL_VectorH3<FT,RT> &,
                                       const CGAL_VectorH3<FT,RT> & );
friend CGAL_VectorH3<FT,RT> operator-( const CGAL_VectorH3<FT,RT> &,
                                       const CGAL_VectorH3<FT,RT> & );
friend FT                   operator*( const CGAL_VectorH3<FT,RT> &,
                                       const CGAL_VectorH3<FT,RT> & );
friend CGAL_VectorH3<FT,RT> operator*( const CGAL_VectorH3<FT,RT> &,
                                       const RT & );
friend CGAL_VectorH3<FT,RT> operator*( const RT &,
                                       const CGAL_VectorH3<FT,RT> & );
friend CGAL_VectorH3<FT,RT> operator/( const CGAL_VectorH3<FT,RT> &,
                                       const RT & );
friend CGAL_VectorH3<FT,RT> CGAL_cross_product(const CGAL_VectorH3<FT,RT>& a,
                                               const CGAL_VectorH3<FT,RT>& b);

protected:

    CGAL__RepH3<RT>*    ptr() const;

};




template < class FT, class RT >
class CGAL_DirectionH3 : public CGAL_Handle
{

public:
                 CGAL_DirectionH3();
                 CGAL_DirectionH3(const CGAL_DirectionH3 & tbc );
                 CGAL_DirectionH3(const CGAL_PointH3<FT,RT> & p );
                 CGAL_DirectionH3(const CGAL_VectorH3<FT,RT> & v );
                 CGAL_DirectionH3(const RT& x, const RT& y,
                                  const RT& z, const RT& w = RT(1) );

                 ~CGAL_DirectionH3();

    CGAL_DirectionH3 &
                 operator=(const CGAL_DirectionH3 & d);

    CGAL_DirectionH3
          transform(const CGAL_Aff_transformationH3<FT,RT> &) const ;
    CGAL_DirectionH3
          operator-() const;

    bool  is_degenerate() const;

    bool  operator==( const CGAL_DirectionH3& d) const;
    bool  operator!=( const CGAL_DirectionH3& d) const;
    bool  identical ( const CGAL_DirectionH3& d) const;

    CGAL_VectorH3<FT,RT>    vector() const;

    RT    dx() const;
    RT    dy() const;
    RT    dz() const;
    RT    x()  const;
    RT    y()  const;
    RT    z()  const;
    RT    hx() const;
    RT    hy() const;
    RT    hz() const;

    RT    delta(int i) const;

 friend CGAL_DirectionH3<FT,RT>
          CGAL_cross_product( const CGAL_DirectionH3<FT,RT>& d1,
                              const CGAL_DirectionH3<FT,RT>& d2);

protected:

    CGAL__RepH3<RT>*    ptr()    const;
};


template < class FT, class RT >
CGAL__RepH3<RT>*
CGAL_PointH3<FT,RT>::ptr() const
{
 return (CGAL__RepH3<RT>*)PTR;
}

template < class FT, class RT >
CGAL__RepH3<RT>*
CGAL_VectorH3<FT,RT>::ptr() const
{
 return (CGAL__RepH3<RT>*)PTR;
}

template <class FT, class RT >
inline
CGAL__RepH3<RT>*
CGAL_DirectionH3<FT,RT>::ptr() const
{
 return (CGAL__RepH3<RT>*)PTR;
}


template < class FT, class RT >
CGAL_PointH3<FT,RT>::CGAL_PointH3()
{
 PTR = new CGAL__RepH3<RT>();
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>::CGAL_PointH3(const CGAL_Origin&)
{
 const RT RT0(0);
 const RT RT1(1);
 PTR = new CGAL__RepH3<RT>( RT0, RT0, RT0, RT1 );
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>::CGAL_PointH3(const CGAL_PointH3<FT,RT>& tbc)
 : CGAL_Handle(tbc)
{
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>::CGAL_PointH3(const CGAL_VectorH3<FT,RT>& v)
 : CGAL_Handle(v)
{
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>::CGAL_PointH3(const RT& x, const RT& y, const RT& z)
{
 PTR = new CGAL__RepH3<RT>(x,y,z, RT(1));
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>::CGAL_PointH3(const RT& x, const RT& y,
                                  const RT& z, const RT& w)
{
 if ( w >= RT(0.0) )
 {
    PTR = new CGAL__RepH3<RT>(x,y,z,w);
 }
 else
 {
    PTR = new CGAL__RepH3<RT>(-x,-y,-z,-w);
 }
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>::~CGAL_PointH3()
{
}

// template < class FT, class RT >
// CGAL_PointH3<FT,RT>::CGAL_PointH3(const CGAL_VectorH3<FT,RT>& v)
//  : CGAL_Handle( (CGAL_Handle&) v)
// {
// }

template < class FT, class RT >
CGAL_PointH3<FT,RT>&
CGAL_PointH3<FT,RT>::operator=(const CGAL_PointH3<FT,RT>& p)
{
 CGAL_Handle::operator=(p);
 return *this;
}

template < class FT, class RT >
FT
CGAL_PointH3<FT,RT>::x()  const
{
 return ( FT(ptr()->hx() ) / FT(ptr()->hw() ));
}


template < class FT, class RT >
FT
CGAL_PointH3<FT,RT>::y()  const
{
 return ( FT(ptr()->hy() ) / FT(ptr()->hw() ));
}

template < class FT, class RT >
FT
CGAL_PointH3<FT,RT>::z()  const
{
 return ( FT(ptr()->hz() ) / FT(ptr()->hw() ));
}

template < class FT, class RT >
RT
CGAL_PointH3<FT,RT>::hx() const
{
 return  ptr()->hx() ;
}

template < class FT, class RT >
RT
CGAL_PointH3<FT,RT>::hy() const
{
 return  ptr()->hy() ;
}

template < class FT, class RT >
RT
CGAL_PointH3<FT,RT>::hz() const
{
 return  ptr()->hz() ;
}

template < class FT, class RT >
RT
CGAL_PointH3<FT,RT>::hw() const
{
 return  ptr()->hw();
}

template < class FT, class RT >
int
CGAL_PointH3<FT,RT>::dimension() const
{
 return 3;
}

template < class FT, class RT >
FT
CGAL_PointH3<FT,RT>::cartesian(int i) const
{
 switch (i)
 {
    case 0:  return x();
    case 1:  return y();
    case 2:  return z();
    default: return cartesian( i%3 );
 }
 return FT( RT() );
}

template < class FT, class RT >
RT
CGAL_PointH3<FT,RT>::homogeneous(int i) const
{
 switch (i)
 {
    case 0:   return hx();
    case 1:   return hy();
    case 2:   return hz();
    case 3:   return hw();
    default:  assert(0);
 }
 return RT();
}

template < class FT, class RT >
FT
CGAL_PointH3<FT,RT>::operator[](int i) const
{
 return cartesian(i);
}
template < class FT, class RT >
CGAL_DirectionH3<FT,RT>
CGAL_PointH3<FT,RT>::direction() const
{
 return CGAL_DirectionH3<FT,RT>(*this);
}
template < class FT, class RT >
bool
CGAL_PointH3<FT,RT>::operator==( const CGAL_PointH3<FT,RT> & p) const
{
 return ( (hx() * p.hw() == p.hx() * hw() )
        &&(hy() * p.hw() == p.hy() * hw() )
        &&(hz() * p.hw() == p.hz() * hw() ) );
}

template < class FT, class RT >
bool
CGAL_PointH3<FT,RT>::operator!=( const CGAL_PointH3<FT,RT> & p) const
{
 return !(*this == p);
}

template < class FT, class RT >
bool
CGAL_PointH3<FT,RT>::identical( const CGAL_PointH3<FT,RT>& p) const
{
 return ::identical(*this,p);
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>::CGAL_VectorH3()
{
 PTR = new CGAL__RepH3<RT>();
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>::CGAL_VectorH3(const CGAL_VectorH3 & tbc)
 : CGAL_Handle((CGAL_Handle&) tbc)
{
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>::CGAL_VectorH3(const CGAL_Null_vector&)
{
 PTR = new CGAL__RepH3<RT>( RT(0), RT(0), RT(0), RT(1) );
}


template < class FT, class RT >
CGAL_VectorH3<FT,RT>::CGAL_VectorH3(const CGAL_PointH3<FT,RT> & p)
 : CGAL_Handle( (CGAL_Handle&) p )
{
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>::CGAL_VectorH3(const CGAL_DirectionH3<FT,RT> & d)
 : CGAL_Handle( (CGAL_Handle&) d )
{
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>::CGAL_VectorH3(const RT& x, const RT& y,
                                    const RT& z, const RT& w)
{
 if ( w >= RT(0) )
 {
    PTR = new CGAL__RepH3<RT>(x, y, z, w);
 }
 else
 {
    PTR = new CGAL__RepH3<RT>(-x,-y,-z,-w);
 }
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>::CGAL_VectorH3(const RT& x, const RT& y, const RT& z)
{
 PTR = new CGAL__RepH3<RT>(x, y, z, RT(1) );
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>::~CGAL_VectorH3()
{
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT> &
CGAL_VectorH3<FT,RT>::operator=(const CGAL_VectorH3 & v)
{
 CGAL_Handle::operator=(v);
 return *this;
}
template < class FT, class RT >
FT
CGAL_VectorH3<FT,RT>::x()  const
{
 return FT(ptr()->hx() )/FT(ptr()->hw() ) ;
}

template < class FT, class RT >
FT
CGAL_VectorH3<FT,RT>::y()  const
{
 return FT(ptr()->hy() )/FT(ptr()->hw() ) ;
}

template < class FT, class RT >
FT
CGAL_VectorH3<FT,RT>::z()  const
{
 return FT(ptr()->hz() )/FT(ptr()->hw() ) ;
}

template < class FT, class RT >
RT
CGAL_VectorH3<FT,RT>::hx() const
{
 return  ptr()->hx() ;
}

template < class FT, class RT >
RT
CGAL_VectorH3<FT,RT>::hy() const
{
 return  ptr()->hy() ;
}

template < class FT, class RT >
RT
CGAL_VectorH3<FT,RT>::hz() const
{
 return  ptr()->hz() ;
}

template < class FT, class RT >
RT
CGAL_VectorH3<FT,RT>::hw() const
{
 return  ptr()->hw() ;
}

template < class FT, class RT >
int
CGAL_VectorH3<FT,RT>::dimension() const
{
 return 3;
}

template < class FT, class RT >
FT
CGAL_VectorH3<FT,RT>::cartesian(int i) const
{
switch (i)
 {
    case 0:   return x();
    case 1:   return y();
    case 2:   return z();
    default: cartesian( i%3 );
 }
 return FT( RT() );
}

template < class FT, class RT >
RT
CGAL_VectorH3<FT,RT>::homogeneous(int i) const
{
 switch (i)
 {
    case 0:   return hx();
    case 1:   return hy();
    case 2:   return hz();
    case 3:   return hw();
    default: assert(0);
 }
 return RT() ;
}
template < class FT, class RT >
CGAL_DirectionH3<FT,RT>
CGAL_VectorH3<FT,RT>::direction() const
{
 return CGAL_DirectionH3<FT,RT>(*this);
}
template < class FT, class RT >
bool
CGAL_VectorH3<FT,RT>::operator==( const CGAL_VectorH3& v) const
{
 return ( (hx() * v.hw() == v.hx() * hw() )
        &&(hy() * v.hw() == v.hy() * hw() )
        &&(hz() * v.hw() == v.hz() * hw() ) );
}

template < class FT, class RT >
bool
CGAL_VectorH3<FT,RT>::operator!=( const CGAL_VectorH3& v) const
{
 return !(*this == v);
}

template < class FT, class RT >
bool
CGAL_VectorH3<FT,RT>::identical( const CGAL_VectorH3& v) const
{
 return ( PTR == v.PTR );
}
template < class FT, class RT >
FT
CGAL_VectorH3<FT,RT>::operator[](int i) const
{
 return cartesian(i);
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>
CGAL_VectorH3<FT,RT>::operator-() const
{
 return CGAL_VectorH3<FT,RT>( - hx(), - hy(), -hz(), hw() );
}

template <class FT, class RT >
CGAL_DirectionH3<FT,RT>::CGAL_DirectionH3()
{
 PTR = new CGAL__RepH3<RT>();
}

template <class FT, class RT >
CGAL_DirectionH3<FT,RT>::CGAL_DirectionH3(const CGAL_DirectionH3 & tbc )
 : CGAL_Handle(tbc)
{
}

template <class FT, class RT >
CGAL_DirectionH3<FT,RT>::CGAL_DirectionH3(const CGAL_PointH3<FT,RT> & p )
 : CGAL_Handle( (CGAL_Handle&) p )
{
}

template <class FT, class RT >
CGAL_DirectionH3<FT,RT>::CGAL_DirectionH3(const CGAL_VectorH3<FT,RT> & v )
 : CGAL_Handle( (CGAL_Handle&) v )
{
}

template <class FT, class RT >
CGAL_DirectionH3<FT,RT>::CGAL_DirectionH3(const RT& x, const RT& y,
                                          const RT& z, const RT& w)
{
 if ( w >= 0 )
 {
    PTR = new CGAL__RepH3<RT>(x,y,z,w);
 }
 else
 {
    PTR = new CGAL__RepH3<RT>(-x,-y,-z,-w);
 }
}

template <class FT, class RT >
CGAL_DirectionH3<FT,RT>::~CGAL_DirectionH3()
{
}

template < class FT, class RT >
CGAL_DirectionH3<FT,RT> &
CGAL_DirectionH3<FT,RT>::operator=(const CGAL_DirectionH3<FT,RT> &d)
{
 CGAL_Handle::operator=(d);
 return *this;
}

template <class FT, class RT >
RT
CGAL_DirectionH3<FT,RT>::delta(int i) const
{
 switch (i)
 {
    case 0:  return x();
    case 1:  return y();
    case 2:  return z();
    default: return delta( i%3 );
 }
 return  RT() ;
}

template <class FT, class RT >
RT
CGAL_DirectionH3<FT,RT>::dx() const
{
 return ptr()->e0;
}

template <class FT, class RT >
RT
CGAL_DirectionH3<FT,RT>::x() const
{
 return ptr()->e0;
}

template <class FT, class RT >
RT
CGAL_DirectionH3<FT,RT>::hx() const
{
 return ptr()->e0;
}

template <class FT, class RT >
RT
CGAL_DirectionH3<FT,RT>::dy() const
{
 return ptr()->e1;
}

template <class FT, class RT >
RT
CGAL_DirectionH3<FT,RT>::y() const
{
 return ptr()->e1;
}

template <class FT, class RT >
RT
CGAL_DirectionH3<FT,RT>::hy() const
{
 return ptr()->e1;
}

template <class FT, class RT >
RT
CGAL_DirectionH3<FT,RT>::dz() const
{
 return ptr()->e2;
}

template <class FT, class RT >
RT
CGAL_DirectionH3<FT,RT>::z() const
{
 return ptr()->e2;
}

template <class FT, class RT >
RT
CGAL_DirectionH3<FT,RT>::hz() const
{
 return ptr()->e2;
}
template <class FT, class RT >
bool
CGAL_DirectionH3<FT,RT>::operator==( const CGAL_DirectionH3& d) const
{
 return ( ( ptr()->hx()*d.ptr()->hy() == ptr()->hy()*d.ptr()->hx() )
        &&( ptr()->hx()*d.ptr()->hz() == ptr()->hz()*d.ptr()->hx() )
        &&( ptr()->hy()*d.ptr()->hz() == ptr()->hz()*d.ptr()->hy() )
        &&( CGAL_sign( ptr()->hx() ) == CGAL_sign( d.ptr()->hx() ) )
        &&( CGAL_sign( ptr()->hy() ) == CGAL_sign( d.ptr()->hy() ) )
        &&( CGAL_sign( ptr()->hz() ) == CGAL_sign( d.ptr()->hz() ) ) );
}

template <class FT, class RT >
bool
CGAL_DirectionH3<FT,RT>::operator!=( const CGAL_DirectionH3& d) const
{
 return !operator==(d);
}

template <class FT, class RT >
bool
CGAL_DirectionH3<FT,RT>::is_degenerate() const
{
 return ((hx() == RT(0)) && (hy() == RT(0)) && (hz() == RT(0)));
}

template <class FT, class RT >
bool
CGAL_DirectionH3<FT,RT>::identical( const CGAL_DirectionH3& d) const
{
 return ( PTR == d.PTR );
}
template <class FT, class RT >
CGAL_DirectionH3<FT,RT>
CGAL_DirectionH3<FT,RT>::operator-() const
{
 return CGAL_DirectionH3( - ptr()->hx(), - ptr()->hy(), - ptr()->hz() );
}
template <class FT, class RT >
CGAL_VectorH3<FT,RT>
CGAL_DirectionH3<FT,RT>::vector() const
{
 return CGAL_VectorH3<FT,RT>(*this);
}


template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator+(const CGAL_VectorH3<FT,RT>& u, const CGAL_VectorH3<FT,RT>& v)
{
 return CGAL_VectorH3<FT,RT>(u.hx()*v.hw() + v.hx()*u.hw(),
                             u.hy()*v.hw() + v.hy()*u.hw(),
                             u.hz()*v.hw() + v.hz()*u.hw(),
                             u.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator-(const CGAL_VectorH3<FT,RT>& u, const CGAL_VectorH3<FT,RT>& v)
{
 return CGAL_VectorH3<FT,RT>(u.hx()*v.hw() - v.hx()*u.hw(),
                             u.hy()*v.hw() - v.hy()*u.hw(),
                             u.hz()*v.hw() - v.hz()*u.hw(),
                             u.hw()*v.hw() );
}

template <class FT, class RT>
FT
operator*(const CGAL_VectorH3<FT,RT>& u, const CGAL_VectorH3<FT,RT>& v)
{
 assert( u.hw() != RT(0) );
 assert( v.hw() != RT(0) );
 return ( FT( u.hx()*v.hx() + u.hy()*v.hy() + u.hz()*v.hz() ) /
          FT( u.hw()*v.hw() ) );
}

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator/(const CGAL_VectorH3<FT,RT>& v, const RT& f)
{
 return CGAL_VectorH3<FT,RT>( v.hx(), v.hy(), v.hz(), v.hw()*f );
}

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator*(const CGAL_VectorH3<FT,RT>& v, const RT& f)
{
 return CGAL_VectorH3<FT,RT>( v.hx()*f, v.hy()*f, v.hz()*f, v.hw() );
}

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator*(const RT& f, const CGAL_VectorH3<FT,RT>& v)
{
 return CGAL_VectorH3<FT,RT>( v.hx()*f, v.hy()*f, v.hz()*f, v.hw() );
}


template <class FT, class RT>
CGAL_VectorH3<FT,RT>
CGAL_cross_product(const CGAL_VectorH3<FT,RT>& a, const CGAL_VectorH3<FT,RT>& b)
{
 return CGAL_VectorH3<FT,RT>(a.hy()*b.hz() - a.hz()*b.hy(),
                             a.hz()*b.hx() - a.hx()*b.hz(),
                             a.hx()*b.hy() - a.hy()*b.hx(),
                             a.hw()*b.hw() );
}

template <class FT, class RT>
CGAL_PointH3<FT,RT>
operator+(const CGAL_Origin& , const CGAL_VectorH3<FT,RT>& v)
{
 return CGAL_PointH3<FT,RT>( v );
}

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator-(const CGAL_PointH3<FT,RT>& p, const CGAL_Origin& )
{
 return CGAL_VectorH3<FT,RT>( p );
}

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator-(const CGAL_Origin& , const CGAL_PointH3<FT,RT>& p)
{
 return  - CGAL_VectorH3<FT,RT>( p );
}

template <class FT, class RT>
CGAL_PointH3<FT,RT>
operator+(const CGAL_PointH3<FT,RT>& p, const CGAL_VectorH3<FT,RT>& v)
{
 return CGAL_PointH3<FT,RT>(p.hx()*v.hw() + v.hx()*p.hw(),
                            p.hy()*v.hw() + v.hy()*p.hw(),
                            p.hz()*v.hw() + v.hz()*p.hw(),
                            p.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_PointH3<FT,RT>
operator-(const CGAL_PointH3<FT,RT>& p, const CGAL_VectorH3<FT,RT>& v)
{
 return CGAL_PointH3<FT,RT>( p.hx()*v.hw() - v.hx()*p.hw(),
                             p.hy()*v.hw() - v.hy()*p.hw(),
                             p.hz()*v.hw() - v.hz()*p.hw(),
                             p.hw()*v.hw() );
}

template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator-(const CGAL_PointH3<FT,RT>& p, const CGAL_PointH3<FT,RT>& q)
{
 return CGAL_PointH3<FT,RT>( p.hx()*q.hw() - q.hx()*p.hw(),
                             p.hy()*q.hw() - q.hy()*p.hw(),
                             p.hz()*q.hw() - q.hz()*p.hw(),
                             p.hw()*q.hw() );
}




template <class FT, class RT>
CGAL_DirectionH3<FT,RT>
CGAL_cross_product( const CGAL_DirectionH3<FT,RT>& d1,
                    const CGAL_DirectionH3<FT,RT>& d2)
{
 return CGAL_cross_product(d1.vector(),d2.vector()).direction();
}


#include <CGAL/Aff_transformationH3.h>

#include <CGAL/Bbox_3.h>
#include <CGAL/misc.h>

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_PointH3<FT,RT>::transform(const CGAL_Aff_transformationH3<FT,RT>& t) const
{
 return t.transform(*this);
}

template < class FT, class RT >
CGAL_Bbox_3
CGAL_PointH3<FT,RT>::bbox() const
{
// double bx = CGAL_to_double(x());
// double by = CGAL_to_double(y());
// double bz = CGAL_to_double(z());
// return CGAL_Bbox_3(bx, by, bz, bx, by, bz);

 double eps  = double(1.0) /(double(1<<26) * double(1<<26));
 double hxd  = CGAL_to_double( hx() );
 double hyd  = CGAL_to_double( hy() );
 double hzd  = CGAL_to_double( hz() );
 double hwd  = CGAL_to_double( hw() );
 double xmin = ( hxd - eps*hxd ) / ( hwd + eps*hwd );
 double xmax = ( hxd + eps*hxd ) / ( hwd - eps*hwd );
 double ymin = ( hyd - eps*hyd ) / ( hwd + eps*hwd );
 double ymax = ( hyd + eps*hyd ) / ( hwd - eps*hwd );
 double zmin = ( hzd - eps*hzd ) / ( hwd + eps*hwd );
 double zmax = ( hzd + eps*hzd ) / ( hwd - eps*hwd );
 if ( hx() < RT(0)   )
 {
    CGAL_swap(xmin, xmax);
 }
 if ( hy() < RT(0)   )
 {
    CGAL_swap(ymin, ymax);
 }
 if ( hz() < RT(0)   )
 {
    CGAL_swap(zmin, zmax);
 }
 return CGAL_Bbox_3(xmin, ymin, zmin, xmax, ymax, zmax);
}

template < class FT, class RT >
CGAL_VectorH3<FT,RT>
CGAL_VectorH3<FT,RT>::transform(const CGAL_Aff_transformationH3<FT,RT>&t ) const
{
 return t.transform(*this);
}

template <class FT, class RT >
CGAL_DirectionH3<FT,RT>
CGAL_DirectionH3<FT,RT>::transform(const CGAL_Aff_transformationH3<FT,RT>& t)
                                                                          const
{
 return t.transform(*this);
}


template <class FT, class RT>
CGAL_VectorH3<FT,RT>
operator/(const CGAL_VectorH3<FT,RT>& v, const RT& f);

#endif // CGAL_PVDH3_H
