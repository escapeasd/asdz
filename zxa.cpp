#include <iostream>

#include <fstream>

#include <ctime>

using namespace std;

void readWordsFromFile(const char* filename, char words[][20], int& wordCount) 
{

    ifstream file(filename);

    if (!file)
    {

        cout << "Ошибка при открытии файла!" << endl;

        exit(1);
    }

    wordCount = 0;

    while (file >> words[wordCount])
    {
        wordCount++;
    }

    file.close();
}

const char* getRandomWord(const char words[][20], int wordCount)
{
    int index = rand() % wordCount;

    return words[index];
}

bool isLetterInWord(const char* word, char letter)
{
    for (int i = 0; word[i] != '\0'; i++) 
    {
        if (word[i] == letter) 
        {
            return true;
        }
    }
    return false;
}

void displayGameStatus(const char* word, const char* guessedLetters, int attempts) 
{
    cout << "Искомое слово: ";

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isLetterInWord(guessedLetters, word[i]))
        {
            cout << word[i] << " ";
        }
        else 
        {
            cout << "_ ";
        }
    }
    cout << endl;

    cout << "Попыток осталось: " << attempts << endl;
}

int main() 
{
    setlocale(LC_ALL, "RUS");

    srand(time(0));

    const char* filename = "words.txt"; //проверил, работает =) можете создать файлик и попробовать поиграть

    char words[100][20];

    int wordCount;

    readWordsFromFile(filename, words, wordCount);

    const char* word = getRandomWord(words, wordCount);

    int wordLength = 0;

    while (word[wordLength] != '\0') 
    {
        wordLength++;
    }

    char guessedLetters[26];

    int guessedLetterCount = 0;

    int attempts = 6;

    bool gameOver = false;

    while (!gameOver) 
    {
        displayGameStatus(word, guessedLetters, attempts);

        char letter;

        std::cout << "Введите букву: ";

        std::cin >> letter;

        guessedLetters[guessedLetterCount] = letter;

        guessedLetterCount++;

        if (!isLetterInWord(word, letter))
        {
            attempts--;
        }

        bool allLettersGuessed = true;

        for (int i = 0; word[i] != '\0'; i++)
        {
            if (!isLetterInWord(guessedLetters, word[i]))
            {
                allLettersGuessed = false;

                break;
            }
        }

        if (allLettersGuessed || attempts == 0) 
        {
            gameOver = true;
        }
    }

    displayGameStatus(word, guessedLetters, attempts);

    cout << "Игра окончена!" << endl;

    cout << "Искомое слово: " << word << endl;

    cout << "Количество попыток: " << 6 - attempts << endl;

    return 0;
}