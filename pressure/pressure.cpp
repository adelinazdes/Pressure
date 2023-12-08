// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <windows.h>

using namespace std;

int main()
{
    struct pipe
    {
        double L, dx, dt, V, D, b, abc, z_0, z_L, ro, u, Q;
    };

    //Данные по трубопроводу в СИ
    pipe myPipe;
    double lyambda, e, p_0, p_L, D, Re;
    p_L = 0.6e6;
    myPipe.L = 80e3;
    myPipe.D = 720e-3;
    myPipe.b = 10e-3;
    myPipe.z_0 = 50;
    myPipe.z_L = 100;
    myPipe.ro = 870;
    myPipe.u = 15e-6;   //15cCт
    myPipe.Q = 3500; //м3/ч
    myPipe.abc = 15e-6;         //абсолютная шероховатость в м
    D = myPipe.D - 2 * myPipe.b;
    double Q = myPipe.Q / 3600;
    myPipe.V = 4 * Q / (3.14 * pow(D, 2));

    Re = myPipe.V * D / myPipe.u;

    e = myPipe.abc / D; //относ. шероховатость
    if (Re < 2300)
        lyambda = 64 / Re;
    else if (Re > 500 / e) //Шифринсон
        lyambda = 0.11 * pow(e, 0.25);
    else if (Re > 2300) //Альтшуль
        lyambda = 0.11 * pow((e + 68 / Re), 0.25);

    p_0 = (p_L / (myPipe.ro * 9.81) - myPipe.z_0 + myPipe.z_L + lyambda * (myPipe.L / D) * pow(myPipe.V, 2) / (2 * 9.81)) * (myPipe.ro * 9.81);
    SetConsoleOutputCP(1251);
    cout << "Результат: p_0 = " << p_0 << " Па";
}