/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anjibdatamnhnabinmatsaliparsinghhhhwa3lasmi        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:18:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/03/23 02:25:02 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

typedef struct s_cmds {
	char	**cmd;
	int		infile;
	int		outfile;
	struct s_cmds	*next;
} t_cmds;

int main(int ac, char **av, char **env)
{
	t_cmds	cmds;
}