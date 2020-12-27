#ifndef STAR_T
#define STAR_T

//	C++ Libraries
#include <string>

//	Structure declarations
#include "world_t.h"

//using namespace std;

struct star_t
{
//	Luminosity class
//	V = main sequence
//	IV = subgiant
//	III = giant
//	D = white dwarf
//	Source: hygData
	char luminosityClass;

//	Which star in the system is this?
//	Source: hygData
	char starNumber;

//	Source: Wikipedia
	float stellarMass;
//	Source: Wikipedia
	float stellarAge;
//	Source: hygData
	float stellarLuminosity;
//	Source: Wikipedia
	float stellarTemperature;
//	Source: Wikipedia
	float stellarRadius;
//	Source: Wikipedia
	float equatorialRotationVelocity;

//	For stellarEvolutionTableConstants
//	Source: hygData
	char starType;
	float tableTemperature;
	float lMin;
	float lMax;
	float mSpan;
	float sSpan;
	float gSpan;
	float energyRadiated;

//	For locateOrbitalZones
	float innerLimitRadius;
	float outerLimitRadius;
	float snowLineRadius;
//	Only applies to multiple-star systems
//	Source: Wikipedia
	float averageOrbitalRadius;
//	Source: Wikipedia
	float orbitalEccentricity;
//	Source: Calculated
	float minSeparationToCompanion;
//	Source: Calculated
	float maxSeparationToCompanion;
//	Source: Generated
	float innerForbiddenZone;
//	Source: Generated
	float outerForbiddenZone;

//	For the actual planetary system
//	The number of orbital slots around the star
	char numberOfOrbits;
//	Stores the size class of each world
	char sizeClassArray[32];
//	Stores the orbital radius around the primary of each world
	float orbitalRadiusArray[32];
//	The index value of the orbital slot closest to the primary
	char firstWorldIndex;
//	Record the object in each of the world's orbital slots
	world_t worldArray[16];
	int sizeClassIndex;

//	Indices of worlds that match this star in worldDoc
	int preplacedWorldIndex[7];
//	Number of worlds that match this star in starDoc
	int numberOfCSVPlanets;

/*
//	This array holds the orbits of each planet in the system
	planetaryOrbitsArray_t planetaryOrbits;
	worldArray_t worldArray;
*/
//	Star's escape velocity
//	Source: Calculated
	double escapeVelocity;

	char gasGiantArrangement;
	bool firstGasGiantPresent;
	float firstGasGiantOrbitalRadius;

//	If the star is a companion
//	Source: Wikipedia
	float stellarOrbitalPeriod;

//	Stellar classification
	std::string harvardLetter;
	std::string yerkesClassification;
	float numericValue;
	std::string starClassification;

//	Apparent color of the star
	uint8_t starColor_r;
	uint8_t starColor_g;
	uint8_t starColor_b;

//	Constellation
	std::string starConstellation;

//	Cartesian coordinates
	double cartesianX;
	double cartesianY;
	double cartesianZ;
	double cartesianVelocityX;
	double cartesianVelocityY;
	double cartesianVelocityZ;

//	Identification
	int hygIndex;
	int hipIndex;
	int hdIndex;
	int hrIndex;
	std::string glieseIndex;
	std::string properName;

};

#endif
