/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:16:51 by cade-oli          #+#    #+#             */
/*   Updated: 2025/02/11 22:26:27 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *b)
{
	char	*block;
	int		bytes;

	block = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!block)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, block, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(block);
			return (NULL);
		}
		block[bytes] = '\0';
		b = ft_strjoin(b, block);
		if (ft_strchr(block, '\n'))
			break ;
	}
	free(block);
	return (b);
}

char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1 + (buffer[i] == '\n')));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	line = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffers[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffers[fd] = read_file(fd, buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	line = get_line(buffers[fd]);
	buffers[fd] = update_line(buffers[fd]);
	return (line);
}
