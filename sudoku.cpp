#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ROWS = 9; // количество строк
const int COLS = 9; // колиесвто стлобцов

void generatePuzzle(int puzzle[ROWS][COLS]);                       // генерирование пазла для игры
void displayMenu();                                                // выводит меню
void displayPuzzle(int puzzle[ROWS][COLS]);                        // выводит пазл
bool isValid(int puzzle[ROWS][COLS], int row, int col, int value); // проверяет правильное ли значение (судоку правила)
bool isComplete(int puzzle[ROWS][COLS]);                           // проверяет заполнен ли пазл
void playGame(int puzzle[ROWS][COLS]);                             // процесс игры
bool solveSudoku(int puzzle[ROWS][COLS]);                          // решение головоломки
bool findEmptyCell(int puzzle[ROWS][COLS], int &row, int &col);    // находит пустые клетки

int main() // основная функция
{
    int puzzle[ROWS][COLS];
    bool quit = false;

    srand(time(0));

    while (!quit) // пока пользователь не выбрал покинуть игру
    {
        displayMenu();
        int choice;    // переменная для управления меню
        cin >> choice; // ввод переменной меню

        switch (choice)
        {
        case 1: // если пользователь выбирает играть
            generatePuzzle(puzzle);
            playGame(puzzle);
            break;
        case 2:
            quit = true; // если пользователь хочет покинуть игру
            break;
        default:
            cout << "Неправильный ввод. Пожалуйста, введите 1 или 2." << endl; // проверка на правильный ввод
        }
    }

    cout << "Спасибо за игру!" << endl;

    return 0;
}

void generatePuzzle(int puzzle[ROWS][COLS])
{
    // Создает пустой пазл со всеми нулями
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            puzzle[row][col] = 0;
        }
    }

    // Заполняет диагональные ячейки случайными числами
    for (int box = 0; box < 3; box++)
    {
        for (int cell = 0; cell < 3; cell++)
        {
            int row = box * 3 + cell;
            int col = box * 3 + cell;
            int value;
            do
            {
                value = rand() % 9 + 1;
            } while (!isValid(puzzle, row, col, value));
            puzzle[row][col] = value;
        }
    }

    // Решает головоломку, используя обратный поиск
    solveSudoku(puzzle);

    // Убирает несколько цифр, чтобы создать головоломку
    int remainingCells = ROWS * COLS;
    while (remainingCells > 20)
    {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (puzzle[row][col] != 0)
        {
            puzzle[row][col] = 0;
            remainingCells--;
        }
    }
}

bool solveSudoku(int puzzle[ROWS][COLS])
{
    int row, col;

    // Если пустых ячеек нет, головоломка решена
    if (!findEmptyCell(puzzle, row, col))
    {
        return true;
    }

    // Пробует значение от 1 до 9
    for (int value = 1; value <= 9; value++)
    {
        // Если значение правильное
        if (isValid(puzzle, row, col, value))
        {
            // Делает ход
            puzzle[row][col] = value;

            // Рекурсия
            if (solveSudoku(puzzle))
            {
                return true;
            }

            // Если рекурсия завершилась неудачей, отмените ход
            puzzle[row][col] = 0;
        }
    }

    // Триггер обратного поиска
    return false;
}

bool findEmptyCell(int puzzle[ROWS][COLS], int &row, int &col)
{
    for (row = 0; row < ROWS; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            if (puzzle[row][col] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool isValid(int puzzle[ROWS][COLS], int row, int col, int value)
{
    // Проверка на допустимость значения
    if (value < 1 || value > 9)
    {
        return false;
    }

    // Проверка строки
    for (int i = 0; i < COLS; i++)
    {
        if (puzzle[row][i] == value && i != col)
        {
            return false;
        }
    }

    // Проверка столбца
    for (int i = 0; i < ROWS; i++)
    {
        if (puzzle[i][col] == value && i != row)
        {
            return false;
        }
    }

    // Проверка малого квадрата 3x3
    int boxRow = row - row % 3;
    int boxCol = col - col % 3;

    for (int i = boxRow; i < boxRow + 3; i++)
    {
        for (int j = boxCol; j < boxCol + 3; j++)
        {
            if (puzzle[i][j] == value && i != row && j != col)
            {
                return false;
            }
        }
    }

    return true;
}

void displayMenu()
{
    cout << "Добро пожаловать в Судоку!" << endl;
    cout << "Выберите:" << endl;
    cout << "1. Начать новую игру" << endl;
    cout << "2. Выйти" << endl;
    cout << "Введите Ваш выбор: ";
}

void displayPuzzle(int puzzle[ROWS][COLS])
{
    cout << "+-------+-------+-------+" << endl;
    for (int row = 0; row < ROWS; row++)
    {
        cout << "| ";
        for (int col = 0; col < COLS; col++)
        {
            if (puzzle[row][col] == 0)
            {
                cout << ". ";
            }
            else
            {
                cout << puzzle[row][col] << " ";
            }
            if ((col + 1) % 3 == 0)
            {
                cout << "| ";
            }
        }
        cout << endl;
        if ((row + 1) % 3 == 0)
        {
            cout << "+-------+-------+-------+" << endl;
        }
    }
}

bool isComplete(int puzzle[ROWS][COLS])
{
    // Проверяем каждую ячейку
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            // Если находим пустую ячейку, головоломка не завершена
            if (puzzle[row][col] == 0)
            {
                return false;
            }
        }
    }
    // Если все ячейки заполнены, головоломка завершена
    return true;
}

void playGame(int puzzle[ROWS][COLS])
{
    int row, col, value;

    while (!isComplete(puzzle))
    {
        // Вывод игрового поля
        displayPuzzle(puzzle);

        // Получение пользовательского ввода
        cout << "Введите строку (1-9), столбец (1-9) и значение (1-9), разделяйте пробелом: ";
        cin >> row >> col >> value;

        // Проверка на допустимость ввода
        if (row < 1 || row > 9 || col < 1 || col > 9 || value < 1 || value > 9)
        {
            cout << "Неправильный ввод. Пожалуйста, введите значение от 1 до 9." << endl;
        }
        else if (!isValid(puzzle, row - 1, col - 1, value))
        {
            cout << "Неправильный ход. Пожалуйста, попробуйте снова." << endl;
        }
        else
        {
            // Присваивание значения клетке
            puzzle[row - 1][col - 1] = value;
        }
    }

    // Вывод финального игрового поля
    displayPuzzle(puzzle);
    cout << "Поздравляем! Вы решили пазл!" << endl;
}
