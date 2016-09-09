// ======================================================================
//
// Copyright (c) 2000,2001 The CGAL Consortium

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
// file          : include/CGAL/Kernel_d/VectorHd.h
// package       : Kernel_d (0.9.68)
// revision      : $Revision: 1.9 $
// revision_date : $Date: 2002/03/18 20:34:02 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_VECTORHD_H
#define CGAL_VECTORHD_H 

#ifndef NOCGALINCL
#include <CGAL/basic.h>
#include <CGAL/Quotient.h>
#endif
#include <CGAL/Kernel_d/Tuple_d.h> 
#include <CGAL/Kernel_d/PointHd.h>
#include <CGAL/Kernel_d/Aff_transformationHd.h>

CGAL_BEGIN_NAMESPACE
#define PointHd PointHd2

template <class RT, class LA> class VectorHd;
template <class RT, class LA>
std::istream& operator>>(std::istream&, VectorHd<RT,LA>&);
template <class RT, class LA>
std::ostream& operator<<(std::ostream&, const VectorHd<RT,LA>&);

/*{\Manpage {Vector_d}{R}{Vectors in d-space}{v}}*/
/*{\Msubst 
Hd<RT,LA>#_d<R>
VectorHd#Vector_d
PointHd#Point_d
Quotient<RT>#FT
}*/

template <class _RT, class _LA>
class VectorHd : public Handle_for< Tuple_d<_RT,_LA> > { 
  typedef Tuple_d<_RT,_LA>  Tuple;
  typedef Handle_for<Tuple> Base;
  typedef VectorHd<_RT,_LA> Self;

/*{\Mdefinition
An instance of data type |\Mname| is a vector of Euclidean space in
dimension $d$. A vector $r = (r_0,\ldots,r_{ d - 1})$ can be represented
in homogeneous coordinates $(h_0,\ldots,h_d)$ of number type |RT|,
such that $r_i = h_i/h_d$ which is of type |FT|. We call the
$r_i$'s the Cartesian coordinates of the vector. The homogenizing
coordinate $h_d$ is positive.

This data type is meant for use in computational geometry. It realizes
free vectors as opposed to position vectors (type |PointHd|). The
main difference between position vectors and free vectors is their
behavior under affine transformations, e.g., free vectors are
invariant under translations.}*/

const typename _LA::Vector& vector_rep() const { return ptr()->v; }
_RT& entry(int i) { return ptr()->v[i]; }
const _RT& entry(int i) const { return ptr()->v[i]; }
void invert_rep() { ptr()->invert(); }
VectorHd(const Base& b) : Base(b) {}

public: 
/*{\Mtypes 4}*/

typedef _RT RT;
/*{\Mtypemember the ring type.}*/
typedef Quotient<_RT> FT;
/*{\Mtypemember the field type.}*/
typedef _LA LA;
/*{\Mtypemember the linear algebra layer.}*/
typedef typename Tuple::Cartesian_const_iterator Cartesian_const_iterator;
/*{\Mtypemember a read-only iterator for the Cartesian coordinates.}*/
typedef typename Tuple::const_iterator Homogeneous_const_iterator;
/*{\Mtypemember a read-only iterator for the homogeneous coordinates.}*/

class Base_vector {};
/*{\Mtypemember construction tag.}*/

friend class PointHd<RT,LA>; 
friend class DirectionHd<RT,LA>; 
friend class HyperplaneHd<RT,LA>; 

/*{\Mcreation 4}*/

VectorHd(int d = 0) : Base( Tuple(d+1) )  
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname| in 
$d$-dimensional space.}*/
{ if ( d > 0 ) entry(d) = 1; }

VectorHd(int d, Null_vector) : Base( Tuple(d+1) )  
/*{\Mcreate introduces the zero vector |\Mvar| of type |\Mname| in 
$d$-dimensional space. There is a constant |CGAL::NULL_VECTOR| that
can be used for the second argument.}*/
{ if ( d > 0 ) entry(d) = 1; }

#ifndef CGAL_SIMPLE_INTERFACE

template <class InputIterator>
VectorHd(int d, InputIterator first, InputIterator last) :
  Base( Tuple(d+1,first,last) )
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname| in dimension |d|.
If |size [first,last) == d| this creates a vector with Cartesian coordinates 
|set [first,last)|. If |size [first,last) == p+1| the range specifies the
homogeneous coordinates $|H = set [first,last)| = (\pm h_0, \pm h_1, \ldots,
\pm h_d)$ where the sign chosen is the sign of $h_d$.
\precond |d| is nonnegative, |[first,last)| has |d| or |d+1| elements where the
last has to be non-zero, and the value type of |InputIterator| is |RT|.}*/
{ RT D = entry(d);
  CGAL_assertion_msg(first!=last || D!=RT(0),
    "VectorHd::constructor: denominator must be nonzero.");
  if ( D == RT(0) ) entry(d) = 1;
  if ( D < RT(0) ) invert_rep();
}

