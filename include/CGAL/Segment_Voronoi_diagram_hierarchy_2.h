// Copyright (c) 2003,2004  INRIA Sophia-Antipolis (France) and
// Notre Dame University (U.S.A.).  All rights reserved.
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
// $Source: /CVSROOT/CGAL/Packages/Segment_Voronoi_diagram_2/include/CGAL/Segment_Voronoi_diagram_hierarchy_2.h,v $
// $Revision: 1.46 $ $Date: 2004/09/07 17:40:44 $
// $Name:  $
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>



#ifndef CGAL_SEGMENT_VORONOI_DIAGRAM_HIERARCHY_2_H
#define CGAL_SEGMENT_VORONOI_DIAGRAM_HIERARCHY_2_H

#include <map>

#include <CGAL/Segment_Voronoi_diagram_short_names_2.h>

#include <CGAL/Random.h>
#include <CGAL/Segment_Voronoi_diagram_2.h>
#include <CGAL/Triangulation_data_structure_2.h>
#include <CGAL/Segment_Voronoi_diagram_vertex_base_2.h>
#include <CGAL/Segment_Voronoi_diagram_hierarchy_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_2.h>


CGAL_BEGIN_NAMESPACE

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// parameterization of the hierarchy
#ifdef CGAL_SVD_HIERARCHY_DEMO
const unsigned int svd_hierarchy_2__ratio    = 3;
const unsigned int svd_hierarchy_2__minsize  = 5;
#else
const unsigned int svd_hierarchy_2__ratio    = 30;
const unsigned int svd_hierarchy_2__minsize  = 20;
#endif
const unsigned int svd_hierarchy_2__maxlevel = 5;
// maximal number of points is 30^5 = 24 millions !

//--------------------------------------------------------------------
//--------------------------------------------------------------------

template < class Gt, class STag = Tag_false,
	   class DS = Triangulation_data_structure_2<
              Segment_Voronoi_diagram_hierarchy_vertex_base_2<
                 Segment_Voronoi_diagram_vertex_base_2<Gt,
			     typename Gt::Intersections_tag> >,
              Triangulation_face_base_2<Gt> >,
	   class LTag = Tag_false>
