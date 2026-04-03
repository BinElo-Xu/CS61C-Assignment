#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t LSB = *reg & 1;
    uint16_t twoTh = (*reg & (1 << 2))>>2;
    uint16_t third = (*reg & (1 << 3))>>3;
    uint16_t fifth = (*reg & (1 << 5))>>5;
    uint16_t MSB = (((LSB ^ twoTh) ^ third) ^ fifth);
    *reg = ((*reg >> 1) | (MSB << 15));
}