template <class InputIterator>
VectorHd(int d, InputIterator first, InputIterator last, 
         const RT& D) : Base( Tuple(d+1,first,last,D) )
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname|
in dimension |d| initialized to the vector with homogeneous 
coordinates as defined by |H = set [first,last)| and |D|:
$(\pm |H[0]|, \pm|H[1]|, \ldots, \pm|H[d-1]|, \pm|D|)$. The sign chosen 
is the sign of $D$. \precond |D| is non-zero, the iterator range defines 
a $d$-tuple of |RT|, and the value type of |InputIterator| is |RT|. }*/
{ CGAL_assertion_msg(D!=RT(0), "VectorHd::constructor: D must be nonzero.");
  if (D < RT(0)) invert_rep();
}

#else
#define FIXVECHD(I) \
VectorHd(int d, I first, I last) : Base( Tuple(d+1,first,last) ) \
{ RT D = entry(d); \
  CGAL_assertion_msg(first!=last || D!=RT(0),\
    "VectorHd::constructor: denominator must be nonzero.");\
  if ( D == RT(0) ) entry(d) = 1; if ( D < RT(0) ) invert_rep();\
} \
VectorHd(int d, I first, I last, const RT& D):Base(Tuple(d+1,first,last,D))\
{ CGAL_assertion_msg(D!=RT(0), "VectorHd::constructor: D must be nonzero.");\
  if (D < RT(0)) invert_rep();\
}

FIXVECHD(int*)
FIXVECHD(const int*)
FIXVECHD(RT*)
FIXVECHD(const RT*)
#undef FIXVECHD
#endif

VectorHd(int d, Base_vector, int i) : Base( Tuple(d+1) )
/*{\Mcreate returns a variable |\Mvar| of type |\Mname| initialized  
to the $i$-th base vector of dimension $d$. }*/
{ entry(d) = 1;
  if ( d == 0 ) return;
  CGAL_assertion_msg((0<=i&&i<d),"VectorHd::base: index out of range.");
  entry(i) = 1;
}

VectorHd(const RT& x, const RT& y, const RT& w = 1) 
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname| in 
$2$-dimensional space. }*/
 : Base( Tuple(x,y,w) ) 
{ CGAL_assertion_msg((w != 0), "VectorHd::construction: w == 0.");
  if (w < 0) invert_rep();
}

VectorHd(int a, int b, int c = 1) : 
  Base( Tuple((RT)a,(RT)b,(RT)c) ) 
{ CGAL_assertion_msg((c != 0), "VectorHd::construction: w == 0.");
  if (c < 0) invert_rep();
}

VectorHd(const RT& x, const RT& y, const RT& z, const RT& w) 
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname| in 
$3$-dimensional space. }*/
  : Base( Tuple((RT)x,(RT)y,(RT)z,(RT)w) )
{ CGAL_assertion_msg((w!=0), "VectorHd::construction: w == 0.");
  if (w < 0) invert_rep();
}

VectorHd(int a, int b, int c, int d) :
  Base( Tuple((RT)a,(RT)b,(RT)c,(RT)d) )
{ CGAL_assertion_msg((d!=0), "VectorHd::construction: w == 0.");
  if (d < 0) invert_rep();
}

VectorHd(const VectorHd<RT,LA>& p) : Base(p)  {}
~VectorHd() {}     

/*{\Moperations 5 3 }*/

int dimension() const { return ptr()->size()-1; } 
/*{\Mop returns the dimension of |\Mvar|. }*/ 

Quotient<RT> cartesian(int i) const 
/*{\Mop returns the $i$-th Cartesian coordinate of |\Mvar|. 
   \precond $0 \leq i < d$.}*/
{ CGAL_assertion_msg((0<=i && i<(dimension())), "VectorHd::cartesian():\
  index out of range.");
  return Quotient<RT>(entry(i), entry(dimension())); 
}

Quotient<RT> operator[](int i) const { return cartesian(i); }
/*{\Marrop returns the $i$-th Cartesian coordinate of |\Mvar|.
   \precond $0 \leq i < d$.}*/

RT homogeneous(int i) const 
/*{\Mop returns the $i$-th homogeneous coordinate of |\Mvar|. 
   \precond $0 \leq i \leq d$.}*/
{ CGAL_assertion_msg((0<=i && i<=(dimension())), "VectorHd::homogeneous():\
  index out of range.");
  return entry(i);
}

