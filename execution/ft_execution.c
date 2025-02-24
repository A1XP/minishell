/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:02:50 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/02/21 16:09:57 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_builtins(t_executer *exec, t_ast_node *node)
{
	if (ft_strcmp(node->cmd->cmd_name, "exit") == 0)
		return (ft_buildin_exit(node->cmd->args));
	else if (ft_strcmp(node->cmd->cmd_name, "pwd") == 0)
		return (ft_buildin_pwd(exec));
	else if (ft_strcmp(node->cmd->cmd_name, "export") == 0)
		return (ft_buildin_export(exec, node->cmd->args));
	else if (ft_strcmp(node->cmd->cmd_name, "cd") == 0)
		return (ft_buildin_cd(exec, node->cmd->args));
	else if (ft_strcmp(node->cmd->cmd_name, "env") == 0)
		return (ft_buildin_env(exec));
	else if (ft_strcmp(node->cmd->cmd_name, "unset") == 0)
		return (ft_buildin_unset(exec, node->cmd->args));
	else if (ft_strcmp(node->cmd->cmd_name, "echo") == 0)
		return (ft_buildin_echo(exec, node->cmd->args));
	return (-1);
}

int	ft_exec_cmd_or_buildin(t_executer *exec, t_ast_node *node)
{
	int		buildin;

	if (node->cmd->redirects != NULL)
		ft_redirection(exec, node);
	buildin = ft_builtins(exec, node);
	if (buildin != -1)
	{
		return (buildin);
	}
	execve_cmd(exec, node);
	close(exec->out_fd);
	exec->out_fd = dup(STDOUT_FILENO);
	close(exec->in_fd);
	exec->in_fd = dup(STDIN_FILENO);
	return (0);
}

int	ft_exec_and(t_executer *exec, t_ast_node *node)
{
	int	res;

	res = ft_exec_recursive(exec, node->left);
	if (errno != 0)
		return (res);
	res = ft_exec_recursive(exec, node->right);
	if (res == 0)
		return (ft_exec_recursive(exec, node->right));
	return (res);
}

int	ft_exec_or(t_executer *exec, t_ast_node *node)
{
	exec->status = ft_exec_recursive(exec, node->left);
	if (!exec->status)
		return (ft_exec_recursive(exec, node->right));
	return (exec->status);
}

int	ft_execution(t_executer *exec, t_ast_node *node)
{
	if (node == NULL)
		return (EXIT_SUCCESS);
	exec->ast = node;
	ft_exec_recursive(exec, node);
	exec->ast = NULL;
	return (exec->status);
}

int	ft_exec_recursive(t_executer *exec, t_ast_node *node)
{
	printf("EX TYPE %d\n", node->type);
	if (node->type == NODE_PIPE)
		ft_exec_pipe(exec, node);
	else if (node->type == NODE_COMMAND)
		ft_exec_cmd_or_buildin(exec, node);
	else if (node->type == NODE_AND)
		ft_exec_and(exec, node);
	else if (node->type == NODE_OR)
		ft_exec_or(exec, node);
	return (0);
}

//mkdir test && cd test
//cd test999 || echo WRONG