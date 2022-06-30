#pragma once
#ifndef ISHELL_H
#define ISHELL_H

#include <boost/filesystem.hpp>
#include <iostream>
#include <string> 
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include <map>
#include <vector>

using namespace std;
using namespace boost;

class IShell {
public:
	virtual ~IShell()                             {};
	virtual void Init(string& cmd, string& path) = 0;
	virtual void ls()                            = 0;
	virtual void pwd()                           = 0;
	virtual void localtime()                     = 0;
	virtual void systemtime()                    = 0;
	virtual void clear()                         = 0;
	virtual void quit()                          = 0;
	virtual void menu()                          = 0;
	virtual void help()                          = 0;
	virtual void cd(string& args)                = 0;
	virtual void mkdir(string& args)             = 0;
	virtual void touch(string& args)             = 0;
	virtual void space(string& args)             = 0;
	virtual void rm(string& args)                = 0;
	virtual void fs(string& args)                = 0;
};

#endif // !ISHELL_H