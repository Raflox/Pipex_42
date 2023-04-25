/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:40:39 by rafilipe          #+#    #+#             */
/*   Updated: 2023/04/25 14:13:19 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_process(char **argv, int *end, char **envp)
{	
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error();
	close(end[0]);
	dup2(infile, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	execute(argv[2], envp);
}

void	child2_process(char **argv, int *end, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		error();
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		end[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (argc != 5)
	{
		write(1, "Error!\nSyntax should be: ./pipex file1 \"cmd1\" \"cmd2\" file2\n", 59);
		exit(EXIT_FAILURE);
	}
	if (pipe(end) < 0)
		error();
	child1 = fork();
	if (child1 < 0)
		error();
	if (child1 == 0)
		child1_process(argv, end, envp);
	child2 = fork();
	if (child2 < 0)
		error();
	if (child2 == 0)
		child2_process(argv, end, envp);
	waitpid(-1, &status, 0);
	return (0);
}
