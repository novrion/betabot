#pragma once
#include "__def_enum_macros.h"
#include "bitboard.h"


const u64 not_a_file = 18374403900871474942ULL;
const u64 not_h_file = 9187201950435737471ULL;
const u64 not_ab_file = 18229723555195321596ULL;
const u64 not_gh_file = 4557430888798830399ULL;

const int bishop_relevant_bits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

const int rook_relevant_bits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

void init_magic_numbers();
void _init_magic_numbers();
u64 find_magic_number(int square, int relevant_bits, u64 bishop);

unsigned int get_random_u32_number();
u64 get_random_u64_number();
u64 generate_magic_number();

void _init_leaper_attacks(u64 pawn_attacks[2][64], u64 knight_attacks[64], u64 king_attacks[64]);

u64 generate_pawn_attacks(int square, int side);
u64 generate_knight_attacks(int square);
u64 generate_king_attacks(int square);

u64 generate_bishop_attacks(int square);
u64 generate_rook_attacks(int square);


u64 generate_bishop_attacks_on_the_fly(int square, u64 block);
u64 generate_rook_attacks_on_the_fly(int square, u64 block);

//u64 set_occupancy(u64 attacks, int bits_in_mask, int index);
u64 set_occupancy(int index, int bits_in_mask, u64 attack_mask);