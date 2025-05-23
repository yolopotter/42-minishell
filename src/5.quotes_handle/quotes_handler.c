/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:46:14 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/27 18:26:38 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	find_and_set_next_command(t_token *current)
{
	current = current->next;
	while (current)
	{
		if (current->type == ARG)
		{
			current->type = COMMAND;
			return ;
		}
		current = current->next;
	}
}

static void	delete_token(t_input *input, t_token *current, t_token *previous)
{
	if (current->type == COMMAND)
		find_and_set_next_command(current);
	if (previous)
	{
		current->type = 0;
		previous->next = current->next;
	}
	else
	{
		current->type = 0;
		input->tokens = current->next;
	}
}

bool	is_ambiguous_redirect(t_minishell *mshell,
		t_quotes_helper quotes, t_token *current, char *str)
{
	size_t	i;
	size_t	len;
	char	**env;

	if (current->type != FILE_TOKEN)
		return (0);
	if (quotes.in_double)
		return (0);
	env = mshell->envp->envp;
	len = get_len_explandeble(str);
	i = -1;
	while (env[++i])
	{
		if (expandable_exists(len, env, i, str))
		{
			if (process_expandable(i, current, mshell->envp->envp) == 1)
				return (1);
			else
				return (0);
		}
	}
	if (env[i] == NULL)
		return (current->ambiguous = 1, 1);
	return (0);
}

static void	loop_through_word(t_minishell *mshell,
	t_input *input, t_token *current, t_token *previous)
{
	t_vars	vars;
	size_t	i;

	init_vars(mshell, &vars, current);
	i = 0;
	while (vars.input_str[i])
	{
		update_quote_state(vars.input_str[i], &vars.quotes);
		if (handle_expandables(mshell, &vars, &i, current) == SUCCESS)
			continue ;
		if (there_is_quote_state_change(vars.quotes))
			update_vars_quote(&vars, &i);
		else
			update_vars_append(mshell, &vars, &i);
	}
	if (is_exp_is_empty_is_bare_is_cmd_or_arg(vars, current))
		delete_token(input, current, previous);
	else
		replace_content_of_token(current, vars.new_str);
}

void	expand_remove_quotes(t_minishell *mshell, t_input *input)
{
	t_token	*current;
	t_token	*previous;

	current = input->tokens;
	previous = NULL;
	while (current)
	{
		if (is_any_word(current->type))
			loop_through_word(mshell, input, current, previous);
		if (current->type != 0)
			previous = current;
		current = current->next;
	}
}
