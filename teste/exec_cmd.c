#include "./test.h"


// char *extract_output_line(const char *buffer, const char *command)
// {
//   char *copy = strdup(buffer);
//   char *line = strtok(copy, "\n");
//   int found_command = 0;

//   while (line)
//   {
//     if (!found_command)
//     {
//       if (strstr(line, command))
//       found_command = 1;
//     }
//     else
//     {
//       char *result = strdup(line);
//       free(copy);
//       return result;
//     }
//     line = strtok(NULL, "\n");
//   }
//   free(copy);
//   return NULL;
// }

char *extract_output_line(const char *buffer, const char *command)
{
    char *copy = strdup(buffer);
    char *line = strtok(copy, "\n");
    int found_command = 0;
    size_t total_len = 0;
    char *result = NULL;

    while (line)
    {
        if (!found_command)
        {
            if (strstr(line, command))
                found_command = 1;
        }
        else
        {
            if (strstr(line, "Minishell~>") || strstr(line, "Exit Minishell"))
            {
                line = strtok(NULL, "\n");
                continue ;
            }

            size_t len = strlen(line);
            result = realloc(result, total_len + len + 2);
            if (!result)
            {
                free(copy);
                return (NULL);
            }
            strcpy(result + total_len, line);
            total_len += len;
            result[total_len++] = '\n';
            result[total_len] = '\0';
        }
        line = strtok(NULL, "\n");
    }
    free(copy);
    return (result);
}

char *get_from_bash(const char *command)
{
    FILE *fp;
    char buffer[1024];
    size_t total_len = 0;
    char *output = NULL;

    // Exec the command using bash and open a pipe for read the output
    char bash_cmd[2048];
    snprintf(bash_cmd, sizeof(bash_cmd), "bash -c '%s'", command);
    fp = popen(bash_cmd, "r");
    if (!fp)
        return NULL;

    while (fgets(buffer, sizeof(buffer), fp))
    {
        size_t len = strlen(buffer);
        output = realloc(output, total_len + len + 1);
        if (!output)
        {
            pclose(fp);
            return NULL;
        }
        strcpy(output + total_len, buffer);
        total_len += len;
    }

    if (output)
        output[total_len] = '\0';

    pclose(fp);
    return (output);
}


void  print_result(const char *command, char *exp_output, char *buffer, int *test_nbr)
{
  char *result;
  int   need_free;

  need_free = 0;
  if (!exp_output)
  {
    exp_output = get_from_bash(command);
    need_free = 1;
  }
  result = extract_output_line(buffer, command);
  if (strstr(result, exp_output))
  {
    // printf("✅ Command - %s\n", command);
    printf("%d.✅ | ", *test_nbr);
    (*test_nbr)++;
  }
  else
  {
    // printf("❌ Command fail - %s\n~> Expected: %s\n~> Received: %s\n", command, exp_output ,result);
    printf("%d. ❌ | \nCommand fail - %s\n~> Expected: %s\n~> Received: %s\n", *test_nbr, command, exp_output, result);
    (*test_nbr)++;
  }
  if (need_free)
    free(exp_output);
}
void  exec_cmd(const char *command, char *exp_output, int *test_nbr)
{
    int stdin_pipe[2], stdout_pipe[2];
    pid_t pid;
    char buffer[2048];
    int status;

    if (pipe(stdin_pipe) == -1 || pipe(stdout_pipe) == -1)
    {
        perror("pipe");
        return ;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return ;
    }

    if (pid == 0)
    {
        // Child process: organizes the pipes and runs the minishell
        dup2(stdin_pipe[0], STDIN_FILENO);
        dup2(stdout_pipe[1], STDOUT_FILENO);
        dup2(stdout_pipe[1], STDERR_FILENO);

        close(stdin_pipe[0]);
        close(stdin_pipe[1]);
        close(stdout_pipe[0]);
        close(stdout_pipe[1]);

        execl(MINISHELL_EXEC, MINISHELL_EXEC, NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    else
    {
      // parent proc: sends the command to the minishell, receives a response
      // from it, stores this response in a string and compares it with the
      // expected result.
        close(stdin_pipe[0]);
        close(stdout_pipe[1]);

        write(stdin_pipe[1], command, strlen(command));
        write(stdin_pipe[1], "\n", 1);
        close(stdin_pipe[1]);

        ssize_t bytes;
        size_t total = 0;
        while ((bytes = read(stdout_pipe[0], buffer + total, sizeof(buffer) - 1 - total)) > 0)
            total += bytes;
        buffer[total] = '\0';

        close(stdout_pipe[0]);
        waitpid(pid, &status, 0);

        print_result(command, exp_output, buffer, test_nbr);
    }
}
