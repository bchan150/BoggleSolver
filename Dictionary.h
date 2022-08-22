#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int ALPHABET = 26;

struct Node {
	Node* letters[ALPHABET];
	bool isWord;
};

class Dictionary
{
public:
	Dictionary();
	Dictionary(string file);
	~Dictionary();
	void addWord(string word);
	bool isWord(string word);
	bool isPrefix(string word);
	int wordCount();

private:
	Node* root;
	int numWords;
	
	void deleteAll(Node* node); // Recursion function to delete all for deconstructor.
};

Dictionary::Dictionary() {
	// Procedure to create initial Node array.
	root = new Node;
	for (int i = 0; i < ALPHABET; i++)
		root->letters[i] = nullptr;
	root->isWord = false;
	numWords = 0;
}

Dictionary::Dictionary(string file) {
	// Open file.
	ifstream list;
	list.open(file);

	// Reused code to create Node array.
	root = new Node;
	for (int i = 0; i < ALPHABET; i++)
		root->letters[i] = nullptr;
	root->isWord = false;

	numWords = 0;

	// While loop that will add all words from the dictionary.
	string word;
	while (list >> word)
		addWord(word);

	// Dictionary closing.
	list.close();
}

Dictionary::~Dictionary() {
	deleteAll(root);
}

void Dictionary::addWord(string word) {
	Node* next = root;
	for (unsigned int i = 0; i < word.length(); i++) {
		int letter = (int)word[i] - (int)'a'; // Converting integer from character.
		if (next->letters[letter] == nullptr) { // Creates new node for array if the letter is nullptr.
			next->letters[letter] = new Node; // Reused code to create Node array.
			next = next->letters[letter];
			for (int i = 0; i < ALPHABET; i++)
				next->letters[i] = nullptr;
			next->isWord = false;
		}
		else
			next = next->letters[letter];
	}
	next->isWord = true;
	numWords++;
}

bool Dictionary::isWord(string word) {
	Node* next = root;
	for (unsigned int i = 0; i < word.length(); i++) {
		int letter = (int)word[i] - (int)'a'; // Converting integer from character.
		if (next->letters[letter] == nullptr)
			return false;
		else
			next = next->letters[letter];
	}
	return next->isWord;
}

bool Dictionary::isPrefix(string word) {
	Node* next = root;
	for (unsigned int i = 0; i < word.length(); i++) {
		int letter = (int)word[i] - (int)'a'; // Converting integer from character.
		if (next->letters[letter] == nullptr)
			return false;
		else
			next = next->letters[letter];
	}
	return true;
}

int Dictionary::wordCount() {
	return numWords;
}

void Dictionary::deleteAll(Node* node) {
	for (int i = 0; i < ALPHABET; i++) {
		if (node->letters[i] != nullptr)
			deleteAll(node->letters[i]);
	}
	delete node; // Base Case (to some extent?
}