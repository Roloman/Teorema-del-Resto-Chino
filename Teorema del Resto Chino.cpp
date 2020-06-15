// Teorema del Resto Chino.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <NTL/ZZ.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <cmath>
using namespace std;
using namespace NTL;

const int tam = 3;

ZZ modulo(ZZ num, ZZ mod) {

    num = num - ((num / mod) * mod);
    if (num < 0) {
        num += mod;
    }
    return num;
}

ZZ MaxComDiv(ZZ a, ZZ b)
{
    ZZ r = modulo(a, b);
    while (r != 0)
    {
        //cout << a << " = " << a / b << " (" << b << ") + " << a - (b * (a / b)) << endl;
        a = b;
        b = r;
        r = modulo(a, b);
    }
    //cout << a << " = " << a / b << " (" << b << ") + " << a - (b * (a / b)) << endl;
    return b;
}

ZZ Extendido_Euclides(ZZ a, ZZ b)
{
    ZZ q;
    ZZ r, r1, r2;
    ZZ s, s1, s2;
    ZZ t, t1, t2;

    r1 = a;
    r2 = b;
    s1 = (1);
    s2 = (0);
    t1 = (0);
    t2 = (1);

    while (r2 > 0) {

        q = r1 / r2;
        r = r1 - (q * r2);
        r1 = r2;
        r2 = r;

        s = s1 - (q * s2);
        s1 = s2;
        s2 = s;

        t = t1 - (q * t2);
        t1 = t2;
        t2 = t;
    }
    r = r1;
    s = s1;
    t = t1;
    if (s < 0)
        s = modulo(s, b);
    if (t < 0)
        t = modulo(t, a);
    //cout << a << "(" << s << ") + " << b << "(" << t << ") = " << r << endl;
    return s;
}

ZZ Inversa(ZZ a, ZZ b) {

    ZZ r = ZZ(0);
    ZZ c;
    if (MaxComDiv(a, b) == 1) {

        c = Extendido_Euclides(a, b);
        if (c < 0)
            c = modulo(c, b);

    }
    else
    {
        cout << a << " No tiene inversa" << endl;
        return ZZ(0);
    }
    return c;
}

bool Primos_Entre_Si(ZZ* Primos, ZZ tam) {

    for (int i = 0; i < tam; i++) {

        for (int j = i + 1; j < tam; j++) {
            if (MaxComDiv(Primos[i], Primos[j]) != 1 || Primos[i] == Primos[j]) {

                cout << Primos[i] << " y " << Primos[j] << " no son primos relativos" << endl;
                return false;
            }
        }
    }

    return true;
}


void Resto_Chino(ZZ* ai, ZZ* pi) {

    ZZ X = ZZ(0), P = ZZ(1);
    ZZ Pi[tam];
    ZZ qi[tam];
    ZZ x0[tam];

    if (Primos_Entre_Si(pi, ZZ(tam)) == 1) {

        for (int i = 0; i < tam; i++) {

            P *= pi[i];
        }

        for (int i = 0; i < tam; i++) {

            Pi[i] = P / pi[i];
            qi[i] = Inversa(Pi[i], pi[i]);
        }

        for (int i = 0; i < tam; i++) {

            x0[i] = modulo(ai[i] * Pi[i] * qi[i], P);
        }

        for (int i = 0; i < tam; i++) {

            X += x0[i];
        }
        X = modulo(X, P);
        //cout << "X = " << X << " (mod " << P << ")" << endl;
        //cout << "X = " << X << " + " << P << "k" << endl;
    }
    else
    {
        cout << "algo salio mal" << endl;
    }

    //Fines de no escritura
    for (int i = 0; i < tam; i++) {
        cout << "P" << i + 1 << " = " << Pi[i] << endl;
    }
    for (int i = 0; i < tam; i++) {
        cout << "q" << i + 1 << " = " << qi[i] << endl;
    }
    for (int i = 0; i < tam; i++) {
        cout << "x" << i + 1 << " = " << x0[i] << endl;
    }
    cout << "X = " << X << " (mod " << P << ")" << endl;
    cout << "X = " << X << " + " << P << "k" << endl;
}

int main()
{
    ZZ a[tam] = { ZZ(12), ZZ(19), ZZ(7) };
    ZZ p[tam] = { ZZ(25), ZZ(26), ZZ(27) };
    Resto_Chino(a, p);
    //cout << modulo(-255, 11) << endl;

}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
