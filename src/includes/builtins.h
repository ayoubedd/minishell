/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:10:28 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/11 15:31:30 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "execution.h"

typedef enum e_bultin {
	NON,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}	t_builtin;

typedef enum e_exmode {
	NORMAL,
	EMBEDDED
}	t_exmode;

void		env_blt(t_exec *exec);
void		pwd_blt(t_exec *exec);
void		cd_blt(t_exec *exec, t_cmd *cmd);
void		exit_blt(t_cmd *cmd);
void		echo_blt(t_cmd *cmd);
void		unset_blt(t_exec *exec, t_cmd *cmd);
void		export_blt(t_exec *exec, t_cmd *cmd);
void		exec_blt(t_exec *exec, t_cmd *cmd, t_parser *raw, t_exmode mode);
t_exenv		*find_item(t_exenv *env, char *key);
char		*extract_key(char *str);
char		*extract_value(char *str);
void		exenv_insert_var(t_exenv **env, char *key, char *val);
void		exenv_add_back(t_exenv **env, t_exenv *node);
t_builtin	which_builtin(t_parser *list);
t_exmode	exec_mode(t_parser *raw);
t_bool		valid_key_check(char *key);

#endif