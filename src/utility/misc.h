#ifndef FUNCS
#define FUNCS


#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))
int max_int(const int array[], const int size);
double max_double(const double array[], const int size);
int sum_ints(const int array[], const int size);
double sum_doubles(const double array[], const int size);
int int_avr(const int array[], const int size);
double double_avr(const double array[], const int size);
int array_occur(const void *array, const void *target, const int size, int elem_size, int (*compare)(const void *, const void *));
//Rotate array elements left or right by one.

//Copy an array into another.

//Check if an array is sorted (ascending or descending).

//Find index of a value in an array (return -1 if not found).
int get_index(const void *array, const void *target, const int size, int elem_size, int (*compare)(const void *, const void *));


//------------ MISC HELP FUNCS -------------
int cmp_int(const void *a, const void *b);
int cmp_double(const void *a, const void *b);
int cmp_string(const void *a, const void *b);
int cmp_node(node a, node b);

#endif
