#ifndef PIPEX_H
# define PIPEX_H

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	panic(void);
int		panic_open(char *path, int flags);
int		create_file(char *path, int flags, int mode);

typedef struct s_pair
{
	int		in;
	int		out;
}				t_pair;

#endif
