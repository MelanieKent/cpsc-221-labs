#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "lab_intro.h"

using namespace cs221util;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * We are still representing the image using RGBA, but each pixel
 * will be adjusted so that it is a shade of gray with equal RGB values.
 * 
 * Note that while setting each RGB channel to the simple average may seem
 * intuitive, the resulting image will not be visually accurate due to the
 * human eye's varying sensitivity to different wavelengths.
 * Therefore the grayscale value for each channel will instead be weighted
 * by the perceived luminosity as 0.229*R + 0.587*G + 0.114*B.
 *
 * Finally, as each channel is stored in a variable of type unsigned char,
 * ensure that the computed grayscale value is truncated to an appropriate
 * value for storage. Also be aware that sufficient precision must be
 * maintained during intermediate computations.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is partially written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      RGBAPixel* pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.

      double grayvalue = 0.0; // this will be changed once you determine what the adjusted RGB values will be below!
      double adjusted_red = 0.229 * pixel->r;
      double adjusted_green = 0.587 * pixel->g;
      double adjusted_blue = 0.114 * pixel->b;

      grayvalue = adjusted_red + adjusted_green + adjusted_blue;
      
      pixel->r = (unsigned char) grayvalue;
      pixel->g = (unsigned char) grayvalue;
      pixel->b = (unsigned char) grayvalue;

    }
  }
  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the brightness of a pixel based on the distance the pixel
 * is away from the center by decreasing the RGB channel values by 0.5% per
 * 1 pixel euclidean distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its brightness is decreased by 2.5% (0.975x its original value).  At a
 * distance over 200 pixels away, the brightness will always 0.
 *
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      RGBAPixel* pixel = image.getPixel(x, y);

      double eucdist = 0.0;
      eucdist = sqrt(((x - centerX) * (x - centerX)) + ((y - centerY) * (y - centerY)));

      double factor = 0.0;
      factor = (100 - (eucdist * 0.5)) / 100;

      if (eucdist > 200) {
        factor = 0.0;
      }
     
      pixel->r *= factor;
      pixel->g *= factor;
      pixel->b *= factor; 
      
    }
  }
  return image;
}


/**
 * Returns a image transformed to UBC colors.
 *
 * The color of every pixel is set to the same value of either UBC yellow or
 * UBC blue, based on if the pixel's color value is closer to yellow than blue.
 * Use the "colordist" function defined in lab_intro.h (and implemented
 * at the bottom of this file). In case of equal distances, set the color to yellow.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The UBCify'd image.
**/
PNG ubcify(PNG image) {

  RGBAPixel ubcbpixel(12,35,68, 1.0);
  RGBAPixel ubcypixel(247,184,0, 1.0);

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      RGBAPixel* pixel = image.getPixel(x, y);

      double bcolordist = 0.0;
      double ycolordist = 0.0;
      bcolordist = colordist(*pixel, ubcbpixel);
      ycolordist = colordist(*pixel, ubcypixel);

      if (ycolordist <= bcolordist) {
        pixel->r = 247;
        pixel->g = 184;
        pixel->b = 0;
      } else {
        pixel->r = 12;
        pixel->g = 35;
        pixel->b = 68;
      }
    }
  }
  return image;
}


/**
* Returns an image that has been watermarked by another image.
*
* The color of every pixel of the second image is checked - if that
* pixel's color is pure white, then the pixel at the same location on
* the first image has each color channel increased by by 40 (up to a maximum
* of 255).
*
* @param firstImage  The first of the two PNGs.
* @param secondImage The second of the two PNGs.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
  firstImage.resize(1024, 768);
  secondImage.resize(1024, 768);
  for (unsigned x = 0; x < secondImage.width(); x++) {
    for (unsigned y = 0; y < secondImage.height(); y++) {
      RGBAPixel* pixel = secondImage.getPixel(x, y);
      bool b = false;

      if ((pixel->r == 255)&&(pixel->g == 255)&&(pixel->b == 255)) {
        b = true;
      }

      if (b) {
        RGBAPixel* pixelFirst = firstImage.getPixel(x,y);
        if ((pixelFirst->r + 40) <= 255) {
          pixelFirst->r += 40;
        } else {
          pixelFirst->r = 255;
        }

        if ((pixelFirst->g + 40) <= 255) {
          pixelFirst->g += 40;
        } else {
          pixelFirst->g = 255;
        }

        if ((pixelFirst->b + 40) <= 255) {
          pixelFirst->b += 40;
        } else {
          pixelFirst->b = 255;
        }
      }
    }
  }
  return firstImage;
}

/**
* Computes the color "distance" between two pixels.
* @param px1 first pixel whose color will be compared
* @param px2 second pixel whose color will be compared
*/
double colordist(RGBAPixel px1, RGBAPixel px2) {
  // scale each channel to [0,1] range and pre-multiply alpha
  double dbl_r_px1 = (double)px1.r / 255.0 * px1.a;
  double dbl_r_px2 = (double)px2.r / 255.0 * px2.a;
  double dbl_g_px1 = (double)px1.g / 255.0 * px1.a;
  double dbl_g_px2 = (double)px2.g / 255.0 * px2.a;
  double dbl_b_px1 = (double)px1.b / 255.0 * px1.a;
  double dbl_b_px2 = (double)px2.b / 255.0 * px2.a;

  double delta_a = px1.a - px2.a;

  // compute maximum of each channel blended on white, and blended on black
  // red channel
  double black = dbl_r_px1 - dbl_r_px2;
  double white = black + delta_a;
  double diff_r = max(black * black, white * white);
  // green channel
  black = dbl_g_px1 - dbl_g_px2;
  white = black + delta_a;
  double diff_g = max(black * black, white * white);
  // blue channel
  black = dbl_b_px1 - dbl_b_px2;
  white = black + delta_a;
  double diff_b = max(black * black, white * white);

  return diff_r + diff_g + diff_b;
}