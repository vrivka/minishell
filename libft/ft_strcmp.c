int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;
	int		r;

	i = 0;
	while (s1[i])
	{
		r = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (r)
			return (r);
		i++;
	}
	return (r);
}
