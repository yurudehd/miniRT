/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:21:38 by iyun              #+#    #+#             */
/*   Updated: 2022/10/02 17:40:56 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_equal(double num1, double num2)
{
	if (ft_abs(num1 - num2) < 0.000005)
		return (0);
	return (1);
}