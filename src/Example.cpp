#include "../include/Log.h"

int main() {
	Log::Initialise("Example.txt");
	Log::Debug("YOU SHOULDN'T BE ABLE TO READ THIS, THIS DOESN'T GET WRITTEN");

	Log::SetThreshold( Log::LOG_TYPE_DEBUG );

	PUSH_LOG_STACK;

	Log::Debug("Hello...");
	Log::Info("Is it %s you're looking for?", "me");
	Log::Warn("I can see it in your eyes, I can see it in your smile...");
	Log::Error("You're all %s ever wanted...", "I");
	Log::Fatal("I love you");
	return 0;
}