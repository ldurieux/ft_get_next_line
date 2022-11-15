/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:15:44 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/03 16:15:46 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*get_next_line(int fd);

void	*ft_realloc(void *ptr, size_t size, size_t new_size);
char	*ft_strchr(const char *str, int chr);
size_t	ft_strlen(const char *str);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strdup(const char *src);

#endif
