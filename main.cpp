#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

#ifdef __WIN32__
#include <windows.h>
#endif

int LCG (int a, int c, int m, int x0) //функция ГПСЧ
{
    return (x0 * a + c ) % m;
}

int maxElement(std::vector <int> arr) //поиск ближайшей к максимуму массива степени двойки
{
    std::vector<int>::iterator res;
    int i;
    res = std::max_element(arr.begin(), arr.end());
    for (i = 2; i < *res; i *= 2);
    return i;
}

short gcd(int a, int b) //проверка: являются ли a и b взаимно простыми?
{
    return b ? gcd(b, a%b) : a;
}

int main()
{
    #ifdef __WIN32__
    SetConsoleOutputCP(65001);
    #endif

    static int N = 4;
    std::vector <int> row,
                    check; //вектор для проверки на соответствие заданной последовательности
    std::vector <bool> isEqual; //набор флагов для сравнений пар чисел. Последний элемент - флаг равенства всех пар чисел

    row.resize(N);
    check.resize(N);
    isEqual.resize(N+1);
    std::cout << "Введите 4 числа: " << std::endl;
    for (int i = 0; i < N; i++)
        std::cin >> row.at(i);
    std::cout << "Введенные числа: ";
    for (int i = 0; i < N; i++)
        std::cout << row.at(i) << " ";
    std::cout << std::endl;

    /**Поскольку чаще всего алгоритм используется
     * для m = 2^e, перебор будет осуществляться по
     * степеням двойки. Заметим, что m не может быть
     * меньше наибольшего заданного числа.**/
    int a = 1, c = 1, m = maxElement(row), 
        max_m = 65535,
        x0 = check.front() = row.front();
        
    for (int i = 0; i <= N; i++)
        isEqual.at(i) = false;

    for (; m < max_m; m*=2)
    {
        std::cout << "Параметры: m = " << m << std::endl;
        for (a = 1; a < m; a++)
        {
            for (c = 1; c < m; c++)
            {
                if (gcd(c, m) != 1)
                    continue;

                /**Заполнение массива для проверки и сравнения**/
                for (int i = 1; i < N; i++)
                    check.at(i) = LCG(a, c, m, check.at(i - 1));

                /**Сверка заданной цепочки с полученной при данных коэффициентах**/
                for (int i = 0; i < N; i++)
                    isEqual.at(i) = check.at(i) == row.at(i);

                /**Проверка на соответствие цепочки: если хотя бы один
                 * член цепочки не равен исходному, то пересчет идет заново**/
                for (int i = 0; i < N; i++)
                {
                    isEqual.back() = isEqual.at(i);
                    if (!isEqual.at(N))
                        break;
                }
                if (isEqual.back())
                    break;
            }
            if (isEqual.back())
                break;
        }
        if (isEqual.back())
                break;
    }

    if (isEqual.back())
    {
        //std::cout << "Параметры: a = " << a << ", c = " << c << ", m = " << m << ", x(n-1) = " << row.back() << std::endl;
        x0 = LCG(a, c, m, row.back());
        std::cout << "Следующее псевдослучайное число: (" << a << "*" << row.back() << " + " << c << ") mod " << m << " = " << x0 << std::endl;
    }
    else
        std::cout << "Число не может быть найдено" << std::endl;

    #ifdef __WIN32__
    system("pause");
    #endif

    return 0;
}