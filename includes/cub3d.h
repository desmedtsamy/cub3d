/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:54:40 by samy              #+#    #+#             */
/*   Updated: 2023/06/27 17:41:29 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

# define XPM_SIZE 64

typedef struct s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct s_color
{
	int				rgb;
}					t_color;

typedef struct s_player
{
	t_pos			pos;
	t_pos			start_pos;
	char			orientation;
}					t_player;
typedef struct s_textures
{
	char			*no_texture_path;
	char			*so_texture_path;
	char			*we_texture_path;
	char			*ea_texture_path;
	void			*no_texture;
	void			*so_texture;
	void			*we_texture;
	void			*ea_texture;
}					t_textures;

typedef struct s_game
{
	t_player		player;
	char			**map;
	t_list			*map_list;
	int				map_width;
	int				map_height;
	void			*mlx_ptr;
	t_textures		textures;
	int				floor_color;
	int				ceiling_color;
}					t_game;

void	error(char *message, t_game *game);
t_game	*parsing(int argc, char **argv);
void	get_data(int fd, t_game *game);
int		open_file(char *path);
void	check_file(char *path, char *file_type, t_game *game);
int		is_valid_map(t_game *game);
void	create_map(t_game *game);
int		is_start_pos(char c);
int		is_accesible(char c);
int		is_valid_elem(char c);
void	get_texture(char *pos, char *xpm_path, t_game *game);
#endif