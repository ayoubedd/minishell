/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:58:35 by hlahrach          #+#    #+#             */
/*   Updated: 2022/07/23 21:52:01 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../libft/libft.h"

typedef struct s_opt
{
	char			*opt;
	struct s_opt	*next;

}	t_opt;

typedef struct s_parser
{
	char			*cmd;
	t_opt			*cmd_option;
	t_list			*file_input;
	t_list			*file_output;
	int				parsre_left;
	int				parser_right;
	struct s_parser	*next;
}	t_parser;

#endif
