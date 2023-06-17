#include <string.h>
#include <stdio.h>
#include <malloc.h>

int get_priority(char item) {
    if (item >= 97) {
        return item - 96;
    }

    return item - 38;
}

int get_rutsack_items(char *str) {
    int total = 0;
    size_t str_len = strlen(str);
    int items[256] = { 0 };

    for (int i = 0; i < str_len / 2; i++) {
        int j = get_priority(str[i]);
        items[j] = j;
    }
    for (int i = str_len / 2; i < str_len; i++) {
        int j = get_priority(str[i]);
        int val = items[j];
        if (val > 0) {
            total += (int) val;
            items[j] = 0;
        }
    }

    return total;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("USAGE: ./rucksack <FILE>");
        return 1;
    }
    FILE *input_file = fopen(argv[1], "r");
    char lines[256];
    int total = 0;

    while(fgets(lines, sizeof(lines), input_file)) {
        lines[strcspn(lines, "\n")] = 0;
        int compartment = get_rutsack_items(lines);
        total += compartment;
    }

    free(input_file);
    printf("Total: %d\n", total);
}