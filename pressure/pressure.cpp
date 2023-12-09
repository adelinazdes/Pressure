// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <clocale>

#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <algorithm>

#include <fixed/fixed.h>
#include <pde_solvers/pde_solvers.h>


using namespace std;

struct pipe
{
    double L, // протяженность участка
        V, //скорость нефти
        D, //диаметр внутр.
        D_vnesh, //диаметр внешний
        b, //толщина стенки
        abc, //абсолютная шероховатость в м
        z_0, z_L, //высотные отметки начала,конца 
        ro, //плотность
        u, // кинематическая вязкость Стоксы в м2/с
        Q, //расход м3/ч
        p_L,// давление в конце участка
        lambda;//коэфф.гидравл.сопротивления
};


double pressure(struct pipe myPipe) {
    double  p_0;
 p_0 = (myPipe.p_L / (myPipe.ro * M_G) - myPipe.z_0 + myPipe.z_L + myPipe.lambda * (myPipe.L / myPipe.D) * pow(myPipe.V, 2) / (2 * M_G)) * (myPipe.ro * M_G);
    
 return p_0;
    }

int main()
{
    double  Re;
    
    setlocale(LC_ALL, "Russian");
    //Данные по трубопроводу в СИ
    pipe myPipe;
    myPipe.p_L = 0.6e6; 
    myPipe.L = 80e3;
    myPipe.D_vnesh = 720e-3;
    myPipe.b = 10e-3;
    myPipe.z_0 = 50;
    myPipe.z_L = 100;
    myPipe.ro = 870;
    myPipe.u = 15e-6;   
    myPipe.Q = 3500; 
    myPipe.abc = 15e-6;  


    myPipe.D = myPipe.D_vnesh - 2 * myPipe.b;
    double Q = myPipe.Q / 3600;                     //перевод в м3/с
    myPipe.V = 4 * Q / (3.14 * pow(myPipe.D, 2));      //вычисляем скорость нефти 
   
    Re = myPipe.V* myPipe.D/ myPipe.u;
    double relative_roughness = myPipe.abc/myPipe.D;    //вычисляем относ.шероховатость
    myPipe.lambda = hydraulic_resistance_isaev(Re, relative_roughness);
   
    double p_0 = pressure(myPipe);   //присваиваем значения из функции pressure
    cout << "Результат: p_0 = " << p_0 << " Па";

}