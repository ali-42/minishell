/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:10:49 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/03 19:19:37 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_file
{
	int				type;
	char			*name;
	struct s_file	*next;
	struct s_file	*prev;
}	t_file;

typedef struct s_cmd
{
	char			**args;
	int				input;
	int				output;
	int				pipe_input;
	int				pipe_output;
	int				redir_error;
	struct s_file	*infile;
	struct s_file	*outfile;
	pid_t			pid;
	pid_t			parent;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

#endif
