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
    float sig, R2 = 0, R, K, Rad2 = sqrt(2); 
    
    while(!generated) 
    {
        R2 = 0;
        for(i = 0; i < D; i++)
        {
            sig = 1.0 * rand()/RAND_MAX;
            (sig > 0.5) ? (sig = 1.0) : (sig = -1.0);
            
            new[i] = 2*(1.0*rand()/RAND_MAX) - 1;
            R2 += (new[i] * new[i]);
        }
        if(R2 >= 1) continue; else generated = 1;
        
        K = sqrt(-2*log(R2)/R2); R = sqrt(R2);
        for(i = 0; i < D; i++) new[i] = (new[i]*K)/(Rad2*R);
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
