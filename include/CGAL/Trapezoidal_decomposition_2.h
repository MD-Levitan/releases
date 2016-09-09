// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Trapezoidal_decomposition_2.h
// package       : Trapezoidal_decomposition (1.26)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Oren Nechushtan
//                 Iddo Hanniel
//
// maintainer(s) : Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_TRAPEZOIDAL_DECOMPOSITION_2_H
#define CGAL_TRAPEZOIDAL_DECOMPOSITION_2_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <ctime>
#include <list>
#include <vector>
#include <map>

#include <CGAL/Trapezoidal_decomposition_2/Trapezoidal_decomposition_2_misc.h>
#include <CGAL/Trapezoidal_decomposition_2/Td_predicates.h>

CGAL_BEGIN_NAMESPACE

/* //////////////////////////////////////////////////////////////////////////

  class         Trapezoidal_decomposition_2
  parameters    Traits,X_curve
  Description   Implementation for a planar trapezoidal map also known as
  trapezoidal decomposition and vertical decomposition.
  
  For requirements on Traits and X_curve classes see 
  Trapezoidal_decomposition_2 documentation.

////////////////////////////////////////////////////////////////////////// */

template < class Td_traits>
class Trapezoidal_decomposition_2
{
public:
  enum Locate_type {POINT=0,CURVE,TRAPEZOID,UNBOUNDED_TRAPEZOID=8} ;
  class Base_trapezoid_iterator;
  class In_face_iterator;
  friend class In_face_iterator;
  class Around_point_circulator;
  struct Unbounded {};
  typedef Td_traits Traits;
  typedef Trapezoidal_decomposition_2<Traits> Self;
  typedef typename Traits::Point Point;
  typedef typename Traits::X_curve X_curve;
  typedef typename Traits::X_curve_ptr curve_pointer;
  typedef typename Traits::X_curve_ref curve_ref;
  typedef typename Traits::X_curve_const_ref curve_const_ref;
  typedef typename Traits::X_trapezoid X_trapezoid;
  typedef typename Traits::X_trapezoid_ptr pointer;
  typedef typename Traits::X_trapezoid_ref reference;
  typedef typename Traits::X_trapezoid_const_ref const_ref;
  typedef std::list<X_trapezoid> list_container;
  typedef std::vector<X_trapezoid> vector_container;
  typedef std::vector<X_curve> X_curve_container;
  typedef In_face_iterator Iterator;
  typedef class Base_trapezoid_iterator Base_trapezoid_circulator;
  // friend class Td_traits::X_trapezoid;
  
  typedef Td_active_trapezoid<X_trapezoid> Active_trapezoid;
  typedef Td_active_non_degenerate_trapezoid<X_trapezoid,Traits> 
  Active_non_degenerate_trapezoid;
  typedef Td_active_right_degenerate_curve_trapezoid<X_trapezoid,Traits> 
  Active_right_degenerate_curve_trapezoid;
  typedef Td_dag< X_trapezoid> Data_structure;
  typedef std::map<int,Data_structure> map_nodes;
  
  /* ///////////////////////////////////////////////////////////////////////
   
     class Base_trapezoid_iterator
     member of Trapezoidal_decomposition_2<Traits>
     Description Implements a basic Trapezoid iterator
    
     /////////////////////////////////////////////////////////////////////// */
  
  class Base_trapezoid_iterator
  {
  public:
    Base_trapezoid_iterator() : traits(0),curr(0) {};
    Base_trapezoid_iterator(Traits* traits_,pointer currt=0):
      traits(traits_),curr(currt) {}
    Base_trapezoid_iterator(const Base_trapezoid_iterator &it):
      traits(it.traits),curr(it.curr){;}
    Base_trapezoid_iterator  & operator=(const Base_trapezoid_iterator &it)
    {
      traits=it.traits;
      curr=it.curr;
      return *this;
    }
    bool operator==(const Base_trapezoid_iterator &it) const
    {
      return (curr==it.curr );
    }
    bool operator!=(const Base_trapezoid_iterator &it) const
    {
      return !operator==(it);
    }
    reference operator*() const
    {
      CGAL_precondition(curr);
      
      return *curr;
    }
    pointer operator->() const
    {
      return curr;
    }
    bool operator!() const
    {
      return curr==0;
    }
    
  protected:
    Traits* traits;
    pointer curr;
  };

  /* *********************************************************************
     
     class In_face_iterator
     member of Trapezoidal_decomposition_2<Traits>
     Description Implements a Trapezoid iterator along a X_curve
     
     ********************************************************************* */
  
  class In_face_iterator : public Base_trapezoid_iterator
  {
  protected:
    const X_curve& sep;
  public:
    
    In_face_iterator(Traits* traits_,const X_curve& sepc,pointer currt=0) :
      Base_trapezoid_iterator(traits_,currt),sep(sepc){}
    In_face_iterator(const In_face_iterator &it) :
      Base_trapezoid_iterator((Base_trapezoid_iterator&)it),sep(it.sep){}
    bool operator==(const In_face_iterator &it) const
    {
      return ( Base_trapezoid_iterator::operator==(it) && 
               traits->curve_is_same(sep,it.sep) );
    }
    
    /*
      destription:
      advances curr to one of the right neighbours according to the relation
      between the seperating X_curve and the right() trapezoid point.
      precoditions:
      sep doesn't intersect no existing edges except possibly on common end
      points.
      postconditions:
      if the rightest trapezoid was traversed curr is set to NULL.
      remark:
      if the seperator is vertical, using the precondition assumptions it
      follows that
      there is exactly one trapezoid to travel.
    */
    In_face_iterator& operator++()
    {
      if (!curr) return *this;// end reached, do nothing!
      
#ifndef CGAL_TD_DEBUG
      
      CGAL_warning(traits);
      
#else
      
      CGAL_assertion(traits);
      
#endif
      
      Point right(curr->right());
      
#ifdef CGAL_TD_DEBUG
      
      CGAL_assertion(curr->is_active());
      CGAL_assertion(!traits->is_degenerate_point(*curr));
      
#endif
      if (!traits->is_degenerate(*curr))
      {
        Data_structure* tt=curr->get_node();
          
#ifndef CGAL_TD_DEBUG
          
        CGAL_warning(!tt->is_inner_node());
          
#else
          
        CGAL_assertion(tt);
        CGAL_assertion(!tt->is_inner_node());
          
#endif
          
        // handle degeneracies
        if (!traits->point_is_left_low(curr->left(),
                                       traits->curve_righttop_most(sep)))
          curr=0;
        else
        {
          switch(traits->curve_get_point_status(sep,right))
          {
            case Traits::UNDER_CURVE:
              curr=curr->right_top_neighbour();
              break;
            case Traits::ABOVE_CURVE:
              curr=curr->right_bottom_neighbour();
              break;
            case Traits::ON_CURVE:
              // end reached
              curr=0;
              break;
            default:
#ifndef CGAL_TD_DEBUG
                  
              std::cout <<
                "\nmake sure input intersects only on common end points";
              CGAL_warning(traits->curve_get_point_status(sep,curr->right()) ==
                           Traits::UNDER_CURVE ||
                           traits->curve_get_point_status(sep,curr->right()) ==
                           Traits::ABOVE_CURVE ||
                           traits->curve_get_point_status(sep,curr->right()) ==
                           Traits::ON_CURVE);
                  
#else
              std::cout << "\nsep==" << sep << std::flush;
              std::cout << "\ncurr->right()==" << curr->right() << std::flush;
              std::cout <<
                "\nmake sure input intersects only on common end points";
              CGAL_assertion(traits->curve_get_point_status(sep,curr->right())
                             == Traits::UNDER_CURVE ||
                             traits->curve_get_point_status(sep,curr->right())
                             == Traits::ABOVE_CURVE ||
                             traits->curve_get_point_status(sep,curr->right())
                             == Traits::ON_CURVE);
                  
#endif
                  
              curr=0;
              break;
          }
        }
      }
      else // pass along degenerate X_curve.
      {
          
#ifndef CGAL_TD_DEBUG
          
        Data_structure* tt=curr->get_node();
        CGAL_warning(tt);
        CGAL_warning(tt->is_inner_node());
          
#else
          
        Data_structure* tt=curr->get_node();
        CGAL_assertion(tt);
        CGAL_assertion(tt->is_inner_node());
          
#endif
          
        curr=curr->right_bottom_neighbour();
        if (curr)
        {
          while(traits->is_degenerate_point(*curr))
            curr=curr->get_node()->left().operator->();
              
#ifndef CGAL_TD_DEBUG
              
          CGAL_warning(traits->is_degenerate_curve(*curr));
              
#else
              
          CGAL_precondition(traits->is_degenerate_curve(*curr));
              
#endif
              
        }
      }
      return *this;
    }
    
    In_face_iterator operator++(int)
    {
      In_face_iterator tmp = *this;
      ++*this;
      return tmp;
    }
    const X_curve& seperator()
    {
      return sep;
    }
  };
  
  /* //////////////////////////////////////////////////////////////////////////
     
     class Around_point_circulator
     member of Trapezoidal_decomposition_2<Traits>
     Description Implements a Trapezoid circulator around a point
     
    /////////////////////////////////////////////////////////////////////// */
  
  class Around_point_circulator : public Base_trapezoid_circulator
  {
  protected:
    const Point& fixed;
  public:
    
    Around_point_circulator(Traits * traits_, const Point & fixedp,
                            pointer currt) :
      Base_trapezoid_iterator(traits_,currt),fixed(fixedp) {};
    
    Around_point_circulator(const Around_point_circulator &it) :
      Base_trapezoid_iterator(it),fixed(it.fixed){};
    
    Around_point_circulator &operator++()
    {
      if (operator!()) return *this;
      
#ifndef CGAL_TD_DEBUG
      
      CGAL_warning(!curr->is_left_unbounded() &&
                   traits->point_is_same(fixed,curr->left()) ||
                   !curr->is_right_unbounded() &&
                   traits->point_is_same(fixed,curr->right()));
      
#else
      
      CGAL_precondition(!curr->is_left_unbounded() &&
                        traits->point_is_same(fixed,curr->left()) ||
                        !curr->is_right_unbounded() &&
                        traits->point_is_same(fixed,curr->right()));
      
#endif
      
      curr=operator->();
      return *this;
    }
    Around_point_circulator operator++(int)
    {
      Around_point_circulator tmp = *this;
      ++*this;
      return tmp;
    }
    pointer operator[](int i) const
    {
      Around_point_circulator c=*this;
      while(i-->0) c++;
      return c.curr;
    }
    /* returns reference to the next trapezoid
       on a clockwise orientation rotation with centre
       taken as the fixed point
       preconditions:
       ciruclator is not empty*/
    reference operator*() const
    {
      
      CGAL_precondition(!operator!());
      return *operator->();
    }
    /* returns pointer to the next trapezoid
       on a clockwise orientation rotation with centre
       taken as the fixed point */
    pointer operator->() const
    {
      pointer cand;
      if (operator!()) return curr;
      cand=is_right_rotation() ? 
        curr->right_top_neighbour() : curr->left_bottom_neighbour();
      if (traits->is_degenerate_curve(*cand)) return cand;
      // cand was splited by a point
      while(traits->is_degenerate_point(*cand))
        cand=traits->point_is_left_low(cand->left(),fixed)?
          // move right using data structure
          cand->get_node()->right().operator->():
          // move left using data structure
          cand->get_node()->left().operator->();
      return cand;
    }
    bool is_valid() const
    {
      return
        (!curr)||(!curr->is_left_unbounded() &&
                  traits->point_is_same(fixed,curr->left())) ||
        (!curr->is_right_unbounded() &&
         traits->point_is_same(fixed,curr->right()));
    }
    
