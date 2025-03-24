/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:14:53 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/20 16:26:17 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "../parser/parser.h"
# include "../lexer/lexer.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

extern int	g_exit_code;

typedef struct s_executer
{
	t_ast_node	*ast;
	char		**env;
	char		**perm_env;
	char		**temp_env;
	// char		**bin_paths;
	char		*wd;
	char		*old_wd;
	int			in_fd;
	int			out_fd;
	int			status;
	int			isexit;
}	t_executer;

void	print_darray(char **array);
int		ft_redirection(t_executer *exec, t_ast_node *node);
int		ft_redirection_group(t_executer *exec, t_ast_node *node);
int		ft_redirection_heredoc(t_executer *exec, t_ast_node *node);
int		ft_execve_cmd(t_executer *exec, t_ast_node *node);

int		init_env(t_executer *exec, char **env);
int		set_bin_paths(t_executer *exec, char **env);
int		init_wds(t_executer *exec);
int		ft_exec_init(t_executer *exec, char **envp);
int		ft_exec_cmd(t_executer *exec, t_ast_node *node);
int		ft_exec_pipe(t_executer *exec, t_ast_node *node);
int		ft_execution(t_executer *exec, t_ast_node *node);
int		ft_exec_recursive(t_executer *exec, t_ast_node *node);

int		ft_builtin_cd(t_executer *exec, char **args);
int		ft_builtin_echo(t_executer *exec, char **args);
int		ft_builtin_env(t_executer *exec);
int		ft_builtin_exit(t_executer *exec, char **args);
int		ft_builtin_export(t_executer *exec, char **args);
int		ft_builtin_pwd(t_executer *exec);
int		ft_builtin_unset(t_executer *exec, char **args);

void	free_ptr(void *ptr);
void	free_double_array(char **array);
int		ft_isalnumunder(int i);
int		check_var(char *var);

char	**var_value_pair(char *arg);
int		env_count(char **env);
int		get_env_index(char **env, char *var);
char	*get_env_var(char **env, char *var);
int		set_var_value(char ***env, char *key, char *value);
char	**reallocate_env_nodes(char **env, int count);
void	ft_exec_clean(t_executer *exec);

#endif