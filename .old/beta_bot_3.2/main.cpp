#include "beta.h"


int main() {

	Board b;
	_init_all(b);


	double max_search_time = 4.0;
	__play_bot__(b, max_search_time);




	return 0;
}