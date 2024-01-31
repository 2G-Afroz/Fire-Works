#ifndef UTILS_H
#define UTILS_H

#include <algorithm>

/**
 * @brief Maps a value from one range to another.
 *
 * This function takes a value and maps it from a source range to a target range.
 *
 * @param value The input value to be mapped.
 * @param fromLow The lower bound of the source range.
 * @param fromHigh The upper bound of the source range.
 * @param toLow The lower bound of the target range.
 * @param toHigh The upper bound of the target range.
 * @return The mapped value in the target range.
 */
float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);
	
#endif