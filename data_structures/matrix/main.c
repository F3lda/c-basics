// matrix by 1d array (2d array by 1d array)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct matrix {
	unsigned rows;
	unsigned cols;
	float *data;
} matrix_t;


matrix_t matrix_create(unsigned rows, unsigned cols)
{
	matrix_t matrix = {0, 0, NULL};

	matrix.data = malloc(sizeof(float)*rows*cols);
	if (matrix.data != NULL) {
		matrix.rows = rows;
		matrix.cols = cols;
	}

	return matrix;
}

void matrix_destroy(matrix_t *matrix)
{
	if (matrix->data != NULL) {
		free(matrix->data);
	}
	matrix->data = NULL;
	matrix->rows = 0;
	matrix->cols = 0;
}

float matrix_get_item(matrix_t *matrix, unsigned row, unsigned col)
{
	if (row < matrix->rows && col < matrix->cols) {
		return matrix->data[row*matrix->cols + col];
	}
	return NAN;
}

void matrix_set_item(matrix_t *matrix, unsigned row, unsigned col, float value)
{
	if (row < matrix->rows && col < matrix->cols) {
		matrix->data[row*matrix->cols + col] = value;
	}
}


int main(int argc, char * argv[])
{
    int row_num = 5;
    int col_num = 5;

    printf("ROWs: %i COLs:%i\n", row_num, col_num);

	matrix_t matrix = matrix_create(row_num, col_num);

	float value = 0;
	for (int it = 0; it < row_num; it++) {
		for (int jt = 0; jt < col_num; jt++) {
			matrix_set_item(&matrix, it, jt, value);
			value++;  		
		}
	}

    for (int it = 0; it < row_num; it++) {
		for (int jt = 0; jt < col_num; jt++) {
	        printf(" %f", matrix_get_item(&matrix, it, jt));
        }
        printf("\n");
    }

    matrix_destroy(&matrix);

    return 0;
}
