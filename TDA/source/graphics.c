#include "source.h"

int drawEightPoints(int r, int* x, int* y, int it, int cr)
{
    HWND hwnd;
    char Title[1024];
    GetConsoleTitle(Title, 1024);
    hwnd = FindWindow(NULL, Title);

    RECT rc;
    GetClientRect(hwnd, &rc);
    int iWidth = rc.right;
    int iHeight = rc.bottom;

    int cx = iWidth / 2;
    int cy = iHeight / 2;

    int c1 = cr + (r - cr) / 2;
    int c2 = cr - (r - cr) / 2;

    int curX = 0;
    int curX1 = cx + cr + (r - cr) / 2;
    int curX2 = cx - cr - (r - cr) / 2;

    int curX3 = cx + cr - (r - cr) / 2;
    int curX4 = cx - cr + (r - cr) / 2;

    int curY = 0;
    int pr = 10;
    int delta = pr;
    int  pointsCount = 0;
    double fi = 0, p = 0;

    int betti2 = 2;

    int* pointsX = (int*)calloc(N, sizeof(int));
    int* pointsY = (int*)calloc(N, sizeof(int));

    HDC hdc = GetDC(hwnd);
    HPEN p1, p2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    p1 = (HPEN)SelectObject(hdc, p2);
    
    Arc(hdc, curX1 - c1, cy - c1, curX1 + c1, cy + c1, curX1 - c1, cy, curX1 + c1, cy);
    Arc(hdc, curX1 - c1, cy - c1, curX1 + c1, cy + c1, curX1 + c1, cy, curX1 - c1, cy);

    Arc(hdc, curX2 - c1, cy - c1, curX2 + c1, cy + c1, curX2 - c1, cy, curX2 + c1, cy);
    Arc(hdc, curX2 - c1, cy - c1, curX2 + c1, cy + c1, curX2 + c1, cy, curX2 - c1, cy);

    Arc(hdc, curX3 - c2, cy - c2, curX3 + c2, cy + c2, curX3 - c2, cy, curX3 + c2, cy);
    Arc(hdc, curX3 - c2, cy - c2, curX3 + c2, cy + c2, curX3 + c2, cy, curX3 - c2, cy);

    Arc(hdc, curX4 - c2, cy - c2, curX4 + c2, cy + c2, curX4 - c2, cy, curX4 + c2, cy);
    Arc(hdc, curX4 - c2, cy - c2, curX4 + c2, cy + c2, curX4 + c2, cy, curX4 - c2, cy);

    HPEN p3, p4 = CreatePen(PS_INSIDEFRAME, 1, RGB(65, 102, 245));
    p3 = (HPEN)SelectObject(hdc, p4);

    for (int i = 0; i < N; i++)
    {

        int curX = x[i] % iWidth;
        int curY = y[i] % iHeight;
        int distance1 = (int)sqrt((int)pow(curX1 - curX, 2) + (int)pow(cy - curY, 2));
        int distance2 = (int)sqrt((int)pow(curX2 - curX, 2) + (int)pow(cy - curY, 2));
        int distance3 = (int)sqrt((int)pow(curX3 - curX, 2) + (int)pow(cy - curY, 2));
        int distance4 = (int)sqrt((int)pow(curX4 - curX, 2) + (int)pow(cy - curY, 2));

        if ((distance3 > (c2 + delta) && distance1 < (c1 - delta)) || (distance4 > (c2 + delta) && distance2 < (c1 - delta)))
        {
            //printf("%d\n", distance);            
            Ellipse(hdc, curX, curY, curX + pr, curY + pr);
            //SetPixel(hdc, curX , curY, RGB(65, 102, 245));
            if (it > 0)
            {
                pointsX[pointsCount] = curX;
                pointsY[pointsCount] = curY;
                pointsCount++;

            }
        }

    }

    HPEN p5, p6 = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
    p5 = (HPEN)SelectObject(hdc, p6);
    

    for (int i = 0; i < pointsCount; i++)
    {
        //printf("\n%d", pointsX[i]);

        for (int j = 0; j < pointsCount; j++)
        {
            double distanceEuc = sqrt(pow(pointsX[j] - pointsX[i], 2) + pow(pointsY[j] - pointsY[i], 2));
            //printf("\n%g", distanceEuc);
            if (distanceEuc < E + STEP * it && distanceEuc != 0)
            {
                p5 = (HPEN)SelectObject(hdc, p6);
                MoveToEx(hdc, (int)(pointsX[i] + pr / 2), (int)(pointsY[i] + pr / 2), NULL);
                LineTo(hdc, (int)(pointsX[j] + pr / 2), (int)(pointsY[j] + pr / 2));
                betti2++;
            }
           
        }
    }

    //for (int i = curX2; i < curX1; i++)
    //{
        //curY = sqrt(sqrt(pow(c1, 4) + 4 * pow(i, 2) * pow(c1, 2)) - pow(i, 2) - pow(c1, 2));
        //curY = (int)sqrt(abs(sqrt(pow(c1, 4) + 4 * pow(i, 2) * pow(c1, 2)) - pow(i, 2) - pow(c1, 2))) % iHeight;
        //printf("X = %d\n", i);
        //printf("Y = %d\n\n", curY);
        //SetPixel(hdc, i, curY, RGB(255, 0, 0));
        //SetPixel(hdc, i, -curY, RGB(255, 0, 0));
    //}
    //do
    //{
    //    p = sqrt(tan(PI / 4 - fi));
    //    curX = (int)(c1 * sqrt(2) * ((p + pow(p, 3)) / (1 + pow(p, 4)))) % iWidth  + cx;
    //    curY = (int)(c1 * sqrt(2) * ((p - pow(p, 3)) / (1 + pow(p, 4)))) % iHeight + cy;
    //    //printf("X = %d\n", curX);
    //    //printf("Y = %d\n", curY);
    //    SetPixel(hdc, cx + curX, cy + curY, RGB(255, 0, 0)); 
    //    //Ellipse(hdc, curX,  curY, curX + pr, curY + pr);
    //    fi += 0.1;
    //} while (fi < PI);


    SelectObject(hdc, p1);
    SelectObject(hdc, p3);
    SelectObject(hdc, p5);
    ReleaseDC(hwnd, hdc);
    DeleteObject(p2);
    DeleteObject(p4);
    DeleteObject(p6);
    _getch();
    system("pause");
    return betti2;
}

