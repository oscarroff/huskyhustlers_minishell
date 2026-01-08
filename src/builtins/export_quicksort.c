#include "../../inc/minishell.h"
#include "../../inc/execution.h"

static void swap(char **a, char **b);
static int  qs_strcmp(const char *s1, const char *s2);

void    quicksort(char **envp, int low, int high)
{
    int     i;
    int     current;
    char    *pivot;

    if (low >= high)
        return ;
    i = low;
    current = low;
    pivot = envp[high];
    while (current < high)
    {
        if (qs_strcmp(envp[current], pivot) < 0)
        {
            swap(&envp[i], &envp[current]);
            i++;
        }
        current++;
    }
    swap(&envp[i], &envp[high]);
    quicksort(envp, low, i - 1);
    quicksort(envp, i + 1, high);
}

static void swap(char **a, char **b)
{
    char     *temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

static int  qs_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return ((const unsigned char)*s1 - (const unsigned char)*s2);
}