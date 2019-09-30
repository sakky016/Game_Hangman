#include "pch.h"
#include"resource.h"

#include<algorithm>
#include "game.h"
#include<fstream>
#include <sstream>
#include<map>
#include<vector>

//#define TEST

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

// Total score
int g_totalScore = 0;

// Score of current game round
int g_gameRoundScore = 0;

// On each correct guess, this is the score that would increment
// if hint was not used
int g_scoreMultiplier = SCORE_MULTIPLIER;

// To track if all letters of the game word were guessed correctly
bool g_bGuessedAllLetters = false;

// Flag to determine if hint was used for this game round
bool g_bIsHintUsed = false;

// Vector of high scores
std::vector<long int> g_highScores;


//--------------------------------------------------------------------------------------------
// @name            : SetWindow
//
// @description     : Stores dialog window
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void SetWindow(HWND hwnd)
{
    g_hwndDialog = hwnd;
}

//--------------------------------------------------------------------------------------------
// @name            : LoadDictionary
//
// @description     : Loads the words and meaning from the dictionary file into memory
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void LoadDictionary()
{
    DictionaryLoadStart();

    std::fstream dictionaryStream(DICTIONARY_FILE_NAME, std::ios::in);
    unsigned long int wordCount = 0;
    std::string line;

    while (getline(dictionaryStream, line))
    {
        // Remove all the double-quotes (")
        line.erase(remove(line.begin(), line.end(), '\"'), line.end());

        // Dictionary file is a csv file having format
        // <word>,<detail>,<meaning>
        WordDictionary_t dictData;
        size_t wordIndex = line.find(',');
        if (wordIndex != std::string::npos)
        {
            dictData.word = line.substr(0, wordIndex);
            std::transform(dictData.word.begin(), dictData.word.end(), dictData.word.begin(), ::toupper);

            std::string meaningStr = line.substr(wordIndex + 1);
            size_t meaningIndex = meaningStr.find(',');
            if (meaningIndex != std::string::npos)
            {
                std::string wordInfo = meaningStr.substr(0, meaningIndex);
                std::string wordMeaning = meaningStr.substr(meaningIndex + 1);
                dictData.meaning = "[ " + wordInfo + " ] " + wordMeaning;
            }
        }

        g_dictionaryVector.push_back(dictData);
        wordCount++;

#ifdef TEST
        if (wordCount >= 100)
        {
            break;
        }
#endif
    }// End of dictionary parsing

    dictionaryStream.close();
    DictionaryLoadEnd();
}

//--------------------------------------------------------------------------------------------
// @name            : LoadHighScoresFromFile
//
// @description     : Loads high score table with values in the file
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void LoadHighScoresFromFile()
{
    std::fstream stream(HIGH_SCORE_FILE_NAME, std::ios::in);
    std::string line;

    while (getline(stream, line))
    {
        int score = std::stoi(line);
        g_highScores.push_back(score);
    }

    stream.close();
}

//--------------------------------------------------------------------------------------------
// @name            : WriteHighScoresToFile
//
// @description     : Updates the highscore file with current high score table
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void WriteHighScoresToFile()
{
    std::fstream stream(HIGH_SCORE_FILE_NAME, std::ios::out);

    for (int i = 0; i < g_highScores.size(); i++)
    {
        stream << g_highScores[i];
        stream << std::endl;
    }

    stream.close();
}

//--------------------------------------------------------------------------------------------
// @name            : DictionaryLoadStart
//
// @description     : Called when the program starts parsing the dictionary file. It displays
//                    a message on screen so that users know that some operation is going on
//                    in background
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void DictionaryLoadStart()
{
    SetDlgItemText(g_hwndDialog, lblGameWord, L"  L O A D I N G   G A M E   D I C T I O N A R Y...");
}

