#include "Log.h"

int main() {
	Log::Initialise("Example.txt");
	Log::Debug("YOU CAN'T READ THIS, THIS DOESN'T GET DUMPED");

	Log::SetThreshold(Log::DEBUG);

	Log::Debug("Hello...");
	Log::Info("Is it me you're looking for?");
	Log::Warn("I can see it in your eyes, I can see it in your smile...");
	Log::Error("You're all I ever wanted...");
	Log::Fatal("I love you");
	return 0;
}