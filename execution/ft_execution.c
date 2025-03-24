/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:02:50 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/20 16:26:59 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_builtins(t_executer *exec, t_ast_node *node)
{
	if (ft_strcmp(node->cmd->cmd_name, "exit") == 0)
		return (ft_builtin_exit(exec, node->cmd->args));
	else if (ft_strcmp(node->cmd->cmd_name, "pwd") == 0)
		return (ft_builtin_pwd(exec));
	else if (ft_strcmp(node->cmd->cmd_name, "export") == 0)
		return (ft_builtin_export(exec, node->cmd->args));
	else if (ft_strcmp(node->cmd->cmd_name, "cd") == 0)
		return (ft_builtin_cd(exec, node->cmd->args));
	else if (ft_strcmp(node->cmd->cmd_name, "env") == 0)
		return (ft_builtin_env(exec));
	else if (ft_strcmp(node->cmd->cmd_name, "unset") == 0)
		return (ft_builtin_unset(exec, node->cmd->args));
	else if (ft_strcmp(node->cmd->cmd_name, "echo") == 0)
		return (ft_builtin_echo(exec, node->cmd->args));
	return (-1);
}

// static void	prepare_args(t_executer *exec, t_ast_node *node)
// {
// 	int		i;
// 	char	*temp;

// 	i = 0;
// 	while (node->cmd->args[i] != NULL)
// 	{
// 		if (node->cmd->args[i][0] == '$')
// 		{
// 			if (node->cmd->args[i + 1] == NULL)
// 				break;
// 			temp = get_env_var(exec->env, node->cmd->args[i + 1]);
// 			if (temp != NULL)
// 			{
// 				free(node->cmd->args[i + 1]);
// 				node->cmd->args[i + 1] = ft_strdup(temp);
// 			}
// 		}
// 		i++;
// 	}
// }

int	ft_exec_cmd_or_builtin(t_executer *exec, t_ast_node *node)
{
	int		buildin;

	if (node->cmd->cmd_name == NULL)
		return (0);
	// printf("CMD: %s\n", node->cmd->cmd_name);
	if (node->cmd->redirects != NULL)
		ft_redirection(exec, node);
	// prepare_args(exec, node);
	buildin = ft_builtins(exec, node);
	if (buildin != -1)
	{
		exec->status = buildin;
		return (exec->status);
	}
	exec->status = ft_execve_cmd(exec, node);
	// close(exec->out_fd);
	// exec->out_fd = dup(STDOUT_FILENO);
	// close(exec->in_fd);
	// exec->in_fd = dup(STDIN_FILENO);
	return (exec->status);
}

int	ft_exec_and(t_executer *exec, t_ast_node *node)
{
	int	resault;

	resault = ft_exec_recursive(exec, node->left);
	// printf("RES %d\n", resault);
	// printf("ERROR NO %d\n", errno);
	if (errno != 0)
		return (resault);
	if (resault == 0)
		return (ft_exec_recursive(exec, node->right));
	return (resault);
}

int	ft_exec_or(t_executer *exec, t_ast_node *node)
{
	exec->status = ft_exec_recursive(exec, node->left);
	if (exec->status)
		return (ft_exec_recursive(exec, node->right));
	return (exec->status);
}

int	ft_execution(t_executer *exec, t_ast_node *node)
{
	if (node == NULL)
		return (EXIT_SUCCESS);
	exec->ast = node;
	exec->status = ft_exec_recursive(exec, node);
	exec->ast = NULL;
	return (exec->status);
}

int	ft_exec_group(t_executer *exec, t_ast_node *node)
{
	pid_t		pid;
	int			status;

	if (node->group_redirs != NULL)
		ft_redirection_group(exec, node);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		exec->status = ft_exec_recursive(exec, node->subtree);
		ft_exec_clean(exec);
		exit(exec->status);
	}
	// close(exec->out_fd);
	// exec->out_fd = dup(STDOUT_FILENO);
	// close(exec->in_fd);
	// exec->in_fd = dup(STDIN_FILENO);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	ft_exec_seq(t_executer *exec, t_ast_node *node)
{
	exec->status = ft_exec_recursive(exec, node->left);
	exec->status = ft_exec_recursive(exec, node->right);
	return (exec->status);
}

void create_env(char ***env, char *arg)
{

	*env = malloc((2) * sizeof(char *));
	if (!*env)
		return ;
	(*env)[0] = ft_strdup(arg);
	(*env)[1] = NULL;
}

int	ft_assignment(char ***env, t_list *assignment)
{
	char **temp;

	while (assignment != NULL)
	{
		if (assignment->content != NULL)
		{
			if (*env == NULL)
				create_env(env, (char *)assignment->content);
			else
			{
				temp = var_value_pair((char *)assignment->content);
				if (temp == NULL)
					return (EXIT_FAILURE);
				set_var_value(env, temp[0], temp[1]);
			}

		}
		assignment = assignment->next;
	}
	return (0);
}

int	ft_exec_recursive(t_executer *exec, t_ast_node *node)
{
	if (node->cmd != NULL && node->cmd->temp_assignments != NULL)
		ft_assignment(&exec->temp_env, node->cmd->temp_assignments);
	if (node->cmd != NULL && node->cmd->perm_assignments != NULL)
		ft_assignment(&exec->perm_env, node->cmd->perm_assignments);
	// printf("node->type %d\n", node->type);
	// print_darray(exec->temp_env);
	if (node->type == NODE_PIPE)
		return (ft_exec_pipe(exec, node));
	else if (node->type == NODE_COMMAND)
		return (ft_exec_cmd_or_builtin(exec, node));
	else if (node->type == NODE_AND)
		return (ft_exec_and(exec, node));
	else if (node->type == NODE_OR)
		return (ft_exec_or(exec, node));
	else if (node->type == NODE_GROUP)
		return (ft_exec_group(exec, node));
	else if (node->type == NODE_SEQUENCE)
		return (ft_exec_seq(exec, node));
	return (0);
}
