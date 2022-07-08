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

int	mark_width_height(int *param, t_data *data, char *tmp)
{
	while (*tmp >= '0' && *tmp <= '9')
	{
		*param = (*param * 10) + (*tmp - '0');
		if (read(data->map_test, tmp, 1) < 0)
			return (-1);
		fprintf(data->read_log, "%c", *tmp);
	}
	return (0);
}

int	read_map_size(t_data *data)
{
	char	tmp;
	int		ret;

	tmp = '[';
	while (tmp != '\0' && (tmp < '0' || tmp > '9'))
	{
		ret = read(data->map_test, &tmp, 1);
		if (ret < 0)
			return (-1);
		fprintf(data->read_log, "%c", tmp);
	}
	if (tmp >= '0' && tmp <= '9')
		mark_width_height(&data->map_height, data, &tmp);
	while (tmp != '\0' && (tmp < '0' || tmp > '9'))
	{
		ret = read(data->map_test, &tmp, 1);
		if (ret < 0)
			return (-1);
		fprintf(data->read_log, "%c", tmp);
	}
	while (tmp >= '0' && tmp <= '9')
		mark_width_height(&data->map_width, data, &tmp);
	if (data->map_height < 1 || data->map_width < 1)
		return (-1);
	return (0);
}

int	read_players_symb(t_data *data)
{
	char	tmp;
	int		ret;

	tmp = '}';
	while (tmp != '\0' && (tmp < '0' || tmp > '9'))
	{
		ret = read(data->map_test, &tmp, 1);
		if (ret < 0)
			return (-1);
		fprintf(data->read_log, "%c", tmp);
	}
	fprintf(data->read_log, "%c", '\n');
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

int	read_map(t_data *data)
{
	char	tmp;
	int		x;
	int		y;

	y = 0;
	tmp = '[';
	while (y < data->map_height)
	{
		while (tmp != '\0' && tmp != '.' && tmp != 'O'
			&& tmp != 'X' && tmp != 'P')
		{
			if (read(data->map_test, &tmp, 1) < 0)
				return (-1);
			fprintf(data->read_log, "%c", tmp);
		}
		x = 0;
		while (x < data->map_width)
		{
			if (tmp == data->player || tmp == data->player + 40)
				data->map->heatmap[y][x] = -2;
			else if (tmp == data->enemy || tmp == data->enemy + 40)
				data->map->heatmap[y][x] = 1;
			if (read(data->map_test, &tmp, 1) < 0)
				return (-1);
			fprintf(data->read_log, "%c", tmp);
			x++;
		}
		y++;
	}
	return (0);
}
