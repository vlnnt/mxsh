#pragma once
#ifndef SHELL_H
#define SHELL_H
#define SPACE_BYTETOGB 9.31 * pow(10, -10)
#define FILE_SIZE 0.977 * pow(10, -3)

#include "IShell.h"

class Shell : public IShell {
public:
	Shell();
	void Init(string& cmd, string& path) override;
	void ls()                            override;
	void pwd()                           override;
	void localtime()                     override;
	void systemtime()                    override;
	void clear()                         override;
	void quit()                          override;
	void menu()                          override;
	void help()                          override;
	void cd(string& args)                override;
	void mkdir(string& args)             override;
	void touch(string& args)             override;
	void space(string& args)             override;
	void rm(string& args)                override;
	void fs(string& args)                override;

private:
	enum class shcmd {

		help, ls, pwd,
		localtime, systemtime,
		clear, quit, cd,
		mkdir, touch,
		space, rm, fs
	};

	map<string, shcmd> _mapshcmd;

private:
	SYSTEMTIME _localtime;
	SYSTEMTIME _systemtime;
	HANDLE _hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO _csbi;
	DWORD _chCount;
	DWORD _cellCount;
	COORD _startCoords = {0,0};
	TCHAR _infoBuf[MAX_PATH];
	DWORD _bufCharCount;

private:
	vector<string> _welcome = {

		"                                 .__             .__   .__",
		"  _____  _____   ___  ___  ______|  |__    ____  |  |  |  | ",
		" /     \u005C \u005C__  \u005C  \u005C  \u005C/  / /  ___/|  |  \u005C _/ __ \u005C |  |  |  |  ",
		"|  Y Y  \u005C / __ \u005C_ >    <  \u005C___ \u005C |   Y  \u005C\u005C  ___/ |  |__|  |__ ",
		"|__|_|  /(____  //__/\u005C_ \u005C/____  >|___|  / \u005C___  >|____/|____/ ",
		"      \u005C/      \u005C/       \u005C/     \u005C/      \u005C/      \u005C/              "
	};

	vector<string> _existcmd = {

		"cd", "ls", "mkdir",
		"pwd", "touch", "help",
		"localtime", "systemtime",
		"quit", "clear", "space",
		"rm", "fs"
	};
};

#endif // !SHELL_H