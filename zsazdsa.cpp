﻿#include <iostream> // использование стандартной библиотеки ввода-вывода

#include <fstream> // использование библиотеки для работы с файлами

#include <ctime> // использование библиотеки для работы с времен

#include <cstdlib> // использование библиотеки для работы с рандом

using namespace std; // использование пространства имен std

const int MAX_WORDS = 10; // максимальное количество слов

const int MAX_ATTEMPTS = 6; // максимальное количество попыток

const int MAX_WORD_LENGTH = 20; // максимальная длина слова

void loadWords(char words[][MAX_WORD_LENGTH + 1], int& numWords) // функция для загрузки словаря
{
    ifstream file("тут либо путь/либо просто название самого текстового файла, когда оба файла находятся в одной и той же директории"); // либо добавить текстовый файл в одну директорию вместе с кодом, либо же указать ПОЛНЫЙ путь к файлу через дабл-флеши

	if (!file) // если не удалось открыть файл
    {
		cout << "Ошибка с открытием." << endl; // сообщение об ошибке

		return; // выход из функции
    }

	char encryptedWord[MAX_WORD_LENGTH + 1]; // зашифрованное слово

	int i = 0; // счетчик слов

	while (file >> encryptedWord) // считывание очередного слова
    {
		for (int j = 0; encryptedWord[j] != '\0'; j++) // перебор символов
        {
			words[i][j] = encryptedWord[j] - 1; // шифрование
        }

		words[i][MAX_WORD_LENGTH] = '\0'; // завершение строки

		i++; // увеличение счетчика

    }

	numWords = i; // количество загруженных слов

	file.close(); // закрытие файла
}

int getRandomIndex(int max) // функция для получения случайного индекса
{
	return rand() % max; // возвращение случайного числа
}

void initializeGame(char word[], char guessedLetters[]) // функция для инициализации игры
{
	int wordLength = 0; // длина слова

	while (word[wordLength] != '\0') // пока не конец строки
    {
		guessedLetters[wordLength] = '_'; // заполнение "_"

		wordLength++; // увеличение счетчика
    }

	guessedLetters[wordLength] = '\0'; // завершение строки
}

bool isWordGuessed(char word[], char guessedLetters[]) // функция для проверки, угадано ли слово
{
	int i = 0; // счетчик

	while (word[i] != '\0') // пока не конец строки
    {
		if (word[i] != guessedLetters[i]) // если символы не совпадают
        {
			return false; // слово не угадано
        }

		i++; // увеличение счетчика
    }

	return true; // слово угадано
}

void printHangman(int attempts) // функция для печати спецсимволов
{
	cout << "  ____" << endl; // печать спецсимволов

	cout << "  |  |" << endl; // печать спецсимволов

	if (attempts >= 1) // если попытки больше 1
    {
		cout << "  |  O" << endl; // печать спецсимволов
    }

	if (attempts == 2) // если попытки равны 2
    {
		cout << "  |  |" << endl; // печать спецсимволов
    }
    else if (attempts == 3) // если попытки равны 3
    {
		cout << "  | \\|" << endl; // печать спецсимволов
    }
	else if (attempts >= 4) // если попытки больше 4
    {
		cout << "  | \\|/" << endl; // печать спецсимволов
    }

	if (attempts == 5) // если попытки равны 5
    {
		cout << "  | /" << endl; // печать спецсимволов
    }
	else if (attempts >= 6) // если попытки больше или равны 6
    {
		cout << "  | / \\" << endl; // печать спецсимволов
    }

	cout << "  |" << endl; // печать спецсимволов

	cout << "__|__" << endl; // печать спецсимволов

	cout << endl; // ...
}

void printGame(char guessedLetters[], int attempts) // функция для печати игры
{
	cout << "Угаданные слова: " << guessedLetters << endl; // печать угаданных слов

	printHangman(attempts); // печать спецсимволов
}

char getPlayerGuess() // функция для получения ввода игрока
{
    char guess; // . . .

	cout << "Попробуй угадать: "; // сообщение

	cin >> guess; // ввод

	cout << endl; // ...

	return guess; // возврат
}

bool isGuessCorrect(char word[], char guessedLetters[], char guess) // функция для проверки правильности ввода
{
	int i = 0; // счетчик

	bool correctGuess = false; // . . .

	while (word[i] != '\0') // пока не конец строки
    {
		if (word[i] == guess) // если символ совпадает
        {
			guessedLetters[i] = guess; // обновление угаданных символов

			correctGuess = true; // символ угадан
        }

		i++; // увеличение счетчика
    }

	return correctGuess; // возврат
}

void playGame(char word[], char guessedLetters[], int& attempts) // функция для запуска игры
{
	while (attempts < MAX_ATTEMPTS && !isWordGuessed(word, guessedLetters)) // пока не конец игры
    {
		printGame(guessedLetters, attempts); // печать игры

		char guess = getPlayerGuess(); // получение ввода игрока

		if (isGuessCorrect(word, guessedLetters, guess)) // проверка правильности ввода
        {
			cout << "Ты угадал!" << endl; // сообщение
        }
		else // если не угадал
        {
			cout << "Блин, не угадал! :(" << endl; // сообщение
			 
			attempts++; // увеличение попыток
        }

		cout << endl; // ...
    }
}

void printStats(int attempts, char word[]) // функция для печати статистики
{
	cout << "Игра закончена!" << endl; // сообщение

	cout << "Попыток: " << attempts << endl; // печать попыток

	cout << "Слово: " << word << endl; // печать слова
}

int main() // основная функция
{
	srand(time(0)); // инициализация генератора случайных чисел

	char words[MAX_WORDS][MAX_WORD_LENGTH + 1]; // словарь

	int numWords = 0; // количество загруженных слов

	loadWords(words, numWords); // загрузка словаря

	int randomIndex = getRandomIndex(numWords); // получение случайного индекса

	char word[MAX_WORD_LENGTH + 1]; // загруженное слово

	strcpy_s(word, words[randomIndex]); // копирование случайного слова

	char guessedLetters[MAX_WORD_LENGTH + 1]; // угаданные символы

	initializeGame(word, guessedLetters); // инициализация игры

	int attempts = 0; // попытки

	playGame(word, guessedLetters, attempts); // запуск игры

	printStats(attempts, word); // печать статистики

	return 0; // выход
}

//* Проверил работоспособность игры, все работает так, как требуется. Если будут проблемы относительно этой игры,
//* укажите их в комментариях к домашнему заданию. Спасибо *//