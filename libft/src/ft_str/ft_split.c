/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:49:15 by alondot           #+#    #+#             */
/*   Updated: 2022/01/12 14:19:12 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words_count(char const *s, char c)
{
	size_t	nbr;
	int		i;

	nbr = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (i > 0 && s[i] && s[i - 1] == c)
			nbr++;
		if (s[i])
			i++;
	}
	if (nbr == 0 && s[i - 1] == c)
		return (0);
	if (s[0] != c)
		nbr++;
	return (nbr);
}

static char	**ft_alloc(char **strs, char const *s, char c)
{
	size_t	count;
	int		i;
	int		h;

	count = 0;
	i = 0;
	h = 0;
	while (s[h])
	{
		if (s[h] != c)
			count++;
		else if (h > 0 && s[h - 1] != c)
		{
			strs[i] = malloc(sizeof(char) * (count + 1));
			if (!strs[i++])
				return (0);
			count = 0;
		}
		if (s[h + 1] == '\0' && s[h] != c)
		{
			strs[i] = malloc(sizeof(char) * count + 1);
			if (!strs[i])
				return (0);
		}
		h++;
	}
	return (strs);
}

static char	**ft_copy(char **strs, char const *s, char c)
{
	int	i;
	int	j;
	int	h;

	i = 0;
	j = 0;
	h = 0;
	while (s[h])
	{
		if (s[h] != c)
			strs[i][j++] = s[h];
		else if (h > 0 && s[h - 1] != c)
		{
			if (h != 0)
			{
				strs[i][j] = '\0';
				j = 0;
				i++;
			}
		}
		if (s[h + 1] == '\0' && s[h] != c)
			strs[i][j] = '\0';
		h++;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		nbr_w;

	if (!s || !*s)
	{
		tab = malloc(sizeof(char *) * 1);
		if (!tab)
			return (NULL);
		*tab = (void *)0;
		return (tab);
	}
	nbr_w = ft_words_count(s, c);
	tab = malloc(sizeof(char *) * (nbr_w + 1));
	if (!tab)
		return (0);
	if (ft_alloc(tab, s, c) != 0)
		ft_copy(tab, s, c);
	else
	{
		free(tab);
		return (NULL);
	}
	tab[nbr_w] = (void *)0;
	return (tab);
}
