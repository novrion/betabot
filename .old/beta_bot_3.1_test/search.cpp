#include "beta.h"
using namespace std;
using namespace std::chrono;

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


const int position[12][64] = {

	{
	90,  90,  90,  90,  90,  90,  90,  90,
	30,  30,  30,  40,  40,  30,  30,  30,
	20,  20,  20,  30,  30,  30,  20,  20,
	10,  10,  10,  20,  20,  10,  10,  10,
	 5,   5,  10,  20,  20,   5,   5,   5,
	 0,   0,   0,   5,   5,   0,   0,   0,
	 0,   0,   0, -10, -10,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
	},


	{
	-5,   0,   0,   0,   0,   0,   0,  -5,
	-5,   0,   0,  10,  10,   0,   0,  -5,
	-5,   5,  20,  20,  20,  20,   5,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,   5,  20,  10,  10,  20,   5,  -5,
	-5,   0,   0,   0,   0,   0,   0,  -5,
	-5, -10,   0,   0,   0,   0, -10,  -5
	},


	{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,  10,  10,   0,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,  10,   0,   0,   0,   0,  10,   0,
	 0,  30,   0,   0,   0,   0,  30,   0,
	 0,   0, -10,   0,   0, -10,   0,   0
	},


	{
	50,  50,  50,  50,  50,  50,  50,  50,
	50,  50,  50,  50,  50,  50,  50,  50,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,   0,  20,  20,   0,   0,   0
	},


	{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
	},


	{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   5,   5,   5,   5,   0,   0,
	 0,   5,   5,  10,  10,   5,   5,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   0,   5,  10,  10,   5,   0,   0,
	 0,   5,   5,  -5,  -5,   0,   5,   0,
	 0,   0,   5,   0, -15,   0,  10,   0
	},










	{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0, -10, -10,   0,   0,   0,
	 0,   0,   0,   5,   5,   0,   0,   0,
	 5,   5,  10,  20,  20,   5,   5,   5,
	10,  10,  10,  20,  20,  10,  10,  10,
	20,  20,  20,  30,  30,  30,  20,  20,
	30,  30,  30,  40,  40,  30,  30,  30,
	90,  90,  90,  90,  90,  90,  90,  90
	},


	{
	-5, -10,   0,   0,   0,   0, -10,  -5,
	-5,   0,   0,   0,   0,   0,   0,  -5,
	-5,   5,  20,  10,  10,  20,   5,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,   5,  20,  20,  20,  20,   5,  -5,
	-5,   0,   0,  10,  10,   0,   0,  -5,
	-5,   0,   0,   0,   0,   0,   0,  -5
	},


	{
	 0,   0, -10,   0,   0, -10,   0,   0,
	 0,  30,   0,   0,   0,   0,  30,   0,
	 0,  10,   0,   0,   0,   0,  10,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,   0,  10,  10,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
	},


	{
	 0,   0,   0,  20,  20,   0,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	50,  50,  50,  50,  50,  50,  50,  50,
	50,  50,  50,  50,  50,  50,  50,  50
	},


	{
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
	},


	{
	 0,   0,   5,   0, -15,   0,  10,   0,
	 0,   5,   5,  -5,  -5,   0,   5,   0,
	 0,   0,   5,  10,  10,   5,   0,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   5,   5,  10,  10,   5,   5,   0,
	 0,   0,   5,   5,   5,   5,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
	}
};


const int material_score[13] = { 0, 1000, 3000, 3000, 5000, 9000, 100000, -1000, -3000, -3000, -5000, -9000, -100000 };


