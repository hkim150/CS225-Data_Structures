/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename){
    /* Your code goes here! */
    ifstream words(filename);
    std::string w, k;
    size_t idx = 0;
    if(words.is_open()){
	while(getline(words, w)){
	    k = w;
	    std::sort(k.begin(), k.end());
	    auto search = dict.find(k);
	    if(search == dict.end()){dict[k].push_back(w);}
	    else{
		while(idx < dict.at(k).size()){
		    if(dict[k][idx++] == w){return;}
		}
		dict[k].push_back(w);
	    }
	}
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    size_t idx = 0;
    for(auto& w : words){
	std::string k = w;
	std::sort(k.begin(), k.end());
	auto search = dict.find(k);
	if(search == dict.end()){dict[k].push_back(w);}
	else{
	    while(idx < dict.at(k).size()){
		if(dict[k][idx++] == w){return;}
	    }
	    dict[k].push_back(w);
	}
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    std::string k = word;
    std::sort(k.begin(), k.end());
    auto search = dict.find(k);
    if(dict.find(k) != dict.end()){return dict.find(k)->second;}
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<std::string>> ret;
    for(auto& d : dict){
	if(d.second.size() > 1){ret.push_back(d.second);}
    }
    return ret;
}
