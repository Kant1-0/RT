/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:21:54 by vafanass          #+#    #+#             */
/*   Updated: 2017/03/27 15:09:50 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		button_matalbedo(void *param)
{
	char			value[256];
	t_rt			*rt;

	rt = (void*)param;
	if (rt->suspend)
	{
		ft_printf("%-40s", "Enter a new material albedo:");
		fgets(value, 255, stdin);
		while (value[0] == '\n' || !xml_to_vec(strtok(&value[0], "\n"),
			&rt->scene->this_obj->p_mat->albedo))
		{
			ft_printf("%-40s", "Try a different material albedo:");
			fgets(value, 255, stdin);
		}
		re_render_win(rt);
	}
}

void		button_mattexture(void *param)
{
	char			value[256];
	t_rt			*rt;

	rt = (void*)param;
	if (rt->suspend)
	{
		ft_printf("%-40s", "Enter a new material texture:");
		fgets(value, 255, stdin);
		while (value[0] == '\n' || !xml_to_texture(strtok(&value[0], "\n"),
			&rt->scene->this_obj->p_mat->m_text->type_texture))
		{
			ft_printf("%-40s", "Try a different material texture:");
			fgets(value, 255, stdin);
		}
		re_render_win(rt);
	}
}

void		button_mattype(void *param)
{
	char			value[256];
	t_rt			*rt;

	rt = (void*)param;
	if (rt->suspend)
	{
		ft_printf("%-40s", "Enter a new material type:");
		fgets(value, 255, stdin);
		while (value[0] == '\n' || !xml_to_material(strtok(&value[0], "\n"),
			&rt->scene->this_obj->p_mat->type_mat))
		{
			ft_printf("%-40s", "Try a different material type:");
			fgets(value, 255, stdin);
		}
		rt->scene->this_obj->p_mat->scatter = select_scatter(
		rt->scene->this_obj->p_mat->type_mat);
		if (rt->scene->this_obj->p_mat->type_mat == MAT_DIFF_LIGHT)
			rt->scene->this_obj->p_mat->emitted =
			rt->scene->this_obj->p_mat->albedo;
		else if (rt->scene->this_obj->p_mat->type_mat == MAT_DIELECT)
			rt->scene->this_obj->p_mat->t = 1.;
		else if (rt->scene->this_obj->p_mat->type_mat == MAT_METAL)
			rt->scene->this_obj->p_mat->t = 0.;
		re_render_win(rt);
	}
}

void		button_matmetal(void *param)
{
	char			value[256];
	t_rt			*rt;

	rt = (void*)param;
	if (rt->suspend)
	{
		ft_printf("%-40s", "Enter a new metal reflection:");
		fgets(value, 255, stdin);
		while (value[0] == '\n' || !xml_to_double(strtok(&value[0], "\n"),
			&rt->scene->this_obj->p_mat->t))
		{
			ft_printf("%-40s", "Try a different metal reflection:");
			fgets(value, 255, stdin);
		}
		re_render_win(rt);
	}
}

void		button_matdielect(void *param)
{
	char			value[256];
	t_rt			*rt;

	rt = (void*)param;
	if (rt->suspend)
	{
		ft_printf("%-40s", "Enter a new dielect refraction:");
		fgets(value, 255, stdin);
		while (value[0] == '\n' || !xml_to_double(strtok(&value[0], "\n"),
			&rt->scene->this_obj->p_mat->t))
		{
			ft_printf("%-40s", "Try a different dielect refraction:");
			fgets(value, 255, stdin);
		}
		re_render_win(rt);
	}
}