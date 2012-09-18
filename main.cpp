#include "Log.h"

int function(int i) {
	PUSH_LOG_STACK;

	if(i == 5) {
		Log::fatal( "Dunno" );
		POP_LOG_STACK;
		return 0;
	}
	
	int retval = function(++i);
	
	POP_LOG_STACK;
	return retval;
}

int main() {
	Log::initialise( "hello.txt" );
	PUSH_LOG_STACK;

	function(0);

	POP_LOG_STACK;
	return 0;
}