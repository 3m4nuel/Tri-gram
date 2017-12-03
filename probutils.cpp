/*
* Author: Emmanuel Ayuyao Castillo
*
* Description:
* ----------------------------------------
* This files provides the functions used for the main program.
*/

#include "stdafx.h"

#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>


/* Below contains contants and a method to open up the file containing the probabilities values *
 * for each character and sequence relationship.											    */
using namespace std;

const char *filePath = "C:\\Users\\emman\\Box Sync\\classes\\Fall2017\\CS571\\homework\\hw8.1\\nlpProb.txt";

void openProbabilitiesFile(std::ifstream &inputStream)
{
	inputStream.open(filePath, std::ifstream::in);

	if (!inputStream.is_open())
	{
		cerr << "Couldn't open file " << filePath << '\n';
		exit(EXIT_FAILURE);
	}
}

/* Below contains the conastants and methods to parse the character, sequence and probabilities *
 * from the probabilities file, nlpProb.txt														*/
const int BUFF = 256;
const string PROB_MATCH_PATTERN = "(P\\()(\\w{1})(\\s\\|\\s)(.*?)(\\)\\s=\\s)(0.\\d{2})";
const int CHAR_MATCH_GROUP = 2;
const int SEQ_MATCH_GROUP = 4;
const int PROB_MATCH_GROUP = 6;

void loadProbabilities(ifstream &inputStream, map<string, long double> &probabilities)
{
	char line[BUFF];
	regex pattern(PROB_MATCH_PATTERN);
	cmatch match;

	/* Each line in the probabilities file is parsed using regular expression. *
	 * After it is inserted in a map data structure                            */
	while (inputStream.getline(line, BUFF))
		if (regex_search(line, match, pattern) && match.size() > 1)
			probabilities.insert(pair<string, long double>(match.str(CHAR_MATCH_GROUP) + "|" + match.str(SEQ_MATCH_GROUP), strtold(match.str(PROB_MATCH_GROUP).c_str(), nullptr)));

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