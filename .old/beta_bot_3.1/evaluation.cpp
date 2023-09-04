#include "beta.h"
using namespace std;
using namespace std::chrono;

/*HM<U64, int> w_knight_hash_map;
HM<U64, int> b_knight_hash_map;

HM<U64, int> w_bishop_hash_map;
HM<U64, int> b_bishop_hash_map;

HM<U64, int> w_rook_hash_map;
HM<U64, int> b_rook_hash_map;

HM<U64, int> w_queen_hash_map;
HM<U64, int> b_queen_hash_map;

HM<U64, int> w_king_hash_map;
HM<U64, int> b_king_hash_map;*/

// White Position
const int w_pawn_position[64] =
{
	90,  90,  90,  90,  90,  90,  90,  90,
	30,  30,  30,  40,  40,  30,  30,  30,
	20,  20,  20,  30,  30,  30,  20,  20,
	10,  10,  10,  20,  20,  10,  10,  10,
	 5,   5,  10,  20,  20,   5,   5,   5,
	 0,   0,   0,   5,   5,   0,   0,   0,
	 0,   0,   0, -10, -10,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
};

const int w_knight_position[64] =
{
	-5,   0,   0,   0,   0,   0,   0,  -5,
	-5,   0,   0,  10,  10,   0,   0,  -5,
	-5,   5,  20,  20,  20,  20,   5,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,   5,  20,  10,  10,  20,   5,  -5,
	-5,   0,   0,   0,   0,   0,   0,  -5,
	-5, -10,   0,   0,   0,   0, -10,  -5
};

const int w_bishop_position[64] =
{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,  10,  10,   0,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,  10,   0,   0,   0,   0,  10,   0,
	 0,  30,   0,   0,   0,   0,  30,   0,
	 0,   0, -10,   0,   0, -10,   0,   0

};

const int w_rook_position[64] =
{
	50,  50,  50,  50,  50,  50,  50,  50,
	50,  50,  50,  50,  50,  50,  50,  50,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,   0,  20,  20,   0,   0,   0

};

const int w_king_position[64] =
{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   5,   5,   5,   5,   0,   0,
	 0,   5,   5,  10,  10,   5,   5,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   0,   5,  10,  10,   5,   0,   0,
	 0,   5,   5,  -5,  -5,   0,   5,   0,
	 0,   0,   5,   0, -15,   0,  10,   0
};


// Black Position
const int b_pawn_position[64] =
{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0, -10, -10,   0,   0,   0,
	 0,   0,   0,   5,   5,   0,   0,   0,
	 5,   5,  10,  20,  20,   5,   5,   5,
	10,  10,  10,  20,  20,  10,  10,  10,
	20,  20,  20,  30,  30,  30,  20,  20,
	30,  30,  30,  40,  40,  30,  30,  30,
	90,  90,  90,  90,  90,  90,  90,  90
};

const int b_knight_position[64] =
{
	-5, -10,   0,   0,   0,   0, -10,  -5,
	-5,   0,   0,   0,   0,   0,   0,  -5,
	-5,   5,  20,  10,  10,  20,   5,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,   5,  20,  20,  20,  20,   5,  -5,
	-5,   0,   0,  10,  10,   0,   0,  -5,
	-5,   0,   0,   0,   0,   0,   0,  -5
};

const int b_bishop_position[64] =
{
	 0,   0, -10,   0,   0, -10,   0,   0,
	 0,  30,   0,   0,   0,   0,  30,   0,
	 0,  10,   0,   0,   0,   0,  10,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,   0,  10,  10,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0

};

const int b_rook_position[64] =
{
	 0,   0,   0,  20,  20,   0,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	50,  50,  50,  50,  50,  50,  50,  50,
	50,  50,  50,  50,  50,  50,  50,  50

};

