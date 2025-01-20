#include <iface.h>

int main()
{
    int err = -1;

    if (setup() < 0)
    {
        while (1);
    }

    if (lockFlash() < 0)
    {
        goto error;
    }

    while (1)
    {
        blink(1);
    }

    err = 0;
error:
    return err;
}
