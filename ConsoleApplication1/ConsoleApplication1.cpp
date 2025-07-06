#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

vector<string> loadWordsFromFile(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    string word;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return words;
    }

    while (file >> word) {
        words.push_back(word);
    }

    file.close();
    return words;
}

string selectRandomWord(const vector<string>& words) {
    srand(static_cast<unsigned int>(time(0)));
    int index = rand() % words.size();
    return words[index];
}

void displayWord(const string& word, const set<char>& guesses) {
    for (char c : word) {
        if (guesses.count(c)) {
            cout << c << ' ';
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}
void displayHangman(int wrongGuesses) {
    static const vector<string> hangmanStages = {
        "  +---+\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "     ===\n",

        "  +---+\n"
        "  O   |\n"
        "      |\n"
        "      |\n"
        "     ===\n",

        "  +---+\n"
        "  O   |\n"
        "  |   |\n"
        "      |\n"
        "     ===\n",

        "  +---+\n"
        "  O   |\n"
        " /|   |\n"
        "      |\n"
        "     ===\n",

        "  +---+\n"
        "  O   |\n"
        " /|\\  |\n"
        "      |\n"
        "     ===\n",

        "  +---+\n"
        "  O   |\n"
        " /|\\  |\n"
        " /    |\n"
        "     ===\n",

        "  +---+\n"
        "  O   |\n"
        " /|\\  |\n"
        " / \\  |\n"
        "     ===\n"
    };

    cout << hangmanStages[wrongGuesses] << endl;
}
int main() {
    vector<string> wordList = loadWordsFromFile("TextFile1.txt");

    if (wordList.empty()) {
        cout << "No words available. Exiting..." << endl;
        return 1;
    }

    string secretWord = selectRandomWord(wordList);
    set<char> guessedLetters;
    int maxTries = 6;
    int wrongGuesses = 0;

    cout << "Welcome to Hangman!\n";

    while (wrongGuesses < maxTries) {
        displayHangman(wrongGuesses);
        displayWord(secretWord, guessedLetters);

        cout << "Enter a letter: ";
        char guess;
        cin >> guess;

        if (guessedLetters.count(guess)) {
            cout << "You already guessed that letter.\n";
            continue;
        }

        guessedLetters.insert(guess);

        if (secretWord.find(guess) != string::npos) {
            cout << "Correct!\n";
        }
        else {
            cout << "Wrong!\n";
            wrongGuesses++;
        }

        bool allGuessed = true;
        for (char c : secretWord) {
            if (!guessedLetters.count(c)) {
                allGuessed = false;
                break;
            }
        }

        if (allGuessed) {
            cout << "You win! The word was: " << secretWord << endl;
            break;
        }
    }

    if (wrongGuesses == maxTries) {
        displayHangman(wrongGuesses);
        cout << "You lost! The word was: " << secretWord << endl;
    }

    return 0;
}