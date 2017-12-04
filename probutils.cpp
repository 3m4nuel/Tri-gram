/*
* Author: Emmanuel Ayuyao Castillo
*
* Description:
* ----------------------------------------
* This files provides the functions used for the main program.
*/

#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>


/* Below contains contants and a method to open up the file containing the probabilities values *
 * for each character and sequence relationship.                                                */
using namespace std;

const char *filePath = "nlpProb.txt";

void openProbabilitiesFile(std::ifstream &inputStream)
{
	inputStream.open(filePath, std::ifstream::in);

	if (!inputStream.is_open())
	{
		cerr << "Couldn't open file " << filePath << '\n';
		exit(EXIT_FAILURE);
	}
}

/* Below contains the constants and methods to parse the character, sequence and probabilities *
 * from the probabilities file, nlpProb.txt						        */
const int BUFF = 256;

void loadProbabilities(ifstream &inputStream, map<string, long double> &probabilities)
{
	/* Each line in the probabilities file is parsed below. This is done by first   *
	 * based on the expected position of a character. After, positions of expected  *
         * characters in the probabilities files are used to obtain the substring that  *
         * represents the sequence and probability values.                              */
	char line[BUFF];
	string character;
	string sequence;
	string probability;

	/* Each line of the file is loop through, extracting the character, sequence and probability */
	while(inputStream.getline(line, BUFF))
	{
		character = line[2];
		sequence = string(line).substr(6, string(line).find(")") - 6);
		probability = string(line).substr(string(line).find("0."), sizeof(line));
		probabilities.insert(pair<string, long double>(character + "|" + sequence, strtold(probability.c_str(), nullptr)));
	}	

	/* Probabilities are displayed after probabilities file is parsed and set into a map data structure. */
	map<string, long double>::iterator it;
	std::cout << "Loading Probabilities....\n\n";
	for (it = probabilities.begin(); it != probabilities.end(); it++)
		std::cout << "P(" << it->first << ") = " << it->second << "\n";

	std::cout << "\n";
}

/* Below verifies only A, B, and C characters are set from the user */
void validateUserInput(string userInput)
{
	char currentCharacter;
	for (unsigned int i = 0; i < userInput.length(); i++)
		currentCharacter = toupper(userInput[i]);
		if (currentCharacter != 'A' && currentCharacter != 'B' && currentCharacter != 'C')
		{
			cerr << "Input must only contain A, B or C. Your input is invalid: " << currentCharacter << '\n';
			exit(EXIT_FAILURE);
		}
}

/* Below generates the sequence that is used for each character from the user input. *
 * This sequence is used as part of the equation to get the probability of a word    */
inline string generateSequence(string word, int currentIndex)
{
	int test = currentIndex - 1;

	/* This checks if a character does not exist on the current character indexed from the user input string *
	 * If so, there is no character to use as a sequence.                                                    */
	if (currentIndex - 1 < 0)
		return "nothing before";

	/* This checks if only one character exist on the current character indexed from the user input string *
	 * If so, only one character is used as a sequence.                                                    */
	stringstream ss;
	if (currentIndex - 2 < 0)
	{
		ss << "only ";
		ss << (char)toupper(word[currentIndex - 1]);
		ss << " before";
	}
	/* Below creates a sequence out of the previous 2 characters of a string relative to the index character. */
	else
	{
		ss << (char)toupper(word[currentIndex - 2]);
		ss << (char)toupper(word[currentIndex - 1]);
	}
	return ss.str();
}

/* Below converts a string into all upper case.*/
inline string toUpper(string word)
{
	string upperCaseStr;

	for (unsigned int i = 0; i < word.length(); i++)
	{
		upperCaseStr += toupper(word[i]);
	}
	return upperCaseStr;
}

/* Below calculates the probability of a user input string. */
long double calculateProbability(string word, map<string, long double> &probabilities)
{
	long double probability = 1;
	stringstream ss;

	cout << "P(\"" << toUpper(word) << "\") = ";

	/* The for loop creates a key by interating through the characters of a string.					 *
	 * Each character is used along side a sequence based on the previous two characters of a string *
	 * if it exists. From there, the probabilities data structure is used to get the probability	 *
	 * of the character sequence relationship to calculate the probability of the word.				 */
	for (unsigned int i = 0; i < word.length(); i++)
	{
		ss << (char)toupper(word[i]);
		ss << "|";
		ss << generateSequence(word, i);
		cout << "P(\"" << ss.str() << "\")" << (word.length() == ((int)i + 1) ? ";\n" : " * ");
		probability *= probabilities.at(ss.str());
		ss.str(std::string());
	}

	cout << "\n";

	return probability;
}
