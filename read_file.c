/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guolivei <guolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:06:33 by guolive           #+#    #+#             */
/*   Updated: 2022/10/14 10:13:06 by guolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include "fdf.h"

t_list	*get_map(char *map_name, t_data *mlx)
{
	int		fd;
	int		j;
	t_list	*tmp;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	mlx->map = get_row(fd, &(mlx->map));
	if (!mlx->map)
		return (NULL);
	tmp = mlx->map;
	j = 0;
	while (tmp)
	{
		j++;
		tmp = tmp->next;
	}
	if (!close(fd))
		return (NULL);
	return (mlx->map);
}

t_list	*get_row(int fd, t_list **list)
{
	char	*line;

	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			ft_bzero(ft_strchr(line, '\n'), 1);
		ft_lstadd_back(list, ft_lstnew(make_row_int(ft_split(line, ' '))));
		free(line);
	}
	return (*list);
}

int	*make_row_int(char **row_str)
{
	int	i;
	int	*row_int;
	int	size;

	size = get_row_size(row_str);
	row_int = (int *)malloc (sizeof (int) * (size + 1));
	if (!row_int)
		return (NULL);
	row_int[size] = INT_MIN;
	i = 0;
	while (row_str[i])
	{
		row_int[i] = ft_atoi(row_str[i]);
		i++;
	}
	free_row(row_str);
	return (row_int);
}

int	get_row_size(char **row_str)
{
	int	size;

	size = 0;
	while (row_str[size])
		size++;
	return (size);
}

void	free_row(char **row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		free(row[i]);
		i++;
	}
	free(row);
}
