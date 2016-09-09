

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

// Source: TriangleH2.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_TRIANGLEH2_H
#define CGAL_TRIANGLEH2_H

#include <CGAL/PointH2.h>
#include <CGAL/predicates_on_pointsH2.h>



template <class FT, class RT>
class CGAL_Triangle_repH2 : public CGAL_Rep
{

friend class CGAL_TriangleH2<FT,RT>;

            CGAL_Triangle_repH2()
            {
            }
            CGAL_Triangle_repH2(const CGAL_PointH2<FT,RT> v1,
                                const CGAL_PointH2<FT,RT> v2,
                                const CGAL_PointH2<FT,RT> v3)
            {
              A[0] = v1;
              A[1] = v2;
              A[2] = v3;
              orientation = CGAL_orientation(v1,v2,v3);
            }
            CGAL_Triangle_repH2(const CGAL_Triangle_repH2<FT,RT>& tbc)
            {
              A[0] = tbc.A[0];
              A[1] = tbc.A[1];
              A[2] = tbc.A[2];
              orientation = tbc.orientation;
            }

            CGAL_PointH2<FT,RT>   A[3];
            CGAL_Orientation      orientation;
};



template <class FT, class RT>
class CGAL_TriangleH2 : public CGAL_Handle
{
public:
                       CGAL_TriangleH2();
                       CGAL_TriangleH2(const CGAL_TriangleH2& t);
                       CGAL_TriangleH2(const CGAL_PointH2<FT,RT>& p,
                                       const CGAL_PointH2<FT,RT>& q,
                                       const CGAL_PointH2<FT,RT>& r);

    CGAL_TriangleH2<FT,RT>&
                       operator=(const CGAL_TriangleH2<FT,RT>& t);

    CGAL_Bbox_2        bbox() const;

    CGAL_TriangleH2<FT,RT>
                       transform(const CGAL_Aff_transformationH2<FT,RT>&) const;

    CGAL_Orientation   orientation() const;

