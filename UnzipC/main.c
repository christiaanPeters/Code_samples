#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "resource_detector.h"
#include "unzip.h"

#define  STRING_LEN  255

static bool with_menu = true;

static int 
get_int (const char * message)
{
    char    line[STRING_LEN];
    int     value;

    if (with_menu == true)
    {
        printf ("%s", message);
    }
    if (fgets (line, sizeof(line), stdin) == NULL)
    {
        fprintf (stderr, "ERROR in fgets()\n");
    }
    sscanf (line, "%d", &value);

    return (value);
}

static void 
get_str (const char * message, char * str)
{
    char    line[STRING_LEN];

    if (with_menu == true)
    {
        printf ("%s", message);
    }
    if (fgets (line, sizeof(line), stdin) == NULL)
    {
        fprintf (stderr, "ERROR in fgets()\n");
    }
    sscanf (line, "%s", str);
}

extern int 
main (int argc, char * argv[])
{
    char    file_in[STRING_LEN];
    char    file_out[STRING_LEN];
    bool    quit = false;
    bool    result;
    int     choice;

    printf ("\n"
        "PRC - UnzipC (version 4)\n"
        "------------------------\n");

    if (argc != 1)
    {
        fprintf (stderr, "%s: argc=%d\n", argv[0], argc);
    }

    while (quit == false)
    {
        if (with_menu == true)
        {
            printf ("\n"
                "Menu\n"
                "===============\n"
                "[1] dump raw hex data\n"
                "[2] dump headers and text\n"
                "[3] unzip\n"
                "[4] test module 'history'\n"
                "[8] show/hide menu\n"
                "[9] quit\n\n");
        }
        choice = get_int ("choice: ");

        switch (choice)
        {
            case 1:
            case 2:
            case 3:
                get_str ("input file (compressed): ", file_in);
                get_str ("output file (text, pdf): ", file_out);

                switch (choice)
                {
                    case 1:
                        result = unzip_dump_hex (file_in, file_out);
                        break;
                    case 2:
                        result = unzip_dump_header_and_text (file_in, file_out);
                        break;
                    case 3:
                        result = unzip_lz77 (file_in, file_out);
                        break;
                }
                if (result == false)
                {
                    fprintf (stderr, "Operation %d ('%s' -> '%s') not successful\n",
                            choice, file_in, file_out);
                }

                break;
            case 4:
                history_test ();
                break;
            case 8:
                if (with_menu == true)
                {
                    with_menu = false;
                    printf ("printing of MENU is diabled\n");
                }
                else
                {
                    // printing enabled
                    with_menu = true;
                }
                break;
            case 9:
                quit = true;
                break;
            default:
                printf ("invalid choice: %d\n", choice);
                break;
        }
    }

    return (0);
}

