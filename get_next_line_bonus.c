/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:15:22 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/03 16:15:24 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*next_line(char *buffer)
{
	char	*next;

	next = ft_strchr(buffer, '\n');
	if (next++ == NULL)
	{
		free(buffer);
		return (NULL);
	}
	return (ft_memmove(buffer, next, ft_strlen(next) + 1));
}

static char	*current_line(char *buffer)
{
	char	*line;
	size_t	i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_memmove(line, buffer, i);
	line[i] = '\0';
	return (line);
}

static char	*read_file_loop(int fd, char *buffer, size_t cur_size,
							size_t mem_size)
{
	char	*tmp;
	ssize_t	bytes_read;

	while (1)
	{
		bytes_read = read(fd, buffer + cur_size, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		cur_size += (size_t)bytes_read;
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
	static char	*buffer[OPEN_MAX][BUFFER_SIZE + 1];
	char		*tmp_buf;
	char		*line;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 || fd >= OPEN_MAX)
		return (NULL);
	tmp_buf = NULL;
	if (buffer[fd][0])
	{
		tmp_buf = ft_strdup((char *)buffer[fd]);
		if (!tmp_buf)
			return (NULL);
	}
	if (!ft_strchr((char *)buffer[fd], '\n'))
	{
		tmp_buf = read_file(fd, tmp_buf);
		if (!tmp_buf || *tmp_buf == '\0')
			return (free(tmp_buf), NULL);
	}
	line = current_line(tmp_buf);
	tmp_buf = next_line(tmp_buf);
	buffer[fd][0] = 0;
	if (tmp_buf)
		ft_memmove(buffer[fd], tmp_buf, ft_strlen(tmp_buf) + 1);
	return (free(tmp_buf), line);
}
