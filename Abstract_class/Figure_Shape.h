#pragma once
#include <iostream>

using namespace std;
class Shape {
protected:
	double x, y, a, b;
	int type;
public:
	Shape(double x, double y, double a, double b, int t) :x(x), y(y), a(a), b(b), type(t) {}
	int GetType() { return type; }
	virtual void Show() = 0;
	virtual void Save(ofstream& fs) = 0;
	virtual void Load(ifstream& fs) = 0;
};

class Square : public Shape {
public:
	Square(double x, double y, double a) : Shape(x, y, a, 0, 1) {}
	void Show() { cout << "Square\t\tx = " << x << "\ty = " << y << "\ta = " << a << endl; }
	void Save(ofstream& fs) {
		fs.write(reinterpret_cast<char*>(&type), sizeof(type));
		fs.write(reinterpret_cast<char*>(&x), sizeof(x));
		fs.write(reinterpret_cast<char*>(&y), sizeof(y));
		fs.write(reinterpret_cast<char*>(&a), sizeof(a));
	}
	void Load(ifstream& fs) {
		fs.read((char*)&x, sizeof(x));
		fs.read((char*)&y, sizeof(y));
		fs.read((char*)&a, sizeof(a));
	}
};

class Rectan : public Shape {
public:
	Rectan(double x, double y, double a, double b) : Shape(x, y, a, b, 2) {}
	void Show() { cout << "Rectangle\tx = " << x << "\ty = " << y << "\ta = " << a << "\tb = " << b << endl; }
	void Save(ofstream& fs) {
		fs.write(reinterpret_cast<char*>(&type), sizeof(type));
		fs.write(reinterpret_cast<char*>(&x), sizeof(x));
		fs.write(reinterpret_cast<char*>(&y), sizeof(y));
		fs.write(reinterpret_cast<char*>(&a), sizeof(a));
		fs.write(reinterpret_cast<char*>(&b), sizeof(b));
	}
	void Load(ifstream& fs) {
		fs.read((char*)&x, sizeof(x));
		fs.read((char*)&y, sizeof(y));
		fs.read((char*)&a, sizeof(a));
		fs.read((char*)&b, sizeof(b));
	}
};

class Circle : public Shape {
public:
	Circle(double x, double y, double R) : Shape(x, y, R, 0, 3) {}
	void Show() { cout << "Circle\t\tx = " << x << "\ty = " << y << "\tR = " << a << endl; }
	void Save(ofstream& fs) {
		fs.write(reinterpret_cast<char*>(&type), sizeof(type));
		fs.write(reinterpret_cast<char*>(&x), sizeof(x));
		fs.write(reinterpret_cast<char*>(&y), sizeof(y));
		fs.write(reinterpret_cast<char*>(&a), sizeof(a));
	}
	void Load(ifstream& fs) {
		fs.read((char*)&x, sizeof(x));
		fs.read((char*)&y, sizeof(y));
		fs.read((char*)&a, sizeof(a));
	}
};

class Ellip : public Shape {
public:
	Ellip(double x, double y, double a, double b) : Shape(x, y, a, b, 4) {}
	void Show() { cout << "Ellipse\t\tx = " << x << "\ty = " << y << "\tR = " << a << "\tb = " << b << endl; }
	void Save(ofstream& fs) {
		fs.write(reinterpret_cast<char*>(&type), sizeof(type));
		fs.write(reinterpret_cast<char*>(&x), sizeof(x));
		fs.write(reinterpret_cast<char*>(&y), sizeof(y));
		fs.write(reinterpret_cast<char*>(&a), sizeof(a));
		fs.write(reinterpret_cast<char*>(&b), sizeof(b));
	}
	void Load(ifstream& fs) {
		fs.read((char*)&x, sizeof(x));
		fs.read((char*)&y, sizeof(y));
		fs.read((char*)&a, sizeof(a));
		fs.read((char*)&b, sizeof(b));
	}
};

void SetRND(Shape** mas, int n) {
	for (size_t i = 0; i < n; i++) {
		int R = 1 + rand() % 4;
		if (R == 1) mas[i] = new Square(3, 4, 10);
		else if (R == 2) mas[i] = new Rectan(3, 3, 5, 15);
		else if (R == 3) mas[i] = new Circle(3, 3, 20);
		else mas[i] = new Ellip(5, 5, 5, 10);
	}
}

void Save(Shape** mas, int n, const char* fn) {
	ofstream fs(fn, ios::out | ios::binary);
	if (!fs.is_open()) { cout << "Error write file\n"; return; }
	fs.write(reinterpret_cast<char*>(&n), sizeof(n));
	for (size_t i = 0; i < n; i++)
		if (mas[i])
			mas[i]->Save(fs);
	fs.close();
}

Shape* CreateShape(int type) {
	if (type == 1) return new Square(0, 0, 0);
	else if (type == 2) return new Rectan(0, 0, 0, 0);
	else if (type == 3) return new Circle(0, 0, 0);
	else return new Ellip(0, 0, 0, 0);
}

Shape** Load(int& m, const char* fn) {
	ifstream fs(fn, ios::in | ios::binary);
	if (!fs.is_open()) { cout << "Error read file\n"; return 0; }
	fs.read((char*)&m, sizeof(m));
	Shape** mas = new Shape * [m] {0};
	int type = 0;
	for (size_t i = 0; i < m; i++) {
		if (!fs.read((char*)&type, sizeof(type))) break;
		mas[i] = CreateShape(type);
		mas[i]->Load(fs);
	}
	fs.close();
	return mas;
}
class Eq {
protected:
	double x1, x2;
public:
	Eq() : x1(0), x2(0) {}
	double GetX1() { return x1; }
	double GetX2() { return x2; }
	virtual int Solve() = 0;
};

class LinEq : public Eq {
protected:
	double b, c;
public:
	LinEq(double b, double c) : b(b), c(c) {}
	int Solve() {
		if (b == 0 && c != 0)
			return -3;
		else {
			if (c == 0 && b == 0)
				return -2;
			x1 = -c / b;
			return 1;
		}
	}
};

class QuaEq : public LinEq {
	double a;
public:
	QuaEq(double a, double b, double c) : a(a), LinEq(b, c) {}
	int Solve() {
		if (a == 0) return LinEq::Solve();
		double D = b * b - 4 * a * c;
		int cr = 0;
		if (D == 0) {
			cr = 1;
			x1 = x2 = -b / (2 * a);
		}
		if (D > 0) {
			cr = 2;
			x1 = (b * -1 + sqrt(D)) / (2 * a);
			x2 = (b * -1 - sqrt(D)) / (2 * a);
		}
		return cr;
	}
};
}

