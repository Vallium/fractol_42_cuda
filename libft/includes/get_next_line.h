/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 12:44:13 by aalliot           #+#    #+#             */
/*   Updated: 2014/12/10 10:37:34 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFF_SIZE 1000

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

int			get_next_line(int fd, char **line);

#endif
