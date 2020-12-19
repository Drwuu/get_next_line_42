/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drwuu <drwuu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 19:01:43 by drwuu             #+#    #+#             */
/*   Updated: 2020/12/19 18:12:07 by drwuu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h" //to remove

int		find_newline(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		read_line(char **str, int fd)
{
	int		head;
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

	while ((head = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[head] = '\0';
		if (!*str)
		{
			*str = ft_strdup(buf);
		}
		else
		{
			tmp = ft_strjoin(*str, buf);
			free(*str);
			*str = tmp;
		}
		if (find_newline(*str) >= 0)
			break ;
	}
	if(!*str)
	{
		printf("bulma\n");
		*str = "\0";
		return (-1);
	}
	return (1);
}

int		build_line(char **str, char **line)
{
	int		i;
	char	*tmp;

	i = find_newline(*str);
	if (i >= 0)
	{
		*line = ft_substr(*str, 0, i);
		tmp = ft_strdup(&(*str)[i + 1]);
		free(*str);
		*str = tmp;
		return (1);
	}
	else
	{
		*line = ft_substr(*str, 0, ft_strlen(*str));
		free(*str);
		*str = NULL;
		return (0);
	}
}

int		get_next_line(const int fd, char **line)
{
	static char	*str[7777];
	
	if (!line || fd < 0 || (read(fd, str[fd], 0) < 0))
		return (-1);
	if (read_line(&str[fd], fd))
		return (build_line(&str[fd], line));
	else
		return (-1);
}
