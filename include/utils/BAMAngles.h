#ifndef BAMANGLES_H
#define BAMANGLES_H

/**
 * \file BAMAngles.h
 *   Library for handling conversions to or from Binary Angle Measure.
 * \author Alex Kneipp
 * \written 10/3/2019
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t bamAngle_t;

/**
 * Convert a floating point angle into Binary Angle Measure.
 * \param degrees
 *   The number of degrees, from 0-360.
 * \return
 *   \p degrees represented as BAM.
 */
bamAngle_t floatToBAM(float degrees);

/**
 * Convert a Binary Angle Measure type into a floationg point number of degrees.
 * \param bam
 *   The angle in BAM.
 * \return
 *   The number of degrees \p bam represents, from 0-360.
 */
float bamToFloat(bamAngle_t bam);

#ifdef __cplusplus
}
#endif

#endif
