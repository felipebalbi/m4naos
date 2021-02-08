#include <sys/stat.h>
#include <errno.h>

#include <m4naos/kernel.h>
#include <m4naos/uart.h>

register char *stack_ptr asm("sp");

caddr_t __weak _sbrk(int incr)
{
	extern char _end;
	static char *heap_end = &_end ;
	char *prev_heap_end = heap_end;

	if (heap_end + incr > stack_ptr) {
		errno = ENOMEM;
		return (caddr_t) -1;
	}

#if 0
	if (heap_end + incr >= (char *)(&__end_stack__ - &__stack_min_size__)) {
		errno = ENOMEM;
		return (caddr_t) -1;
	}
#endif

	heap_end += incr;

	return (caddr_t) prev_heap_end;
}

int __weak _close(int fd __unused)
{
	return -1;
}

int __weak _fstat(int fd __unused, struct stat *st)
{
	st->st_mode = S_IFCHR;

	return 0;
}

int __weak _isatty(int fd __unused)
{
	return 1;
}

int __weak _lseek(int fd __unused, int ptr __unused, int dir __unused)
{
	return 0;
}

int __weak _read(int fd __unused, char *ptr __unused, int len __unused)
{
	return 0;
}

int __weak _write(int file __unused, char *str, int len)
{
	int i;

	for (i = 0; i < len; i++)
		uart_putch(*str++);

	return 0;
}

void __weak _exit(int status __unused)
{
	for (;;);
}

int __weak _kill(int pid __unused, int sig __unused)
{
	errno = EINVAL;

	return -1;
}

int __weak _getpid(void)
{
	return 1;
}