    CGAL_Oriented_side oriented_side(const CGAL_PointH2<FT,RT>& ) const;
    CGAL_Bounded_side  bounded_side(const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_positive_side( const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_negative_side( const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_boundary( const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_bounded_side( const CGAL_PointH2<FT,RT>& ) const;
    bool               has_on_unbounded_side(const CGAL_PointH2<FT,RT>& )const;
    bool               is_degenerate() const;

    bool               operator==( const CGAL_TriangleH2<FT,RT>& ) const;
    bool               operator!=( const CGAL_TriangleH2<FT,RT>& ) const;
    bool               identical ( const CGAL_TriangleH2<FT,RT>& ) const;
    int                id() const;

    // bool            oriented_equal( const CGAL_TriangleH2<FT,RT>& ) const;
    // bool            unoriented_equal( const CGAL_TriangleH2<FT,RT>& ) const;

    CGAL_PointH2<FT,RT>
                       vertex(int i) const;
    CGAL_PointH2<FT,RT>
                       operator[](int i) const;

protected:

    CGAL_Triangle_repH2<FT,RT>*
                       ptr() const;
};

template < class FT, class RT >
inline
CGAL_Triangle_repH2<FT,RT>*
CGAL_TriangleH2<FT,RT>::ptr() const
{
 return (CGAL_Triangle_repH2<FT,RT>*)PTR;
}

template < class FT, class RT >
inline
CGAL_TriangleH2<FT,RT>::CGAL_TriangleH2()
{
 PTR = new CGAL_Triangle_repH2<FT,RT>();
}

template < class FT, class RT >
CGAL_TriangleH2<FT,RT>::CGAL_TriangleH2(const CGAL_TriangleH2<FT,RT>& t)
 : CGAL_Handle((CGAL_Handle&) t)
{
}

template < class FT, class RT >
CGAL_TriangleH2<FT,RT>::CGAL_TriangleH2(const CGAL_PointH2<FT,RT>& p,
                                        const CGAL_PointH2<FT,RT>& q,
                                        const CGAL_PointH2<FT,RT>& r)
{
 PTR = new CGAL_Triangle_repH2<FT,RT>(p,q,r);
}

template < class FT, class RT >
CGAL_TriangleH2<FT,RT>&
CGAL_TriangleH2<FT,RT>::operator=(const CGAL_TriangleH2<FT,RT> &t)
{
 CGAL_Handle::operator=(t);
 return *this;
}
template <class FT, class RT>
CGAL_PointH2<FT,RT>
CGAL_TriangleH2<FT,RT>::vertex(int i) const
{
 return ptr()->A[ i % 3 ];
}

template <class FT, class RT>
CGAL_PointH2<FT,RT>
CGAL_TriangleH2<FT,RT>::operator[](int i) const
{
 return vertex(i);
}

template <class FT, class RT>
CGAL_Orientation
CGAL_TriangleH2<FT,RT>::orientation() const
{
 return ptr()->orientation;
}
template <class FT, class RT>
CGAL_Oriented_side
CGAL_TriangleH2<FT,RT>::oriented_side( const CGAL_PointH2<FT,RT>& p) const
{
 CGAL_Orientation o12 = CGAL_orientation( vertex(1), vertex(2), p);
 CGAL_Orientation o23 = CGAL_orientation( vertex(2), vertex(3), p);
 CGAL_Orientation o31 = CGAL_orientation( vertex(3), vertex(1), p);

 if (ptr()->orientation == CGAL_CLOCKWISE)
 {
    if (  (o12 == CGAL_COUNTERCLOCKWISE)
        ||(o23 == CGAL_COUNTERCLOCKWISE)
        ||(o31 == CGAL_COUNTERCLOCKWISE) )
    {
        return CGAL_ON_POSITIVE_SIDE;
    }
    if (  (o12 == CGAL_COLLINEAR)
        ||(o23 == CGAL_COLLINEAR)
        ||(o31 == CGAL_COLLINEAR) )
    {
        return CGAL_ON_ORIENTED_BOUNDARY;
    }
    else
    {
        return CGAL_ON_NEGATIVE_SIDE;
    }
 }
 else       // COUNTERCLOCKWISE
 {
    if (  (o12 == CGAL_CLOCKWISE)
        ||(o23 == CGAL_CLOCKWISE)
        ||(o31 == CGAL_CLOCKWISE) )
    {
        return CGAL_ON_NEGATIVE_SIDE;
    }
    if (  (o12 == CGAL_COLLINEAR)
        ||(o23 == CGAL_COLLINEAR)
        ||(o31 == CGAL_COLLINEAR) )
    {
        return CGAL_ON_ORIENTED_BOUNDARY;
    }
    else
    {
        return CGAL_ON_POSITIVE_SIDE;
    }
 }
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::has_on_positive_side( const CGAL_PointH2<FT,RT>& p)
                                                                         const
{
 return ( oriented_side(p) == CGAL_ON_POSITIVE_SIDE );
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::has_on_boundary(const CGAL_PointH2<FT,RT>& p) const
{
 return oriented_side(p) == CGAL_ON_ORIENTED_BOUNDARY;
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::has_on_negative_side( const CGAL_PointH2<FT,RT>& p)
                                                                         const
{
 return  oriented_side(p) == CGAL_ON_NEGATIVE_SIDE;
}

template <class FT, class RT>
CGAL_Bounded_side
CGAL_TriangleH2<FT,RT>::bounded_side(const CGAL_PointH2<FT,RT>& p) const
{
 CGAL_kernel_precondition( ! is_degenerate() );

 CGAL_Orientation o12 = CGAL_orientation( vertex(1), vertex(2), p);
 CGAL_Orientation o23 = CGAL_orientation( vertex(2), vertex(3), p);
 CGAL_Orientation o31 = CGAL_orientation( vertex(3), vertex(1), p);
 CGAL_Orientation ori = orientation();
 CGAL_Orientation opp = CGAL_opposite( ori);

 if ( (o12 == opp) || (o23 == opp) || (o31 == opp) )
 {
    return CGAL_ON_UNBOUNDED_SIDE;
 }
 if ( (o12 == ori) && (o23 == ori) && (o31 == ori) )
 {
    return CGAL_ON_BOUNDED_SIDE;
 }
 return CGAL_ON_BOUNDARY;
}


template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::has_on_bounded_side(const CGAL_PointH2<FT,RT>& p) const
{
 CGAL_kernel_precondition( ! is_degenerate() );

 CGAL_Orientation o12 = CGAL_orientation( vertex(1), vertex(2), p);
 CGAL_Orientation o23 = CGAL_orientation( vertex(2), vertex(3), p);
 CGAL_Orientation o31 = CGAL_orientation( vertex(3), vertex(1), p);
 CGAL_Orientation ori = ptr()->orientation;

 return  ( (o12 == ori) && (o23 == ori) && (o31 == ori) );
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::has_on_unbounded_side(const CGAL_PointH2<FT,RT>& p)
                                                                          const
{
 CGAL_kernel_precondition( ! is_degenerate() );

 CGAL_Orientation o12 = CGAL_orientation( vertex(1), vertex(2), p);
 CGAL_Orientation o23 = CGAL_orientation( vertex(2), vertex(3), p);
 CGAL_Orientation o31 = CGAL_orientation( vertex(3), vertex(1), p);
 CGAL_Orientation opp = CGAL_opposite( ptr()->orientation );

 return  ( (o12 == opp) || (o23 == opp) || (o31 == opp) );
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::is_degenerate() const
{
 return (ptr()->orientation == CGAL_COLLINEAR);
}

template <class FT, class RT>
CGAL_Bbox_2
CGAL_TriangleH2<FT,RT>::bbox() const
{
 return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
}


template <class FT, class RT>
CGAL_TriangleH2<FT,RT>
CGAL_TriangleH2<FT,RT>::transform( const CGAL_Aff_transformationH2<FT,RT>& t)
                                                                          const
{
 return CGAL_TriangleH2<FT,RT>(t.transform(ptr()->A[0]),
                               t.transform(ptr()->A[1]),
                               t.transform(ptr()->A[2]) );
}


template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::operator==(const CGAL_TriangleH2<FT,RT>& t) const
{
 int j = 0;
 while ( (t.vertex(0) != vertex(j)) && (j < 3) ) j++;
 if ( j == 3)
 {
    return false;
 }
 if ( (t.vertex(1) == vertex(j+1)) && (t.vertex(2) == vertex(j+2)) )
 {
    return true;
 }
 return false;
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::operator!=(const CGAL_TriangleH2<FT,RT>& t) const
{
 return !(*this == t);
}

template <class FT, class RT>
bool
CGAL_TriangleH2<FT,RT>::identical(const CGAL_TriangleH2<FT,RT>& t) const
{
 return (PTR == t.PTR) ;
}

template <class FT, class RT>
int
CGAL_TriangleH2<FT,RT>::id() const
{
 return (int)PTR;
}


#endif // CGAL_TRIANGLEH2_H
