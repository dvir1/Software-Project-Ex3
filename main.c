#include "Parser.h"
#include "SPBufferset.h"

int main(int argc, char **argv) {
	bool firstCommand = true; /* bool firstCommand - indicator of first command after choosing number of fixed cells */

	SP_BUFF_SET();

	if (argc>1)
		srand(atoi(argv[1]));

	while (true) {
		if (firstCommand)
			start();
		firstCommand = getCommand(firstCommand);
	}
	return 0;
}
