/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkitoko <gkitoko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:51:46 by gkitoko           #+#    #+#             */
/*   Updated: 2022/11/15 19:34:38 by gkitoko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global	g_glo;

void	print_word_list(t_lexer_node *node)
{
	if (node == NULL)
		return ;
	printf("%s ->\n", node->word);
	print_word_list(node->next);
}

static
void	print_env_list(t_env_node *node)
{
	if (node == NULL)
		return ;
	printf("%s ->\n", node->var);
	print_env_list(node->next);
}


int	main(int ac, char **av, char **envp)
{
	char	*str;

	(void)av;
	init_global(envp);
	if (ac > 1)
		return (printf("minishell binary does not take any argument.\n"), 0);
	print_env_list(g_glo.env);
	while (1)
	{
		str = readline("minishell~ ");
		add_history(str);
		lexer(str);
	}
	ft_free();
	return (0);
}

/*
```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "unistd.h"
# define    T_PIPE 1
# define    T_REDIRECT_IN 2
# define    T_REDIRECT_OUT 3
# define    T_HEREDOC 4
# define    D_REDIRECT_OUT 5
# define    S_QUOTE 6
# define    D_QUOTE 7


typedef struct s_lexer_node
{
	struct s_lexer_node	*next;
	char				*word;
	char				*token;
}				t_lexer_node;

int valid_quote(char *str, char quote)
{
	int i = 0;
	int res = 0;
	while (str[i])
	{
		if (str[i] == quote)
			res++;
		i++;
	}
	if (res % 2 == 0)
		return (1);
	return (0);
}

int    ft_ischarset(char c)
{
    if (c == ' ' || c == '\t'|| c == '\r')
        return (1);
    return (0);
}

int ft_isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int white_space_to_neg(char **str)
{
    int		i;
    char	start;

    i = 1;
    start = (*str)[0];
    while ((*str)[i] && (*str)[i] != start)
	{
		if (ft_ischarset((*str)[i]))
			(*str)[i] *= -1;
		i++;
	}
	if ((*str)[i] != start)
		return (-1);
	return (i);
}

int	quote_space_to_neg(char **str)
{
	int 	i;
	int		return_index;
	char	*quoted_substring;

	i = 0;
	return_index = 0;
	while ((*str)[i])
	{
		if ((*str)[i] && ((*str)[i] == '"' || (*str)[i] == '\''))
		{
			quoted_substring = &(*str)[i];
			return_index = white_space_to_neg(&quoted_substring);
			if (return_index < 0)
				return (0);
			i += return_index;
		}
		i++;
	}
	return (1);
}

int	unscape_quote(char **str)
{
	int 	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] && ((*str)[i] == '\\'))
		{
			if (ft_isquote(*(str)[i + 1]))
				(*str)[i + 1] *= -1;
		}
		i++;
	}
	return (1);
}

void quote_unscaped_establish(char *str)
{
	int i;

	if (!str)
		return ; 
	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
}

void quote_space_establish(char *str)
{
	int i;

	if (!str)
		return ; 
	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
}

int main(void)
{
   	char	*str;

	str = readline("minishell~ ");
	add_history(str);
	char **split;
	if(!quote_space_to_neg(&str))
		return (0);
	int i = 0;
	split =  ft_split(str);
	while (split[i])
		quote_space_establish(split[i++]);
	i = 0;
	while(split[i])
		printf("%s\n",split[i++]);
	return (0);
}
*/
