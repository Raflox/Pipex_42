/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:40:39 by rafilipe          #+#    #+#             */
/*   Updated: 2023/03/20 12:57:07 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/ft_split.c"
#include "./libft/ft_memset.c"
#include "./libft/ft_bzero.c"
#include "./libft/ft_calloc.c"
#include "./libft/ft_strlen.c"
#include "./libft/ft_substr.c"
#include "./libft/ft_strnstr.c"
#include "./libft/ft_strjoin.c"
#include "./libft/ft_strdup.c"

void error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

char	*find_path(char **envp, char *cmd)
{
	int i;
	char *path;
	char **paths;
	
	i = 0;
	while(!ft_strnstr(envp[i], "PATH", 4))
		i++;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	paths = ft_split(path, ':');
	free (path);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (!access(path, F_OK))
		{
			/* printf("PATH OK --> %s\n", path); */
			return (path);
		}
		free(path);
		i++;
	}
/*	int k = 0;
 	while (path[k++])
	{	
		printf("%s\n", path[k]);
		
	} */
	
	return (NULL);
}

void execute(char *cmd, char **envp)
{
	char **exec_cmd;
	char *path;
	
	exec_cmd = ft_split(cmd, ' ');
	cmd = *exec_cmd;
	printf("%s\n", cmd);
	
	int k = 0;
 	while (exec_cmd[k])
	{	
		printf("EXEC_CMD --> %s\n", exec_cmd[k]);
		k++;
	}
	
	
	if (!(path = find_path(envp, cmd)))
	{
		free(exec_cmd);
		error();
	}
	printf("PATH FOUND\n");
	if (execve(path, exec_cmd, envp) == -1)
		error();
	
	free(cmd);
	free(exec_cmd);
}

void	child_process(char **argv, int *end, char **envp)
{	
	int infile;
	
	infile = open(argv[1], O_RDONLY, 0777);
/*****************************+
********************************/
	close(end[0]);
	dup2(end[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	/* dup2(1, STDOUT_FILENO); */
	execute(argv[2], envp);  
	
	
	//execve(PATH, ARGV, ENVP); // SHOULD FREE PATH
}

void	parent_process(char **argv, int *end, char **envp)
{
		int outfile;
	
	outfile = open(argv[4], O_RDWR | O_CREAT | O_APPEND, 0777);

	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	/* dup2(1, STDOUT_FILENO); */
	execute(argv[3], envp);  
}

int main(int argc, char **argv, char **envp)
{
/* 	int		f1;
	int		f2; */
	int		end[2];
	pid_t	child;
	
	if (argc != 5)
		exit(EXIT_FAILURE);// print ./pipex sintax 
/* 	
	f1 = open(argv[1], O_RDONLY, 0777);
	f2 = open(argv[4], O_RDWR | O_CREAT | O_APPEND, 0777); */
/* 	if (f1 < 0 || f2 < 0)
		error(); */
	if (pipe(end) < 0)
	// end[1] --> you write into this end
	// end[0] --> so it can be read by this end
		error();
	if ((child = fork()) < 0)
		error();
	if (child == 0) // Working on the child process
		child_process(argv, end, envp);
	wait(&child);
	parent_process(argv, end, envp);

	while (1)
		;
/* 	close(f1);
	close(f2); */
	return 0;
}
