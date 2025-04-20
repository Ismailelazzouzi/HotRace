#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define BUFFER_SIZE 1000003

typedef struct s_filed
{
    char    *keyword;
    char    *value;
    int     init;
    struct s_filed *next;
} t_filed;

typedef struct s_table
{
    t_filed *fileds[BUFFER_SIZE];
    int     size;
} t_table;