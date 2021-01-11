#include <stdbool.h>
#include "utester.h"


int main()
{
    u_enable_logging("logfile.txt");
    u_assert("Debería salir este mensaje\n", false, "Test false");
    u_assert("No debería salir este mensaje", true, "Test true");
    u_disable_logging();
}