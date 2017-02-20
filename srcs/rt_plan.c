/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhouide <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:25:50 by nkhouide          #+#    #+#             */
/*   Updated: 2017/02/20 17:43:01 by nkhouide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_plane	*new_plane(t_vec3 normale, t_vec3 on_plane)
{
	t_plane	*p;

	if (!(p = malloc(sizeof(t_plane))))
		return (0);
	p->normale = normale;
	p->on_plane = on_plane;
	return (p);
}

BOOL	normal_plane(t_plane *plane, const t_ray ray, const float sol,
		t_hit *param)
{
	param->t = sol;
	param->pos = ray_point_at(ray, param->t);
	if (v3_dot_double_(ray.dir , plane->normale) < 0)
		param->normal = plane->normale;
	else
		param->normal = v3_scale_vec_(plane->normale, -1);
	return (TRUE);
}

BOOL	hit_plane(void *obj, const t_ray ray, const double t[2],
		t_hit *param)
{
	t_plane	*plane;
	t_vec3	oc;
	double	sol;

	sol = 0.;
	plane = (t_plane*)obj;
	oc = v3_sub_vec_(ray.orig, plane->on_plane);
	if (v3_dot_double_(ray.dir , plane->normale))
	{
		sol = - (v3_dot_double_(oc, plane->normale)
			/ v3_dot_double_(ray.dir , plane->normale));
		if (sol > 0. && (sol < t[1] && sol > t[0]))
			return (normal_plane(plane, ray, sol, param));
	}
	return (FALSE);
}