    /* description:
       inserts the input trapezoid between the
       current trapezoid and the next trapezoid
       on a clockwise orientation rotation with
       centre taken as the fixed point.
       preconditions:
       current trapezoid exist
       input trapezoid is adjacent to fixed point
    */
    void insert(reference tr)
    {
      
#ifndef CGAL_TD_DEBUG
      
      CGAL_precondition(curr);
      CGAL_warning(!tr.is_left_unbounded() && traits->point_is_same(tr.left(),
                                                                    fixed) ||
                   !tr.is_right_unbounded()&& traits->point_is_same(tr.right(),
                                                                    fixed));
      
#else
      
      CGAL_precondition(curr);
      CGAL_precondition(!tr.is_left_unbounded() &&
                        traits->point_is_same(tr.left(),fixed) ||
                        !tr.is_right_unbounded() &&
                        traits->point_is_same(tr.right(),fixed));
      
#endif
      
      if (!tr.is_left_unbounded()&&traits->point_is_same(tr.left(),fixed))
        tr.set_lb(operator->());
      else
        tr.set_rt(operator->());
      if (is_right_rotation())
        curr->set_rt(&tr);
      else
        curr->set_lb(&tr);
    }
    /* precondition:
       curr!=NULL
    */
    void remove()
    {
      
#ifndef CGAL_TD_DEBUG
      
      CGAL_precondition(curr);
      CGAL_warning(!curr->is_left_unbounded() &&
                   traits->point_is_same(curr->left(), fixed) ||
                   !curr->is_right_unbounded() &&
                   traits->point_is_same(curr->right(), fixed));
      
#else
      
      CGAL_precondition(curr);
      CGAL_warning(!curr->is_left_unbounded() &&
                   traits->point_is_same(curr->left(),fixed) ||
                   !curr->is_right_unbounded() &&
                   traits->point_is_same(curr->right(),fixed));
      
#endif
      
      Around_point_circulator old=*this;
      old++;
      pointer next=old.operator->();
      // handle 1-cycle and 2-cycles seperately
      if (curr!=next)
      {
      }
      // 2-cycle
      else if (*this!=old)
      {
        next=curr;
      }
      // 1-cycle
      else
      {
        if (is_right_rotation())
          curr->set_rt(0);
        else
          curr->set_lb(0);
        curr=0;
        return;
      }
      if (is_right_rotation())
        curr->set_rt(next);
      else
        curr->set_lb(next);
      if (old.is_right_rotation())
        old[0]->set_rt(0);
      else
        old[0]->set_lb(0);
    }
    void replace(reference tr)
    {
      
#ifndef CGAL_TD_DEBUG
      
      CGAL_precondition(curr);
      CGAL_warning(!curr->is_left_unbounded() &&
                   traits->point_is_same(curr->left(),fixed) ||
                   !curr->is_right_unbounded() &&
                   traits->point_is_same(curr->right(),fixed));
      
#else
      
      CGAL_precondition(curr);
      CGAL_precondition(!curr->is_left_unbounded() &&
                        traits->point_is_same(curr->left(),fixed) ||
                        !curr->is_right_unbounded() &&
                        traits->point_is_same(curr->right(),fixed));
      
#endif
      
      Around_point_circulator old=*this;
      old++;
      pointer next=old.operator->();
      // handle 1-cycle and 2-cycles seperately
      if (curr!=next)
        {
        }
      // 2-cycle
      else if (*this!=old)
        {
          next=curr;
        }
      // 1-cycle
      else
        {
          curr=&tr;
          if (is_right_rotation())
            curr->set_rt(curr);
          else
            curr->set_lb(curr);
          return;
        }
      if (!tr.is_right_unbounded()&&traits->point_is_same(tr.right(),fixed))
        tr.set_rt(next);
      else
        tr.set_lb(next);
      if (is_right_rotation())
        curr->set_rt(&tr);
      else
        curr->set_lb(&tr);
    }
    bool is_right_rotation() const
    {
      return !curr->is_right_unbounded() &&
          traits->point_is_same(curr->right(),fixed);
    }
    const Point& fixed_point() const
    {
      return fixed;
    }
  };
  //////////////////////////////////////////////
  //Trapezoidal_decomposition_2 member functions:
  //////////////////////////////////////////////
  
#ifndef CGAL_TD_DEBUG
  
protected:

#else

public:

#endif

/* input: X_curve,
two Trapezoidal maps that corespond the the
X_curve's source degenerate trapezoid and the
X_curve's target degenerate trapezoid
output: trapezoid iterator

 Description:
 the output (trapezoid iterator) is initialized with 
 the leftmost and rightmost
 (non degenerate) trapezoids in the trapezoid interval that corresponds 
 to the input from either the top side or the bottom side, 
 depending on the up flag.
 preconditions:
 There exist non degenerate trapezoids between the roots of the input DS's
*/
  In_face_iterator follow_curve(const Data_structure& left_end_point,
                                const X_curve& cv,
                                Comparison_result up) const
  {

#ifndef CGAL_TD_DEBUG

    CGAL_warning(traits);
    CGAL_warning(traits->is_degenerate_point(*left_end_point));
    if (!(traits->point_is_same(traits->curve_leftlow_most(cv),
                                left_end_point->left())))
    {
      CGAL_warning(traits->point_is_same(traits->curve_leftlow_most(cv),
                                         left_end_point->left()));
    }
    
#else
    
    CGAL_assertion(traits);
    CGAL_precondition(traits->is_degenerate_point(*left_end_point));
    CGAL_precondition(traits->point_is_same(traits->curve_leftlow_most(cv),
                                            left_end_point->left()));
    
#endif
    
    const Point& p1=left_end_point->left();
    Data_structure left=left_end_point.right();
    search_using_data_structure(left,traits,p1,&cv,up);
    return In_face_iterator(traits,cv,left.operator->());
  }
  
  /*
  input:
  X_trapezoid reference
  X_trapezoid pointer
  output:
  bool
  preconditions:
  the referenced trapezoid is to the right of the pointered trapezoid
  description:
  if the two input Trapezoids can be merged they are ,
  with one copy destroyed(the right one).
  postconfition:
  The reference points to the right trapezoid
  The returned value is true iff merging took place.
  */
  bool merge_if_possible(pointer left,pointer right)
  {
    if (left && right &&
    traits->trapezoid_top_curve_is_same(*left,*right) &&
    traits->trapezoid_bottom_curve_is_same(*left,*right) &&
      traits->point_is_same(left->right(),right->left()))
    {
      left->merge_trapezoid(*right);

#ifdef CGAL_TD_DEBUG
      CGAL_assertion(left->is_right_unbounded()==right->is_right_unbounded());
#endif

      return true;
    }
    return false;
  }
  
  /* Description:
  splits the trapezoid with vertical line through p */
  /* Precondition:
  The trapezoid is active and contains p in its closure */
  
  Data_structure& split_trapezoid_by_point(
    Data_structure& tt,
    const Point& p,
    const X_curve& cv_bottom_ray_shoot,
    const X_curve& cv_top_ray_shoot
    )
  {
    
#ifndef CGAL_TD_DEBUG
    
    CGAL_warning(!!tt);
    if (!tt)  return tt;
    
#else
    
    CGAL_precondition(!!tt);
    
#endif
    
    reference curr=*tt;
    pointer
      lb=curr.left_bottom_neighbour(),
      lt=curr.left_top_neighbour(),
      rb=curr.right_bottom_neighbour(),
      rt=curr.right_top_neighbour();
    
#ifndef CGAL_TD_DEBUG
    CGAL_warning(curr.is_active());
    CGAL_warning(traits->is_in_closure(curr,p));
#else
    CGAL_precondition(curr.is_active());
    if (!traits->is_in_closure(curr,p))
    {
      std::cout << "\ncurr=";
      write(std::cout,curr,*traits) << "\tp=" << p;
    }
    CGAL_precondition(traits->is_in_closure(curr,p));
#endif
    
    // left and right are set to the point itself,
    // bottom and top are set to the ray shooting resulting curves at this
    // stage.
    X_trapezoid sep(p,p,cv_bottom_ray_shoot,cv_top_ray_shoot);
    Data_structure leftDS = Data_structure(X_trapezoid(curr.left(), p,
                                                       curr.bottom(),
                                                       curr.top(),
      curr.boundedness() & (CGAL_TRAPEZOIDAL_DECOMPOSITION_2_LEFT_UNBOUNDED |
                            CGAL_TRAPEZOIDAL_DECOMPOSITION_2_BOTTOM_UNBOUNDED |
                            CGAL_TRAPEZOIDAL_DECOMPOSITION_2_TOP_UNBOUNDED)
      ));
    Data_structure rightDS=Data_structure(X_trapezoid(p, curr.right(),
                                                      curr.bottom(),curr.top(),
      curr.boundedness()&(CGAL_TRAPEZOIDAL_DECOMPOSITION_2_RIGHT_UNBOUNDED |
                          CGAL_TRAPEZOIDAL_DECOMPOSITION_2_BOTTOM_UNBOUNDED |
                          CGAL_TRAPEZOIDAL_DECOMPOSITION_2_TOP_UNBOUNDED)
      ));
    
    reference left = *leftDS;
    reference right = *rightDS;
    
#ifndef CGAL_TD_DEBUG
    CGAL_warning(traits->trapezoid_top_curve_is_same(left,right));
    CGAL_warning(traits->trapezoid_bottom_curve_is_same(left,right));
    CGAL_warning(left.is_left_unbounded()==curr.is_left_unbounded());
    CGAL_warning(right.is_right_unbounded()==curr.is_right_unbounded());
#else
    CGAL_warning(traits->trapezoid_top_curve_is_same(left,right));
    CGAL_warning(traits->trapezoid_bottom_curve_is_same(left,right));
    CGAL_assertion(left.is_left_unbounded()==curr.is_left_unbounded());
    CGAL_assertion(right.is_right_unbounded()==curr.is_right_unbounded());
#endif
    
    if (!traits->is_degenerate_curve(curr))
    {
      left.init_neighbours(lb,lt,&right,&right);
      right.init_neighbours(&left,&left,rb,rt);
      if (lb) lb->set_rb(&left);
      if (lt) lt->set_rt(&left);
      if (rb) rb->set_lb(&right);
      if (rt) rt->set_lt(&right);
    }
    else
    {
      left.set_bottom(cv_bottom_ray_shoot);
      left.set_top(cv_bottom_ray_shoot);
      right.set_bottom(cv_top_ray_shoot);
      right.set_top(cv_top_ray_shoot);
      left.set_rt(&right);
      left.set_lb(lb);
      left.set_rb(0);
      right.set_lb(&left);
      right.set_rt(rt);
      right.set_rb(rb);
    }
    tt.replace(sep,leftDS,rightDS);
    const Data_structure
      *leftPtr=&tt.left(),
      *rightPtr=&tt.right();
    (*leftPtr)->set_node((Data_structure*)leftPtr);
    (*rightPtr)->set_node((Data_structure*)rightPtr);
    
#ifdef CGAL_TD_DEBUG    
    CGAL_assertion(&left==leftDS.operator->());
    CGAL_assertion(&right==rightDS.operator->());
    CGAL_assertion(left==*leftDS);
    CGAL_assertion(right==*rightDS);
    CGAL_assertion(left==*tt.left());
    CGAL_assertion(right==*tt.right());
/*
    CGAL_assertion(left.get_node()==&tt.left());
    CGAL_assertion(right.get_node()==&tt.right());
*/
    CGAL_assertion(**left.get_node()==left);
    CGAL_assertion(**right.get_node()==right);    
#endif
    
    return tt;
  }
  
  /* Description:
  the opposite operation for spliting the trapezoid with 
  vertical line through p */
  /* Precondition:
  The root trapezoid is degenerate point (p) and is active */
  
  void remove_split_trapezoid_by_point(
    Data_structure& tt,
    const Point& p)
  {
    
#ifndef CGAL_TD_DEBUG
    
    if (!tt||
      !tt->is_active()||
      !traits->is_degenerate_point(*tt)||
      !traits->point_is_same(tt->left(),p)
      )
    {
      CGAL_warning(!!tt);
      CGAL_warning(tt->is_active());
      CGAL_warning(traits->is_degenerate_point(*tt));
      CGAL_warning(traits->point_is_same(tt->left(),p));
      return;
    }
    
#else
    
    CGAL_precondition(!!tt);
    CGAL_precondition(tt->is_active());
    CGAL_precondition(traits->is_degenerate_point(*tt));
    CGAL_precondition(traits->point_is_same(tt->left(),p));
    
#endif
    
    Data_structure
      tt_left=tt.left(),
      tt_right=tt.right();
    
    search_using_data_structure(tt_left,traits,p,0);
    search_using_data_structure(tt_right,traits,p,0);

#ifndef CGAL_TD_DEBUG
    merge_if_possible(&*tt_left,&*tt_right);
    
    CGAL_warning(!tt_left.is_inner_node());
    CGAL_warning(!tt_right.is_inner_node());
    CGAL_warning(tt_left->is_right_unbounded() ==
                 tt_right->is_right_unbounded());

#else
    std::cout << "\nremove_split_trapezoid_by_point(){";
    std::cout << "\ntt_left=";
    write(std::cout,*tt_left,*traits);
    std::cout << "\ntt_right=";
    write(std::cout,*tt_right,*traits) << "}" << std::endl;

    bool merge_if_poss_left_right = merge_if_possible(&*tt_left,&*tt_right);

    std::cout << "\n->";
    write(std::cout,*tt_left,*traits) << std::endl;

    CGAL_postcondition(merge_if_poss_left_right);
    CGAL_assertion(!tt_left.is_inner_node());
    CGAL_assertion(!tt_right.is_inner_node());
    CGAL_assertion(tt_left->is_right_unbounded() ==
                   tt_right->is_right_unbounded());
    CGAL_assertion(**tt_left->get_node()==*tt_left);
#endif
    
    tt_right->remove(&tt_left);
    // mark root as deleted
    tt->remove();
  }
  
