/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:07:05 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/08 14:19:16 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

t_bool	check_file_exist(t_file *file)
{
	if (access(file->file_name, R_OK))
		return (FALSE);
	return (TRUE);
}
