#pragma once

#include <stdio.h>

/**
 * Stop the execution if assertion is false and show details
 * @param assert the assertion to check
 * @param message the message to display in error case
 */
extern void fatal(int assert, const char message[], int status);
