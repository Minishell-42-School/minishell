#include "pipe.h"
// # include "../../libft/libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(len);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		str[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 != '\0')
	{
		str[i] = *s2;
		i++;
		s2++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	ch = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	if (ch == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

// char *get_path(t_command *cmd)
// {
//   char  *path;

//   if (ft_strchr(cmd->command_name, '/'))
//     path = cmd->command_name;
//   else
//     path = ft_strjoin("/bin/", cmd->command_name);
//   if (access(path, X_OK) != 0)
//     perror("Command not found or not executable");
//   return (path);
// }
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || dest == src)
		return (dest);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}


static size_t	ft_elem_array(const char *s, char c)
{
	size_t	i;
	size_t	array_len;
	int		word_control;

	i = 0;
	array_len = 0;
	word_control = 0;
	while (s[i])
	{
		if (s[i] != c && word_control == 0)
		{
			word_control = 1;
			array_len++;
		}
		else if (s[i] == c)
			word_control = 0;
		i++;
	}
	return (array_len);
}

static char	*ft_new_string(const char *str, unsigned int i, unsigned int start)
{
	size_t	str_len;
	char	*new_str;

	str_len = i - start;
	new_str = (char *)malloc((str_len + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_memcpy(new_str, str, str_len);
	new_str[str_len] = '\0';
	return (new_str);
}

static void	ft_free_all(char **array, unsigned int j)
{
	while (j > 0)
		free(array[--j]);
	free(array);
}

static char	*ft_allocate_array(char **array, char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			array[j] = ft_new_string(s + start, i, start);
			if (array[j] == NULL)
			{
				ft_free_all(array, j);
				return (NULL);
			}
			j++;
		}
		else
			i++;
	}
	return (*array);
}

char	**ft_split(char const *s, char c)
{
	size_t	array_len;
	char	**array;

	array_len = ft_elem_array(s, c);
	array = (char **)malloc((array_len + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	array[array_len] = NULL;
	ft_allocate_array(array, s, c);
	return (array);
}
