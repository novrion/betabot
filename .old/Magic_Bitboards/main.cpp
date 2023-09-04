/**********************************\
 ==================================

             didactic
       bitboard chess engine

                by

         code monkey king

 ==================================
\**********************************/

// system headers
#include <stdio.h>
#include <string.h>
#include <bit>
#include <iostream>

// define bitboard data type
#define u64 unsigned long long


// sides to move (colors)
enum { black, white };



// Pseudo-random number generator
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



// set/get/pop bit macros
#define set_bit(bitboard, square) (bitboard |= (1ull << square))
#define get_bit(bitboard, square) (bitboard & (1ull << square))
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (1ull << square) : 0)

// count bits within a bitboard
static inline int bit_count(u64 x) {

    x -= (x >> 1) & 0x5555555555555555;
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
    x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;

    return ((x * 0x0101010101010101) >> 56);
}








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

// rook magic numbers
u64 rook_magic_numbers[64] = {
    0x8a80104000800020ull,
    0x140002000100040ull,
    0x2801880a0017001ull,
    0x100081001000420ull,
    0x200020010080420ull,
    0x3001c0002010008ull,
    0x8480008002000100ull,
    0x2080088004402900ull,
    0x800098204000ull,
    0x2024401000200040ull,
    0x100802000801000ull,
    0x120800800801000ull,
    0x208808088000400ull,
    0x2802200800400ull,
    0x2200800100020080ull,
    0x801000060821100ull,
    0x80044006422000ull,
    0x100808020004000ull,
    0x12108a0010204200ull,
    0x140848010000802ull,
    0x481828014002800ull,
    0x8094004002004100ull,
    0x4010040010010802ull,
    0x20008806104ull,
    0x100400080208000ull,
    0x2040002120081000ull,
    0x21200680100081ull,
    0x20100080080080ull,
    0x2000a00200410ull,
    0x20080800400ull,
    0x80088400100102ull,
    0x80004600042881ull,
    0x4040008040800020ull,
    0x440003000200801ull,
    0x4200011004500ull,
    0x188020010100100ull,
    0x14800401802800ull,
    0x2080040080800200ull,
    0x124080204001001ull,
    0x200046502000484ull,
    0x480400080088020ull,
    0x1000422010034000ull,
    0x30200100110040ull,
    0x100021010009ull,
    0x2002080100110004ull,
    0x202008004008002ull,
    0x20020004010100ull,
    0x2048440040820001ull,
    0x101002200408200ull,
    0x40802000401080ull,
    0x4008142004410100ull,
    0x2060820c0120200ull,
    0x1001004080100ull,
    0x20c020080040080ull,
    0x2935610830022400ull,
    0x44440041009200ull,
    0x280001040802101ull,
    0x2100190040002085ull,
    0x80c0084100102001ull,
    0x4024081001000421ull,
    0x20030a0244872ull,
    0x12001008414402ull,
    0x2006104900a0804ull,
    0x1004081002402ull
};

// bishop magic numbers
u64 bishop_magic_numbers[64] = {
    0x40040844404084ull,
    0x2004208a004208ull,
    0x10190041080202ull,
    0x108060845042010ull,
    0x581104180800210ull,
    0x2112080446200010ull,
    0x1080820820060210ull,
    0x3c0808410220200ull,
    0x4050404440404ull,
    0x21001420088ull,
    0x24d0080801082102ull,
    0x1020a0a020400ull,
    0x40308200402ull,
    0x4011002100800ull,
    0x401484104104005ull,
    0x801010402020200ull,
    0x400210c3880100ull,
    0x404022024108200ull,
    0x810018200204102ull,
    0x4002801a02003ull,
    0x85040820080400ull,
    0x810102c808880400ull,
    0xe900410884800ull,
    0x8002020480840102ull,
    0x220200865090201ull,
    0x2010100a02021202ull,
    0x152048408022401ull,
    0x20080002081110ull,
    0x4001001021004000ull,
    0x800040400a011002ull,
    0xe4004081011002ull,
    0x1c004001012080ull,
    0x8004200962a00220ull,
    0x8422100208500202ull,
    0x2000402200300c08ull,
    0x8646020080080080ull,
    0x80020a0200100808ull,
    0x2010004880111000ull,
    0x623000a080011400ull,
    0x42008c0340209202ull,
    0x209188240001000ull,
    0x400408a884001800ull,
    0x110400a6080400ull,
    0x1840060a44020800ull,
    0x90080104000041ull,
    0x201011000808101ull,
    0x1a2208080504f080ull,
    0x8012020600211212ull,
    0x500861011240000ull,
    0x180806108200800ull,
    0x4000020e01040044ull,
    0x300000261044000aull,
    0x802241102020002ull,
    0x20906061210001ull,
    0x5a84841004010310ull,
    0x4010801011c04ull,
    0xa010109502200ull,
    0x4a02012000ull,
    0x500201010098b028ull,
    0x8040002811040900ull,
    0x28000010020204ull,
    0x6000020202d0240ull,
    0x8918844842082200ull,
    0x4010011029020020ull
};

