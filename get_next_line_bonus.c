/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaziane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 16:57:20 by zmaziane          #+#    #+#             */
/*   Updated: 2021/12/19 21:52:47 by zmaziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buff, int i, char *backup)
{
	char	*temp;

	while (!ft_strchr(backup) && i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[i] = '\0';
		temp = backup;
		if (!temp)
		{
			temp = malloc(1 * sizeof(char));
			temp[0] = '\0';
		}
		backup = ft_strjoin(temp, buff);
		free(temp);
	}
	free(buff);
	return (backup);
}

char	*ft_get_string(char *backup)
{
	char	*string;
	int		i;

	i = 0;
	if (!backup[i])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\n')
		i++;
	string = malloc((i + 1) * sizeof(char));
	if (!string)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i - 1] != '\n')
	{
		string[i] = backup[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

char	*ft_get_new_backup(char *backup)
{
	char	*new_backup;
	int		i;
	int		index;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	new_backup = malloc((ft_strlen(backup) - i + 1) * sizeof(char));
	if (!new_backup)
		return (NULL);
	i++;
	index = 0;
	while (backup[i])
		new_backup[index++] = backup[i++];
	new_backup[index] = '\0';
	free(backup);
	backup = NULL;
	return (new_backup);
}

char	*get_next_line(int fd)
{
	static char	*backup[65535];
	char		*buff;
	char		*string;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
		i = 1;
		backup[fd] = ft_read(fd, buff, i, backup[fd]);
	if (!backup[fd])
		return (NULL);
	string = ft_get_string(backup[fd]);
	backup[fd] = ft_get_new_backup(backup[fd]);
	return (string);
}
