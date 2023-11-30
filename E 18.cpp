#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 1024
#define LANE_SIZE 64
#define CAPACITY 512

uint64_t state[BLOCK_SIZE / LANE_SIZE];

void init_state() {
    for (int i = 0; i < CAPACITY / LANE_SIZE; i++) {
        state[i] = 0;
    }
}

void process_block(uint64_t block[BLOCK_SIZE / LANE_SIZE]) {
    for (int i = 0; i < BLOCK_SIZE / LANE_SIZE; i++) {
        state[i] ^= block[i];
    }

    for (int round = 0; round < 24; round++) {
        
        for (int i = 0; i < 5; i++) {
            uint64_t c[5];

            for (int j = 0; j < 5; j++) {
                c[j] = state[(i + 4 * j) % 5];
            }

            uint64_t d = 0;
            for (int j = 0; j < 5; j++) {
                d ^= c[j];
            }

            for (int j = 0; j < 5; j++) {
                state[(i + 4 * j) % 5] = (d << j) | (d >> (64 - j));
            }
        }

       
        uint64_t t = state[0];
        for (int i = 1; i < 5; i++) {
            state[i - 1] = state[i];
        }
        state[4] = t;

        t = state[0];
        t = (t << 1) | (t >> 63);
        state[0] = t;

      
        uint64_t a = state[0];
        uint64_t b = state[4];
        for (int i = 0; i < 5; i++) {
            state[(i + 1) % 5] ^= state[(i + 4) % 5];
        }
        state[0] = a;
        state[4] = b;

        for (int i = 0; i < 5; i++) {
            uint64_t a = state[i];
            uint64_t b = state[(i + 1) % 5];
            uint64_t c = state[(i + 2) % 5];
            state[i] = a ^ ((b << 1) | (b >> 63));
        }

        state[0] ^= round;
    }
}

int main() {
    init_state();

    
    int num_blocks = 0;
    while (1) {
        uint64_t block[BLOCK_SIZE / LANE_SIZE];
       
        process_block(block);

        bool all_lanes_nonzero = true;
        for (int i = 0; i < CAPACITY / LANE_SIZE; i++) {
            if (state[i] == 0) {
                all_lanes_nonzero = false;
                break;
            }
        }

        if (all_lanes_nonzero) {
            break;
        }

        num_blocks++;
    }

    printf("Number of blocks: %d\n", num_blocks);

    return 0;
}