  /* Description:
  splits the trapezoid that corresponds to the root of the
  trapezoidal tree with an input edge cv*/
  /* Precondition:
  The root trapezoid is active
  cv is non degenerate
  The root trapezoid is devided by cv or
  is equal to it and is vertical.
  */
  Data_structure&
    split_trapezoid_by_curve(
    Data_structure& tt,
    pointer& prev,
    pointer& prev_bottom,
    pointer& prev_top,
    const X_curve& cv)
  {
    
#ifndef CGAL_TD_DEBUG
    
    CGAL_warning(traits);
    
#else
    
    CGAL_assertion(traits);
    
#endif
    
    reference currt=*tt;
    Point p[2];
    int i= traits->point_is_left_low(
      p[0]=traits->curve_source(cv),
      p[1]=traits->curve_target(cv)
      ) ? 0 : 1;
    
    // sets left and right accoring to curves source's and target's positions
    // sets bottom and top to X_curve itself
    X_trapezoid sep(p[i],p[1-i],cv,cv);
    /*
    creates a one-way path for all the X_curve-degenerate
    trapezoids that represent the X_curve.
    right_bottom_neighbour() is used to retrieve the
    next on path information
    */
    Data_structure
      topBT = Data_structure(X_trapezoid(currt.left(), currt.right(), cv,
                                         currt.top(),
        currt.boundedness() &
          (CGAL_TRAPEZOIDAL_DECOMPOSITION_2_LEFT_UNBOUNDED |
           CGAL_TRAPEZOIDAL_DECOMPOSITION_2_RIGHT_UNBOUNDED|
           CGAL_TRAPEZOIDAL_DECOMPOSITION_2_TOP_UNBOUNDED))),
      bottomBT = Data_structure(X_trapezoid(currt.left(),currt.right(),
                                            currt.bottom(), cv,
        currt.boundedness() &
          (CGAL_TRAPEZOIDAL_DECOMPOSITION_2_LEFT_UNBOUNDED|
           CGAL_TRAPEZOIDAL_DECOMPOSITION_2_RIGHT_UNBOUNDED|
           CGAL_TRAPEZOIDAL_DECOMPOSITION_2_BOTTOM_UNBOUNDED)));
    reference bottom=*bottomBT;
    reference top=*topBT;
    top.init_neighbours(prev_top, currt.left_top_neighbour(), 0,
                        currt.right_top_neighbour());
    bottom.init_neighbours(currt.left_bottom_neighbour(),
                           prev_bottom,currt.right_bottom_neighbour(),0);
    if (prev_bottom) prev_bottom->set_rt(&bottom);
    if (prev_top) prev_top->set_rb(&top);
    if (currt.left_bottom_neighbour())
      currt.left_bottom_neighbour()->set_rb(&bottom);
    if (currt.left_top_neighbour())
      currt.left_top_neighbour()->set_rt(&top);
    if (currt.right_bottom_neighbour())
      currt.right_bottom_neighbour()->set_lb(&bottom);
    if (currt.right_top_neighbour()) currt.right_top_neighbour()->set_lt(&top);
    tt.replace(sep,bottomBT,topBT);
    const Data_structure
      *bottomPtr=&tt.left(),
      *topPtr=&tt.right();
    (*bottomPtr)->set_node((Data_structure*)bottomPtr);
    (*topPtr)->set_node((Data_structure*)topPtr);
    if (prev) prev->set_rb(tt.operator->());
    prev_bottom=(*bottomPtr).operator->();
    prev_top=(*topPtr).operator->();
    prev=tt.operator->();
    return tt;
  }
  
  /* replace X_curve-point adjacency in the data structure with
  a new one
  precondition:
  the X_curve represented by t is top-right
  relative to the point represented by sep
  if and only if top=true
  */
  void replace_curve_at_point_using_geometry(reference t, reference sep,
    bool cv_top_right=true)
  {
    Point p(sep.left());
    X_curve cv(t.top());
    Around_point_circulator circ(traits,p,cv_top_right ?
                                 sep.right_top_neighbour() :
                                 sep.left_bottom_neighbour());
    if (circ.operator->())
    {
      if (cv_top_right)
        while(traits->curve_compare_at_x_from_top(circ->top(),cv,p)!=EQUAL)
          circ++;
        else
          while(traits->curve_compare_at_x_from_bottom(circ->bottom(), cv, p)
                != EQUAL)
            circ++;
          circ.replace(t);
    }
  }
  void insert_curve_at_point_using_geometry(reference sep, reference end_point)
  {
    
#ifndef CGAL_TD_DEBUG
    
    CGAL_warning(traits);
    CGAL_warning(traits->is_degenerate_point(end_point));
    CGAL_warning(traits->is_degenerate_curve(sep));
    CGAL_warning(traits->point_is_same(end_point.left(),sep.right()) ||
                 traits->point_is_same(end_point.left(),sep.left()));
    
#else
    
    CGAL_assertion(traits);
    CGAL_precondition(traits->is_degenerate_point(end_point));
    CGAL_precondition(traits->is_degenerate_curve(sep));
    CGAL_precondition(traits->point_is_same(end_point.left(),sep.right()) ||
                      traits->point_is_same(end_point.left(),sep.left()));
    
#endif
    
    /* update (in this order)
    end_point.left_bottom_neighbour()
    if no curves adjacent to the point eminating toward up
    or right exist returns null, otherwise return
    the first X_curve sweeped using a counter clockwise sweep
    starting from up direction not including.
    end_point.right_top_neighbour()
    if no curves adjacent to the point eminating toward bottom
    or left exist returns null, otherwise return
    the first X_curve sweeped using a counter clockwise sweep
    starting from bottom direction not including.
    sep.right_top_neighbour()
    next clockwise degenerate_curve around rightmost end_point (possibly
    himself)
    sep.left_bottom_neighbour()
    next clockwise degenerate_curve around leftmost end_point (possibly
    himself)
    */
    const X_curve& cv=sep.top();
    const Point& p=end_point.left();
    pointer rt = end_point.right_top_neighbour(),
        lb = end_point.left_bottom_neighbour();
    if(!traits->point_is_same(end_point.left(),sep.right()))
    {
      if (!rt && !lb)
        // empty circulator
      {
        end_point.set_rt(&sep);
        sep.set_lb(&sep);
      }
      else
      {
      /* set circ[0] to first X_curve on a counter clockwise 
        sweep starting at cv */
        Around_point_circulator circ(traits,p,rt ? rt : lb),stopper=circ;
        // if !rt set circ to lb
        // otherwise advance as required
#ifdef CGAL_TD_DEBUG
        
        Around_point_circulator first_circ(circ);
        
#endif
        
        while(traits->curve_compare_at_x_from_top(circ->top(),cv,p)
          ==SMALLER)
        {
          circ++;
          if (circ==stopper)
            break;
          
#ifdef CGAL_TD_DEBUG
          
          CGAL_assertion(first_circ!=circ);
          CGAL_assertion(circ->is_active());
          
#endif
          
        }
        
#ifdef CGAL_TD_DEBUG
        
        CGAL_assertion(traits->curve_compare_at_x_from_top(circ->top(), cv, p)
                       != EQUAL);
        
#endif
        
        circ.insert(sep);
        // set end_point.left_bottom_neighbour()
        // set end_point.right_top_neighbour();
        if (lb)
        {
          Around_point_circulator lb_circ(traits,p,lb);
          if (!rt) end_point.set_rt(lb);
          if (lb_circ.operator->()==&sep) end_point.set_lb(&sep);
        }
        else
        {
          if (traits->curve_compare_at_x_from_bottom(rt->top(), cv, p) ==
              SMALLER)
            end_point.set_rt(&sep);
        }
      }
    }
    else
    {
      if (!rt && !lb)
        // empty circulator
      {
        end_point.set_lb(&sep);
        sep.set_rt(&sep);
      }
      else
      {
      /* set circ[0] to first X_curve on a counter clockwise 
        sweep starting at cv */
        Around_point_circulator circ(traits,p,lb ? lb : rt),stopper=circ;
        // if !lb set circ to rt
        // otherwise advance as required
        while (traits->curve_compare_at_x_from_bottom(circ->top(),cv,p) ==
               SMALLER)
        {
          circ++;
          if (circ==stopper)
            break;
        }
        
#ifdef CGAL_TD_DEBUG
        
        CGAL_assertion(traits->curve_compare_at_x_from_bottom(circ->top(), cv,
                                                              p) != EQUAL);
        
#endif
        
        circ.insert(sep);
        if (rt)
          // set end_point.left_bottom_neighbour()
        {
          Around_point_circulator rt_circ(traits,p,rt);
          if (!lb) end_point.set_lb(rt);
          if (rt_circ.operator->()==&sep) end_point.set_rt(&sep);
        }
        else
        {
          // set end_point.right_top_neighbour();
          if(traits->curve_compare_at_x_from_top(lb->top(),cv,p)
            ==SMALLER)
            end_point.set_lb(&sep);
        }
      }
    }
  }
  /*
  description:
  Update top(),bottom() for trapezoid
  Update rt,lb
  remarks:
  The point degenerate trapezoid representing a point p holds as its top and
  bottom curves
  the output for a vertical ray shoot quiries immidiately below the point
  toward up and
  immediately above the point toward down respectively.
  optimization:
  Each degenerate X_curve trapezoid eminating from the point p holds a pointer
  to the next
  trapezoid in a clockwise sweep around p(possibly to itself).
  This pointer is stored in rt or lb depending on the trapezoid is top right or
  bottom left of p.
  For the trapezoid representing p rt and lb hold the previous X_curve
  degenerate trapezoid
  in a clockwise sweep to the first top right and bottom left respectively.
  */
  
  void remove_curve_at_point_using_geometry(const_ref sep,reference end_point)
  {
    
#ifndef CGAL_TD_DEBUG
    
    CGAL_warning(traits);
    CGAL_warning(traits->is_degenerate_point(end_point));
    CGAL_warning(traits->is_degenerate_curve(sep));
    CGAL_warning(traits->point_is_same(end_point.left(),sep.right()) ||
                 traits->point_is_same(end_point.left(),sep.left()));
    CGAL_warning(end_point.is_active());
    CGAL_warning(sep.is_active());
    
#else
    
    CGAL_assertion(traits);
    CGAL_precondition(traits->is_degenerate_point(end_point));
    CGAL_precondition(traits->is_degenerate_curve(sep));
    CGAL_precondition(traits->point_is_same(end_point.left(),sep.right()) ||
                      traits->point_is_same(end_point.left(),sep.left()));
    CGAL_precondition(end_point.is_active());
    CGAL_precondition(sep.is_active());
    
#endif
    
    /* update (in this order)
    end_point.left_bottom_neighbour()
    if no curves adjacent to the point eminating toward up
    or right exist returns null, otherwise return
    the first X_curve sweeped using a counter clockwise sweep
    starting from up direction not including.
    end_point.right_top_neighbour()
    if no curves adjacent to the point eminating toward bottom
    or left exist returns null, otherwise return
    the first X_curve sweeped using a counter clockwise sweep
    starting from bottom direction not including.
    sep.right_top_neighbour()
    next clockwise degenerate_curve around rightmost end_point (possibly
    himself)
    sep.left_bottom_neighbour()
    next clockwise degenerate_curve around leftmost end_point (possibly
    himself)
    */
    const X_curve& cv=sep.top();
    const Point& p=end_point.left();
    Around_point_circulator
      prev_top(traits,p,end_point.right_top_neighbour()),
      prev_bottom(traits,p,end_point.left_bottom_neighbour());
    
    // update bottom
    if(traits->curve_is_same(cv,end_point.bottom()))
    {
      Around_point_circulator bottom=(!!prev_bottom) ? prev_bottom : prev_top;
      bottom++;
      
#ifdef CGAL_TD_DEBUG
      
      CGAL_assertion(!!bottom);
      
#endif
      
      if (!bottom->is_bottom_unbounded())
        end_point.set_bottom(bottom->bottom());
      else
        end_point.set_bottom_unbounded();
    }
    // update top
    if(traits->curve_is_same(cv,end_point.top()))
    {
      Around_point_circulator top=(!!prev_top) ? prev_top : prev_bottom;
      top++;
      
#ifdef CGAL_TD_DEBUG
      
      CGAL_assertion(!!top);
      
#endif
      
      if (!top->is_top_unbounded())
        end_point.set_top(top->top());
      else
        end_point.set_top_unbounded();
    }
    
    //update right top neighbour and left bottom neighbour
    bool b=traits->point_is_left_low(p,sep.right());
    Around_point_circulator circ(traits,p,b ? end_point.right_top_neighbour() :
                                 end_point.left_bottom_neighbour());
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_precondition(!!circ);
    
#endif
    
    while(*circ!=sep)circ++;
    pointer removed=circ.operator->();
    circ.remove();
    if(!!circ)
    {
      pointer effective_curr=circ[0];
      if (end_point.right_top_neighbour()==removed)
        end_point.set_rt(effective_curr);
      if (end_point.left_bottom_neighbour()==removed)
        end_point.set_lb(effective_curr);
      Around_point_circulator rt_circ(traits, p,
                                      end_point.right_top_neighbour());
      if (!!rt_circ)
      {
        rt_circ++;
        if (rt_circ.is_right_rotation())
          end_point.set_rt(0);
      }
      Around_point_circulator lb_circ(traits, p,
                                      end_point.left_bottom_neighbour());
      if (!!lb_circ)
      {
        lb_circ++;
        if (!lb_circ.is_right_rotation())
          end_point.set_lb(0);
      }
    }
    else
    {
      end_point.set_rt(0);
      end_point.set_lb(0);
    }
  }
  