int drawCirclePoints(int r, int* x, int* y, int it, int cr)
{      
    HWND hwnd;
    char Title[1024];
    GetConsoleTitle(Title, 1024);
    hwnd = FindWindow(NULL, Title); 

    RECT rc;
    GetClientRect(hwnd, &rc);
    int iWidth = rc.right;
    int iHeight = rc.bottom;

    int cx = iWidth / 2;
    int cy = iHeight / 2;
    //int cr = 150;
    int pr = 10;
    int delta = pr;
    int  pointsCount = 0;

    int betti2 = 1;

    int* pointsX = (int*)calloc(N, sizeof(int));
    int* pointsY = (int*)calloc(N, sizeof(int));

    if (r < cr)
    {
        printf("Radius must be more than %d\n", cr);
        exit(1);
    }

    HDC hdc = GetDC(hwnd);    
    HPEN p1, p2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    p1 = (HPEN)SelectObject(hdc, p2); 
    
    Arc(hdc, cx - r, cy - r, cx + r, cy + r, cx - r, cy, cx + r, cy);
    Arc(hdc, cx - r, cy - r, cx + r, cy + r, cx + r, cy, cx - r, cy);

    Arc(hdc, cx - cr, cy - cr, cx + cr, cy + cr, cx - cr, cy, cx + cr, cy);
    Arc(hdc, cx - cr, cy - cr, cx + cr, cy + cr, cx + cr, cy, cx - cr, cy);

    //HBRUSH p3, p4 = CreateSolidBrush(RGB(65, 102, 245));
    //p3 = (HBRUSH)SelectObject(hdc, p4);

    HPEN p3, p4 = CreatePen(PS_INSIDEFRAME, 1, RGB(65, 102, 245));
    p3 = (HPEN)SelectObject(hdc, p4);

    for (int i = 0; i < N; i++)
    {
              
        int curX = x[i] % iWidth;
        int curY = y[i] % iHeight;
        int distance = (int)sqrt((int)pow(cx - curX, 2) + (int)pow(cy - curY, 2));

        if (distance > (cr + delta) && distance < (r - delta))
        {   
            //printf("%d\n", distance);            
            Ellipse(hdc, curX, curY, curX + pr, curY + pr);
            //SetPixel(hdc, curX , curY, RGB(65, 102, 245));
            if (it > 0)
            {
                pointsX[pointsCount] = curX;
                pointsY[pointsCount] = curY;
                pointsCount++;
                
            }
        }   
        
    }

    HPEN p5, p6 = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
    p5 = (HPEN)SelectObject(hdc, p6);
    /*HPEN p7, p8 = CreatePen(PS_INSIDEFRAME, 1, RGB(0, 0, 0));
    p7 = (HPEN)SelectObject(hdc, p8);*/

    for (int i = 0; i < pointsCount; i++)
    {
        //printf("\n%d", pointsX[i]);
        
        for (int j = 0; j < pointsCount; j++)
        {
            double distanceEuc = sqrt(pow(pointsX[j] - pointsX[i], 2) + pow(pointsY[j] - pointsY[i], 2));
            //printf("\n%g", distanceEuc);
            if (distanceEuc < E + STEP * it && distanceEuc != 0)
            {
                p5 = (HPEN)SelectObject(hdc, p6);
                MoveToEx(hdc, (int)(pointsX[i] + pr /2), (int)(pointsY[i] + pr / 2), NULL);
                LineTo(hdc, (int)(pointsX[j] + pr / 2), (int)(pointsY[j] + pr / 2));
                betti2++;
            }
            /*else
            {
                p7 = (HPEN)SelectObject(hdc, p8);
                Ellipse(hdc, pointsX[j], pointsY[j], pointsX[j] + pr, pointsY[j] + pr);
            }*/
        }
    }

    SelectObject(hdc, p1);  
    SelectObject(hdc, p3);
    SelectObject(hdc, p5);
   /* SelectObject(hdc, p7);*/
    ReleaseDC(hwnd, hdc);    
    DeleteObject(p2); 
    DeleteObject(p4);
    DeleteObject(p6);
    /*DeleteObject(p8);*/
    free(pointsX);
    free(pointsY);
    _getch();
    system("pause");
    return betti2;
}

