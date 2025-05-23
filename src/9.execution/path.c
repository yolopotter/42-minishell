/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:38:20 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/25 20:38:22 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_cmd_full_path(t_minishell *mshell, char **path, char *cmd);
static char	*build_cmd_path(t_minishell *mshell, char *dir, char *cmd);
static void	split_env_path_value(t_minishell *mshell);

char	*get_command_path(t_minishell *mshell, t_ast *ast)
{
	char	*full_path;

	full_path = NULL;
	if (!ast || !ast->cmd || !ast->cmd[0])
		exit_cleanup_error(mshell, "command");
	split_env_path_value(mshell);
	if (!ft_strchr(ast->cmd[0], '/') && mshell->path && *mshell->path)
	{
		full_path = get_cmd_full_path(mshell, mshell->path, ast->cmd[0]);
		if (!full_path)
		{
			ft_dprintf(2, "Giraffeshell: %s: command not found\n", ast->cmd[0]);
			delete_minishell(mshell);
			exit(127);
		}
	}
	else
	{
		full_path = ft_strdup(ast->cmd[0]);
		if (!full_path)
			exit_cleanup_error(mshell, "malloc");
	}
	return (full_path);
}

static void	split_env_path_value(t_minishell *mshell)
{
	char	*env_path_value;

	env_path_value = get_env_value(mshell->envp->envp, "PATH");
	if (env_path_value && *env_path_value)
	{
		mshell->path = ft_split(env_path_value, ':');
		if (!mshell->path)
			exit_cleanup_error(mshell, "malloc");
	}
}

static char	*get_cmd_full_path(t_minishell *mshell, char **path, char *cmd)
{
	int		i;
	char	*full_path;

	if (*cmd == '\0')
		return (NULL);
	i = 0;
	while (path && path[i])
	{
		full_path = build_cmd_path(mshell, path[i], cmd);
		if (!full_path)
			exit_cleanup_error(mshell, "malloc");
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*build_cmd_path(t_minishell *mshell, char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (temp == NULL)
		exit_cleanup_error(mshell, "malloc");
	full_path = ft_strjoin(temp, cmd);
	if (full_path == NULL)
	{
		free(temp);
		exit_cleanup_error(mshell, "malloc");
	}
	free(temp);
	return (full_path);
}
