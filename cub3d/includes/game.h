/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 21:55:23 by samy              #+#    #+#             */
/*   Updated: 2023/07/06 17:57:39 by hgeissle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define WIN_W 1280
# define WIN_H 720
# define XPM_SIZE 64
# define FOV 70
# define MOVE_SPEED 0.6
# define CAMERA_SPEED 0.2
# define SLIDE_SPEED 0.6

typedef struct s_game	t_game;

typedef struct s_pos
{
	double			x;
	double			y;
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

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		sl;
	int		endian;
}				t_img;

void	move(t_game *game, int up_or_down);
void	rotate(t_game *game, int left_or_right);
t_rect	*set_rect(t_pos *pos, t_pos *end_pos, t_rect *rect);
t_game	*init_game(t_game *game);
void	minimap(t_game *game);
int		raycasting(t_game *game);
#endif