const int b_king_position[64] =
{
	 0,   0,   5,   0, -15,   0,  10,   0,
	 0,   5,   5,  -5,  -5,   0,   5,   0,
	 0,   0,   5,  10,  10,   5,   0,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   5,   5,  10,  10,   5,   5,   0,
	 0,   0,   5,   5,   5,   5,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
};



/*const int position_matrix[64] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 2, -10, -10, 2, 1, 0,
	0, 2, 20, 4, 4, 20, 2, 0,
	0, 3, 10, 50, 50, 10, 3, 0,
	0, 3, 10, 50, 50, 10, 3, 0,
	0, 2, 20, 10, 10, 20, 2, 0,
	0, 1, 2, -10, -10, 2, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

bool comparator(U64 x, U64 y) {
	return (position_matrix[get_move_to(x)] + get_move_capture(x) * 100 > position_matrix[get_move_to(y)] + get_move_capture(y) * 100);
}



void init_knight_hash_maps() {

	// One Knight
	for (int square = 0; square < 64; ++square) {
		w_knight_hash_map.insert({ 1ULL << square, 3000 + w_knight_position[square] });
		b_knight_hash_map.insert({ 1ULL << square, 3000 + b_knight_position[square] });
	}

	// Two Knights
	for (int x = 0; x < 64; ++x) {
		for (int y = 0; y < 64; ++y) {
			if (!(w_knight_hash_map.contains(1ULL << x | 1ULL << y))) {
				w_knight_hash_map.insert({ 1ULL << x | 1ULL << y, 6000 + w_knight_position[x] + w_knight_position[y]});
				b_knight_hash_map.insert({ 1ULL << x | 1ULL << y, 6000 + b_knight_position[x] + b_knight_position[y]});
			}
		}
	}
}

void init_bishop_hash_maps() {

	// One Bishop
	for (int square = 0; square < 64; ++square) {
		w_bishop_hash_map.insert({ 1ULL << square, 3000 + w_bishop_position[square] });
		b_bishop_hash_map.insert({ 1ULL << square, 3000 + b_bishop_position[square] });
	}

	// Two Bishops
	for (int x = 0; x < 64; ++x) {
		for (int y = 0; y < 64; ++y) {
			if (!(w_knight_hash_map.contains(1ULL << x | 1ULL << y))) {
				w_bishop_hash_map.insert({ 1ULL << x | 1ULL << y, 6000 + w_bishop_position[x] + w_bishop_position[y] });
				b_bishop_hash_map.insert({ 1ULL << x | 1ULL << y, 6000 + b_bishop_position[x] + b_bishop_position[y] });
			}
		}
	}
}

void init_rook_hash_maps() {

	// One Rook
	for (int square = 0; square < 64; ++square) {
		w_rook_hash_map.insert({ 1ULL << square, 5000 + w_rook_position[square] });
		b_rook_hash_map.insert({ 1ULL << square, 5000 + b_rook_position[square] });
	}

	// Two Rooks
	for (int x = 0; x < 64; ++x) {
		for (int y = 0; y < 64; ++y) {
			if (!(w_rook_hash_map.contains(1ULL << x | 1ULL << y))) {
				w_rook_hash_map.insert({ 1ULL << x | 1ULL << y, 10000 + w_rook_position[x] + w_rook_position[y] });
				b_rook_hash_map.insert({ 1ULL << x | 1ULL << y, 10000 + b_rook_position[x] + b_rook_position[y] });
			}
		}
	}
}

void init_queen_hash_maps() {

	for (int square = 0; square < 64; ++square) {
		w_queen_hash_map.insert({ 1ULL << square, 9000 });
		b_queen_hash_map.insert({ 1ULL << square, 9000 });
	}
}

void init_king_hash_maps() {

	for (int square = 0; square < 64; ++square) {
		w_king_hash_map.insert({ 1ULL << square, 100000 + w_king_position[square] });
		b_king_hash_map.insert({ 1ULL << square, 100000 + b_king_position[square] });
	}
}


void init_evaluation_hash_maps() {

	init_knight_hash_maps();
	init_bishop_hash_maps();
	init_rook_hash_maps();
	init_queen_hash_maps();
	init_king_hash_maps();
}*/





