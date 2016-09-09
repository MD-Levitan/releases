// Copyright (c) 2003-2006  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.7-branch/Algebraic_kernel_for_circles/include/CGAL/Algebraic_kernel_for_circles/internal_functions_on_roots_and_polynomial_1_2_and_2_2.h $
// $Id: internal_functions_on_roots_and_polynomial_1_2_and_2_2.h 35577 2006-12-17 13:28:08Z hemmer $
//
// Author(s)     : Monique Teillaud, Sylvain Pion, Julien Hazebrouck

// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)

#ifndef CGAL_ALGEBRAIC_KERNEL_FOR_CIRCLES_FUNCTIONS_ON_ROOTS_AND_POLYNOMIAL_1_2_AND_2_2_H
#define CGAL_ALGEBRAIC_KERNEL_FOR_CIRCLES_FUNCTIONS_ON_ROOTS_AND_POLYNOMIAL_1_2_AND_2_2_H


namespace CGAL {
  namespace AlgebraicFunctors {


  template < class AK, class OutputIterator >
  inline 
  OutputIterator
  solve( const typename AK::Polynomial_1_2 & e1,
	 const typename AK::Polynomial_for_circles_2_2 & e2,
	 OutputIterator res )
  {
    typedef typename AK::FT FT;
    typedef typename AK::Root_of_2 Root_of_2;
    typedef typename AK::Root_for_circles_2_2 Root_for_circles_2_2;
    if (is_zero(e1.a())){//horizontal line
      
      const FT hy = -e1.c()/e1.b();
      const FT hdisc = e2.r_sq() - CGAL::square(hy - e2.b());
      CGAL::Sign sign_hdisc = CGAL::sign(hdisc);
    
      if(sign_hdisc == NEGATIVE) return res;
      if(sign_hdisc == ZERO) {	
	*res++ = std::make_pair
	  ( Root_for_circles_2_2(Root_of_2(e2.a()), 
                                 Root_of_2(hy)), 2u);
	return res;
      }
      const Root_of_2 x_res1 = make_root_of_2(e2.a(),FT(-1),hdisc);
      const Root_of_2 x_res2 = make_root_of_2(e2.a(),FT(1),hdisc);
      const Root_of_2 y_res = Root_of_2(hy);  
      *res++ = std::make_pair
	( Root_for_circles_2_2(x_res1, y_res), 1u);
      *res++ = std::make_pair
	( Root_for_circles_2_2(x_res2, y_res), 1u);
      return res;
    }
    else if(is_zero(e1.b())){//vertical line
      
      const FT vx = -e1.c()/e1.a();
      const FT vdisc = e2.r_sq() - CGAL::square(vx - e2.a());
      CGAL::Sign sign_vdisc = CGAL::sign(vdisc);

      if(sign_vdisc == NEGATIVE) return res;
      if(sign_vdisc == ZERO) {
	*res++ = std::make_pair
	  ( Root_for_circles_2_2(Root_of_2(vx), 
                                 Root_of_2(e2.b())), 2u);
	return res;
      }
      
      const Root_of_2 x_res = Root_of_2(vx); 
      const Root_of_2 y_res1 = make_root_of_2(e2.b(),FT(-1),vdisc);
      const Root_of_2 y_res2 = make_root_of_2(e2.b(),FT(1),vdisc);

      *res++ = std::make_pair
	( Root_for_circles_2_2(x_res, y_res1), 1u);
      *res++ = std::make_pair
	( Root_for_circles_2_2(x_res, y_res2), 1u);
      return res;
    }
    else {
      
      const FT line_factor = CGAL::square(e1.a()) + CGAL::square(e1.b());
      const FT disc = line_factor*e2.r_sq() -
                      CGAL::square(e1.a()*e2.a() + e1.b()*e2.b() + e1.c());
      CGAL::Sign sign_disc = CGAL::sign(disc);

      if (sign_disc == NEGATIVE) return res;

      const FT aux = e1.b()*e2.a() - e1.a()*e2.b();
      const FT x_base = (aux*e1.b() - e1.a()*e1.c()) / line_factor;
      const FT y_base = (-aux*e1.a() - e1.b()*e1.c()) / line_factor;

      if (sign_disc == ZERO) {
        *res++ = std::make_pair
	  ( Root_for_circles_2_2(Root_of_2(x_base), 
                                 Root_of_2(y_base)), 2u);
	return res;
      }

      // We have two intersection points, whose coordinates are one-root numbers. 
      const FT x_root_coeff = e1.b() / line_factor;
      const FT y_root_coeff = e1.a() / line_factor;

      if (CGAL::sign(e1.b()) == POSITIVE) {
        *res++ = std::make_pair
	( Root_for_circles_2_2(make_root_of_2(x_base, -x_root_coeff, disc), 
                               make_root_of_2(y_base, y_root_coeff, disc)), 1u);
        *res++ = std::make_pair
	( Root_for_circles_2_2(make_root_of_2(x_base, x_root_coeff, disc), 
                               make_root_of_2(y_base, -y_root_coeff, disc)), 1u);
      } else {
        *res++ = std::make_pair
	( Root_for_circles_2_2(make_root_of_2(x_base, x_root_coeff, disc), 
                               make_root_of_2(y_base, -y_root_coeff, disc)), 1u);
        *res++ = std::make_pair
	( Root_for_circles_2_2(make_root_of_2(x_base, -x_root_coeff, disc), 
                               make_root_of_2(y_base, y_root_coeff, disc)), 1u);
      }
      return res;
    }
  }

