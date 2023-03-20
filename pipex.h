/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafilipe <rafilipe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:48:43 by rafilipe          #+#    #+#             */
/*   Updated: 2023/03/20 13:01:24 by rafilipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

void    pipex(int f1, int f2, char *cmd1, char *cmd2, char **envp);
void	child_process(char **argv, int *end, char **envp);


// Check if FD's are closed --> lsof -c a.out --> infinite loop in main()
#endif