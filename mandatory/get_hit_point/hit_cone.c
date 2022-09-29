/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:49:20 by iyun              #+#    #+#             */
/*   Updated: 2022/09/29 19:32:54 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cone_meet(t_object object, t_meet *meet, t_line line)
{
	t_cylinder		*cone;
	t_point			temp_vec;
	t_formula_coef	coef;
	t_solution		solution;
	double			temp;

	cone = (t_cylinder *)(object.object);
	temp = cone->diameter * cone->diameter / cone->height * cone->height;
	coef.a = dot_product(line.dir_vec, line.dir_vec) - (1 + temp) * square(dot_product(line.dir_vec, cone->normal_vec));
	vec_minus_vec(line.start_point, cone->under_cent, &temp_vec);
	coef.b = dot_product(line.dir_vec, temp_vec) + temp * cone->height * dot_product(line.dir_vec, cone->normal_vec) - (1 + temp) * dot_product(temp_vec, cone->normal_vec) * dot_product(line.dir_vec, cone->normal_vec);
	coef.c = dot_product(temp_vec, temp_vec) + 2 * temp * cone->height * dot_product(temp_vec, cone->normal_vec) - (1 + temp) * square(dot_product(temp_vec, cone->normal_vec)) - square(cone->diameter);
	coef.discriminant = coef.b * coef.b - coef.a * coef.c;
	coef.max = (dot_product(cone->under_cent, cone->normal_vec) - dot_product(line.start_point, cone->normal_vec) + cone->height) / dot_product(line.dir_vec, cone->normal_vec);
	coef.min = (dot_product(cone->under_cent, cone->normal_vec) - dot_product(line.start_point, cone->normal_vec)) / dot_product(line.dir_vec, cone->normal_vec);
	//원뿔과 meet 여부//
	if (coef.discriminant < 0)
		return ;
	//원뿔 몸통//
	meet->temp_t = (coef.b * -1 + sqrt(coef.discriminant)) / coef.a;
	if (ret_min(coef.max, coef.min) <= meet->temp_t && meet->temp_t <= ret_max(coef.max, coef.min) && meet->temp_t > 0 && meet->parm_t > meet->temp_t)
		renew_parm_t(object, meet, line, CONE);
	meet->temp_t = (coef.b * -1 - sqrt(coef.discriminant)) / coef.a;
	if (ret_min(coef.max, coef.min) <= meet->temp_t && meet->temp_t <= ret_max(coef.max, coef.min) && meet->temp_t > 0 && meet->parm_t > meet->temp_t)
		renew_parm_t(object, meet, line, CONE);
	//원뿔 아랫면//
	temp_vec = line.dir_vec;
	n_multi_vec(coef.min, &temp_vec);
	vec_plus_vec(temp_vec, line.start_point, &temp_vec);
	if (distance(temp_vec, cone->under_cent) <= cone->diameter)
	{
		meet->parm_t = coef.min;
		meet->meet = temp_vec;
		meet->object_type = DOWN_CIRCLE;
		meet->object = object.object;
	}
}