//--------------------------------------------------------------------------------------------
// @name            : DictionaryLoadEnd
//
// @description     : Called when the dictionary has been loaded
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void DictionaryLoadEnd()
{
    SetDlgItemText(g_hwndDialog, lblGameWord, L"  Game Dictionary loaded");
}

//--------------------------------------------------------------------------------------------
// @name            : PrepareButtonMapping
//
// @description     : Creates a mapping of alphabet and the corresponding button ID.
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
// @name            : EnableGame
//
// @description     : Enables the game buttons
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void EnableGame()
{
    for (char ch = 'A'; ch <= 'Z'; ch++)
    {
        // Mark all letters as available for guess
        g_guessedLetterMap[ch] = false;

        // Enable all the buttons
        SetButtonState(ch, TRUE);
    }

    HWND hwndShowHintButton = GetDlgItem(g_hwndDialog, btnShowHint);
    EnableWindow(hwndShowHintButton, TRUE);

    HWND hwndSkipButton = GetDlgItem(g_hwndDialog, btnSkip);
    EnableWindow(hwndSkipButton, TRUE);

    // Clear Hint text
    SetDlgItemText(g_hwndDialog, lblHint, L"");
}

//--------------------------------------------------------------------------------------------
// @name            : DisableGame
//
// @description     : Disables the game buttons
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void DisableGame()
{
    for (char ch = 'A'; ch <= 'Z'; ch++)
    {
        // Disable all the letter buttons
        SetButtonState(ch, FALSE);
    }

    HWND hwndShowHintButton = GetDlgItem(g_hwndDialog, btnShowHint);
    EnableWindow(hwndShowHintButton, FALSE);

    HWND hwndSkipButton = GetDlgItem(g_hwndDialog, btnSkip);
    EnableWindow(hwndSkipButton, FALSE);
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
    g_bIsHintUsed = false;
    g_scoreMultiplier = SCORE_MULTIPLIER;
    g_triesRemaining = MAX_TRIES_ALLOWED;
    g_gameWordDict = {};
    g_guessedWord = "";
    g_guessedLetterMap.clear();
}

//--------------------------------------------------------------------------------------------
// @name            : InitializeGame
//
// @description     : Initializes the game module
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void InitializeGame(HWND hwnd)
{
    // Generate a seed for this game
    srand(time(0));
    g_hwndDialog = hwnd;
    PrepareButtonMapping();
    LoadHighScoresFromFile();
    DisableGame();

    SetDlgItemText(g_hwndDialog, lblGameWord, L" Click on \" New Game \" to begin");
}

//--------------------------------------------------------------------------------------------
// @name            : StartNewGame
//
// @description     : Called to start a new game. Dictionary is loaded.
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void StartNewGame()
{
    ResetGameVariables();
    LoadDictionary();
    EnableGame();
    StartGameRound();
    UpdateStats();
}

//--------------------------------------------------------------------------------------------
// @name            : ContinueGame
//
// @description     : Called to start a new game round
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void ContinueGame()
{
    ResetGameVariables();
    EnableGame();

    // Start the game now
    StartGameRound();

    UpdateStats();
}

