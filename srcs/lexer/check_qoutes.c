#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

static char check_qoutes_util(char c, char *flag, char *dbl, char *sngl)
{
	if (c == '\"')
	{
		if (!*flag)
			*flag = 'd';
		if (*flag == 'd' && *dbl && *sngl)
		{
			*sngl = !*sngl;
			*flag = 0;
		}
		*dbl = !*dbl;
	}
	else if (c == '\'')
	{
		if (!*flag)
			*flag = 's';
		if (*flag == 's' && *dbl && *sngl)
		{
			*dbl = !*dbl;
			*flag = 0;
		}
		*sngl = !*sngl;
	}
	// else if (ft_strchr("!#%&()*+,:;@[\\]^_`{}", c) && (!*dbl && !*sngl))
	// 	return (1);
	return (0);
}

/*----------------------------------------------------------------------------*/

char check_qoutes(char *line)
{
    int i;
    char dbl;
    char sngl;
	char flag;

    dbl = 0;
    sngl = 0;
	flag = 0;
    i = 0;
    while (line[i])
    {
		if (check_qoutes_util(line[i], &flag, &dbl, &sngl))
			return (1);
        i++;
    }
    if (dbl || sngl)
        return (1);
    return (0);
}
