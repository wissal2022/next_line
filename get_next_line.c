/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabourah <wabourah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:42:48 by wabourah          #+#    #+#             */
/*   Updated: 2024/12/30 18:43:38 by wabourah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(int fd, char *buffer, char *read_lines)
{
	ssize_t	read_file;
	char	*tmp;

	read_file = 1;
	while (read_file > 0)
	{
		read_file = read(fd, buffer, BUFFER_SIZE);
		if (read_file == 0)
			break ;
		else if (read_file == -1)
		{
			free(read_lines);
			return (NULL);
		}
		buffer[read_file] = '\0';
		if (!read_lines)
			read_lines = ft_strdup("");
		tmp = read_lines;
		read_lines = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (read_lines);
}

static char	*file_line(char *line)
{
	int		i;
	char	*read_lines;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	read_lines = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	if (*read_lines == 0)
	{
		free(read_lines);
		read_lines = NULL;
	}
	line [i + 1] = '\0';
	return (read_lines);
}

char	*get_next_line(int fd)
{
	static char	*read_lines;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(read_lines);
		read_lines = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = get_line(fd, buffer, read_lines);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	read_lines = file_line(line);
	return (line);
}
