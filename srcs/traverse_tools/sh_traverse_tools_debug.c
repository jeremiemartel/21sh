/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_debug.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 17:52:40 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/28 17:56:20 by jmartel          ###   ########.fr       */
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
