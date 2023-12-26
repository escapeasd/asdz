#include <iostream>

#include <fstream>

using namespace std;

const int MAX_WALLETS = 10;

const int MAX_CARDS = 10;

const int MAX_CATEGORIES = 10;

const int MAX_TRANSACTIONS = 100;

struct Wallet 
{
    int id;

    int balance;
};

struct Card 
{
    int id;

    int balance;
};

struct Category 
{
    int id;

    char name[256];
};

struct Transaction 
{
    int id;

    int walletId;

    int cardId;

    int categoryId;

    int amount;

    char date[11];
};

void createWallet(Wallet wallets[], int& numWallets)
{
    if (numWallets >= MAX_WALLETS)
    {
        cout << "Достигнуто максимальное количество кошельков." << endl;

        return;
    }

    Wallet newWallet;

    newWallet.id = numWallets + 1;

    newWallet.balance = 0;

    wallets[numWallets++] = newWallet;

    cout << "Кошелек, созданный с помощью ID: " << newWallet.id << endl;
}

void createCard(Card cards[], int& numCards)
{
    if (numCards >= MAX_CARDS)
    {
        cout << "Достигнуто максимальное количество карточек." << endl;

        return;
    }

    Card newCard;

    newCard.id = numCards + 1;

    newCard.balance = 0;

    cards[numCards++] = newCard;

    cout << "Карта, созданная с использованием идентификатора: " << newCard.id << endl;
}

void createCategory(Category categories[], int& numCategories) 
{
    if (numCategories >= MAX_CATEGORIES)
    {
        cout << "Достигнуто максимальное количество категорий." << endl;

        return;
    }

    Category newCategory;

    newCategory.id = numCategories + 1;

    cout << "Введите название категории: ";

    cin >> newCategory.name;

    categories[numCategories++] = newCategory;

    cout << "Категория, созданная с идентификатором: " << newCategory.id << endl;
}

void deposit(Wallet wallets[], int numWallets, Card cards[], int numCards) 
{
    int walletId, cardId, amount;

    cout << "Введите идентификатор кошелька: ";

    cin >> walletId;

    if (walletId <= numWallets && walletId >= 1) 
    {
        cout << "Введите сумму для внесения депозита: ";

        cin >> amount;

        wallets[walletId - 1].balance += amount;

        cout << "Сумма внесена успешно." << endl;
    }
    else
    {
        cout << "Неверный идентификатор кошелька." << endl;
    }

    cout << "Введите идентификатор карты: ";

    cin >> cardId;

    if (cardId <= numCards && cardId >= 1)
    {
        cout << "Введите сумму для внесения депозита: ";

        cin >> amount;

        cards[cardId - 1].balance += amount;

        cout << "Сумма внесена успешно." << endl;
    }
    else
    {
        cout << "Недействительный идентификатор карты." << endl;
    }
}

void spend(Wallet wallets[], int numWallets, Card cards[], int numCards, Category categories[], int numCategories, Transaction transactions[], int& numTransactions) 
{
    int walletId, cardId, categoryId, amount;

    cout << "Введите идентификатор кошелька: ";

    cin >> walletId;

    if (walletId <= numWallets && walletId >= 1)
    {
        cout << "Введите идентификатор категории: ";

        cin >> categoryId;

        if (categoryId <= numCategories && categoryId >= 1) 
        {
            cout << "Введите сумму, которую нужно потратить: ";

            cin >> amount;

            if (wallets[walletId - 1].balance >= amount) 
            {
                wallets[walletId - 1].balance -= amount;

                Transaction newTransaction;

                newTransaction.id = numTransactions + 1;

                newTransaction.walletId = walletId;

                newTransaction.cardId = 0;

                newTransaction.categoryId = categoryId;

                newTransaction.amount = amount;

                transactions[numTransactions++] = newTransaction;

                cout << "Расходы зафиксированы успешно." << endl;
            }
            else 
            {
                cout << "Недостаточно средств в кошельке." << endl;
            }
        }
        else 
        {
            cout << "Неверный идентификатор категории." << endl;
        }
    }
    else 
    {
        cout << "Неверный идентификатор кошелька." << endl;
    }
}

void generateReport(Transaction transactions[], int numTransactions)
{
    char date[11];

    cout << "Введите дату (ГГГГ-ММ-ДД):";

    cin >> date;

    int totalExpenses = 0;

    int totalIncome = 0;

    for (int i = 0; i < numTransactions; i++) 
    {
        if (strcmp(transactions[i].date, date) == 0) 
        {
            if (transactions[i].amount < 0)
            {
                totalExpenses += transactions[i].amount;
            }
            else
            {
                totalIncome += transactions[i].amount;
            }
        }
    }

    cout << "Отчет на дату " << date << ":" << endl;

    cout << "Общие расходы: " << totalExpenses << endl;

    cout << "Общий доход: " << totalIncome << endl;
}

void saveReports(Transaction transactions[], int numTransactions) 
{

    ofstream file;

    file.open("reports.txt"); 

    if (!file) 
    {
        cout << "Ошибка при открытии файла." << endl;

        return;
    }

    for (int i = 0; i < numTransactions; i++) 
    {
        file << "Идентификатор транзакции: " << transactions[i].id << endl;

        file << "Идентификатор кошелька: " << transactions[i].walletId << endl;

        file << "Идентификатор карты: " << transactions[i].cardId << endl;

        file << "Идентификатор категории: " << transactions[i].categoryId << endl;

        file << "Сумма: " << transactions[i].amount << endl;

        file << "Дата: " << transactions[i].date << endl;

        file << endl;
    }

    file.close();

    cout << "Отчеты сохраняются в файл." << endl;
}

int main() 
{
    setlocale(LC_ALL, "RUS");

    Wallet wallets[MAX_WALLETS];

    int numWallets = 0;

    Card cards[MAX_CARDS];

    int numCards = 0;

    Category categories[MAX_CATEGORIES];

    int numCategories = 0;

    Transaction transactions[MAX_TRANSACTIONS];

    int numTransactions = 0;

    int choice;

    do 
    {
        cout << "1. Создать кошелек" << endl;

        cout << "2. Создать карточку" << endl;

        cout << "3. Создать категорию" << endl;

        cout << "4. Депозит" << endl;

        cout << "5. Тратить" << endl;

        cout << "6. Сгенерировать отчет" << endl;

        cout << "7. Сохранение отчетов" << endl;

        cout << "8. Выход" << endl;

        cout << "Введите свой выбор: ";

        cin >> choice;

        switch (choice) 
        {
        case 1:
            createWallet(wallets, numWallets);
            break;
        case 2:
            createCard(cards, numCards);
            break;
        case 3:
            createCategory(categories, numCategories);
            break;
        case 4:
            deposit(wallets, numWallets, cards, numCards);
            break;
        case 5:
            spend(wallets, numWallets, cards, numCards, categories, numCategories, transactions, numTransactions);
            break;
        case 6:
            generateReport(transactions, numTransactions);
            break;
        case 7:
            saveReports(transactions, numTransactions);
            break;
        case 8:
            cout << "Выход." << endl;
            break;
        default:
            cout << "Неправильный выбор." << endl;
        }

        cout << endl;

    } 
    while (choice != 8);

    return 0;
}