//--------------------------------------------------------------------------------------------
// @name            : GetButtonIdFromLetter
//
// @description     : Fetches button ID from the character
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
// @description     : Marks the given letter as used.
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
// @description     : enables/disables a alphabet button
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
// @description     : Updates the values in the different text fields of the dialog after 
//                    each user action.
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void UpdateStats()
{
    // High scores
    // Sort the vector
    sort(g_highScores.begin(), g_highScores.end(), std::greater<>());
    SendDlgItemMessage(g_hwndDialog, lstHighScore, LB_RESETCONTENT, 0, 0);

    for (size_t i = 0; i < g_highScores.size(); i++)
    {
        CString sHighScore;
        sHighScore.Format(L"%-2d) %-5d ", i+1, g_highScores[i]);
        SendDlgItemMessage(g_hwndDialog, lstHighScore, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)sHighScore);
    }

    // Score
    CString sScore;
    sScore.Format(L" %d ", g_totalScore);
    SetDlgItemText(g_hwndDialog, lblScoreValue, sScore);

    // Tries remaining
    CString sTriesRemaining;
    sTriesRemaining.Format(L" %d ", g_triesRemaining);
    SetDlgItemText(g_hwndDialog, lblTriesRemainingValue, sTriesRemaining);

    // Score Multiplier
    CString sScoreMultiplier;
    sScoreMultiplier.Format(L" %d ", g_scoreMultiplier);
    SetDlgItemText(g_hwndDialog, lblScoreMultiplier, sScoreMultiplier);

    // Max points that can be scored in this round
    int scoreable = 0;
    for (size_t i = 0; i < g_guessedWord.size(); i++)
    {
        if (g_guessedWord[i] == CONCEALED_LETTER)
        {
            scoreable++;
        }
    }

    scoreable = scoreable * g_scoreMultiplier;

    CString sScoreable;
    sScoreable.Format(L" %d ", scoreable);
    SetDlgItemText(g_hwndDialog, lblScoreable, sScoreable);
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
// @description     : Executed whenever a user presses any of the alphabet buttons. Checks
//                    if selected character is present in the game word or not.
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
        for (size_t i = 0; i < g_gameWordDict.word.size(); i++)
        {
            // Reveal all the guessed letters present in the word
            if (g_gameWordDict.word[i] == letter)
            {
                g_guessedWord[i] = letter;
                g_gameRoundScore += g_scoreMultiplier;
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
// @description     : Fetches a random word from the dictionary. Once a valid word has been
//                    selected for the game round, it is removed from the dictionary so as 
//                    to avoid repetition.
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
WordDictionary_t GetRandomWord()
{
    bool bRequiredWordFetched = false;
    WordDictionary_t word{};

    while (!bRequiredWordFetched)
    {
        int index = rand() % g_dictionaryVector.size();
        word = g_dictionaryVector[index];

        if (word.word.size() >= MIN_WORD_LENGTH)
        {
            bRequiredWordFetched = true;

            // Remove this word from dictionary.
            g_dictionaryVector.erase(g_dictionaryVector.begin() + index);
        }
    }

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
// @description     : Checks if a character is vowel
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
// @description     : Hide some of the letters as per parameter PERCENT_LETTERS_TO_REVEAL
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void ConcealLettersInWord()
{
    int lettersToHide = (float(100 - (PERCENT_LETTERS_TO_REVEAL % 100)) / 100) * g_guessedWord.size();
    int hiddenLetters = 0;

    // Hide random letters 
    while (hiddenLetters < lettersToHide)
    {
        int indexToHide = rand() % g_guessedWord.size();
        char ch = g_guessedWord[indexToHide];

        // If not already hidden
        if (ch != CONCEALED_LETTER)
        {
            // Check if any other index has same letter
            for (size_t i = 0; i < g_guessedWord.size(); i++)
            {
                if (g_guessedWord[i] == ch)
                {
                    g_guessedWord[i] = CONCEALED_LETTER;
                    hiddenLetters++;
                    if (hiddenLetters >= lettersToHide)
                    {
                        break;
                    }
                }
            }
        }
    }
}

//--------------------------------------------------------------------------------------------
// @name            : ShowGuessedWord
//
// @description     : Displays the game round word
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void ShowGuessedWord()
{
    std::string textToDisplay;

    // Do some modifications so that it looks better on display
    for (size_t i = 0; i < g_guessedWord.size(); i++)
    {
        textToDisplay.push_back(' ');
        textToDisplay.push_back(g_guessedWord[i]);
    }

    CString sTextToDisplay(textToDisplay.c_str());
    SetDlgItemText(g_hwndDialog, lblGameWord, sTextToDisplay);
}

//--------------------------------------------------------------------------------------------
// @name            : ShowHint
//
// @description     : Displays hint for the current word. Once used, it will reduce the points
//                    that can be scored in the current game round
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void ShowHint()
{
    CString sTextToDisplay(g_gameWordDict.meaning.c_str());
    SetDlgItemText(g_hwndDialog, lblHint, sTextToDisplay);
    
    // Disable the Hint button
    HWND hwndShowHintButton = GetDlgItem(g_hwndDialog, btnShowHint);
    EnableWindow(hwndShowHintButton, FALSE);

    // Update game variables
    g_bIsHintUsed = true;
    g_scoreMultiplier = g_scoreMultiplier / 2;

    UpdateStats();
}

//--------------------------------------------------------------------------------------------
// @name            : UpdateHighScore
//
// @description     : Maintains and updates the high score table. Writes down the data to file.
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void UpdateHighScore()
{
    if (g_totalScore > 0)
    {
        if (g_highScores.size() >= MAX_STORED_HIGHSCORES)
        {
            // If we have reached MAX_STORED_HIGHSCORES, then replace the least value
            // of score
            auto it_minElement = std::min_element(g_highScores.begin(), g_highScores.end());
            if (g_totalScore > * it_minElement)
            {
                *it_minElement = g_totalScore;
            }
        }
        else
        {
            g_highScores.push_back(g_totalScore);
        }

        // Write the updated high scores to file
        WriteHighScoresToFile();
    }
}

//--------------------------------------------------------------------------------------------
// @name            : StartGameRound
//
// @description     : Called at the beginning of each game round
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void StartGameRound()
{
    if (g_dictionaryVector.size() > 0)
    {
        g_gameRoundScore = 0;
        g_gameWordDict = GetRandomWord();
        std::string originalWord = g_gameWordDict.word;
        g_guessedWord = originalWord;
        ConcealLettersInWord();
        ShowGuessedWord();
    }
    else
    {
        MessageBox(g_hwndDialog, L"No new words found in database!", L"Cannot start new game", 0);
        DisableGame();
    }
}

//--------------------------------------------------------------------------------------------
// @name            : EndGameRound
//
// @description     : Called when game is over - either on winning or losing
//
// @returns         : Nothing
//--------------------------------------------------------------------------------------------
void EndGameRound()
{
    CString sTitle(L"Game Over");
    CString sMsg;
    CString sSolution(g_gameWordDict.word.c_str());
    sMsg = L"Tries exhausted. Correct word was [ " + sSolution + L" ] \nDo you wish to play again?";


    if (g_bGuessedAllLetters)
    {
        // On winning game round
        if (g_triesRemaining == MAX_TRIES_ALLOWED)
        {
            g_gameRoundScore *= SCORE_BONUS_FOR_PERFECT_GUESS;
            sTitle = L"Perfect!";
            sMsg.Format(L"You found all the letters without any incorrect guess and won %d points. \n\nDo you wish to continue?", g_gameRoundScore);
        }
        else
        {
            sTitle = L"Congratulations!";
            sMsg.Format(L"You guessed all the letters and won %d points. \n\nDo you wish to continue?", g_gameRoundScore);
        }

        g_totalScore += g_gameRoundScore;
    }
    else
    {
        // Since we could not guess the word, this round's score 
        // should not add up to the total score.
        g_gameRoundScore = 0;
        
        // Update the high score and write it down to file
        UpdateHighScore();

        // Reset the total score to 0 after High score table has been updated
        g_totalScore = 0;
    }

    int choice = MessageBox(g_hwndDialog, sMsg, sTitle, MB_YESNO | MB_DEFBUTTON1);
    if (choice == IDYES)
    {
        ContinueGame();
    }
    else
    {
        SetDlgItemText(g_hwndDialog, lblGameWord, L" ** Thank you for playing ** ");
        SetDlgItemText(g_hwndDialog, lblHint, L"");
        DisableGame();
        ResetGameVariables();
    }
}