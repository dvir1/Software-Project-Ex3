#include "ParserUnitTest.h"

int parserTest() {
	bool firstCommand = true; /* bool firstCommand - indicator of first command after choosing number of fixed cells */

	SP_BUFF_SET();


	while(true) {
		if (firstCommand)
			start();
		firstCommand = getCommand(firstCommand);
	}
    return 0;
}