  /*update
  tr.bottom()
  vertical_ray_shoot downward from tr
  tr.top()
  vertical_ray_shoot upward from tr
  */
  reference insert_curve_at_point_using_geometry(const X_curve &     cv,
                                                 const Point&        p,
                                                 pointer &           tr,
                                                 const Locate_type & lt)
  {
    CGAL_assertion(traits);
    CGAL_precondition(lt==POINT);
    
    if (traits->curve_compare_at_x_from_top(cv,tr->top(),p)==SMALLER)
      tr->set_top(cv);
    if (traits->curve_compare_at_x_from_bottom(cv,tr->bottom(),p)==SMALLER)
      tr->set_bottom(cv);
    return *tr;
  }
  
  reference insert_curve_at_point_using_data_structure(const X_curve & cv,
                                                       const Point & p,
                                                       pointer & tr,
                                                       const Locate_type & lt)
  {
    CGAL_precondition(lt==TRAPEZOID || lt==UNBOUNDED_TRAPEZOID);
    
    Data_structure *tt=tr->get_node();
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_assertion(tr->get_node());
    
#endif
    
    return *split_trapezoid_by_point(*tt,p,cv,cv);
    //return *tr;
  }
        
  void replace_curve_at_point_using_geometry(const X_curve& old_cv,
    const X_curve& new_cv,reference sep)
  {
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_precondition(traits->is_degenerate_point(sep));
    
#endif
    
    if (!sep.is_top_unbounded() && traits->curve_is_same(sep.top(), old_cv))
      sep.set_top(new_cv);
    if (!sep.is_bottom_unbounded() &&
        traits->curve_is_same(sep.bottom(), old_cv)) sep.set_bottom(new_cv);
  }
  
  /* update geometric boundary(top and bottom) for trapezoids
  traveled along an iterator till end reached
  precondition:
  end==0 or end is on the path of the iterator
  postcondition:
  end is pointer to the last trapezoid encountered,if any
  */
  void replace_curve_using_geometry(In_face_iterator & it,
                                    const X_curve & old_cv,
                                    const X_curve & new_cv,pointer & end)
  {
    pointer last=0;
    while (it.operator->()!=end)
    {
      if (!it->is_top_unbounded() && traits->curve_is_same(it->top(),old_cv))
        it->set_top(new_cv);
      if (!it->is_bottom_unbounded() &&
          traits->curve_is_same(it->bottom(),old_cv)) it->set_bottom(new_cv);
      last=it.operator->();
      ++it;
    }
    end=last;
  }
  
  /*
    description:
    advances input Data structure using data structure,input point p and 
    possibly X_curve cv till
    p is found(if cv hadn't been given)
    cv is found(if cv was given)
    or
    leaf node reached
    postcondition:
    output is the closest active trapezoid to p/cv
    remark:
    use this function with care!
  */
  /*static */
  Locate_type search_using_data_structure(Data_structure& curr,Traits* traits,
                                          const Point& p,const X_curve* cv,
                                          Comparison_result up=EQUAL) const
  {
    const Point* pp;
    const X_curve* pc;
    
#ifdef CGAL_TD_DEBUG
    pointer old=NULL;
#endif
    
    while(true)
      {
        
#ifdef CGAL_TD_DEBUG
        
        // unbounded loop
        CGAL_assertion(curr.operator->()!=old);
        old=curr.operator->();
        
#endif
        
        if (traits->is_degenerate_point(*curr))
        // point node conditional (separation)
          {
            // extract point from trapezoid
            pp=&curr->left();
            if (traits->point_is_left_low(p,*pp))
              {
                curr=curr.left();
                continue;
              }
            else if (traits->point_is_left_low(*pp,p))
              {
                curr=curr.right();
                continue;
              }
            else if (traits->point_is_same(*pp,p))
              {
                if (!cv)
                {
                  if ( up == EQUAL ) { // point found!
                    if (curr->is_active()) return POINT;
                    curr=curr.left();
                  }
                  else if ( up == LARGER ) { // vertical ray shut up
                    curr=curr.right();                      
                  }
                  else /*if ( up == SMALLER ) */ {
                    curr=curr.left();     // vertical ray shut down
                  }
                  continue;
                }
                else
                  {
#ifndef CGAL_TD_DEBUG
                    
                    CGAL_warning(
                      traits->point_is_same(
                        traits->curve_leftlow_most(*cv),
                        p
                        )||
                      traits->point_is_same(
                        traits->curve_righttop_most(*cv),
                        p
                        ));
                    
#else
                    
                    CGAL_assertion(
                      traits->point_is_same(
                        traits->curve_leftlow_most(*cv),
                        p
                        )||
                      traits->point_is_same(
                        traits->curve_righttop_most(*cv),
                        p
                        ));
                    
#endif
                    
                    curr=traits->point_is_same(traits->curve_leftlow_most(*cv),
                                               p) ? curr.right() : curr.left();
                    // (Oren 14/4/02) ??
                    
                    continue;
                  }
              }
            else
              {
                
#ifndef CGAL_TD_DEBUG
                
                CGAL_warning(
                             traits->point_is_left_low(p,*pp)||
                             traits->point_is_left_low(*pp,p)||
                             traits->point_is_same(*pp,p)
                             );
                
#else
                
                CGAL_assertion(
                               traits->point_is_left_low(p,*pp)||
                               traits->point_is_left_low(*pp,p)||
                               traits->point_is_same(*pp,p)
                               );
                
#endif
                
                return Locate_type();
              }
          }
        if (traits->is_degenerate_curve(*curr))
        // CURVE SEPRATION
          {
            pc = &curr->top();
            typename Traits::Curve_point_status c =
              traits->curve_get_point_status(*pc,p);
            if (c==Traits::UNDER_CURVE)
            {
              curr=curr.left();
              continue;
            }
            else if (c==Traits::ABOVE_CURVE)
            {
              curr=curr.right();
              continue;
            }
            else if (c==Traits::ON_CURVE)
            {  // p on CURVE
                
#ifndef CGAL_TD_DEBUG
                
              CGAL_warning(c == Traits::ON_CURVE &&
                !traits->point_is_right(p,traits->curve_rightmost(*pc))&&
                !traits->point_is_left(p,traits->curve_leftmost(*pc)));
#else
                
              CGAL_postcondition(c == Traits::ON_CURVE &&
                !traits->point_is_right(p,traits->curve_rightmost(*pc))&&
                !traits->point_is_left(p,traits->curve_leftmost(*pc)));
#endif
                if (!cv)
                {
                  // For a vertical curve, we always visit it after visiting
                  // one of its endpoints.
                  if ((up == EQUAL) || traits->is_vertical(*curr)) {
                    //std::cout << "EQUAL or VERTICAL" << std::endl;
                    if (curr->is_active()) return CURVE;
                    curr=curr.left();
                  }
                  else if (up==LARGER) {
                    curr=curr.right();
                  }
                  else /* if (up==SMALLER) */ {
                    curr=curr.left();
                  }
                  continue;
                }
                else
                {
                    
#ifndef CGAL_TD_DEBUG
                    
                  CGAL_warning(traits->point_is_same
                               (traits->curve_leftlow_most(*cv),
                                traits->curve_leftlow_most(*pc)) ||
                               traits->point_is_same
                               (traits->curve_righttop_most(*cv),
                                traits->curve_righttop_most(*pc)));
                    
#else
                    
                  if (!(traits->point_is_same
                        (traits->curve_leftlow_most(*cv),
                         traits->curve_leftlow_most(*pc))||
                        traits->point_is_same
                        (traits->curve_righttop_most(*cv),
                         traits->curve_righttop_most(*pc))))
                  {
                    std::cerr << "\npc " << *pc;
                    std::cerr << "\ncv " << *cv << std::endl;
                    CGAL_assertion(traits->point_is_same
                                   (traits->curve_leftlow_most(*cv),
                                    traits->curve_leftlow_most(*pc)) ||
                                   traits->point_is_same
                                   (traits->curve_righttop_most(*cv),
                                    traits->curve_righttop_most(*pc)));
                  }
                    
#endif
                    
                  Comparison_result res =
                    traits->point_is_same(traits->curve_leftlow_most(*cv),
                                          traits->curve_leftlow_most(*pc)
                                          ) ?
                      traits->curve_compare_at_x_from_top(*pc,*cv,p) :
                      traits->curve_compare_at_x_from_bottom(*cv,*pc,p);
                    
                  switch(res)
                  {
                    case LARGER:
                      curr=curr.right();
                      break;
                    case SMALLER:
                      curr=curr.left();
                      break;
                    case EQUAL:
                      switch(up)
                      {
                        case LARGER:
                          curr=curr.right();
                          break;
                        case SMALLER:
                          curr=curr.left();
                          break;
                        case EQUAL:
                          if (curr->is_active()) return CURVE;
                          curr=curr.left();
                          break;
                            
#ifdef CGAL_TD_DEBUG
                            
                        default:
                          CGAL_assertion(up==LARGER||up==SMALLER||up==EQUAL);
                          return Locate_type();
                            
#endif

                      }
                      break;
                        
#ifdef CGAL_TD_DEBUG
                        
                    default:
                      CGAL_assertion(res==LARGER||res==SMALLER||res==EQUAL);
                      return Locate_type();
                        
#endif

                  }
                }
            }
            
#ifdef CGAL_TD_DEBUG
            
            else //traits->curve_get_point_status(*pc,p)==
                //Traits::CURVE_NOT_IN_RANGE
            {
              std::cerr << "\ncurr->top()==" << *pc;
              std::cerr << "\np==" << p;
              CGAL_assertion(
                               c==Traits::UNDER_CURVE||
                               c==Traits::ABOVE_CURVE||
                               c==Traits::ON_CURVE
                               );
                return Locate_type();
              }
            
#endif
            
          }
        else
        // !is_degenerate()
          {
            if (curr->is_active()) return curr->is_unbounded() ? 
                                       UNBOUNDED_TRAPEZOID : TRAPEZOID;
            curr=curr.left();
            continue;
          }
      }
  }
  Data_structure container2data_structure(map_nodes& ar, int left,
                                          int right) const
  {

#ifndef CGAL_TD_DEBUG
    
    CGAL_warning(traits);
    
#else
    
    CGAL_assertion(traits);
    
#endif
    
    if (right>left)
    {
      int d=(int)CGAL_CLIB_STD::floor((double(right+left))/2);
      // Replacing operator [] of map with find to please MSVC 7
      Point p = (ar.find(d)->second)->right();
      //Point p=ar[d]->right();
      Data_structure curr=
        Data_structure(
        X_trapezoid(&p,&p,0,0),
        container2data_structure(ar,left,d),
        container2data_structure(ar,d+1,right)
        );
      curr.left()->set_node((Data_structure*)&curr.left());
      curr.right()->set_node((Data_structure*)&curr.right());
      curr->set_node(&curr);// fake temporary node
      curr->remove(); // mark as deleted
      curr->set_node(0);

      return curr;
    }
    else
      // Replacing operator [] of map with find to please MSVC 7
      return ar.find(left)->second;
      //return ar[left];
  }
  /*==============================================
  Trapezoidal_decomposition_2 public member functions
  ==============================================*/
public:
  
  Trapezoidal_decomposition_2(bool rebuild=true) :
    depth_threshold(CGAL_TD_DEFAULT_DEPTH_THRESHOLD),
    size_threshold(CGAL_TD_DEFAULT_SIZE_THRESHOLD) 
    {init();set_needs_update(rebuild);}
  Trapezoidal_decomposition_2(const double& depth_th,const double& size_th) : 
    depth_threshold(depth_th),size_threshold(size_th) 
    {init();set_needs_update(rebuild);}
  
