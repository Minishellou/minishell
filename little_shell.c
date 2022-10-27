#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char *str;
	int i = 0;

	while(1)
	{
		str = readline("minishell~ ");
		add_history(str);
		if (str[i] == 'x')
		{
			break;
		}
		printf("%s", str);
		printf("\n");
	}
	return (0);
}
