/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:26:03 by kahmada           #+#    #+#             */
/*   Updated: 2024/05/31 06:34:14 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

void	split_and_check(char *arg, char ***cmd_args);
void	error(void);
int		is_whitespace_or_tab(char *str);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	**ft_split(char *str);
char	**ft_split_lib(char const *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*find_commande(char *cmd, char **envp);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	cleanup_2darray(char **cmd_args1, char **cmd_args2);
#endif
