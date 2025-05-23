/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:44:21 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/27 14:06:25 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	sig_action_ignore(t_minishell *mshell)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit_cleanup_error(mshell, "signal");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit_cleanup_error(mshell, "signal");
	return (SUCCESS);
}

bool	sig_action_main(t_minishell *mshell)
{
	g_signal = 0;
	if (signal(SIGINT, sigint_handler_main) == SIG_ERR)
		exit_cleanup_error(mshell, "signal");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit_cleanup_error(mshell, "signal");
	return (SUCCESS);
}

bool	sig_action_heredoc(t_minishell *mshell)
{
	g_signal = 0;
	if (signal(SIGINT, sigint_handler_heredoc) == SIG_ERR)
		exit_cleanup_error(mshell, "signal");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit_cleanup_error(mshell, "signal");
	return (SUCCESS);
}

bool	sig_action_parent(t_minishell *mshell)
{
	if (signal(SIGINT, sigint_handler_parent) == SIG_ERR)
		exit_cleanup_error(mshell, "signal");
	if (signal(SIGQUIT, sigint_handler_parent) == SIG_ERR)
		exit_cleanup_error(mshell, "signal");
	return (SUCCESS);
}

bool	sig_action_default(t_minishell *mshell)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit_cleanup_error(mshell, "signal");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit_cleanup_error(mshell, "signal");
	return (SUCCESS);
}
