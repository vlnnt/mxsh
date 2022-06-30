#include "Shell.h"

int main() {

	setlocale(LC_ALL, "RU");
	string EnterCmd;
	string EnterPath;
	Shell shInstance;

	do {

		try {
			
			shInstance.menu();
			cin >> EnterCmd;
			shInstance.Init(EnterCmd, EnterPath);
		}

		catch (const std::exception& e) {
			cout << "Exception: " << e.what() << endl;
		}

	} while (true);

	return 0;
}