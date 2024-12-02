#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Matrix
{
    int row;    // Number of rows
	int column;	// Number of columns
	int* data;	// Address of matrix data
}
Matrix;

Matrix matrix_new(int rows, int columns)
{
    int *data = (int*)malloc(rows*columns*sizeof(int));
    assert(data);
    return (Matrix){rows, columns, data};
}

Matrix matrix_from_file(FILE* fp)
{
    int rows, columns;
    fscanf(fp,"%d",&rows);
    fscanf(fp,"%d",&columns);
    Matrix matrix = matrix_new(rows, columns);
    for (int i = 0; i < rows*columns; i++)
        fscanf(fp, "%d", &matrix.data[i]);
    return matrix;
}

void matrix_free(Matrix* matrix)
{
    free(matrix->data);
}

extern int matrix_mul(Matrix *results, const Matrix *source1, const Matrix *source2);

void matrix_print(const Matrix* matrix)
{
	for (int i = 0; i < matrix->row; i++)
	{
		for (int j = 0; j < matrix->column; j++)
			printf("%d ", *(matrix->data + i * matrix->column + j));
		printf("\n");
	}
}

int main(int argc,char* argv[])
{
    Matrix source_matrix1 = matrix_from_file(stdin);
    Matrix source_matrix2 = matrix_from_file(stdin);

    Matrix results_matrix = matrix_new(source_matrix1.row, source_matrix2.column);
    
    // memset(results_matrix.data, 0, sizeof(int) * results_matrix.row * results_matrix.column); // unnecessary

    if (matrix_mul(&results_matrix, &source_matrix1, &source_matrix2) == 0)
        matrix_print(&results_matrix);
    else
        fprintf(stderr, "Fail to multiply two matrices.\n");
    matrix_free(&source_matrix1);
    matrix_free(&source_matrix2);
    matrix_free(&results_matrix);
    return 0;
}
