// Copyright (c) 2003,2004,2005  INRIA Sophia-Antipolis (France) and
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Segment_Delaunay_graph_2/include/CGAL/Segment_Delaunay_graph_2/edge_list.h $
// $Id: edge_list.h 28567 2006-02-16 14:30:13Z lsaboret $
// 
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>

#ifndef CGAL_SEGMENT_DELAUNAY_GRAPH_2_EDGE_LIST_H
#define CGAL_SEGMENT_DELAUNAY_GRAPH_2_EDGE_LIST_H


#include <CGAL/Unique_hash_map.h>
#include <CGAL/Edge_hash_function.h>
#include <CGAL/circulator_bases.h>

CGAL_BEGIN_NAMESPACE


namespace CGALi {

  template<class Edge_t>
  class Edge_list_item
  {
  public:
    typedef Edge_t                      Edge;

  private:
    typedef typename Edge::first_type   Face_handle;

  private:
    Edge prev_;
    Edge next_;

  public:
    // remove the following method and make SENTINEL_EDGE a static const
    // member of the class.
    static const Edge& sentinel_edge() {
      static Edge SENTINEL_EDGE = Edge(Face_handle(), sentinel_index());
      return SENTINEL_EDGE;
    }

  private:
    static int sentinel_index() { return -1; }

  public:
    Edge_list_item()
      : prev_(sentinel_edge()), next_(sentinel_edge()) {}
    Edge_list_item(const Edge& prev, const Edge& next)
      : prev_(prev), next_(next) {}


    bool is_in_list() const
    {
      return ( next_.second != sentinel_index() ||
	       prev_.second != sentinel_index() );
    }

    void set_next(const Edge& next)
    {
      next_ = next;
    }

    void set_previous(const Edge& prev)
    {
      prev_ = prev;
    }

    const Edge& next()     const { return next_; }
    const Edge& previous() const { return prev_; }

    void reset() {
      Edge SENTINEL_EDGE = sentinel_edge();
      next_ = prev_ = SENTINEL_EDGE;
    }
  };


  
  template<class E_t, class ListItem, class USE_STL_MAP_Tag>
  struct Edge_list_which_map;

  // use STL's map
  template<class E_t, class ListItem>
  struct Edge_list_which_map<E_t,ListItem,Tag_true>
  {
    typedef E_t                       Edge;
    typedef ListItem                  List_item;
    typedef std::map<Edge,List_item>  Edge_map;
  };

  // use CGAL's Unique_hash_map
  template<class E_t, class ListItem>
  struct Edge_list_which_map<E_t,ListItem,Tag_false>
  {
    typedef E_t                         Edge;
    typedef ListItem                    List_item;
    typedef CGAL::Edge_hash_function    Hash_function;

    typedef Unique_hash_map<Edge,List_item,Hash_function>  Edge_map;
  };


  template<class Edge_list_t>
  class Edge_list_circulator
    : public CGAL::Bidirectional_circulator_base<typename Edge_list_t::Edge>
  {
  private:
    typedef Edge_list_t                                 List;
    typedef typename List::Edge                         Edge;
    typedef Edge_list_item<Edge>                        List_item;
    typedef CGAL::Bidirectional_circulator_base<Edge>   Base;

    typedef Edge_list_circulator<List>                  Self;

  public:
    Edge_list_circulator()
      : l_(NULL), c_(List_item::sentinel_edge()) {}

    Edge_list_circulator(const List* l, const Edge& c)
      : l_(l), c_(/*const_cast<Edge&>(*/c/*)*/) {}

    Edge_list_circulator(const Edge_list_circulator& other)
      : l_(other.l_), c_(other.c_) {}

    Edge_list_circulator& operator=(const Edge_list_circulator& other) {
      l_ = other.l_;
      c_ = other.c_;
      return *this;
    }

    Self& operator++() {
      CGAL_precondition( l_ != NULL );
      //      c_ = const_cast<Edge&>(l_->next(c_));
      c_ = l_->next(c_);
      return *this;
    }

    Self& operator--() {
      CGAL_precondition( l_ != NULL );
      //      c_ = const_cast<Edge&>(l_->previous(c_));
      c_ = l_->previous(c_);
      return *this;
    }

    Self operator++(int) {
      Self tmp(*this);
      ++tmp;
      return tmp;
    }

    Self operator--(int) {
      Self tmp(*this);
      --tmp;
      return tmp;
    }

    typename Base::pointer   operator->() { return &c_; }
    typename Base::reference operator*() { return c_; }

    bool operator==(const Self& other) const {
      return l_ == other.l_ && c_ == other.c_;
    }

    bool operator!=(const Self& other) const {
      return l_ != other.l_ || c_ != other.c_;
    }

  protected:
    const List* l_;
    //    Edge& c_;
    Edge c_;
  };


} // namespace CGALi



