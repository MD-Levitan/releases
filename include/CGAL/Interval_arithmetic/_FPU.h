// ======================================================================
//
// Copyright (c) 1998,1999,2000 The CGAL Consortium

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
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Interval_arithmetic/_FPU.h
// package       : Interval_arithmetic (4.58)
// revision      : $Revision: 2.69 $
// revision_date : $Date: 2000/09/07 11:39:38 $
// author(s)     : Sylvain Pion
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_FPU_H
#define CGAL_FPU_H

// This file specifies some platform dependant functions, regarding the FPU
// directed rounding modes.  There is only support for double precision.
//
// It also contains the definition of the Protect_FPU_rounding<> classes,
// a helper class which is a nice way to protect blocks of code needing a
// particular rounding mode.

#ifdef __linux__
#include <fpu_control.h>
#elif defined __SUNPRO_CC || (defined __KCC && defined __sun)
#include <ieeefp.h>
#elif defined __osf || defined __osf__ || defined __BORLANDC__
#include <float.h>
#elif defined __sgi
    // The 3 C functions provided on IRIX 6.5 do not work !
    // So we use precompiled (by gcc) object files linked into libCGAL.
    // See revision 2.23 for the old code.
extern "C" {
  void CGAL_workaround_IRIX_set_FPU_cw (int);
  int  CGAL_workaround_IRIX_get_FPU_cw (void);
}
#endif

// See below for explanation.  This must be outside namespace CGAL.
#ifdef _MSC_VER
extern "C" { double CGAL_ms_sqrt(double); }
#endif

CGAL_BEGIN_NAMESPACE

// Some useful constants
#define CGAL_IA_MIN_DOUBLE (5e-324) // subnormal
#define CGAL_IA_MAX_DOUBLE (1.7976931348623157081e+308)

// Inline function to stop compiler optimization.
inline double IA_force_to_double(double x)
{
#ifdef __GNUG__
  asm("" : "=m"(x) : "m"(x));  // Portable assembly :)
  return x;
#else
  volatile double e = x;
  return e;
#endif
}

// The x86 processor keeps too wide exponents (15bits) in registers, even in
// double precision mode !  It's a problem when the intervals overflow or
// underflow.  To work around that, we store the variable to memory when
// needed, using the macro below.
// Another possible workaround would be to use intervals of "long doubles"
// directly, but I think it would be much slower.
#if !defined (CGAL_IA_NO_X86_OVER_UNDER_FLOW_PROTECT) && \
    (defined __i386__ || defined _MSC_VER || defined __BORLANDC__)
#  define CGAL_IA_FORCE_TO_DOUBLE(x) CGAL::IA_force_to_double(x)
#else
#  define CGAL_IA_FORCE_TO_DOUBLE(x) (x)
#endif // __i386__

// We sometimes need to stop constant propagation,
// because operations are done with a wrong rounding mode at compile time.
// G++ also uses __builtin_constant_p().
#ifndef CGAL_IA_DONT_STOP_CONSTANT_PROPAGATION
#  ifdef __GNUG__
	// Note : GCC 2.96 seems to have "issues" with this now (august'00).
#    define CGAL_IA_STOP_CPROP(x) \
            (__builtin_constant_p (x) ? CGAL::IA_force_to_double(x) : (x) )
#    define CGAL_IA_STOP_CPROP2(x,y) \
            (__builtin_constant_p (y) ? CGAL_IA_STOP_CPROP(x) : (x) )
#  else
#    define CGAL_IA_STOP_CPROP(x)    CGAL::IA_force_to_double(x)
#    define CGAL_IA_STOP_CPROP2(x,y) CGAL::IA_force_to_double(x)
#  endif
#else
#  define CGAL_IA_STOP_CPROP(x)    (x)
#  define CGAL_IA_STOP_CPROP2(x,y) (x)
#endif

// std::sqrt(double) on VC++ and CygWin is buggy when not optimizing.
#ifdef _MSC_VER
#  define CGAL_BUG_SQRT(d) CGAL_ms_sqrt(d)
#elif defined __CYGWIN__
inline double IA_bug_sqrt(double d)
{
  double r;
  asm volatile ("fsqrt" : "=t"(r) : "0"(d));
  return r;
}
#  define CGAL_BUG_SQRT(d) CGAL::IA_bug_sqrt(d)
#else
#  define CGAL_BUG_SQRT(d) CGAL_CLIB_STD::sqrt(d)
#endif

