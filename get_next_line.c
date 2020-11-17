/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:40:31 by sujeon            #+#    #+#             */
/*   Updated: 2020/11/17 17:41:26 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	cnt_len(char *str)
{
	int len;

	len = 0;
	while (*str)
	{
		if (*str == '\n')
			break ;
		str++;
		len++;
	}
	return (len);
}

void		free_line(char *str)
{
	free(str);
	str = NULL;
}

int			get_next_line(int fd, char **line)
{
	static char	*backup;
	char		*src;
	char		*start;
	int 		len;
	int			n;

	if (backup)
	{
		len = cnt_len(backup);
		if (!(start = (char *)malloc(sizeof(char) * len + 1)))
		{
			free_line(start);
			return (-1);
		}
		ft_strlcpy(start, src, len + 1);
	}
	while (1)
	{
		if (!(src = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
		ft_memset(src, '\0', BUFFER_SIZE + 1);
		if ((n = read(fd, src, BUFFER_SIZE)) < 0)
			return (-1);
		printf("after read: %s\n", src);
		len = cnt_len(src);
		if (!(start = (char *)malloc(sizeof(char) * len + 1)))
		{
			free_line(start);
			return (-1);
		}
		ft_strlcpy(start, src, len + 1);
		printf("line: %s\n", start);
		if (ft_strchr(src, '\n'))
		{
			backup = ft_strchr(src, '\n') + 1;
			break ;
		}
		else
			start += BUFFER_SIZE + 1;
	}
	if (!n)
		return (0);
	else
		return (1);
}