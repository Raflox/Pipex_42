/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:48:43 by rafilipe          #+#    #+#             */
/*   Updated: 2023/04/25 13:07:56 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

// MAIN
void	child_process(char **argv, int *end, char **envp);
void	parent_process(char **argv, int *end, char **envp);

// UTILS
void	error(void);
char	*find_path(char **envp, char *cmd);
void	execute(char *cmd, char **envp);
void	clean_matrix(char **matrix);

#endif