// Here are the operator macros that make use of the above.
// With __GNUG__, we can do slightly better : test with __builtin_constant_p()
// that both arguments are constant before stopping one of them.
// Use inline functions instead ?
#define CGAL_IA_ADD(a,b) CGAL_IA_FORCE_TO_DOUBLE((a)+CGAL_IA_STOP_CPROP2(b,a))
#define CGAL_IA_SUB(a,b) CGAL_IA_FORCE_TO_DOUBLE((a)-CGAL_IA_STOP_CPROP2(b,a))
#define CGAL_IA_MUL(a,b) CGAL_IA_FORCE_TO_DOUBLE((a)*CGAL_IA_STOP_CPROP2(b,a))
#define CGAL_IA_DIV(a,b) CGAL_IA_FORCE_TO_DOUBLE((a)/CGAL_IA_STOP_CPROP2(b,a))
#define CGAL_IA_SQUARE(a) CGAL_IA_MUL(a,a)
#define CGAL_IA_SQRT(a) \
        CGAL_IA_FORCE_TO_DOUBLE(CGAL_BUG_SQRT(CGAL_IA_STOP_CPROP(a)))

#ifdef __STD_IEC_559__
// This is a version for the ISO C99 standard, which aims at portability.
// It should work with GNU libc 2.1.  Not tested yet.
#define CGAL_IA_SETFPCW(CW) fesetround(CW)
#define CGAL_IA_GETFPCW(CW) CW = fegetround()
typedef int FPU_CW_t;
#define CGAL_FE_TONEAREST    FE_TONEAREST
#define CGAL_FE_TOWARDZERO   FE_TOWARDZERO
#define CGAL_FE_UPWARD       FE_UPWARD
#define CGAL_FE_DOWNWARD     FE_DOWNWARD

#elif defined __i386__
// The GNU libc version (cf powerpc) is nicer, but doesn't work on libc 5 :(
// This one also works with CygWin.
#define CGAL_IA_SETFPCW(CW) asm volatile ("fldcw %0" : :"m" (CW))
#define CGAL_IA_GETFPCW(CW) asm volatile ("fnstcw %0" : "=m" (CW))
typedef unsigned short FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x000 | 0x127f)
#define CGAL_FE_TOWARDZERO   (0xc00 | 0x127f)
#define CGAL_FE_UPWARD       (0x800 | 0x127f)
#define CGAL_FE_DOWNWARD     (0x400 | 0x127f)

#elif defined __powerpc__
#define CGAL_IA_SETFPCW(CW) _FPU_SETCW(CW)
#define CGAL_IA_GETFPCW(CW) _FPU_GETCW(CW)
typedef fpu_control_t FPU_CW_t;
#define CGAL_FE_TONEAREST    (_FPU_RC_NEAREST | _FPU_DEFAULT)
#define CGAL_FE_TOWARDZERO   (_FPU_RC_ZERO    | _FPU_DEFAULT)
#define CGAL_FE_UPWARD       (_FPU_RC_UP      | _FPU_DEFAULT)
#define CGAL_FE_DOWNWARD     (_FPU_RC_DOWN    | _FPU_DEFAULT)

#elif defined __SUNPRO_CC || (defined __KCC && defined __sun)
#define CGAL_IA_SETFPCW(CW) fpsetround(fp_rnd(CW))
#define CGAL_IA_GETFPCW(CW) CW = fpgetround()
typedef unsigned int FPU_CW_t;
#define CGAL_FE_TONEAREST    FP_RN
#define CGAL_FE_TOWARDZERO   FP_RZ
#define CGAL_FE_UPWARD       FP_RP
#define CGAL_FE_DOWNWARD     FP_RM

#elif defined __sparc__
#define CGAL_IA_SETFPCW(CW) asm volatile ("ld %0,%%fsr" : :"m" (CW))
#define CGAL_IA_GETFPCW(CW) asm volatile ("st %%fsr,%0" : "=m" (CW))
typedef unsigned int FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x0        | 0x20000000 | 0x1f)
#define CGAL_FE_TOWARDZERO   (0x40000000 | 0x20000000 | 0x1f)
#define CGAL_FE_UPWARD       (0x80000000 | 0x20000000 | 0x1f)
#define CGAL_FE_DOWNWARD     (0xc0000000 | 0x20000000 | 0x1f)

#elif defined __sgi
#define CGAL_IA_SETFPCW(CW) CGAL_workaround_IRIX_set_FPU_cw(CW)
#define CGAL_IA_GETFPCW(CW) CW = CGAL_workaround_IRIX_get_FPU_cw()
typedef unsigned int FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x0)
#define CGAL_FE_TOWARDZERO   (0x1)
#define CGAL_FE_UPWARD       (0x2)
#define CGAL_FE_DOWNWARD     (0x3)

