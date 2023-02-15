/**
 * @file RGBAPixel.cpp
 * Implementation of the RGBAPixel class for use with the PNG library.
 */

#include "RGBAPixel.h"

namespace cs221util {
  bool RGBAPixel::operator== (RGBAPixel const & other) const {
    if (this->a == 0 && other.a == 0) { return true; }
    else {
      return ( this->r == other.r &&
               this->g == other.g &&
               this->b == other.b &&
               this->a == other.a );
    }
  }
  
  bool RGBAPixel::operator!= (RGBAPixel const & other) const {
    return !(*this == other);
  }

  RGBAPixel::RGBAPixel() {
    r = 255;
    g = 255;
    b = 255;
    a = 1.0;
  }

  RGBAPixel::RGBAPixel(int red, int green, int blue) {
    r = red;
    g = green;
    b = blue;
    a = 1.0;
  }

  RGBAPixel::RGBAPixel(int red, int green, int blue, double alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
  }
}