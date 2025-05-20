

#include "../../includes/minishell.h"

char **var_to_envp(t_var *vars)
{
	t_aux	aux;
	t_var *v;
	char **envp;
	char  *s;
	
	aux.count = 0;
    aux.i = 0;
    v = vars;
    while (v)
    {
        if (v->exported)
            aux.count++;
        v = v->next;
    }
    envp = malloc((aux.count + 1) * sizeof(char *));
    if (!envp)
        return (NULL);
    v = vars;
    while (v)
    {
        if (v->exported)
        {
            aux.len = ft_strlen(v->key) + 1 + ft_strlen(v->value) + 1;
            s = malloc(aux.len);
            if (!s)
                return (NULL);
            ft_strcpy(s, v->key);
            s[ft_strlen(v->key)] = '=';
            ft_strcpy(s + ft_strlen(v->key) + 1, v->value);
            envp[aux.i++] = s;
        }
        v = v->next;
    }
    envp[aux.i] = NULL;
    return (envp);
}
