// Copyright (c) 2005-2008 ASCLEPIOS Project, INRIA Sophia-Antipolis (France)
// All rights reserved.
//
// This file is part of the ImageIO Library, and as been adapted for
// CGAL (www.cgal.org).
// You can redistribute it and/or  modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation;
// version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// These files are provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.7-branch/CGALimageIO/src/CGALimageIO/convert.cpp $
// $Id: convert.cpp 45554 2008-09-15 14:30:53Z lrineau $
//
//
// Author(s)     :  ASCLEPIOS Project (INRIA Sophia-Antipolis), Laurent Rineau

/*************************************************************************
 * convert.c - conversion between types
 *
 * $Id: convert.cpp 45554 2008-09-15 14:30:53Z lrineau $
 *
 * CopyrightŠINRIA 1999
 *
 * AUTHOR:
 * Gregoire Malandain (greg@sophia.inria.fr)
 * 
 * CREATION DATE: 
 * June, 9 1998
 *
 * ADDITIONS, CHANGES
 *
 * - Tue Feb 22 11:25:39 MET 2000 (G. Malandain)
 *   add in ConvertBuffer():
 *       USHORT to UCHAR
 *       USHORT to SHORT
 *
 */

#include "convert.h"

void ConvertBuffer( void *bufferIn,
		    bufferType typeIn,
		    void *bufferOut,
		    bufferType typeOut,
		    int bufferLength )
{
  const char *proc = "ConvertBuffer";
  register int i, min, max;
  register u8 *u8buf;
  register s8 *s8buf;
  register u16 *u16buf;
  register s16 *s16buf;
  register s32 *s32buf;
  register r32 *r32buf;
  register r64 *r64buf;

  if ( (typeOut == typeIn) && (bufferOut == bufferIn) )
    return;

  if ( bufferLength <= 0 ) {
    fprintf( stderr, " Fatal error in %s: buffer length is negative or zero.\n", 
	     proc );
    return;
  }
  if ( (bufferIn == (void*)NULL) || (bufferOut == (void*)NULL) ) {
    fprintf( stderr, " Fatal error in %s: NULL buffer(s).\n", 
	     proc );
    return;
  }
  
  switch ( typeOut ) {
  case CGAL_SCHAR :
    s8buf = (s8*)bufferOut;
    min = -128; max = 127;
    switch( typeIn ) {
    case CGAL_SCHAR :
      if ( bufferOut == bufferIn ) return;
      (void)memcpy( bufferOut, bufferIn, bufferLength * sizeof(s8) );
      break;
    case CGAL_FLOAT :
      r32buf = (r32*)bufferIn;
      for (i=bufferLength; i>0; i--, s8buf++, r32buf++ ) {
	if ( *r32buf < min ) *s8buf = min;
	else if ( *r32buf < 0.0 ) *s8buf = (int)(*r32buf - 0.5);
	else if ( *r32buf < max ) *s8buf = (int)(*r32buf + 0.5);
	else *s8buf = max;
      }
      break;
    case CGAL_DOUBLE :
      r64buf = (r64*)bufferIn;
      for (i=bufferLength; i>0; i--, s8buf++, r64buf++ ) {
	if ( *r64buf < min ) *s8buf = min;
	else if ( *r64buf < 0.0 ) *s8buf = (int)(*r64buf - 0.5);
	else if ( *r64buf < max ) *s8buf = (int)(*r64buf + 0.5);
	else *s8buf = max;
      }
      break;
    default :
      fprintf( stderr, " Error in %s: such conversion not yet implemented.\n", 
	       proc );
      return;
    }
    break; /* end case typeOut = CGAL_SCHAR */




    
  case CGAL_UCHAR :
    u8buf = (u8*)bufferOut;
    min = 0; max = 255;
    switch( typeIn ) {
    case CGAL_UCHAR :
      if ( bufferOut == bufferIn ) return;
      (void)memcpy( bufferOut, bufferIn, bufferLength * sizeof(u8) );
      break;
    case CGAL_USHORT :
      u16buf = (u16*)bufferIn;
      for (i=bufferLength; i>0; i--, u8buf++, u16buf++ ) {
	if ( *u16buf < max ) *u8buf = (u8)*u16buf;
	else *u8buf = max;
      }
      break;
    case CGAL_FLOAT :
      r32buf = (r32*)bufferIn;
      for (i=bufferLength; i>0; i--, u8buf++, r32buf++ ) {
	if ( *r32buf < min ) *u8buf = min;
	else if ( *r32buf < max ) *u8buf = (int)(*r32buf + 0.5);
	else *u8buf = max;
      }
      break;
    case CGAL_DOUBLE :
      r64buf = (r64*)bufferIn;
      for (i=bufferLength; i>0; i--, u8buf++, r64buf++ ) {
	if ( *r64buf < min ) *u8buf = min;
	else if ( *r64buf < max ) *u8buf = (int)(*r64buf + 0.5);
	else *u8buf = max;
      }
      break;
    default :
      fprintf( stderr, " Error in %s: such conversion not yet implemented.\n", 
	       proc );
      return;
    }
    break; /* end case typeOut = CGAL_UCHAR */





    
  case CGAL_SSHORT :
    s16buf = (s16*)bufferOut;
    min = -32768; max = 32767;
    switch( typeIn ) {
    case CGAL_SSHORT :
      if ( bufferOut == bufferIn ) return;
      (void)memcpy( bufferOut, bufferIn, bufferLength * sizeof(s16) );
      break;
    case CGAL_USHORT :
      u16buf = (u16*)bufferIn;
      for (i=bufferLength; i>0; i--, s16buf++, u16buf++ ) {
	if ( *u16buf < max ) *s16buf = (s16)*u16buf;
	else *s16buf = max;
      }
      break;
    case CGAL_FLOAT :
      r32buf = (r32*)bufferIn;
      for (i=bufferLength; i>0; i--, s16buf++, r32buf++ ) {
	if ( *r32buf < min ) *s16buf = min;
	else if ( *r32buf < 0.0 ) *s16buf = (int)(*r32buf - 0.5);
	else if ( *r32buf < max ) *s16buf = (int)(*r32buf + 0.5);
	else *s16buf = max;
      }
      break;
    case CGAL_DOUBLE :
      r64buf = (r64*)bufferIn;
      for (i=bufferLength; i>0; i--, s16buf++, r64buf++ ) {
	if ( *r64buf < min ) *s16buf = min;
	else if ( *r64buf < 0.0 ) *s16buf = (int)(*r64buf - 0.5);
	else if ( *r64buf < max ) *s16buf = (int)(*r64buf + 0.5);
	else *s16buf = max;
      }
      break;
    default :
      fprintf( stderr, " Error in %s: such conversion not yet implemented.\n",
	       proc );
      return;
    }
    break; /* end case typeOut = CGAL_SSHORT */




    
  case CGAL_USHORT :
    u16buf = (u16*)bufferOut;
    min = 0; max = 65535;
    switch( typeIn ) {
    case CGAL_USHORT :
      if ( bufferOut == bufferIn ) return;
      (void)memcpy( bufferOut, bufferIn, bufferLength * sizeof(u16) );
      break;
    case CGAL_FLOAT :
      r32buf = (r32*)bufferIn;
      for (i=bufferLength; i>0; i--, u16buf++, r32buf++ ) {
	if ( *r32buf < min ) *u16buf = min;
	else if ( *r32buf < 0.0 ) *u16buf = (int)(*r32buf - 0.5);
	else if ( *r32buf < max ) *u16buf = (int)(*r32buf + 0.5);
	else *u16buf = max;
      }
      break;
    case CGAL_DOUBLE :
      r64buf = (r64*)bufferIn;
      for (i=bufferLength; i>0; i--, u16buf++, r64buf++ ) {
	if ( *r64buf < min ) *u16buf = min;
	else if ( *r64buf < 0.0 ) *u16buf = (int)(*r64buf - 0.5);
	else if ( *r64buf < max ) *u16buf = (int)(*r64buf + 0.5);
	else *u16buf = max;
      }
      break;
    default :
      fprintf( stderr, " Error in %s: such conversion not yet implemented.\n",
	       proc );
      return;
    }
    break; /* end case typeOut = CGAL_USHORT */





    
  case CGAL_INT :
    s32buf = (s32*)bufferOut;
    switch( typeIn ) {
    case CGAL_INT :
      if ( bufferOut == bufferIn ) return;
      (void)memcpy( bufferOut, bufferIn, bufferLength * sizeof(s32) );
      break;
    case CGAL_FLOAT :
      r32buf = (r32*)bufferIn;
      for (i=bufferLength; i>0; i--, s32buf++, r32buf++ ) {
	*s32buf = (int)(*r32buf);
      }
      break;
    case CGAL_DOUBLE :
      r64buf = (r64*)bufferIn;
      for (i=bufferLength; i>0; i--, s32buf++, r64buf++ ) {
	*s32buf = (int)(*r64buf);
      }
      break;
    default :
      fprintf( stderr, " Error in %s: such conversion not yet implemented.\n",
	       proc );
      return;
    }
    break; /* end case typeOut = CGAL_INT */





    
  case CGAL_FLOAT :
    r32buf = (r32*)bufferOut;
    switch( typeIn ) {
    case CGAL_UCHAR :
      u8buf = (u8*)bufferIn;
      for (i=bufferLength; i>0; i--, r32buf++, u8buf++ ) {
	*r32buf = (float)(*u8buf);
      }
      break;
    case CGAL_SCHAR :
      s8buf = (s8*)bufferIn;
      for (i=bufferLength; i>0; i--, r32buf++, s8buf++ ) {
	*r32buf = (float)(*s8buf);
      }
      break;
    case CGAL_USHORT :
      u16buf = (u16*)bufferIn;
      for (i=bufferLength; i>0; i--, r32buf++, u16buf++ ) {
	*r32buf = (float)(*u16buf);
      }
      break;
    case CGAL_SSHORT :
      s16buf = (s16*)bufferIn;
      for (i=bufferLength; i>0; i--, r32buf++, s16buf++ ) {
	*r32buf = (float)(*s16buf);
      }
      break;
    case CGAL_INT :
      s32buf = (s32*)bufferIn;
      for (i=bufferLength; i>0; i--, r32buf++, s32buf++ ) {
	*r32buf = (float)(*s32buf);
      }
      break;
    case CGAL_FLOAT :
      if ( bufferOut == bufferIn ) return;
      (void)memcpy( bufferOut, bufferIn, bufferLength * sizeof(r32) );
      break;
    case CGAL_DOUBLE :
      r64buf = (r64*)bufferIn;
      for (i=bufferLength; i>0; i--, r32buf++, r64buf++ ) {
	*r32buf = (float)(*r64buf);
      }
      break;
    default :
      fprintf( stderr, " Error in %s: such conversion not yet implemented.\n",
	       proc );
      return;
    }
    break; /* end case typeOut = CGAL_FLOAT */




    
  case CGAL_DOUBLE :
    r64buf = (r64*)bufferOut;
    switch( typeIn ) {
    case CGAL_UCHAR :
      u8buf = (u8*)bufferIn;
      for (i=bufferLength; i>0; i--, r64buf++, u8buf++ ) {
	*r64buf = (double)(*u8buf);
      }
      break;
    case CGAL_SCHAR :
      s8buf = (s8*)bufferIn;
      for (i=bufferLength; i>0; i--, r64buf++, s8buf++ ) {
	*r64buf = (double)(*s8buf);
      }
      break;
    case CGAL_USHORT :
      u16buf = (u16*)bufferIn;
      for (i=bufferLength; i>0; i--, r64buf++, u16buf++ ) {
	*r64buf = (double)(*u16buf);
      }
      break;
    case CGAL_SSHORT :
      s16buf = (s16*)bufferIn;
      for (i=bufferLength; i>0; i--, r64buf++, s16buf++ ) {
	*r64buf = (double)(*s16buf);
      }
      break;
    case CGAL_INT :
      s32buf = (s32*)bufferIn;
      for (i=bufferLength; i>0; i--, r64buf++, s32buf++ ) {
	*r64buf = (double)(*s32buf);
      }
      break;
    case CGAL_FLOAT :
      r32buf = (r32*)bufferIn;
      for (i=bufferLength; i>0; i--, r32buf++, r64buf++ ) {
	*r64buf = (double)(*r32buf);
      }
      break;
    case CGAL_DOUBLE :
      if ( bufferOut == bufferIn ) return;
      (void)memcpy( bufferOut, bufferIn, bufferLength * sizeof(r64) );
      break;
    default :
      fprintf( stderr, " Error in %s: such conversion not yet implemented.\n", 
	       proc );
      return;
    }
    break; /* end case typeOut = CGAL_DOUBLE */



   
  default :
    fprintf( stderr, " Error in %s: such output type not yet handled.\n",
	     proc );
    return;
  }
}





