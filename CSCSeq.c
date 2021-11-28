#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#define iteration 8


int main( int argc, char *argv[] )  {

    int threads;
    FILE *fp, *fp_output;
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

    switch (argv[1][6])
    {
    case '1':
        if ((fp = fopen("matrix1.txtcsc.txt", "r")) == NULL)
        {
            printf("Open Failed!");
            return -1;
        }
        fp_output = fopen("CSCvec1.txt", "w");
        break;
    case '2':
        if ((fp = fopen("matrix2.txtcsc.txt", "r")) == NULL)
        {
            printf("Open Failed!");
            return -1;
        }
        fp_output = fopen("CSCvec2.txt", "w");
        break;
    case '3':
        if ((fp = fopen("matrix3.txtcsc.txt", "r")) == NULL)
        {
            printf("Open Failed!");
            return -1;
        }
        fp_output = fopen("CSCvec3.txt", "w");
        break;
    }
    int row, col, edge_number,line;
    line = 1;
    fscanf(fp, "%d%d%d", &row, &col, &edge_number);
    // printf("row = %d, col = %d, edgenumber = %d\n",row, col, edge_number);
    int row_buffer,col_buffer;
    float val_buffer;
    int col_index[col+1];
    int row_index[edge_number+1];
    float inter_sum[edge_number+1];
    float val[edge_number+1];
    float vector[col+1];
    float partial_sum[col+1];
    for (int i = 0; i < col+1; i++)
    {
        col_index[i] = 0;
        vector[i] = 1;
        partial_sum[i] = 0;
    }
    for (int i = 0; i < edge_number+1; i++)
    {
        val[i] = 0;
        row_index[i] = 0;
        inter_sum[i] = 0;
    }
    
    while ((fscanf(fp, "%d%d%e", &row_index[line], &col_buffer, &val[line])!=EOF))
    {   
        col_index[col_buffer]++;
        line++;
    }
    // printf("col_10 ends in %d\n", row_index[150]);
    for (int i = 1; i < col+1; i++)
    {
        col_index[i]+= col_index[i-1];
    }
    // convert to CSC format
    // for (int i = 317; i < 318; i++)
    // {
    //     printf("The col %d has %d edges\n", i, col_index[i]-col_index[i-1]);
    //     // printf("The %d ends in %d\n",i, row_index[col_index[i-1]]);
    //     printf("The start edge src is %d, the val is %f\n", row_index[col_index[i-1]+1], val[col_index[i-1]+1]);
    //     printf("The end edge src is %d, the val is %f\n", row_index[col_index[i]], val[col_index[i]]);
    //     // printf("It starts from %d, and ends in %d\n", row_index[col_index[i-1]], row_index[col_index[i]-1]);

    // }
    int j;
    double start, end;
    start = omp_get_wtime();
    for (int i = 0; i < iteration; i++)
    {
        for (j = 1; j < col+1; j++)
        {
            for (int k = col_index[j-1]+1; k < col_index[j]+1; k++)
            {
                partial_sum[row_index[k]] += val[k] * vector[j];
                // if ((row_index[k] ==317) && (i == 0))
                // {
                //     printf("value to %d is %f\n", row_index[k], val[k]);
                // }
                
            }
        }
        for (int j = 1; j < col+1; j++){
            vector[j] = partial_sum[j];
            partial_sum[j] = 0;
        }      
    }
    end = omp_get_wtime();
    printf("CSCseq Execution time for %s is %f\n", argv[1], end - start);
    switch (argv[1][6])
    {
    case 1:
        // argv[1] = "matrix1.txtcsc.txt";
        argv[1] = "CSCseqvec1.txt";
        break;
    case 2:
        // argv[1] = "matrix2.txtcsc.txt";
        argv[1] = "CSCseqvec2.txt";
        break;
    case 3:
        // argv[1] = "matrix3.txtcsc.txt";
        argv[1] = "CSCseqvec3.txt";
        break;
    }

    for (int i = 1; i < col+1; i++)
    {
        fprintf(fp_output, "%d %f\n", i, vector[i]);
    }
    fclose(fp_output);
    fclose(fp);
    return(0);
}
