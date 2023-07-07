/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:44:16 by samy              #+#    #+#             */
/*   Updated: 2023/07/07 11:34:09 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_game	t_game;

typedef struct s_data
{
	char		*line;
	char		*name;
	char		*value;
	char		**split;
	int			nb_elem;
	int			textures;
	int			colors;
	int			map;
}				t_data;

t_game			*parsing(int argc, char **argv, t_game *game);
void			get_data(int fd, t_game *game);
int				open_file(char *path);
void			check_file(char *path, char *file_type, t_game *game);
int				is_valid_map(t_game *game);
void			create_map(t_game *game);
int				is_start_pos(char c);
int				is_accesible(int y, int x, t_game *game);
int				is_valid_elem(int y, int x, t_game *game);
int				set_start_pos(int row, int col, int *start_pos, t_game *game);
#endif