  virtual ~Trapezoidal_decomposition_2()
  {
    
#ifndef CGAL_TD_DEBUG
    
    CGAL_warning(DS);
    if (!DS) return;
    
#else
    
    CGAL_assertion(DS);
    
#endif
    
    delete DS;
  }
  
  /*  Input:
  X_curve
  Output:
  if X_curve or twin already inserted the latter is returned.
  otherwise the left-low most edge-degenerate trapezoid that represents
  the input X_curve is returned
  Remark:
  Given an edge-degenerate trapezoid representing a X_curve,
  all the other trapezoids representing the X_curve can be  extracted
  via moving continously to the left and right neighbours.
  */
  X_trapezoid insert(curve_const_ref cv)
  {
#ifdef CGAL_TD_DEBUG
    *cv.get_parent();
#endif
/*
    Point tmp;
    // maintaining some bounding box for future use.
    
    if (!number_of_curves_) 
      // give initiale values to  bounding points when empty
    {
      POINT_AT_LEFT_TOP_INFINITY=POINT_AT_RIGHT_BOTTOM_INFINITY=
      traits->curve_source(cv);
    }
    
    if (!traits->point_is_left_low(POINT_AT_LEFT_TOP_INFINITY,tmp=
    traits->curve_leftlow_most(cv)))
      POINT_AT_LEFT_TOP_INFINITY=traits->point_to_left(tmp);
    if (!traits->point_is_right_top(POINT_AT_RIGHT_BOTTOM_INFINITY,tmp=
    traits->curve_righttop_most(cv)))
      POINT_AT_RIGHT_BOTTOM_INFINITY=traits->point_to_right(tmp);
*/
    return insert_in_face_interior(cv);
  }
  
  /*        Input:
  X_curve
  Output:
  if X_curve or twin already inserted the latter is returned.
  otherwise the left-low most edge-degenerate trapezoid that represents the
  input X_curve is returned
  Remark:
  Given an edge-degenerate trapezoid representing a X_curve,
  all the other trapezoids representing the X_curve can be  extracted
  via moving continously to the left and right neighbours.
  */
  const X_trapezoid insert_in_face_interior(curve_const_ref cv)
  {
#ifdef CGAL_TD_DEBUG
    *cv.get_parent();
#endif
#ifdef CGAL_TDBB_DEBUG
    std::cout << "\ninsert_in_face_interior(" << cv << ")" 
      << "\nBbox " << traits->get_bounding_box();
#endif

#ifdef CGAL_TD_DEBUG
   std::cout << "\nTD::insert_in_face_interior(" << cv << ") called with "
    << (is_valid(*DS) ? "valid" : "invalid") << " data structure"
    <<  std::endl;
   write(std::cout,*DS,*traits) << std::endl;
#endif

    if (needs_update_) update();
    // locate the input X_curve end points in the X_trapezoid Dag

    CGAL_assertion(traits);
    
#ifndef CGAL_TD_DEBUG
    
    CGAL_warning(!traits->point_is_same(traits->curve_source(cv),
                                        traits->curve_target(cv)));
    
#else
    
    CGAL_precondition(!traits->point_is_same(traits->curve_source(cv),
                                             traits->curve_target(cv)));
    
#endif
    
    Point p[2];
    int i= traits->point_is_left_low(
      p[0]=traits->curve_source(cv),
      p[1]=traits->curve_target(cv)
      ) ? 0 : 1;
    Locate_type lt1,lt2;
    pointer tr1,tr2;
    
#ifndef CGAL_NO_TRAPEZOIDAL_DECOMPOSITION_2_OPTIMIZATION
    
    locate_optimization(p[i],tr1,lt1);
    
#else
    
    tr1=&locate(p[i],lt1);
    
#endif
    
    if (lt1==CURVE)
    {
      CGAL_precondition_msg(lt1!=CURVE,"Input is not planar as\
        one of the input point inside previously inserted X_curve.");
      return X_trapezoid();
    }
    
    reference t_p1=
      (lt1==POINT) ?
      insert_curve_at_point_using_geometry(cv,p[i],tr1,lt1) :
    insert_curve_at_point_using_data_structure(cv,p[i],tr1,lt1);
    
#ifndef CGAL_NO_TRAPEZOIDAL_DECOMPOSITION_2_OPTIMIZATION
    
    locate_optimization(p[1-i],tr2,lt2);
    locate_opt_empty();
    
#else
    
    tr2=&locate(p[1-i],lt2);
    
#endif
    
    if (lt2==CURVE)
    {
      CGAL_precondition_msg(lt2!=CURVE,"Input is not planar as\
        one of the input point inside previously inserted X_curve.");
      return X_trapezoid();
    }
    
    reference t_p2= (lt2==POINT) ?
      insert_curve_at_point_using_geometry(cv,p[1-i],tr2,lt2) :
    insert_curve_at_point_using_data_structure(cv,p[1-i],tr2,lt2);
    
    // locate and insert end points of the input X_curve to the X_trapezoid Dag
    // if needed
    Data_structure tt_p1(*t_p1.get_node());
    Data_structure tt_p2(*t_p2.get_node());
    
    // create the X_trapezoid iterator for traveling along the Trapezoids that
    // intersect the input X_curve, using left-low to right-high order
    In_face_iterator it=follow_curve(tt_p1,cv,LARGER);
    pointer curr,prev=&t_p1,prev_bottom,prev_top;
    pointer old_output = it.operator->(), old_top = 0, old_bottom = 0;
    
#ifndef CGAL_TD_DEBUG

    CGAL_warning(!traits->is_degenerate(*old_output));

#else
    
    CGAL_assertion(!traits->is_degenerate(*old_output));
    
#endif
    
    old_output=0;
    Data_structure *tt;
    bool first_time=true;
    while(!!it)
    {
      curr=it.operator->();
      prev_bottom=curr->left_bottom_neighbour();
      prev_top=curr->left_top_neighbour();
      // pass using it along cv
      it++;
      tt = curr->get_node();
      if(first_time)
      {
        
#ifndef CGAL_TD_DEBUG
        
        if(!curr->is_top_unbounded()&&traits->curve_is_same(curr->top(),cv))
        {
          CGAL_warning(!traits->curve_is_same(curr->top(),cv));
          return X_trapezoid();
        }
        
#else
        
        CGAL_precondition(curr->is_top_unbounded()||
                          !traits->curve_is_same(curr->top(),cv));
        
#endif
        
      }
      split_trapezoid_by_curve(*tt,old_output, old_bottom, old_top, cv);
      
#ifdef CGAL_TD_DEBUG
      
      CGAL_assertion(traits->curve_is_same((**tt).top(),cv));
      
#endif
      
      if(first_time)
      {
        insert_curve_at_point_using_geometry(*old_output,t_p1);
        first_time=false;
      }
      if (tt->is_inner_node())
      {
        // merge adjacent trapezoids on input X_curve's bottom side if possible
        if(merge_if_possible(
          prev_bottom,
          tt->left().operator->()
          ))
        {
          tt->set_left(*(prev_bottom->get_node()));
          old_bottom = prev_bottom;
        }
        // merge adjacent trapezoids on input X_curve's top side if possible
        if(merge_if_possible(
          prev_top,
          tt->right().operator->()
          ))
        {
          tt->set_right(*(prev_top->get_node()));
          old_top=prev_top;
        }
        
        // update trapezoid's left/right neighbouring relations
        if(!traits->is_degenerate(*prev) &&
          !traits->is_degenerate(*curr))
        {
          curr->set_lb(prev);
          curr->set_lt(prev);
          prev->set_rb(curr);
          prev->set_rt(curr);
        }
      }
      else
      {
        
#ifdef CGAL_TD_DEBUG
        
        CGAL_assertion(curr->is_valid(traits));
        
#endif
        
        break;
      }
      
#ifdef CGAL_TD_DEBUG
      
      CGAL_assertion(curr->is_valid(traits));
      
#endif
      
    }
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_postcondition(traits->is_degenerate_curve(*old_output));
    CGAL_postcondition(traits->curve_is_same((const X_curve)old_output->top(),
                                             cv));
    
#endif
    
    insert_curve_at_point_using_geometry(*old_output,t_p2);
    number_of_curves_++;
    
#ifdef CGAL_TD_DEBUG
   std::cout << "\nTD::insert_in_face_interior() exited with data structure" 
      << is_valid(*DS) << std::endl;
   write(std::cout,*DS,*traits) << std::endl;
#endif
    
    return *old_output;
  }

  // removal functions

  void remove(curve_const_ref cv)
  // We assume here that the input curves are in planar position.
  {
    remove_in_face_interior(cv);
  }
  template <class curve_iterator>
  void remove(curve_iterator begin, curve_iterator end)
  {
    std::random_shuffle(begin,end);
    curve_iterator it=begin,next=it;
    while(it!=end) {++next;remove(*it);it=next;}
  }
  void clear()
  {
    delete DS;
    init();
  }

