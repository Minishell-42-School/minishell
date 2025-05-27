

#include "../../../includes/minishell.h"

// HEREDOC PELO GEMINI

// heredoc.c

// // Um novo manipulador de sinal para o processo filho do heredoc
// static void	heredoc_sigint_handler(int sig)
// {
// 	(void)sig;
//     // Feche o pipe de escrita e saia. Isso vai fazer o readline no loop_heredoc retornar NULL.
//     // Poderíamos também usar exit(1), mas fechar o pipe é mais limpo para o pai.
//     exit(130); // Use 130 para indicar que foi encerrado por SIGINT
// }

// void	handle_heredoc(t_redirections *redir)
// {
// 	int		heredoc_fd[2];
// 	pid_t	pid;
//     int     status;

// 	if (pipe(heredoc_fd) == -1)
// 	{
// 		perror("pipe");
// 		return ;
// 	}

//     pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         close(heredoc_fd[0]);
//         close(heredoc_fd[1]);
//         return ;
//     }
//     else if (pid == 0) // Processo filho para o heredoc
//     {
//         close(heredoc_fd[0]); // Filho só escreve no pipe
//         signal(SIGINT, heredoc_sigint_handler); // Manipulador específico para o filho
//         signal(SIGQUIT, SIG_IGN); // Ignora Ctrl+\ no filho

//         loop_heredoc(redir, heredoc_fd); // O loop do heredoc agora roda no filho
//         close(heredoc_fd[1]); // Fecha o pipe de escrita
//         exit(0); // Filho sai
//     }
//     else // Processo pai
//     {
//         close(heredoc_fd[1]); // Pai só lê do pipe
//         signal(SIGINT, SIG_IGN); // Ignora SIGINT no pai enquanto o filho do heredoc está ativo
//         signal(SIGQUIT, SIG_IGN); // Garante que o pai ignore SIGQUIT também

//         waitpid(pid, &status, 0); // Espera o processo filho do heredoc terminar

//         // Restaura os manipuladores de sinal do pai após o heredoc
//         config_signals(); // Isso reconfiguraria para o seu handle_sigint original

//         if (WIFEXITED(status))
//         {
//             if (WEXITSTATUS(status) == 130) // Se o filho saiu por SIGINT (130)
//             {
//                 g_exit_status = 130;
//                 // Você pode querer fazer algo mais aqui, como pular a execução do comando
//                 // para o qual o heredoc estava destinado, se o heredoc foi interrompido.
//                 // Para isso, você precisaria de uma forma de sinalizar isso para a função chamadora.
//                 // Por enquanto, apenas defina o status de saída.
//             } else {
//                 g_exit_status = WEXITSTATUS(status);
//             }
//         }
//         else if (WIFSIGNALED(status))
//         {
//             g_exit_status = 128 + WTERMSIG(status);
//         }

//         if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
//             perror("dup2");
//         close(heredoc_fd[0]); // Fecha o pipe de leitura
//     }
// }

// // Em loop_heredoc, você pode ter um tratamento para NULL de readline:
// void	loop_heredoc(t_redirections *redir, int fd[2])
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("Heredoc ~> ");
// 		if (!line) // Ctrl+D ou sinal que causou o retorno de NULL
// 		{
// 			// Se o readline retornou NULL por causa de um sinal,
// 			// o heredoc_sigint_handler já teria saído.
// 			// Este caso seria mais para Ctrl+D.
// 			printf("%s\n", SIG_HEREDOC); // Ou uma mensagem mais genérica de EOF
// 			// Você pode decidir se quer adicionar uma linha vazia ou não
// 			// se a saída for por EOF (Ctrl+D)
// 			free(line); // readline pode retornar NULL, então cuidado ao fazer free(NULL)
// 			break ;
// 		}
// 		if (ft_strncmp(line, redir->filename, ft_strlen(redir->filename)) == 0 &&
//             ft_strlen(line) == ft_strlen(redir->filename)) // Adicionar verificação de tamanho para exatidão
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(fd[1], line, ft_strlen(line));
// 		write(fd[1], "\n", 1); // Sempre adicione uma nova linha, readline remove
// 		free(line);
// 	}
// }

// ==============================================

// static void	heredoc_sigint_handler(int sig)
// {
// 	(void)sig;
//     // Feche o pipe de escrita e saia. Isso vai fazer o readline no loop_heredoc retornar NULL.
//     // Poderíamos também usar exit(1), mas fechar o pipe é mais limpo para o pai.
//     exit(130); // Use 130 para indicar que foi encerrado por SIGINT
// }

void	loop_heredoc(t_redirections *redir, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("Heredoc ~> ");
		if (!line)
		{
			printf("%s\n", SIG_HEREDOC);
      free(line);
      break ;
		}
		if (ft_strncmp(line, redir->filename, ft_strlen(redir->filename)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		if (line[0] != '\0')
			write(fd, "\n", 1);
		free(line);
	}
}

static void	hdoc_child_proc(t_redirections *redir, int hdo_fd[2])
{
	close(hdo_fd[0]);
  heredoc_signals();
  // signal(SIGINT, heredoc_sigint);
  // signal(SIGQUIT, SIG_IGN);
	loop_heredoc(redir, hdo_fd[1]);
	close(hdo_fd[1]);
	exit(EXIT_SUCCESS);
}

static void	hdoc_parent_proc(int hdo_fd[2], pid_t pid)
{
	int status;

	close(hdo_fd[1]);
  ign_signals();
  // signal(SIGINT, SIG_IGN);
  // signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
  config_signals();
	if (WIFEXITED(status))
  {
    if (WEXITSTATUS(status) == 130)
      g_exit_status = 130;
    else
      g_exit_status = WEXITSTATUS(status);
  }
  else if (WIFSIGNALED(status))
    g_exit_status = 128 + WTERMSIG(status);
	if (dup2(hdo_fd[0], STDIN_FILENO) == -1)
		perror("dup2");
	close(hdo_fd[0]);
}

void	handle_heredoc(t_redirections *redir)
{
	int		heredoc_fd[2];
	pid_t	pid;

	if (pipe(heredoc_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
    close(heredoc_fd[0]);
    close(heredoc_fd[1]);
		return ;
	}
	if (pid == 0)
		hdoc_child_proc(redir, heredoc_fd);
	else
    hdoc_parent_proc(heredoc_fd, pid);
}
