// Copyright (c) 2007  GeometryFactory (France).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/BGL/include/CGAL/Triangulation_vertex_base_with_id_2.h $
// $Id: Triangulation_vertex_base_with_id_2.h 36383 2007-02-16 11:34:18Z afabri $
// 
//
// Author(s)     : Andreas Fabri, Fernando Cacciola

#ifndef CGAL_TRIANGULATION_VERTEX_BASE_WITH_ID_2_H
#define CGAL_TRIANGULATION_VERTEX_BASE_WITH_ID_2_H

#include <CGAL/Triangulation_vertex_base_2.h>

CGAL_BEGIN_NAMESPACE

template < typename GT,
           typename Vb = Triangulation_vertex_base_2<GT> >
class Triangulation_vertex_base_with_id_2
  : public Vb
{
  int _id;

public:
  typedef typename Vb::Face_handle                   Face_handle;
  typedef typename Vb::Point                         Point;

  template < typename TDS2 >
  struct Rebind_TDS {
    typedef typename Vb::template Rebind_TDS<TDS2>::Other          Vb2;
    typedef Triangulation_vertex_base_with_id_2<GT, Vb2>   Other;
  };

  Triangulation_vertex_base_with_id_2()
    : Vb() {}

  Triangulation_vertex_base_with_id_2(const Point & p)
    : Vb(p) {}

  Triangulation_vertex_base_with_id_2(const Point & p, Face_handle c)
    : Vb(p, c) {}

  Triangulation_vertex_base_with_id_2(Face_handle c)
    : Vb(c) {}

  int id() const { return _id; }
  int&       id()       { return _id; }
};

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_VERTEX_BASE_WITH_ID_2_H