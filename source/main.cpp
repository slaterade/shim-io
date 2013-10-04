#include "shim_io.h"
#include <thread>

using namespace std;

int main() {
	shim_io io;
	thread io_thread( [&] { io.execute(); } );
	std::vector<uint8_t> input_buffer;

	while ( true ) {
		io.read( input_buffer );
		if ( !input_buffer.empty() ) {

			// just echo back the input
			io.write( input_buffer );

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
