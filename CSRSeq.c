#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#define iteration 8

int main( int argc, char *argv[] )  {
    FILE *fp, *fp_output;
    int threads;
    //clock_t start, end;
    if( argc == 3 ) {
        
        threads = atoi(argv[2]);
    }
    else if( argc > 3 ) {
        printf("Too many arguments supplied.\n");
    }
    else {
        printf("Two argument expected.\n");
    }
    int row, col, edge_number,line;
    line = 0;
    
    const char *output = "output";
    // const char *fileoutName = "matrix1_out.txt";
    
    switch (argv[1][6])
    {
    case '1':
        if ((fp = fopen("matrix1.txt", "r")) == NULL)
        {
            printf("Open Failed!");
            return -1;
        }
        fp_output = fopen("CSRseqvec1.txt", "w");
        break;
    case '2':
        if ((fp = fopen("matrix2.txt", "r")) == NULL)
        {
            printf("Open Failed!");
            return -1;
        }
        fp_output = fopen("CSRseqvec2.txt", "w");
        break;
    case '3':
        if ((fp = fopen("matrix3.txt", "r")) == NULL)
        {
            printf("Open Failed!");
            return -1;
        }
        fp_output = fopen("CSRseqvec3.txt", "w");
        break;
    }
    fscanf(fp, "%d%d%d", &row, &col, &edge_number);
    float val[edge_number];
    int row_index[row+1];
    int col_index[edge_number];
    int row_buffer, spmv_cal_flag;
    float vector[row+1], new_vector[row];
    float partial_sum[row+1];
    for (int i = 0; i < row+1; i++)
    {
        row_index[i] = 0;
        partial_sum[i] = 0;
    }
    
    for (int i = 0; i < row+1; i++)
    {
        vector[i] = 1; // give a random value
    }
    for (int i = 0; i < edge_number; i++)
    {
        col_index[i] = 0;
        val[i] = 0;
    }
    while ((fscanf(fp, "%d%d%e", &row_buffer, &col_index[line], &val[line])!=EOF))
    {   
        row_index[row_buffer]++;

        line++;
    }
    for (int i = 1; i < row+1; i++)
    {
        row_index[i] += row_index[i-1];
    }

    // convert to CSR format
    // for (int i = 5; i < 6; i++)
    // {
    //     printf("The row %d's index is %d, the start edge dest is %d, the end edge dest is %d\n",(i),row_index[i], col_index[row_index[i-1]], col_index[row_index[i]-1]);
    //     printf("The start edge's val is %f, The end edge's value is %f\n", val[row_index[i-1]], val[row_index[i]-1]);
    //     printf("The start edge corresponding vertex's val is %f, the end val is %f\n", vector[col_index[row_index[i-1]]], vector[col_index[row_index[i]-1]]);
    // }
    double start, end;
    start = omp_get_wtime();
    for (int i = 0; i < iteration; i++) // check
    {
        // printf("This is iteration %d, the initial value of vector[%d] is %f\n", i, 8 ,vector[8]);
        for (int j = 1; j < row+1; j++)
        {
            for (int k = row_index[j-1]; k < row_index[j]; k++)
            {
                partial_sum[j] += val[k] * vector[col_index[k]];
                
            }
            
        }
        for (int j = 1; j < row+1; j++)
        {
            vector[j] = partial_sum[j];
            partial_sum[j] = 0;
        }
        // printf("This is iteration %d, the value of vector[%d] is %f\n", i, 8 ,vector[8]);
    }
    end = omp_get_wtime();
    printf("CSRseq Execution time for %s is %f\n", argv[1], end - start);

    for (int i = 1; i < row+1; i++)
    {
        fprintf(fp_output, "%d %f\n", i, vector[i]);
    }
    fclose(fp_output);
    fclose(fp);
    //printf("Time for serial CSR is %f\n",(end-start));
    return(0);
}