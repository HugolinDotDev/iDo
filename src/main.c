#include "../include/cmd.h"

int main(int argc, char* argv[]) {
    int status = parse_cmd(argc, argv);

    return status;
}