class Segment_Voronoi_diagram_hierarchy_2
  : public Segment_Voronoi_diagram_2<Gt,DS,LTag>
{
protected:
  typedef Segment_Voronoi_diagram_hierarchy_2<Gt,STag,DS,LTag>  Self;

public:
  // PUBLIC TYPES
  //-------------
  typedef Segment_Voronoi_diagram_2<Gt,DS,LTag>  Base;

  typedef typename Base::Geom_traits        Geom_traits;

  typedef typename Geom_traits::Point_2     Point_2;
  typedef typename Geom_traits::Site_2      Site_2;

  typedef typename Base::Vertex_handle      Vertex_handle;
  typedef typename Base::Face_handle        Face_handle;
  typedef typename Base::Edge               Edge;

  typedef typename Base::Vertex_circulator         Vertex_circulator;
  typedef typename Base::Edge_circulator           Edge_circulator;
  typedef typename Base::Face_circulator           Face_circulator;

  typedef typename Base::All_faces_iterator        All_faces_iterator;
  typedef typename Base::Finite_faces_iterator     Finite_faces_iterator;
  typedef typename Base::All_vertices_iterator     All_vertices_iterator;
  typedef typename Base::Finite_vertices_iterator  Finite_vertices_iterator;
  typedef typename Base::All_edges_iterator        All_edges_iterator;
  typedef typename Base::Finite_edges_iterator     Finite_edges_iterator;

  typedef typename Base::Input_sites_iterator      Input_sites_iterator;
  typedef typename Base::Output_sites_iterator     Output_sites_iterator;

  typedef typename Base::Point_handle              Point_handle;

protected:
  typedef typename Base::Handle_map                Handle_map;
  typedef typename Base::Point_handle_pair         Point_handle_pair;

public:
  typedef typename Base::Point_container           Point_container;
  typedef typename Base::size_type                 size_type;

  typedef typename Base::Intersections_tag         Intersections_tag;

  typedef STag                            Insert_segments_in_hierarchy_tag;
  typedef STag                            Segments_in_hierarchy_tag;

protected:
  // LOCAL TYPES
  //------------
  typedef typename Base::Storage_site_2            Storage_site_2;
  typedef typename Base::List                      List;
  typedef typename Base::Face_map                  Face_map;
  typedef typename Base::Vertex_triple             Vertex_triple;

  typedef typename Base::Arrangement_type          Arrangement_type;
  typedef typename Base::AT2                       AT2;

protected:
  // LOCAL VARIABLES
  //----------------
  static const int UNDEFINED_LEVEL = -1;

  // here is the stack of triangulations which form the hierarchy
  Base*   hierarchy[svd_hierarchy_2__maxlevel];
  Random random; // random number generator

public:
  // CONSTRUCTORS
  //-------------
  Segment_Voronoi_diagram_hierarchy_2(const Gt& gt = Gt());

  template<class Input_iterator>
  Segment_Voronoi_diagram_hierarchy_2(Input_iterator first,
				      Input_iterator beyond,
				      const Gt& gt=Gt())
    : Base(gt), random((long)0)
  {
    init_hierarchy(gt);
    insert(first, beyond);
  }

  Segment_Voronoi_diagram_hierarchy_2(const Self& svd);
  Self& operator=(const Self& svd);

  // DESTRUCTOR
  //-----------
  ~Segment_Voronoi_diagram_hierarchy_2();

public:
  // ACCESS METHODS
  //---------------
  const Base& diagram(unsigned int i) const  {
    CGAL_precondition( i < svd_hierarchy_2__maxlevel );
    return *hierarchy[i];
  }

public:
  // INSERTION METHODS
  //------------------
  template<class Input_iterator>
  size_type insert(Input_iterator first, Input_iterator beyond) {
    return insert(first, beyond, Tag_false());
  }

  template<class Input_iterator>
  size_type insert(Input_iterator first, Input_iterator beyond,	Tag_true)
  {
    std::vector<Site_2> site_vec;
    for (Input_iterator it = first; it != beyond; ++it) {
      site_vec.push_back(Site_2(*it));
    }
    std::random_shuffle(site_vec.begin(), site_vec.end());
    return insert(site_vec.begin(), site_vec.end(), Tag_false());
  }

  template<class Input_iterator>
  size_type insert(Input_iterator first, Input_iterator beyond,	Tag_false)
  {
    // do it the obvious way: insert them as they come;
    // one might think though that it might be better to first insert
    // all end points and then all segments, or a variation of that.
    size_type n_before = this->number_of_vertices();
    for (Input_iterator it = first; it != beyond; ++it) {
      insert(*it);
    }
    size_type n_after = this->number_of_vertices();
    return n_after - n_before;
  }

  Vertex_handle  insert(const Point_2& p) {
    Point_handle ph = this->register_input_site(p);
    Storage_site_2 ss = Storage_site_2::construct_storage_site_2(ph);
    return insert_point(p, ss, UNDEFINED_LEVEL);
  }

  Vertex_handle  insert(const Point_2& p0, const Point_2& p1) {
    Point_handle_pair php = this->register_input_site(p0,p1);
    Storage_site_2 ss =
      Storage_site_2::construct_storage_site_2(php.first, php.second);
    return insert_segment(p0, p1, ss, UNDEFINED_LEVEL);
  }

  Vertex_handle insert(const Point_2& p, Vertex_handle) {
    return insert(p);
  }

  Vertex_handle insert(const Point_2& p0, const Point_2& p1,
		       Vertex_handle) {
    return insert(p0, p1);
  }

  Vertex_handle  insert(const Site_2& t) {
    // the intended use is to unify the calls to insert(...);
    // thus the site must be an exact one; 
    CGAL_precondition( t.is_input() );

    if ( t.is_segment() ) {
      Point_handle_pair php =
	this->register_input_site(t.source(), t.target());
      Storage_site_2 ss =
	Storage_site_2::construct_storage_site_2(php.first, php.second);
      return insert_segment(t.source(), t.target(), ss, UNDEFINED_LEVEL);
    } else if ( t.is_point() ) {
      Point_handle ph = this->register_input_site( t.point() );
      Storage_site_2 ss = Storage_site_2::construct_storage_site_2(ph);
      return insert_point(t.point(), ss, UNDEFINED_LEVEL);
    } else {
      CGAL_precondition ( t.is_defined() );
      return Vertex_handle(); // to avoid compiler error
    }
  }

  Vertex_handle  insert(const Site_2& t, Vertex_handle) {
    return insert(t);
  }

protected:
  Vertex_handle insert_point(const Point_2& p, const Storage_site_2& ss,
			     int level) {
    if ( level == UNDEFINED_LEVEL ) {
      level = random_level();
    }

    Vertex_handle vertices[svd_hierarchy_2__maxlevel];
  
    insert_point(p, ss, level, vertices);

    return vertices[0];
  }

  void          insert_point(const Point_2& p, const Storage_site_2& ss,
			     int level,	Vertex_handle* vertices);

  void          insert_point(const Site_2& t, const Storage_site_2& ss,
			     int low, int high, Vertex_handle vbelow,
			     Vertex_handle* vertices);

  Vertex_handle insert_segment(const Point_2& p0, const Point_2& p1,
			       const Storage_site_2& ss, int level); 

  Vertex_handle insert_segment_interior(const Site_2& t,
					const Storage_site_2& ss,
					const Vertex_handle* vertices0,
					int level);

  void insert_segment_in_upper_levels(const Site_2& t,
				      const Storage_site_2& ss,
				      Vertex_handle vbelow,
				      const Vertex_handle* vertices0,
				      int level, Tag_true);

  void insert_segment_in_upper_levels(const Site_2& t,
				      const Storage_site_2& ss,
				      Vertex_handle vbelow,
				      const Vertex_handle* vertices,
				      int level, Tag_false) {}

  Vertex_handle insert_segment_on_point(const Storage_site_2& ss,
					const Vertex_handle& v,
					int level, Tag_false stag,
					int which) {
    return Vertex_handle();
  }

  Vertex_handle insert_segment_on_point(const Storage_site_2& ss,
					const Vertex_handle& v,
					int level, Tag_true stag,
					int which);

  template<class Tag>
  Vertex_handle
  insert_intersecting_segment_with_tag(const Storage_site_2& ss,
				       const Site_2& t,
				       Vertex_handle v,
				       int level, Tag_false itag, Tag) {
#if defined(__POWERPC__) && \
  defined(__GNUC__) && (__GNUC__ == 3) && (__GNUC_MINOR__ == 4)
    // hack to avoid nasty warning for G++ 3.4 on Darwin
    static int i;
#else
    static int i = 0;
#endif
    if ( i == 0 ) {
      i = 1;
      print_error_message();
    }
    return Vertex_handle();
  }

  Vertex_handle
  insert_intersecting_segment_with_tag(const Storage_site_2& ss,
				       const Site_2& t,
				       Vertex_handle v,
				       int level,
				       Tag_true itag, Tag_false stag);

  Vertex_handle
  insert_intersecting_segment_with_tag(const Storage_site_2& ss,
				       const Site_2& t,
				       Vertex_handle v,
				       int level,
				       Tag_true itag, Tag_true stag);

public:
  // NEAREST NEIGHBOR LOCATION
  //--------------------------
  Vertex_handle  nearest_neighbor(const Point_2& p,
				  bool force_point = false) const;

  Vertex_handle  nearest_neighbor(const Point_2& p, Vertex_handle)
  {
    return nearest_neighbor(p);
  }

protected:
  void nearest_neighbor(const Site_2& p,
			Vertex_handle vnear[svd_hierarchy_2__maxlevel],
			bool force_point) const; 

public:
  // MISCELLANEOUS
  //--------------
  void init_hierarchy(const Geom_traits& gt);

  void copy(const Segment_Voronoi_diagram_hierarchy_2& svdh);

  void swap(Segment_Voronoi_diagram_hierarchy_2& svdh);
  void clear();

public:
  // VALIDITY CHECK
  //---------------
  bool is_valid(bool verbose = false, int level = 1) const;

protected:
  // LOCAL HELPER METHODS
  //---------------------
  int random_level() {
    unsigned int l = 0;
    while ( true ) {
      if ( random(svd_hierarchy_2__ratio) ) break;
      ++l;
    }
    if (l >= svd_hierarchy_2__maxlevel)
      l = svd_hierarchy_2__maxlevel - 1;
    return l;
  }

  size_type find_level(Vertex_handle v) const {
    CGAL_precondition( v != Vertex_handle() );
    size_type level = 0;
    Vertex_handle vertex = v;
    while ( vertex->up() != Vertex_handle() ) {
      vertex = vertex->up();
      level++;
    }

    return level;
  }

  Vertex_handle
  vertex_at_level(const Vertex_handle& v, size_type k) const
  {
    CGAL_precondition( k <= svd_hierarchy_2__maxlevel );

    size_type level = 0;
    Vertex_handle v_at_level = v;
    while ( level < k ) {
      v_at_level = v_at_level->up();
      level++;
    }
    return v_at_level;
  }

  void print_error_message() const;
};


CGAL_END_NAMESPACE



#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#  include <CGAL/Segment_Voronoi_diagram_hierarchy_2.C>
#endif

#endif // CGAL_SEGMENT_VORONOI_DIAGRAM_HIERARCHY_2_H

