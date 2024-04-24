/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:21:30 by daortega          #+#    #+#             */
/*   Updated: 2023/12/13 19:21:39 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char static	*get_linee(char *buff)
{
	char	*line;
	int		pos;
	int		i;

	pos = 0;
	i = 0;
	if (buff[0] == '\0')
		return (NULL);
	while (buff[pos] != '\n' && buff[pos] != '\0')
		pos++;
	if (buff[pos] == '\n')
		pos++;
	line = malloc((pos + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	while (buff[i] != '\0' && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char static	*cleanbuff(char *buff, int linelength)
{
	int		i;
	char	*newbuff;

	i = 0;
	newbuff = malloc((ft_gnl_strlen(buff) - linelength + 1) * sizeof(char));
	if (newbuff == NULL)
	{
		free(buff);
		return (NULL);
	}
	while (buff[linelength] != '\0')
		newbuff[i++] = buff[linelength++];
	newbuff[i] = '\0';
	free(buff);
	return (newbuff);
}

char static	*read_line(int fd, char *buff)
{
	char	*str;
	int		cread;

	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (str == NULL)
		return (free(buff), NULL);
	cread = 1;
	while ((ft_gnl_strchr(buff, '\n') == 0) && cread != 0)
	{
		cread = read(fd, str, BUFFER_SIZE);
		if (cread == -1)
			return (free(str), free(buff), NULL);
		if (cread != 0)
		{
			str[cread] = '\0';
			if (buff == NULL)
				buff = ft_gnl_strdup(str);
			else
				buff = ft_gnl_strjoin(buff, str);
		}
	}
	free(str);
	return (buff);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buff = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = read_line(fd, buff);
	if (buff == NULL)
		return (NULL);
	line = get_linee(buff);
	if (line == NULL)
	{
		free(buff);
		buff = NULL;
	}
	else
		buff = cleanbuff(buff, ft_gnl_strlen(line));
	return (line);
}
