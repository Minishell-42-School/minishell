#include "../includes/minishell.h"

char *get_path(t_command *cmd)
{
  char  *path;

  if (ft_strchr(cmd->command_name, '/'))
    path = cmd->command_name;
  else
    path = ft_strjoin("/bin/", cmd->command_name);
  if (access(path, X_OK) != 0)
    perror("Command not found or not executable");
  return (path);
}

void  exec_cmd_ext(t_command *cmd)
{
  char *path;
  pid_t pid;

  path = get_path(cmd);
  pid = fork();
  if (pid == 0)
  {
    execve(path, cmd->args, NULL);
    perror("Error execve");
    exit(EXIT_FAILURE);
  }
  else if (pid > 0)
    waitpid(pid, NULL, 0);
  else
    perror("Error fork");
  free(path);
}