void drawPoint(int* x, int* y,int size)
{
    HWND hwnd;
    char Title[1024];
    GetConsoleTitle(Title, 1024);
    hwnd = FindWindow(NULL, Title);

    RECT rc;
    GetClientRect(hwnd, &rc);
    int iWidth = rc.right;
    int iHeight = rc.bottom;

    HDC hdc = GetDC(hwnd);
    HPEN p1, p2 = CreatePen(PS_SOLID, 2, RGB(65, 102, 245));
    p1 = (HPEN)SelectObject(hdc, p2);

    if (size == 0)
    {
        for (int i = 0; i < N; i++)
        {
            SetPixel(hdc, x[i] % iWidth, y[i] % iHeight, RGB(65, 102, 245));
        }
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            Ellipse(hdc, x[i] % iWidth, y[i] % iHeight, (x[i] % iWidth) + size, (y[i] % iHeight) + size);
        }
    }

    SelectObject(hdc, p1);
    ReleaseDC(hwnd, hdc);
    DeleteObject(p2);
    _getch();
    system("pause");
}

void example()
{
    HWND hwnd;
    char Title[1024];
    GetConsoleTitle(Title, 1024); // Узнаем имя окна
    hwnd = FindWindow(NULL, Title); // Узнаем hwnd окна

    RECT rc;
    GetClientRect(hwnd, &rc);
    int iWidth = rc.right;
    int iHeight = rc.bottom;

    HDC hdc = GetDC(hwnd);    // Получаем контекст для рисования
    HPEN p1, p2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // Создаем красное перо
    p1 = (HPEN)SelectObject(hdc, p2);  // Заносим красное перо в контекст рисования

    int x = 0, y = 0, R = iWidth / 2;
    double fi = 0;
    do
    {
        x = R * cos(fi);
        y = R * sin(fi);
        MoveToEx(hdc, iWidth / 2, iHeight / 2, NULL);
        LineTo(hdc, x + iWidth / 2, iHeight / 2 - y);
        fi += 0.1;
    } while (fi < 6.28);

    SelectObject(hdc, p1);   // Возвращаем старое перо
    ReleaseDC(hwnd, hdc);    // Освобождаем контекст рисования
    DeleteObject(p2);       // Удаляем созданное перо
    _getch();
    system("pause");
}