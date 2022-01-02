#include "common_header.h"

#define XFREE(FP)	\
	if (FP) {		\
		fclose(FP);	\
		FP = NULL;	\
	}

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
    pdr->sin_addr.s_addr = INADDR_ANY;
    pdr->sin_port = htons(port);

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

void *file_trans(void *args) {
    uint8_t buf[1024] = {0};
    ThreadVars *tv = args;
    if (FAILURE == getSkt(tv, "", 1337)) {
        perror("getSkt");
        return NULL;
    }

    if (0 > bind(tv->sock, (struct sockaddr*)&tv->pdr, sizeof(struct sockaddr))) {
		perror("[-] bind");
		goto err;
	}
	if (0 > listen(tv->sock, 5)) {
		perror("[-] listen");
		goto err;
	}

	struct sockaddr_in newSck;
	socklen_t len = sizeof(struct sockaddr);
	bzero(&newSck, len);

	int nfd = accept(tv->sock, (void *)&newSck, &len);

	int rcnt = 0, res = 0;
	FILE *fp = fopen("xfile", "r");
	if (NULL == fp) {
		perror("fopen");
		goto err;
	}

    printf("send start\n");
	while(1) {
		rcnt = fread(buf, 1, 1024, fp);
		if (0 == rcnt) break;
		res = write(nfd, buf, rcnt);
		printf("%d %d\n", rcnt, res);
        if (0 >= res) break;
	}

    printf("[!] send end\n");
err:
    XFREE(fp);
    freeSkt(tv);
    return NULL;
}

int main() {
	ThreadVars *tv = malloc(sizeof(ThreadVars));

    pthread_t pid;

    // create file trans thread
    pthread_create(&pid, NULL, file_trans, tv);

    // wait for file trans thread
    pthread_join(pid);

    return 0;
}
