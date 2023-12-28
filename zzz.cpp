#include <iostream> // вводим библиотеку

#include <fstream> // вводим библиотеку 

using namespace std;

const int MAX_WALLETS = 10; // максимальное количество кошельков

const int MAX_CARDS = 10; // максимальное количество карточек 

const int MAX_CATEGORIES = 10; // максимальное количество категорий 

const int MAX_TRANSACTIONS = 100; // максимальное количество транзакции 

struct Wallet  // структура кошелька
{
	int id; // идентификатор кошелька

	int balance; // баланс
};

struct Card  // структура карточки
{
	int id; // идентификатор карточки

	int balance; // баланс
};

struct Category // структура категории 
{
	int id; // идентификатор категории

	char name[256]; // название категории
};

struct Transaction // структура транзакции
{
	int id; // идентификатор транзакции

	int walletId; // идентификатор кошелька

	int cardId; // идентификатор карты

	int categoryId; // идентификатор категории

	int amount; // сумма

	char date[11]; // дата
};

void createWallet(Wallet wallets[], int& numWallets) // функция создания кошелька
{
	if (numWallets >= MAX_WALLETS) // проверка на максимальное количество кошельков
    {
		cout << "Достигнуто максимальное количество кошельков." << endl; // если максимальное количество кошельков достигнуто, выводится сообщение об ошибке

		return; // выход из функции
    }

	Wallet newWallet; // создание нового кошелька

	newWallet.id = numWallets + 1; // увеличение идентификатора кошелька

	newWallet.balance = 0; // установка баланса кошелька в ноль

	wallets[numWallets++] = newWallet; // добавление нового кошелька в массив кошельков

	cout << "Кошелек, созданный с помощью ID: " << newWallet.id << endl; // вывод сообщения о создании кошелька
}

void createCard(Card cards[], int& numCards) // функция создания карточки
{
	if (numCards >= MAX_CARDS) // проверка на максимальное количество карточек
    {
		cout << "Достигнуто максимальное количество карточек." << endl; // если максимальное количество карточек достигнуто, выводится сообщение об ошибке

		return; // выход из функции
    }

	Card newCard; // создание новой карточки

	newCard.id = numCards + 1; // увеличение идентификатора карточки

	newCard.balance = 0; // установка баланса карточки в ноль

	cards[numCards++] = newCard; // добавление новой карточки в массив карточек

	cout << "Карта, созданная с использованием идентификатора: " << newCard.id << endl; // вывод сообщения о создании карточки
}

void createCategory(Category categories[], int& numCategories) // функция создания категории
{
	if (numCategories >= MAX_CATEGORIES) // проверка на максимальное количество категорий
    {
		cout << "Достигнуто максимальное количество категорий." << endl; // если максимальное количество категорий достигнуто, выводится сообщение об ошибке

		return; // выход из функции
    }

	Category newCategory; // создание новой категории

	newCategory.id = numCategories + 1; // увеличение идентификатора категории

	cout << "Введите название категории: "; // запрос на ввод названия категории

	cin >> newCategory.name; // считывание названия категории

	categories[numCategories++] = newCategory; // добавление новой категории в массив категорий

	cout << "Категория, созданная с идентификатором: " << newCategory.id << endl; // вывод сообщения о создании категории
}

void deposit(Wallet wallets[], int numWallets, Card cards[], int numCards) // функция пополнения, которая включает в себя все выше перечисленное 
{
	int walletId, cardId, amount; // идентификатор кошелька, идентификатор карты, сумма

	cout << "Введите идентификатор кошелька: "; // запрос на ввод идентификатора кошелька

	cin >> walletId; // считывание идентификатора кошелька

	if (walletId <= numWallets && walletId >= 1) // проверка идентификатора кошелька
    {
		cout << "Введите сумму для внесения депозита: "; // запрос на ввод суммы для внесения депозита

		cin >> amount; // считывание суммы для внесения депозита

		wallets[walletId - 1].balance += amount; // добавление суммы к балансу кошелька

		cout << "Сумма внесена успешно." << endl; // вывод сообщения об успешном внесении депозита
    }
	else // иначе
    {
		cout << "Неверный идентификатор кошелька." << endl; // вывод сообщения об ошибке
    }

	cout << "Введите идентификатор карты: "; // запрос на ввод идентификатора карты

	cin >> cardId; // считывание идентификатора карты

	if (cardId <= numCards && cardId >= 1) // проверка идентификатора карты
    {
		cout << "Введите сумму для внесения депозита: "; // запрос на ввод суммы для внесения депозита

		cin >> amount; // считывание суммы для внесения депозита

		cards[cardId - 1].balance += amount; // добавление суммы к балансу карты

		cout << "Сумма внесена успешно." << endl; // вывод сообщения об успешном внесении депозита
    }
	else // иначе
    {
		cout << "Недействительный идентификатор карты." << endl; // вывод сообщения об ошибке
    }
}

