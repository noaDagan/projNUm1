#include "MyMain.h"
#include <string>
#include <string.h>

using namespace server_side;
using namespace std;

/**
 * The main function call to MyMain and delete in the end
 */
int main(int argc, char *argv[]) {
    boot::MyMain *myMain = new boot::MyMain();
    myMain->main(argc, argv);
    delete myMain;
    return 0;
};