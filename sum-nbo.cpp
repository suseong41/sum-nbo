#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
    FILE* fp[argc-1];
    uint32_t *tmp[argc-1];
    uint32_t o[argc-1];
    uint32_t sum = 0;

    for(int i=0; i<argc-1; i++){
        fp[i] = fopen(argv[i+1], "rb");
        if(fp[i] == NULL){
            printf("error");
            return -1;
        }

        tmp[i] = (uint32_t*)malloc(sizeof(uint32_t));
        if(tmp[i] == NULL){
            printf("malloc error");
        }
        fread(tmp[i], sizeof(uint32_t), 4, fp[i]);
        o[i] = ntohl(*tmp[i]);
        sum = sum + o[i];

        fclose(fp[i]);
        free(tmp[i]);
    }

    uint32_t hex_zero = 0x00000000;
    for(int i=0; i<argc-1; i++){
        if (i != argc-2){
            printf("%d(0x%08x) + ", o[i], o[i]|hex_zero);
        } else{
            printf("%d(0x%08x)  = ", o[i], o[i]|hex_zero);
        }
    }
    printf("%d(0x%08x)", sum, sum|hex_zero);
    return 0;
}
