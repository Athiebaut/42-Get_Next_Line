/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:14:33 by athiebau          #+#    #+#             */
/*   Updated: 2023/05/25 16:14:35 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_save(int fd, char *save)
{
	char	*buffer;
	ssize_t	reads;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	reads = 1;
	while (!ft_strchr(save, '\n') && reads > 0)
	{
		reads = read(fd, buffer, BUFFER_SIZE);
		if (reads == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[reads] = '\0';
		save = ft_strjoin(save, buffer);
	}
	free(buffer);
	return (save);
}

static char	*save_next_line(char *save)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!buffer)
		return (NULL);
	i++;
	while (save[i])
	{
		buffer[j++] = save[i++];
	}
	buffer[j] = '\0';
	free(save);
	return (buffer);
}

static char	*get_the_line(char *save)
{
	int		i;
	char	*buffer;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	buffer = (char *)malloc(i + 2);
	if (!buffer)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		buffer[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		buffer[i] = save[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = read_and_save(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = get_the_line(save[fd]);
	save[fd] = save_next_line(save[fd]);
	return (line);
}
