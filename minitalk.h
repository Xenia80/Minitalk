/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnona <pnona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:43:52 by pnona             #+#    #+#             */
/*   Updated: 2022/03/13 19:47:18 by pnona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF 1024

struct	s_message
{
	int		char_num;
	int		bit_num;
	char	*str;
	int		flag;
};

typedef struct s_message	t_message;

#endif