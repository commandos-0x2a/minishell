#include <unistd.h>

int main()
{
	ssize_t	_read;
	char	buf[1024];

	_read = read(0, buf, sizeof(buf));
	while (_read > 0)
	{
		write(2, buf, _read);
		_read = read(0, buf, sizeof(buf));
	}
	return (0);
}