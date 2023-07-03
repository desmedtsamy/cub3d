/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:54:40 by samy              #+#    #+#             */
/*   Updated: 2023/07/03 13:49:36 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"
# include "game.h"
# include "minimap.h"
# include "parsing.h"

# define DESTROYNOTIFY 17
# define KEYPRESS 2
# define KEYRELEASE 3
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define ESC_KEY 53
# define SPEED 0.5

typedef struct s_color
{
	int			rgb;
}				t_color;

typedef struct s_player
{
	t_pos		pos;
	t_pos		start_pos;
	double		orientation;
}				t_player;

typedef struct s_textures
{
	char		*no_texture_path;
	char		*so_texture_path;
	char		*we_texture_path;
	char		*ea_texture_path;
	void		*no_texture;
	void		*so_texture;
	void		*we_texture;
	void		*ea_texture;
}				t_textures;

typedef struct s_game
{
	t_minimap	minimap;
	t_player	player;
	t_move		move;
	char		**map;
	t_list		*map_list;
	int			map_width;
	int			map_height;
	void		*mlx;
	void		*window;
	t_textures	textures;
	int			floor_color;
	int			ceiling_color;

}				t_game;

void			error(char *message, t_game *game);
void			get_texture(char *pos, char *xpm_path, t_game *game);
void			set_pos(int x, int y, t_pos *pos);
void			free_game(t_game *game);
#endif