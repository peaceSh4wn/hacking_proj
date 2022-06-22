#include "config.h"

static pid_t *cpid = NULL;

int popen2(const char *cmd) {
	
	int i, fds[2];

	pid_t pid;

	if (!cpid) {
		if (!(cpid = calloc(1024, sizeof(pid_t)))) {
			return -1;
		}
	}

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == -1) 
		return -1;
	
	if ((pid = fork()) < 0) 
		return -1;
	else if (!pid) {
		close(fds[1]);
		if (fds[0] != STDIN_FILENO) {
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
		}
		dup2(STDIN_FILENO, STDOUT_FILENO);
		dup2(STDIN_FILENO, STDERR_FILENO);

		for (i = 0; i < 1024; i++) {
			if (cpid[i] > 0)
				close(i);
		}
		execl("/bin/sh", "sh", "-c", cmd, NULL);
		_exit(127);
	}
	close(fds[0]);
	cpid[fds[1]] = pid;
	return fds[1];
}

int pclose2(int fd) {
	int stat;
	pid_t pid;

	if (!cpid) {
		return -1;
	}
	if (!cpid[fd]) {
		return -1;
	}
	close(fd);
	pid = cpid[fd];

	while (waitpid(pid, &stat, 0) == -1) 
		if (errno != EINTR)
			return -1;
	
	return stat;
}
