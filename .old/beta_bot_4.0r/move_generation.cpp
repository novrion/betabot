#include "move_generation.h"
using namespace std;



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

u64 pawn_attacks[2][64];
u64 knight_attacks[64];
u64 king_attacks[64];


u64 bishop_masks[64];
u64 rook_masks[64];

u64 bishop_attacks[64][512];
u64 rook_attacks[64][4096];



void init_attacks() {

    init_all(rook_magic_numbers, bishop_magic_numbers, bishop_masks, rook_masks, bishop_attacks, rook_attacks, pawn_attacks, knight_attacks, king_attacks);
}



void generate_move(u64 moves[100], Board& b, int side) {

    int source, target;
    u64 bitboard;

    u64 w_block = _w_block(b.bb);
    u64 b_block = _b_block(b.bb);


    for (int piece = P; piece <= k; ++piece) {

        bitboard = b.bb[piece];

        if (side) {

            if (piece == P) {

                while (bitboard) {

                    source = countr_zero(bitboard);
                    target = source - 8;

                    if (!(target < 0) && !get_bit(w_block | b_block, target)) {

                        // Add Move here...


                        if (source >= 48 && source <= 55) {

                            // Double pawn move
                            if (!get_bit(w_block | b_block, target - 8)) {

                            }

                        }

                        else if

                        
                    }

                    pop_bit(bitboard, source);
                }
            }
        }


        else {

        }
    }
}



static inline u64 get_bishop_attacks(int square, u64 occupancy) {

	occupancy &= bishop_masks[square];
    occupancy *= bishop_magic_numbers[square];
    occupancy >>= 64 - bishop_relevant_bits[square];


    return bishop_attacks[square][occupancy];
}

static inline u64 get_rook_attacks(int square, u64 occupancy) {

    occupancy &= rook_masks[square];
    occupancy *= rook_magic_numbers[square];
    occupancy >>= 64 - rook_relevant_bits[square];


    return rook_attacks[square][occupancy];
}

static inline u64 get_queen_attacks(int square, u64 occupancy) {

    u64 queen_attacks = 0ULL;

    u64 bishop_occupancy = occupancy;
    u64 rook_occupancy = occupancy;


    bishop_occupancy &= bishop_masks[square];
    bishop_occupancy *= bishop_magic_numbers[square];
    bishop_occupancy >>= 64 - bishop_relevant_bits[square];

    queen_attacks = bishop_attacks[square][bishop_occupancy];


    rook_occupancy &= rook_masks[square];
    rook_occupancy *= rook_magic_numbers[square];
    rook_occupancy >>= 64 - rook_relevant_bits[square];

    queen_attacks |= rook_attacks[square][rook_occupancy];


    return queen_attacks;
}