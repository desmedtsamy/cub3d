/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 21:55:23 by samy              #+#    #+#             */
/*   Updated: 2023/07/12 10:57:11 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define WIN_W 1280
# define WIN_H 720
# define XPM_SIZE 64
# define FOV 70
# define MOVE_SPEED 0.08
# define SIDE_SPEED 0.05
# define CAMERA_SPEED 0.1
# define SLIDE_SPEED 0.05

typedef struct s_game	t_game;

typedef struct s_posint
{
	int					x;
	int					y;
}						t_posint;

typedef struct s_pos
{
	double				x;
	double				y;
}						t_pos;

typedef struct s_move
{
	int					forward;
	int					backward;
	int					left;
	int					right;
	int					turn_left;
	int					turn_right;
}						t_move;

typedef struct s_rect
{
	t_pos				*pos;
	t_pos				*end_pos;
	t_pos				*max;
}						t_rect;

typedef struct s_img
{
	void				*ptr;
	char				*addr;
	int					bpp;
	int					sl;
	int					endian;
}						t_img;

void					move_forward(t_game *game, int x);
void					move_sideways(t_game *game, int y);
void					rotate_left(t_game *game);
void					rotate_right(t_game *game);
t_rect					*set_rect(t_pos *pos, t_pos *end_pos, t_rect *rect);
t_game					*init_game(t_game *game);
void					minimap(t_game *game);
int						raycasting(t_game *game);
unsigned int			get_pixel_color(t_game *game, int tex_x, int tex_y);
void					ft_mlx_pixel_put(t_game *game, int x, int y,
							unsigned int col);
double					length_until_hit(t_game *game);
int						get_texture_column(t_game *game, double dist);
void					*select_texture(t_game *game);
int						is_dir(char *str);
void					moves(t_game *game);
#endif