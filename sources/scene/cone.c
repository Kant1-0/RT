/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 14:33:42 by nkhouide          #+#    #+#             */
/*   Updated: 2017/02/27 11:47:24 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cone	*new_cone(t_vec3 vertex, t_vec3 cp, const double tang)
{
	t_cone	*cone;

	if (!(cone = malloc(sizeof(t_cone))))	
		return (0);
	v3_normalize(&vertex);
	cone->vertex = vertex;
	cone->cp = cp;
	cone->tang = tang;
	return (cone);
}

BOOL	normal_cone(t_cone *cone, const t_ray ray, const float sol,
		t_hit *param)
{
	double	a;
	t_vec3	parta;
	t_vec3	partb;

	a = cone->m * cone->tang * cone->tang;
	parta = v3_scale_vec_(cone->vertex, a);
	partb = v3_sub_vec_(param->pos, v3_sub_vec_(cone->cp, v3_scale_vec_(cone->vertex, cone->m)));
	param->t = sol;
	param->pos = ray_point_at(ray, param->t);
	param->normal = v3_sub_vec_(partb, parta);
//	param->normal = v3_sub_vec_(param->pos,	v3_sub_vec_
//		(cone->cp, v3_scale_vec_(v3_scale_vec_(cone->vertex, (1 + cone->tang * cone->tang)), cone->m)));

	v3_normalize(&param->normal);
	
	return (TRUE);
}

BOOL	hit_cone(void *obj, const t_ray ray, const double t[2],
		t_hit *param)
{
	t_cone	*cone;
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sol;
	double	minm = -2.0;

	cone = (t_cone*)obj;
	oc = v3_sub_vec_(ray.orig, cone->cp);
	
	a = v3_dot_double_(ray.dir, ray.dir) - (1 + cone->tang * cone->tang) 
		* v3_dot_double_(ray.dir, cone->vertex)
		* v3_dot_double_(ray.dir, cone->vertex);

	b = 2 * (v3_dot_double_(ray.dir, oc) - (1 + cone->tang * cone->tang) 
		* v3_dot_double_(ray.dir, cone->vertex)
		* v3_dot_double_(oc, cone->vertex));

	c = v3_dot_double_(oc, oc) - (1 + cone->tang * cone->tang)
		* v3_dot_double_(oc, cone->vertex)
		* v3_dot_double_(oc, cone->vertex);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant >= 0)
	{
		sol = (-b - sqrt(discriminant)) / (2.0 * a);
		if (sol < t[1] && sol > t[0])
		{
			cone->m = (v3_dot_double_(ray.dir, v3_scale_vec_(cone->vertex, sol))
						+ v3_dot_double_(oc, cone->vertex));
			if (cone->m >= minm && cone->m <= 0)
				return (normal_cone(cone, ray, sol, param));
		}
		sol = (-b + sqrt(discriminant)) / (2.0 * a);
		if (sol < t[1] && sol > t[0])
		{
			cone->m = (v3_dot_double_(ray.dir, v3_scale_vec_(cone->vertex, sol))
						+ v3_dot_double_(oc, cone->vertex));
			if (cone->m >= minm && cone->m <= 0)
				return (normal_cone(cone, ray, sol, param));
		}
	}
	return (FALSE);
}