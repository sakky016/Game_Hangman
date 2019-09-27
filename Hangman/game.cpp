#include "pch.h"
#include "game.h"
#include<vector>
#include<map>
#include"resource.h"

//-----------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------
 // This should not be cleared as long as game is running
std::vector< WordDictionary_t> g_dictionaryVector; 

std::map<char, bool> g_guessedLetterMap;
std::map<char, int> g_buttonMap;

// HWND of dialog
HWND g_hwndDialog;

// Word for the current game round
WordDictionary_t g_gameWordDict;

// Guessed word for the current game round
std::string g_guessedWord;

// To keep track of number of tries remaining.
int g_triesRemaining = MAX_TRIES_ALLOWED;

// Starting score
int g_score = 0;

// To track if all letters of the game word were guessed correctly
bool g_bGuessedAllLetters = false;

//--------------------------------------------------------------------------------------------
// @name            : LoadDictionary
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void LoadDictionary()
{
    WordDictionary_t word1{"HELLO", "A form of greeting"};
    WordDictionary_t word2{"PLANET", "A heavenly body "};
    WordDictionary_t word3{"MAGNIFICENT", "extraordinary"};

    g_dictionaryVector.push_back(word1);
    g_dictionaryVector.push_back(word2);
    g_dictionaryVector.push_back(word3);
}

//--------------------------------------------------------------------------------------------
// @name            : PrepareButtonMapping
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void PrepareButtonMapping()
{
    g_buttonMap['A'] = btnA;
    g_buttonMap['B'] = btnB;
    g_buttonMap['C'] = btnC;
    g_buttonMap['D'] = btnD;
    g_buttonMap['E'] = btnE;
    g_buttonMap['F'] = btnF;
    g_buttonMap['G'] = btnG;
    g_buttonMap['H'] = btnH;
    g_buttonMap['I'] = btnI;
    g_buttonMap['J'] = btnJ;
    g_buttonMap['K'] = btnK;
    g_buttonMap['L'] = btnL;
    g_buttonMap['M'] = btnM;
    g_buttonMap['N'] = btnN;
    g_buttonMap['O'] = btnO;
    g_buttonMap['P'] = btnP;
    g_buttonMap['Q'] = btnQ;
    g_buttonMap['R'] = btnR;
    g_buttonMap['S'] = btnS;
    g_buttonMap['T'] = btnT;
    g_buttonMap['U'] = btnU;
    g_buttonMap['V'] = btnV;
    g_buttonMap['W'] = btnW;
    g_buttonMap['X'] = btnX;
    g_buttonMap['Y'] = btnY;
    g_buttonMap['Z'] = btnZ;
}

//--------------------------------------------------------------------------------------------
// @name            : InitializeGuessLetters
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void InitializeGuessLetters()
{
    for (char ch = 'A'; ch < 'Z'; ch++)
    {
        // Mark all letters as available for guess
        g_guessedLetterMap[ch] = false;

        // Enable all the buttons
        SetButtonState(ch, TRUE);
    }
}

//--------------------------------------------------------------------------------------------
// @name            : ResetGameVariables
//
// @description     : Called to reset game global variables. Called on every game round
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void ResetGameVariables()
{
    g_bGuessedAllLetters = false;
    g_triesRemaining = MAX_TRIES_ALLOWED;
    g_gameWordDict = {};
    g_guessedWord = "";
    g_guessedLetterMap.clear();
    g_buttonMap.clear();
}

//--------------------------------------------------------------------------------------------
// @name            : ResetStats
//
// @description     : These global variable values get reset only on new game. Should not be
//                    called if continuing a game round.
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void ResetStats()
{
    g_score = 0;
}

//--------------------------------------------------------------------------------------------
// @name            : InitializeGame
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void InitializeGame(HWND hwnd)
{
    // Generate a seed for this game
    srand(time(0));

    g_hwndDialog = hwnd;

    ResetGameVariables();
    ResetStats();
    UpdateStats();
    PrepareButtonMapping();
    InitializeGuessLetters();

    // Start the game now
    StartGameRound();
}

//--------------------------------------------------------------------------------------------
// @name            : ContinueGame
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void ContinueGame()
{
    ResetGameVariables();
    UpdateStats();
    PrepareButtonMapping();
    InitializeGuessLetters();

    // Start the game now
    StartGameRound();
}

//--------------------------------------------------------------------------------------------
// @name            : GetButtonIdFromLetter
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
int GetButtonIdFromLetter(char letter)
{
    return g_buttonMap[letter];
}

//--------------------------------------------------------------------------------------------
// @name            : UseGuessLetter
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void UseGuessLetter(char letter)
{
    g_guessedLetterMap[letter] = true;
}

//--------------------------------------------------------------------------------------------
// @name            : SetButtonState
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void SetButtonState(char letter, BOOL state)
{
    int buttonId = GetButtonIdFromLetter(letter);
    HWND hwndButton = GetDlgItem(g_hwndDialog, buttonId);
    EnableWindow(hwndButton, state);
}

