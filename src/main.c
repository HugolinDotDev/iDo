#include "../include/task.h"

int main() {


    Date* date = Date_factory("12/10/2020");
    Date_debug(date);
    Date_destructor(date);

    return 0;
}
