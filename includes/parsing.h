/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:44:16 by samy              #+#    #+#             */
/*   Updated: 2023/07/05 14:35:14 by samy             ###   ########.fr       */
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
int				is_accesible(char c);
int				is_valid_elem(char c);
#endif