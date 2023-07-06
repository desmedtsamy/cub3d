/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 22:53:14 by samy              #+#    #+#             */
/*   Updated: 2023/07/06 23:10:44 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_pos	*set_pos(double x, double y, t_pos *pos)
{
	pos->x = x;
	pos->y = y;
	return (pos);
}

t_rect	*set_rect(t_pos *pos, t_pos *end_pos, t_rect *rect)
{
	rect->pos = pos;
	rect->end_pos = end_pos;
	return (rect);
}

static void	set_start_dir(int row, int col, t_game *game)
{
	if (game->map[row][col] == 'E')
		set_pos(1.0, 0.0, &game->player.dir);
	if (game->map[row][col] == 'N')
		set_pos(0.0, -1.0, &game->player.dir);
	if (game->map[row][col] == 'W')
		set_pos(1.0, 0.0, &game->player.dir);
	if (game->map[row][col] == 'S')
		set_pos(0.0, -1.0, &game->player.dir);
}

static void	set_start_plane(int row, int col, t_game *game)
{
	double	plane_len;
	double	fov_rad;
	double	fov;

	fov = (double)FOV;
	fov_rad = (fov / 180) * M_PI;
	plane_len = tan(fov_rad / 2);
	if (game->map[row][col] == 'E')
		set_pos(0.0, -plane_len, &game->player.plane);
	if (game->map[row][col] == 'N')
		set_pos(plane_len, 0.0, &game->player.plane);
	if (game->map[row][col] == 'W')
		set_pos(0.0, plane_len, &game->player.plane);
	if (game->map[row][col] == 'S')
		set_pos(-plane_len, 0.0, &game->player.plane);
}

int	set_start_pos(int row, int col, int *start_pos, t_game *game)
{
	if (*start_pos)
		return (0);
	*start_pos = 1;
	set_pos(col + 0.5, row + 0.5, &game->player.pos);
	set_pos(col + 0.5, row + 0.5, &game->player.start_pos);
	set_start_dir(row, col, game);
	set_start_plane(row, col, game);
	return (1);
}
