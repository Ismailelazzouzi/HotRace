#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct s_filed
{
    char    *keyword;
    char    *value;
    struct s_filed *next;
} t_filed;

typedef struct s_table
{
    t_filed **fileds;
    size_t  size;
} t_table;