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
        si += (a[i]-b[i])*(a[i]-b[i]);

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

void set_seed(int seed) { srand(seed); }
float lower_limit()     { return 0.0; }
float upper_limit()     { float D = get_dimension(); return 1.0/sqrt(D); }

int eq(point p1, point p2)
{
    int i, D = get_dimension();
    for(i = 0; i < D; i++)
        if(p1[i] != p2[i]) return 0;
    return 1;
}

void print_point(point p)
{
    int j = 0, D = get_dimension();
    for(j = 0; j < D; j++) printf("%g ", p[j]);
    printf("\n");
}
