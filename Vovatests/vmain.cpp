#define CATCH_CONFIG_RUNNER
#include "vcatch.hpp"

	int main(int argc, char* argv[]) {
		using std::endl;
		using std::cout;
		cout <<
			"\nWelcome to the homework Wet 1 Data structures tests"
			"\nThe tests were written by: Vova Parakhin."
			"\n\n------Passing those tests won't"
			" guarantee you a good grade------\nBut they might get you closer"
			",make some tests yourself to be sure.\n\n";
		cout << "You can change w/e you want in the file itself"
			" but make sure \nto contact me if you want to upload";
		cout << " \'upgraded version\' of the file.\n" << endl;

		cout << "              _                                                \n"
				"             | |                                               \n"
				"             | |===( )   //////                                \n"
				"             |_|   |||  | o o|                                 \n"
				"                    ||| ( c  )                  ____           \n"
				"                     ||| \\= /                  ||   \\_       \n"
				"                      ||||||                   ||     |        \n"
				"                      ||||||                ...||__/|-\"       \n"
				"                      ||||||             __|________|__        \n"
				"                        |||             |______________|       \n"
				"                        |||             |    ENTER     |       \n"
				"                        |||             |______________|       \n"
				"                        |||             || ||      || ||       \n"
				"                        |||             || ||      || ||       \n"
				"------------------------|||-------------||-||------||-||-------\n"
				"                        |__>            || ||      || ||       \n"
				"                                                               \n"
				"                                                               \n"
				"\033[1;31m            hit ENTER to continue             \033[0m\n";
		getchar();
		int result = Catch::Session().run(argc, argv);
		return result;
	}