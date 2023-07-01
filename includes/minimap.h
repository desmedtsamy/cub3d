/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:54:40 by samy              #+#    #+#             */
/*   Updated: 2023/07/02 00:41:13 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# define MINI_X 200
# define MINI_Y 200
# define MINI_START 20
# define MINI_SQUARE_SIZE 10

typedef struct s_game	t_game;

typedef struct s_minimap
{
	int			bg_color;
	int			floor_color;
	int			wall_color;
	int			player_color;
}				t_minimap;

void	draw_minimap(t_pos *start, t_pos *size, t_pos *pos_max, t_game *g);
void	init_minimap(t_game *game);
void	draw_rect(t_rect *r, t_pos *max_p, int color, t_game *g);
#endif