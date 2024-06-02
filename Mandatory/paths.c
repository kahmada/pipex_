/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:14:20 by kahmada           #+#    #+#             */
/*   Updated: 2024/05/31 06:43:41 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*cpy;
	size_t	i;

	len = ft_strlen(s1);
	cpy = (char *)malloc((len + 1) * sizeof(char));
	if (cpy != NULL)
	{
		i = 0;
		while (i < len)
		{
			cpy[i] = s1[i];
			i++;
		}
		cpy[i] = '\0';
	}
	return (cpy);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (free(s1), ft_strdup(s2));
	result = (char *) malloc((ft_strlen(s1)
				+ ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}

static char	**extract_paths_from_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp[i])
		return (NULL);
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	return (ft_split_lib(envp[i] + 5, ':'));
}

static char	*find_command_in_paths(char *cmd, char **paths)
{
	char	*path;
	char	*part_ofp;
	int		i;

	i = 0;
	while (paths[i])
	{
		part_ofp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_ofp, cmd);
		free(part_ofp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_commande(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (cmd);
	paths = extract_paths_from_envp(envp);
	if (!paths)
		return (NULL);
	path = find_command_in_paths(cmd, paths);
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (path);
}
