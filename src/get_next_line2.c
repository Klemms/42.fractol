/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 01:56:37 by cababou           #+#    #+#             */
/*   Updated: 2018/09/16 23:11:27 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	remove_and_free(t_lstcontainer *cont, t_list *el)
{
	free(((t_file *)el->content)->content);
	cont->remove(cont, el);
}
