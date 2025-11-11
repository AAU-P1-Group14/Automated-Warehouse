#include <stdio.h>


enum pos {vacant, v_line, h_line, robot, shelf, drop_off, charging};

void initArray(int layout[36][19]);
void printArray(int layout[36][19]);

int main(void) {

    enum pos pos;

    static int layout[36][19];

    initArray(layout);
    printArray(layout);

    return 0;
}

void initArray(int layout[36][19])
{
    for (int y_row = 0; y_row < 19; ++y_row)
    {
        for (int x_col = 0; x_col < 36; ++x_col)
        {
            switch (y_row)
            {
            case 3: case 4: case 7: case 8: case 11: case 12:

                if ((x_col+2)%6 == 0)
                {
                    layout[x_col][y_row] = shelf;
                    layout[x_col-1][y_row] = shelf;
                    layout[x_col-2][y_row] = shelf;
                    layout[x_col-3][y_row] = shelf;
                }
                break;

            case 0: case 18:
                layout[x_col][y_row] = h_line;
            }
            switch (x_col)
            {
                case 0: case 35:
                layout[x_col][y_row] = v_line;
            }
        }
    }
    layout[4][16] = drop_off;
    layout[31][16] = charging;
}

void printArray(int layout[36][19])
{
    for (int y_row = 0; y_row < 19; ++y_row)
    {
        for (int x_col = 0; x_col < 36; ++x_col)
        {
            switch (layout[x_col][y_row])
            {
            case vacant:
                printf(" ");
                break;

            case v_line:
                printf("|");
                break;

            case h_line:
                printf("-");
                break;

            case robot:
                printf("O");
                break;

            case shelf:
                printf("X");
                break;

            case drop_off:
                printf("D");
                break;

            case charging:
                printf("C");
                break;

            }


        }
        printf("\n");
    }
}