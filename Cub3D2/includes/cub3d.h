/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:54:40 by samy              #+#    #+#             */
/*   Updated: 2023/07/05 19:51:03 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "game.h"
# include "minimap.h"
# include "math.h"

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
	t_pos		dir;
	t_pos		plane;
	t_pos		step;
	t_pos		delta;
	t_pos		side;
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
	int			side;
}				t_game;

void			error(char *message, t_game *game);
t_game			*parsing(int argc, char **argv, t_game *game);
void			get_data(int fd, t_game *game);
int				open_file(char *path);
void			check_file(char *path, char *file_type, t_game *game);
int				is_valid_map(t_game *game);
void			create_map(t_game *game);
int				is_start_pos(char c);
int				is_accesible(char c);
int				is_valid_elem(char c);
void			get_texture(char *pos, char *xpm_path, t_game *game);
void			set_pos(int x, int y, t_pos *pos);
#endif