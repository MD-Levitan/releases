

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

// Source: CircleH2.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_CIRCLEH2_H
#define CGAL_CIRCLEH2_H

#include <CGAL/enum.h>
#include <CGAL/PointH2.h>
#include <CGAL/predicates_on_pointsH2.h>
#include <CGAL/distance_predicatesH2.h>
#include <CGAL/basic_constructionsH2.h>



template <class FT, class RT>
class CGAL_Circle_repH2 : public CGAL_Rep
{
public:

friend class CGAL_CircleH2<FT,RT>;

            CGAL_Circle_repH2();
            CGAL_Circle_repH2(const CGAL_PointH2<FT,RT> p,
                              const FT sq_rad,
                              const CGAL_Orientation& or);
            ~CGAL_Circle_repH2();

protected:
            CGAL_PointH2<FT,RT>   center;
            FT                    squared_radius;
            CGAL_Orientation      orientation;
};

template <class FT, class RT>
CGAL_Circle_repH2<FT,RT>::CGAL_Circle_repH2()
{}

template <class FT, class RT>
CGAL_Circle_repH2<FT,RT>::CGAL_Circle_repH2(
                              const CGAL_PointH2<FT,RT> p,
                              const FT sq_rad,
                              const CGAL_Orientation& or)
 : center(p), squared_radius(sq_rad), orientation(or)
{}

template <class FT, class RT>
CGAL_Circle_repH2<FT,RT>::~CGAL_Circle_repH2()
{}



template <class FT, class RT>
class CGAL_CircleH2 : public CGAL_Handle
{
public:
                       CGAL_CircleH2();
                       CGAL_CircleH2(const CGAL_CircleH2& t);
                       CGAL_CircleH2(const CGAL_PointH2<FT,RT>& p,
                                     const CGAL_PointH2<FT,RT>& q,
                                     const CGAL_PointH2<FT,RT>& r);
                       CGAL_CircleH2(const CGAL_PointH2<FT,RT>& cp,
                                     const FT&  sq_rad );
                       CGAL_CircleH2(const CGAL_PointH2<FT,RT>& cp,
                                     const CGAL_PointH2<FT,RT>& p);
                       CGAL_CircleH2(const CGAL_PointH2<FT,RT>& cp,
                                     const CGAL_PointH2<FT,RT>& p,
                                     const CGAL_Orientation& o);
                       CGAL_CircleH2(const CGAL_PointH2<FT,RT>& cp,
                                     const FT&  sq_rad,
                                     const CGAL_Orientation& o);
                       ~CGAL_CircleH2();

    CGAL_CircleH2<FT,RT>&
                       operator=(const CGAL_CircleH2<FT,RT>& t);

    CGAL_Bbox_2        bbox() const;

    CGAL_CircleH2<FT,RT>
                       orthogonal_transform(
                                 const CGAL_Aff_transformationH2<FT,RT>&) const;

    CGAL_PointH2<FT,RT>
                       center() const;
    CGAL_Orientation   orientation() const;
    FT                 squared_radius() const;

    CGAL_CircleH2<FT,RT>
                       opposite() const;

