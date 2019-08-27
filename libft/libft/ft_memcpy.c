/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 20:14:45 by fhignett       #+#    #+#                */
/*   Updated: 2019/08/27 19:14:25 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	char			*d;
	const char		*s;
	long long		*d8;
	const long long	*s8;

	i = 0;
	d8 = dst;
	s8 = src;
	while (n - (i * 8) > 8)
	{
		d8[i] = s8[i];
		i++;
	}
	i *= 8;
	if (i == n)
		return (dst);
	d = dst;
	s = src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
