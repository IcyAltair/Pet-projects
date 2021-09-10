#include "source.h"

int main(int argc, char* argv[])
{
    fullScreen();
    int* arrX;
    int* arrY;    

    const int arrR[5] = {200, 225, 250, 275, 300};
    int r = 0, it = 0, cr = 150, fig = 0;
    int betti1 = 1, betti2 = 0, betti3 = 0;

    srand((unsigned int)time(NULL));   

    if ((arrX = rayGenInt(N,0,N)) != NULL && (arrY = rayGenInt(N, 0, N)) != NULL)
    {
#if DEBUG
        printf("Array of X points:\n");
        for (int i = 0; i < N; i++)
        {
            printf("%d\n", arrX[i]);
        }
        printf("\n");
        printf("Array of Y points:\n");        
        for (int i = 0; i < N; i++)
        {
            printf("%d\n", arrY[i]);
        }

#endif // DEBUG             
        printf("Avalaible radiuses:\n");
        for (int i = 0; i <(int)(sizeof(arrR) / sizeof(arrR[0])); i++)
        {
            printf("%d ", arrR[i]);
        }
        printf("\nEnter radius (0 - show all points, -1 - show an example, -8 - show a 'lemniscate' example):\n");
        scanf_s("%d", &r);
        switch (r) 
        {
        case 200:
            printf("Enter iteration from 1 to 10 (0 - show simple figure):\n");
            scanf_s("%d", &it);
            switch (it)
            {
            case 0:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);                
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 1:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 2:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 3:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 4:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\n\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 5:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 6:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 7:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 8:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 9:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 10:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            default:
                system("cls");
                printf("Wrong choice. Restart program\n");
                break;
            }
            
        case 225:
            printf("Enter iteration from 1 to 10 (0 - show simple figure):\n");
            scanf_s("%d", &it);
            switch (it)
            {
            case 0:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 1:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 2:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 3:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 4:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 5:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 6:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 7:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 8:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 9:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 10:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            default:
                system("cls");
                printf("Wrong choice. Restart program\n");
                break;
            }
        case 250:
            printf("Enter iteration from 1 to 10 (0 - show simple figure):\n");
            scanf_s("%d", &it);
            switch (it)
            {
            case 0:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 1:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 2:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 3:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 4:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 5:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 6:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 7:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 8:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 9:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 10:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            default:
                system("cls");
                printf("Wrong choice. Restart program\n");
                break;
            }
        case 275:
            printf("Enter iteration from 1 to 10 (0 - show simple figure):\n");
            scanf_s("%d", &it);
            switch (it)
            {
            case 0:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 1:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 2:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 3:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 4:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 5:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 6:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 7:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 8:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 9:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 10:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            default:
                system("cls");
                printf("Wrong choice. Restart program\n");
                break;
            }
        case 300:
            printf("Enter iteration from 1 to 10 (0 - show simple ring):\n");
            scanf_s("%d", &it);
            switch (it)
            {
            case 0:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 1:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 2:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 3:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 4:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 5:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 6:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 7:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 8:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 9:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            case 10:
                printf("\nChoose figure (1 - ring, 2 - eight):\n");
                scanf_s("%d", &fig);
                system("cls");
                printf("\t\t\t\tR = %d, iteration = %d, eps = %d, step = %d", r, it, E, STEP);
                if (fig == 1)
                    betti2 = drawCirclePoints(r, arrX, arrY, it, cr);
                else
                    betti2 = drawEightPoints(r, arrX, arrY, it, cr);
                printf("\n\t\t\t\tBetti numbers: b1 = %d, b2 = %d, b3 = %d", betti1, betti2, betti3);
            default:
                system("cls");
                printf("Wrong choice. Restart program\n");
                break;
            }
        case 0:
            system("cls");
            drawPoint(arrX, arrY, 10);
        case -1:
            system("cls");
            example();
        case -8:
            system("cls");
            drawEightPoints(200, arrX, arrY, it, cr);
        default:
            printf("Wrong choice. Restart program\n");
            break;
        }        
        
        free(arrX);
        free(arrY);
    }

    return 0;
    
}
