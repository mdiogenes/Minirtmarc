/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_grammar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irifarac <irifarac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:43:00 by irifarac          #+#    #+#             */
/*   Updated: 2023/05/03 09:47:42 by irifarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_check_ident(char *str)
{
	while (str && ft_strchr("\t ", *str))
		str++;
	if (ft_strchr("ACL\n", *str))
		return (0);
	else if (!ft_strncmp("pl ", str, 3) || !ft_strncmp("pl\t", str, 3))
		return (0);
	else if (!ft_strncmp("sp ", str, 3) || !ft_strncmp("sp\t", str, 3))
		return (0);
	else if (!ft_strncmp("cy ", str, 3) || !ft_strncmp("cy\t", str, 3))
		return (0);
	else if (!ft_strncmp("di ", str, 3) || !ft_strncmp("di\t", str, 3))
		return (0);
	else
		return (ft_error("No valid identifier", -1));
	return (0);
}

static int	ft_repeat(char c)
{
	static int	bin_hash[256] = {0};
	int			temp;

	temp = (int)c;
	if (bin_hash[temp] == 0)
		bin_hash[temp] = 1;
	else
		return (ft_error("Wrong identifier", -1));
	return (0);
}

static int	ft_check_param(char *str)
{
	while (str && ft_strchr("\t ", *str))
		str++;
	if (*str == 'A')
		return (ft_repeat(*str));
	else if (*str == 'C')
		return (ft_repeat(*str));
	else if (*str == 'L')
		return (0);
	else if (*str == 'p' && *(str + 1) == 'l')
		return (0);
	else if (*str == 's' && *(str + 1) == 'p')
		return (0);
	else if (*str == 'c' && *(str + 1) == 'y')
		return (0);
	else if (*str == 'd' && *(str + 1) == 'i')
		return (0);
	else if (*str == 10)
		return (0);
	return (-1);
}

static int	ft_check_line(char *str)
{
	if (ft_check_ident(str) < 0)
		return (-1);
	if (ft_check_param(str) < 0)
		return (-1);
	return (0);
}

int	ft_check_grammar(int fd)
{
	char	*line;
	char	*tmp;

	line = ft_get_next_line(fd);
	if (line == NULL)
		return (ft_error("Empty file", -1));
	while (line != NULL)
	{
		if (ft_check_line(line) < 0)
		{
			free(line);
			return (-1);
		}
		tmp = line;
		free(tmp);
		line = ft_get_next_line(fd);
	}
	close(fd);
	return (0);
}