void spend(Wallet wallets[], int numWallets, Card cards[], int numCards, Category categories[], int numCategories, Transaction transactions[], int& numTransactions)  // функция расходов
{
	int walletId, cardId, categoryId, amount; // идентификатор кошелька, идентификатор карты, идентификатор категории, сумма

	cout << "Введите идентификатор кошелька: "; // запрос на ввод идентификатора кошелька

	cin >> walletId; // считывание идентификатора кошелька

	if (walletId <= numWallets && walletId >= 1) // проверка идентификатора кошелька
    {
		cout << "Введите идентификатор категории: "; // запрос на ввод идентификатора категории

		cin >> categoryId; // считывание идентификатора категории

		if (categoryId <= numCategories && categoryId >= 1) // проверка идентификатора категории
        {
			cout << "Введите сумму, которую нужно потратить: ";  // запрос на ввод суммы, которую нужно потратить

			cin >> amount; // считывание суммы, которую нужно потратить

			if (wallets[walletId - 1].balance >= amount)  // проверка на достаточность средств в кошельке
            {
				wallets[walletId - 1].balance -= amount; // вычитание суммы из баланса кошелька

				Transaction newTransaction; // новая транзакция

				newTransaction.id = numTransactions + 1; // идентификатор транзакции

				newTransaction.walletId = walletId; // идентификатор кошелька

				newTransaction.cardId = 0; // идентификатор карты

				newTransaction.categoryId = categoryId; // идентификатор категории

				newTransaction.amount = amount; // сумма

				transactions[numTransactions++] = newTransaction; // добавление транзакции в массив

				cout << "Расходы зафиксированы успешно." << endl; // вывод сообщения об успешном фиксировании расходов
            }
			else // иначе
            {
				cout << "Недостаточно средств в кошельке." << endl; // вывод сообщения об ошибке
            }
        }
		else // иначе
        {
			cout << "Неверный идентификатор категории." << endl; // вывод сообщения об ошибке
        }
    }
	else   // иначе
    {
		cout << "Неверный идентификатор кошелька." << endl; // вывод сообщения об ошибке
    }
}

void generateReport(Transaction transactions[], int numTransactions) // функция генерации отчета
{
	char date[11]; // дата

	cout << "Введите дату (ГГГГ-ММ-ДД):"; // запрос на ввод даты

	cin >> date; // считывание даты

	int totalExpenses = 0;  // общие расходы

	int totalIncome = 0; // общий доход

	for (int i = 0; i < numTransactions; i++) // цикл по всем транзакциям
    {
		if (strcmp(transactions[i].date, date) == 0) // сравнение даты с заданной
        {
			if (transactions[i].amount < 0) // если сумма меньше нуля
            {
				totalExpenses += transactions[i].amount; // добавление суммы к общим расходам
            }
			else // иначе
            {
				totalIncome += transactions[i].amount; // добавление суммы к общему доходу
            }
        }
    }

	cout << "Отчет на дату " << date << ":" << endl; // вывод отчета

	cout << "Общие расходы: " << totalExpenses << endl; // вывод общих расходов

	cout << "Общий доход: " << totalIncome << endl; // вывод общего дохода
}

void saveReports(Transaction transactions[], int numTransactions) //функция сохранения отчетов
{

	ofstream file; // поток для записи

	file.open("reports.txt"); // открытие файла

    if (!file) 
    {
		cout << "Ошибка при открытии файла." << endl; // вывод сообщения об ошибке

        return;
    }

	for (int i = 0; i < numTransactions; i++) // цикл по всем транзакциям
    {
		file << "Идентификатор транзакции: " << transactions[i].id << endl; // вывод идентификатора транзакции

		file << "Идентификатор кошелька: " << transactions[i].walletId << endl; // вывод идентификатора кошелька

		file << "Идентификатор карты: " << transactions[i].cardId << endl; // вывод идентификатора карты

		file << "Идентификатор категории: " << transactions[i].categoryId << endl; // вывод идентификатора категории

		file << "Сумма: " << transactions[i].amount << endl; // вывод суммы

		file << "Дата: " << transactions[i].date << endl; // вывод даты

        file << endl;
    }

	file.close(); // закрытие файла

	cout << "Отчеты сохраняются в файл." << endl; // вывод сообщения об успешном сохранении отчетов
}

int main() 
{
	setlocale(LC_ALL, "RUS"); // установка русского языка

	Wallet wallets[MAX_WALLETS]; // создание массива кошельков

	int numWallets = 0; // инициализация количества кошельков

	Card cards[MAX_CARDS]; // создание массива карточек

	int numCards = 0; // инициализация количества карточек

	Category categories[MAX_CATEGORIES]; // создание массива категорий

	int numCategories = 0; // инициализация количества категорий

	Transaction transactions[MAX_TRANSACTIONS]; // создание массива транзакции

	int numTransactions = 0; // инициализация количества транзакции

	int choice; // выбор пользователя

	do  // цикл меню
    {
		cout << "1. Создать кошелек" << endl; // вывод меню

		cout << "2. Создать карточку" << endl; // вывод меню

		cout << "3. Создать категорию" << endl; // вывод меню

		cout << "4. Депозит" << endl; // вывод меню

		cout << "5. Тратить" << endl; // вывод меню

		cout << "6. Сгенерировать отчет" << endl; // вывод меню

		cout << "7. Сохранение отчетов" << endl; // вывод меню

		cout << "8. Выход" << endl; // вывод меню

		cout << "Введите свой выбор: "; // запрос на ввод

		cin >> choice; // считывание

		switch (choice)  // проверка выбора
        {
		case 1: // создание кошелька
            createWallet(wallets, numWallets);
            break;
		case 2: // создание карточки
            createCard(cards, numCards);
            break;
		case 3: // создание категории
            createCategory(categories, numCategories);
            break;
		case 4: // депозит
            deposit(wallets, numWallets, cards, numCards);
            break;
		case 5: // расход
            spend(wallets, numWallets, cards, numCards, categories, numCategories, transactions, numTransactions);
            break;
		case 6: // сгенерировать отчет
            generateReport(transactions, numTransactions); 
            break;
		case 7: // сохранение отчетов
            saveReports(transactions, numTransactions);
            break;
		case 8: // выход
            cout << "Выход." << endl; 
            break;
		default: // обработка ошибки
			cout << "Неправильный выбор." << endl; // вывод сообщения об ошибке
        }

		cout << endl; // переход на новую строку

    } 
	while (choice != 8); // цикл меню

	return 0; // возврат значения 0
}