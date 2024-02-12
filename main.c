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

typedef struct Board_point {
    int count;
    int index;
} Board_point;

int creat_matr(Matr* matr);
int get_arr(int count, int* arr);
int get_num(const char* str, void* temp);
int get_lines(int count, Line* lines, int* arr);

void matrix_output(Matr* matr);
void freedom_matr(Matr* matr);
int process (Matr* matr);

int main()
{
    // Initialization
    int check = 0;
    Matr matr = {0, NULL};

    // Creating a matrix
    check = creat_matr(&matr);
    if (check == -1)
        return -1;
    matrix_output(&matr);

    // Processing
    check = process(&matr);
    if (check == -1)
        return -1;
    matrix_output(&matr);

    // Free a memory
    freedom_matr(&matr);

    return 0;
}

int process(Matr* matr)
{
    // Init
    Board_point mn = {-1, matr->count_lines - 1};
    Board_point mx = {-1, 0};
    int count_neg = -1;
    int count_pos = -1;
    int elem = 0;
    Line temp = {-1, NULL};

    // Finding strings
    for (int i = 0; i < (*matr).count_lines; i++) {
        for (int j = 0; j < (*matr).lines[i].count; j++) {
            elem = (*matr).lines[i].elem_line[j];
            if (elem < 0)
                count_neg += 1;
            if (elem > 0)
                count_pos += 1;
        }
        if (count_neg > mn.count)
            mn.index = i;
        if (count_pos > mx.count)
            mx.index = i;
    }

    // Changing strings
    temp = (*matr).lines[mn.index];
    (*matr).lines[mn.index] = (*matr).lines[0];
    (*matr).lines[0] = temp;

    temp = (*matr).lines[mx.index];
    (*matr).lines[mx.index] = (*matr).lines[(*matr).count_lines - 1];
    (*matr).lines[(*matr).count_lines - 1] = temp;
    return 0;
}

void freedom_matr(Matr* matr)
{
    for (int i = 0; i < (*matr).count_lines; i++) {
        free(((*matr).lines)[i].elem_line);
        //free((*matr).lines + i);
    }
    free(matr->lines);
    //free(matr);
}

int creat_matr(Matr* matr)
{
    // Init
    int i = 0;
    int check = 0;
    int* nj = NULL;

    // Count of strings
    do {
        printf("Count lines: ");
        check = get_num("%d", &i);
        if (check == -1)
            return -1;
    } while (i < 0);

    // Array of columns
    nj = (int*) (calloc(i, sizeof(int)));
    check = get_arr(i, nj);
    if (check == -1)
        return -1;

    // Making a lines
    Line* lines = (Line*) (calloc(i, sizeof(Line)));
    check = get_lines(i, lines, nj);
    if (check == -1)
        return -1;

    // Making matrix
    matr->count_lines = i;
    matr->lines = lines;

    free(nj);
    return 0;
}

int get_arr(int count, int* arr)
{
    int check = 0;

    // Init an array
    for (int i = 0; i < count; i++) {
        printf("Item in line %d: ", i);
        check = get_num("%d", arr + i);
        if (check == -1)
            return -1;
    }
    return 0;
}

int get_lines(int count, Line* lines, int* arr)
{
    int check = 0;
    double* temp_arr = NULL;

    for (int i = 0; i < count; i++) {
        printf("Number of item: %d\n", arr[i]);
        // Write count elems in line
        lines[i].count = arr[i];
        // Get array of double
        temp_arr = (double*) (calloc(arr[i], sizeof(double)));
        for (int j = 0; j < arr[i]; j++) {
            printf("a[%d][%d] = ", i, j);
            check = get_num("%lf", temp_arr + j);
            if (check == -1)
                return -1;
        }
        // Write an array in line
        lines[i].elem_line = temp_arr;
    }
    return 0;
}

int get_num(const char* str, void* temp)
{
    int check = 0;
    do {
        check = scanf(str, temp);
        if (check == 0) {
            scanf("%*[^\n]c");
            printf("Input integer: ");
        }
        if (check == -1) {
            printf("Overflow!\n");
            return -1;
        }
    } while(check != 1);
    return 0;
}

void matrix_output(Matr* matr)
{
    printf("Count lines: %d\n", matr->count_lines);
    for (int j = 0; j < matr->count_lines; j++) {
        printf("Line %d: ", j);
        for (int k = 0; k < matr->lines[j].count; k++) {
           printf("%lf ", ((matr->lines)[j].elem_line)[k]);
        }
        printf("\n");
    }
}
