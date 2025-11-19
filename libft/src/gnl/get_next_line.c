/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:52:38 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/19 14:02:27 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_join_free(char *temp, char *str)
{
	char	*res;

	res = ft_strjoin(temp, str);
	free(temp);
	return (res);
}

char	*ft_leftover(char *temp)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	res = ft_calloc((ft_strlen(temp) - i + 1), sizeof(char));
	if (!res)
		return (free(temp), NULL);
	j = 0;
	while (temp[i])
		res[j++] = temp[i++];
	free(temp);
	res[j] = '\0';
	return (res);
}

char	*ft_find_line(char *heap)
{
	char	*line;
	size_t	i;

	i = 0;
	while (heap[i] && heap[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (heap[i] && heap[i] != '\n')
	{
		line[i] = heap[i];
		i++;
	}
	if (heap[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	buffer = ft_calloc((BUF_SIZE + 1), sizeof(char));
	if (!buffer)
		return (free(res), NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUF_SIZE);
		if (byte_read < 0)
			return (free(res), free(buffer), NULL);
		buffer[byte_read] = '\0';
		res = ft_join_free(res, buffer);
		if (!res)
			return (free(buffer), NULL);
		if (ft_strchr(res, '\n'))
			break ;
	}
	return (free(buffer), res);
}

char	*get_next_line(int fd)
{
	static char	*heap[FD_MAX];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUF_SIZE < 1)
		return (NULL);
	heap[fd] = ft_read_file(fd, heap[fd]);
	if (!heap[fd])
		return (NULL);
	if (heap[fd][0] == '\0')
	{
		if (heap[fd])
			free(heap[fd]);
		heap[fd] = NULL;
		return (NULL);
	}
	line = ft_find_line(heap[fd]);
	if (!line)
		return (free(heap[fd]), NULL);
	heap[fd] = ft_leftover(heap[fd]);
	if (!heap[fd])
		return (free(line), NULL);
	return (line);
}
