#include <stdbool.h>
#include "Parser.h"
#include "SPBufferset.h"


int main() {
	SP_BUFF_SET();

	bool firstCommand = true;
	start();
	while(true) {
		getCommand(firstCommand);
		firstCommand = false;
	}
    return 0;
}
