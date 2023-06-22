#include "ms.h"
 
#define ERROR_MSG SHELL_MSG"wildcard: "

# include <sys/types.h>
# include <dirent.h>

//returns count of matches added
int    add_wildmatches_in_dir(char *dirname, t_list **lst, char *pattern)
{
	struct dirent	*dir;
    DIR				*d;
    int             count;

	if (!in('*', pattern))
        return (0);
    d = opendir(dirname);
    if (d == NULL) crash();
    
    count = 0;
    while ((dir = readdir(d)) != NULL)
    {
        if (dir->d_name[0] == '.')
            continue;
        if (match(dir->d_name, pattern))
        {
            ft_lstadd_back(lst, ft_lstnew(ft_strdup(dir->d_name)));
            count++;
        }
    }
    closedir(d);
    return (count);
}

void	add_wildmatches(t_list **lst, char *pattern)
{
    int count;

	count = add_wildmatches_in_dir(".", lst, pattern);
    if (count == 0)
        ft_lstadd_back(lst, ft_lstnew(ft_strdup(pattern)));
}
