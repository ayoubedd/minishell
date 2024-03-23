/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:25:27 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/12 22:29:30 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include "../../includes/signals.h"
#include <readline/history.h>
#include <readline/readline.h>

int	g_exit_code;

t_lexer	*parse_line_helper(t_env **env)
{
	char		*tmp;
	char		*line;
	t_lexer		*lexer;

	tmp = readline ("minishell $ ");
	if (tmp == NULL)
		return (NULL);
	base_line_case(tmp);
	line = ft_strtrim(tmp, " \n\t\r\f\v");
	free (tmp);
	tmp = parser_new_string (line, env, 5);
	free (line);
	lexer = init_lexer(tmp);
	if (lexer == NULL)
		return (NULL);
	return (lexer);
}

void	parser_line_helper2(t_minshell **minishell,
		t_data **data, t_parser **parse)
{
	parser_parse_lexer(data, parse);
	(*minishell)->parser = *parse;
}

void	parse_line(t_env *env_data, t_minshell **minishell,
		t_data **data, t_parser *parse)
{
	t_lexer		*lexer;
	int			n;

	n = 0;
	lexer = parse_line_helper(&env_data);
	if (lexer == NULL)
		exit(g_exit_code);
	if (check_not_empty (&lexer) == 1)
		return ;
	n = lexer_get_next_token(lexer, data);
	free (lexer->cmd);
	free (lexer);
	if (n == 1 || syntax_error (data) == 0)
	{
		if (n == 1)
			syntax_error2 (minishell, data, &parse);
		else if (syntax_error (data) == 0)
			syntax_error3 (minishell, data, &parse);
		ft_clear(data);
		parser_clear (&(*minishell)->parser);
		return ;
	}
	parser_line_helper2 (minishell, data, &parse);
}

/* ===================== main ============ */
int	main(int ac, char **av, char **env)
{
	t_minshell	*minishell;
	t_data		*data;

	data = NULL;
	g_exit_code = 0;
	minishell = ft_calloc(1, sizeof (t_minshell));
	(void)av;
	if (ac != 1)
		return (ft_error ("Error bad arguments \n", 1));
	minishell->env = NULL;
	minishell->parser = NULL;
	insert_env (&minishell->env, env);
	signal_handling();
	minishell->cwd = getcwd(NULL, 0);
	if (!minishell->cwd)
		ft_putstr_fd("shell-init: error retrieving \
current directory\n", STDERR_FILENO);
	while (1)
	{
		parse_line(minishell->env, &minishell, &data, minishell->parser);
		executor (minishell);
		giga_clear (&minishell->parser, &data);
	}
	free (minishell);
	ft_clear_env(&minishell->env);
	return (0);
}
