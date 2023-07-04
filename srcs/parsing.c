/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:01:02 by samy              #+#    #+#             */
/*   Updated: 2023/07/04 15:32:23 by sde-smed         ###   ########.fr       */
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

int	open_file(char *path)
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
	get_data(open_file(argv[1]), game);
	create_map(game);
	is_valid_map(game);
	return (game);
}