//--------------------------------------------------------------------------------------------
// @name            : UpdateStats
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void UpdateStats()
{
    CString sScore;
    sScore.Format(L" %d ", g_score);

    CString sTriesRemaining;
    sTriesRemaining.Format(L" %d ", g_triesRemaining);
    
    SetDlgItemText(g_hwndDialog, lblScoreValue, sScore);
    SetDlgItemText(g_hwndDialog, lblTriesRemainingValue, sTriesRemaining);
}

//--------------------------------------------------------------------------------------------
// @name            : IsGameOver
//
// @description     : All the conditions of game over to be specified here
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
bool IsGameOver()
{
    if (g_gameWordDict.word == g_guessedWord)
    {
        g_bGuessedAllLetters = true;
        return true;
    }

    if (g_triesRemaining <= 0)
    {
        return true;
    }

    return false;
}

//--------------------------------------------------------------------------------------------
// @name            : OnGuessLetter
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void OnGuessLetter(char letter)
{
    UseGuessLetter(letter);
    SetButtonState(letter, FALSE);

    if (IsLetterPresentInWord(letter))
    {
        // Correct guess
        for (int i = 0; i < g_gameWordDict.word.size(); i++)
        {
            // Reveal all the guessed letters present in the word
            if (g_gameWordDict.word[i] == letter)
            {
                g_guessedWord[i] = letter;
                g_score++;
            }
        }

        ShowGuessedWord();
    }
    else
    {
        // Incorrect guess
        g_triesRemaining--;
    }

    UpdateStats();

    if (IsGameOver())
    {
        EndGameRound();
    }
}

//--------------------------------------------------------------------------------------------
// @name            : GetRandomWord
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
WordDictionary_t GetRandomWord()
{
    int index = rand() % g_dictionaryVector.size();
    WordDictionary_t word =  g_dictionaryVector[index];

    // Remove this word from dictionary.
    g_dictionaryVector.erase(g_dictionaryVector.begin() + index);

    return word;
}

//--------------------------------------------------------------------------------------------
// @name            : IsLetterPresentInWord
//
// @description     : 
//
// @returns         : true/false
//--------------------------------------------------------------------------------------------
bool IsLetterPresentInWord(const char letter)
{
    auto it = g_gameWordDict.word.find(letter);
    return it != std::string::npos;
}

//--------------------------------------------------------------------------------------------
// @name            : IsVowel
//
// @description     : 
//
// @returns         : true/false
//--------------------------------------------------------------------------------------------
bool IsVowel(char letter)
{
    return (letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U');
}

//--------------------------------------------------------------------------------------------
// @name            : ConcealLettersInWord
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void ConcealLettersInWord()
{
    for (int i = 0; i < g_guessedWord.size(); i++)
    {
        if (!IsVowel(g_guessedWord[i]))
        {
            g_guessedWord[i] = '-';
        }
    }
}

//--------------------------------------------------------------------------------------------
// @name            : ShowGuessedWord
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void ShowGuessedWord()
{
    std::string textToDisplay;

    // Do some modifications so that it looks better on display
    for (int i = 0; i < g_guessedWord.size(); i++)
    {
        textToDisplay.push_back(' ');
        textToDisplay.push_back(g_guessedWord[i]);
    }

    CString sTextToDisplay(textToDisplay.c_str());
    SetDlgItemText(g_hwndDialog, lblGameWord, sTextToDisplay);
}

void ShowHint()
{
    CString sTextToDisplay(g_gameWordDict.meaning.c_str());
    SetDlgItemText(g_hwndDialog, lblHint, sTextToDisplay);

    //HWND hwndButton = GetDlgItem(g_hwndDialog, btnShowHint);
    //EnableWindow(hwndButton, FALSE);
}

//--------------------------------------------------------------------------------------------
// @name            : StartGameRound
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void StartGameRound()
{
    if (g_dictionaryVector.size() > 0)
    {
        g_gameWordDict = GetRandomWord();
        std::string originalWord = g_gameWordDict.word;
        g_guessedWord = originalWord;
        ConcealLettersInWord();
        ShowGuessedWord();
    }
    else
    {
        //SetDlgItemText(g_hwndDialog, lblGameWord, L"No new words found in database!");
        MessageBox(g_hwndDialog, L"No new words found in database!", L"Cannot start new game", 0);
    }
}

//--------------------------------------------------------------------------------------------
// @name            : EndGameRound
//
// @description     : 
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void EndGameRound()
{
    CString sTitle(L"Tries exhausted");
    CString sMsg(L"Do you wish to try a new word?");
    if (g_bGuessedAllLetters)
    {
        sTitle = L"Congratulations!";
        sMsg = L"You guessed all the letters. Do you wish to continue?";
    }


    int choice = MessageBox(g_hwndDialog, sMsg, sTitle, MB_YESNO | MB_DEFBUTTON1);
    if (choice == IDYES)
    {
        ContinueGame();
    }
    else
    {
        SetDlgItemText(g_hwndDialog, lblGameWord, L"Thank you for playing!");
    }
}