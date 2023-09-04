#include "negamax.h"

using namespace std;
using namespace std::chrono;



inline void GetMoveTargets(Board& b, U64 moves[100]) {

    if (GET_MOVE_PIECE(moves[0]) < 7) {

        for (int i = 0; i < moves[99]; ++i) {

            int target = GET_MOVE_TARGET(moves[i]);

            for (int j = 7; j < 13; ++j) {

                if (b.bb[j] & (1ULL << target)) {

                    RESET_MOVE_CAPTURE(moves[i]);
                    SET_MOVE_CAPTURE(moves[i], j);

                    break;
                }
            }
        }
    }

    else {

        for (int i = 0; i < moves[99]; ++i) {

            int target = GET_MOVE_TARGET(moves[i]);

            for (int j = 1; j < 7; ++j) {

                if (b.bb[j] & (1ULL << target)) {

                    RESET_MOVE_CAPTURE(moves[i]);
                    SET_MOVE_CAPTURE(moves[i], j);

                    break;
                }
            }
        }
    }
}

inline void OrderMoves(Board& b, U64 moves[100]) {

    sort(moves, moves + moves[99], [](const U64 a, const U64 b) {return (GET_MOVE_CAPTURE(a)) > (GET_MOVE_CAPTURE(b)); });
    GetMoveTargets(b, moves);

    sort(moves, moves + moves[99], \
        [](const U64 a, const U64 b) {return kMVVLVA[GET_MOVE_PIECE(a) - 1][GET_MOVE_CAPTURE(a) - 1] > kMVVLVA[GET_MOVE_PIECE(b) - 1][GET_MOVE_CAPTURE(b) - 1]; });
}



void IterativeDeepening(Board& b, const bool kSide, const double kMaxTime, int& evaluation_out, U64& move_out) {

    pair<int, U64> search_data;

    for (int depth = 1; depth < 256; ++depth) {

        duration<double> time;
        time_point<high_resolution_clock> start_time = high_resolution_clock::now();

        search_data = LayerOneNegaMax(b, depth, kSide, kMaxTime);

        time = high_resolution_clock::now() - start_time;


        if (!(search_data.second == kTimeFlag)) {

            evaluation_out = search_data.first;
            move_out = search_data.second;


            // Interface
            cout << depth << " ";

            SetConsoleTextAttribute(hConsole, 14);
            cout << "[ ";

            SetConsoleTextAttribute(hConsole, 12);
            cout << time.count();

            SetConsoleTextAttribute(hConsole, 14);
            cout << " ]   ";

            SetConsoleTextAttribute(hConsole, 15);
        }


        if (search_data.second == kTimeFlag || time.count() > 0.2 * kMaxTime) return;

        if (time.count() < kMaxTime / 100) ++depth;
    }
}

inline pair<int, U64> LayerOneNegaMax(Board& b, const int depth, const bool side, const double kMaxTime) {

    duration<double> time;
    time_point<high_resolution_clock> start_time = high_resolution_clock::now();

    int alpha = -999999;
    int beta = 999999;
    U64 best_move;
    U64 moves[100];
    moves[99] = 0;

    GenerateMoves(b.bb, moves, side);

    sort(moves, moves + moves[99], [](const U64 a, const U64 b) {return (GET_MOVE_CAPTURE(a)) > (GET_MOVE_CAPTURE(b)); });
    //GetMoveTargets(b, moves);
    //sort(moves, moves + moves[99], \
    []( const U64 a, const U64 b ) {return kMVVLVA[GET_MOVE_PIECE(a) - 1][GET_MOVE_CAPTURE(a) - 1] > kMVVLVA[GET_MOVE_PIECE(b) - 1][GET_MOVE_CAPTURE(b) - 1]; } );


    Board b_copy;

    for (int i = 0; i < moves[99]; ++i) {

        if (GET_MOVE_CAPTURE(moves[i]) == 12 || GET_MOVE_CAPTURE(moves[i]) == 6) return { (100000 + depth), moves[i] };

        b_copy = b;
        MakeMove(b_copy.bb, moves[i], side);

        int score = -NegaMax(b_copy, depth - 1, !side, -beta, -alpha);

        if (score > alpha) {
            alpha = score;
            best_move = moves[i];
        }

        if ((time = high_resolution_clock::now() - start_time).count() > kMaxTime) return { 0, kTimeFlag };
    }

    return { alpha, best_move };
}

inline int NegaMax(Board& b, const int depth, const bool side, int alpha, int beta) {

    if (depth == 0) return Quiescence(b, 4, side, alpha, beta);

    // Null Move Heuristic
    if (depth >= 3) {

        Board b_copy = b;
        int eval = -NegaMax(b_copy, depth - 1 - kR, !side, -beta, -beta + 1);
        if (eval >= beta) return beta;
    }

    U64 moves[100];
    moves[99] = 0;

    GenerateMoves(b.bb, moves, side);

    sort(moves, moves + moves[99], [](const U64 a, const U64 b) {return (GET_MOVE_CAPTURE(a)) > (GET_MOVE_CAPTURE(b)); });
    //GetMoveTargets(b, moves);
    //sort(moves, moves + moves[99], \
    []( const U64 a, const U64 b ) {return kMVVLVA[GET_MOVE_PIECE(a) - 1][GET_MOVE_CAPTURE(a) - 1] > kMVVLVA[GET_MOVE_PIECE(b) - 1][GET_MOVE_CAPTURE(b) - 1]; } );


    Board b_copy;

    for (int i = 0; i < moves[99]; ++i) {

        if (GET_MOVE_CAPTURE(moves[i]) == 12 || GET_MOVE_CAPTURE(moves[i]) == 6) return (100000 + depth);

        b_copy = b;
        MakeMove(b_copy.bb, moves[i], side);

        int score = -NegaMax(b_copy, depth - 1, !side, -beta, -alpha);

        if (score > alpha) {
            alpha = score;

            if (score >= beta) {
                return beta;
            }
        }
    }

    return alpha;
}

inline int Quiescence(Board& b, const int depth, const bool side, int alpha, int beta) {

    if (depth == 0) return side ? Evaluate(b.bb) : -Evaluate(b.bb);

    int eval = side ? Evaluate(b.bb) : -Evaluate(b.bb);
    if (eval >= beta) return beta;
    if (eval > alpha) alpha = eval;

    U64 moves[100];
    moves[99] = 0;

    GenerateCaptures(b.bb, moves, side);

    //GetMoveTargets(b, moves);
    //sort(moves, moves + moves[99], \
    []( const U64 a, const U64 b ) {return kMVVLVA[GET_MOVE_PIECE(a) - 1][GET_MOVE_CAPTURE(a) - 1] > kMVVLVA[GET_MOVE_PIECE(b) - 1][GET_MOVE_CAPTURE(b) - 1]; } );


    Board b_copy;

    for (int i = 0; i < moves[99]; ++i) {

        if (GET_MOVE_CAPTURE(moves[i]) == 12 || GET_MOVE_CAPTURE(moves[i]) == 6) return (100000 + depth);

        b_copy = b;
        MakeMove(b_copy.bb, moves[i], side);

        int score = -Quiescence(b_copy, depth - 1, !side, -beta, -alpha);

        if (score > alpha) {
            alpha = score;

            if (score >= beta) {
                return beta;
            }
        }
    }

    return alpha;
}