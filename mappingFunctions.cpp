//	This file declares functions used for world mapping
//	NOTE: These are based off the mapping rules from 2300 AD and Traveller: The New Era - World Tamer's Handbook

//	C++ libraries
#include <cstdint>
#include <cmath>

//	Constant declarations
#include "declarations/constants/mappingConstants.h"
#include "declarations/constants/unitConversions.h"

//	Function declarations
#include "declarations/functions/diceRoller.h"

//	Return the number of hexes per triangle side
uint8_t getHexesPerSide(const float& worldDiameter)
{
	uint8_t worldSize = uint8_t(round((worldDiameter * EARTH_RADIUS_IN_KM) / 1000));
	uint8_t hexesPerSide = WORLDSIZE_TRIANGLESIZE_LOOKUP_TABLE[worldSize];
	return hexesPerSide;
}

//	Return the total number of hexes on the map
uint16_t getTotalHexCount(const uint8_t& hexesPerSide)
{
	uint16_t totalHexCount = WORLD_MAP_TOTAL_HEXES[hexesPerSide];
	return totalHexCount;
}

//	Return the Traveller UWP size code for the world
//	This function is used by getTectonicPlateCount, and applies only to terrestrial worlds
uint8_t getUWPSize(const float& worldDiameter)
{
//	Initialize return value
	uint8_t uwpSize = 0;
//	Convert worldDiameter to km
	float worldDiameterKM = worldDiameter * EARTH_RADIUS_IN_KM;

	if 		(worldDiameter < 800)								{uwpSize = 0;}
	else if (worldDiameter >= 800 	&& worldDiameter < 2400)	{uwpSize = 1;}
	else if (worldDiameter >= 2400 	&& worldDiameter < 4000)	{uwpSize = 2;}
	else if (worldDiameter >= 4000 	&& worldDiameter < 5600)	{uwpSize = 3;}
	else if (worldDiameter >= 5600 	&& worldDiameter < 7200)	{uwpSize = 4;}
	else if (worldDiameter >= 7200 	&& worldDiameter < 8800)	{uwpSize = 5;}
	else if (worldDiameter >= 8800 	&& worldDiameter < 10400)	{uwpSize = 6;}
	else if (worldDiameter >= 10400 && worldDiameter < 12000)	{uwpSize = 7;}
	else if (worldDiameter >= 12000 && worldDiameter < 13600)	{uwpSize = 8;}
	else if (worldDiameter >= 13600 && worldDiameter < 15200)	{uwpSize = 9;}
	else if (worldDiameter >= 15200 && worldDiameter < 16800)	{uwpSize = 10;}
	else if (worldDiameter >= 16800 && worldDiameter < 18400)	{uwpSize = 11;}
	else														{uwpSize = 12;}

	return uwpSize;
}

//	Return the Traveller UWP hydrographic code for the world
//	This function is used by getTectonicPlateCount, and applies only to terrestrial worlds
uint8_t getUWPHydrographic(const float& hydrographicCoverage)
{
//	Initialize return value
	uint8_t uwpHydrographic = 0;

	if 		(hydrographicCoverage < 0.06)									{uwpHydrographic = 0;}
	else if (hydrographicCoverage >= 0.06 && hydrographicCoverage < 0.15)	{uwpHydrographic = 1;}
	else if (hydrographicCoverage >= 0.16 && hydrographicCoverage < 0.25)	{uwpHydrographic = 2;}
	else if (hydrographicCoverage >= 0.26 && hydrographicCoverage < 0.35)	{uwpHydrographic = 3;}
	else if (hydrographicCoverage >= 0.36 && hydrographicCoverage < 0.45)	{uwpHydrographic = 4;}
	else if (hydrographicCoverage >= 0.46 && hydrographicCoverage < 0.55)	{uwpHydrographic = 5;}
	else if (hydrographicCoverage >= 0.56 && hydrographicCoverage < 0.65)	{uwpHydrographic = 6;}
	else if (hydrographicCoverage >= 0.66 && hydrographicCoverage < 0.75)	{uwpHydrographic = 7;}
	else if (hydrographicCoverage >= 0.76 && hydrographicCoverage < 0.85)	{uwpHydrographic = 8;}
	else if (hydrographicCoverage >= 0.86 && hydrographicCoverage < 0.95)	{uwpHydrographic = 9;}
	else																	{uwpHydrographic = 10;}

	return uwpHydrographic;
}


//	Return the number of tectonic plates on the world
uint8_t getTectonicPlateCount(const float& worldDiameter, const float& hydrographicCoverage)
{
	int diceRoll = diceRoller(6, 2);
	uint8_t tectonicPlateCount = (getUWPHydrographic(hydrographicCoverage) + getUWPSize(worldDiameter)) - diceRoll;
//	A planet needs at least one tectonic plate
	tectonicPlateCount = tectonicPlateCount <= 0 ? 1 : tectonicPlateCount;
	return tectonicPlateCount;
}

//	Return the size (in hexes) of the tectonic plate
uint8_t getTectonicPlateSize(const float& worldDiameter)
{
	const int TECTONIC_PLATE_SIZE_COEFFICIENT[6] = {5, 10, 15, 20, 25, 30};
	int diceRoll = diceRoller(6, 1);
	uint8_t roundedDiameter = round(worldDiameter * 100);
	uint8_t tectonicPlateSize = 2 * roundedDiameter * TECTONIC_PLATE_SIZE_COEFFICIENT[diceRoll];
	return tectonicPlateSize;
}