Quotient<RT> squared_length() const
/*{\Mop returns the square of the length of |\Mvar|. }*/
{ RT nom = 0; 
  for (int i = 0; i < dimension(); i++) 
    nom += CGAL_NTS square(homogeneous(i));
  RT denom = CGAL_NTS square(homogeneous(dimension()));
  return Quotient<RT>(nom,denom); 
}

Cartesian_const_iterator cartesian_begin() const 
/*{\Mop returns an iterator pointing to the zeroth Cartesian coordinate 
of |\Mvar|. }*/
{ return Cartesian_const_iterator(ptr()->begin(),ptr()->last()); }

Cartesian_const_iterator cartesian_end() const 
/*{\Mop returns an iterator pointing beyond the last Cartesian coordinate 
of |\Mvar|. }*/
{ return Cartesian_const_iterator(ptr()->last(),ptr()->last()); }

Homogeneous_const_iterator homogeneous_begin() const 
/*{\Mop returns an iterator pointing to the zeroth homogeneous coordinate 
of |\Mvar|. }*/
{ return ptr()->begin(); }

Homogeneous_const_iterator homogeneous_end() const 
/*{\Mop returns an iterator pointing beyond the last homogeneous
coordinate of |\Mvar|. }*/ 
{ return ptr()->end(); }

inline PointHd<RT,LA> to_point() const;

inline DirectionHd<RT,LA> direction() const; 
/*{\Mop returns the direction of |\Mvar|. }*/

VectorHd<RT,LA> transform(const Aff_transformationHd<RT,LA>& t) const; 
/*{\Mop returns $t(v)$. }*/
/*{\Mtext \headerline{Arithmetic Operators, Tests and IO}}*/

VectorHd<RT,LA> scale(const RT& m, const RT& n) const 
{ int d = dimension(); 
  VectorHd<RT,LA> result(d); 
  result.entry(d) = entry(d) * n; 
  for (int i = 0; i < d; i++) 
    result.entry(i) = entry(i) * m; 
  return result; 
}

void self_scale(const RT& m, const RT& n) 
{ int d = dimension(); 
  copy_on_write();
  entry(d) *= n; 
  for (int i = 0; i < d; i++) entry(i) *= m; 
}

VectorHd<RT,LA>& operator*=(const RT& n) 
/*{\Mbinop  multiplies all Cartesian coordinates by |n|.}*/
{ self_scale(n,1); return *this; }

VectorHd<RT,LA>& operator*=(int n) 
{ self_scale(n,1); return *this; }

VectorHd<RT,LA>& operator*=(const Quotient<RT>& r) 
/*{\Mbinop  multiplies all Cartesian coordinates by |r|.}*/
{ self_scale(r.numerator(),r.denominator()); return *this; }

VectorHd<RT,LA> operator/(int n) const
{ return scale(1,n); }

VectorHd<RT,LA> operator/(const RT& n) const
/*{\Mbinop returns the vector with Cartesian coordinates 
$v_i/n, 0 \leq i < d$.}*/
{ return scale(1,n); }

VectorHd<RT,LA> operator/(const Quotient<RT>& r) const
/*{\Mbinop returns the vector with Cartesian coordinates 
$v_i/r, 0 \leq i < d$.}*/
{ return scale(r.denominator(),r.numerator()); }

VectorHd<RT,LA>& operator/=(const RT& n) 
{ self_scale(1,n); return *this; }
/*{\Mbinop divides all Cartesian coordinates by |n|.}*/

VectorHd<RT,LA>& operator/=(int n) 
{ self_scale(1,n); return *this; }

VectorHd<RT,LA>& operator/=(const Quotient<RT>& r) 
{ self_scale(r.denominator(),r.numerator()); return *this; }
/*{\Mbinop divides all Cartesian coordinates by |r|.}*/

Quotient<RT> 
operator* (const VectorHd<RT,LA>& w) const
/*{\Mbinop inner product, i.e., $\sum_{ 0 \le i < d } v_i w_i$, 
where $v_i$ and $w_i$ are the Cartesian coordinates of $v$ and $w$ 
respectively. }*/
{ int d = dimension(); 
  CGAL_assertion_msg((d==w.dimension()),
    "inner product: dimensions disagree."); 
  RT nom = 0; 
  for (int i = 0; i < d; i++) 
    nom += homogeneous(i) * w.homogeneous(i); 
  RT denom = homogeneous(d) * w.homogeneous(d); 
  return Quotient<RT>(nom,denom); 
}

