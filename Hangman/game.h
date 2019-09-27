#pragma once
#include<string>

//-----------------------------------------------------------------------
// Game settings
//-----------------------------------------------------------------------
const int MAX_TRIES_ALLOWED = 5;


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
void ContinueGame();
void InitializeGuessLetters();
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