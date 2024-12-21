/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdinc <mdinc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:58:07 by mdinc             #+#    #+#             */
/*   Updated: 2024/12/21 20:58:09 by mdinc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1907
# endif

char	*get_next_line(int fd);

size_t	ft_strlen(char *s);
int		ft_count_newline(char *remainder);
char	*ft_check_newline(char *s);
char	*ft_strjoin(char *remainder, char *temp);
char	*ft_get_new_remainder(char *remainder);
char	*ft_get_line(char *remainder);
char	*ft_get_remainder(int fd, char *remainder);
char	*ft_strchr(const char *s, int c);

#endif