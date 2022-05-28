#include <iostream>
#include <Windows.h>
#include <time.h>
#include <fstream>
#include "Figure_Shape.h"

using namespace std;

	
void Task1() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int res = 0;
	double a = 0, b = 0, c = 0;
	cin >> a;
	cout << "b = ";
	cin >> b;
	LinEq LE(a, b);
	res = LE.Solve();
	cout << "\n a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "n = ";
	cin >> c;
	QuaEq QE(a, b, c);
	res = QE.Solve();
	if (res > 0) {
		cout << "\nx1 = " << QE.GetX1() << endl;
		if (a) cout << "x2 = " << QE.GetX2() << endl;
	}
}
void Task2() {
	int m = 0, n = 10;
	char fn[] = "file.bin";
	Shape** fig = new Shape * [n] {0};
	srand(time(0));

	SetRND(fig, n);
	cout << endl;

	for (size_t i = 0; i < n; i++) {
		fig[i]->Show();
		cout << endl;
	}

	Save(fig, n, fn);

	cout << "--------------------------------------\n\n";

	Shape** newfig = Load(m, fn);

	for (size_t i = 0; i < m; i++) {
		newfig[i]->Show();
		cout << endl;
	}


	for (size_t i = 0; i < n; i++)
		delete fig[i];
	delete fig;

	for (size_t i = 0; i < m; i++)
		delete newfig[i];
	delete newfig;
}

int main()
{

	/*Task1();*/
	Task2();
	return 0;
}
