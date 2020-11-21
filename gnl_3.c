/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:45:44 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/20 23:31:32 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		find_n(char *backup)
{
	int len;

	len = 0;
	while (backup[len])
	{
		if (backup[len] == '\n')
			return (len);
		len++;
	}
	return (0);
}

static int		put_value(char **line, char **backup)
{
	int len;

	len = find_n(*backup);
	if (!(*line = ft_substr(*backup, 0, len)))
	{
		/*free(*backup);
		*backup = NULL;*/
		return (-1);
	}
	len++;
	while (len-- && **backup)
		(*backup)++;
	/*if (!(**backup))
	{
		free(*backup);
		*backup = NULL;
	}*/
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char	*backup[1024];
	char		src[BUFFER_SIZE + 1];
	int			n;

	while ((n = read(fd, src, BUFFER_SIZE)) > 0)
	{
		src[n] = '\0';
		if (!(backup[fd] = ft_strjoin(backup[fd], src)))
		{
			free(backup[fd]);
			backup[fd] = NULL;
			return (-1);
		}
		if (find_n(backup[fd]))
			return (put_value(line, &backup[fd]));
	}
	return (put_value(line, &backup[fd]));
}