  void remove_in_face_interior(curve_const_ref cv)
  // Assumes the map to be planar.
  {

#ifdef CGAL_TD_DEBUG
   std::cout << "\nTD::remove_in_face_interior(" << cv << ") called with "
    << (is_valid(*DS) ? "valid" : "invalid") << " data structure"
    <<  std::endl;
   write(std::cout,*DS,*traits) << std::endl;
#endif

    if (needs_update_) update();
    
#ifndef CGAL_NO_TRAPEZOIDAL_DECOMPOSITION_2_OPTIMIZATION
    locate_opt_empty();
#endif
    
#ifndef CGAL_TD_DEBUG
    CGAL_warning(traits);
#else
    CGAL_assertion(traits);
#endif
    
    // calculating leftmost and rightmost points of X_curve cv
    Point
      leftmost=traits->curve_leftlow_most(cv),
      rightmost=traits->curve_righttop_most(cv);
    Locate_type lt1,lt2;
    reference
      t1=locate(leftmost,lt1),
      t2=locate(rightmost,lt2);
    
        CGAL_warning(lt1==POINT && lt2==POINT);
    if (!(lt1==POINT && lt2==POINT)) return;
    
#ifndef CGAL_TD_DEBUG
    
    CGAL_warning(t1.get_node());
    CGAL_warning(t2.get_node());
    
#endif
    
    Data_structure
      &tt1=*t1.get_node(),
      &tt2=*t2.get_node();

/* calculate the immediate lower central and upper neighbourhood of the curve 
    in the data structure */
    In_face_iterator
      bottom_it(follow_curve(tt1,cv,SMALLER)),
      mid_it(follow_curve(tt1,cv,EQUAL)),
      top_it(follow_curve(tt1,cv,LARGER));
    
    bool bottom, old_bottom = false, end_reached;
    map_nodes new_array;
    int last_index[]={0,0};
    int sz=0;
    Point left=bottom_it->left(),right;
    pointer last_bottom,last_top,last=0,old;
    
#ifndef CGAL_TD_DEBUG
    CGAL_warning(traits->point_is_same(top_it->left(),left));
#else
    CGAL_precondition(traits->point_is_same(top_it->left(),left));
#endif
    
    // remove adjacency at left end point
    const_ref first=*mid_it;
    //X_curve const * old_cv=&first.top();
    
#ifdef CGAL_TD_DEBUG
    CGAL_assertion(traits->curve_is_same(first.top(),cv));
    CGAL_assertion(traits->point_is_same(t1.left(),leftmost));
#endif
    
    remove_curve_at_point_using_geometry(first,t1);
    
    do
    {
      // which of bottom_it,top_it to advance.
      bottom=traits->point_is_left_low(bottom_it->right(),top_it->right());
      Iterator& it =  bottom ? bottom_it : top_it;
      pointer& last_it = bottom ? last_bottom : last_top;
      right=it->right();

      // copy trapezoid's content and node pointer.
      typename map_nodes::value_type pair(sz,
        Data_structure(
          X_trapezoid(&left,&right,
          !bottom_it->is_bottom_unbounded() ? &bottom_it->bottom() : 0,
          !top_it->is_top_unbounded() ? &top_it->top() : 0)));
      new_array.insert(pair);
      Data_structure & curr = (new_array.find(sz))->second;
      ++sz;
      curr->set_node(&curr);
      curr->set_lb(bottom_it->left_bottom_neighbour());
      curr->set_lt(top_it->left_top_neighbour());
      if (last)
      {
        if (traits->trapezoid_top_curve_is_same(*last,*curr))
        {
          curr->set_lt(last);
        }

        if (traits->trapezoid_bottom_curve_is_same(*last,*curr))
        {
          curr->set_lb(last);
        }
      }
      if (curr->left_bottom_neighbour())
          curr->left_bottom_neighbour()->set_rb(curr.operator->());
      if (curr->left_top_neighbour())
          curr->left_top_neighbour()->set_rt(curr.operator->());
      last=curr.operator->();
      left=right;
      last_bottom=bottom_it.operator->();
      last_top=top_it.operator->();
      
#ifdef CGAL_TD_DEBUG
      CGAL_warning(last_bottom);
      CGAL_warning(last_top);
#endif
      
      old=it.operator->();
      it++;
      end_reached=!bottom_it||!top_it;
      if (!bottom_it ||
          bottom && !traits->trapezoid_bottom_curve_is_same(*old,*it))
      {
        pointer rb=old->right_bottom_neighbour();
        if (rb) {rb->set_lb(last);last->set_rb(rb);}
      }
      if (!top_it || !bottom && !traits->trapezoid_top_curve_is_same(*old,*it))
      {
        pointer rt=old->right_top_neighbour();
        if (rt) {rt->set_lt(last);last->set_rt(rt);}
      }

#ifdef CGAL_TD_DEBUG
      CGAL_assertion(last->get_node());
#endif

      if (old_bottom != bottom)
      {
        Data_structure tmp=container2data_structure(
          new_array,last_index[bottom ? 0 : 1],sz-1);

#ifdef CGAL_TD_DEBUG
        std::cout << "\nremove_in_face_interior allocated ";
        write(std::cout,tmp,*traits) << "\ninto ";
        write(std::cout,*last_it,*traits,false) << std::endl;
#endif

        last_it->remove(&tmp);
        last_index[bottom ? 0 : 1] = sz;
        old_bottom = bottom;
      }
      else
      {
        Data_structure tmp=container2data_structure(new_array,sz-1,sz-1);

#ifdef CGAL_TD_DEBUG
        std::cout << "\nremove_in_face_interior allocated ";
        write(std::cout,tmp,*traits) << "\ninto ";
        write(std::cout,*last_it,*traits,false) << std::endl;
#endif

        last_it->remove(&tmp);
        last_index[bottom ? 0 : 1] = sz;
      }
      const Data_structure *real=&last_it->get_node()->left();
      (*real)->set_node((Data_structure*)real);
    }
    while(!end_reached);
    Iterator & it = !old_bottom ? bottom_it : top_it;
    
#ifdef CGAL_TD_DEBUG
    CGAL_warning(traits->point_is_same(it->right(),rightmost));
#endif
    
    pointer rb=it->right_bottom_neighbour(),rt=it->right_top_neighbour();

    Data_structure tmp=container2data_structure(new_array,
      last_index[!bottom ? 0 : 1],new_array.size()-1);

#ifdef CGAL_TD_DEBUG
        std::cout << "\nremove_in_face_interior allocated ";
        write(std::cout,tmp,*traits) << "\ninto ";
        write(std::cout,*it,*traits,false) << std::endl;
#endif

    it->remove(&tmp);
    const Data_structure *real=&it->get_node()->left();

    (*real)->set_node((Data_structure*)real);
    if (rb) {last->set_rb(rb);rb->set_lb(last);}
    if (rt) {last->set_rt(rt);rt->set_lt(last);}
    
    Base_trapezoid_iterator last_mid=mid_it;
    while(!!++mid_it)
    {
      
#ifdef CGAL_TD_DEBUG
      CGAL_warning(traits->is_degenerate_curve(*last_mid));
#endif
      
      last_mid->remove();
      last_mid=mid_it;
    }
    
    // remove adjacency at right end point
    
#ifdef CGAL_TD_DEBUG
    CGAL_assertion(traits->curve_is_same(cv,last_mid->top()));
    CGAL_assertion(traits->point_is_same(rightmost,t2.left()));
#endif
    
    remove_curve_at_point_using_geometry(*last_mid,t2);
    last_mid->remove();
    
    if (is_isolated_point(t1)) remove_split_trapezoid_by_point(tt1,leftmost);
    if (is_isolated_point(t2)) remove_split_trapezoid_by_point(tt2,rightmost);
    //freeing memory that was allocated for X_curve
    //delete old_cv;
    // reevaluating number of curves
    number_of_curves_--;
    
#ifdef CGAL_TD_DEBUG
   std::cout << "\nTD::remove_in_face_interior() exited with data structure" 
      << is_valid(*DS) << std::endl;
   write(std::cout,*DS,*traits) << std::endl;
#endif
    
  }
  /*
  output:
  The active trapezoid representing the input point.
  preconditions:
  The trapezoidal tree is not empty
  postcondition:
  the input locate type is set to the type of the output trapezoid.
  remarks:
  locate call may change the class
  */
  
  reference locate(const Point& p,Locate_type &t) const
  {
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_assertion(traits);
    CGAL_assertion(DS);
    
#endif
    
    Data_structure curr=*DS;
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_precondition(!!curr);
    
#endif
    
    t=search_using_data_structure(curr,traits,p,0);
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_postcondition(t == POINT || t == CURVE || t == TRAPEZOID ||
                       t == UNBOUNDED_TRAPEZOID);
    
#endif
    
#ifndef CGAL_NO_TRAPEZOIDAL_DECOMPOSITION_2_OPTIMIZATION
    
    locate_opt_push(curr.operator->());
    
#endif
    
    return *curr;
  }
  
  /* preconditions:
  p is not on an edge or a vertex.
  */
  
  curve_const_ref vertical_ray_shoot(const Point & p,Locate_type & t,
                                     const bool up_direction = true) const
  {
#ifdef CGAL_TD_DEBUG
    CGAL_assertion(traits);
#endif

    // We replace the following locate with a direct call to 
                // search_using_data_structure because we need to deal
                // with cases where the source of shoot is a point/curve.
                // reference t_p = locate(p,t);
    
    Data_structure curr=*DS;
#ifdef CGAL_TD_DEBUG
    CGAL_precondition(!!curr);
#endif

    t = search_using_data_structure(curr, traits, p, NULL, 
                                    up_direction ?
                                    CGAL::LARGER : CGAL::SMALLER);
    reference t_p = *curr;

    //std::cout << "t" << t << "\n";

#ifdef CGAL_TD_DEBUG
    CGAL_warning(t_p.get_node());
#endif
    reference tr = **t_p.get_node();

    //    std::cout << "tr" << tr << "\n";

    // tr should be non degenerate trapezoid
    /* using exact traits, it may happen that p is on the
    right side of the trapezoid directly under its
    right point(analogouly directly above its left point).
    with the trapezoid extending to the left.
    In this case vertical ray shoot upwards(downwards)
    doesn't returns c as output.
    
     Example.
     x---x
     p
     x------x
    */

    if (up_direction && !tr.is_right_unbounded() &&
        traits->point_is_same_x(p,tr.right()) && 
        (tr.is_left_unbounded() ||
         !traits->point_is_same(tr.left(),tr.right())) ||
        !up_direction && !tr.is_left_unbounded() &&
        traits->point_is_same_x(p,tr.left()) && 
        (tr.is_right_unbounded() ||
         !traits->point_is_same(tr.left(),tr.right())))
    {
      // recalculate vertical ray shoot using locate on point
      return up_direction ?
          locate(tr.right(),t).top() : locate(tr.left(),t).bottom();
    }
                curve_const_ref c = up_direction ? tr.top() : tr.bottom();
    if (up_direction ? tr.is_top_unbounded() : tr.is_bottom_unbounded())
    {
      t=UNBOUNDED_TRAPEZOID;
    }
    else
                {
                  // Now we know that the trapezoid is bounded on in the
                  // direction of the shoot.
                  t = (traits->point_is_same(p,traits->curve_source(c)) || 
                       traits->point_is_same(p,traits->curve_target(c))) ? 
                    POINT : CURVE;
                }
    return c;
  }
  
  /*    Input:
  1 whole curves
  2 partial curves
  Output:
  X_curve
  precondition:
  c          
  The first input X_curve is the union of the other two.
  The intersection of the latter is a point inside the 
  interior of the former.
  The latter are ordered from left-down to right-up
  postcondition:
  The first input X_curve is broken into two curves 
  corresponding to the input.
  The output is the degenerate point trapezoid that 
  corresponds to the splitting point.*/
  
