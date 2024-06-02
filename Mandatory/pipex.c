/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 00:31:08 by kahmada           #+#    #+#             */
/*   Updated: 2024/05/25 18:01:41 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **cmd_args, int pipefd[], char *envp[], char *infile)
{
	int		infile_fd;
	char	*full_cmd;

	close(pipefd[0]);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		close (pipefd[1]);
		error();
	}
	if (dup2(infile_fd, 0) == -1)
		error();
	close(infile_fd);
	if (dup2(pipefd[1], 1) == -1)
		error();
	close(pipefd[1]);
	full_cmd = find_commande(cmd_args[0], envp);
	if (!full_cmd)
		error();
	if (execve(full_cmd, cmd_args, envp) == -1)
		error();
	exit (0);
}

void	second_child_process(char **cmd_args, int pipefd[],
			char *envp[], char *outfile)
{
	int		outfile_fd;
	char	*full_cmd;

	close(pipefd[1]);
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		error();
	if (dup2(outfile_fd, 1) == -1)
		error();
	close(outfile_fd);
	if (dup2(pipefd[0], 0) == -1)
		error();
	close(pipefd[0]);
	full_cmd = find_commande(cmd_args[0], envp);
	if (!full_cmd)
		error();
	if (execve(full_cmd, cmd_args, envp) == -1)
		error();
	exit (0);
}

void	setup_and_execute_commands(char *argv[], char *envp[],
			char ***cmd1_args, char ***cmd2_args)
{
	char	*infile;
	char	*outfile;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	split_and_check(argv[2], cmd1_args);
	split_and_check(argv[3], cmd2_args);
	infile = argv[1];
	outfile = argv[4];
	if (pipe(pipefd) == -1)
		error();
	pid1 = fork();
	if (pid1 < 0)
		error();
	else if (pid1 == 0)
		child_process(*cmd1_args, pipefd, envp, infile);
	pid2 = fork();
	if (pid2 < 0)
		error();
	else if (pid2 == 0)
		second_child_process(*cmd2_args, pipefd, envp, outfile);
	close(pipefd[0]);
	close(pipefd[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**cmd1_args;
	char	**cmd2_args;

	if (argc != 5)
		error();
	if (is_whitespace_or_tab(argv[2]) || is_whitespace_or_tab(argv[3])
		|| is_whitespace_or_tab(argv[4]))
		error();
	setup_and_execute_commands(argv, envp, &cmd1_args, &cmd2_args);
	wait(NULL);
	wait(NULL);
	cleanup_2darray(cmd1_args, cmd2_args);
	return (0);
}
