/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_output_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:39:52 by gkitoko           #+#    #+#             */
/*   Updated: 2023/01/16 21:27:43 by mcorso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	tokenizer(void);

int	process_lexer_output_chain(char *input)
{
	if (quote_neon(&input) != SUCCESS)
		return (ft_putstr_fd("syntax error: invalid cmd line\n", 2), ERROR);
	if (catch_parsing_error(input) != SUCCESS)
		return (ft_putstr_fd("syntax error: invalid cmd line\n", 2), ERROR);
	g_glo.lexer_output_chain = lexer_line_parsing_process(input);
	if (g_glo.lexer_output_chain == NULL)
		return (ERROR);
	tokenizer();
	if (catch_redir_error() != SUCCESS)
		return (ft_putstr_fd("syntax error: invalid cmd line\n", 2), ERROR);
	if (reset_double_quote_content_to_pst() != SUCCESS)
		return (ERROR);
	if (!envar_expansion())
		return (ERROR);
	if (reset_single_quote_content_to_pst() != SUCCESS)
		return (ERROR);
	if (unquoted_lexer_output_chain() != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

static void	tokenizer(void)
{
	t_lexer_node	*tmp;
	int				word_len;

	tmp = g_glo.lexer_output_chain;
	while (tmp)
	{
		word_len = ft_strlen(tmp->word);
		if (!ft_strncmp(tmp->word, "|", word_len))
			tmp->token = PIPE;
		else if (!ft_strncmp(tmp->word, "<", word_len))
			tmp->token = LESS;
		else if (!ft_strncmp(tmp->word, ">", word_len))
			tmp->token = GREAT;
		else if (!ft_strncmp(tmp->word, "<<", word_len))
			tmp->token = LESSER;
		else if (!ft_strncmp(tmp->word, ">>", word_len))
			tmp->token = GREATER;
		else
			tmp->token = WORD;
		tmp = tmp->next;
	}
}
