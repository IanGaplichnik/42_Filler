/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:12:13 by igaplich          #+#    #+#             */
/*   Updated: 2022/07/05 15:12:14 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libft/includes/ft_printf.h"

//DELETE
# include <fcntl.h>
# include <stdio.h>
//DELETE

typedef struct s_map
{
	int	**heatmap;
}	t_map;

typedef struct s_piece
{
	int	stars;
	int	pheight;
	int	pwidth;
	int	*x;
	int	*y;
}	t_piece;

typedef struct s_data
{
	FILE	*read_log;
	FILE	*struct_log;
	FILE	*heat_log;
	int		map_test;
	char	player;
	char	enemy;
	int		map_height;
	int		map_width;
	t_piece	*piece;
	t_map	*map;
}	t_data;

void	print_struct(t_data *data);
int		init_data(t_data *data, t_piece *piece, t_map *map);
int		read_piece_width_height(t_data *data);
int		read_piece_shape(t_data *data);
int		build_piece(t_data *data);
int		read_map(t_data *data);
int		read_map_size(t_data *data);
int		read_players_symb(t_data *data);
int		mark_width_height(int *param, t_data *data, char *tmp);
int		build_heatmap(t_data *data);
void	print_heatmap(t_data *data);
int		update_heatmap(t_data *data);
int		smallest_around(t_data *data, int x, int y);
int		fill_heatmap(t_data *data, int x, int y);
int		place_piece(t_data *data);

#endif
