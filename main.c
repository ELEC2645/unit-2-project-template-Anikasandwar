// ELEC2645 Unit 2 Project Template
// Command Line Application Menu Handling Code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"

/* Prototypes mirroring the C++ version */
static void main_menu(void);            /* runs in the main loop */
static void print_main_menu(void);      /* output the main menu description */
static int  get_user_input(void);       /* get a valid integer menu choice */
static void select_menu_item(int input);/* run code based on user's choice */
static void go_back_to_main(void);      /* wait for 'b'/'B' to continue */
static int  is_integer(const char *s);  /* validate integer string */

int main(void)
{
    for(;;) {
        main_menu();
    }
    return 0;
}

static void main_menu(void)
{
    print_main_menu();
    {
        int input = get_user_input();
        select_menu_item(input);
    }
}

static int get_user_input(void)
{
    enum { MENU_ITEMS = 7 };   /* 1..7 = items, 7 = Exit */
    char buf[128];
    int valid_input = 0;
    int value = 0;

    do {
        printf("\nSelect item: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            puts("\nInput error. Exiting.");
            exit(1);
        }

        buf[strcspn(buf, "\r\n")] = '\0'; /* strip newline */

        if (!is_integer(buf)) {
            printf("Enter an integer!\n");
            valid_input = 0;
        } else {
            value = (int)strtol(buf, NULL, 10);
            if (value >= 1 && value <= MENU_ITEMS) {
                valid_input = 1;
            } else {
                printf("Invalid menu item!\n");
                valid_input = 0;
            }
        }
    } while (!valid_input);

    return value;
}

static void select_menu_item(int input)
{
    switch (input) {
        case 1:
            menu_item_1();
            go_back_to_main();
            break;

        case 2:
            menu_item_2();
            go_back_to_main();
            break;

        case 3:
            menu_item_3();
            go_back_to_main();
            break;

        case 4:
            menu_item_4();
            go_back_to_main();
            break;

        case 5:
            //menu_item_5();
            go_back_to_main();
            break;

        case 6:
            printf("Bye!Thank you for using the program! \n");
            exit(0);

        default:
            printf("Invalid choice!\n");
            break;
    }
}

static void print_main_menu(void)
{
    printf("\n----------- Main Menu -----------\n");
    printf("\t1. Resistor Network Analysis\n");
    printf("\t2. Voltage/Power/Current Calculations\n");
    printf("\t3. RC Circuit Analytics\n");
    printf("\t4. Engineering Unit Converter\n");
    printf("\t5. Basic Circuit Theory Help\n");
    printf("\t6. Exit\n");
    printf("--------------------------------\n");
}

static void go_back_to_main(void)
{
    char buf[64];
    do {
        printf("\nEnter 'b' or 'B' to go back to main menu: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            puts("\nInput error. Exiting.");
            exit(1);
        }
        buf[strcspn(buf, "\r\n")] = '\0';
    } while (!(buf[0] == 'b' || buf[0] == 'B') || buf[1] != '\0');
}

static int is_integer(const char *s)
{
    if (!s || !*s) return 0;

    if (*s == '+' || *s == '-') s++;

    if (!isdigit((unsigned char)*s)) return 0;

    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}




 
