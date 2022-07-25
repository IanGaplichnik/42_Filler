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

typedef struct s_insert
{
	int	x_act;
	int	y_act;
	int	i;
	int	overlap;
	int	lowest;
	int	priority;
	int	side;
	int	touch_enemy;
}	t_insert;

typedef struct s_map
{
	int	**heatmap;
	int	filled;
	int	best_x;
	int	best_y;
	int	max_value;
	int	best_value;
}	t_map;

typedef struct s_piece
{
	int	stars;
	int	p_height;
	int	p_width;
	int	*x;
	int	*y;
	int	*in_heat;
}	t_piece;

typedef struct s_data
{
	char	player;
	char	enemy;
	int		ex;
	int		ey;
	int		map_height;
	int		map_width;
	int		contact;
	int		side_touch;
	t_piece	*piece;
	t_map	*map;
}	t_data;

int		init_data(t_data *data, t_piece *piece, t_map *map);
int		read_piece_width_height(t_data *data);
int		read_piece_shape(t_data *data, int i);
int		build_piece(t_data *data);
int		read_map(t_data *data);
int		read_map_size(t_data *data);
int		read_players_symb(t_data *data);
int		mark_width_height(int *param, char *tmp);
int		build_heatmap(t_data *data);
int		update_heatmap(t_data *data, int x, int y);
int		place_iterative(t_data *data, int x, int y, int i);
int		build_piece_heatmap(t_data *data);

#endif
