#include "shim_io.h"
#include <thread>

using namespace std;

int main() {

	shim_io io;
	thread io_thread( [&] { io.execute(); } );

	std::vector<uint8_t> input_buffer;

	// echo back
	while ( true ) {
		io.read( input_buffer );
		if ( !input_buffer.empty() ) {
			vector<uint8_t> temp = input_buffer;
			io.write( temp );

			// killsignal
			if ( input_buffer[0] == 'Q' ) {
				io.shutdown();
				break;
			}
		}
	}

	io_thread.join();
	return 0;
}
