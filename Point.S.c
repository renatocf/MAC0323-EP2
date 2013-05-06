#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "Point.h"
#include "Dimension.h"

static float generate_gaussian();
static float spare;
static int spareUsed = 1;

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
    point new, origin;
    int i, D = get_dimension(); float N;
    
    new    = malloc(D * sizeof(*new));
    origin = malloc(D * sizeof(*origin));
    
    for(i = 0; i < D; i++)
        { new[i] = generate_gaussian(); origin[i] = 0; }
    /* printf("Point: "); print_point(new); */
    
    N = distance(new, origin);
    /* printf("N: %g\n", N); */
    for(i = 0; i < D; i++)
        { new[i] = new[i]/N * upper_limit(); }
    
    return new;
}

static float generate_gaussian()
{
    float u, v, np, S; float K;
    
    if(!spareUsed)
        { spareUsed = 1; return spare; }
    
    do {
        u = (1.0 * rand()/RAND_MAX); u = u*2-1;
        v = (1.0 * rand()/RAND_MAX); v = v*2-1;
        S = u*u + v*v;
        /* printf("S: %g, u: %g, v: %g\n", S, u, v); */
        
    } while(S >= 1 || S == 0);
    
    K = sqrt(-2 * log(S)/S);
    np = u*K; spare = v*K;
    /* printf("np: %g, spare: %g\n", np, spare); */
    
    spareUsed = 0; return np;
}

void set_seed(int seed) { srand(seed); }
float lower_limit()     { return -0.5; }
float upper_limit()     { return 0.5;  }

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
