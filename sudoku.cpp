#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

// класс для представления ячейки головоломки Судоку
class Cell
{
public:
    int value;  // значение ячейки
    bool fixed; // флаг, указывающий, является ли ячейка неизменяемой
    Cell()
    {
        value = 0;
        fixed = false;
    }
};

class Sudoku
{
public:
    Sudoku();     // конструктор класса
    void print(); // метод для вывода головоломки на экран
    void play();  // метод для запуска игры
private:
    vector<vector<Cell>> grid;                 // матрица, представляющая головоломку Судоку
    void generateNew();                        // метод для генерации новой головоломки
    bool isValid(int row, int col, int value); // метод для проверки корректности установки значения в ячейку
    bool solve();                              // метод для решения головоломки
};
Sudoku::Sudoku()
{
    // создание пустой головоломки
    grid.resize(9, vector<Cell>(9));
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            grid[i][j] = Cell();
        }
    }
}

// метод для генерации новой головоломки
void Sudoku::generateNew()
{
    srand(time(NULL));
    // заполнение первой строки случайными значениями
    for (int j = 0; j < 9; j++)
    {
        int value = rand() % 9 + 1;
        while (!isValid(0, j, value))
        {
            value = rand() % 9 + 1;
        }
        grid[0][j].value = value;
        grid[0][j].fixed = true;
    }
    // заполнение оставшихся строк случайными значениями
    for (int i = 1; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (!grid[i][j].fixed)
            {
                int value = rand() % 9 + 1;
                while (!isValid(i, j, value))
                {
                    value = rand() % 9 + 1;
                }
                grid[i][j].value = value;
            }
        }
    }
}

// метод для вывода головоломки на экран
void Sudoku::print()
{
    cout << "-------------------------" << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << "| ";
        for (int j = 0; j < 9; j++)
        {
            if (grid[i][j].value != 0)
            {
                cout << grid[i][j].value << " ";
            }
            else
            {
                cout << "  ";
            }
            if (j % 3 == 2)
            {
                cout << "| ";
            }
        }
        cout << endl;
        if (i % 3 == 2)
        {
            cout << "-------------------------" << endl;
        }
    }
}

// метод для проверки корректности установки значения в ячейку
bool Sudoku::isValid(int row, int col, int value)
{
    // проверка строки и столбца
    for (int i = 0; i < 9; i++)
    {
        if (grid[row][i].value == value)
        {
            return false;
        }
        if (grid[i][col].value == value)
        {
            return false;
        }
    }
    // проверка квадрата 3x3
    int r = row / 3 * 3;
    int c = col / 3 * 3;
    for (int i = r; i < r + 3; i++)
    {
        for (int j = c; j < c + 3; j++)
        {
            if (grid[i][j].value == value)
            {
                return false;
            }
        }
    }
    return true;
}

// метод для решения головоломки
bool Sudoku::solve()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (grid[i][j].value == 0)
            {
                for (int k = 1; k <= 9; k++)
                {
                    if (isValid(i, j, k))
                    {
                        grid[i][j].value = k;
                        if (solve())
                        {
                            return true;
                        }
                        grid[i][j].value = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// метод для запуска игры
void Sudoku::play()
{
    generateNew();
    print();
    cout << "Enter row, column, and value (e.g. '3 5 4') or type 'solve' to see the solution." << endl;
    string input;
    while (true)
    {
        getline(cin, input);
        if (input == "solve")
        {
            solve();
            print();
            break;
        }
        int row = input[0] - '1';
        int col = input[2] - '1';
        int value = input[4] - '0';
        if (isValid(row, col, value))
        {
            grid[row][col].value = value;
            print();
        }
        else
        {
            cout << "Invalid move." << endl;
        }
    }
}

int main()
{
    Sudoku sudoku;
    sudoku.play();
    return 0;
}
