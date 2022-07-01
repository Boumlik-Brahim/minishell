#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

char check_in_out_operators(char *line, char oper)
{
	int i;
	char flag;

	i = 0;
	flag = 0;
	while(line[i])
	{
		if (line[i] == oper && line[i + 1] == oper)
			i += 2;
		if (!flag && line[i] == oper)
			flag = !flag;
		else if (flag && line[i] == oper)
			return (1);
		if (flag && !ft_strchr("#&();|<> \\`~/", line[i]))
			flag = !flag;
		i++;
	}
	if (flag)
		return (1);
	return (0);
}

/*----------------------------------------------------------------------------*/

char	check_errors(char *line)
{
	if (check_qoutes(line))
		return (1);
	if (check_in_out_operators(line, '<'))
		return (1);
	if (check_in_out_operators(line, '>'))
		return (1);
	return (0);
}