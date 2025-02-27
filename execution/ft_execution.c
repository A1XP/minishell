/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:02:50 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/02/27 16:53:49 by pkhvorov         ###   ########.fr       */
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

int	ft_exec_cmd_or_builtin(t_executer *exec, t_ast_node *node)
{
	int		buildin;

	// printf("CMD: %s\n", node->cmd->cmd_name);
	if (node->cmd->redirects != NULL)
		ft_redirection(exec, node);
	buildin = ft_builtins(exec, node);
	if (buildin != -1)
	{
		return (buildin);
	}
	ft_execve_cmd(exec, node);
	close(exec->out_fd);
	exec->out_fd = dup(STDOUT_FILENO);
	close(exec->in_fd);
	exec->in_fd = dup(STDIN_FILENO);
	return (0);
}

int	ft_exec_and(t_executer *exec, t_ast_node *node)
{
	int	resault;

	resault = ft_exec_recursive(exec, node->left);
	printf("RES %d\n", resault);
	printf("ERROR NO %d\n", errno);
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

int ft_exec_group(t_executer *exec, t_ast_node *node)
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
			if (exec->status == 0)
				exit(EXIT_SUCCESS);
		}
	close(exec->out_fd);
	exec->out_fd = dup(STDOUT_FILENO);
	close(exec->in_fd);
	exec->in_fd = dup(STDIN_FILENO);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	ft_exec_recursive(t_executer *exec, t_ast_node *node)
{
	// printf("node->type %d\n", node->type);
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
	return (0);
}

//mkdir test && cd test
//cd test999 || echo WRONG
//echo test && (ls -lah | grep msh)
// (ls -lah && echo test)
// (ls -lah | grep msh) && (echo test1 && echo test2)