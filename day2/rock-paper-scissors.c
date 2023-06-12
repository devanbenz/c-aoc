#include <string.h>
#include <stdio.h>

int MAX_TABLE_SIZE = 100;

int hash(char *key) {
    int hash = 0;
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        int h = hash += key[i];
        hash *= h % 10;
        hash %= 10;
    }

    return hash;
}

int get(int hash_table[], char *key) {
    return hash_table[hash(key)];
}

int play_round(const char *player, char *opponent, char *win_table[], char *tie_table[]) {
    if (strcmp(win_table[hash(opponent)],player) == 0) {
        return 6;
    }
    if (strcmp(tie_table[hash(opponent)],player) == 0) {
        return 3;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("USAGE: ./rps <FILE>");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    char lines[256];

    int score = 0;

    int point_table[MAX_TABLE_SIZE];
    char *win_table[MAX_TABLE_SIZE];
    char *tie_table[MAX_TABLE_SIZE];

    int x = hash("X");
    int y = hash("Y");
    int z = hash("Z");
    int a = hash("A");
    int b = hash("B");
    int c = hash("C");

    point_table[x] = 1;
    point_table[y] = 2;
    point_table[z] = 3;
    win_table[a] = "Y";
    win_table[b] = "Z";
    win_table[c] = "X";
    tie_table[a] = "X";
    tie_table[b] = "Y";
    tie_table[c] = "Z";

    while(fgets(lines, sizeof(lines), input_file)) {
        char opponent[2] = { lines[0], '\0' };
        char player[2] = { lines[1], '\0' };
        score += get(point_table, player) + play_round(player, opponent, win_table, tie_table);
    }

    printf("%d\n", score);
}