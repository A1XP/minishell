/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:08:16 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/03/03 17:13:51 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	set_bin_paths(t_executer *exec, char **env)
{
	char	*path_env;
	int		i;

	path_env = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = env[i] + 5;
			break;
		}
		i++;
	}
	exec->bin_paths = ft_split(path_env, ':');
	if (exec->bin_paths == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*find_cmd(char *cmd, t_executer *exec)
{
	char	*tmp;
	char	*new_cmd;
	int		i;

	i = -1;
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		return (NULL);
	}
	while (exec->bin_paths[++i] != NULL)
	{
		tmp = ft_strjoin(exec->bin_paths[i], "/");
		if (tmp == NULL)
			return (NULL);
		new_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (new_cmd == NULL)
			return (NULL);
		if (access(new_cmd, F_OK) == 0)
			return (new_cmd);
		free(new_cmd);
	}
	return (NULL);
}

int	ft_execve_cmd(t_executer *exec, t_ast_node *node)
{
	char	*cmd;
	int	 prc_id;
	int	 status;

	prc_id = fork();
	if (prc_id == -1)
		return (EXIT_FAILURE);
	if (prc_id == 0)
	{
		dup2(exec->in_fd, STDIN_FILENO);
		dup2(exec->out_fd, STDOUT_FILENO);
		close(exec->in_fd);
		close(exec->out_fd);
		cmd = find_cmd(node->cmd->cmd_name, exec);
		if (!cmd)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(node->cmd->cmd_name, 2);
			return (127);
		}
		execve(cmd, node->cmd->args, exec->env);
	}
	waitpid(prc_id, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

char			**get_envp_copy(char **envp);

int	ft_exec_init(t_executer *exec, char **envp)
{
	exec->env = get_envp_copy(envp);
	if (exec->env == NULL)
		return (EXIT_FAILURE);
	if (init_wds(exec) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (set_bin_paths(exec, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exec->status = 0;
	exec->ast = NULL;
	exec->isexit = 0;
	exec->in_fd = dup(STDIN_FILENO);
	if (exec->in_fd == -1)
		return (EXIT_FAILURE);
	exec->out_fd = dup(STDOUT_FILENO);
	if (exec->out_fd == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
