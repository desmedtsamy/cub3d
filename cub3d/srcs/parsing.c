/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:01:02 by samy              #+#    #+#             */
/*   Updated: 2023/07/10 00:59:06 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_file(char *path, char *file_type, t_game *game)
{
	if (ft_strrncmp(path, file_type, ft_strlen(file_type)))
	{
		write(2, "Error\n", 6);
		write(2, path, ft_strlen(path));
		write(2, " should be a ", 13);
		write(2, file_type, ft_strlen(file_type));
		write(2, "\n", 1);
		error(NULL, game);
	}
}

static int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		error("can't open file", NULL);
	return (fd);
}

t_game	*parsing(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		error("Wrong number of arguments", NULL);
	init_game(game);
	check_file(argv[1], ".cub", game);
	game->fd = open_file(argv[1]);
	get_data(game);
	close(game->fd);
	create_map(game);
	is_valid_map(game);
	return (game);
}
