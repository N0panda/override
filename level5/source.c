#include <string.h>
#include <stdio.h>

void    main()
{
    int     i = 0;
    char    buffer[0x64];

    fgets(buffer, 0x64, stdin);

    int len = strlen(buffer);
    while (i < len)
    {
        if (buffer[i] > 0x40 && buffer[i] <= 0x5a)
            buffer[i] += 0x20;
        i++;
    }
    printf(buffer);
}