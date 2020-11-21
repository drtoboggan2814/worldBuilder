//	Constant declarations
#include <cstdint>
#include "declarations/constants/atmosphericPressureCategoryConstants.h"

int8_t habitabilityModifiersBreathable(char pressureCategory, bool breathable)
{
	int8_t habitabilityModifier;

	if 		(breathable == false																				) {habitabilityModifier = 0;}
	else if (breathable == true && pressureCategory == APC_VERY_THIN											) {habitabilityModifier = 1;}
	else if (breathable == true && pressureCategory == APC_THIN													) {habitabilityModifier = 2;}
	else if (breathable == true && pressureCategory == APC_STANDARD		|| pressureCategory == APC_DENSE		) {habitabilityModifier = 3;}
	else if (breathable == true && pressureCategory == APC_VERY_DENSE	|| pressureCategory == APC_SUPERDENSE	) {habitabilityModifier = 1;}
	else																									  	  {habitabilityModifier = 0;}
	return habitabilityModifier;
}
