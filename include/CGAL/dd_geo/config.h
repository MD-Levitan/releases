// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/dd_geo/config.h
// package       : Convex_hull_3 (2.6)
// source        : LEP dd_geo_kernel
// revision      : 2.1.2
// revision_date : 09 Jul 1998
// author(s)     : Kurt Mehlhorn
//                 Michael Seel
//                 Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
/*******************************************************************************
+
+  LEP dd_geokernel 2.1
+
+  This file is part of the research version of a LEDA extension package,
+  that can be used free of charge in academic research and teaching. 
+  Any commercial use of this software requires a commercial license,
+  which is distributed by the Algorithmic Solutions GmbH, 
+  Postfach 151101, 66041 Saarbruecken, FRG (fax +49 681 31104).
+
+  Copyright (c) 1997-1998  by  Max-Planck-Institut fuer Informatik
+  Im Stadtwald, 66123 Saarbruecken, Germany     
+  All rights reserved.
+ 
*******************************************************************************/

#ifndef CGAL_DD_GEO_CONFIG_H
#define CGAL_DD_GEO_CONFIG_H

// #ifndef __SUNPRO_CC              /* !!! should not be compiler-dependent !!! */
// #define DDGEO_STL_ITERATORS
// #endif // __SUNPRO_CC

#if ( __LEDA__ < 380 )
#define LEDA_PREFIXLI
#else
#define LEDA_PREFIXLI  LEDA::
#endif 

#if !defined(LEP_DDGEO_INCL_ID)
#define LEDA_ROOT_INCL_ID NOT_ANY_KERNEL_NUMBER
#define LEP_DDGEO_INCL_ID 21027
#include <LEDA/REDEFINE_NAMES.h>
#endif


#ifndef CGAL_CFG_NO_TEMPLATE_FRIEND_DISTINCTION
#define EGCSNTA <>
#else
#define EGCSNTA
#endif


#ifndef CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS
#define CHSIMPLEX  ch_simplex
#define DTVERTEX   dt_vertex
#else
#define CHSIMPLEX  ch_Simplex<CHTRAITS,POINT,PLANE>*
#define DTVERTEX   rc_Vertex<CHTRAITS,LPNT>*
#endif // CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS


#ifndef CGAL_CFG_NO_DEFAULT_TEMPLATE_ARGUMENTS
#define DDGEO_TEMPLATE_DEFAULTS
#endif // CGAL_CFG_NO_DEFAULT_TEMPLATE_ARGUMENTS



#if LEP_DDGEO_INCL_ID == 21027
#undef LEDA_ROOT_INCL_ID
#undef LEP_DDGEO_INCL_ID
#include <LEDA/UNDEFINE_NAMES.h>
#endif

#endif // CGAL_DD_GEO_CONFIG_H
