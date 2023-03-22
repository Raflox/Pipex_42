/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:40:39 by rafilipe          #+#    #+#             */
/*   Updated: 2023/03/20 16:19:33 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, int *end, char **envp)
{	
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile < 0)
		error();
	close(end[0]);
	dup2(end[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	execute(argv[2], envp);
}

void	parent_process(char **argv, int *end, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
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
	pid_t	child;

	if (argc != 5)
		exit(EXIT_FAILURE);// TODO: print ./pipex sintax 
	if (pipe(end) < 0)
		error();
	child = fork();
	if (child < 0)
		error();
	if (child == 0)
		child_process(argv, end, envp);
	wait(&child);
	parent_process(argv, end, envp);
	return (0);
}
