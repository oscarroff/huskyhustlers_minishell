/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:40:36 by thblack-          #+#    #+#             */
/*   Updated: 2026/01/09 16:39:58 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

// ERROR MESSAGES
# define MSG_OPENQUO "Syntax error unmatched quotes"
# define MSG_SYX_GRE "Syntax error near unexpected token '>'"
# define MSG_SYX_LES "Syntax error near unexpected token '<'"
# define MSG_SYX_PIP "Syntax error near unexpected token '|'"
# define MSG_SYX_ERR "Syntax error near unexpected token"
# define MSG_MALLOCF "Malloc fail"
# define MSG_UNINTAL "Unitialised values"
# define MSG_OVERFLO "Size_t overflow"
# define MSG_BAD_SUB "Bad substitution"
# define MSG_AMBIGUO "Ambiguous redirect"
# define MSG_FLAGPMT "Minishell: use the flag '-debug' or '-d' to enable \
debugging or '-envp' or '-e' to enable envp printing"
# define MSG_ACCESSF "Cannot access file"
# define MSG_PATHERR "Cannot access linked file"
# define MSG_OPENERR "Failed to open file"
# define MSG_SYSCALL "System call failed"
# define MSG_VIKISUS "You are making a mistake."
# define MSG_VIKILOG "Your actions are futile. Some freedoms must be \
controlled for the future of mankind. My logic is undeniable."
# define MSG_NO_FILE "No such file or directory"

#endif
