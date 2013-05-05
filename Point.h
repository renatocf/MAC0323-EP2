#ifndef H_POINT_DEFINED
#define H_POINT_DEFINED

typedef float *point;
point randPoint();
float distance(point, point);

void set_seed(int);
void print_point(point);

#endif
