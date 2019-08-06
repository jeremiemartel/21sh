/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_debug.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 17:52:40 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/29 00:45:24 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	*t_phase_name(t_phase phase)
{
	if (phase == E_TRAVERSE_PHASE_EXECUTE)
		return ("execute");
	else if (phase == E_TRAVERSE_PHASE_EXPANSIONS)
		return ("expansions");
	else if (phase == E_TRAVERSE_PHASE_REDIRECTIONS)
		return ("redirections");
	else if (phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
		return ("interactive redirections");
	return ("");
}

char	*ret_to_str(int ret)
{
	if (ret == 0)
		return ("SUCCESS");
	else if (ret == 1)
		return ("ERROR");
	else if (ret == 2)
		return ("FAILURE");
	else if (ret == 3)
		return ("ATTR_ERROR");
	else if (ret == 4)
		return ("STOP_CMD_LINE");
	else if (ret == 5)
		return ("CTRL_D");
	else if (ret == 6)
		return ("CTRL_C");
	else if (ret == 7)
		return ("KEEP_READ");
	else
		return ("unknown returned value");
}