VectorHd<RT,LA> operator+(const VectorHd<RT,LA>& w) const 
/*{\Mbinop returns the vector with Cartesian coordinates 
$v_i+w_i, 0 \leq i < d$.}*/
{ VectorHd<RT,LA> res(dimension()); 
  res.ptr()->homogeneous_add(ptr(), w.ptr()); 
  return res; 
}

VectorHd<RT,LA>& operator+=(const VectorHd<RT,LA>& w) 
/*{\Mbinop addition plus assignment.}*/
{ int d = dimension(); 
  VectorHd<RT,LA> old(*this); 
  *this = VectorHd<RT,LA>(d); 
  ptr()->homogeneous_add(old.ptr(), w.ptr()); 
  return *this; 
}

VectorHd<RT,LA> operator-(const VectorHd<RT,LA>& w) const 
/*{\Mbinop returns the vector with Cartesian coordinates 
$v_i-w_i, 0 \leq i < d$.}*/
{ VectorHd<RT,LA> res(dimension()); 
  res.ptr()->homogeneous_sub(ptr(), w.ptr()); 
  return res; 
}

VectorHd<RT,LA>& operator-=(const VectorHd<RT,LA>& w) 
/*{\Mbinop subtraction plus assignment.}*/
{ int d = dimension(); 
  VectorHd<RT,LA> old(*this); 
  *this = VectorHd<RT,LA>(d); 
  ptr()->homogeneous_sub(old.ptr(), w.ptr()); 
  return *this; 
}

VectorHd<RT,LA> operator-() const 
/*{\Munop returns the vector in opposite direction.}*/
{ VectorHd<RT,LA> result(*this); 
  result.copy_on_write(); // creates a copied object!
  result.ptr()->invert(dimension()); 
  return result; 
}

static Comparison_result cmp(
  const VectorHd<RT,LA>& x, const VectorHd<RT,LA>& y) 
{ Compare_homogeneously<RT,LA> cmpobj;
  return cmpobj(x.vector_rep(),y.vector_rep());
}

bool operator==(const VectorHd<RT,LA>& w) const
{ if ( identical(w) ) return true;
  if ( dimension() != w.dimension() ) return false;
  return cmp(*this,w) == EQUAL; 
}

bool operator!=(const VectorHd<RT,LA>& w) const
{ return !operator==(w); }

bool  is_zero() const
/*{\Mop returns true if |\Mvar| is the zero vector. }*/
{ for (int i = 0; i < dimension(); i++)
    if  ( homogeneous(i) != RT(0) ) return false;
  return true;
}

/*{\Mtext \headerline{Downward compatibility}
We provide all operations of the lower dimensional interface |x()|, |y()|,
|z()|, |hx()|, |hy()|, |hz()|, |hw()|.}*/
RT hx() const { return homogeneous(0); }
RT hy() const { return homogeneous(1); }
RT hz() const { return homogeneous(2); }
RT hw() const { return homogeneous(dimension()); }
Quotient<RT> x()  const { return Quotient<RT>(hx(),hw());}
Quotient<RT> y()  const { return Quotient<RT>(hy(),hw());}
Quotient<RT> z()  const { return Quotient<RT>(hz(),hw());}

friend std::istream& operator>> CGAL_NULL_TMPL_ARGS 
  (std::istream& I, VectorHd<RT,LA>& v);
friend std::ostream& operator<< CGAL_NULL_TMPL_ARGS 
  (std::ostream& O, const VectorHd<RT,LA>& v);

}; // end of class VectorHd


template <class RT, class LA>
VectorHd<RT,LA> operator*(const int& n, const VectorHd<RT,LA>& v) 
{ return v.scale(n,1); }

template <class RT, class LA>
VectorHd<RT,LA> operator*(const RT& n, const VectorHd<RT,LA>& v) 
/*{\Mbinopfunc returns the vector with Cartesian coordinates $n v_i$.}*/
{ return v.scale(n,1); }

template <class RT, class LA>
VectorHd<RT,LA> operator*(const Quotient<RT>& r, const VectorHd<RT,LA>& v)
/*{\Mbinopfunc returns the vector with Cartesian coordinates 
$r v_i, 0 \leq i < d$.}*/
{ return v.scale(r.numerator(),r.denominator()); }


/*{\Mimplementation 
Vectors are implemented by arrays of variables of type |RT|.  All
operations like creation, initialization, tests, vector arithmetic,
input and output on a vector $v$ take time $O(|v.dimension()|)$. 
coordinate access, |dimension()| and conversions
take constant time.  The space requirement of a vector is
$O(|v.dimension()|)$.}*/



#undef PointHd
CGAL_END_NAMESPACE
#endif // CGAL_VECTORHD_H 
//----------------------- end of file ----------------------------------