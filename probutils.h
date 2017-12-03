/*
* Author: Emmanuel Ayuyao Castillo
*
* Description:
* ----------------------------------------
* This files provides the prototypes used for the main program.
*/

#include <fstream>
#include <map>

void openProbabilitiesFile(std::ifstream &inputStream);

void loadProbabilities(std::ifstream &inputStream, std::map<std::string, long double> &probabilities);

void validateUserInput(std::string userInput);

long double calculateProbability(std::string word, std::map<std::string, long double> &probabilities);