template<class Edge_t, class USE_STL_MAP_Tag = Tag_true>
class Edge_list
{
public:
  // TYPES
  //======
  typedef std::size_t       size_type;
  typedef Edge_t            Edge;
  typedef USE_STL_MAP_Tag   Use_stl_map_tag;

private:
  typedef CGALi::Edge_list_item<Edge>  List_item;

  typedef
  CGALi::Edge_list_which_map<Edge,List_item,Use_stl_map_tag>
  Which_map;

  typedef typename Which_map::Edge_map  Edge_map;

  typedef Edge_list<Edge,Use_stl_map_tag>  Self;

public:
  typedef CGALi::Edge_list_circulator<Self>  circulator;

private:
  // PRIVATE DATA MEMBERS
  //=====================
  Edge_map             emap;
  Edge                 front_;
  size_type            size_;

private:
  // PRIVATE METHODS
  //================
  void increase_size() {
    size_++;
  }

  void decrease_size() {
    size_--;
  }

  void insert_before_nocheck(const Edge& e, const Edge& new_e) {
    List_item& li_e = emap[e];

    const Edge& prev_e = li_e.previous();
    List_item& li_prev_e = emap[prev_e];

    emap[new_e] = List_item(prev_e, e);
    li_e.set_previous(new_e);
    li_prev_e.set_next(new_e);
    increase_size();
  }

  // check whether the edge is in the list;
  // the map used is STL's map 
  bool is_in_list_with_tag(const Edge& e, const Tag_true&) const
  {
    if ( emap.find(e) == emap.end() ) { return false; }
    return emap.find(e)->second.is_in_list();    
  }

  // check whether the edge is in the list;
  // the map used is CGAL's Unique_hash_map 
  bool is_in_list_with_tag(const Edge& e, const Tag_false&) const
  {
    if ( !emap.is_defined(e) ) { return false; }
    return emap[e].is_in_list();
  }

  // return the next edge in the list;
  // the map used is STL's map 
  const Edge& next_with_tag(const Edge& e, const Tag_true&) const
  {
    return emap.find(e)->second.next();
  }

  // return the next edge in the list;
  // the map used is CGAL's Unique_hash_map 
  const Edge& next_with_tag(const Edge& e, const Tag_false&) const
  {
    return emap[e].next();
  }

  // return the previous edge in the list;
  // the map used is STL's map 
  const Edge& previous_with_tag(const Edge& e, const Tag_true&) const
  {
    return emap.find(e)->second.previous();
  }

  // return the previous edge in the list;
  // the map used is CGAL's Unique_hash_map 
  const Edge& previous_with_tag(const Edge& e, const Tag_false&) const
  {
    return emap[e].previous();
  }

public:
  // CONSTRUCTOR
  //============
#ifdef _MSC_VER
  Edge_list(const Edge& e = Edge(typename Edge::first_type(),-1) )
    : emap(), front_(e), size_(0) {}
#else
  Edge_list(const Edge& e = List_item::sentinel_edge() )
    : emap(), front_(e), size_(0) {}
#endif

