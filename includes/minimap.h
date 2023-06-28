/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:54:40 by samy              #+#    #+#             */
/*   Updated: 2023/06/28 22:04:03 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# define MINIMAP_SIZE 200
# define MINIMAP_START_POS 20

typedef struct s_game	t_game;

typedef struct s_minimap
{
	t_pos		start_pos;
	int			square_size;
	int			bg_color;
	int			floor_color;
	int			wall_color;
	int			player_color;
}				t_minimap;

void			minimap(t_game *game);
void			draw_minimap(t_game *game);
void			draw_square(t_game *game, t_pos *pos, int size, int color);
#endif