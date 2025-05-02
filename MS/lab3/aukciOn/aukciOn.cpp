#include <iostream>
#include <conio.h>
#include <random>
using namespace std;

int main()
{
    const int minV = 1;
    const int maxV = 3;
    const int minkol = 6;
    const int maxkol = 12;
    
    random_device rd;       //Источник энтропии(короче беспорядок и случайность)
    mt19937 gen(rd());      //генератор случайного числа
    uniform_int_distribution<int> distrib0(minV, maxV);//преобразует выход генератора в нужный диапазон и тип
    int kolt = distrib0(gen);
    vector<double> V;       //Массив со степенью износа товара
    vector<double> x;
    vector<int> p;
    vector<double> u;

    for (int i = 0; i < kolt; i++) {
        uniform_real_distribution<double> distrib2(0.0, 1.0);
        int kf = distrib2(gen); //Коэфициент сохраненности товара
        V.push_back(kf);        //Добавляем степень износа
    }

    for (int i = 0; i < kolt; i++) {
        uniform_int_distribution<int> distrib(minkol, maxkol);             
        int kol = distrib(gen); //Количество участников
        vector<int> b;
        for (int j = 0; j < kol; j++) {
            uniform_int_distribution<int> distribS(1, 50);
            b.push_back(distribS(gen)); 
            cout << b[j] << " ";
        }
        cout << endl;
    }
}
