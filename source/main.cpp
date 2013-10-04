#include "shim_io.h"
#include <thread>

using namespace std;

int main() {

	shim_io io;
	thread io_thread( [&] { io.execute(); } );


	io_thread.join();
	return 0;
}
