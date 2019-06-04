#include <stdbool.h>
#include "Parser.h"
#include "SPBufferset.h"


int parserTest() {
	bool firstCommand = true; /* bool firstCommand - indicator of first command after choosing number of fixed cells */

	SP_BUFF_SET();


	start();
	while(true) {
		getCommand(firstCommand);
		firstCommand = false;
	}
    return 0;
}
