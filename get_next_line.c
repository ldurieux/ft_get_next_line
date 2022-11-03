/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:59:50 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/03 15:59:51 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*next_line(char *buffer)
{
	char	*next;

	next = ft_strchr(buffer, '\n');
	if (next++ == NULL)
		return (free(buffer), NULL);
	return (ft_memmove(buffer, next, ft_strlen(next) + 1));
}

static char	*current_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	i += buffer[i] == '\n';
	line = malloc(sizeof(char) * (i + 1));
	ft_memmove(line, buffer, i);
	line[i] = '\0';
	return (line);
}

static char	*read_file_loop(int fd, char *buffer, size_t cur_size,
							size_t mem_size)
{
	char	*tmp;
	size_t	bytes_read;

	while (1)
	{
		bytes_read = read(fd, buffer + cur_size, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), NULL);
		cur_size += bytes_read;
		buffer[cur_size] = '\0';
		if (ft_strchr(buffer, '\n') || bytes_read == 0)
			break ;
		if (cur_size + BUFFER_SIZE + 1 >= mem_size)
		{
			mem_size *= 2;
			tmp = buffer;
			buffer = ft_realloc(buffer, cur_size, mem_size);
			if (!buffer)
				return (free(tmp), NULL);
		}
	}
	return (buffer);
}

static char	*read_file(int fd, char *res)
{
	char	*buffer;
	size_t	mem_size;
	size_t	cur_size;

	cur_size = 0;
	mem_size = BUFFER_SIZE + 1;
	if (res)
	{
		cur_size = ft_strlen(res);
		mem_size += cur_size;
		buffer = ft_realloc(res, cur_size, mem_size);
	}
	else
		buffer = malloc(sizeof(char) * (mem_size));
	if (!buffer)
		return (NULL);
	return (read_file_loop(fd, buffer, cur_size, mem_size));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	if (!ft_strchr(buffer, '\n'))
	{
		buffer = read_file(fd, buffer);
		if (!buffer || *buffer == '\0')
			return (NULL);
	}
	line = current_line(buffer);
	buffer = next_line(buffer);
	return (line);
}
