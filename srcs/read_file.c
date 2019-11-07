#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int		calc_file_len(const char *file_name)
{
	char	buf[256];
	int		len;
	int		ret;
	int		fd;

	len = 0;
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		write(2, "open ERROR\n", 11);
		return (0);
	}
	while ((ret = read(fd, buf, 256)) > 0)
		len += ret;
	close(fd);
	if (ret < 0)
	{
		write(2, "read ERROR\n", 11);
		return (0);
	}
	return (len);
}

int		copy_file_to_buf(const char *name, char *buf, int len)
{
	int	fd;

	if ((fd = open(name, O_RDONLY)) < 0)
	{
		write(2, "open ERROR\n", 11);
		return (0);
	}
	if (read(fd, buf, len) < len)
	{
		write(2, "read ERROR\n", 11);
		return (0);
	}
	close(fd);
	return (1);
}

char	*read_file(const char *file_name)
{
	int		len;
	char	*file;

	if (!(len = calc_file_len(file_name)))
	{
		write(2, "file error\n", 11);
		return (0);
	}
	if (!(file = malloc((len + 1) * sizeof(char))))
	{
		write(2, "malloc error\n", 13);
		return (0);
	}
	file[len] = 0;
	//printf("file len: %i\n", len);
	if (!copy_file_to_buf(file_name, file, len))
	{
		free(file);
		return (0);
	}
	return (file);
}
