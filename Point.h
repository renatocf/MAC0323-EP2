#ifndef H_POINT_DEFINED
#define H_POINT_DEFINED

typedef float *point;

point randPoint   (void);
float distance    (point, point);
                  
void  set_seed    (int);
float lower_limit (void);
float upper_limit (void);

int   eq          (point, point);
void  print_point (point);

#endif