/*____________________ ATTACK TABLES ____________________*/

u64 pawn_attacks[2][64];
u64 knight_attacks[64];
u64 king_attacks[64];


u64 mask_pawn_attacks(int square, int side)
{
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
u64 mask_knight_attacks(int square)
{
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
u64 mask_king_attacks(int square)
{
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

u64 mask_bishop_attacks(int square)
{
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
u64 mask_rook_attacks(int square)
{
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



u64 bishop_attacks_on_the_fly(int square, u64 block)
{
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
u64 rook_attacks_on_the_fly(int square, u64 block)
{
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


void init_leapers_attacks()
{
    for (int square = 0; square < 64; square++)
    {
        pawn_attacks[white][square] = mask_pawn_attacks(square, white);
        pawn_attacks[black][square] = mask_pawn_attacks(square, black);

        knight_attacks[square] = mask_knight_attacks(square);

        king_attacks[square] = mask_king_attacks(square);
    }
}


u64 set_occupancy(int index, int bits_in_mask, u64 attack_mask)
{
    u64 occupancy = 0ull;

    for (int count = 0; count < bits_in_mask; count++)
    {
        int square = std::countr_zero(attack_mask);

        pop_bit(attack_mask, square);

        if (index & (1 << count))
            occupancy |= (1ull << square);
    }

    return occupancy;
}

/*_______________________________________________________*/










/*____________________ MAGIC NUMBERS ____________________*/

u64 find_magic_number(int square, int relevant_bits, int bishop)
{
    u64 occupancies[4096];
    u64 attacks[4096];
    u64 used_attacks[4096];

    u64 attack_mask = bishop ? mask_bishop_attacks(square) : mask_rook_attacks(square);

    int occupancy_indicies = 1 << relevant_bits;


    for (int index = 0; index < occupancy_indicies; index++)
    {
        occupancies[index] = set_occupancy(index, relevant_bits, attack_mask);

        attacks[index] = bishop ? bishop_attacks_on_the_fly(square, occupancies[index]) :
            rook_attacks_on_the_fly(square, occupancies[index]);
    }

    for (int random_count = 0; random_count < 100000000; random_count++)
    {
        u64 magic_number = generate_magic_number();

        if (bit_count((attack_mask * magic_number) & 0xFF00000000000000) < 6) continue;

        memset(used_attacks, 0ull, sizeof(used_attacks));

        int index, fail;

        for (index = 0, fail = 0; !fail && index < occupancy_indicies; index++)
        {
            int magic_index = (int)((occupancies[index] * magic_number) >> (64 - relevant_bits));

            if (used_attacks[magic_index] == 0ull)
                used_attacks[magic_index] = attacks[index];

            else if (used_attacks[magic_index] != attacks[index])
                fail = 1;
        }

        if (!fail)
            return magic_number;
    }

    printf("  magic number fails!\n");
    return 0ull;
}

void init_magic_numbers()
{
    for (int square = 0; square < 64; square++)
        rook_magic_numbers[square] = find_magic_number(square, rook_relevant_bits[square], 0);


    for (int square = 0; square < 64; square++)
        bishop_magic_numbers[square] = find_magic_number(square, bishop_relevant_bits[square], 1);
}

/*_______________________________________________________*/





// init all variables
void init_all()
{
    // init leaper pieces attacks
    init_leapers_attacks();

    // init magic numbers
    init_magic_numbers();
}







int main()
{
    // init all
    init_all();


    return 0;
}