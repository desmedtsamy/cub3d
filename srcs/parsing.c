/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:01:02 by samy              #+#    #+#             */
/*   Updated: 2023/06/27 15:00:35 by samy             ###   ########.fr       */
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

void	print_binary_rgb(int rgb)
{
	int	i;

	i = 0;
	while (i < 24)
	{
		printf("%d", (rgb >> i) & 1);
		i++;
	}
	printf("\n");
}

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		error("Can't open file", NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		error("Can't open file", NULL);
	return (fd);
}

void	print_game(t_game *game)
{
	int	i;

	i = 0;
	printf("NO: %s\n", game->textures.no_texture_path);
	printf("SO: %s\n", game->textures.so_texture_path);
	printf("WE: %s\n", game->textures.we_texture_path);
	printf("EA: %s\n", game->textures.ea_texture_path);
	print_binary_rgb(game->ceiling_color);
	print_binary_rgb(game->floor_color);
	printf("Map width: %d\n", game->map_width);
	printf("Map height: %d\n", game->map_height);
	while (i < game->map_height)
		printf("%s\n", game->map[i++]);
}

static t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		error("Malloc error", NULL);
	game->textures.no_texture = NULL;
	game->textures.so_texture = NULL;
	game->textures.we_texture = NULL;
	game->textures.ea_texture = NULL;
	game->textures.no_texture_path = NULL;
	game->textures.so_texture_path = NULL;
	game->textures.we_texture_path = NULL;
	game->textures.ea_texture_path = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->map = NULL;
	game->map_list = NULL;
	return (game);
}

t_game	*parsing(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		error("Wrong number of arguments", NULL);
	game = init_game();
	check_file(argv[1], ".cub", game);
	get_data(open_file(argv[1]), game);
	create_map(game);
	is_valid_map(game);
	print_game(game);
	return (NULL);
}
