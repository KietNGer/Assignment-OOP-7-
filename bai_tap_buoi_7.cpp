#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Matrix;
class Vector
{
private:
    double *coords;
    int n;
public:

    Vector();
    Vector(int N, double x);
    Vector(const Vector &a);
    ~Vector();
    void Nhap();
    void Xuat();
    int Cong(const Vector &a);
    void NhanK(const double &k);
    int Tru(Vector a);
    double TichVoHuong(const Vector &a);
    friend Vector multiply(const Matrix &a, const Vector &b);
};

Vector ::Vector()
{
    coords = NULL;
}

Vector ::Vector(int N, double x)
{
    n = N;
    coords = new double[n];
    for(int i = 0; i < n; i++)
    {
        coords[i] = x;
    }
}

Vector ::Vector(const Vector & a)
{
    n = a.n;
    coords = new double[n];
    for(int i = 0; i < n; i++)
        coords[i] = a.coords[i];
}

Vector ::~Vector()
{
    if(coords != NULL)
        delete[] coords;
}

void Vector ::Nhap()
{
    cin >> n;
    coords = new double[n];
    for(int i = 0; i < n; i++)
    {
        cin >> coords[i];
    }
}

void Vector ::Xuat()
{
    for(int i = 0; i < n; i++)
    {
        cout << roundf(coords[i] * 100) / 100 << " ";
    }
    cout << endl;
}

int Vector ::Cong(const Vector &a)
{
    if(n != a.n)
        return 0;
    for(int i = 0; i < n; i++)
        coords[i] += a.coords[i];
    return 1;
}

void Vector ::NhanK(const double &k)
{
    for(int i = 0; i < n; i++)
        coords[i] *= k;
}

int Vector ::Tru(Vector a)
{
    if(n != a.n)
        return 0;
    for(int i = 0; i < n; i++)
    {
        coords[i] -= a.coords[i];
    }
    return 1;
}

double Vector ::TichVoHuong(const Vector &a)
{
    double s = 0;
    for(int i = 0; i < n; i++)
        s += coords[i] * a.coords[i];
    return s;
}

class Vector;
class Matrix
{
private:
    int dong; // dòng
    int cot; // cột
    double **elements;
public:
    Matrix();
    ~Matrix();
    Matrix(const Matrix & a);
    void Nhap();
    void Xuat();
    int Cong(const Matrix & a); // return 1 nếu cộng được
    void Nhan(const double & k);// Nhân với 1 số K
    int Nhan(const Matrix & a);// Nhân với 1 CMatrix, return 1 nếu nhân được
    friend Vector multiply(const Matrix &a, const Vector &b);
};

Matrix ::Matrix()
{
    dong = 0;
    cot = 0;
    elements = NULL;
}

Matrix ::~Matrix()
{
    if(elements == NULL)
        return;
    for(int i = 0; i < cot; i++)
    {
        delete[] elements[i];
        elements[i] = NULL;
    }
    delete[] elements;
    elements = NULL;
}

Matrix ::Matrix(const Matrix &a)
{
    dong = a.dong;
    cot = a.cot;
    elements = new double *[dong];
    for(int i = 0; i < dong; i++)
    {
        elements[i] = new double[cot];
    }
    for(int i = 0; i < dong; i++)
    {
        for(int j = 0; j < cot; j++)
        {
            elements[i][j] = a.elements[i][j];
        }
    }
}

void Matrix ::Nhap()
{
    cin >> dong >> cot;
    elements = new double *[dong];
    for(int i = 0; i < dong; i++)
    {
        elements[i] = new double[cot];
    }
    for(int i = 0; i < dong; i++)
    {
        for(int j = 0; j < cot; j++)
        {
            cin >> elements[i][j];
        }
    }
}

void Matrix ::Xuat()
{
    cout << "\n";
    for(int i = 0; i < dong; i++)
    {
        for(int j = 0; j < cot; j++)
        {
            cout << elements[i][j] << " ";
        }
        cout << endl;
    }
}

int Matrix ::Cong(const Matrix &a)
{
    if(!(dong != a.dong && cot != a.cot))
        return 0;
    for(int i = 0; i < dong; i++)
    {
        for(int j = 0; j < cot; j++)
            elements[i][j] += a.elements[i][j];
    }
    return 1;
}

void Matrix ::Nhan(const double &k)
{
    for(int i = 0; i < dong; i++)
    {
        for(int j = 0; j < cot; j++)
        {
             elements[i][j] *= k;
        }
    }
}

int Matrix::Nhan(const Matrix& a)
{
    if (cot != a.dong)
        return 0;

    double** elements1 = new double* [dong];
    for (int i = 0; i < dong; i++)
        elements1[i] = new double[a.cot];

    for (int i = 0; i < dong; i++)
    {
        for (int j = 0; j < a.cot; j++)
        {
            elements1[i][j] = 0;
            for (int k = 0; k < cot; k++)
                elements1[i][j] = elements1[i][j] + elements[i][k] * a.elements[k][j];
        }
    }
    for (int i = 0; i < dong; i++)
        delete[] elements[i];
    delete[] elements;
    dong = dong;
    cot = a.cot;
    elements = elements1;
    return 1;
}

Vector multiply(const Matrix &a, const Vector &b)
{
    if(a.cot != b.n)
    {
        cout << "Khong nhan duoc!\n";
        return Vector(0, 0);
    }
    Vector c(a.dong, 0);
    c.n = a.dong;
    for(int i = 0; i < a.dong; i++)
    {
        c.coords[i] = 0;
        for(int j = 0; j < b.n; j++)
        {
            c.coords[i] = c.coords[i] + b.coords[j] * a.elements[i][j];
        }
    }
    return c;
}

int main()
{
    Matrix c;
    c.Nhap();
    Vector d;
    d.Nhap();
    Vector s;
    s = multiply(c, d);
    s.Xuat();
    return 0;
}
