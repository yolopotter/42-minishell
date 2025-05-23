/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:45:46 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/27 14:06:49 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_eof(char *eof, char *input)
{
	return (!(ft_strncmp(eof, input, ft_strlen(eof))
			|| (ft_strlen(input) != ft_strlen(eof))));
}

int	is_valid_char_expansion(char c)
{
	return (ft_isalnum(c) || c == '_');
}

void	close_fds(int *fd1, int *fd2)
{
	if (fd1 && *fd1 != -1)
	{
		if (close(*fd1) == -1)
			perror("close");
		*fd1 = -1;
	}
	if (fd1 && *fd2 != -1)
	{
		if (close(*fd2) == -1)
			perror("close");
		*fd2 = -1;
	}
}

void	free_and_set(char **input)
{
	free(*input);
	*input = NULL;
}

int	get_stdin(t_minishell *mshell)
{
	int		fd_stdin;

	fd_stdin = dup(STDIN_FILENO);
	if (fd_stdin == -1)
		exit_cleanup_error(mshell, "dup");
	return (fd_stdin);
}
