#pragma once
#include "magic.h"



void init_attacks();


static inline u64 get_bishop_attacks(int square, u64 occupancy);
static inline u64 get_rook_attacks(int square, u64 occupancy);
static inline u64 get_queen_attacks(int square, u64 occupancy);