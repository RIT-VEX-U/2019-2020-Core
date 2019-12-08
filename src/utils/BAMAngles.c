#include "utils/BAMAngles.h"
#include <math.h>

/**
 * \file BAMAngles.c
 *   Library for handling conversions to or from Binary Angle Measure.
 * \author Alex Kneipp
 * \written 10/3/2019
 */

#ifdef __cplusplus
extern "C" {
#endif

bamAngle_t floatToBAM(float degrees)
{
  //normalize from any value to 0-360
  float normalizedDegrees = ((degrees - (floor(degrees/360.0) * 360))) / 360.0;
  //Bring it into BAM
  bamAngle_t bam = (bamAngle_t)(normalizedDegrees * INT32_MAX);
  return bam;
}

float bamToFloat(bamAngle_t bam)
{
  //Scale it to -1 - 1 and bring it back into the degree range
  float degrees = (((float)(bam)) / INT32_MAX) * 360.0;
  return degrees;
}

#ifdef __cplusplus
}
#endif
