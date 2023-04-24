#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cmath>
#include <iomanip>
#include <ctime>
using namespace std;

const int WIDTH = 900;
const int HEIGHT = 500;
const double PI = 3.14159265;

void setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};
void show_menu(char s[])
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    setcur(0, 0);
    cout << "\n\n\n\n\n\n\n\n";
        SetConsoleTextAttribute(h, 3);
        cout << setw(65) << right << "---------------------" << endl;
        cout << setw(48) << right << "|   "; SetConsoleTextAttribute(h, 7); cout << "1. Заставка " << s[0]; SetConsoleTextAttribute(h, 3); cout << "   |" << endl
            << setw(48) << right << "|   "; SetConsoleTextAttribute(h, 7); cout << "2. Таблица " << s[1]; SetConsoleTextAttribute(h, 3); cout << "    |" << endl
            << setw(48) << right << "|   "; SetConsoleTextAttribute(h, 7); cout << "3. Графики " << s[2]; SetConsoleTextAttribute(h, 3); cout << "    |" << endl
        << setw(48) << right << "|   "; SetConsoleTextAttribute(h, 7); cout<< "4. Уравнения " << s[3]; SetConsoleTextAttribute(h, 3); cout << "  |" << endl
        << setw(48) << right << "|   "; SetConsoleTextAttribute(h, 7); cout<< "5. Интергал " << s[4]; SetConsoleTextAttribute(h, 3); cout <<"   |" <<endl
        << setw(48) << right << "|   "; SetConsoleTextAttribute(h, 7); cout << "6. Об авторе " << s[5]; SetConsoleTextAttribute(h, 3); cout << "  |" << endl
        << setw(48) << right << "|   "; SetConsoleTextAttribute(h, 7); cout << "7. Выход " << s[6]; SetConsoleTextAttribute(h, 3); cout << "      |" << endl
        << setw(65) << right << "---------------------" << endl;  SetConsoleTextAttribute(h, 7);
}
char menu_down(char s[])
{
    for (int i = 0; i < 7; i++)
    {
        if (s[i] == '<')
        {
            s[i] = ' ';
            s[i + 1] = '<';
            break;
        }
    }
    return *s;
}
char menu_up(char s[])
{
    for (int i = 0; i < 7; i++)
    {
        if (s[i] == '<')
        {
            s[i] = ' ';
            s[i - 1] = '<';
            break;
        }
    }
    return *s;
}


double max_arr(double a[], int N)
{
    double max = a[0];
    for (int i = 1; i < N; i++)
    {
        if (a[i] > max)
            max = a[i];
    }
    return max;
}
double min_arr(double a[], int N)
{
    double min = a[0];
    for (int i = 1; i < N; i++)
    {
        if (a[i] < min)
            min = a[i];
    }
    return min;
}
void cursor_off()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
double resh_urav(double x)
{
    double X = 2*x*pow(sin(x),2)-3*sqrt(x+cos(x));
    return X;
}
double resh_integral(double x)
{
    double y = ((x * x) * atan(x));
    return y;
}
double del_popol(double e, double a, double b)
{
    double c = 0, fc = 0;
    double fa = resh_urav(a), fb = resh_urav(b);
    bool flag = true;
    if (resh_urav(a) * resh_urav(b) > 0)
        flag = false;

    while (flag)
    {

        c = ((a + b) / 2.0);
        double fc = resh_urav(c);
        if (fabs(fc) < e)
            break;
        if (fc * fa < 0)
            b = c, fb = fc;
        else
            a = c, fa = fc;

    }
    if (flag)
        return c;
    else
        return 0;
    
   
}
double metod_hord(double e, double a, double b)
{
    double x0 = a, x1 = b, x2;
    while (fabs(resh_urav(x1)) > e)
    {
        x2 = x1 - resh_urav(x1) * (x1 - x0) / (resh_urav(x1) - resh_urav(x0));
        x0 = x1, x1 = x2;
    }
    return x1;
}
double self_integral(double x)
{
    return (pow(x, 2) * atan(x));
}
double integral_primougle(int n, double h, int a)
{
    double answ = 0;
    for (int i = 0; i < n; i++)
    {
        double dx = a + i * h + h / 2;
        answ += self_integral(dx);
    }
    return answ * h;
}
double integral_trap(int n, double h, int a, int b)
{
    double answ = (self_integral(a) + self_integral(b)) / 2;
    for (int i = 1; i < n; i++)
    {
        float dx = a + i * h;
        answ += self_integral(dx);
    }
    return h * answ;
}



