/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:16:47 by igaplich          #+#    #+#             */
/*   Updated: 2022/07/06 19:17:03 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
 * Converting string number to an integer and saving
 * it to a passed parameter: width or height of
 * either map or piece
 */
int	mark_width_height(int *param, char *tmp)
{
	while (*tmp >= '0' && *tmp <= '9')
	{
		*param = (*param * 10) + (*tmp - '0');
		if (read(0, tmp, 1) < 0)
			return (-1);
	}
	return (0);
}

/*
 * Reading width and height of the play field.
 * Readings are converted into an int value and saved in
 * data structure.
 * If width or height is less, than one, or there's an error
 * reading the input, -1 is returned.
 */
int	read_map_size(t_data *data)
{
	char	tmp;
	int		ret;

	tmp = '[';
	while (tmp != '\0' && (tmp < '0' || tmp > '9'))
	{
		ret = read(0, &tmp, 1);
		if (ret < 0)
			return (-1);
	}
	if (tmp >= '0' && tmp <= '9')
		mark_width_height(&data->map_height, &tmp);
	while (tmp != '\0' && (tmp < '0' || tmp > '9'))
	{
		ret = read(0, &tmp, 1);
		if (ret < 0)
			return (-1);
	}
	while (tmp >= '0' && tmp <= '9')
		mark_width_height(&data->map_width, &tmp);
	if (data->map_height < 1 || data->map_width < 1)
		return (-1);
	return (0);
}

/* 
 * Reading players symbols in the beginning of the game.
 * If players number is 1, then it uses 'O' and 'o' symbols
 * on the playing field. Otherwise, it uses 'X' and 'x' symbols.
 */
int	read_players_symb(t_data *data)
{
	char	tmp;

	tmp = '}';
	while (tmp != '\0' && (tmp < '0' || tmp > '9'))
	{
		if (read(0, &tmp, 1) < 0)
			return (-1);
	}
	if (tmp == '1')
	{
		data->player = 'O';
		data->enemy = 'X';
	}
	else if (tmp == '2')
	{
		data->player = 'X';
		data->enemy = 'O';
	}
	return (0);
}

/*
 * Parsing one row of the playfield from STDIN.
 * if symbol corresponds to the enemy symbol, corresponding
 * heatmap value is marked set to 0. If symbol corresponds
 * to the player symbol, corresponding heatmap value is set to -2
 */
int	parse_map_row(t_data *data, char *tmp, int y)
{
	int	x;

	x = 0;
	while (x < data->map_width)
	{
		if (*tmp == '.')
			data->map->heatmap[y][x] = -1;
		if (*tmp == data->player)
			data->map->heatmap[y][x] = -2;
		if (*tmp == data->enemy || *tmp == data->enemy + 40)
		{
			if (data->map->heatmap[y][x] != 0)
			{
				data->ex = x;
				data->ey = y;
			}
			data->map->heatmap[y][x] = 0;
		}
		if (read(0, tmp, 1) < 0)
			return (-1);
		x++;
	}
	return (1);
}

/*
 * Map is being read. Skipping rubbish values
 * before the actual map starts, and then calling
 * the parsing function to parse one row
 */
int	read_map(t_data *data)
{
	char	tmp;
	int		y;

	y = 0;
	tmp = '[';
	while (y < data->map_height)
	{
		while (tmp != '\0' && tmp != '.' && tmp != 'O' && tmp != 'X'
			&& tmp != 'P' && tmp != 'o' && tmp != 'x')
		{
			if (read(0, &tmp, 1) < 0)
				return (-1);
		}
		parse_map_row(data, &tmp, y);
		y++;
	}
	return (0);
}