  void split_edge(curve_const_ref cv,curve_const_ref cv1, curve_const_ref cv2)
  {
    
#ifdef CGAL_TD_DEBUG
   std::cout << "\nTD::split_edge(" << cv << "," << cv1 << "," << cv2 
     << ") called with " << (is_valid(*DS) ? "valid" : "invalid") 
     << " data structure" <<  std::endl;
   write(std::cout,*DS,*traits) << std::endl;
#endif
    
    if (needs_update_) update();
    
#ifndef CGAL_NO_TRAPEZOIDAL_DECOMPOSITION_2_OPTIMIZATION
    
    locate_opt_empty();
    
#endif
    
#ifndef CGAL_TD_DEBUG
    
    if (!traits)
    {
      CGAL_warning(traits);
      return;
    }
    if (!traits->curve_merge_condition(cv,cv1,cv2))
    {
      CGAL_warning(traits->curve_merge_condition(cv,cv1,cv2));
      return;
    }
    
#else
    
    if (!traits->curve_merge_condition(cv,cv1,cv2))
    {
      std::cerr << "\ncv " << cv;
      std::cerr << "\ncv1 " << cv1;
      std::cerr << "\ncv2 " << cv2 << std::endl;
    }
    CGAL_precondition(traits);
    CGAL_precondition(traits->curve_merge_condition(cv,cv1,cv2));
    
#endif
    
    // spliting point
    Point p = traits->point_is_same(traits->curve_target(cv1),
                                    traits->curve_source(cv2)) ?
        traits->curve_target(cv1) : traits->curve_target(cv2);
    
#ifndef CGAL_TD_DEBUG
    
    CGAL_warning(
      traits->point_is_left_low(
      traits->curve_leftlow_most(cv),p));
    
    CGAL_warning(
      traits->point_is_right_top(
      traits->curve_righttop_most(cv),p));
    
#else
    
    CGAL_precondition(
      traits->point_is_left_low(
      traits->curve_leftlow_most(cv),p));
    
    CGAL_precondition(
      traits->point_is_right_top(
      traits->curve_righttop_most(cv),p));
    
#endif
    
    // extremal points
    Point
      leftmost=traits->curve_leftlow_most(cv),
      rightmost=traits->curve_righttop_most(cv);
    Locate_type lt1,lt2;
    // representing trapezoids for extremal points
    reference
      t1=locate(leftmost,lt1),
      t2=locate(rightmost,lt2);
    
#ifndef CGAL_TD_DEBUG
    
    CGAL_warning(lt1==POINT && lt2==POINT);
    CGAL_warning(t1.is_active() && t2.is_active());

#else
    
    CGAL_precondition(lt1==POINT && lt2==POINT);
    CGAL_precondition(t1.is_active() && t2.is_active());
    CGAL_warning(t1.get_node());
    CGAL_warning(t2.get_node());
    
#endif
    
    Data_structure
      &tt1=*t1.get_node();
    In_face_iterator
      bottom_it(follow_curve(tt1,cv,SMALLER)),
      mid_it(follow_curve(tt1,cv,EQUAL)),
      top_it(follow_curve(tt1,cv,LARGER));
    Locate_type lt;
    reference old_t=locate(p,lt);
    //X_curve const * old_cv=&old_t.top();
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_assertion(lt==CURVE);
    CGAL_precondition(old_t.is_active());
    CGAL_warning(old_t.get_node());
    
#endif
    
    Data_structure
      &old_tt=*old_t.get_node();
    
    // previous left and right sons of old_tt
    const Data_structure
      &old_left=old_tt.left(),
      &old_right=old_tt.right();
    
    X_curve left_cv,right_cv;
    if (traits->point_is_same(traits->curve_leftlow_most(cv2),p))
    {
      left_cv=cv1;
      right_cv=cv2;
    }
    else
    {
      left_cv=cv2;
      right_cv=cv1;
    }
    const Data_structure
      &new_left_tt=Data_structure(X_trapezoid(old_t.left(), p, left_cv,
                                              left_cv), old_left, old_right),
      &new_right_tt=Data_structure(X_trapezoid(p, old_t.right(), right_cv,
                                               right_cv), old_left, old_right),
      &new_tt=Data_structure(X_trapezoid(p, p, left_cv, right_cv), new_left_tt,
                             new_right_tt);
    reference
      new_left_t=*new_left_tt,
      new_right_t=*new_right_tt,
      new_t=*new_tt;
    
      /* locate trapezoid trees that correspond to the closest
    trapezoids above and below p */
    pointer 
      left_top_t=top_it.operator->(),
      left_bottom_t=bottom_it.operator->();
    while(traits->point_is_left_low(left_top_t->right(),p))
      left_top_t=left_top_t->right_bottom_neighbour();
    while(traits->point_is_left_low(left_bottom_t->right(),p))
      left_bottom_t=left_bottom_t->right_top_neighbour();
    Data_structure
      left_top=*left_top_t->get_node(),
      left_bottom=*left_bottom_t->get_node();
    
    replace_curve_at_point_using_geometry(cv,left_cv,t1);
    replace_curve_at_point_using_geometry(cv,right_cv,t2);
    // the point p belongs to cv interior
    new_t.set_rt(&new_left_t);
    new_t.set_lb(&new_right_t);
    new_left_t.set_lb(old_t.left_bottom_neighbour() != &old_t ?
                      old_t.left_bottom_neighbour() : &new_left_t);
    new_left_t.set_rt(&new_right_t);
    new_right_t.set_lb(&new_left_t);
    new_right_t.set_rt(old_t.right_top_neighbour() != &old_t ?
                       old_t.right_top_neighbour() : &new_right_t);
    
    // update geometric boundary for trapezoids representing cv
    pointer prev=0;
    while(*mid_it != old_t) {
      mid_it->set_top(left_cv);
      mid_it->set_bottom(left_cv);
      mid_it->set_right(p);
      prev=mid_it.operator->();mid_it++;
    }
    if (prev)
    {
      prev->set_rb(&new_left_t);
    }
    // new_left_t is leftmost representative for cv
    else
    {
      replace_curve_at_point_using_geometry(new_left_t,t1);
    }
    if (t1.right_top_neighbour()==&old_t) t1.set_rt(&new_left_t);
    if (t1.left_bottom_neighbour()==&old_t) t1.set_lb(&new_left_t);
    mid_it++;
    new_right_t.set_rb(mid_it.operator->());
    prev=0;
    while(!!mid_it) {
      mid_it->set_top(right_cv);
      mid_it->set_bottom(right_cv);
      mid_it->set_left(p);
      prev=mid_it.operator->();
      mid_it++;
    }
    if (prev)
    {
      new_right_t.set_rb(old_t.right_bottom_neighbour());
    }
    else
      // new_right_t is rightmost representative for cv
    {
      replace_curve_at_point_using_geometry(new_right_t,t2,false);
    }
    if (t2.right_top_neighbour()==&old_t) t2.set_rt(&new_right_t);
    if (t2.left_bottom_neighbour()==&old_t) t2.set_lb(&new_right_t);
    
    /* update geometric boundary for trapezoids below cv*/
    while (*bottom_it!=*left_bottom)
    {
      
#ifdef CGAL_TD_DEBUG
      
      CGAL_assertion(traits->curve_is_same(bottom_it->top()
          ,cv));
      
#endif
      
      bottom_it->set_top(left_cv);
      bottom_it++;
    }
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_assertion(*bottom_it==*left_bottom);
    
#endif
    
    Data_structure &bottom_tt=*bottom_it->get_node();
    bottom_it++;
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_assertion(traits->is_in_closure(*bottom_tt,p));
    
#endif
    
    split_trapezoid_by_point(bottom_tt,p,left_cv,right_cv);
    // set the splitting trapezoid to be the same one that splits the 
    // X_curve'like trapezoid
    *bottom_tt=new_t;
    // update top curves
    bottom_tt.left()->set_top(left_cv);
    bottom_tt.right()->set_top(right_cv);
    // left and right are not neighbours.
    bottom_tt.left()->set_rt(0);
    bottom_tt.right()->set_lt(0);
    while(!!bottom_it)
    {
      
#ifdef CGAL_TD_DEBUG
      
      CGAL_assertion(traits->curve_is_same(bottom_it->top(),cv));
      
#endif
      
      bottom_it->set_top(right_cv);
      bottom_it++;
    }
    /* update geometric boundary for trapezoids above cv*/
    while (*top_it!=*left_top)
    {
      
#ifdef CGAL_TD_DEBUG
      
      CGAL_assertion(traits->curve_is_same(top_it->bottom(),cv));
      
#endif
      
      top_it->set_bottom(left_cv);
      top_it++;
    }
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_assertion(*top_it==*left_top);
    
#endif
    
    Data_structure &top_tt=*top_it->get_node();
    top_it++;
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_assertion(traits->is_in_closure(*bottom_tt,p));
    
#endif
    
    split_trapezoid_by_point(top_tt,p,left_cv,right_cv);
    // set the splitting trapezoid to be the same one that splits the 
    // X_curve'like trapezoid
    *top_tt=new_t;
    // update bottom side
    top_tt.left()->set_bottom(left_cv);
    top_tt.right()->set_bottom(right_cv);
    // left and right aren't neighbours
    top_tt.left()->set_rb(0);
    top_tt.right()->set_lb(0);
    while(!!top_it)
    {
      
#ifndef CGAL_TD_DEBUG
      
      CGAL_warning(traits->curve_is_same(top_it->bottom(),cv));
      
#else
      
      if (!traits->curve_is_same(top_it->bottom(),cv))
        std::cout << "\ntop_it->bottom() "<< top_it->bottom() << "\t cv= "
                  << cv;
      CGAL_assertion(traits->curve_is_same(top_it->bottom(),cv));
      
#endif
      
      top_it->set_bottom(right_cv);
      top_it++;
    }
    // mark inactive trapezoids
    old_t.remove((Data_structure*)&new_tt);
    const Data_structure
      *newPtr=&old_t.get_node()->left(),
      *newleftPtr=&newPtr->left(),
      *newrightPtr=&newPtr->right(),
      *oldleftPtr=&newleftPtr->left(),
      *oldrightPtr=&newleftPtr->right();
    (*newPtr)->set_node((Data_structure*)newPtr);
    (*newleftPtr)->set_node((Data_structure*)newleftPtr);
    (*newrightPtr)->set_node((Data_structure*)newrightPtr);
    (*oldleftPtr)->set_node((Data_structure*)oldleftPtr);
    (*oldrightPtr)->set_node((Data_structure*)oldrightPtr);
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_assertion(old_tt->is_valid(traits));
    CGAL_assertion(new_tt->is_valid(traits));
    CGAL_assertion((*newPtr)->is_valid(traits));
    CGAL_assertion((*newleftPtr)->is_valid(traits));
    CGAL_assertion((*newrightPtr)->is_valid(traits));
    CGAL_assertion((*oldleftPtr)->is_valid(traits));
    CGAL_assertion((*oldrightPtr)->is_valid(traits));
    CGAL_assertion(top_tt->is_valid(traits));
    CGAL_assertion(bottom_tt->is_valid(traits));
    CGAL_assertion(old_left->is_valid(traits));
    CGAL_assertion(old_right->is_valid(traits));
    CGAL_assertion(traits->is_degenerate_point(**newPtr));
    CGAL_assertion(traits->is_degenerate_curve(**newleftPtr));
    CGAL_assertion(traits->is_degenerate_curve(**newrightPtr));
    CGAL_assertion(
      traits->point_is_same(
      traits->curve_leftlow_most((*newrightPtr)->bottom()),
      (*newPtr)->right()
      )
      );
    CGAL_assertion(
      traits->point_is_same(
      traits->curve_righttop_most((*newleftPtr)->top()),
      (*newPtr)->left()
      )
      );
#endif
    
    // reevaluating number of curves
    number_of_curves_++;
    
#ifdef CGAL_TD_DEBUG
   std::cout << "\nTD::split_edge() exited with data structure" 
      << is_valid(*DS) << std::endl;
   write(std::cout,*DS,*traits) << std::endl;
#endif

  }
  
  void merge_edge(
    curve_const_ref cv1 ,
    curve_const_ref cv2,
    curve_const_ref cv)
  {

#ifdef CGAL_TD_DEBUG
   std::cout << "\nTD::merge_edge(" << cv1 << "," << cv2 << "," << cv 
     << ") called with " << (is_valid(*DS) ? "valid" : "invalid") 
     << " data structure" <<  std::endl;
   write(std::cout,*DS,*traits) << std::endl;
#endif

   if (needs_update_) update();
    
#ifndef CGAL_NO_TRAPEZOIDAL_DECOMPOSITION_2_OPTIMIZATION
    
    locate_opt_empty();
    
#endif
    
#ifndef CGAL_TD_DEBUG
    
    if (!traits)
    {
      CGAL_warning(traits);
      return;
    }
    if (!traits->curve_merge_condition(cv,cv1,cv2))
    {
      CGAL_warning(traits->curve_merge_condition(cv,cv1,cv2));
      return;
    }
    
#else
    if (!traits->curve_merge_condition(cv,cv1,cv2))
    {
      std::cerr << "\ncv " << cv;
      std::cerr << "\ncv1 " << cv1;
      std::cerr << "\ncv2 " << cv2 << std::endl;
    }    
    CGAL_assertion(traits);
    CGAL_precondition(traits->curve_merge_condition(cv,cv1,cv2));
    
#endif    
    Point p=
      // Calculate the common point of cv1 and cv2. 
      // There should be one!
      traits->point_is_same(traits->curve_target(cv1),
          traits->curve_source(cv2)) ? 
      traits->curve_target(cv1) : 
      // [-- cv1 -->] p [-- cv2 -->] or [<-- cv2 --] p [<-- cv1 --]
      traits->point_is_same(traits->curve_source(cv1),
          traits->curve_target(cv2)) ? 
      // [<-- cv1 --] p [<-- cv2 --] or [-- cv2 -->] p [-- cv1 -->]
      traits->curve_source(cv1) : //
      traits->point_is_same(traits->curve_source(cv1),
          traits->curve_source(cv2)) ? 
      // [<-- cv1 --] p [-- cv2 -->]
      traits->curve_source(cv1) : 
      // [-- cv1 -->] p [<-- cv2 --]
      traits->curve_target(cv1);

#ifdef CGAL_TD_DEBUG
    // p is interior to the union curve
    CGAL_precondition(
      traits->point_is_left_low(
      traits->curve_leftlow_most(cv),p
      ));
    CGAL_precondition(
      traits->point_is_right_top(
      traits->curve_righttop_most(cv),p
      ));
#endif
    
    Point
      leftmost=traits->curve_leftlow_most(cv),
      rightmost=traits->curve_righttop_most(cv);
    Locate_type lt1,lt2,lt;
    reference
      t1=locate(leftmost,lt1),
      t2=locate(rightmost,lt2),
      t=locate(p,lt);
    
#ifndef CGAL_TD_DEBUG
    
    CGAL_warning(t1.get_node());
    CGAL_warning(t2.get_node());
    CGAL_warning(t.get_node());
    
#else
    
    CGAL_precondition(lt1==POINT && lt2==POINT && lt==POINT);
    CGAL_precondition(t1.is_active() && t2.is_active() && t.is_active());
    CGAL_assertion(t1.get_node());
    CGAL_assertion(t2.get_node());
    CGAL_assertion(t.get_node());
    
#endif
    
    X_curve left_cv,right_cv;
    if (traits->point_is_same(traits->curve_leftlow_most(cv2),p))
    {
      left_cv=cv1;
      right_cv=cv2;
    }
    else
    {
      left_cv=cv2;
      right_cv=cv1;
    }
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_assertion(traits->point_is_same(
      t1.left(),leftmost
      ));
    CGAL_assertion(traits->point_is_same(
      t2.right(),rightmost
      ));
    CGAL_assertion(traits->point_is_left_low(
      leftmost,p
      ));
    CGAL_assertion(traits->point_is_left_low(
      p,rightmost
      ));
    CGAL_assertion(traits->point_is_same(
      traits->curve_leftlow_most(left_cv),leftmost
      ));
    CGAL_assertion(traits->point_is_same(
      traits->curve_righttop_most(left_cv),p
      ));
    CGAL_assertion(traits->point_is_same(
      traits->curve_leftlow_most(right_cv),p
      ));
    CGAL_assertion(traits->point_is_same(
      traits->curve_righttop_most(right_cv),rightmost
      ));
    CGAL_assertion(traits->point_is_same(
      traits->curve_leftlow_most(cv),leftmost
      ));
    CGAL_assertion(traits->point_is_same(
      traits->curve_righttop_most(cv),rightmost
      ));
    
#endif
    
    Data_structure
      &tt1=*t1.get_node(),
      &tt=*t.get_node();
    In_face_iterator
      bottom_left_it(follow_curve(tt1,left_cv,SMALLER)),
      mid_left_it(follow_curve(tt1,left_cv,EQUAL)),
      top_left_it(follow_curve(tt1,left_cv,LARGER)),
      bottom_right_it(follow_curve(tt,right_cv,SMALLER)),
      mid_right_it(follow_curve(tt,right_cv,EQUAL)),
      top_right_it(follow_curve(tt,right_cv,LARGER));
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_assertion(bottom_left_it.operator->());
    CGAL_assertion(mid_left_it.operator->());
    CGAL_assertion(top_left_it.operator->());
    CGAL_assertion(bottom_right_it.operator->());
    CGAL_assertion(mid_right_it.operator->());
    CGAL_assertion(top_right_it.operator->());
    CGAL_assertion(bottom_left_it->is_active());
    CGAL_assertion(mid_left_it->is_active());
    CGAL_assertion(top_left_it->is_active());
    CGAL_assertion(bottom_right_it->is_active());
    CGAL_assertion(mid_right_it->is_active());
    CGAL_assertion(top_right_it->is_active());
    
#endif
    
    pointer
      left=mid_left_it.operator->(),
      mid_left=0,
      mid_right=mid_right_it.operator->(),
      top_left=0,
      top_right=top_right_it.operator->(),
      bottom_left=0,
      bottom_right=bottom_right_it.operator->(),
      right=0,
      dummy=0,
      dummy2=0;
    replace_curve_using_geometry(mid_left_it,left_cv,cv,mid_left);
    replace_curve_using_geometry(mid_right_it,right_cv,cv,right);
    replace_curve_using_geometry(top_left_it,left_cv,cv,top_left);
    replace_curve_using_geometry(top_right_it,right_cv,cv,dummy);
    replace_curve_using_geometry(bottom_left_it,left_cv,cv,bottom_left);
    replace_curve_using_geometry(bottom_right_it,right_cv,cv,dummy2);
    // merge trapezoids splited by the upward and downward
    // vertical extensions from p
    
#ifndef CGAL_TD_DEBUG
    
    merge_if_possible(top_left,top_right);
    merge_if_possible(bottom_left,bottom_right);
    
#else
    
    CGAL_warning(top_left);
    CGAL_warning(top_right);
    CGAL_warning(merge_if_possible(top_left,top_right));
    CGAL_warning(bottom_left);
    CGAL_warning(bottom_right);
    CGAL_warning(merge_if_possible(bottom_left,bottom_right));
    
#endif
    
    // mark older trapezoids as inactive
    top_right->remove(top_left->get_node());
    bottom_right->remove(bottom_left->get_node());
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_warning(mid_left);
    CGAL_warning(mid_right);
    CGAL_warning(tt->is_active());
    
#endif
    
    // make p's representative inactive
    tt->remove();
    mid_left->set_rb(mid_right);
    mid_left->set_right(mid_right->right());
    mid_right->set_left(mid_left->left());
    mid_left->set_rt(0);
    mid_right->set_lb(0);
    replace_curve_at_point_using_geometry(left_cv,cv,t1);
    replace_curve_at_point_using_geometry(right_cv,cv,t2);
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_warning(left);
    CGAL_warning(right);
    
#endif
    
    replace_curve_at_point_using_geometry(*left,t1,true);
    replace_curve_at_point_using_geometry(*right,t2,false);
    // reevaluating number of curves
    number_of_curves_--;
    
#ifdef CGAL_TD_DEBUG
   std::cout << "\nTD::merge_edge() exited with data structure" 
      << is_valid(*DS) << std::endl;
   write(std::cout,*DS,*traits) << std::endl;
#endif

  }
  
