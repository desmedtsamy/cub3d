/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:54:40 by samy              #+#    #+#             */
/*   Updated: 2023/07/10 01:00:51 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# define MINI_X 200
# define MINI_Y 200
# define MINI_START 20
# define MINI_SQUARE_SIZE 10
# define PLAYER_SIZE 13
# define WALL_COLOR 0x2b2d3d
# define PLAYER_COLOR 0xff0000

typedef struct s_game	t_game;

typedef struct s_triangle
{
	t_pos		*p1;
	t_pos		*p2;
	t_pos		*p3;
}				t_triangle;

typedef struct s_minimap
{
	int			bg_color;
	int			floor_color;
	int			wall_color;
	int			player_color;
}				t_minimap;

void	init_minimap(t_game *game);
void	init_triangle(t_triangle *t, t_pos *p1, t_pos *p2, t_pos *p3);
void	draw_rect(t_rect *r, t_pos *max_p, int color, t_game *g);
void	draw_player(t_pos *pos, float angle, t_game *game);
#endif