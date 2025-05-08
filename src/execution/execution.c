#include "../includes/minishell.h"

// REVER SOH MONTEI COMO "MODELO"
void exec_cmd(t_command *cmd)
{
	if (is_builtin(cmd))
		exec_builtin(cmd);
	else if (has_pipe(cmd))
		exec_pipeline(cmd);
	else
		exec_exter_cmd(cmd);
}
