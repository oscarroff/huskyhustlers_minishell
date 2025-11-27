/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:40:36 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/24 20:44:51 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

// ERROR MESSAGES
# define MSG_OPENQUO "syntax error unmatched quotes"
# define MSG_SYX_GRE "syntax error near unexpected token '>'"
# define MSG_SYX_LES "syntax error near unexpected token '<'"
# define MSG_SYX_PIP "syntax error near unexpected token '|'"
# define MSG_SYX_ERR "syntax error near unexpected token"
# define MSG_MALLOCF "malloc fail"
# define MSG_UNINTAL "unitialised values"
# define MSG_OVERFLO "size_t overflow"
# define MSG_BAD_SUB "bad substitution"
# define MSG_AMBIGUO "ambiguous redirect"
# define MSG_FLAGPMT "minishell: use the flag '-debug' or '-d' to enable \
	debugging or '-envp' or '-e' to enable envp printing"
# define MSG_ACCESSF "cannot access file"
# define MSG_PATHERR "cannot access linked file"
# define MSG_OPENERR "failed to open file"

#endif