#elif defined __mips__ // && !defined __sgi
#define CGAL_IA_SETFPCW(CW) asm volatile ("ctc1 %0,$31" : :"r" (CW))
#define CGAL_IA_GETFPCW(CW) asm volatile ("cfc1 %0,$31" : "=r" (CW))
typedef unsigned int FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x0)
#define CGAL_FE_TOWARDZERO   (0x1)
#define CGAL_FE_UPWARD       (0x2)
#define CGAL_FE_DOWNWARD     (0x3)

#elif defined __osf || defined __osf__  // Not yet supported.
#define CGAL_IA_SETFPCW(CW) write_rnd(CW)
#define CGAL_IA_GETFPCW(CW) CW = read_rnd()
typedef unsigned int FPU_CW_t;
#define CGAL_FE_TONEAREST    FP_RND_RN
#define CGAL_FE_TOWARDZERO   FP_RND_RZ
#define CGAL_FE_UPWARD       FP_RND_RP
#define CGAL_FE_DOWNWARD     FP_RND_RM

#elif defined __alpha__  // Not yet supported.
#define CGAL_IA_SETFPCW(CW) asm volatile ("mt_fpcr %0; excb" : :"f" (CW))
#define CGAL_IA_GETFPCW(CW) asm volatile ("excb; mf_fpcr %0" : "=f" (CW))
typedef unsigned long FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x0800000000000000UL)
#define CGAL_FE_TOWARDZERO   (0x0000000000000000UL)
#define CGAL_FE_UPWARD       (0x0c00000000000000UL)
#define CGAL_FE_DOWNWARD     (0x0400000000000000UL)

#elif defined _MSC_VER
// Found in http://msdn.microsoft.com/library/sdkdoc/directx/imover_7410.htm :
#define CGAL_IA_SETFPCW(CW) __asm fldcw (CW)
#define CGAL_IA_GETFPCW(CW) __asm fstcw (CW)
typedef unsigned short FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x0   | 0x127f)
#define CGAL_FE_TOWARDZERO   (0xC00 | 0x127f)
#define CGAL_FE_UPWARD       (0x800 | 0x127f)
#define CGAL_FE_DOWNWARD     (0x400 | 0x127f)

#elif defined __BORLANDC__
#define CGAL_IA_SETFPCW(CW) _control87(CW,~0)
#define CGAL_IA_GETFPCW(CW) CW = _control87(0,0)
typedef unsigned short FPU_CW_t;
#define CGAL_FE_TONEAREST    (0x0   | 0x127f)
#define CGAL_FE_TOWARDZERO   (0xC00 | 0x127f)
#define CGAL_FE_UPWARD       (0x800 | 0x127f)
#define CGAL_FE_DOWNWARD     (0x400 | 0x127f)

#else
#error Architecture not supported
#endif

// User interface:

inline
FPU_CW_t
FPU_get_cw (void)
{
    FPU_CW_t cw;
    CGAL_IA_GETFPCW(cw);
    return cw;
}

inline
void
FPU_set_cw (FPU_CW_t cw)
{
    CGAL_IA_SETFPCW(cw);
}

inline
FPU_CW_t
FPU_get_and_set_cw (FPU_CW_t cw)
{
    FPU_CW_t old = FPU_get_cw();
    FPU_set_cw(cw);
    return old;
}

FPU_CW_t FPU_empiric_test(); // Only used for debug.

// A class whose constructor sets the FPU mode to +inf, saves a backup of it,
// and whose destructor resets it back to the saved state.

template <bool Protected> class Protect_FPU_rounding;
 
template <>
struct Protect_FPU_rounding<true>
{
  Protect_FPU_rounding(FPU_CW_t r = CGAL_FE_UPWARD)
    : backup( FPU_get_and_set_cw(r) ) {}

  ~Protect_FPU_rounding()
  {
     FPU_set_cw(backup);
  }

private:
  FPU_CW_t backup;
};
 
template <>
struct Protect_FPU_rounding<false>
{
  Protect_FPU_rounding(FPU_CW_t CGAL_expensive_assertion_code(r)
		        = CGAL_FE_UPWARD)
  {
    CGAL_expensive_assertion(FPU_empiric_test() == r);
  }

  ~Protect_FPU_rounding() {}
  // just to shut up a warning, but it has a performance issue with GCC 2.95,
  // so I should disable it for the moment.  Use __attribute__((unused)) ?
};

CGAL_END_NAMESPACE

#endif // CGAL_FPU_H
