#include "../include/Utils.h"

float map(float value, float fromLow, float fromHigh, float toLow, float toHigh){
 	// Ensure the input value is within the current range
    value = std::min(std::max(value, fromLow), fromHigh);

    // Map the value to the target range
    return toLow + (toHigh - toLow) * ((value - fromLow) / (fromHigh - fromLow));
}