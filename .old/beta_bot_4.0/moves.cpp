#include "moves.h"
#include <string.h>
#include <stdio.h>
using namespace std;


/*void _init_magic_numbers() {

	for (int square = 0; square < 64; ++square) {
		printf(" 0x%lluxULL\n", find_magic_number(square, bishop_relevant_bits[square], 1));
	}
}
u64 find_magic_number(int square, int relevant_bits, u64 bishop) {

	u64 occupancies[4096];
	u64 attacks[4096];
	u64 used_attacks[4096];

	u64 attack_mask = (bishop ? generate_bishop_attacks(square) : generate_rook_attacks(square));

	int occupancy_index = 1 << relevant_bits;

	for (int index = 0; index < occupancy_index; ++index) {

		occupancies[index] = set_occupancy(attack_mask, relevant_bits, index);
		attacks[index] = (bishop ? generate_bishop_attacks_on_the_fly(square, occupancies[index]) : generate_rook_attacks_on_the_fly(square, occupancies[index]));
	}

	for (int random_count = 0; random_count < 100000000; ++random_count) {

		u64 magic_number = generate_magic_number();

		if (bit_count((attack_mask * magic_number) * 0xFF00000000000000) < 6) continue;

		memset(used_attacks, 0ULL, sizeof(used_attacks));

		int index, fail;

		for (index = 0, fail = 0; !fail && index < occupancy_index; ++index) {

			int magic_index = (int)(occupancies[index] * magic_number) >> (64 - relevant_bits);

			if (used_attacks[magic_index] == 0ULL) used_attacks[magic_index] = attacks[index];
			else if (used_attacks[magic_index] != attacks[index]) fail = 1;
		}

		if (!fail) return magic_number;
	}

	cout << "Magic number unsuccessfully generated!\n";
}*/

u64 find_magic_number(int square, int relevant_bits, int bishop)
{
	// init occupancies
	u64 occupancies[4096];

	// init attack tables
	u64 attacks[4096];

	// init used attacks
	u64 used_attacks[4096];

	// init attack mask for a current piece
	u64 attack_mask = bishop ? generate_bishop_attacks(square) : generate_rook_attacks(square);

	// init occupancy indicies
	int occupancy_indicies = 1 << relevant_bits;

	// loop over occupancy indicies
	for (int index = 0; index < occupancy_indicies; index++)
	{
		// init occupancies
		occupancies[index] = set_occupancy(index, relevant_bits, attack_mask);

		// init attacks
		attacks[index] = bishop ? generate_bishop_attacks_on_the_fly(square, occupancies[index]) :
			generate_rook_attacks_on_the_fly(square, occupancies[index]);
	}

	// test magic numbers loop
	for (int random_count = 0; random_count < 100000000; random_count++)
	{
		// generate magic number candidate
		u64 magic_number = generate_magic_number();

		// skip inappropriate magic numbers
		if (bit_count((attack_mask * magic_number) & 0xFF00000000000000) < 6) continue;

		// init used attacks
		memset(used_attacks, 0ULL, sizeof(used_attacks));

		// init index & fail flag
		int index, fail;

		// test magic index loop
		for (index = 0, fail = 0; !fail && index < occupancy_indicies; index++)
		{
			// init magic index
			int magic_index = (int)((occupancies[index] * magic_number) >> (64 - relevant_bits));

			// if magic index works
			if (used_attacks[magic_index] == 0ULL)
				// init used attacks
				used_attacks[magic_index] = attacks[index];

			// otherwise
			else if (used_attacks[magic_index] != attacks[index])
				// magic index doesn't work
				fail = 1;
		}

		// if magic number works
		if (!fail)
			// return it
			return magic_number;
	}

	// if magic number doesn't work
	printf("  Magic number fails!\n");
	return 0ULL;
}

// init magic numbers
void init_magic_numbers()
{

	for (int square = 0; square < 64; square++) {
		printf(" 0x%llxULL\n", find_magic_number(square, rook_relevant_bits[square], 0));
	}

	cout << "\n\n\n\n\n";

	for (int square = 0; square < 64; square++) {
		printf(" 0x%llxULL\n", find_magic_number(square, bishop_relevant_bits[square], 1));
	}
}


unsigned int random_state = 1804289383;
unsigned int get_random_u32_number() {

	unsigned int number = random_state;

	// XOR shift algorithm
	number ^= number << 13;
	number ^= number >> 17;
	number ^= number << 5;

	// Update state
	random_state = number;


	return number;
}
u64 get_random_u64_number() {

	u64 n1, n2, n3, n4;

	// Random numbers slicing 16 bits from most significant bit
	n1 = (u64)(get_random_u32_number() & 0xFFFF);
	n2 = (u64)(get_random_u32_number() & 0xFFFF);
	n3 = (u64)(get_random_u32_number() & 0xFFFF);
	n4 = (u64)(get_random_u32_number() & 0xFFFF);


	return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}
u64 generate_magic_number() {

	return get_random_u64_number() & get_random_u64_number() & get_random_u64_number();
}


