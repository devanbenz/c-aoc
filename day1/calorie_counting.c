#include <printf.h>
#include <stdlib.h>
#include <string.h>

struct File {
    FILE *file;
    char line[256];
};

struct File* create_file_struct(FILE *file) {
    struct File *file_struct = (struct File*) malloc(sizeof(struct File));
    file_struct->file = file;

    return file_struct;
}

void destroy_file_struct(struct File *file_struct) {
    free(file_struct);
}

int die(char *message) {
    printf("%s\n", message);
    return 1;
}

int main(int argc, char *argv[]) {
    int largest = 0;
    int curr_calorie_count = 0;

    if (argc < 2) {
        printf("USAGE: ./calorie_counting <FILE>");
        return 1;
    }
    FILE *calorie_file = fopen(argv[1], "r");

    if (calorie_file == NULL) {
        die("Could not open file");
    }

    struct File *file_struct = create_file_struct(calorie_file);

    while (fgets(file_struct->line, sizeof(file_struct->line), file_struct->file)) {
        if (strcmp(file_struct->line, "\n") != 0) {
            int curr_calorie = atoi(file_struct->line);
            curr_calorie_count += curr_calorie;
        }
        if (strcmp(file_struct->line, "\n") == 0) {
            printf("curr_calories: %d\n", curr_calorie_count);
            if (curr_calorie_count > largest) {
                largest = curr_calorie_count;
            }

            // reset curr calories
            curr_calorie_count = 0;
        }
    }

    printf("Largest: %d\n", largest);

    fclose(file_struct->file);
    destroy_file_struct(file_struct);

    return 0;
}