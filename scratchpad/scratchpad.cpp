#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <boost/algorithm/string.hpp>
#include <random>
#include <chrono> 
#include <unordered_map>

using namespace std;

// A function that reads the lines from a text file and stores them as a vector of strings
vector<string> readWordsFile(string filename){
	ifstream file(filename);
	string str; 

	vector<string> words;

	while (getline(file, str)){
		words.push_back(boost::to_upper_copy(str.substr(0, str.size() - 1)));
	}

	return words;
}

int main(){
	vector<string> allTheWords = readWordsFile("misc/english.txt");
	vector<string> nineLetterWords;
    
    // Add all nine letter words
    for (auto it = allTheWords.begin(); it != allTheWords.end(); it++) {
		string word = *it;
        if (word.length() == 9) {
            nineLetterWords.push_back(word);
        }
    }

    // Randomly select 9 letter word
    uniform_int_distribution<int> distribution(0, nineLetterWords.size() - 1);
    mt19937 gen;
    gen.seed(random_device()());
    string currentNineLetterWord = nineLetterWords[distribution(gen)];
    
	cout << currentNineLetterWord << endl;

    // Scramble 9 letter word
    string chars = currentNineLetterWord;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(chars.begin(), chars.end() - 1, default_random_engine(seed));

    // Add characters and tally character count
	vector<char> characters;
	unordered_map<char, int> characterCount;
    for (int i = 0; i < chars.size(); i++) {
        characters.push_back(chars[i]);
		characterCount[chars[i]]++;
    }
    
	for (int i = 0; i < chars.size(); i++) {
        cout << characters[i] << endl;
    }

	for (auto const& pair : characterCount) {
		cout << "{" << pair.first << ":" << pair.second << "}" << endl;
	}

	cout << "Enter a word to see if it exists in 9 letter word." << endl;
	string word;
	cin >> word;
	// Check if 'word' exists in dictionary
	bool exists = find(allTheWords.begin(), allTheWords.end(), word) != allTheWords.end();
	if (exists) {
		// Check if characters of 'word' all exist in nine letter word
		unordered_map<char, int> tempCharacterCount = characterCount;
		for (int i = 0; i < word.length(); i++) {
			if (tempCharacterCount[word[i]] >= 1) {
				cout << "char exists" << endl;
				tempCharacterCount[word[i]]--;
			} else {
				cout << "char/word does not exist in nine letter word" << endl;
				break;
			}
		}
	} else {
		cout << "word does not exist" << endl;
	}

	vector<string> solution;
	int start = clock();
    // Find all words that are inside nine letter word
    for (auto it = allTheWords.begin(); it != allTheWords.end(); it++) {
		string word = *it;
		if (word.length() <= 9) {
			// Check if characters of 'word' all exist in nine letter word
			bool valid = true;
			unordered_map<char, int> tempCharacterCount = characterCount;
			for (int i = 0; i < word.length(); i++) {
				if (tempCharacterCount[word[i]] >= 1) {
					tempCharacterCount[word[i]]--;
				} else {
					valid = false;
					i = word.length();
				}
			}
			if (valid) {
				solution.push_back(word);
			}
		}
    }

	int end = clock();
	std::cout << "it took " << end - start << "ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "seconds to get solution." << std::endl;

	// cout << "SOLUTION:" << endl;
	// for (int i = 0; i < solution.size(); i++) {
	// 	cout << solution[i] << endl;
	// }

	return 0;
}
