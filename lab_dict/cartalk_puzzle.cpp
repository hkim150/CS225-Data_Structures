/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    /* Your code goes here! */
    ifstream words(word_list_fname);
    std::string w, w1, w2, w3;
    vector<StringTriple> ret;
    if(words.is_open()){
	while(getline(words, w)){
	    if(w.length() == 5){
		w1 = w.substr(1, w.length()-1);
		w2 = w.substr(0, 1);
		w3 = w.substr(2, w.length()-2);
		w2.append(w3);
		if(d.homophones(w1, w2)){ret.push_back(make_tuple(w, w1, w2));}
	    }
	}
    }
    return ret;
}
