//	This functions returns a string representing the size of the gas giant
char getGasGiantSize(int diceRoll);

//	This function returns a string representing the non-gas giant contents of the orbit
char orbitContentsTable(int orbitContentsRoll);

//	This function checks which modifiers should be applied to orbitContentsRoll
//	currentIndex is the current index of the for loop iterating through the orbits
int getOrbitContentsRollModifier(star_t primary, int currentIndex);

star_t fillOrbits(star_t primary);