int evaluation(U64 bb[13]) {

	/*duration<double> time;
	time_point<high_resolution_clock> start_time = high_resolution_clock::now();*/

	//U64 all_block = _w_block(bb) | _b_block(bb);
	int evaluation = w_king_position[countr_zero(bb[6])] - b_king_position[countr_zero(bb[12])];


	/*--------------------------------------------------------------------------------*/
	/// 20+ mil n/s

	for (int board = 1; board < 13; ++board) {
		for (int square = 0; square < 64; ++square) {
			if (1ULL << square & bb[board]) {
				evaluation += material_score[board];
				//evaluation += w_pawn_position[square];
			}
		}
	}
	/*--------------------------------------------------------------------------------*/




	/*--------------------------------------------------------------------------------*/
	/// 1 mil n/s

	/*for (int board = 1; board < 6; ++board) {
		for (int square = 0; square < 64; ++square) {
			if (1ULL << square && bb[board]) evaluation += material_score[board];
		}
	}

	for (int board = 7; board < 12; ++board) {
		for (int square = 0; square < 64; ++square) {
			if (1ULL << square && bb[board]) evaluation += material_score[board];
		}
	}*/
	/*--------------------------------------------------------------------------------*/



	//for (int board = 1; board < 13; ++board) {
	//	for (int square = 0; square < 64; ++square) {
	//		if (1ULL << square & bb[board]) {
	//			evaluation += material_score[board];
	//			//evaluation += w_pawn_position[square];
	//		}

	//		//if (1ULL << square & bb[board]) evaluation += material_score[board];
	//	}
	//}


	/*for (int square = 0; square < 64; ++square) {

		if (!(all_block & 1ULL << square)) continue;

		else if (1ULL << square & bb[1]) evaluation += 1000 + w_pawn_position[square];
		else if (1ULL << square & bb[7]) evaluation -= 1000 + b_pawn_position[square];

		else if (1ULL << square & bb[2]) evaluation += 3000 + w_knight_position[square];
		else if (1ULL << square & bb[8]) evaluation -= 3000 + b_knight_position[square];

		else if (1ULL << square & bb[3]) evaluation += 3000 + w_bishop_position[square];
		else if (1ULL << square & bb[9]) evaluation -= 3000 + b_bishop_position[square];

		else if (1ULL << square & bb[4]) evaluation += 5000 + w_rook_position[square];
		else if (1ULL << square & bb[10]) evaluation -= 5000 + b_rook_position[square];

		else if (1ULL << square & bb[5]) evaluation += 9000;
		else if (1ULL << square & bb[11]) evaluation -= 9000;
	}*/

	return evaluation;
}

//int minimax(U64 b2[13], int depth, int colour) {
//
//	if (!depth) {
//		//duration<double> time;
//		//time_point<high_resolution_clock> start_time = high_resolution_clock::now();
//
//		//int x = evaluation(b2);
//		//cout << (time = high_resolution_clock::now() - start_time).count() << "\n";
//
//		return 1;
//	}
//
//	int evaluation = 0;
//
//	vector<U64> moves;
//	gen_moves(b2, colour, moves);
//	//sort(moves.begin(), moves.end());
//
//
//	if (colour) {
//
//		for (int i = moves.size() - 1; i > -1 ; i--) {
//
//			make_move(b2, moves[i], colour);
//			evaluation += minimax(b2, depth - 1, 0);
//			undo_move(b2, moves[i], colour);
//		}
//
//		return evaluation;
//	}
//
//
//	else {
//
//		for (int i = moves.size() - 1; i > -1; i--) {
//
//			make_move(b2, moves[i], colour);
//			evaluation += minimax(b2, depth - 1, 1);
//			undo_move(b2, moves[i], colour);
//		}
//
//		return evaluation;
//	}
//}

U64 minimax(Board& b, int depth, int colour) {

	if (!depth) {
		//duration<double> time;
		//time_point<high_resolution_clock> start_time = high_resolution_clock::now();

		//int x = evaluation(b.b2);
		//cout << (time = high_resolution_clock::now() - start_time).count() << "\n";

		return 1;
	}

	U64 evaluation = 0;

	U64 moves[100];
	moves[99] = 0;
	gen_moves(b.b2, colour, moves);
	//sort(moves.begin(), moves.end());


	if (colour) {

		for (int i = 0; i < moves[99]; ++i) {

			Board b_copy = b;

			make_move(b.b2, moves[i], colour);
			evaluation += minimax(b, depth - 1, 0);

			b = b_copy;
		}

		return evaluation;
	}


	else {

		for (int i = 0; i < moves[99]; ++i) {

			Board b_copy = b;

			make_move(b.b2, moves[i], colour);
			evaluation += minimax(b, depth - 1, 1);

			b = b_copy;
		}

		return evaluation;
	}
}