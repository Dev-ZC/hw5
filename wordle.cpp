#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void allCombinations(const std::string& in, const std::string& floating, std::set<std::string>& allCombos, size_t index, string& currWord, const std::set<std::string>& dict);

bool checkWord(const std::string& in, const std::string& floating, string word, const std::set<std::string>& dict);

bool inDict(const std::set<std::string>& dict, string word);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    //map<int, string> fixed; // Might not need, we'll see
    //int wordLength = in.length();
    set<string> allCombos;
    size_t index = 0;

    string placeholder(in.length(), ' ');
    allCombinations(in, floating, allCombos, index, placeholder, dict);

    //cout << "ooga booga" << endl;

    return allCombos;
}

// Define any helper functions here
void allCombinations(
    const std::string& in, 
    const std::string& floating, 
    std::set<std::string>& allCombos,
    size_t index, 
    string& currWord,
    const std::set<std::string>& dict)
{
    if (index >= in.length()){ // Stop adding if we index beyond word length
        if (checkWord(in, floating, currWord, dict)){
            //index = 0;
            //currWord.resize(in.length());
            //currWord.assign(in.length(), ' ');
            allCombos.insert(currWord);
        }
        return;

        //cout << "1" << endl;
    }

    if (in[index] != '-'){ // Skip if a fixed letter exists
        currWord[index] = in[index];
        allCombinations(in, floating, allCombos, index+1, currWord, dict);
        //cout << "2" << endl;
    } else {
        //cout << "3" << endl;
        for (char ch : floating) {
            currWord[index] = ch;
            allCombinations(in, floating, allCombos, index + 1, currWord, dict);
        }
        for (char ch = 'a'; ch <= 'z'; ++ch){
            currWord[index] = ch;
            allCombinations(in, floating, allCombos, index+1, currWord, dict);
        }
        //cout << "4" << endl;
    }
}

bool checkWord(const std::string& in, 
    const std::string& floating, 
    string word, 
    const std::set<std::string>& dict)
{
    // Checking length
    // This check is likely unnecessary as recursion already accounts for it
    if (word.length() != in.length()){ // Probably dont need either
        return false;
    }

    // Reverifying fixed letter positions
    // This check is likely unnecessary as recursion already accounts for it
    for (size_t i = 0; i < in.length(); ++i){ // Might not need
        if (word[i] != in[i] && in[i] != '-'){
            return false;
        }
    }

    // Reverifying floating letters
    // This check is likely unnecessary as recursion already accounts for it
    for (size_t i = 0; i < floating.length(); ++i){
        bool chFound = false;
        for (size_t j = 0; j < in.length(); ++j){
            if (word[j] == floating[i]){
                chFound = true;
                break;
            }
        }
        if (chFound == false){
            return false;
        }
    }

    // Check if word exists in dictionary
    if(!inDict(dict, word)){
        return false;
    }

    return true;
}

bool inDict(const std::set<std::string>& dict, string word){
    for(const std::string& dictWord : dict){
      if (dictWord == word){
        return true;
      }
    }

    return false;
}