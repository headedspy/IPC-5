#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include "block.h"
#include "gen.h"

int main(){
	int memFd = shm_open("mem", O_CREAT | O_RDWR, S_IRWXU);
	if(memFd < 0){
		perror("Open");
		return -1;
	}
	if(ftruncate(memFd, sizeof(struct block)) == -1){
		perror("Truncate");
		return -1;
	}

	struct block* mmr = mmap(NULL, sizeof(struct block), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0);
	if(mmr == NULL){
		perror("Mmap");
		return -1;
	}

	uint32_t seed = 0;
	mmr->pos = 0;
	for(;;){
		generate((void*)mmr->arr[mmr->pos%512], seed);
		seed++;

		printf("seed: %d\n",verify((void*)mmr->arr[mmr->pos%512]));

		mem->pos++;
	}
	return 0;
}
