#include <iostream>
#include <conio.h>
#include <iomanip>
#include <random>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    const int minV = 1;
    const int maxV = 3;
    const int minkol = 6;
    const int maxkol = 12;

    random_device rd;       //Источник энтропии(короче беспорядок и случайность)
    mt19937 gen(rd());      //генератор случайного числа
    uniform_int_distribution<int> distrib0(minV, maxV);//преобразует выход генератора в нужный диапазон и тип
    int kolt = distrib0(gen);   //Количество товаров
    vector<double> V;       //Массив со степенью износа товара
    int kol;                //Количество участников
    double maxStav = 0;
    vector<int> draw;       //Массив куда буду записывать чудиков при равенстве максимальных ставок
    int numWin;
    int N;                  //Для выбора номера участника
    int count = 0;          //Для подсчета количества сценариев
    int kolWinT = 0;        //Для подсчета количества выигранных товаров
    double pol = 0.0;       //Для подсчета общей полезности стратегии
    double kfS = 0.7;       //Коэффициент стратегии
    double Rt;

    cout << "Введите номер человека за которым будем следить(от 1 до 12, но лучше от 1 до 6, тк с 7 по 12 не всегда учавствуют в торгах):";
    cin >> N;

    while (count < 1100) {
        for (int i = 0; i < kolt; i++) {
            uniform_real_distribution<double> distrib2(0.0, 1.0);
            double kf = distrib2(gen); //Коэфициент сохраненности товара
            V.push_back(kf);        //Добавляем степень износа
        }

        for (int i = 0; i < kolt; i++) {
            uniform_int_distribution<int> distrib(minkol, maxkol);
            kol = distrib(gen);
            vector<int> b;
            for (int j = 0; j < kol; j++) {
                uniform_int_distribution<int> distribS(1, 50);
                b.push_back(distribS(gen));     //Добавляем внутренние оценки стоимости товаров
            }
            for (int j = 0; j < kol; j++) {
                if (j + 1 == N) {
                    Rt = kfS * b[j];
                }
                else {
                    Rt = b[j];
                }
                if (maxStav == Rt) {
                    draw.push_back(j);
                }
                if (maxStav < Rt) {
                    draw.clear();
                    draw.push_back(j);
                    maxStav = Rt;
                }
            }
            if (draw.size() > 1) {
                uniform_int_distribution<int> distribDraw(0, draw.size() - 1);
                numWin = draw[distribDraw(gen)];    //Выбираем случайного победителя по ставке.
                if (numWin + 1 == N) {
                    pol += b[N - 1] * V[i] - maxStav;
                    kolWinT += 1;
                }

            }
            else {
                if (draw[0] + 1 == N) {
                    pol += b[N - 1] * V[i] - maxStav;
                    kolWinT++;
                }
            }
            maxStav = 0.0;
            draw.clear();
        }
        count++;
    }
    cout << "Коэффициент для внутренней стоимости: " << kfS << endl;
    cout << "Участник аунциона с номером " << N << " урвал себе " << kolWinT << " товар(а/ов)." << endl;
    cout << "Полезность участника составила " << pol;
    _getch();
}
