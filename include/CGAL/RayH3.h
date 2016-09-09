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

#ifndef CGAL_RAYH3_H
#define CGAL_RAYH3_H

#include <CGAL/LineH3.h>

template < class FT, class RT >
class CGAL__Ray_repH3 : public CGAL_Rep
{

public:
        CGAL__Ray_repH3()
          {
          }
        CGAL__Ray_repH3(const CGAL_PointH3<FT,RT>& p,
                        const CGAL_DirectionH3<FT,RT>& d)
          {
            startpoint = p;
            direction  = d;
          }
        ~CGAL__Ray_repH3()
          {
          }

 friend class CGAL_RayH3<FT,RT>;

private:

    CGAL_PointH3<FT,RT>      startpoint;
    CGAL_DirectionH3<FT,RT>  direction;
};

template < class FT, class RT >
class CGAL_RayH3 : public CGAL_Handle
{
public:
        CGAL_RayH3();
        CGAL_RayH3( const CGAL_RayH3 & tbc);
        CGAL_RayH3( const CGAL_PointH3<FT,RT>& sp,
                    const CGAL_PointH3<FT,RT>& secondp);
        CGAL_RayH3( const CGAL_PointH3<FT,RT>& sp,
                    const CGAL_DirectionH3<FT,RT>& d);
        ~CGAL_RayH3();

    CGAL_RayH3<FT,RT>&  operator=(const CGAL_RayH3 & r);

    CGAL_PointH3<FT,RT> start() const;
    CGAL_PointH3<FT,RT> source() const;
    CGAL_PointH3<FT,RT> second_point() const;
    CGAL_PointH3<FT,RT> point(int i) const;
    CGAL_DirectionH3<FT,RT>
                        direction() const;
    CGAL_LineH3<FT,RT>  supporting_line() const;
    CGAL_RayH3<FT,RT>   opposite() const;
    CGAL_RayH3<FT,RT>   transform( const CGAL_Aff_transformationH3<FT,RT> & t)
                                                                         const;
    bool                has_on(const CGAL_PointH3<FT,RT> p) const;
    bool                collinear_has_on(const CGAL_PointH3<FT,RT> p) const;
    bool                is_degenerate() const;

    bool                operator==(const CGAL_RayH3& r) const;
    bool                operator!=(const CGAL_RayH3& r) const;
    bool                identical( const CGAL_RayH3& r) const;

protected:

    CGAL__Ray_repH3<FT,RT>*
                        ptr() const;
};

template < class FT, class RT >
CGAL_RayH3<FT,RT>::CGAL_RayH3()
{
 PTR = new CGAL__Ray_repH3<FT,RT>;
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>::CGAL_RayH3(const CGAL_RayH3 & tbc)
 : CGAL_Handle(tbc)
{
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>::CGAL_RayH3( const CGAL_PointH3<FT,RT>& sp,
                               const CGAL_PointH3<FT,RT>& secondp)
{
 PTR = new CGAL__Ray_repH3<FT,RT>(sp,(secondp - sp).direction() );
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>::CGAL_RayH3( const CGAL_PointH3<FT,RT>& sp,
                               const CGAL_DirectionH3<FT,RT>& d)
{
 PTR = new CGAL__Ray_repH3<FT,RT>(sp, d );
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>::~CGAL_RayH3()
{
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>&
CGAL_RayH3<FT,RT>::operator=(const CGAL_RayH3<FT,RT>& r)
{
 CGAL_Handle::operator=(r);
 return *this;
}
template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_RayH3<FT,RT>::source() const
{
 return ptr()->startpoint;
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_RayH3<FT,RT>::start() const
{
 return ptr()->startpoint;
}

template < class FT, class RT >
CGAL_DirectionH3<FT,RT>
CGAL_RayH3<FT,RT>::direction() const
{
 CGAL_kernel_precondition( !is_degenerate() );
 return CGAL_DirectionH3<FT,RT>( ptr()->direction );
}
template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_RayH3<FT,RT>::second_point() const
{
 return start() + direction().vector();
}

template < class FT, class RT >
CGAL_PointH3<FT,RT>
CGAL_RayH3<FT,RT>::point(int i) const
{
 CGAL_kernel_precondition( i >= 0 );
 return start() + RT(i)*(direction().vector() ) ;
}

template < class FT, class RT >
CGAL_LineH3<FT,RT>
CGAL_RayH3<FT,RT>::supporting_line() const
{
 CGAL_kernel_precondition( !is_degenerate() );
 return CGAL_LineH3<FT,RT>(start(), second_point() );
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>
CGAL_RayH3<FT,RT>::opposite() const
{
 return CGAL_RayH3( start(), - direction() );
}

template < class FT, class RT >
CGAL_RayH3<FT,RT>
CGAL_RayH3<FT,RT>::transform( const CGAL_Aff_transformationH3<FT,RT> & t) const
{
 return CGAL_RayH3(t.transform(start()), t.transform(direction()) );
}
template < class FT, class RT >
bool
CGAL_RayH3<FT,RT>::has_on(const CGAL_PointH3<FT,RT> p) const
{
 return ( (  p == start() )
        ||(  CGAL_DirectionH3<FT,RT>(p - start()) == direction() ) );
}

template < class FT, class RT >
bool
CGAL_RayH3<FT,RT>::collinear_has_on(const CGAL_PointH3<FT,RT> p) const
{
 return has_on(p);
}

template < class FT, class RT >
bool
CGAL_RayH3<FT,RT>::is_degenerate() const
{
 return (ptr()->direction).is_degenerate() ;
}
template < class FT, class RT >
bool
CGAL_RayH3<FT,RT>::operator==(const CGAL_RayH3& r) const
{
 return ( (start() == r.start() )&&( direction() == r.direction() ) );
}

template < class FT, class RT >
bool
CGAL_RayH3<FT,RT>::operator!=( const CGAL_RayH3& r) const
{
 return !operator==(r);
}

template < class FT, class RT >
bool
CGAL_RayH3<FT,RT>::identical( const CGAL_RayH3& r) const
{
 return ( PTR == r.PTR );
}
template < class FT, class RT >
CGAL__Ray_repH3<FT,RT>*
CGAL_RayH3<FT,RT>::ptr() const
{
 return (CGAL__Ray_repH3<FT,RT>*)PTR;
}


#endif // CGAL_RAYH3_H
