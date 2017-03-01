/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 18:00:00 by qfremeau          #+#    #+#             */
/*   Updated: 2017/03/01 15:56:02 by vafanass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**SDL_WINDOWEVENT_RESIZED needs more work, and other rendering functions
**need to get dynamic values not just MACROS.
*/

void		button_list(t_rt *rt, t_input *in)
{
	t_button		*button_curs;

	button_curs = rt->panel.lst_button;
	while (button_curs != NULL)
	{
		if (in->m_x > button_curs->rect->x &&
				in->m_x < (button_curs->rect->x + button_curs->rect->w) &&
				in->m_y > button_curs->rect->y &&
				in->m_y < (button_curs->rect->y + button_curs->rect->h))
		{
			button_curs->hover = TRUE;
			if (in->button[SDL_BUTTON_LEFT])
			{
				button_curs->action(button_curs->param);
				SDL_Delay(300);
			}
		}
		else
			button_curs->hover = FALSE;
		button_curs = button_curs->next;
	}
}

void		windows_resized(t_rt *rt, t_input *in)
{
	pthread_cancel(rt->render_th);
	pthread_join(rt->render_th, NULL);
	rt->render = 0;
	udpate_view(rt);
	free(rt->r_menu);
	reset_menu(rt);
	display_rt(rt);
	pthread_create(&rt->render_th, NULL, (void*)render_loop, (void*)rt);
	in->window = 0;
}

void		button_left(t_rt *rt, t_input *in)
{
	if (in->m_x < rt->r_view->w && in->m_y < rt->r_view->h)
	{
		set_viewparam(&rt->panel.viewparam, rt, in->m_x, in->m_y);
		update_menu(rt);
	}
}

void		rt_events_bis(t_rt *rt, t_input *in)
{
	if (rt->suspend == TRUE && in->key[SDL_SCANCODE_RIGHT] &&
			in->button[SDL_BUTTON_RIGHT])
		right_rmouse(rt);
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_LEFT] &&
			in->button[SDL_BUTTON_RIGHT])
		left_rmouse(rt);
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_UP] &&
			in->button[SDL_BUTTON_RIGHT])
		up_rmouse(rt);
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_DOWN] &&
			in->button[SDL_BUTTON_RIGHT])
		down_rmouse(rt);
}

void		rt_events(t_rt *rt, t_input *in)
{
	esdl_update_events(in, &rt->esdl->run);
	if (in->quit)
		pthread_join(rt->render_th, NULL);
	button_list(rt, in);
	if (in->window == SDL_WINDOWEVENT_RESIZED)
		windows_resized(rt, in);
	else if (in->button[SDL_BUTTON_LEFT])
		button_left(rt, in);
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_RIGHT] &&
			!in->button[SDL_BUTTON_RIGHT])
		right_lmouse(rt);
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_LEFT] &&
			!in->button[SDL_BUTTON_RIGHT])
		left_lmouse(rt);
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_UP] &&
			!in->button[SDL_BUTTON_RIGHT])
		up_lmouse(rt);
	else if (rt->suspend == TRUE && in->key[SDL_SCANCODE_DOWN] &&
			!in->button[SDL_BUTTON_RIGHT])
		down_lmouse(rt);
	else
		rt_events_bis(rt, in);
}
