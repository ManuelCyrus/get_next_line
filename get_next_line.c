#include "get_next_line.h"

static char	*extract_line(char *resto)
{
	char	*line;
	size_t	i = 0;

	if (!resto[i])
		return (NULL);

	while (resto[i] && resto[i] != '\n')
		i++;

	line = malloc(i + (resto[i] == '\n') + 1);
	if (!line)
		return (NULL);

	i = 0;
	while (resto[i] && resto[i] != '\n')
	{
		line[i] = resto[i];
		i++;
	}
	if (resto[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*clean_resto(char *resto)
{
	char	*new_rest;
	size_t	i = 0, j = 0;

	while (resto[i] && resto[i] != '\n')
		i++;
	if (!resto[i])
	{
		free(resto);
		return (NULL);
	}

	new_rest = malloc(ft_strlen(resto) - i);
	if (!new_rest)
		return (NULL);

	i++;	
	while (resto[i])
		new_rest[j++] = resto[i++];

	new_rest[j] = '\0';
	free(resto);
	return (new_rest);
}

static char	*read_and_join(int fd, char *resto)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);

	bytes = 1;
	while (!ft_strchr(resto, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		resto = ft_strjoin(resto, buffer);
	}
	free(buffer);
	return (resto);
}

char	*get_next_line(int fd)
{
	static char	*resto;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	resto = read_and_join(fd, resto);
	if (!resto)
		return (NULL);

	line = extract_line(resto);
	resto = clean_resto(resto);

	return (line);
}
