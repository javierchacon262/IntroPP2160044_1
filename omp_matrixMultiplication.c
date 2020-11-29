/*
    Archivo modificado de matrixMultiplication.c para paralelizarlo
    Se utilizará openMP para esta labor
*/

#include<stdio.h>
#include<omp.h>

int main()
{
    printf("\n\n\t\tStudytonight - Best place to learn\n\n\n");

// Se eliminan variables que tienen interaccion con el usuario, se ingresan directamente    
    int n, m, c, d, p, q, k, first[10][10], second[10][10], pro[10][10],sum = 0;
        
    m = 3;
    n = 3;
    p = 3;
    q = 3;

    #pragma omp parallel shared (first, second, m, n) private(c, d)
    {
        #pragma omp for
        for(c=0; c<m; c++){
            for(d=0;d<n;d++){
                first[c][d] = (c+d)/2;
            }
        }
        #pragma omp for
        for(c=0; c<p; c++){
            for(d=0;d<q;d++){
                second[c][d] = (d-c)/2;
            }
        }
    }

    if(n != p)
        printf("Matrices with the given order cannot be multiplied with each other.\n\n");

    else    // matrices can be multiplied
    {
        printf("\n\nThe first matrix is: \n\n");
        for(c = 0; c < m; c++)   // to iterate the rows
        {
            for(d = 0; d < n; d++)   // to iterate the columns
            {
                printf("%d\t", first[c][d]);
            }
            printf("\n");
        }

        // printing the second matrix
        printf("\n\nThe second matrix is: \n\n");
        for(c = 0; c < p; c++)   // to iterate the rows
        {
            for(d = 0; d < q; d++)   // to iterate the columns
            {
                printf("%d\t", second[c][d]);
            }
            printf("\n");
        }

        #pragma omp parallel shared (first, second, pro) private(c, d, k, sum)
        {
            # pragma omp for
            for(c = 0; c < m; c++)   // to iterate the rows
            {
                for(d = 0; d < q; d++)   // to iterate the columns
                {
                    for(k = 0; k < p; k++)
                    {
                        sum = sum + first[c][k]*second[k][d];
                    }
                pro[c][d] = sum;    // resultant element of pro after multiplication
                sum = 0;    // to find the next element from scratch
                }
            }
        }

        // printing the elements of the product matrix
        printf("\n\nThe multiplication of the two entered matrices is: \n\n");
        for(c = 0; c < m; c++)   // to iterate the rows
        {
            for(d = 0; d < q; d++)   // to iterate the columns
            {
                printf("%d\t", pro[c][d]);
            }
            printf("\n"); // to take the control to the next row
        }
    }
    printf("\n\n\t\t\tCoding is Fun !\n\n\n");
    return 0;
}