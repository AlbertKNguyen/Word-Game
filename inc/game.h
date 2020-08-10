#ifndef GAME_H
#define GAME_H

#include <string>
#include <random>
#include <chrono> 
#include <set>
#include <unordered_map>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <fstream>

namespace game {

class Game {
    private:
        void readWordsFile(std::string filename);
        std::set<std::string> allTheWords;
        std::vector<std::string> nineLetterWords;
        std::string currentNineLetterWord;
        std::vector<char> characters;
        std::unordered_map<char, int> characterCount;
        unsigned int highscore;

    public:
        Game();
        Game(std::string fileName);
        std::vector<char> generateList();
        bool check(std::string word);
        std::vector<std::string> getSolution();
        int getHighscore();
        void setHighscore(unsigned int highscore);
};

Game::Game() {
    this->currentNineLetterWord = "";
    this->highscore = 0;
    readWordsFile("misc/english.txt");

    // Add all nine letter words
    for (auto it = allTheWords.begin(); it != allTheWords.end(); it++) {
		std::string word = *it;
        if (word.length() == 9) {
            this->nineLetterWords.push_back(word);
        }
    }
}

Game::Game(std::string fileName) {
    this->currentNineLetterWord = "";
    this->highscore = 0;
    readWordsFile(fileName);

    // Add all nine letter words
    for (auto it = allTheWords.begin(); it != allTheWords.end(); it++) {
		std::string word = *it;
        if (word.length() == 9) {
            this->nineLetterWords.push_back(word);
        }
    }
}

void Game::readWordsFile(std::string filename){
	std::ifstream file(filename);
	std::string str; 

	while (getline(file, str)){
		this->allTheWords.insert(boost::to_upper_copy(str.substr(0, str.size() - 1)));
	}
}

std::vector<char> Game::generateList() {
    // Randomly select 9 letter word
    std::uniform_int_distribution<int> distribution(0, nineLetterWords.size() - 1);
    std::mt19937 gen;
    gen.seed(std::random_device()());
    this->currentNineLetterWord = this->nineLetterWords[distribution(gen)];
    
    // Scramble 9 letter word
    std::string chars = this->currentNineLetterWord;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(chars.begin(), chars.end(), std::default_random_engine(seed));

    // Reset 'characters' and 'characterCount'
    this->characters.clear();
    this->characterCount.clear();

    // Add characters and tally character count
    for (int i = 0; i < chars.size(); i++) {
        this->characters.push_back(chars[i]);
        this->characterCount[chars[i]]++;
    }

    return this->characters;
}

bool Game::check(std::string word) {

    // Check if 'word' exists in dictionary
    bool exists = allTheWords.count(word);
    
    if (exists) {
        // Check if characters of 'word' all exist in nine letter word
        std::unordered_map<char, int> tempCharacterCount = this->characterCount;
        for (int i = 0; i < word.length(); i++) {
            if (tempCharacterCount[word[i]] >= 1) {
                tempCharacterCount[word[i]]--;
            } else {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

std::vector<std::string> Game::getSolution() {
    std::vector<std::string> solution;

    // Find all words that are inside nine letter word
    for (std::string word : this->allTheWords) {
        if (word.length() <= 9) {
            // Check if characters of 'word' all exist in nine letter word
            bool valid = true;
            std::unordered_map<char, int> tempCharacterCount = this->characterCount;
            for (int i = 0; i < word.length(); i++) {
                if (tempCharacterCount[word[i]] >= 1) {
                    tempCharacterCount[word[i]]--;
                } else {
                    valid = false;
                    i = word.length(); // Stop going through invalid word
                }
            }
            if (valid) {
                solution.push_back(word);
            }
        }
    }

    return solution;
}

int Game::getHighscore() {
    return this->highscore;
}

void Game::setHighscore(unsigned int highscore) {
    this->highscore = highscore;
}


}

#endif