void _init_leaper_attacks(u64 pawn_attacks[2][64], u64 knight_attacks[64], u64 king_attacks[64]) {

	for (int square = 0; square < 64; ++square) {

		pawn_attacks[white][square] = generate_pawn_attacks(square, white);
		pawn_attacks[black][square] = generate_pawn_attacks(square, black);

		knight_attacks[square] = generate_knight_attacks(square);

		king_attacks[square] = generate_king_attacks(square);
	}
}



u64 generate_pawn_attacks(int square, int side) {

	u64 bitboard = 1ULL << square;
	u64 attacks = 0ULL;

	if (side) {

		if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
		if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
	}

	else {

		if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
		if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);

	}


	return attacks;
}
u64 generate_knight_attacks(int square) {

	u64 bitboard = 1ULL << square;
	u64 attacks = 0ULL;

	if ((bitboard >> 17) & not_h_file) attacks |= (bitboard >> 17);
	if ((bitboard >> 15) & not_a_file) attacks |= (bitboard >> 15);
	if ((bitboard >> 10) & not_gh_file) attacks |= (bitboard >> 10);
	if ((bitboard >> 6) & not_ab_file) attacks |= (bitboard >> 6);
	if ((bitboard << 17) & not_a_file) attacks |= (bitboard << 17);
	if ((bitboard << 15) & not_h_file) attacks |= (bitboard << 15);
	if ((bitboard << 10) & not_ab_file) attacks |= (bitboard << 10);
	if ((bitboard << 6) & not_gh_file) attacks |= (bitboard << 6);


	return attacks;
}
u64 generate_king_attacks(int square) {

	u64 bitboard = 1ULL << square;
	u64 attacks = 0ULL;

	if (bitboard >> 8) attacks |= (bitboard >> 8);
	if (bitboard << 8) attacks |= (bitboard << 8);

	if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
	if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
	if ((bitboard >> 1) & not_h_file) attacks |= (bitboard >> 1);
	if ((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);
	if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
	if ((bitboard << 1) & not_a_file) attacks |= (bitboard << 1);


	return attacks;
}

u64 generate_bishop_attacks(int square) {

	u64 attacks = 0ULL;

	int r, f;

	int tr = square / 8;
	int tf = square % 8;

	for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++) attacks |= (1ULL << (r * 8 + f));
	for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++) attacks |= (1ULL << (r * 8 + f));
	for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--) attacks |= (1ULL << (r * 8 + f));
	for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; r--, f--) attacks |= (1ULL << (r * 8 + f));


	return attacks;
}
u64 generate_rook_attacks(int square) {

	u64 attacks = 0ULL;

	int r, f;

	int tr = square / 8;
	int tf = square % 8;

	for (r = tr + 1; r <= 6; r++) attacks |= (1ULL << (r * 8 + tf));
	for (r = tr - 1; r >= 1; r--) attacks |= (1ULL << (r * 8 + tf));
	for (f = tf + 1; f <= 6; f++) attacks |= (1ULL << (tr * 8 + f));
	for (f = tf - 1; f >= 1; f--) attacks |= (1ULL << (tr * 8 + f));


	return attacks;
}


u64 generate_bishop_attacks_on_the_fly(int square, u64 block) {

	u64 attacks = 0ULL;

	int r, f;

	int tr = square / 8;
	int tf = square % 8;


	for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++) {

		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block) break;
	}

	for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++) {

		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block) break;
	}

	for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--) {

		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block) break;
	}

	for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--) {

		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block) break;
	}


	return attacks;
}
u64 generate_rook_attacks_on_the_fly(int square, u64 block) {

	u64 attacks = 0ULL;

	int r, f;

	int tr = square / 8;
	int tf = square % 8;

	for (r = tr + 1; r <= 7; r++) {
		attacks |= (1ULL << (r * 8 + tf));
		if ((1ULL << (r * 8 + tf)) & block) break;
	}

	for (r = tr - 1; r >= 0; r--) {
		attacks |= (1ULL << (r * 8 + tf));
		if ((1ULL << (r * 8 + tf)) & block) break;
	}

	for (f = tf + 1; f <= 7; f++) {
		attacks |= (1ULL << (tr * 8 + f));
		if ((1ULL << (tr * 8 + f)) & block) break;
	}

	for (f = tf - 1; f >= 0; f--) {
		attacks |= (1ULL << (tr * 8 + f));
		if ((1ULL << (tr * 8 + f)) & block) break;
	}


	return attacks;
}



/*u64 set_occupancy(u64 attacks, int bits_in_mask, int index) {

	u64 occupancy = 0ULL;

	for (int count = 0; count < bits_in_mask; ++count) {

		int square = countr_zero(attacks);
		pop_bit(attacks, square);

		if (index & (1 << count))
			occupancy |= (1ULL << square);
	}


	return occupancy;
}*/
u64 set_occupancy(int index, int bits_in_mask, u64 attack_mask)
{
	// occupancy map
	u64 occupancy = 0ULL;

	// loop over the range of bits within attack mask
	for (int count = 0; count < bits_in_mask; count++)
	{
		// get LS1B index of attacks mask
		int square = countr_zero(attack_mask);

		// pop LS1B in attack map
		pop_bit(attack_mask, square);

		// make sure occupancy is on board
		if (index & (1 << count))
			// populate occupancy map
			occupancy |= (1ULL << square);
	}

	// return occupancy map
	return occupancy;
}