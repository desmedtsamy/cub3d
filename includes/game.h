/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samy <samy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 21:55:23 by samy              #+#    #+#             */
/*   Updated: 2023/07/02 00:37:50 by samy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define WIN_W 1280
# define WIN_H 720
# define XPM_SIZE 64

typedef struct s_game	t_game;

typedef struct s_pos
{
	float				x;
	float				y;
}						t_pos;

typedef struct s_move
{
	int					forward;
	int					backward;
	int					left;
	int					right;
}						t_move;

typedef struct s_rect
{
	t_pos				*pos;
	t_pos				*end_pos;
	t_pos				*max;
}						t_rect;

void	move(float pos_x, float pos_y, t_game *game);
t_rect	*set_rect(t_pos *pos, t_pos *end_pos, t_rect *rect);
t_game	*init_game(void);
void	minimap(t_game *game);
#endif