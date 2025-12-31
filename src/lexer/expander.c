/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:59:02 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 19:53:10 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

static size_t	expand_parse(t_token *tok, t_vec *tmp, size_t i, t_tree *tree);
static size_t	expand_len(t_token *tok, size_t i);
static int		expand_env_var(t_vec *tmp, t_tree *tree);

void	expandise(t_token *tok, t_tree *tree)
{
	char	*src;
	t_vec	*tmp;
	size_t	i;

	if (!tok || !tok->tok_chars || tok->tok_chars->len == 0)
		return ;
	tmp = NULL;
	i = 0;
	if (!vec_alloc(&tmp, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	while (i + 1 < tok->tok_chars->len)
	{
		src = (char *)tok->tok_chars->data;
		if (src[i] == '$' && (ft_isalpha(src[i + 1]) || src[i + 1] == '_'))
		{
			i += expand_parse(tok, tmp, i, tree);
			vec_reset(tmp);
		}
		else
			i++;
	}
}

static size_t	expand_parse(t_token *tok, t_vec *tmp, size_t i, t_tree *tree)
{
	size_t	len;
	char	null;

	len = expand_len(tok, i);
	null = '\0';
	if (len == 0)
	{
		if (!vec_trim(tok->tok_chars, i, 1))
			exit_parser(tree, MSG_MALLOCF);
		return (0);
	}
	if (!vec_from(tmp, vec_get(tok->tok_chars, i + 1), len, sizeof(char))
		|| !vec_push(tmp, &null)
		|| !vec_trim(tok->tok_chars, i, len + 1))
		exit_parser(tree, MSG_MALLOCF);
	if (!expand_env_var(tmp, tree))
		return (0);
	if (!vec_inpend(tok->tok_chars, tmp, i))
		exit_parser(tree, MSG_MALLOCF);
	return (tmp->len);
}

static size_t	expand_len(t_token *tok, size_t i)
{
	char	*str;
	size_t	str_len;
	size_t	len;

	str = (char *)tok->tok_chars->data;
	str_len = tok->tok_chars->len;
	len = 1;
	if (i + len < str_len
		&& (ft_isalpha(str[i + len]) || str[i + len] == '_'))
		len++;
	while (i + len < str_len && ft_isalnum(str[i + len]))
		len++;
	return (len - 1);
}

static int	expand_env_var(t_vec *tmp, t_tree *tree)
{
	const char	*env_var;

	env_var = getenv((char *)tmp->data);
	if (!env_var || ft_strlen(env_var) == 0)
		return (FAIL);
	if (ft_isambiguous(env_var))
		ft_putendl_fd(MSG_AMBIGUO, 2);
	vec_reset(tmp);
	if (!vec_from(tmp, (void *)env_var, ft_strlen(env_var), sizeof(char)))
		exit_parser(tree, MSG_MALLOCF);
	return (SUCCESS);
}
