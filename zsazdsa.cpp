#include <iostream>

#include <fstream>

#include <ctime>

#include <cstdlib>

using namespace std;

const int MAX_WORDS = 10;

const int MAX_ATTEMPTS = 6;

const int MAX_WORD_LENGTH = 20;

void loadWords(char words[][MAX_WORD_LENGTH + 1], int& numWords)
{
    ifstream file("тут либо путь/либо просто название самого текстового файла, когда оба файла находятся в одной и той же директории"); //либо добавить текстовый файл в одну директорию вместе с кодом, либо же указать ПОЛНЫЙ путь к файлу через дабл-флеши

    if (!file)
    {
        cout << "Ошибка с открытием." << endl;

        return;
    }

    char encryptedWord[MAX_WORD_LENGTH + 1];

    int i = 0;

    while (file >> encryptedWord)
    {
        for (int j = 0; encryptedWord[j] != '\0'; j++)
        {
            words[i][j] = encryptedWord[j] - 1;
        }

        words[i][MAX_WORD_LENGTH] = '\0';

        i++;

    }

    numWords = i;

    file.close();
}

int getRandomIndex(int max)
{
    return rand() % max;
}

void initializeGame(char word[], char guessedLetters[])
{
    int wordLength = 0;

    while (word[wordLength] != '\0')
    {
        guessedLetters[wordLength] = '_';

        wordLength++;
    }

    guessedLetters[wordLength] = '\0';
}

bool isWordGuessed(char word[], char guessedLetters[])
{
    int i = 0;

    while (word[i] != '\0')
    {
        if (word[i] != guessedLetters[i])
        {
            return false;
        }

        i++;
    }

    return true;
}

void printHangman(int attempts)
{
    cout << "  ____" << endl;

    cout << "  |  |" << endl;

    if (attempts >= 1)
    {
        cout << "  |  O" << endl;
    }

    if (attempts == 2)
    {
        cout << "  |  |" << endl;
    }
    else if (attempts == 3)
    {
        cout << "  | \\|" << endl;
    }
    else if (attempts >= 4)
    {
        cout << "  | \\|/" << endl;
    }

    if (attempts == 5)
    {
        cout << "  | /" << endl;
    }
    else if (attempts >= 6)
    {
        cout << "  | / \\" << endl;
    }

    cout << "  |" << endl;

    cout << "__|__" << endl;

    cout << endl;
}

void printGame(char guessedLetters[], int attempts)
{
    cout << "Угаданные слова: " << guessedLetters << endl;

    printHangman(attempts);
}

char getPlayerGuess()
{
    char guess;

    cout << "Попробуй угадать: ";

    cin >> guess;

    cout << endl;

    return guess;
}

bool isGuessCorrect(char word[], char guessedLetters[], char guess)
{
    int i = 0;

    bool correctGuess = false;

    while (word[i] != '\0')
    {
        if (word[i] == guess)
        {
            guessedLetters[i] = guess;

            correctGuess = true;
        }

        i++;
    }

    return correctGuess;
}

void playGame(char word[], char guessedLetters[], int& attempts)
{
    while (attempts < MAX_ATTEMPTS && !isWordGuessed(word, guessedLetters))
    {
        printGame(guessedLetters, attempts);

        char guess = getPlayerGuess();

        if (isGuessCorrect(word, guessedLetters, guess))
        {
            cout << "Ты угадал!" << endl;
        }
        else
        {
            cout << "Блин, не угадал! :(" << endl;

            attempts++;
        }

        cout << endl;
    }
}

void printStats(int attempts, char word[])
{
    cout << "Игра закончена!" << endl;

    cout << "Попыток: " << attempts << endl;

    cout << "Слово: " << word << endl;
}

int main()
{
    srand(time(0));

    char words[MAX_WORDS][MAX_WORD_LENGTH + 1];

    int numWords = 0;

    loadWords(words, numWords);

    int randomIndex = getRandomIndex(numWords);

    char word[MAX_WORD_LENGTH + 1];

    strcpy_s(word, words[randomIndex]);

    char guessedLetters[MAX_WORD_LENGTH + 1];

    initializeGame(word, guessedLetters);

    int attempts = 0;

    playGame(word, guessedLetters, attempts);

    printStats(attempts, word);

    return 0;
}