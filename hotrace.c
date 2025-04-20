#include "hotrace.h"

void ft_putstr_fd(int fd, char *str)
{
    while (str && *str)
        write(fd, str++, 1);
}

size_t  ft_strlen(char *str)
{
    int i = 0;
    while (str && str[i])
        i++;
    return (i);
}

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
}


t_table *init_table()
{
    t_table *table;

    int i;

    i = 0;
    table = malloc(sizeof(t_table));
    if (!table)
    {
        ft_putstr_fd(2, "ALLOCATION FAILED!\n");
            return (NULL);
    }
    table->size = 0;
    while (i < BUFFER_SIZE)
        table->fileds[i++] = NULL;
    return (table);
}

t_filed    *make_field(char *keyword, char *value)
{
    t_filed *field;
    int  i;

    if (!keyword || !value)
        return (NULL);
    field = malloc(sizeof(t_filed));
    if (!field)
    {
        ft_putstr_fd(2, "ALLOCATION FAILED!\n");
        return (NULL);        
    }
    i = 0;
    field->keyword = malloc(ft_strlen(keyword) + 1);
    if (!field->keyword)
    {
        ft_putstr_fd(2, "ALLOCATION FAILED!\n");
        return (free(field), NULL);        
    }
    while (keyword[i])
    {
        field->keyword[i] = keyword[i];
        i++;
    }
    field->keyword[i] = '\0';
    i = 0;
    field->value = malloc(ft_strlen(value) + 1);
    if (!field->value)
    {
        ft_putstr_fd(2, "ALLOCATION FAILED!\n");
        return (free(field->keyword), free(field), NULL);      
    }
    while (value[i])
    {
        field->value[i] = value[i];
        i++;
    }
    field->value[i] = '\0';
    field->init = 69;
    return(field->next = NULL, field);
}

size_t    hashing(char *str, size_t size)
{
    unsigned int hash_value;

    hash_value = 0;
    while (*str)
    {
        hash_value = (hash_value * 31) + *str;
        str++;
    }
    return (hash_value % size);
}


bool    insert(t_table *table, t_filed *field)
{
    size_t hash;
    t_filed *current;

    if (!table || !field)
        return (false);
    hash = hashing(field->keyword, BUFFER_SIZE);
    if (!table->fileds[hash])
    {
        table->fileds[hash] = field;
        table->size++;
        return (true);
    }
    current = table->fileds[hash];
    while (current)
    {
        if (ft_strcmp(current->keyword, field->keyword) == 0)
        {
            current->value = field->value;
            field->value = NULL;
            free (field->keyword);
            free (field);
            table->size++;
            return (true);
        }
        if (!current->next)
        {
            current->next = field;
            table->size++;
            return (true);
        }
        current = current->next;
    }
    return (false);
}

char *read_line() {
    static char buffer[BUFFER_SIZE];
    static int buf_i = 0, buf_size = 0;
    char *line = malloc(BUFFER_SIZE);
    int line_len = 0;
    if (!line) return NULL;
    while (1) {
        if (buf_i >= buf_size) {
            buf_size = read(0, buffer, BUFFER_SIZE);
            buf_i = 0;
            if (buf_size <= 0)
                break;
        }
        char c = buffer[buf_i++];
        if (c == '\n')
            break;
        line[line_len++] = c;
    }
    line[line_len] = '\0';
    if (line_len == 0 && buf_size <= 0) {
        free(line);
        return NULL;
    }
    return line;
}

void    leakcheck()
{
    system("leaks hotrace");
}

int main(void)
{
    atexit(leakcheck);
    t_table *table;
    t_filed *field;
    char *keyword;
    char *value;

    table = init_table();
    while (69)
    {
        keyword = read_line();
        if (*keyword == 0)
        {
            free(keyword);
            break;
        }
        value = read_line();
        if (*value == 0)
        {
            free(keyword);
            free(value);
            break;
        }
        field = make_field(keyword, value);
        if (!field)
            return (ft_putstr_fd(2, "ALLOCATION FAILED!\n"), 1);
        if (!insert(table, field))
            return (ft_putstr_fd(2, "error!\n"), 1);
        free(keyword);
        free(value);
    }
    int id;
    while ((keyword = read_line()) != NULL)
    {
        id = hashing(keyword, BUFFER_SIZE);
        t_filed *current;
        current = table->fileds[id];
        if (!current)
        {
            ft_putstr_fd(1, keyword);
            ft_putstr_fd(1, ": Not Found.\n");
            free (keyword);
            continue ;
        }
        while (current)
        {
            if (ft_strcmp(current->keyword, keyword) == 0)
            {
                ft_putstr_fd(1, current->value);
                ft_putstr_fd(1, "\n");
                int i = 0;
                while (i < BUFFER_SIZE)
                {
                    if (table->fileds[i])
                    {
                        free(table->fileds[i]->keyword);
                        free(table->fileds[i]->value);
                        free(table->fileds[i]);
                    }
                    i++;
                }
                free(table),free(keyword),exit(1);
            }
            current = current->next;
        }
        free(keyword);
    }
    free(table);
    return (0);
}