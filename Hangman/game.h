#pragma once
#include<string>

//-----------------------------------------------------------------------
// Game settings
//-----------------------------------------------------------------------
const int MAX_TRIES_ALLOWED = 5;
const int MIN_WORD_LENGTH = 3;
const int PERCENT_LETTERS_TO_REVEAL = 50;
const int SCORE_MULTIPLIER = 10;
const int SCORE_BONUS_FOR_PERFECT_GUESS = 50;
const char CONCEALED_LETTER = '-';
const int MAX_STORED_HIGHSCORES = 10;
const std::string DICTIONARY_FILE_NAME = "dictionary.csv";
const std::string HIGH_SCORE_FILE_NAME = "highscores.txt";

//-----------------------------------------------------------------------
// Structures
//-----------------------------------------------------------------------
typedef struct WordDictionary_tag
{
    std::string word;
    std::string meaning;
}WordDictionary_t;

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
void InitializeGame(HWND);
void StartNewGame();
void ContinueGame();
void DisableGame();
void DictionaryLoadStart();
void DictionaryLoadEnd();
void SetWindow(HWND hwnd);
void InitializeGameButtons();
void LoadDictionary();
bool IsLetterPresentInWord(const char letter);
void OnGuessLetter(char letter);
void ShowGuessedWord();
void ShowHint();
void SetButtonState(char letter, BOOL state);
WordDictionary_t GetRandomWord();
void StartGameRound();
void EndGameRound();
void ResetGameVariables();
void UpdateStats();
void UpdateHighScore();