#include <stdio.h>
#include <stdlib.h>

typedef struct Line {
    int count;
    double* elem_line;
} Line;

typedef struct Matr {
    int count_lines;
    Line* lines;
} Matr;

int get_lines(int count, Line* lines, int* arr);
void matrix_output(Matr* matr, int* arr);

int main()
{
    int i = 5;
    int arr[5] = {1, 5, 2, 1, 1};

    printf("Making a lines\n");
    Line* lines = (Line*) (calloc(i, sizeof(Line)));
    get_lines(i, lines, &arr);
    printf("Making matrix...\n");
    Matr matr = {i, lines};
    matrix_output(&matr, &arr);

    return 0;
}

void matrix_output(Matr* matr, int* arr)
{
    printf("Count lines: %d\n", matr->count_lines);
    for (int j = 0; j < matr->count_lines; j++) {
        printf("Line %d ", j);
        for (int k = 0; k < arr[j]; k++) {
           printf("%lf ", ((matr->lines)[j].elem_line)[k]);
        }
        printf("\n");
    }
}

int get_lines(int count, Line* lines, int* arr)
{
    double* temp_arr = NULL;
    for (int i = 0; i < count; i++) {
        printf("Number of line: %d\n", arr[i]);
        // Write count elems in line
        lines[i].count = arr[i];
        // Get array of double
        temp_arr = (double*) (calloc(arr[i], sizeof(double)));
        for (int j = 0; j < arr[i]; j++) {
            scanf("%lf", temp_arr + j);
        }
        // Write an array in line
        lines[i].elem_line = temp_arr;
    }
}
