/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 22:11:23 by qfremeau          #+#    #+#             */
/*   Updated: 2016/12/22 15:48:57 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cam		set_camera(t_vec3 look_from, t_vec3 look_at, t_vec3 v_up, \
			t_camparam param)
{
	t_cam			cam;
	double			theta;
	
	cam.param = param;
	cam.lens_radius = param.aperture / 2.;
	theta = param.vfov * M_PI / 180.;
	cam.half_height = tan(theta / 2.);
	cam.half_width = param.aspect * cam.half_height;
	cam.param.look_from = look_from;
	cam.param.look_at = look_at;
	cam.param.v_up = v_up;
	cam.w = v3_unit_vec_(v3_sub_vec_(cam.look_from, cam.look_at));
	cam.u = v3_unit_vec_(v3_cross_vec_(cam.v_up, w));
	cam.v = v3_cross_vec_(cam.w, cam.u);
	cam.low_left_corner = v3_sub_vec_(v3_sub_vec_(v3_sub_vec_(cam.look_from,
	v3_scale_vec_(cam.u, cam.half_width * param.focus)), v3_scale_vec_(cam.v,
	cam.half_height * param.focus)), v3_scale_vec_(cam.w, param.focus));
	cam.horizontal = v3_scale_vec_(cam.u, 2. * cam.half_width * param.focus);
	cam.vertical = v3_scale_vec_(cam.v, 2. * cam.half_height * param.focus);
	return (cam);
}
