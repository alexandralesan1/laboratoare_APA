#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;


int fib1(int n) {
    if (n < 2)
        return n;
    else
        return fib1(n - 1) + fib1(n - 2);
}

int fib2(int n) {
    if (n < 0) {
        cout << "Valoarea lui n nu poate fi negativa.\n";
        return -1;
    }
    if (n == 0) return 0; 
    if (n == 1) return 1; 

    int i = 1, j = 0, temp;
    for (int k = 2; k <= n; k++) { 
        temp = i + j;
        j = i;
        i = temp;
    }
    return i; 
}

int fib3(int n) {
    if (n < 0) {
        cout << "Valoarea lui n nu poate fi negativa.\n";
        return -1;
    }

    int i = 1, j = 0, k = 0, h = 1, t;
    while (n > 0) {
        if (n % 2 == 1) {
            t = j * h;
            j = i * h + j * k + t;
            i = i * k + t;
        }
        t = h * h;
        h = 2 * k * h + t;
        k = k * k + t;
        n /= 2;
    }
    return j;
}


long long totalExecTime = 0;


long long analizaFib1(int n) {
    const int limita = 40;

    if (n < 0) {
        cout << "Valoarea lui n nu poate fi negativa.\n";
        return -1; 
    }

    if (n > limita) {
        cout << "Valoarea lui n este prea mare pentru algoritmul recursiv. Alege o valoare mai mica de " << limita << ".\n";
        return 0;
    }

    auto start = high_resolution_clock::now();
    int rezultat = fib1(n);
    auto stop = high_resolution_clock::now();
    auto durata = duration_cast<microseconds>(stop - start);

    cout << "Fibonacci Recursiv (" << n << ") = " << rezultat << "\n";
    cout << "Timp de executie: " << durata.count() << " microsecunde\n";
    cout << "Complexitate estimata: O(2^n)\n";

    totalExecTime += durata.count(); 
    return durata.count(); 
}

long long analizaFib2(int n) {
    auto start = high_resolution_clock::now();
    int rezultat = fib2(n);
    auto stop = high_resolution_clock::now();
    auto durata = duration_cast<microseconds>(stop - start);

    if (rezultat >= 0) {
        cout << "Fibonacci Iterativ (" << n << ") = " << rezultat << "\n"; 
    }
    cout << "Timp de executie: " << durata.count() << " microsecunde\n";
    cout << "Complexitate estimata: O(n)\n";

    totalExecTime += durata.count(); 
    return durata.count(); 
}

long long analizaFib3(int n) {
    auto start = high_resolution_clock::now();
    int rezultat = fib3(n);
    auto stop = high_resolution_clock::now();
    auto durata = duration_cast<microseconds>(stop - start);

    if (rezultat >= 0) {
        cout << "Fibonacci Binar (" << n << ") = " << rezultat << "\n"; 
    }
    cout << "Timp de executie: " << durata.count() << " microsecunde\n";
    cout << "Complexitate estimata: O(log n)\n";

    totalExecTime += durata.count(); 
    return durata.count(); 
}


void analizaComplexitate(int n, long long execTime) {
    cout << "\nAnaliza complexitatii pentru n = " << n << " si timpul de executie " << execTime << " microsecunde:\n";

    if (execTime <= 0) {
        cout << "Nu a fost realizat niciun calcul valid.\n";
        return;
    }

    if (execTime > 1000000) { 
        cout << "Complexitate estimata: O(2^n) (foarte ineficient pentru n mare)\n";
    }
    else if (execTime < 1000) { 
        cout << "Complexitate estimata: O(n) sau mai bun.\n";
    }
    else {
        cout << "Complexitate estimata: O(n log n) sau O(n^2).\n";
    }
}


void afiseazaTimpTotal() {
    cout << "\nTimp total de executie pentru toate functiile apelate: " << totalExecTime << " microsecunde\n";
}

int main() {
    int optiune, n;
    long long execTime = 0;

    do {
        cout << "\nMENIU:\n";
        cout << "1. Fibonacci Recursiv\n";
        cout << "2. Fibonacci Iterativ\n";
        cout << "3. Fibonacci Binar (log n)\n";
        cout << "4. Analiza Complexitatii\n";
        cout << "5. Afiseaza Timpul Total de Executie\n"; 
        cout << "6. Iesire\n";
        cout << "Alegeti o optiune: ";
        cin >> optiune;

        if (optiune >= 1 && optiune <= 3) {
            cout << "Introduceti o valoare pentru n: ";
            cin >> n;
        }

        switch (optiune) {
        case 1:
            execTime = analizaFib1(n);
            break;
        case 2:
            execTime = analizaFib2(n);
            break;
        case 3:
            execTime = analizaFib3(n);
            break;
        case 4:
            analizaComplexitate(n, execTime);
            break;
        case 5:
            afiseazaTimpTotal(); 
            break;
        case 6:
            cout << "Iesire din program.\n";
            break;
        default:
            cout << "Optiune invalida. Incercati din nou.\n";
        }
    } while (optiune != 6);

    return 0;
}
