#pragma once
#include "__def_enum_macros.h"
#include "bitboard.h"



// Relevant bit counts
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


// File masks
const u64 not_a_file = 18374403900871474942ULL;
const u64 not_h_file = 9187201950435737471ULL;
const u64 not_ab_file = 18229723555195321596ULL;
const u64 not_gh_file = 4557430888798830399ULL;



u64 set_occupancy(int index, int bits_in_mask, u64 attack_mask);


void init_leaper_attacks(u64 pawn_attacks[2][64], u64 knight_attacks[64], u64 king_attacks[64]);
void init_slider_attacks(u64 bishop_magic_number[64], u64 rook_magic_number[64], u64 bishop_masks[64], u64 rook_masks[64], u64 bishop_attacks[64][512], u64 rook_attacks[64][4096], int bishop);


u64 mask_pawn_attacks(int square, int side);
u64 mask_knight_attacks(int square);
u64 mask_king_attacks(int square);
u64 mask_bishop_attacks(int square);
u64 mask_rook_attacks(int square);

u64 bishop_attacks_on_the_fly(int square, u64 block);
u64 rook_attacks_on_the_fly(int square, u64 block);