    CGAL_Oriented_side oriented_side(const CGAL_PointH2<FT,RT>& ) const;
    CGAL_Bounded_side  bounded_side(const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_positive_side( const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_negative_side( const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_boundary( const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_bounded_side( const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_unbounded_side(const CGAL_PointH2<FT,RT>& )const;
    bool               is_degenerate() const;

    bool               operator==( const CGAL_CircleH2<FT,RT>& ) const;
    bool               operator!=( const CGAL_CircleH2<FT,RT>& ) const;
    bool               identical ( const CGAL_CircleH2<FT,RT>& ) const;
    int                id() const;

    // bool            oriented_equal( const CGAL_CircleH2<FT,RT>& ) const;
    // bool            unoriented_equal( const CGAL_CircleH2<FT,RT>& ) const;


protected:

    CGAL_Circle_repH2<FT,RT>*
                       ptr() const;
};

template < class FT, class RT >
inline
CGAL_Circle_repH2<FT,RT>*
CGAL_CircleH2<FT,RT>::ptr() const
{
 return (CGAL_Circle_repH2<FT,RT>*)PTR;
}

template < class FT, class RT >
inline
CGAL_CircleH2<FT,RT>::~CGAL_CircleH2()
{}

template < class FT, class RT >
inline
CGAL_CircleH2<FT,RT>::CGAL_CircleH2()
{
 PTR = new CGAL_Circle_repH2<FT,RT>();
}

template < class FT, class RT >
CGAL_CircleH2<FT,RT>::CGAL_CircleH2(const CGAL_CircleH2<FT,RT>& c)
 : CGAL_Handle((CGAL_Handle&) c)
{}

template < class FT, class RT >
CGAL_CircleH2<FT,RT>::CGAL_CircleH2(const CGAL_PointH2<FT,RT>& p,
                                    const CGAL_PointH2<FT,RT>& q,
                                    const CGAL_PointH2<FT,RT>& r)
{
 CGAL_PointH2<FT,RT> cp  = CGAL_circumcenter( p,q,r );
 CGAL_Orientation    o;
 FT                  sq_r;
 if ( cp.hw() != RT(0) )
 {
    o      = CGAL_orientation( p, q, r);
    sq_r   = CGAL_squared_distance( p, cp );
    PTR = new CGAL_Circle_repH2<FT,RT>(cp, sq_r, o);
 }
 else
 {
    PTR = new CGAL_Circle_repH2<FT,RT>(cp, RT(0), CGAL_ZERO);
 }
}

template < class FT, class RT >
CGAL_CircleH2<FT,RT>::CGAL_CircleH2(const CGAL_PointH2<FT,RT>& cp,
                                    const FT&  sq_rad)
{
 PTR = new CGAL_Circle_repH2<FT,RT>(cp, sq_rad, CGAL_POSITIVE);
}

template < class FT, class RT >
CGAL_CircleH2<FT,RT>::CGAL_CircleH2(const CGAL_PointH2<FT,RT>& cp,
                                    const CGAL_PointH2<FT,RT>& p,
                                    const CGAL_Orientation& o)
{
 PTR = new CGAL_Circle_repH2<FT,RT>(cp,
                                    CGAL_squared_distance(cp, p),
                                    o );
}

template < class FT, class RT >
CGAL_CircleH2<FT,RT>::CGAL_CircleH2(const CGAL_PointH2<FT,RT>& cp,
                                    const CGAL_PointH2<FT,RT>& p)
{
 PTR = new CGAL_Circle_repH2<FT,RT>(cp,
                                    CGAL_squared_distance(cp, p),
                                    CGAL_POSITIVE);
}

template < class FT, class RT >
CGAL_CircleH2<FT,RT>::CGAL_CircleH2(const CGAL_PointH2<FT,RT>& cp,
                                    const FT&  sq_rad,
                                    const CGAL_Orientation& o)
{
 PTR = new CGAL_Circle_repH2<FT,RT>(cp, sq_rad, o);
}

template < class FT, class RT >
CGAL_CircleH2<FT,RT>&
CGAL_CircleH2<FT,RT>::operator=(const CGAL_CircleH2<FT,RT> &t)
{
 CGAL_Handle::operator=(t);
 return *this;
}
template <class FT, class RT>
CGAL_PointH2<FT,RT>
CGAL_CircleH2<FT,RT>::center() const
{
 return ptr()->center;
}

template <class FT, class RT>
FT
CGAL_CircleH2<FT,RT>::squared_radius() const
{
 return ptr()->squared_radius;
}

template <class FT, class RT>
CGAL_CircleH2<FT,RT>
CGAL_CircleH2<FT,RT>::opposite() const
{
 return CGAL_CircleH2<FT,RT>( center(),
                              squared_radius(),
                              CGAL_opposite( orientation() ) );
}

template <class FT, class RT>
CGAL_Orientation
CGAL_CircleH2<FT,RT>::orientation() const
{
 return ptr()->orientation;
}
template <class FT, class RT>
CGAL_Oriented_side
CGAL_CircleH2<FT,RT>::oriented_side( const CGAL_PointH2<FT,RT>& p) const
{
 FT sq_dist = CGAL_squared_distance( p, center() );
 FT sq_rad  = squared_radius();
 CGAL_Comparison_result vgl = CGAL_compare( sq_dist, sq_rad );
 CGAL_Oriented_side rel_pos = (vgl == CGAL_LARGER ) ?
                                  CGAL_ON_NEGATIVE_SIDE :
                                  ( (vgl == CGAL_SMALLER ) ?
                                         CGAL_ON_POSITIVE_SIDE :
                                         CGAL_ON_ORIENTED_BOUNDARY);
 if (ptr()->orientation == CGAL_POSITIVE)
 {
    return rel_pos;
 }
 else       // NEGATIVE
 {
    return CGAL_opposite( rel_pos );
 }
}

template <class FT, class RT>
bool
CGAL_CircleH2<FT,RT>::has_on_positive_side( const CGAL_PointH2<FT,RT>& p) const
{
 if ( orientation() == CGAL_POSITIVE )
 {
    return (has_on_bounded_side(p) );
 }
 else
 {
    return (has_on_unbounded_side(p) );
 }
}

template <class FT, class RT>
bool
CGAL_CircleH2<FT,RT>::has_on_boundary(const CGAL_PointH2<FT,RT>& p) const
{
 FT sq_dist = CGAL_squared_distance( p, center() );
 FT sq_rad  = squared_radius();
 return ( sq_dist == sq_rad );
}

template <class FT, class RT>
bool
CGAL_CircleH2<FT,RT>::has_on_negative_side( const CGAL_PointH2<FT,RT>& p) const
{
 if ( orientation() == CGAL_NEGATIVE )
 {
    return (has_on_bounded_side(p) );
 }
 else
 {
    return (has_on_unbounded_side(p) );
 }
}

template <class FT, class RT>
CGAL_Bounded_side
CGAL_CircleH2<FT,RT>::bounded_side(const CGAL_PointH2<FT,RT>& p) const
{
 FT sq_dist = CGAL_squared_distance( p, center() );
 FT sq_rad  = squared_radius();
 CGAL_Comparison_result vgl = CGAL_compare( sq_dist, sq_rad );
 return  (vgl == CGAL_LARGER ) ? CGAL_ON_UNBOUNDED_SIDE :
                                  ( (vgl == CGAL_SMALLER ) ?
                                         CGAL_ON_BOUNDED_SIDE :
                                         CGAL_ON_BOUNDARY);
}

template <class FT, class RT>
bool
CGAL_CircleH2<FT,RT>::has_on_bounded_side(const CGAL_PointH2<FT,RT>& p) const
{
 FT sq_dist = CGAL_squared_distance( p, center() );
 FT sq_rad  = squared_radius();
 return ( sq_dist < sq_rad );
}

template <class FT, class RT>
bool
CGAL_CircleH2<FT,RT>::has_on_unbounded_side(const CGAL_PointH2<FT,RT>& p) const
{
 FT sq_dist = CGAL_squared_distance( p, center() );
 FT sq_rad  = squared_radius();
 return ( sq_dist > sq_rad );
}

template <class FT, class RT>
bool
CGAL_CircleH2<FT,RT>::is_degenerate() const
{
 return ( squared_radius() == RT(0) );
}

template <class FT, class RT>
CGAL_Bbox_2
CGAL_CircleH2<FT,RT>::bbox() const
{
 double eps  = double(1.0) /(double(1<<26) * double(1<<26));
 double hxd  = CGAL_to_double( center().hx() );
 double hyd  = CGAL_to_double( center().hy() );
 double hwd  = CGAL_to_double( center().hw() );
 double xmin = ( hxd - eps*hxd ) / ( hwd + eps*hwd );
 double xmax = ( hxd + eps*hxd ) / ( hwd - eps*hwd );
 double ymin = ( hyd - eps*hyd ) / ( hwd + eps*hwd );
 double ymax = ( hyd + eps*hyd ) / ( hwd - eps*hwd );
 if ( center().hx() < RT(0)   )
 {
    CGAL_swap(xmin, xmax);
 }
 if ( center().hy() < RT(0)   )
 {
    CGAL_swap(ymin, ymax);
 }
 double sqradd = CGAL_to_double( squared_radius() );
 sqradd += sqradd*eps;
 xmin -= sqradd;
 xmax += sqradd;
 xmin -= xmin*eps;
 xmax += xmax*eps;
 return CGAL_Bbox_2(xmin, ymin, xmax, ymax);
}


template <class FT, class RT>
CGAL_CircleH2<FT,RT>
CGAL_CircleH2<FT,RT>::orthogonal_transform(
                               const CGAL_Aff_transformationH2<FT,RT>& t) const
{
 CGAL_VectorH2<FT,RT> vec( RT(1), RT(0) );   // unit vector
 vec = vec.transform(t);                     // transformed
 FT  sq_scale = FT( vec*vec );               // squared scaling factor

 if ( t.is_even() )
 {
    return CGAL_CircleH2<FT,RT>(t.transform(center() ),
                                sq_scale * squared_radius(),
                                orientation() );
 }
 else
 {
    return CGAL_CircleH2<FT,RT>(t.transform(center() ),
                                sq_scale * squared_radius(),
                                CGAL_opposite( orientation()) );
 }
}


template <class FT, class RT>
bool
CGAL_CircleH2<FT,RT>::operator==(const CGAL_CircleH2<FT,RT>& c) const
{
 return  ( center() == c.center() )
       &&( squared_radius() == c.squared_radius() )
       &&( orientation() == c.orientation() );
}

template <class FT, class RT>
bool
CGAL_CircleH2<FT,RT>::operator!=(const CGAL_CircleH2<FT,RT>& c) const
{
 return !(*this == c);
}

template <class FT, class RT>
bool
CGAL_CircleH2<FT,RT>::identical(const CGAL_CircleH2<FT,RT>& c) const
{
 return (PTR == c.PTR) ;
}

template <class FT, class RT>
int
CGAL_CircleH2<FT,RT>::id() const
{
 return (int)PTR;
}


#endif // CGAL_CIRCLEH2_H
