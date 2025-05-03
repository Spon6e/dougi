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
    vector<double> x(12, 0.0);       //Массив распределения
    vector<double> p(12, 0.0);       //Массив платежей(тип double потому что будет умножение при различных стратегиях)
    vector<double> u(12, 0.0);       //Массив полезности участников аукциона
    int kol;                //Количество участников
    int maxStav = 0;
    vector<int> draw;       //Массив куда буду записывать чудиков при равенстве максимальных ставок
    int numWin;

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
            if (maxStav == b[j]) {
                draw.push_back(j);
            }
            if (maxStav < b[j]) {
                draw.clear();
                draw.push_back(j);
                maxStav = b[j];
            }
        }
        if (draw.size() > 1) {
            uniform_int_distribution<int> distribDraw(0, draw.size() - 1);
            numWin = draw[distribDraw(gen)];    //Выбираем случайного победителя по ставке.
            x[numWin] += V[i];
            p[numWin] += b[numWin];
            u[numWin] += b[numWin] * V[i] - b[numWin];
        }
        else {
            numWin = draw[0];
            x[numWin] += V[i];
            p[numWin] += b[numWin];
            u[numWin] += b[numWin] * V[i] - b[numWin];
        }
        cout << fixed << setprecision(2) << "Товар " << i + 1 << endl;
        cout << setw(15) << "№ участника";
        for (int j = 0; j < 12; j++) {
            cout << setw(7) << j+1;
        }
        cout << endl;
        cout << setw(15) << "Распределение";
        for (int j = 0; j < 12; j++) {
            cout << setw(7) << x[j];
        }
        cout << endl;
        x[numWin] = 0;
        maxStav = 0;
        draw.clear();
    }
    cout << "Массив платежей:" << endl;
    cout << setw(15) << "№ участника";
    for (int j = 0; j < 12; j++) {
        cout << setw(7) << j+1;
    }
    cout << endl;
    cout << setw(15) << "Распределение";
    for (int j = 0; j < 12; j++) {
        cout << setw(7) << p[j];
    }
    cout << endl << "Массив полезности:" << endl;
    cout << setw(15) << "№ участника";
    for (int j = 0; j < 12; j++) {
        cout << setw(7) << j+1;
    }
    cout << endl;
    cout << setw(15) << "Распределение";
    for (int j = 0; j < 12; j++) {
        cout << setw(7) << u[j];
    }
    _getch();
}
