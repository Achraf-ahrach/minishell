# include <stdio.h>
# include <stdlib.h>
# include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = strlen(src);
	if (dstsize == 0)
		return (len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (len);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sub;
	size_t	len;

	len = strlen(s1) + strlen(s2);
	sub = malloc(len + 1);
	memset((void *)sub, 'a', len);
	if (!sub)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(sub, s1, strlen(s1) + 1);
		bzero((void *)s1, strlen(s1));
		free((void *)s1);
		s1 = 0;
	}
	if (s2)
	{
		strlcat(sub, s2, len + 1);
		bzero((void *)s2, strlen(s2));
		free((void *)s2);
		s2 = 0;
	}
	return (sub);
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int main()
{
	// char *p;

	// p = strjoin("achraf ", "ahrach");
	printf("%d", ft_isalpha(1));
	// printf("%c", p[0]);
	// printf("%c", p[1]);
	// printf("%c", p[2]);
	// printf("%c", p[3]);
	// printf("%c", p[4]);
}