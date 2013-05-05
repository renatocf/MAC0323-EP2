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
    int i, generated = 0;
    point new = malloc(D * sizeof(float));
    float sig, R2 = 0; 
    
    while(!generated) 
    {
        R2 = 0;
        for(i = 0; i < D; i++)
        {
            sig = 1.0 * rand()/RAND_MAX;
            (sig > 0.5) ? (sig = 1.0) : (sig = -1.0);
            
            new[i] = sig * rand()/RAND_MAX;
            R2 += (new[i] *= new[i]);
        }
        (R2 >= 1) ? (continue) : (generated = 1);
        
        
    }
    
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
