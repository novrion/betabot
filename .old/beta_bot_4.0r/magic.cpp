#include "magic.h"
using namespace std;



/*____________________ PSUEDO-RANDOM NUMBER GENERATOR ____________________*/

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

/*________________________________________________________________________*/





/*____________________ FIND MAGIC NUMBER ____________________*/

u64 find_magic_number(int square, int relevant_bits, int bishop) {

    u64 occupancies[4096];
    u64 attacks[4096];
    u64 used_attacks[4096];

    u64 attack_mask = bishop ? mask_bishop_attacks(square) : mask_rook_attacks(square);

    int occupancy_indicies = 1 << relevant_bits;


    for (int index = 0; index < occupancy_indicies; index++) {

        occupancies[index] = set_occupancy(index, relevant_bits, attack_mask);

        attacks[index] = bishop ? bishop_attacks_on_the_fly(square, occupancies[index]) :
            rook_attacks_on_the_fly(square, occupancies[index]);
    }

    for (int random_count = 0; random_count < 100000000; random_count++) {

        u64 magic_number = generate_magic_number();

        if (bit_count((attack_mask * magic_number) & 0xFF00000000000000) < 6) continue;

        memset(used_attacks, 0ULL, sizeof(used_attacks));

        int index, fail;

        for (index = 0, fail = 0; !fail && index < occupancy_indicies; index++) {

            int magic_index = (int)((occupancies[index] * magic_number) >> (64 - relevant_bits));

            if (used_attacks[magic_index] == 0ULL)
                used_attacks[magic_index] = attacks[index];

            else if (used_attacks[magic_index] != attacks[index])
                fail = 1;
        }

        if (!fail)
            return magic_number;
    }

    cout << "Couldn't generate magic number\n";
    return 0ULL;
}

/*___________________________________________________________*/





/*____________________ INITIALIZATION ____________________*/

void init_all(u64 rook_magic_numbers[64], u64 bishop_magic_numbers[64], u64 bishop_masks[64], u64 rook_masks[64], u64 bishop_attacks[64][512], u64 rook_attacks[64][4096], u64 pawn_attacks[2][64], u64 knight_attacks[64], u64 king_attacks[64]) {

    init_leaper_attacks(pawn_attacks, knight_attacks, king_attacks);

    init_slider_attacks(bishop_magic_numbers, rook_magic_numbers, bishop_masks, rook_masks, bishop_attacks, rook_attacks, 1);
    init_slider_attacks(bishop_magic_numbers, rook_magic_numbers, bishop_masks, rook_masks, bishop_attacks, rook_attacks, 0);


    //init_magic_numbers(rook_magic_numbers, bishop_magic_numbers);
}

void init_magic_numbers(u64 rook_magic_numbers[64], u64 bishop_magic_numbers[64]) {

    for (int square = 0; square < 64; square++)
        rook_magic_numbers[square] = find_magic_number(square, rook_relevant_bits[square], 0);


    for (int square = 0; square < 64; square++)
        bishop_magic_numbers[square] = find_magic_number(square, bishop_relevant_bits[square], 1);
}

/*________________________________________________________*/