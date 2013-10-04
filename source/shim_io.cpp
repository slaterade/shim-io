#include "shim_io.h"
#include <thread>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

using namespace std;

shim_io::shim_io( size_t max_buffer_size )
	: _is_good( false )
	, _max_buffer_size( max_buffer_size ) {
}

void shim_io::execute() {

// Win32 needs some love for binary
#ifdef _WIN32
	if ( _setmode( _fileno( stdin ), _O_BINARY ) == -1 ) { return; }
	if ( _setmode( _fileno( stdout ), _O_BINARY ) == -1 ) { return; }
	_is_good = true;
#else
	freopen( NULL, "rb", stdin );
	freopen( NULL, "wb", stdout );
	_is_good = true;
#endif

	thread reader( [&] { this->process_input(); } );
	thread writer( [&] { this->process_output(); } );

	reader.join();
	writer.join();
}

void shim_io::shutdown() {
	_is_good = false;
}

void shim_io::read( std::vector<uint8_t>& dest_buffer ) {
	lock_guard<mutex> lock( _input_buffer_mutex );
	swap( _input_buffer, dest_buffer );
	_input_buffer.clear();
}

void shim_io::write( std::vector<uint8_t>&& source_buffer ) {
	lock_guard<mutex> lock( _output_buffer_mutex );
	swap( source_buffer, _output_buffer );
	_output_buffer_condition.notify_one();
}

//void shim_io::write( const std::vector<uint8_t>& source_buffer ) {
//
//}

void shim_io::process_input() {

}

void shim_io::process_output() {

}
