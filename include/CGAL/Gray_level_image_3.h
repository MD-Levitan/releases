// Copyright (c) 2005-2007  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.7-branch/Surface_mesher/include/CGAL/Gray_level_image_3.h $
// $Id: Gray_level_image_3.h 43257 2008-05-21 22:11:03Z lrineau $
//
// Author(s)     : Laurent RINEAU

#ifndef CGAL_MESH_3_GRAY_LEVEL_IMAGE_3_H
#define CGAL_MESH_3_GRAY_LEVEL_IMAGE_3_H

#include <CGAL/basic.h>

#include <CGAL/auto_link/ImageIO.h>

#include <boost/shared_ptr.hpp>

#ifdef CGAL_SURFACE_MESHER_DEBUG_GRAY_LEVEL_IMAGE_3_CONSTRUCTOR
#include <boost/format.hpp>
#endif

#include <CGAL/Image_3.h>

namespace CGAL {

template <typename FT, typename Point>
class Gray_level_image_3 : public Image_3
{
  float isovalue;
  bool positive_inside;
  float value_outside;
public:
  Gray_level_image_3(const Image_3& image, float isoval) 
    : Image_3(image),
      isovalue(isoval),
      positive_inside(true),
      value_outside(0.f)
  {
  }

  Gray_level_image_3(const char* file, float isoval, bool positive_inside_=true, float value_outside = 0.f)
    : Image_3(),
      isovalue(isoval),
      positive_inside(positive_inside_),
      value_outside(value_outside)
  {
#ifdef CGAL_SURFACE_MESHER_DEBUG_GRAY_LEVEL_IMAGE_3_CONSTRUCTOR
    std::cerr << 
      ::boost::format("Constructing a Gray_level_image_3(\"%1%\")... ") % file;
#endif
    Image_3::read(file);
#ifdef CGAL_SURFACE_MESHER_DEBUG_GRAY_LEVEL_IMAGE_3_CONSTRUCTOR
    if( image_ptr.get() != 0 )
    {
      std::cerr << ::boost::format(" = %1%\n") % image_ptr.get();
    }
#endif
  }

  ~Gray_level_image_3()
  {
#ifdef CGAL_SURFACE_MESHER_DEBUG_GRAY_LEVEL_IMAGE_3_CONSTRUCTOR
      std::cerr << ::boost::format("~Gray_level_image_3() image=%1%\n") % image;
#endif
  }

  static void print_supported_file_format()
  {
    ::printSupportedFileFormat();
  }

  FT operator()(Point p) const
  {
    const float X=static_cast<float>(to_double(p.x()));
    const float Y=static_cast<float>(to_double(p.y()));
    const float Z=static_cast<float>(to_double(p.z()));

    float value = ::triLinInterp(this->image_ptr.get(), X, Y, Z, value_outside); 
    if (positive_inside)
    {
      if (value > isovalue) // inside
        return FT(-1);
      else if (value < isovalue) // outside
        return FT(1);
      else
        return FT(0);
    }
    else
    {      
      if (value < isovalue) // inside
        return FT(-1);
      else if (value > isovalue) // outside
        return FT(1);
      else
        return FT(0);
    }
  }
}; // end Gray_level_image_3
 
} // end namespace CGAL

#endif // CGAL_MESH_3_GRAY_LEVEL_IMAGE_3_H
