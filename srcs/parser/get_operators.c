#include "../../minishell.h"

/*----------------------------------------------------------------------------*/

void    check_file_permession(char  *file, int macro)
{
    if (macro == RED_IN)
	{
		if (access(file, F_OK) != 0)
			put_error(file, "No such file of directory");
		else if (access(file, R_OK) != 0)
			put_error(file, "Permission denied");
	}
    if (macro == RED_OUT || macro == RED_APPEND)
		if (access(file, W_OK) != 0)
			put_error(file, "Permission denied");
}

/*----------------------------------------------------------------------------*/

int	open_file(char *filename, int macro)
{
	int file;
	int	type;

    file = -1;
	type = -1;
    if (macro == RED_IN)
	{
        file = open(filename, O_RDONLY);
		type = RED_IN;
	}
    else if (macro == RED_OUT)
	{
	    file = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		type = RED_OUT;
	}
    else if (macro == RED_APPEND)
	{
        file = open(filename, O_CREAT | O_RDWR | O_APPEND, 0777);
		type = RED_APPEND;
	}
	if (type && file < 0)
		check_file_permession(filename, type);
	return (file);
}
