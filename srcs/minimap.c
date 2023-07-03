/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:51:23 by samy              #+#    #+#             */
/*   Updated: 2023/07/03 13:27:22 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_cell(t_pos *pos, t_pos *test, char cell, t_game *game)
{
	t_rect		rect;
	t_minimap	*mini;
	t_pos		pos_max;

	set_pos((MINI_X + MINI_START), (MINI_Y + MINI_START), &pos_max);
	mini = &game->minimap;
	set_rect(pos, test, &rect);
	if (cell == '1')
		draw_rect(&rect, &pos_max, mini->wall_color, game);
	else if (is_accesible(cell))
		draw_rect(&rect, &pos_max, mini->floor_color, game);
}

void	print_map(float x, float y, t_pos *ofset, t_game *g)
{
	t_pos	pos;
	t_pos	size;
	int		i;
	int		j;

	pos.y = MINI_START;
	i = -1;
	while (++i + y < g->map_height && pos.y < (MINI_Y + MINI_START))
	{
		pos.x = MINI_START;
		j = -1;
		while (++j + x < g->map_width && pos.x < (MINI_X + MINI_START))
		{
			size.y = MINI_SQUARE_SIZE;
			size.x = MINI_SQUARE_SIZE;
			if (j == 0)
				size.x = MINI_SQUARE_SIZE - ofset->x;
			if (i == 0)
				size.y = MINI_SQUARE_SIZE - ofset->y;
			if (j + x >= 0 && i + y >= 0)
				print_cell(&pos, &size, g->map[(int)(i + y)][(int)(j + x)], g);
			pos.x += size.x;
		}
		pos.y += size.y;
	}
}

static void	print_pos(t_game *game)
{
	t_pos	pos;
	t_pos	size;
	char	*pos_x;
	char	*pos_y;
	t_rect	rect;

	set_pos(MINI_START, MINI_START + MINI_Y, &pos);
	set_pos(40, 15, &size);
	pos_x = ft_itoa(game->player.pos.x);
	pos_y = ft_itoa(game->player.pos.y);
	draw_rect(set_rect(&pos, &size, &rect), NULL, game->minimap.bg_color, game);
	pos.x += 5;
	pos.y += 10;
	mlx_string_put(game->mlx, game->window, pos.x, pos.y, 0xccccff, pos_x);
	pos.x += 20;
	mlx_string_put(game->mlx, game->window, pos.x, pos.y, 0xccccff, pos_y);
	free(pos_x);
	free(pos_y);
}

// Rotation d'un point autour d'un point central
void rotate_point(t_pos *point, const t_pos *center, float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    // Translater le point par rapport au centre
    point->x -= center->x;
    point->y -= center->y;

    // Effectuer la rotation
    float new_x = point->x * c - point->y * s;
    float new_y = point->x * s + point->y * c;

    // Re-translater le point vers sa position d'origine
    point->x = new_x + center->x;
    point->y = new_y + center->y;
}

// Vérifier si un point est à l'intérieur d'un triangle en utilisant la méthode du barycentre
int point_in_triangle(const t_pos *point, const t_pos *p1, const t_pos *p2, const t_pos *p3)
{
    float alpha = ((p2->y - p3->y) * (point->x - p3->x) + (p3->x - p2->x) * (point->y - p3->y)) /
                  ((p2->y - p3->y) * (p1->x - p3->x) + (p3->x - p2->x) * (p1->y - p3->y));
    float beta = ((p3->y - p1->y) * (point->x - p3->x) + (p1->x - p3->x) * (point->y - p3->y)) /
                 ((p2->y - p3->y) * (p1->x - p3->x) + (p3->x - p2->x) * (p1->y - p3->y));
    float gamma = 1.0f - alpha - beta;

    // Le point est à l'intérieur du triangle si tous les coefficients alpha, beta, gamma sont positifs
    return alpha >= 0 && beta >= 0 && gamma >= 0;
}
// Dessiner un triangle plein à l'aide de trois points
void fill_triangle(const t_pos *p1, const t_pos *p2, const t_pos *p3, int color, t_game *game)
{
    t_pos min_pos = {
        fminf(p1->x, fminf(p2->x, p3->x)),
        fminf(p1->y, fminf(p2->y, p3->y))
    };
    t_pos max_pos = {
        fmaxf(p1->x, fmaxf(p2->x, p3->x)),
        fmaxf(p1->y, fmaxf(p2->y, p3->y))
    };

    // Parcourir chaque pixel à l'intérieur du rectangle englobant le triangle
    for (int y = min_pos.y; y <= max_pos.y; y++)
    {
        for (int x = min_pos.x; x <= max_pos.x; x++)
        {
            t_pos current_pos = {x, y};

            // Vérifier si le pixel est à l'intérieur du triangle
            if (point_in_triangle(&current_pos, p1, p2, p3))
            {
                // Dessiner le pixel
                mlx_pixel_put(game->mlx, game->window, x, y, color);
            }
        }
    }
}

void draw_player(t_pos *pos, float angle, t_game *game)
{
    t_minimap *mini;
	float	radian;

	mini = &game->minimap;
	radian = angle * M_PI / 180;
    // Définir les coins du triangle
    t_pos p1 = {pos->x, pos->y - 7};
    t_pos p2 = {pos->x - 7, pos->y + 7};
    t_pos p3 = {pos->x + 7, pos->y + 7};

    // Rotation du triangle autour du point central (pos)
    rotate_point(&p1, pos, radian);
    rotate_point(&p2, pos, radian);
    rotate_point(&p3, pos, radian);

    // Dessiner le triangle plein
    fill_triangle(pos, &p1, &p2, mini->player_color, game);
    fill_triangle(pos, &p2, &p3, mini->player_color, game);
    fill_triangle(pos, &p3, &p1, mini->player_color, game);
}

void	draw_minimap(t_pos *start, t_pos *size, t_pos *pos_max, t_game *g)
{
	t_pos	pos;
	t_pos	ofset;
	float	x;
	float	y;
	t_rect	rect;

	x = g->player.pos.x - ((MINI_X / MINI_SQUARE_SIZE) / 2);
	y = g->player.pos.y - ((MINI_Y / MINI_SQUARE_SIZE) / 2);
	set_pos((g->player.pos.x - (int)g->player.pos.x) * MINI_SQUARE_SIZE,
		(g->player.pos.y - (int)g->player.pos.y) * MINI_SQUARE_SIZE, &ofset);
	draw_rect(set_rect(start, size, &rect), pos_max, g->minimap.bg_color, g);
	print_map(x, y, &ofset, g);
	set_pos((MINI_X / 2) + MINI_START - MINI_SQUARE_SIZE / 2, (MINI_Y / 2) + MINI_START - MINI_SQUARE_SIZE / 2, &pos);
	//draw_rect(set_rect(&pos, NULL, &rect), pos_max, g->minimap.player_color, g);
	draw_player(&pos, g->player.orientation, g);
	pos.x += MINI_START / 2;
	pos.y += MINI_START / 2;
	print_pos(g);
}

void	minimap(t_game *game)
{
	t_pos	size;
	t_pos	start;
	t_pos	pos_max;

	set_pos(MINI_START, MINI_START, &start);
	set_pos(MINI_X, MINI_Y, &size);
	set_pos((MINI_X + MINI_START), (MINI_Y + MINI_START), &pos_max);
	draw_minimap(&start, &size, &pos_max, game);
}
