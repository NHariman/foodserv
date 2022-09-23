/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve_minishell_example.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 23:27:59 by nhariman      #+#    #+#                 */
/*   Updated: 2022/08/19 13:08:20 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

/*
** returns several exit, returns 1 if execution failed
** returns 127 if the executable was not found in the $PATH variable.
*/

static int	ft_run_path(char **pathcmd, char **argv)
{
	int	i;

	i = 0;
	while (pathcmd[i] != (char *) 0)
	{
		execve(pathcmd[i], argv, g_shell.env);
		i++;
	}
	ft_printf_err("minishell: %s: command not found\n", argv[0]);
	exit (127);
}

static void	ft_execute_path(char **pathcmd, char **argv)
{
	g_shell.tpid = 0;
	g_shell.child_pid = fork();
	if (g_shell.child_pid < 0)
		error_exit("fork error execute_path.", -1);
	g_shell.child_status = 0;
	if (g_shell.child_pid == 0)
		ft_run_path(pathcmd, argv);
}

static int	ft_execve_path(char *cmd, char **argv)
{
	char	**pathcmd;

	errno = 0;
	g_shell.exit_code = 0;
	pathcmd = ft_path_array(ft_find_envvar("PATH"), cmd);
	if (!pathcmd)
		ft_execute_path(argv, argv);
	else
		ft_execute_path(pathcmd, argv);
	if (pathcmd)
		ft_free_array(pathcmd, ft_arrlen(pathcmd));
	return (0);
}

int	ft_execve(char **argv)
{
	errno = 0;
	g_shell.tpid = 0;
	g_shell.child_pid = fork();
	if (g_shell.child_pid < 0)
		error_exit("fork error ft_execve.", -1);
	if (g_shell.child_pid == 0)
	{
		execve(argv[0], argv, g_shell.env);
		ft_printf_err("minishell: %s: %s\n", argv[0],
			strerror(errno));
		exit (127);
	}
	return (0);
}

void	ft_execute(char *cmd)
{
	g_shell.exit_code = 0;
	signal(SIGINT, handle_exec_signals);
	signal(SIGQUIT, handle_exec_signals);
	if (ft_ispath(cmd))
	{
		if (ft_is_directory(cmd))
			return ;
		else if (cmd[0] == '\0')
			return ;
		ft_execve(g_shell.argv);
	}
	else
		ft_execve_path(cmd, g_shell.argv);
	return ;
}