  unsigned long size()
  {
    return DS->size();
  }
  unsigned long depth()
  {
    return DS->depth();
  }  
  unsigned long number_of_curves()
  {
    return number_of_curves_;
  }
  void init_traits(Traits* t)
  {
    traits = t;
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_assertion(!!*DS);
    
#endif
    
  }
  
  /* update geometric boundary(top and bottom) for trapezoids
  traveled along an iterator till end reached
  precondition:
  end==0 or end is on the path of the iterator
  postcondition:
  end is pointer to the last trapezoid encountered,if any
  */
  /*------------------------------------------------------------------
  description:
  returns whether the Trapezoidal Dag is valid
  */
  
#ifdef CGAL_TD_DEBUG
  
  bool is_valid(const Data_structure& ds) const
  {
    return !ds || ds->is_valid(traits) && ds->get_node() &&
        is_valid(ds.left()) && is_valid(ds.right());
  }
  
  /*------------------------------------------------------------------
  description:
  returns whether the member Trapezoidal data structure is valid
  */
  bool is_valid() const
  {
    return is_valid(*DS);
  }
  
  void debug()
  {
    std::cout << "\nTrapezoidal_decomposition_2<Traits>::debug()\n" << *this
              << std::endl;
    X_trapezoid x;
    x.debug();
  }
  
#endif
  
/*------------------------------------------------------------------
description:
  Rebuilds the trapezoid data structure by reinserting the curves 
  in a random order in an empty data structure.

postcondition:
  The old and new data structures agree on their member curves.
------------------------------------------------------------------*/
  Self& rebuild()
  {
#ifdef CGAL_TD_DEBUG
    std::cout << "\nrebuild()" << std::flush;
#endif
    
    X_curve_container content;
    unsigned long rep = container(content);
    clear();

    // initialize content to point to curves in X_trapezoid Tree
    if (rep>0)
    {
      bool o=set_needs_update(false);
      typename std::vector<X_curve>::iterator it = content.begin(),
          it_end = content.end();
      while(it!=it_end) 
      {
        insert(*it);
        ++it;
      }
      set_needs_update(o);
    }
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_assertion(is_valid());
    unsigned long sz=number_of_curves();
    if(sz!=rep)
      {
        std::cerr << "\nnumber_of_curves()=" << sz;
        std::cerr << "\nrepresentatives.size()=" << rep;
        CGAL_assertion(number_of_curves()==rep);
      }
    
#endif
    
    content.clear();
    return *this;
  }
  
  /* 
     Input:  
     a list of pointers to X_trapezoids and a X_trapezoid boolean predicate.
     Output: 
     void
     Postcondition:
     the list pointers correspond to all the X_trapezoids in the data
     structure for which the predicate value is true. 
  */
  
  template <class Container,class Predicate>
  void container(Container& c, const Predicate& pr) const
  {
    DS->filter(c,pr);
  }
  unsigned long container(X_curve_container& content)
  {
    unsigned long sz=number_of_curves();
    list_container representatives;
    container(representatives,
              Active_right_degenerate_curve_trapezoid(*traits));
    
#ifndef CGAL_TD_DEBUG
    
    CGAL_warning(sz==representatives.size());
    
#else
    
    unsigned long rep=representatives.size();
    if (sz!=rep)
    {
      std::cerr << "\nnumber_of_curves()=" << sz;
      std::cerr << "\nrepresentatives.size()=" << rep;
      CGAL_assertion(number_of_curves()==representatives.size());
    }
    
#endif
    
    if (sz>0)
    {
      typename list_container::iterator it = representatives.begin(),
          it_end = representatives.end();
      while(it!=it_end)
      {
        content.push_back(it->top());
        ++it;
      }
    }
    std::random_shuffle(content.begin(),content.end());
    return sz;
}
    
    
    
    /*------------------------------------------------------------------
    Input:
    None
    Output:
    bool
    Description:
    determines according to pre defined conditions whether the
    current Trapezoidal_decomposition_2<Traits> needs update
    Postconditions:
    The output is true iff the depth of the Trapezoidal Tree is more then
    DepthThreshold times log of the X_curve count or the Trapezoidal Tree's
    size 
    is more then SizeThreshold times the log of the last count.
    */
    bool set_needs_update(bool u)
    {
      bool old=needs_update_;
      needs_update_=u;
      return old;
    }
    bool needs_update()
    {
      unsigned long sz = number_of_curves();
      //to avoid signed / unsigned conversion warnings
                        // rand() returns an int but a non negative one.
      if (static_cast<unsigned long>(rand()) > 
                            RAND_MAX / (sz+1))
                          return false;
      /*       INTERNAL COMPILER ERROR overide
      #ifndef __GNUC__
      */
#ifdef CGAL_TD_REBUILD_DEBUG
      std::cout << "\n|heavy!" << std::flush;
#endif
      return
        depth()>(get_depth_threshold()*(CGAL_CLIB_STD::log(double(sz+1))))
        || size()>(get_size_threshold()*(sz+1));
        /*
        #else
        // to avoid comparison between signed and unsigned
        return ((depth()/10)>log(sz+1))||((size()/10)>(sz+1));
        //return ((((signed)depth())/10)>log(sz+1))||
        ((((signed)size())/10)>(sz+1));
        
         #endif
      */
    }
    
    /*------------------------------------------------------------------
    input:
    None
    output:
    bool
    Description:
    uses needs_update to determine whether the
    Trapezoidal_decomposition_2<Traits> needs update
    and calls rebuild accordingly
    Postcondition:
    the return value is true iff rebuilding took place.
    */
    bool update()
    {
#ifdef CGAL_TD_REBUILD_DEBUG
      std::cout << "\n|" << needs_update() << std::flush;
#endif
      if (needs_update()) {rebuild();return true;}
      
      return false;
    }
    
/* returns a reference to the internal data structure */
    const Data_structure& get_data_structure() const {return *DS;}

/* returns a reference to the internal data structure */
    const Traits& get_traits() const {return *traits;}

/* returns a reference to the internal depth threshold constant */
    const double& get_depth_threshold() const
    {
      return depth_threshold;
    }
/* returns a reference to the internal size threshold constant */
    const double& get_size_threshold() const
    {
      return size_threshold;
    }
/* sets the internal depth threshold constant to the parameter and 
  returns its reference */
    const double& set_depth_threshold(const double& depth_th)
    {
      return depth_threshold=depth_th;
    }

/* sets the internal size threshold constant to the parameter and 
  returns its reference */
    const double& set_size_threshold(const double& size_th)
    {
      return size_threshold=size_th;
    }
protected:
  Data_structure* DS;
  bool needs_update_;
  unsigned long number_of_curves_;
  Traits* traits;
  
private:
  
#ifndef CGAL_NO_TRAPEZOIDAL_DECOMPOSITION_2_OPTIMIZATION
  
  mutable pointer last_cv,prev_cv;
  
#endif
  
  void init()
  {
    // traits may be initialized later
    DS = new Data_structure(X_trapezoid());
    (*DS)->set_node(DS);
    
    
    
    /*    Point tmp;
    if (!traits->point_is_left_low(TD_X_trapezoid<Traits,
    X_curve>::POINT_AT_LEFT_TOP_INFINITY,tmp=TD_X_trapezoid<Traits,
    X_curve>::POINT_AT_RIGHT_BOTTOM_INFINITY))
    TD_X_trapezoid<Traits,
    X_curve>::POINT_AT_LEFT_TOP_INFINITY=traits->point_to_left(tmp);
    */
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_warning(!!*DS);
    
#endif
    
    number_of_curves_=0;
    
#ifndef CGAL_NO_TRAPEZOIDAL_DECOMPOSITION_2_OPTIMIZATION
    
    locate_opt_empty();
    
#endif
    
  }
  
#ifndef CGAL_NO_TRAPEZOIDAL_DECOMPOSITION_2_OPTIMIZATION
  
  void locate_opt_push(pointer cv) const
  {
    prev_cv=last_cv;
    last_cv=cv;
  }
  void locate_opt_empty() const
  {
    last_cv=prev_cv=0;
  }
  bool locate_opt_swap(pointer& cv) const
  {
    cv=last_cv;
    last_cv=prev_cv;
    prev_cv=cv;
    return (cv!=0);
  }
  void locate_optimization(const Point& p,pointer& tr,Locate_type& lt) const
  {
    // optimization
    if (locate_opt_swap(tr)&&tr->is_active()&&
        (traits->is_degenerate_point(*tr)&&
         traits->point_is_same(tr->left(),p)||
         !traits->is_degenerate(*tr)&&
         traits->is_inside(*tr,p)
         )||
        locate_opt_swap(tr)&&tr->is_active()&&
        (traits->is_degenerate_point(*tr)&&
         traits->point_is_same(tr->left(),p)||
         !traits->is_degenerate(*tr)&&
         traits->is_inside(*tr,p)
         )
        )
      if(traits->is_degenerate_point(*tr)) lt=POINT;
      else lt=tr->is_unbounded()?UNBOUNDED_TRAPEZOID:TRAPEZOID;
    else
      tr=&locate(p,lt);
  }
  
#endif

protected:
  bool is_isolated_point(const_ref tr) const
  {
    
#ifdef CGAL_TD_DEBUG
    
    CGAL_precondition(traits->is_degenerate_point(tr));
    
#endif
    
    return !tr.right_top_neighbour()&&!tr.left_bottom_neighbour();
  }

protected:
  double depth_threshold,size_threshold;
};

CGAL_END_NAMESPACE

#ifndef CGAL_TD_X_TRAPEZOID_H
#include <CGAL/Td_X_trapezoid.h>
#endif

#ifdef CGAL_TD_DEBUG
#ifndef CGAL_TRAPEZOIDAL_DECOMPOSITION_2_IOSTREAM_H
#include <CGAL/IO/Trapezoidal_decomposition_2_iostream.h>
#endif
#endif

#endif// CGAL_TRAPEZOIDAL_DECOMPOSITION_2_H