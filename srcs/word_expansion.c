#include "minishell.h"

char	*strjoin_replace(char *s1, char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (join);
}

char	*ft_strtok(char **str, char *delim)
{
	int		i;
	char	*res;

	i = 0;
	while (!ft_strchr(delim, (*str)[i]))
		i++;
	res = ft_strldup(*str, i);
	*str += i;
	return (res);
}

char	*getname(char **word)
{
	int		i;
	char	*name;

	i = 0;
	if (ft_isalpha((*word)[i]))
		while (ft_isalnum((*word)[++i]) || (*word)[i] == '_')
			;
	name = ft_strldup((*word), i);
	*word += i;
	return (name);
}

char	*expand_param(char **word, char *envp[], int exitcode)
{
	char	*value;
	char	*name;

	++*word;
	name = getname(word);
	if (ft_strcmp(name, "") == 0)
	{
		free(name);
		if (**word == '?')
		{
			++*word;
			return (ft_itoa(exitcode));
		}
		if (isquotechar(**word))
			return (ft_strdup(""));
		return (ft_strdup("$"));
	}
	value = get_env(envp, name);
	if (!value)
		value = "";
	return (ft_strdup(value));
}

char	*expand_quote(char **word, char *envp[], int exitcode)
{
	char	*res;

	if (*(*word)++ == '\'')
		res = ft_strtok(word, "'");
	else
	{
		res = ft_strdup("");
		while (**word != '"')
			if (**word == '$')
				res = strjoin_replace(res, expand_param(word, envp, exitcode));
			else
				res = strjoin_replace(res, ft_strtok(word, "\"$"));
	}
	++*word;
	return (res);
}

/* wasq: was quoted */

struct s_field
{
	int		wasq;
	char	*str;
};

struct s_field	*new_field(int wasq, char *str)
{
	struct s_field	*new;

	new = malloc(sizeof(struct s_field));
	new->wasq = wasq;
	new->str = str;
	return (new);
}

void	free_field(void *f)
{
	free(((struct s_field *)f)->str);
	free(f);
}

struct s_field	*merge_field(struct s_field *f1, struct s_field *f2)
{
	struct s_field	*new;

	new = new_field(f1->wasq | f2->wasq, ft_strjoin(f1->str, f2->str));
	free_field(f1);
	free_field(f2);
	return (new);
}

t_list	*split_to_list(char *str)
{
	t_list	*list;

	list = ft_lstnew(new_field(0, ft_strtok(&str, " \t\n")));
	while (*str)
	{
		while (ft_isblank(*str) || *str == '\n')
			str++;
		ft_lstadd_front(
				&list,
				ft_lstnew(new_field(0, ft_strtok(&str, " \t\n"))));
	}
	return (list);
}

t_list	*expand_split_param(char **word, char *envp[], int exitcode)
{
	char	*param_exp;
	t_list	*list;

	param_exp = expand_param(word, envp, exitcode);
	list = split_to_list(param_exp);
	free(param_exp);
	return (list);
}

t_list	*merge_fieldlist(t_list *fl1, t_list *fl2)
{
	t_list	*last;

	last = ft_lstlast(fl1);
	last->content = merge_field(
			(struct s_field *)fl2->content,
			(struct s_field *)last->content);
	last->next = fl2->next;
	free(fl2);
	return (fl1);
}

void	remove_empty_fields(t_list **fields)
{
	struct s_field	*f;
	t_list			*tmp;

	while (*fields)
	{
		f = (*fields)->content;
		if (!f->wasq && ft_strcmp(f->str, "") == 0)
		{
			tmp = *fields;
			*fields = (*fields)->next;
			ft_lstdelone(tmp, free_field);
		}
		else
			fields = &(*fields)->next;
	}
}

t_list	*expand_word(char *word, char *envp[], int exitcode)
{
	t_list	*fields;

	fields = ft_lstnew(new_field(0, ft_strdup("")));
	while (*word)
		if (isquotechar(*word))
			fields->content = merge_field(
					(struct s_field *)fields->content,
					new_field(1, expand_quote(&word, envp, exitcode)));
		else if (*word == '$')
			fields = merge_fieldlist(
					expand_split_param(&word, envp, exitcode),
					fields);
		else
			fields->content = merge_field(
					(struct s_field *)fields->content,
					new_field(0, ft_strtok(&word, "'\"$")));
	remove_empty_fields(&fields);
	return (fields);
}

static char **get_array_from_list(t_list **list, int size)
{
	t_list	*node;
	char	**arr;

	node = *list;
	arr = malloc(sizeof(char *) * (size + 1));
	arr[size] = 0;
	while (--size >= 0)
	{
		arr[size] = ((struct s_field *)node->content)->str;
		node = node->next;
	}
	ft_lstclear(list, free);
	return (arr);
}

t_list	*ft_lstjoin(t_list *lst1, t_list *lst2)
{
	t_list	**end;

	end = &lst1;
	while (*end)
		end = &(*end)->next;
	*end = lst2;
	return (lst1);
}

void	expand_args(t_data *p)
{
	t_list	*arglist;
	int		i;

	arglist = 0;
	i = -1;
	while (p->av[++i])
		arglist = ft_lstjoin(
				expand_word(p->av[i], p->envp, p->ret),
				arglist);
	free_matrix(p->av);
	p->ac = ft_lstsize(arglist);
	p->av = get_array_from_list(&arglist, p->ac);
}