void intro()
{
    system("cls");

    HWND handle = FindWindowA("ConsoleWindowClass", NULL);
    HDC hdc = GetDC(handle);
    HPEN hPen = CreatePen(PS_SOLID, 7, RGB(255, 255, 255)); //сплошная линия, толщиной 10 пикселей, цвет - синий
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));//сплошной черный
    SelectObject(hdc, hPen);// указываем перо 
    SelectObject(hdc, hBrush);//указываем кисть
    int dR = 13;
    for (int j=0; j<150;j++)
    {
        for (int i = 1; i <= 12; i++)
        {
            
            Ellipse(hdc, 50 + i * dR, 50 + i * dR, 400 - i * dR, 400 - i * dR);
            int color = rand() % 7;
            switch (color)
            {
            case(0):
                hPen = CreatePen(PS_SOLID, 7, RGB(255, 0, 0));
                break;
            case(1):
                hPen = CreatePen(PS_SOLID, 7, RGB(255, 127, 0));
                break;
            case(2):
                hPen = CreatePen(PS_SOLID, 7, RGB(255, 255, 0));
                break;
            case(3):
                hPen = CreatePen(PS_SOLID, 7, RGB(0, 255, 0));
                break;
            case(4):
                hPen = CreatePen(PS_SOLID, 7, RGB(0, 0, 255));
                break;
            case(5):
                hPen = CreatePen(PS_SOLID, 7, RGB(75, 0, 130));
                break;
            case(6):
                hPen = CreatePen(PS_SOLID, 7, RGB(144, 0, 255));
                break;
            }
            SelectObject(hdc, hPen);
        }
        Sleep(20);
        
            
        
    }
    _getch();
    system("cls");


}
void table()
{
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int a = 1, b = 3;
    const int N = 15;
    double mass_table_x[N], mass_table_y[N];
    double x = a, y;
    double dx = (double)(((fabs(b - a))) / (N - 1));
    cout << "y = x*ln(x)^2" << endl;
    for (int i = 0; i < N; i++)
    {
        mass_table_x[i] = x;
        y = x * (log(x) * log(x));
        mass_table_y[i] = y;
        x += dx;
    }
    cout<< "------------------------" << endl
        << "|    X    |     Y      |"<<endl
        << "------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        if (mass_table_y[i] == max_arr(mass_table_y, N))
        {
            cout << "| " << setw(8) << left << mass_table_x[i] << "| ";
            SetConsoleTextAttribute(h,4);
            cout << setw(9) << left << mass_table_y[i]; SetConsoleTextAttribute(h, 7);
            cout<< "  |" << endl;
            
        }
        else if (mass_table_y[i] == min_arr(mass_table_y, N))
        {
            cout << "| " << setw(8) << left << mass_table_x[i] << "| ";
            SetConsoleTextAttribute(h, 2);
            cout << setw(11) << left << mass_table_y[i]; SetConsoleTextAttribute(h, 7);
            cout<< "|" << endl;
            
        }
        else
           cout << "| " << setw(8) << left << mass_table_x[i] << "| " << setw(9) << left << mass_table_y[i]  <<"  |"<< endl;
        SetConsoleTextAttribute(h, 7);  
    }  
    cout << "------------------------" << endl;
    
    cout << "Максимальное значение функции = " << max_arr(mass_table_y, N) << endl;
    cout << "Минимальное значение функции = " << min_arr(mass_table_y, N) << endl;
    _getch();
    system("cls");
    x = a;
    cout << "y = cos(3x)/(1+x^2)" << endl;
    for (int i = 0; i < N; i++)
    {
        mass_table_x[i] = x;
        y = (double)(cos(3 * x) / (1 + x * x));
        mass_table_y[i] = y;
        x += dx;
    }
    cout << "--------------------------" << endl
        << "|    X    |      Y       |" << endl
        << "--------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        if (mass_table_y[i] == max_arr(mass_table_y, N))
        {
            cout << "| " << setw(8) << left << mass_table_x[i] << "| ";
            SetConsoleTextAttribute(h, 4);
            cout << setw(11) << left << mass_table_y[i]; SetConsoleTextAttribute(h, 7);
            cout << "  |" << endl;

        }
        else if (mass_table_y[i] == min_arr(mass_table_y, N))
        {
            cout << "| " << setw(8) << left << mass_table_x[i] << "| ";
            SetConsoleTextAttribute(h, 2);
            cout << setw(13) << left << mass_table_y[i]; SetConsoleTextAttribute(h, 7);
            cout << "|" << endl;

        }
        else
            cout << "| " << setw(8) << left << mass_table_x[i] << "| " << setw(11) << left << mass_table_y[i] << "  |" << endl;
        SetConsoleTextAttribute(h, 7);
    }
    cout << "--------------------------" << endl;
    cout << "Максимальное значение функции = " << max_arr(mass_table_y, N) << endl;
    cout << "Минимальное значение функции = " << min_arr(mass_table_y, N) << endl;
    _getch();
    system("cls");

}
void graphick()
{
    system("cls");
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(GetConsoleWindow());
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    SelectObject(hdc, pen);
    const int x0 = 450, y0 = 250, ky = 40, kx=100;

    //Оси
    MoveToEx(hdc, x0  *-kx, y0, NULL);
    LineTo(hdc, x0 * ky, y0);		// ось X
    MoveToEx(hdc, x0, 0, NULL);
    LineTo(hdc, x0, 2 * y0);



    for (int i = 0, j = 0; j < 30; i ++, j++)
	{
		//засечки на оси У
		MoveToEx(hdc, x0 - 10, y0 - ky * i, NULL);
		LineTo(hdc, x0 + 10, y0 - ky * i);
		MoveToEx(hdc, x0 - 10, y0 + ky * i, NULL);
		LineTo(hdc, x0 + 10, y0 + ky * i);

		//засечки на оси Х
		MoveToEx(hdc, x0 + kx * j/2, y0 - 10, NULL);
		LineTo(hdc, x0 + kx * j / 2, y0 + 10);
		MoveToEx(hdc, x0 - kx * j / 2, y0 - 10, NULL);
		LineTo(hdc, x0 - kx * j / 2, y0 + 10);
	}
    LPWSTR str = const_cast<LPWSTR>(TEXT("0"));
    TextOut(hdc, x0, y0, str, 1);

    str = const_cast<LPWSTR>(TEXT("y"));
    TextOut(hdc, y0*2, 5, str, 1);

    str = const_cast<LPWSTR>(TEXT("x"));
    TextOut(hdc, 2 * x0, y0 + 5, str, 1);

    TextOut(hdc, 2 * 800, 600 + 5, str, 1);
    str = const_cast<LPWSTR>(TEXT("y = cos(3x)/(1+x^2)"));
    TextOut(hdc, x0 - 158, y0 + 50, str, 16);
    str = const_cast<LPWSTR>(TEXT("y = x*ln(x)^2"));
    TextOut(hdc, x0 + 250, y0 - 200, str, 16);
    double x1 = -3.14;
    for (int i = 0; i <= WIDTH+100; i++)
    {
        double x = (double)(i - WIDTH / 2) * PI / (WIDTH / 2);
        double y1 = x*pow(log(x),2);
        double y2 = cos(3 * x) / (1 + x * x);
        int j1 = HEIGHT / 2 - y1 * HEIGHT / 2 / PI;
        int j2 = HEIGHT / 2 - y2 * HEIGHT / 2 / PI;
        SetPixel(hdc, i, j1, RGB(255, 255, 0));
        SetPixel(hdc, i, j2, RGB(0, 255, 255));
    }
    DeleteObject(pen);
    ReleaseDC(hwnd, hdc);

    _getch();
    system("cls");

}
void uravn()
{
    bool flag = true;
    system("cls");
    cout << " Решение уравнения: 2x*sin^2(x)-3*sqrt(x+cos(x))=0" << endl;
    double a, b, e = 0.001;
    cout << "Введите нижнию границу интервала" << endl;
    cin >> a;
    cout << "Введите верхнюю границу интервала" << endl;
    cin >> b;
    if (del_popol(e, a, b) != 0)

        cout << "Результат полученный методом биссекции: " << del_popol(e, a, b) << endl;
    else
    {
        cout << "Нет корней на данном отрезке" << endl;
        flag = false;
    }
    if(flag)
        cout << "Результат полученный методом хорд: " << metod_hord(e, a, b) << endl;
    
    _getch();
    system("cls");

}
void integral()
{
    bool flag = true;
    system("cls");
    cout << "Взятие определенного интерграла x^2*arctg(x) на промежутке" << endl;
    double a, b, answ = 0;
    int n;
    cout << "Введите нижнию границу интегрирования" << endl;
    cin >> a;
    cout << "Введите верхнюю границу верхнюю" << endl;
    cin >> b;
    cout << "Введите число частей (больше 50)"<<endl;
    cin >> n;
    if (n < 50)
    {
        cout << "Это число меньше 50" << endl;
        flag = false;
    }
         
    if (flag)
    {
        double h = abs(b - a) / n;
        cout << "Ответ методом прямоугольников: " << integral_primougle(n, h, a) << endl;
        cout << "Ответ методм трапеций: " << integral_trap(n, h, a, b) << endl;
    }
    
    _getch();
    system("cls");
}
void about_autor()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    cout << "\n\n";
    SetConsoleTextAttribute(h, 3);
    cout << setw(80) << right << "Расчётно-графическая работа по программированию";
    cout << "\n\n\n\n\n\n\n\n\n";
    SetConsoleTextAttribute(h, 7);
    
    cout << setw(57) << right << "ФИТиКС" << endl
        << setw(61) << right << "Группа ПИН-222" << endl
        << setw(60) << right<<"Шашков Данил"<<endl;
    _getch();
    system("cls");
}



