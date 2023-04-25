/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:37:51 by rafilipe          #+#    #+#             */
/*   Updated: 2023/04/25 13:06:30 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	clean_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{	
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

char	*find_path(char **envp, char *cmd)
{
	int		i;
	char	*path;
	char	*temp;
	char	**paths;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	paths = ft_split(path, ':');
	free (path);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		if (access(path, F_OK) != -1)
			return (path);
		free(temp);
		free(path);
		i++;
	}
	clean_matrix(paths);
	return (cmd);
}

void	execute(char *cmd, char **envp)
{
	char	**exec_cmd;
	char	*path;
	int		k;

	exec_cmd = ft_split(cmd, ' ');
	cmd = *exec_cmd;
	path = find_path(envp, cmd);
	if (!path)
	{
		k = 0;
		while (exec_cmd[k])
		{	
			free(exec_cmd[k]);
			k++;
		}
		free(exec_cmd);
		error();
	}
	if (execve(path, exec_cmd, envp) == -1)
		error();
}
