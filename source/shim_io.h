#include <cstdint>
#include <cstdio>
#include <vector>
#include <mutex>
#include <condition_variable>

class shim_io {
public:
	shim_io( size_t max_buffer_size = 4096 );
	void execute();
	void shutdown();
	void read( std::vector<uint8_t>& dest_buffer );
	void write( std::vector<uint8_t>&& source_buffer );
	//void write( const std::vector<uint8_t>& source_buffer );

private:
	void process_input();
	void process_output();

	bool _is_good;
	size_t _max_buffer_size;

	std::mutex _input_buffer_mutex;
	std::vector<uint8_t> _input_buffer;

	std::mutex _output_buffer_mutex;
	std::condition_variable _output_buffer_condition;
	std::vector<uint8_t> _output_buffer;
};