  // PREDICATES
  //===========
  bool is_valid() const { return true; }

  bool is_in_list(const Edge& e) const {
    static Use_stl_map_tag  map_tag;
    return is_in_list_with_tag(e, map_tag);
  }


  // ACCESS METHODS
  //===============
  size_type size() const {
    return size_;
  }

  const Edge& next(const Edge& e) const {
    CGAL_precondition( is_in_list(e) );
    static Use_stl_map_tag  map_tag;
    return next_with_tag(e, map_tag);
  }

  const Edge& previous(const Edge& e) const {
    CGAL_precondition( is_in_list(e) );
    static Use_stl_map_tag  map_tag;
    return previous_with_tag(e, map_tag);
  }

  const Edge& front() const {
    CGAL_precondition( size() > 0 );
    return front_;
  }

  const Edge& back() const {
    CGAL_precondition( size() > 0 );
    return previous(front_);
  }


  // INSERTION
  //==========
  void push_front(const Edge& e) {
    push_back(e);
    front_ = e;
  }

  void push_back(const Edge& e) {
    CGAL_precondition( !is_in_list(e) );

    if ( size() == 0 ) {
      emap[e] = List_item(e,e);
      front_ = e;
      increase_size();
      return;
    }

    insert_before_nocheck(front_, e);
  }

  void insert_after(const Edge& e, const Edge& new_e) {
    CGAL_precondition( is_in_list(e) );
    CGAL_precondition( !is_in_list(new_e) );

    List_item& li_e = emap[e];

    const Edge& next_e = li_e.next();
    List_item& li_next_e = emap[next_e];

    emap[new_e] = List_item(e, next_e);
    li_e.set_next(new_e);
    li_next_e.set_previous(new_e);
    increase_size();
  }

  void insert_before(const Edge& e, const Edge& new_e) {
    CGAL_precondition( is_in_list(e) );
    CGAL_precondition( !is_in_list(new_e) );
    insert_before_nocheck(e, new_e);
  }


  // REPLACEMENT
  //============
  void replace(const Edge& e, const Edge& new_e) {
    CGAL_precondition( is_in_list(e) );
    CGAL_precondition( !is_in_list(new_e) );

    List_item& li_e = emap[e];

    if ( size() == 1 ) {
      emap[new_e] = List_item(new_e, new_e);
      front_ = new_e;
      li_e.reset();
    }

    const Edge& next_e = li_e.next();
    const Edge& prev_e = li_e.previous();

    emap[prev_e].set_next(new_e);
    emap[next_e].set_previous(new_e);

    emap[new_e] = List_item(prev_e, next_e);

    li_e.reset();

    if ( e == front_ ) {
      front_ = new_e;
    }
  }


  // REMOVAL
  //========

  void remove(const Edge& e) {
    CGAL_precondition( is_in_list(e) );

    if ( size() == 1 ) {
      front_ = List_item::sentinel_edge();
      emap[e].reset();
      decrease_size();
      return;
    }

    List_item& li_e = emap[e];
    const Edge& next_e = li_e.next();
    const Edge& prev_e = li_e.previous();

    emap[prev_e].set_next(next_e);
    emap[next_e].set_previous(prev_e);

    if ( e == front_ ) {
      //      front_ = next_e;
      front_ = next_e;
    }

    li_e.reset();

    decrease_size();
  }

#if 0
  // ACCESS TO CIRCULATOR
  //=====================
  inline circulator start() const {
    return start(front());
  }

  inline circulator start(const Edge& start) const {
    CGAL_precondition( is_in_list(start) );
    return circulator(this, start);
  }
#endif

  // MISCELLANEOUS
  //==============
  void clear() {
    emap.clear();
  }
};

CGAL_END_NAMESPACE


#endif // CGAL_SEGMENT_DELAUNAY_GRAPH_2_EDGE_LIST_H