  template < class AK, class OutputIterator >
  inline 
  OutputIterator
  solve( const typename AK::Polynomial_for_circles_2_2 & e1,
	 const typename AK::Polynomial_1_2 & e2,
	 OutputIterator res )
  {
    return solve<AK> (e2, e1, res);
  }

  template < class AK, class OutputIterator >
  inline 
  OutputIterator
  solve( const typename AK::Polynomial_1_2 & e1,
	 const typename AK::Polynomial_1_2 & e2,
	 OutputIterator res )
  {
    typedef typename AK::FT FT;
    typedef typename AK::Root_of_2 Root_of_2;
    typedef typename AK::Root_for_circles_2_2 Root_for_circles_2_2;
    //parallele case
    const FT delta = e1.a()*e2.b() - e2.a()*e1.b();
    if(is_zero(delta)) return res;
    //case : e2 horizontal
    if(is_zero(e2.a())){
      const FT sol = -e2.c()/e2.b();
      *res++ = std::make_pair
	  ( Root_for_circles_2_2(Root_of_2(-(e1.b()*sol + e1.c())/e1.a()),
                                 Root_of_2(sol)), 1u);
      return res;
    }
    //general case
    const FT sol = (e2.a()*e1.c() - e2.c()*e1.a()) / delta; 
    *res++ = std::make_pair
	  ( Root_for_circles_2_2(Root_of_2(-(e2.b()*sol + e2.c())/e2.a()),
                                 Root_of_2(sol)), 1u);
    return res;
  }

    template < class AK >
    inline 
    Sign sign_at( const typename AK::Polynomial_1_2 & equation,
		  const typename AK::Root_for_circles_2_2 & r)
    {
      typedef typename AK::Root_of_2 Root_of_2;
      Comparison_result c = compare(r.x()*equation.a(), 
                                    -equation.c() - r.y()*equation.b());
      if(c == EQUAL) return ZERO;
      if(c == LARGER) return POSITIVE;
      return NEGATIVE;
    }


  
  } // namespace AlgebraicFunctors
} // namespace CGAL

#endif //  CGAL_ALGEBRAIC_KERNEL_FOR_CIRCLES_FUNCTIONS_ON_ROOTS_AND_POLYNOMIAL_1_2_AND_2_2_H
