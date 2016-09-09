

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

// Source: basic_constructionsH2.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_BASIC_CONSTRUCTIONSH2_H
#define CGAL_BASIC_CONSTRUCTIONSH2_H

#include <CGAL/PointH2.h>
#include <CGAL/LineH2.h>



template <class FT, class RT>
CGAL_PointH2<FT,RT>
CGAL_gp_linear_intersection(const CGAL_LineH2<FT,RT>& l1,
                            const CGAL_LineH2<FT,RT>& l2)
{
 return CGAL_PointH2<FT,RT>( l1.b()*l2.c() - l2.b()*l1.c(),
                             l2.a()*l1.c() - l1.a()*l2.c(),
                             l1.a()*l2.b() - l2.a()*l1.b() );
}

template <class FT, class RT>
CGAL_LineH2<FT,RT>
CGAL_bisector( const CGAL_PointH2<FT,RT>& p,
               const CGAL_PointH2<FT,RT>& q )
{
 // Bisector equation is based on equation
 // ( X - p.x())^2 + (Y - p.y())^2 == ( X - q.x())^2 + (Y - q.y())
 // and x() = hx()/hw() ...

 RT phx = p.hx();
 RT phy = p.hy();
 RT phw = p.hw();
 RT qhx = q.hx();
 RT qhy = q.hy();
 RT qhw = q.hw();

 RT a = 2 * ( qhx*qhw*phw*phw - phx*phw*qhw*qhw );
 RT b = 2 * ( qhy*qhw*phw*phw - phy*phw*qhw*qhw );
 RT c = phx*phx*qhw*qhw + phy*phy*qhw*qhw - qhx*qhx*phw*phw - qhy*qhy*phw*phw;

 return CGAL_LineH2<FT,RT>( a, b, c );
}

template <class FT, class RT>
FT
CGAL_squared_distance( const CGAL_PointH2<FT,RT>& p,
                       const CGAL_PointH2<FT,RT>& q )
{
 RT phx = p.hx();
 RT phy = p.hy();
 RT phw = p.hw();
 RT qhx = q.hx();
 RT qhy = q.hy();
 RT qhw = q.hw();

 RT sq_dist_numerator =
         phx * phx * qhw * qhw
   - 2 * phx * qhx * phw * qhw
   +     qhx * qhx * phw * phw

   +     phy * phy * qhw * qhw
   - 2 * phy * qhy * phw * qhw
   +     qhy * qhy * phw * phw ;

 RT sq_dist_denominator = qhw * qhw * phw * phw ;

 return FT( sq_dist_numerator ) / FT( sq_dist_denominator );
}

template <class FT, class RT>
CGAL_PointH2<FT,RT>
CGAL_circumcenter( const CGAL_PointH2<FT,RT>& p,
                   const CGAL_PointH2<FT,RT>& q,
                   const CGAL_PointH2<FT,RT>& r )
{
 RT phx = p.hx();
 RT phy = p.hy();
 RT phw = p.hw();
 RT qhx = q.hx();
 RT qhy = q.hy();
 RT qhw = q.hw();
 RT rhx = r.hx();
 RT rhy = r.hy();
 RT rhw = r.hw();

#ifdef EXPANDED
 RT vvx =
      ( qhy*qhw*phw*phw - phy*phw*qhw*qhw )
     *( phx*phx*rhw*rhw + phy*phy*rhw*rhw - rhx*rhx*phw*phw - rhy*rhy*phw*phw )
   -  ( rhy*rhw*phw*phw - phy*phw*rhw*rhw )
     *( phx*phx*qhw*qhw + phy*phy*qhw*qhw - qhx*qhx*phw*phw - qhy*qhy*phw*phw );

 RT vvy =
   -  ( qhx*qhw*phw*phw - phx*phw*qhw*qhw )
     *( phx*phx*rhw*rhw + phy*phy*rhw*rhw - rhx*rhx*phw*phw - rhy*rhy*phw*phw )
   +  ( rhx*rhw*phw*phw - phx*phw*rhw*rhw )
     *( phx*phx*qhw*qhw + phy*phy*qhw*qhw - qhx*qhx*phw*phw - qhy*qhy*phw*phw );

 RT vvw = RT(2) *
   (  ( qhx*qhw*phw*phw - phx*phw*qhw*qhw )
     *( rhy*rhw*phw*phw - phy*phw*rhw*rhw )
   -  ( rhx*rhw*phw*phw - phx*phw*rhw*rhw )
     *( qhy*qhw*phw*phw - phy*phw*qhw*qhw ) );
#endif

 RT qy_py = ( qhy*qhw*phw*phw - phy*phw*qhw*qhw );
 RT qx_px = ( qhx*qhw*phw*phw - phx*phw*qhw*qhw );
 RT rx_px = ( rhx*rhw*phw*phw - phx*phw*rhw*rhw );
 RT ry_py = ( rhy*rhw*phw*phw - phy*phw*rhw*rhw );

 RT px2_py2_rx2_ry_2 =
     phx*phx*rhw*rhw + phy*phy*rhw*rhw - rhx*rhx*phw*phw - rhy*rhy*phw*phw ;
 RT px2_py2_qx2_qy_2 =
     phx*phx*qhw*qhw + phy*phy*qhw*qhw - qhx*qhx*phw*phw - qhy*qhy*phw*phw ;

 RT vvx = qy_py * px2_py2_rx2_ry_2 - ry_py * px2_py2_qx2_qy_2;
 RT vvy = rx_px * px2_py2_qx2_qy_2 - qx_px * px2_py2_rx2_ry_2;
 RT vvw = RT(2) * ( qx_px * ry_py - rx_px * qy_py );

 return CGAL_PointH2<FT,RT>( vvx, vvy, vvw );
}


#endif // CGAL_BASIC_CONSTRUCTIONSH2_H
