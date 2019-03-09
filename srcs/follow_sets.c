/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_sets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:46:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/08 23:59:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_follow_sets(t_cfg *cfg)
{
	(void)cfg;
	return (0);
}

int		sh_compute_follow_sets(t_cfg *cfg)
{
	cfg->symbols[cfg->start_index].follow_sets[END_OF_INPUT] = 1;
	while (sh_process_follow_sets(cfg))
		;
	return (0);
}
