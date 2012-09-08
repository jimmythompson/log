#include "Log.h"

int function(int i) {
	Log& log = Log::instance();
	PUSH_LOG_STACK;
	if(i == 5) {
		log.error( "Dunno" );
		POP_LOG_STACK;
		return 0;
	}
	int retval = function(++i);
	POP_LOG_STACK;
	return retval;
}

int main() {
	Log& log = Log::instance();
	log.initialise( "hello.txt" );
	PUSH_LOG_STACK;

	function(0);

	POP_LOG_STACK;
	return 0;
}