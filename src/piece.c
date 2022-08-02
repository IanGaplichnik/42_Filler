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

/* Width and height of a single piece are read.
 * After reading, values are being converted to integers
 * and saved in data->piece structure
 */
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

/*
 * Based on the dimensions of the piece, 2D integer array is being created
 */
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

/*
 * Reading piece shape from the input and saving non-empty
 * coordinates in separate piece->x and piece->y arrays.
 * For instance, coordinates for 2x2 square, missing top left slot will be:
 * x: 1, 0, 1
 * y: 0, 1, 1
 */
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
