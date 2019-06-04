/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_map.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 11:11:47 by fhignett       #+#    #+#                */
/*   Updated: 2019/05/06 15:14:10 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

double	ft_map(double n, double *old, double *new)
{
	return ((n - old[0]) * (new[1] - new[0]) / (old[1] - old[0]) + new[0]);
}