void Convert_r32_to_s8( r32 *theBuf,
			s8 *resBuf,
			int size )
{
  register int i;
  register r32* tb = theBuf;
  register s8* rb = resBuf;
  
  for ( i=0; i<size; i++, tb++, rb++ ) {
    if ( *tb < -128.0 ) {
      *rb = -128;
    } else if ( *tb < 0.0 ) {
      *rb = (int)(*tb - 0.5);
    } else if ( *tb < 127.0 ) {
      *rb = (int)(*tb + 0.5);
    } else {
      *rb = 127;
    }
  }
}





void Convert_r32_to_u8( r32 *theBuf,
			u8 *resBuf,
			int size )
{
  register int i;
  register r32* tb = theBuf;
  register u8* rb = resBuf;
  
  for ( i=0; i<size; i++, tb++, rb++ ) {
    if ( *tb < 0.0 ) {
      *rb = 0;
    } else if ( *tb < 255.0 ) {
      *rb = (int)(*tb + 0.5);
    } else {
      *rb = 255;
    }
  }
}





void Convert_r32_to_s16( r32 *theBuf,
			 s16 *resBuf,
			 int size )
{
  register int i;
  register r32* tb = theBuf;
  register s16* rb = resBuf;
  
  for ( i=0; i<size; i++, tb++, rb++ ) {
    if ( *tb < -32768.0 ) {
      *rb = -32768;
    } else if ( *tb < 0.0 ) {
      *rb = (int)(*tb - 0.5);
    } else if ( *tb < 32767.0 ) {
      *rb = (int)(*tb + 0.5);
    } else {
      *rb = 32767;
    }
  }
}





void Convert_r32_to_u16( r32 *theBuf,
			 u16 *resBuf,
			 int size )
{
  register int i;
  register r32* tb = theBuf;
  register u16* rb = resBuf;
  
  for ( i=0; i<size; i++, tb++, rb++ ) {
    if ( *tb < 0.0 ) {
      *rb = 0;
    } else if ( *tb < 65535.0 ) {
      *rb = (int)(*tb + 0.5);
    } else {
      *rb = 65535;
    }
  }
}


      
