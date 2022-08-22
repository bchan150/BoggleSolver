#include "Dictionary.h"
#include <ostream>

// Pre-Initializing
void SolveBoard(string board[4][4], Dictionary& dict, Dictionary& wordsFound, bool printBoard);
void SearchForWord(int row, int col, int step, string word, string board[4][4], Dictionary& dict, int used[4][4], Dictionary& wordsFound, bool printBoard);
void BoardPrint(string word, string board[4][4], int used[4][4], Dictionary& wordsFound);
void Menu(string board[4][4], bool& printBoard);
void FileSetup(string board[4][4], bool printBoard);

// Defining Functions:
void SolveBoard(string board[4][4], Dictionary& dict, Dictionary& wordsFound, bool printBoard) {
	// Variable creation for recursion.
	int used[4][4];

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++)
			used[r][c] = 0;
	}

	string word;

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			SearchForWord(r, c, 1, word, board, dict, used, wordsFound, printBoard);
		}
	}
}

void SearchForWord(int row, int col, int step, string word, string board[4][4], Dictionary& dict, int used[4][4], Dictionary& wordsFound, bool printBoard) {
	// Base Case: Out of bounds.
	if (row >= 4 || row < 0 || col >= 4 || col < 0)
		return;

	// Base Case: Used already.
	if (used[row][col] > 0)
		return;

	word += board[row][col];

	// Base Case: Not Prefix.
	if (dict.isPrefix(word) == false)
		return;

	used[row][col] = step;

	if (dict.isWord(word) && !wordsFound.isWord(word)) {
		wordsFound.addWord(word);
		if (printBoard)
			BoardPrint(word, board, used, wordsFound);
		else {
			ofstream output;
			output.open("output.txt", ios::app);

			cout << wordsFound.wordCount() << "\t" << word << endl;
			output << wordsFound.wordCount() << "\t" << word << endl;

			output.close();
		}
	}

	// Continuation Cases (In order: Down, Up, Left, Right, SW, SE, NW, NE)
	step++;
	SearchForWord(row, col + 1, step, word, board, dict, used, wordsFound, printBoard);
	SearchForWord(row, col - 1, step, word, board, dict, used, wordsFound, printBoard);
	SearchForWord(row - 1, col, step, word, board, dict, used, wordsFound, printBoard);
	SearchForWord(row + 1, col, step, word, board, dict, used, wordsFound, printBoard);
	SearchForWord(row + 1, col + 1, step, word, board, dict, used, wordsFound, printBoard);
	SearchForWord(row - 1, col + 1, step, word, board, dict, used, wordsFound, printBoard);
	SearchForWord(row - 1, col - 1, step, word, board, dict, used, wordsFound, printBoard);
	SearchForWord(row + 1, col - 1, step, word, board, dict, used, wordsFound, printBoard);

	// Remove Step
	used[row][col] = 0;
}

void BoardPrint(string word, string board[4][4], int used[4][4], Dictionary& wordsFound) {
	ofstream output;
	output.open("output.txt", ios::app);

	cout << "Word: " << word << endl;
	output << "Word: " << word << endl;
	cout << "Number of Words: " << wordsFound.wordCount() << endl;
	output << "Number of Words: " << wordsFound.wordCount() << endl;

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (used[r][c] > 0) {
				cout << "'" << board[r][c] << "'   ";
				output << "'" << board[r][c] << "'   ";
			}
			else {
				cout << " " << board[r][c] << "    ";
				output << " " << board[r][c] << "    ";
			}
		}

		for (int c = 0; c < 4; c++) {
			cout << " " << used[r][c] << "    ";
			output << " " << used[r][c] << "    ";
		}
		cout << endl;
		output << endl;
	}
	cout << endl;
	output << endl;

	output.close();
}

void Menu(string board[4][4], bool& printBoard) {
	// Separated from main in the case that random was implemented. Wasn't unfortunately.
	cout << "Enter Board" << endl
	<< "-----------" << endl;
	
	for (int r = 0; r < 4; r++) {
		cout << "Row " << r + 1 << ": ";
		for (int c = 0; c < 4; c++) {
			cin >> board[r][c];
		}
	}

	// Request for showing board.
	string show;

	cout << endl << "Show Board (y/n)?: ";
	cin >> show;

	if (show == "y")
		printBoard = true;
}

void FileSetup(string board[4][4], bool printBoard) {
	ofstream output;
	output.open("output.txt");

	output << "Board" << endl
		<< "-----" << endl;

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			output << board[r][c] << "    ";
		}
		output << endl;
	}

	output << endl
		<< "Board Output: ";
	
	if (printBoard)
		output << "TRUE"
		<< endl << endl;
	else
		output << "FALSE"
		<< endl << endl;


	output.close();
}

int main()
{
	// Personal touch to code.
	cout << "Boggle Solver v0.5 - Brian Chan" << endl
		<< "-------------------------------" << endl
		<< " - I hope the person running this code knows what they're doing." << endl
		<< " - Otherwise, we'll have issues." << endl
		<< " - Dictionary is hardcoded." << endl
		<< " - Please make sure your dictionary is called 'Dictionary.txt'." << endl
		<< " - Also, please make sure the dictionary is in the same directory as code." << endl
		<< " - On top of that, the output file generated in this program is 'output.txt'." << endl << endl;

	// Starting code for board generation.
	string board[4][4];
	Dictionary wordsFound;
	bool printBoard = false;

	Dictionary dict("Dictionary.txt");
	cout << dict.wordCount() << " words loaded." << endl << endl;

	Menu(board, printBoard);

	FileSetup(board, printBoard);

	// Code for board solving.
	SolveBoard(board, dict, wordsFound, printBoard);

	return 0;
}
