#include "hotrace.h"

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


t_table *init_table(int size)
{
    t_table *table;
    int     i;

    table = malloc(sizeof(t_table));
    if (!table)
    {
        write(2 ,"ALLOCATION ERROR!\n", 18);
            return (NULL);
    }
    table->size = size;
    table->fileds = malloc(size * sizeof(t_filed *));
    if (!table->fileds)
    {
        free(table);
        write(2 ,"ALLOCATION ERROR!\n", 18);
            return (NULL);
    }
    i = 0;
    while (i < size)
        table->fileds[i++] = NULL;
    return (table);
}

t_filed    *make_field(char *keyword, char *value)
{
    t_filed *field;
    int  i;

    field = malloc(sizeof(t_filed));
    if (!field)
    {
        write(2, "Allocation Error!\n", 18);
        return (NULL);        
    }
    i = 0;
    field->keyword = malloc(ft_strlen(keyword) + 1);
    if (!field->keyword)
    {
        write(2, "Allocation Error!\n", 18);
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
        write(2, "Allocation Error!\n", 18);
        return (free(field->keyword), free(field), NULL);      
    }
    while (value[i])
    {
        field->value[i] = value[i];
        i++;
    }
    field->value[i] = '\0';
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
    hash = hashing(field->keyword, table->size);
    if (!table->fileds[hash])
    {
        table->fileds[hash] = field;
        return (true);
    }
    current = table->fileds[hash];
    while (current)
    {
        if (ft_strcmp(current->keyword, field->keyword) == 0)
        {
            free(current->value);
            current->value = field->value;
            field->value = NULL;
            free (field->keyword);
            free (field);
            return (true);
        }
        if (!current->next)
        {
            current->next = field;
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

int main(void)
{
    char *line;
    while (1)
    {
        line = read_line();
        printf("%s\n", line);
        free(line);
    }
}