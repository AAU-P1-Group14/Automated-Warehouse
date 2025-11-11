#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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
            case vacant: printf(" "); break;

            case v_line: printf(ANSI_COLOR_BLUE "|" ANSI_COLOR_RESET); break;

            case h_line: printf(ANSI_COLOR_BLUE "-" ANSI_COLOR_RESET); break;

            case robot: printf(ANSI_COLOR_CYAN "O" ANSI_COLOR_RESET); break;

            case shelf: printf(ANSI_COLOR_YELLOW "X" ANSI_COLOR_RESET); break;

            case drop_off: printf(ANSI_COLOR_GREEN "D" ANSI_COLOR_RESET); break;

            case charging: printf(ANSI_COLOR_GREEN "C" ANSI_COLOR_RESET); break;
            }


        }
        printf("\n");
    }
}