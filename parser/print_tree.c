/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:28:05 by natallia          #+#    #+#             */
/*   Updated: 2025/03/14 17:11:56 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stdio.h>

#define RESET_COLOR "\033[0m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define ORANGE "\033[38;5;214m"
#define MAGENTA "\033[35m"
#define RED "\033[31m"
#define WHITE "\033[37m"

void print_redirects(t_redirect *redirects)
{
	while (redirects)
	{
		const char *redir_type;
		if (redirects->redir_type == 8)
			redir_type = "IN";
		if (redirects->redir_type == 9)
			redir_type = "OUT";
		if (redirects->redir_type == 10)
			redir_type = "OUT_APPEND";
		if (redirects->redir_type == 11)
			redir_type = "HEREDOC";
		printf("  { %s: %s }", redir_type, redirects->filename);
		redirects = redirects->next;
	}
}

void print_assignments(t_list *assignments, const char *type)
{
	while (assignments)
	{
		printf("  { %s: %s }", type, (char *)assignments->content);
		assignments = assignments->next;
	}
}

void print_ast(t_ast_node *node, int level)
{
	// ft_printf("Am I in print tree\n");
	if (!node)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	switch (node->type)
	{
		case NODE_SEQUENCE:
			printf(MAGENTA "NODE_SEQUENCE" RESET_COLOR "\n");
			break;
		case NODE_PIPE:
			printf(ORANGE "NODE_PIPE" RESET_COLOR "\n");
			break;
		case NODE_AND:
			printf(GREEN "NODE_AND" RESET_COLOR "\n");
			break;
		case NODE_OR:
			printf(RED "NODE_OR" RESET_COLOR "\n");
			break;
		case NODE_GROUP:
			printf(YELLOW "NODE_GROUP" RESET_COLOR);
			if (node->group_redirs)
			{
				t_redirect *group_redirs = node->group_redirs;
				printf(" ");
				print_redirects(group_redirs);
			}
			printf("\n");
			break;
		case NODE_COMMAND:
			printf(CYAN "NODE_COMMAND: " RESET_COLOR);
			printf(CYAN "%s" RESET_COLOR, node->cmd && node->cmd->cmd_name ? node->cmd->cmd_name : "(null)");

			if (node->cmd && node->cmd->args)
			{
				char **arg = (node->cmd->args);
				printf(" { Args: ");
				while (*arg)
				{
					printf("%s ", *arg);
					arg++;
				}
				printf("}");
			}

			if (node->cmd && node->cmd->redirects)
			{
				t_redirect *redirs = node->cmd->redirects;
				printf(" ");
				print_redirects(redirs);
			}

			if (node->cmd && node->cmd->temp_assignments)
			{
				printf(" ");
				print_assignments(node->cmd->temp_assignments, "Temp Assignment");
			}

			if (node->cmd && node->cmd->perm_assignments)
			{
				printf(" ");
				print_assignments(node->cmd->perm_assignments, "Perm Assignment");
			}

			printf("\n");
			break;
		default:
			printf(RED "UNKNOWN NODE TYPE" RESET_COLOR "\n");
	}

	if (node->left)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("├─ Left:\n");
		print_ast(node->left, level + 1);
	}

	if (node->right)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("├─ Right:\n");
		print_ast(node->right, level + 1);
	}

	if (node->subtree)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("└─ Subtree:\n");
		print_ast(node->subtree, level + 1);
	}
}
