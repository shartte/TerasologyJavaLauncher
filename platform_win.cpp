
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Shlwapi.h>

#include "platform.h"
#include "log.h"

const char Platform::directorySep = '\\';

string Platform::getBaseDir() {
	char *exeFilenamePtr = NULL;

	if (_get_pgmptr(&exeFilenamePtr)) {
		// Unable to get our own exe name
		log() << "Unable to determine our own executable path.\n";
		return "";
	}

	string exeFilename(exeFilenamePtr);

	// Strip the executable filename
	auto lastOf = exeFilename.find_last_of("\\/");
	if (lastOf == string::npos) {
		// Odd filename retrieved (no path separator)
		log() << "Executable name does not contain a path separator: " << exeFilename << "\n";
		return "";
	}

	string baseDir = exeFilename.substr(0, lastOf);
	baseDir = ensureDirectorySep(baseDir);
	return baseDir;
}

void Platform::showError(const string &title, const string &message) {
	MessageBoxA(NULL, message.c_str(), title.c_str(), MB_ICONERROR | MB_OK);
}

bool Platform::fileExists(string path) {
	return PathFileExists(path.c_str()) == TRUE;
}