#include "Log.h"

int main() {
	Log& log = Log::instance();
	log.initialise( "hello.txt" );

	PUSH_LOG_STACK;
	log.info( "Hello World" );
	POP_LOG_STACK;
	return 0;
}