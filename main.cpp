/*
 * Author: Emmanuel Ayuyao Castillo
 *
 * Assignment:
 * ---------------------------
 * Use a Tri-gram model to get
 * the probability of a word.
 *
 * Description: 
 * ----------------------------------------
 * The program uses a file
 * containing probabilities of characters
 * given a sequence. This file is created
 * at random. The probabilities in the file
 * is used to calculate the probability
 * of a user input string of the characters
 * A, B, or C only.
 */

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "probutils.h"

using namespace std;

int main()
{
	/* A probabilities file is opened and loaded into a map data structure *
	 * of the following key/value structure:                               *
	 * key = character|sequence					       *
	 * value = probability                                                 */
	ifstream inputStream;
	map<string, long double> probabilities;
	openProbabilitiesFile(inputStream);
	loadProbabilities(inputStream, probabilities);

	/* A prompt is displayed on the console for a user to input a string  *
	 * to calculate its probability                                       */
	string userInput;
	cout << "Please enter a string consisting of A, B, or C only: ";
	getline(cin, userInput);
	cout << "\n";

	/* User input string is validated that it only contains A, B, or C characters. */
	validateUserInput(userInput);

	/* User input string probability is calculated than displayed */
	stringstream probability;
	probability << calculateProbability(userInput, probabilities);
	cout << "Probability of " << userInput << " is " << probability.str() << "\n";

    return 0;
}
