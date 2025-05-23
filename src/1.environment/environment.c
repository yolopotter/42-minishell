/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:53:28 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/25 22:16:15 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	init_env_storage(t_env *env, char **envp)
{
	int	var_amount;

	var_amount = 0;
	while (envp[var_amount])
		var_amount++;
	env->envp = malloc(sizeof(char *) * (var_amount + 1));
	if (!env->envp)
		return (FAIL);
	env->allocated_capacity = var_amount + 1;
	env->len = 0;
	return (SUCCESS);
}

char	*get_env_value(char **envp, const char *key)
{
	size_t	key_len;
	size_t	i;

	key_len = ft_strlen(key);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (envp[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int	match_env_key(const char *env_entry, const char *key)
{
	size_t	key_len;
	int		match;

	key_len = ft_strlen(key);
	match = ft_strncmp(env_entry, key, key_len);
	if (match == 0 && (env_entry[key_len] == '=' || env_entry[key_len] == '\0'))
		return (1);
	else
		return (0);
}

int	realloc_env_capacity(t_env *env)
{
	size_t	new_capacity;
	char	**new_envp;
	size_t	i;

	if (env->len + 1 < env->allocated_capacity)
		return (SUCCESS);
	new_capacity = env->allocated_capacity * 2;
	if (new_capacity == 0)
		new_capacity = 8;
	new_envp = malloc(sizeof(char *) * (new_capacity + 1));
	if (!new_envp)
		return (FAIL);
	i = 0;
	while (i < env->len)
	{
		new_envp[i] = env->envp[i];
		i++;
	}
	free(env->envp);
	env->envp = new_envp;
	env->allocated_capacity = new_capacity;
	return (SUCCESS);
}

int	copy_env(t_env **env, char **envp)
{
	size_t	i;

	*env = malloc(sizeof(t_env));
	if (!*env)
		exit_env("malloc", NULL);
	if (init_env_storage(*env, envp))
		exit_env("malloc", env);
	i = 0;
	while (envp[i])
	{
		(*env)->envp[i] = ft_strdup(envp[i]);
		if (!(*env)->envp[i])
		{
			perror("malloc");
			free_partial_env((*env)->envp, i);
			free(*env);
			exit(FAIL);
		}
		i++;
	}
	(*env)->envp[i] = NULL;
	(*env)->len = i;
	return (SUCCESS);
}
