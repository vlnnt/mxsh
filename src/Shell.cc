#include "Shell.h"

Shell::Shell() : _localtime{}, _systemtime{}, _hStdOut{}, _csbi{}, _chCount{}, _cellCount{}, _startCoords{}, _bufCharCount{MAX_PATH} {}

void Shell::Init(string& cmd, string& path) {

	_mapshcmd["ls"] = shcmd::ls;
	_mapshcmd["pwd"] = shcmd::pwd;
	_mapshcmd["localtime"] = shcmd::localtime;
	_mapshcmd["systemtime"] = shcmd::systemtime;
	_mapshcmd["clear"] = shcmd::clear;
	_mapshcmd["quit"] = shcmd::quit;
	_mapshcmd["cd"] = shcmd::cd;
	_mapshcmd["mkdir"] = shcmd::mkdir;
	_mapshcmd["touch"] = shcmd::touch;
	_mapshcmd["space"] = shcmd::space;
	_mapshcmd["rm"] = shcmd::rm;
	_mapshcmd["fs"] = shcmd::fs;

	switch (_mapshcmd[cmd]) {
	case shcmd::ls:          ls(); break;
	case shcmd::pwd:         pwd(); break;
	case shcmd::localtime:   localtime(); break;
	case shcmd::systemtime:  systemtime(); break;
	case shcmd::clear:       clear(); break;
	case shcmd::quit:        quit(); break;
	case shcmd::cd:          cin >> path; cd(path); break;
	case shcmd::mkdir:       cin >> path; mkdir(path); break;
	case shcmd::touch:       cin >> path; touch(path); break;
	case shcmd::space:       cin >> path; space(path); break;
	case shcmd::rm:          cin >> path; rm(path); break;
	case shcmd::fs:          cin >> path; fs(path); break;
	}

	if (cmd == "help") help();
}

void Shell::ls() {
	filesystem::path pathname = filesystem::current_path();
	for (const auto& entry : filesystem::directory_iterator(pathname)) {
		cout << entry.path() << endl;
	}
}

void Shell::pwd() {
	cout << filesystem::current_path() << endl;
}

void Shell::localtime() {

	try {

		GetLocalTime(&_localtime);
		cout << "Local time is: " << _localtime.wHour << "h "
			<< _localtime.wMinute << "m " << _localtime.wSecond <<
			"s " << _localtime.wMilliseconds << "ms " << _localtime.wDay
			<< "/" << _localtime.wMonth << "/" << _localtime.wYear << endl;
	}

	catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl;
	}
}

void Shell::systemtime() {

	try {

		GetSystemTime(&_systemtime);
		cout << "System time is: " << _systemtime.wHour << "h "
			<< _systemtime.wMinute << "m " << _systemtime.wSecond <<
			"s " << _systemtime.wMilliseconds << "ms " << _systemtime.wDay
			<< "/" << _systemtime.wMonth << "/" << _systemtime.wYear << endl;
	}

	catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl;
	}
}

void Shell::clear() {

	try {

		_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (_hStdOut == INVALID_HANDLE_VALUE) { return; }
		if (!GetConsoleScreenBufferInfo(_hStdOut, &_csbi)) { return; }

		_cellCount = _csbi.dwSize.X * _csbi.dwSize.Y;

		if (!FillConsoleOutputCharacter(_hStdOut, (TCHAR)' ', _cellCount, _startCoords, &_chCount)) { return; }
		if (!FillConsoleOutputAttribute(_hStdOut, _csbi.wAttributes, _cellCount, _startCoords, &_chCount)) { return; }

		SetConsoleCursorPosition(_hStdOut, _startCoords);
	}

	catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl;
	}
}

void Shell::quit() {
	exit(0);
}

void Shell::cd(string& args) {
	filesystem::current_path(args);
}

void Shell::mkdir(string& args) {
	filesystem::path pathname = args;
	filesystem::create_directory(pathname);
}

void Shell::touch(string& args) {
	ofstream file(args);
	file.close();
}

void Shell::space(string& args) {
	filesystem::space_info space_struct = filesystem::space(args);
		cout << "Capacity: " << space_struct.capacity * SPACE_BYTETOGB << " GB" << endl
			<< "Free: " << space_struct.free * SPACE_BYTETOGB << " GB" << endl
			<< "Available: " << SPACE_BYTETOGB * space_struct.capacity - space_struct.free * SPACE_BYTETOGB << " GB" << '\n';
}

void Shell::rm(string& args) {
	filesystem::remove(args);
}

void Shell::fs(string& args) {
	cout << filesystem::file_size(args) * FILE_SIZE << " KB" << endl;
}

void Shell::menu() {
	GetComputerName(_infoBuf, &_bufCharCount);
	_tprintf(_infoBuf); printf(":~$ ");
}

void Shell::help() {
	for (const auto& i : _welcome) { cout << i << '\n'; }
	cout << endl << '\t' << "   Built-in commands in the maxshell:" << '\n' << '\n';
	for (const auto& i : _existcmd) { cout << "\t\t\t" << i << endl; }
}