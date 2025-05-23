/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:19:03 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/25 22:36:54 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_env		t_env;
typedef struct s_ast		t_ast;
typedef struct s_minishell	t_minishell;

int		is_valid_identifier_range(const char *str, size_t len);
int		count_argv(char **argv);
int		update_var_env(t_env *env, const char *arg, const char *key,
			int key_has_value);
int		add_var_to_env(t_env *env, const char *arg);
int		ft_env(t_env **my_env, char **argv);
int		ft_pwd(void);
int		get_current_directory(char *buffer, size_t size);
int		ft_cd(t_env **my_env, int argv_count, char **argv);
int		ft_echo(int argc, char **argv);
void	ft_exit(char **argv, t_minishell *minishell);
int		ft_unset(char **args, t_env *env);
int		ft_export(char **args, t_minishell *mshell);

#endif
