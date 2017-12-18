#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "gen.h"
#include "block.h"

int main(){
	int memFd = shm_open("mem", O_RDONLY, 0);
	if(memFd < 0){
		perror("Open");
		return -1;
	}

	struct block* mmr = mmap(NULL, sizeof(struct block), PROT_READ, MAP_SHARED, memFd, 0);
	if(mmr == NULL){
		perror("Mmap");
		return -1;
	}

	while(mmr->pos < 512);

	uint64_t cur_pos = mmr->pos - 150;
	uint32_t prev_seed = verify((void*)mmr->arr[cur_pos%512]);

	++cur_pos;

	for(;;){
		uint32_t cur_seed = verify((void*)mmr->arr[cur_pos%512]);

		if(cur_seed - 1 == prev_seed){
			printf("seed:%d\n", cur_seed);
			prev_seed = cur_seed;
		}else{
			return 0;
		}
		++cur_pos;
	}
	return 0;
}
