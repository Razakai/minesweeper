//Author Sean Adam Holland
#include <stdbool.h>
#define DIM 4
#define UNKNOWN -1
#define BOMB -2

struct locations {
    int x;
    int y;
    bool found;

};

void display(int grid[][DIM], int size);
void update_status(int row, int col, int scores[][4], int known[][4]);
void check_found(int row, int col, struct locations bombs[], int numBombs);
char get_user_char();
void update_known_info(int row, int col, int bomb_info[][DIM], int known[][DIM], struct locations bombs[], int numBombs);
void start_game(int grid[][DIM], int size, int bomb_info[][DIM], struct locations bombs[], int numBombs);
