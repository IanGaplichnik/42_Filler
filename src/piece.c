/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:17:55 by igaplich          #+#    #+#             */
/*   Updated: 2022/07/06 19:18:03 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int	read_piece_width_height(t_data *data)
{
	char	tmp;

	tmp = '[';
	while (tmp != '\0' && (tmp < '0' || tmp > '9'))
	{
		if (read(0, &tmp, 1) < 1)
			return (-1);
	}
	if (tmp >= '0' && tmp <= '9')
		mark_width_height(&data->piece->p_height, &tmp);
	while (tmp != '\0' && (tmp < '0' || tmp > '9'))
	{
		if (read(0, &tmp, 1) < 1)
			return (-1);
	}
	if (tmp >= '0' && tmp <= '9')
		mark_width_height(&data->piece->p_width, &tmp);
	return (0);
}

int	build_piece(t_data *data)
{
	int	arr_size;

	arr_size = data->piece->p_height * data->piece->p_width;
	data->piece->x = (int *)malloc(sizeof(int) * arr_size);
	if (!data->piece->x)
		return (-1);
	data->piece->y = (int *)malloc(sizeof(int) * arr_size);
	if (!data->piece->y)
	{
		free(data->piece->x);
		return (-1);
	}
	return (0);
}

void	mark_piece_star(t_data *data, int x, int y, int *i)
{
	data->piece->x[*i] = x;
	data->piece->y[*i] = y;
	*i += 1;
}

int	read_piece_shape(t_data *data, int i)
{
	char	tmp;
	int		x;
	int		y;

	x = -1;
	y = 0;
	tmp = '[';
	if (read(0, &tmp, 1) < 0)
		return (-1);
	while (y < data->piece->p_height)
	{
		while (x < data->piece->p_width)
		{
			if (read(0, &tmp, 1) < 0)
				return (-1);
			x++;
			if (tmp == '*')
				mark_piece_star(data, x, y, &i);
		}
		x = -1;
		y++;
	}
	data->piece->stars = i;
	return (0);
}

int	build_piece_heatmap(t_data *data)
{
	int	i;

	data->piece->in_heat = (int *)malloc(sizeof(int) * data->piece->stars);
	if (!data->piece->in_heat)
		return (-1);
	else
	{
		i = 0;
		while (i < data->piece->stars)
			data->piece->in_heat[i++] = 0;
	}
	return (0);
}