void call_func(char s[])
{
    setcur(0, 0);
    int num_func;
    for (int i = 0; i < 7; i++)
    {
        if (s[i] == '<')
        {
            num_func = i;
            break;
        }
    }
    switch (num_func)
    {
    case(0):
    {
        intro();
        break;
    }
    case (1):
        table();
        break;
    case (2):
         graphick();
        break;
    case (3):
        uravn();
        break;
    case(4):
        integral();
        break;
    case(5):
        about_autor();
        break;
    case (6):
        system("cls");
        exit(1);
        break;


    }

}


int main()
{
    char s[] = { '<', ' ', ' ', ' ', ' ', ' ', ' ' };
    cursor_off();
    setlocale(LC_ALL, "");
    bool out_up = false;
    srand(time(NULL));



    while (true)
    {
        show_menu(s);
        switch (_getch())
        {
        case('P'):
        {
            if (s[6] == '<')
            {
                s[6] = ' ';
                s[0] = '<';
            }
            else
                menu_down(s);
            show_menu(s);
            break;
        }
        case('H'):
        {
            if (s[0] == '<')
            {
                s[0] = ' ';
                s[6] = '<';
            }
            else
                menu_up(s);
            show_menu(s);
            break;
        }
        case('\r'):
        {
            call_func(s);
        }
        }



    }
}