//	Return the tectonic plate movement
uint8_t getTectonicPlateMovementType()
{
	int diceRoll = diceRoller(6, 2);
	uint8_t tectonicPlateMovementType = 0;
	if (diceRoll <= 5)						{tectonicPlateMovementType = TPMT_CONVERGING;}
	else if (diceRoll > 5 && diceRoll <= 8)	{tectonicPlateMovementType = TPMT_TRAVERSING;}
	else									{tectonicPlateMovementType = TPMT_DIVERGING;}

	return tectonicPlateMovementType;
}

//	Return the total number of water hexes
uint16_t getWaterHexCount(const uint16_t& totalHexCount, const float& hydrographicCoverage)
{
	uint16_t waterHexCount = uint16_t(round(totalHexCount * hydrographicCoverage));
	return waterHexCount;
}

//	Return the total number of land hexes
uint16_t getLandHexCount(const uint16_t& totalHexCount, const uint16_t& waterHexCount)
{
	uint16_t landHexCount = totalHexCount - waterHexCount;
	return landHexCount;
}

//	Mapping water hexes
//	Return the number of major oceans
uint8_t getMajorOceans(const int& diceRoll)
{
	uint8_t numberOfMajorOceans = 0;
	if 		(diceRoll <= 6)		{numberOfMajorOceans = 0;}
	else if (diceRoll >= 19)	{numberOfMajorOceans = 1;}
	else						{numberOfMajorOceans = diceRoller(6, 1) - MAJOR_OCEAN_ADDITION_COEFFICIENT[diceRoll];}

	return numberOfMajorOceans;
}

//	Return the number of minor oceans
uint8_t getMinorOceans(const int& diceRoll)
{
	uint8_t numberOfMinorOceans = 0;
	if 		(diceRoll <= 6)		{numberOfMinorOceans = 0;}
	else						{numberOfMinorOceans = diceRoller(6, MINOR_OCEAN_MULTIPLIER_COEFFICIENT[diceRoll]) - MINOR_OCEAN_ADDITION_COEFFICIENT[diceRoll];}

	return numberOfMinorOceans;
}

//	Return the number of small seas
uint8_t getSmallSeas(const int& diceRoll)
{
	uint8_t numberOfSmallSeas = 0;
	if 		(diceRoll < 5)	{numberOfSmallSeas = 0;}
	else if (diceRoll == 5)	{numberOfSmallSeas = diceRoller(6, 1) - 3;}
	else if (diceRoll == 6)	{numberOfSmallSeas = diceRoller(6, 2) - 3;}
	else					{numberOfSmallSeas = diceRoller(6, 3) - 3;}

	return numberOfSmallSeas;
}

//	Return the number of scattered lakes
uint8_t getScatteredLakes(const int& diceRoll)
{
	uint8_t numberOfScatteredLakes = 0;
	if 		(diceRoll < 3)						{numberOfScatteredLakes = 0;}
	else if (diceRoll == 3 || diceRoll == 4)	{numberOfScatteredLakes = 1;}
	else										{numberOfScatteredLakes = diceRoller(6, 2);}

	return numberOfScatteredLakes;
}

//	Mapping land hexes
//	NOTE: "Mapping Land Hexes" in Traveller: The New Era - World Tamer's Handbook starts at 16 and ends at 36
//	Ensure that this is factored into the diceRoll
//	Return the number of major continents
uint8_t getMajorContinents(const int& diceRoll)
{
	uint8_t numberOfMajorContinents = 0;
	if (diceRoll < (31 - 16))	{numberOfMajorContinents = diceRoller(6, MAJOR_CONTINENT_MULTIPLIER_COEFFICIENT[diceRoll]) + MAJOR_CONTINENT_ADDITION_COEFFICIENT[diceRoll];}
	else						{numberOfMajorContinents = 0;}

	return numberOfMajorContinents;
}

//	Return the number of minor continents
uint8_t getMinorContinents(const int& diceRoll)
{
	uint8_t numberOfMinorContinents = 0;
	if (diceRoll < (31 - 16))	{numberOfMinorContinents = diceRoller(6, MINOR_CONTINENT_MULTIPLIER_COEFFICIENT[diceRoll]) + MINOR_CONTINENT_ADDITION_COEFFICIENT[diceRoll];}
	else						{numberOfMinorContinents = 0;}

	return numberOfMinorContinents;
}

//	Return the number of major islands
uint8_t getMajorIslands(const int& diceRoll)
{
	uint8_t numberOfMajorIslands = 0;
	if 		(diceRoll < (30 - 16))	{numberOfMajorIslands = diceRoller(6, 3) - 3;}
	else if (diceRoll == (30 - 16))	{numberOfMajorIslands = diceRoller(6, 2);}
	else if (diceRoll == (31 - 16))	{numberOfMajorIslands = diceRoller(6, 1) - 3;}
	else							{numberOfMajorIslands = 0;}

	return numberOfMajorIslands;
}

//	Return the number of archipelagoes
uint8_t getArchipelagoes(const int& diceRoll)
{
	uint8_t numberOfArchipelagoes = 0;
	if 		(diceRoll < (32 - 16))							{numberOfArchipelagoes = diceRoller(6, 2);}
	else if (diceRoll < (35 - 16) && diceRoll > (31 - 16))	{numberOfArchipelagoes = 1;}
	else													{numberOfArchipelagoes = 0;}

	return numberOfArchipelagoes;
}
