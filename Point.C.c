#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "Point.h"
#include "Dimension.h"

float distance(point a, point b)
{
    int i; float si = 0;
    int D = get_dimension();
    
    for(i = 0; i < D; i++)
        si += a[i] - b[i];

    return sqrt(si);
}

point randPoint()
{
    int D = get_dimension();
    int i; float K = 1.0/sqrt(D);
    point new = malloc(D * sizeof(float));
    
    for(i = 0; i < D; i++)
        new[i] = K * rand()/RAND_MAX;
    
    return new;
}

void set_seed(int seed)
{
    srand(seed);
}

void print_point(point p)
{
    int j = 0, D = get_dimension();
    for(j = 0; j < D; j++) printf("%g ", p[j]);
    printf("\n");
}