inline int Evaluation(U64 b2[13]) {


	//
	duration<double> time;
	time_point<chrono::high_resolution_clock> start_time;
	start_time = high_resolution_clock::now();
	//


	// Even newer newer :D


	U64 all_block = _w_block(b2) | _b_block(b2);
	// King position (kings must exist for Evaluation to be called...)
	int evaluation = w_king_position[countr_zero(b2[6])] - b_king_position[countr_zero(b2[12])];
	
	

	for (int square = 0; square < 64; ++square) {

		if (!(all_block & 1ULL << square)) continue;

		else if (1ULL << square & b2[1]) evaluation += 1000 + w_pawn_position[square];
		else if (1ULL << square & b2[7]) evaluation -= 1000 + b_pawn_position[square];

		else if (1ULL << square & b2[2]) evaluation += 3000 + w_knight_position[square];
		else if (1ULL << square & b2[8]) evaluation -= 3000 + b_knight_position[square];

		else if (1ULL << square & b2[3]) evaluation += 3000 + w_bishop_position[square];
		else if (1ULL << square & b2[9]) evaluation -= 3000 + b_bishop_position[square];

		else if (1ULL << square & b2[4]) evaluation += 5000 + w_rook_position[square];
		else if (1ULL << square & b2[10]) evaluation -= 5000 + b_rook_position[square];

		else if (1ULL << square & b2[5]) evaluation += 9000;
		else if (1ULL << square & b2[11]) evaluation -= 9000;
	}
	
























	// Even newer
	// 
	// Fix so that it is different if promotion has happened

	//evaluation += w_knight_hash_map[b2[2]] + w_bishop_hash_map[b2[3]] + w_rook_hash_map[b2[4]] + w_queen_hash_map[b2[5]] + w_king_hash_map[b2[6]];
	/*evaluation += w_bishop_hash_map[b2[3]];
	evaluation += w_rook_hash_map[b2[4]];
	evaluation += w_queen_hash_map[b2[5]];
	evaluation += w_king_hash_map[b2[6]];*/

	//evaluation -= b_knight_hash_map[b2[8]] + b_bishop_hash_map[b2[9]] + b_rook_hash_map[b2[10]] + b_queen_hash_map[b2[11]] + b_king_hash_map[b2[12]];
	/*evaluation -= b_bishop_hash_map[b2[9]];
	evaluation -= b_rook_hash_map[b2[10]];
	evaluation -= b_queen_hash_map[b2[11]];
	evaluation -= b_king_hash_map[b2[12]];*/








	//U64 all_block = _w_block(b2) | _b_block(b2);


	// new
	/*for (int square = 0; square < 64; ++square) {

		if (!(1ULL << square & all_block)) continue;

		/*else if (1ULL << square & b2[1]) evaluation += 1000;
		else if (1ULL << square & b2[2]) evaluation += 3000;
		else if (1ULL << square & b2[3]) evaluation += 3000;
		else if (1ULL << square & b2[4]) evaluation += 5000;
		else if (1ULL << square & b2[5]) evaluation += 9000;
		else if (1ULL << square & b2[6]) evaluation += 100000;

		else if (1ULL << square & b2[7]) evaluation -= 1000;
		else if (1ULL << square & b2[8]) evaluation -= 3000;
		else if (1ULL << square & b2[9]) evaluation -= 3000;
		else if (1ULL << square & b2[10]) evaluation -= 5000;
		else if (1ULL << square & b2[11]) evaluation -= 9000;
		else if (1ULL << square & b2[12]) evaluation -= 100000;*/

		/*else if (1ULL << square & b2[1]) evaluation += 1000 + w_pawn_position[square];
		else if (1ULL << square & b2[2]) evaluation += 3000 + w_knight_position[square];
		else if (1ULL << square & b2[3]) evaluation += 3000 + w_bishop_position[square];
		else if (1ULL << square & b2[4]) evaluation += 5000 + w_rook_position[square];
		else if (1ULL << square & b2[5]) evaluation += 9000;
		//+ w_queen_position[square];
		else if (1ULL << square & b2[6]) evaluation += 100000 + w_king_position[square];

		else if (1ULL << square & b2[7]) evaluation -= 1000 + b_pawn_position[square];
		else if (1ULL << square & b2[8]) evaluation -= 3000 + b_knight_position[square];
		else if (1ULL << square & b2[9]) evaluation -= 3000 + b_bishop_position[square];
		else if (1ULL << square & b2[10]) evaluation -= 5000 + b_rook_position[square];
		else if (1ULL << square & b2[11]) evaluation -= 9000;
		//+b_queen_position[square];
		else if (1ULL << square & b2[12]) evaluation -= 100000 + b_king_position[square];
	}*/


	// worse
	/*for (int i = 0; i < 64; i++) {
		if (b2[1] & 1ULL << i) evaluation += 1000 + position_matrix[i];
	}

	for (int i = 0; i < 64; i++) {
		if (b2[2] & 1ULL << i) evaluation += 3000 + position_matrix[i];
	}

	for (int i = 0; i < 64; i++) {
		if (b2[3] & 1ULL << i) evaluation += 3000 + position_matrix[i];
	}

	for (int i = 0; i < 64; i++) {
		if (b2[4] & 1ULL << i) evaluation += 5000 + position_matrix[i];
	}

	for (int i = 0; i < 64; i++) {
		if (b2[5] & 1ULL << i) evaluation += 9000 + position_matrix[i];
	}

	for (int i = 0; i < 64; i++) {
		if (b2[6] & 1ULL << i) evaluation += 100000 + position_matrix[i];
	}



	for (int i = 0; i < 64; i++) {
		if (b2[7] & 1ULL << i) evaluation -= 1000 + position_matrix[i];
	}

	for (int i = 0; i < 64; i++) {
		if (b2[8] & 1ULL << i) evaluation -= 3000 + position_matrix[i];
	}

	for (int i = 0; i < 64; i++) {
		if (b2[9] & 1ULL << i) evaluation -= 3000 + position_matrix[i];
	}

	for (int i = 0; i < 64; i++) {
		if (b2[10] & 1ULL << i) evaluation -= 5000 + position_matrix[i];
	}

	for (int i = 0; i < 64; i++) {
		if (b2[11] & 1ULL << i) evaluation -= 9000 + position_matrix[i];
	}

	for (int i = 0; i < 64; i++) {
		if (b2[12] & 1ULL << i) evaluation -= 100000 + position_matrix[i];
	}*/

	// better
	/*evaluation += 1000 * popcount(b2[1]);
	evaluation += 3000 * popcount(b2[2]);
	evaluation += 3000 * popcount(b2[3]);
	evaluation += 5000 * popcount(b2[4]);
	evaluation += 9000 * popcount(b2[5]);
	if (b2[6]) evaluation += 100000;

	evaluation -= 1000 * popcount(b2[7]);
	evaluation -= 3000 * popcount(b2[8]);
	evaluation -= 3000 * popcount(b2[9]);
	evaluation -= 5000 * popcount(b2[10]);
	evaluation -= 9000 * popcount(b2[11]);
	if (b2[12]) evaluation -= 100000;*/

	/*U64 w_block = _w_block(b2);
	U64 b_block = _b_block(b2);

	for (int i = 0; i < 64; ++i) {
		if (1ULL << i & w_block) evaluation += position_matrix[i];
		if (1ULL << i & b_block) evaluation -= position_matrix[i];
	}*/

	//
	time = high_resolution_clock::now() - start_time;
	cout << time.count() << "\n";
	//

	//4e-07 -> 1e-06


	return evaluation;
}