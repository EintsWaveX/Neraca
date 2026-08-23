#include <assert.h>             // Assertion for truth testing
#include <ctype.h>              // Characters typing methods
#include <errno.h>              // Error handling
#include <dirent.h>             // Working with directories and files
#include <fenv.h>               // File environment handling
#include <float.h>              // Float conversion (more spesific)
#include <limits.h>             // Limitations per data types
#include <math.h>               // Mathematical functions
#include <stdbool.h>            // Standard boolean values handling
#include <stddef.h>             // Standard definitions for certain types
#include <stdint.h>             // Standard integers handling (more spesific)
#include <stdio.h>              // Standard stream handling
#include <stdlib.h>             // Standard library (more spesific)
#include <signal.h>             // Signal handling for future better runtime experience
#include <string.h>             // String manipulation and handling
#include <time.h>               // Time conversion
#include <uchar.h>              // Character conversion (U type conversion)
#include <unistd.h>             // Giving POSIX syntaxes operating system API
#include <wchar.h>              // Wide character conversion (W type conversion)
#include <wctype.h>             // Wide character typing method (String type conversion)

// #include <gtk-4.0/gtk/gtk.h>    // GTK-4.0+ Application Implementation
#include <conio.h>              // Windows handling compatibility
// #include <raylib.h>             // Raylib library to display graphs and more
// #include <SDL2/SDL.h>           // SDL2 library to support more with Raylib
#include <windows.h>            // Windows header file (apps and notifications)

/*
DEFINE::FDBufferSIZE
Usage:  Used for setting a certain spesific FDBuffer for
        spesific variables that might have to work with
        more than just a basic variables (pointers,
        structs, and more).
*/
#define BUFSIZE07   128         // 2^7  FDBuffer size (min. defined)
#define BUFSIZE08   256         // 2^8  FDBuffer size
#define BUFSIZE09   512         // 2^9  FDBuffer size
#define BUFSIZE10   1024        // 2^10 FDBuffer size
#define BUFSIZE11   2048        // 2^11 FDBuffer size
#define BUFSIZE12   4096        // 2^12 FDBuffer size
#define BUFSIZE13   8192        // 2^13 FDBuffer size
#define BUFSIZE14   16384       // 2^14 FDBuffer size
#define BUFSIZE15   32768       // 2^15 FDBuffer size
#define BUFSIZE16   65536       // 2^16 FDBuffer size (max. defined)
#define LISTOFFUC   60          // (max FDBuffer for list of strings of chars about FUC)

/*
DEFINE::APPLANGUAGE
Usage:  Determining the whole application language that
        mostly the user have to interact with. Given two
        languages registered on the system, that is ENG
        for (English) and IND for (Indonesian).
*/
#define ENG "English"
#define IND "Bahasa Indonesia"

/*
DEFINE::ARROWKEYWORD
Usage:  For more safe-choice input session, so the user
        can't make any rousy inputs that can interrupt
        the whole core of the app functionality by some
        unexpected errors or bugs.
*/
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_RIGHT   77
#define KEY_LEFT    75
#define KEY_ENTER   '\r'

/*
DEFINE::DEFINITIVEHISTOGRAM
Usage:  Used for generating a histogram from (y -> x)
        because of the exhaustive printing if done in
        (x -> y) format.
*/
#define SQUARE_BAR "\u2B1C"

/*
DEFINE::ANSICOLORFONTMODE
Usage:  Creating a spesific colored font to highlight the
        ARROWKEYWORD defining session for helping the user
        to know spesifically the choice they're on while
        in the restricted input mode.
*/
#define ANSI_COLOR_RESET           "\x1b[0;0m"
#define ANSI_COLOR_DARKGRAY        "\x1b[0;30m"
#define ANSI_COLOR_RED             "\x1b[0;38;5;196m"
#define ANSI_COLOR_GREEN           "\x1b[0;38;5;82m"
#define ANSI_COLOR_YELLOW          "\x1b[0;38;5;220m"
#define ANSI_COLOR_BLUE            "\x1b[0;38;5;33m"
#define ANSI_COLOR_MAGENTA         "\x1b[0;38;5;207m"
#define ANSI_COLOR_PURPLE          "\x1b[0;38;5;93m"
#define ANSI_COLOR_CYAN            "\x1b[0;38;5;81m"
#define ANSI_COLOR_PINK            "\x1b[0;38;5;206m"
#define ANSI_COLOR_ORANGE          "\x1b[0;38;5;208m"
#define ANSI_COLOR_WHITE           "\x1b[0;37m"
#define ANSI_COLOR_LIGHTRESET      "\x1b[1;0m"
#define ANSI_COLOR_LIGHTGRAY       "\x1b[1;30m"
#define ANSI_COLOR_LIGHTRED        "\x1b[1;38;5;196m"
#define ANSI_COLOR_LIGHTGREEN      "\x1b[1;38;5;82m"
#define ANSI_COLOR_LIGHTYELLOW     "\x1b[1;38;5;220m"
#define ANSI_COLOR_LIGHTBLUE       "\x1b[1;38;5;33m"
#define ANSI_COLOR_LIGHTMAGENTA    "\x1b[1;38;5;207m"
#define ANSI_COLOR_LIGHTPURPLE     "\x1b[1;38;5;93m"
#define ANSI_COLOR_LIGHTCYAN       "\x1b[1;38;5;81m"
#define ANSI_COLOR_LIGHTWHITE      "\x1b[1;37m"
#define ANSI_COLOR_LIGHTORANGE     "\x1b[1;38;5;208m"
#define ANSI_COLOR_LIGHTPINK       "\x1b[1;38;5;206m"
#define ANSI_STYLE_BOLD            "\x1b[1m"
#define ANSI_STYLE_FAINT           "\x1b[2m"
#define ANSI_STYLE_ITALIC          "\x1b[3m"
#define ANSI_STYLE_UNDERLINE       "\x1b[4m"
#define ANSI_STYLE_BLINK           "\x1b[5m"
#define ANSI_STYLE_NEGATIVE        "\x1b[7m"
#define ANSI_STYLE_CROSSED         "\x1b[9m"

/* COLOR HIGHLIGHTING FOR MAIN MENU ONLY */
#define BRIGHTGREEN154             "\x1b[0;38;5;154m"
#define BRIGHTGREEN155             "\x1b[0;38;5;155m"
#define BRIGHTGREEN156             "\x1b[0;38;5;156m"
#define BRIGHTBLUE157              "\x1b[0;38;5;157m"
#define BRIGHTBLUE158              "\x1b[0;38;5;158m"
#define BRIGHTBLUE159              "\x1b[0;38;5;159m"

#define BRIGHTRED216               "\x1b[0;38;5;216m"
#define BRIGHTMAGENTA217           "\x1b[0;38;5;217m"
#define BRIGHTPURPLE218            "\x1b[0;38;5;218m"
#define BRIGHTPINK219              "\x1b[0;38;5;219m"

#define BRIGHTRED208               "\x1b[0;38;5;208m"
#define BRIGHTRED209               "\x1b[0;38;5;209m"
#define BRIGHTMAGENTA210           "\x1b[0;38;5;210m"
#define BRIGHTMAGENTA211           "\x1b[0;38;5;211m"
#define BRIGHTPURPLE212            "\x1b[0;38;5;212m"
#define BRIGHTPURPLE213            "\x1b[0;38;5;213m"

// ClearScreen() method, works for both Windows and UNIX.
void ClearScreen(void) {
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
#else
    #error "ERROR: Unsupported platform for performing clear screen!"
#endif
}

/* ERROR HANDLING METHOD */
// Working with various errors, mostly defined here as global variables

bool TruthConfirmation;
bool SKYRApplicationRunning = false;
size_t GlobalSKYRFMSARegisteredAccounts = 0, GlobalRegisteredMTR = 0, GlobalRegisteredBCAM = 0;
const char* UserApplicationLanguage;
const char* SOURCEFILENULLERROR = "SourceFileNotExists";
const char* DESTINATIONFILENULLERROR = "DestinationFileNotExists";
bool ARMNotificationEnabled_01 = false, ARMNotificationEnabled_02 = false, ARMNotificationEnabled_03 = false;
bool ALMNotificationEnabled_01 = false, ALMNotificationEnabled_02 = false;
bool ACMNotificationEnabled_01 = false, ACMNotificationEnabled_02 = false, ACMNotificationEnabled_03 = false;

/* ENCRYPTION KEY MUST NOT EVER BE CHANGED! */
/* ENCRYPTION KEY MUST NOT EVER BE CHANGED! */
/* ENCRYPTION KEY MUST NOT EVER BE CHANGED! */
const int EncryptionKey = 776853;
/* ENCRYPTION KEY MUST NOT EVER BE CHANGED! */
/* ENCRYPTION KEY MUST NOT EVER BE CHANGED! */
/* ENCRYPTION KEY MUST NOT EVER BE CHANGED! */

char FullName[BUFSIZE10], UserName[BUFSIZE07];
char ProfileSaveFileData[BUFSIZE07];

const char* ApplicationPresent       = "SKYR Corp. Foundation Inc., PRESENTS:\n";
const char* ApplicationTitle         = "SKYR Corp. :: Personal Financial Management System [CLI-Win32] Application\n";
const char* ApplicationVersion       = "SKYR Corp. :: @PRE-RELEASE V2.13.65.85.8102 [f887bc7] (March 08, 2024)\n";
const char* AppGuideOnUsageUDRL      = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t        "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:\t\t\t   Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[1][2][...][N - 1][N]: Auto-Enter Selection " ANSI_STYLE_ITALIC"(up to N-availability)\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT, [<]: Go LEFT\n"ANSI_COLOR_RESET;
const char* AppRegistrationUDRL      = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t\t\t\t       "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:    Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t\t       (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[1][2][3][4][5] | [6][7][8][9]: Auto-Enter Selection\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT " ANSI_STYLE_UNDERLINE"(Login Menu)"ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC", [<]: Go LEFT " ANSI_STYLE_UNDERLINE"(...)\n"ANSI_COLOR_RESET;
const char* AppLoginUDRL             = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t\t\t\t       "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:    Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t\t\t\t\t (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[1][2][3][4]: Auto-Enter Selection\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT " ANSI_STYLE_UNDERLINE"(Recovery Menu)"ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC", [<]: Go LEFT " ANSI_STYLE_UNDERLINE"(Registration Menu)\n"ANSI_COLOR_RESET;
const char* AppRecoveryUDRL          = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t\t\t\t       "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:    Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t\t\t\t\t (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[1][2][3][4]: Auto-Enter Selection\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT " ANSI_STYLE_UNDERLINE"(...)"ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC", [<]: Go LEFT " ANSI_STYLE_UNDERLINE"(Login Menu)\n"ANSI_COLOR_RESET;
const char* AppMainMenuUDRL          = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t\t\t\t       "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:    Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t\t\t\t   (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[1][2][3][4][5][6]: Auto-Enter Selection\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT " ANSI_STYLE_UNDERLINE"(Profile Manager)"ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC", [<]: Go LEFT " ANSI_STYLE_UNDERLINE"(...)\n"ANSI_COLOR_RESET;
const char* AppProfileManagerUDRL    = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t\t\t\t       "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:    Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t\t\t\t   (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[1][2][3] | [4][5]: Auto-Enter Selection\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT " ANSI_STYLE_UNDERLINE"(About Application)"ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC", [<]: Go LEFT " ANSI_STYLE_UNDERLINE"(Home Menu)\n"ANSI_COLOR_RESET;
const char* AppInformationsUDRL      = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t\t\t\t       "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:    Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t\t\t\t   (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[1][2][3][4][5][6]: Auto-Enter Selection\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT " ANSI_STYLE_UNDERLINE"(...)"ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC", [<]: Go LEFT " ANSI_STYLE_UNDERLINE"(Profile Manager)\n"ANSI_COLOR_RESET;
const char* AppFUCUI01UDRL           = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t\t\t\t       "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:    Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t\t       (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[A][B][C][D][E][F][G][H][I][J]: Auto-Enter Selection\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT " ANSI_STYLE_UNDERLINE"(Next Page; 2 of 6)"ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC", [<]: Go LEFT " ANSI_STYLE_UNDERLINE"(Previous Page; 6 of 6)\n"ANSI_COLOR_RESET;
const char* AppFUCUI02UDRL           = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t\t\t\t       "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:    Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t\t       (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[A][B][C][D][E][F][G][H][I][J]: Auto-Enter Selection\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT " ANSI_STYLE_UNDERLINE"(Next Page; 3 of 6)"ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC", [<]: Go LEFT " ANSI_STYLE_UNDERLINE"(Previous Page; 1 of 6)\n"ANSI_COLOR_RESET;
const char* AppFUCUI03UDRL           = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t\t\t\t       "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:    Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t\t       (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[A][B][C][D][E][F][G][H][I][J]: Auto-Enter Selection\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT " ANSI_STYLE_UNDERLINE"(Next Page; 4 of 6)"ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC", [<]: Go LEFT " ANSI_STYLE_UNDERLINE"(Previous Page; 2 of 6)\n"ANSI_COLOR_RESET;
const char* AppFUCUI04UDRL           = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t\t\t\t       "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:    Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t\t       (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[A][B][C][D][E][F][G][H][I][J]: Auto-Enter Selection\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT " ANSI_STYLE_UNDERLINE"(Next Page; 5 of 6)"ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC", [<]: Go LEFT " ANSI_STYLE_UNDERLINE"(Previous Page; 3 of 6)\n"ANSI_COLOR_RESET;
const char* AppFUCUI05UDRL           = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t\t\t\t       "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:    Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t\t       (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[A][B][C][D][E][F][G][H][I][J]: Auto-Enter Selection\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT " ANSI_STYLE_UNDERLINE"(Next Page; 6 of 6)"ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC", [<]: Go LEFT " ANSI_STYLE_UNDERLINE"(Previous Page; 4 of 6)\n"ANSI_COLOR_RESET;
const char* AppFUCUI06UDRL           = "\n\t   " ANSI_COLOR_LIGHTGREEN"[^]\t\t\t\t\t\t\t\t       "ANSI_COLOR_RESET BRIGHTGREEN156"[ENTER]:    Confirm Selection\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[>]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTGREEN"[v]"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"[<]\t\t\t       (Direct) "ANSI_COLOR_RESET BRIGHTBLUE159"[A][B][C][D][E][F][G][H][I][J]: Auto-Enter Selection\n\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"[^]: Go UP, [v]: Go DOWN, "ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC"[>]: Go RIGHT " ANSI_STYLE_UNDERLINE"(Next Page; 1 of 6)"ANSI_COLOR_RESET ANSI_COLOR_CYAN ANSI_STYLE_ITALIC", [<]: Go LEFT " ANSI_STYLE_UNDERLINE"(Previous Page; 5 of 6)\n"ANSI_COLOR_RESET;

const char* AppRegisterUI            = "Section: Profile Account :: Registration Menu\n";
const char* AppLanguageUI            = "Section: Language Option :: First Starter - Choosing a Language\n";
const char* AppLoginUI               = "Section: Profile Account :: Login Menu\n";
const char* AppRecoveryUI            = "Section: Profile Account :: Recovery Menu\n";
const char* AppMainMenuUI            = "Section: Home (Dashbord) :: Main Menu of The Application Features\n";
const char* AppProfileManagerUI      = "Section: Home (Accounts) :: Main Menu of The Profile Account(s) Manager\n";
const char* AppInformationsUI        = "Section: Home (About UI) :: Main Menu of The Latest Informations and About Application\n";
const char* AppFUCUI01               = "Section: F.U. Category 1 :: Financial Uses Category || Page: 1 of 6\n";
const char* AppFUCUI02               = "Section: F.U. Category 2 :: Financial Uses Category || Page: 2 of 6\n";
const char* AppFUCUI03               = "Section: F.U. Category 3 :: Financial Uses Category || Page: 3 of 6\n";
const char* AppFUCUI04               = "Section: F.U. Category 4 :: Financial Uses Category || Page: 4 of 6\n";
const char* AppFUCUI05               = "Section: F.U. Category 5 :: Financial Uses Category || Page: 5 of 6\n";
const char* AppFUCUI06               = "Section: F.U. Category 6 :: Financial Uses Category || Page: 6 of 6\n";
const char* AppFeature01             = "Section: App Feature: 01 :: Financial Moneytory Transaction(s) Registration\n";
const char* AppFeature02             = "Section: App Feature: 02 :: Financial Moneytory Transaction(s) Grouping per Category\n";
const char* AppFeature03             = "Section: App Feature: 03 :: Financial Moneytoring and Budget(s) Creations\n";
const char* AppFeature04             = "Section: App Feature: 04 :: Financial Moneytory Filtering and Searched History\n";
const char* AppFeature05             = "Section: App Feature: 05 :: Financial Moneytoring for Reminders and Notifications\n";
const char* AppFeature06             = "Section: App Feature: 06 :: Financial Moneytoring with Data and 2D Graphical Visualizations\n";

const char *FinancialUsesCategoryListing[LISTOFFUC] = {
    "Account Receiveable", "Additional Income", "Allowance", "Electricity, Water, and Gas", "House and Appartment Rent", "Household", "Insurance", "Mobile and Data", "Handheld Electric Device", "TV and Internet",
    "Bonus", "Business Profit", "Classes and Workshops", "School Supplies", "Tuition Fee", "Children and Family Needs", "Parents and Family Needs", "Daily Meal", "Snacks and Drinks", "Gifting",
    "Charity", "Groceries", "Doctor and Hospital", "Medicines", "Personal Care", "Books", "Dining Out", "Games", "Hobby", "Movies and Music",
    "Pets", "Incomings", "Interests", "Investments Withdrawal", "Loan Disbursements", "Car Installments", "Credit Card", "Home Mortgage", "Refunds", "Reimbursements",
    "Salary", "Investments", "Savings", "Fashions", "Gadget and Electronics", "Home Appliances", "Sport Activities", "Sport Equipments", "Daily Transportations", "Gasolines",
    "Parking and Toll Fee", "Vehicle Maintenance", "Attractions and Tours", "Hotel and Villa", "Transport on Vacations", "Cash Withdrawal", "Cost and Taxes", "Send to Business", "Send to Personal", "Top Up e-Wallets and/or Cards"
};

const char *ArrowKeyChoiceDialogModes[10] = {
    "Trial Mode", "Truth Confirmation",
    "Language Mode", "Account Register Mode", "Account Login Mode",
    "Main Menu", "Help Menu", "About Menu", "Recovery Menu", "Settings Menu"
};
char *MessagesShown_ArrowKeyChoiceDialog[BUFSIZE10] = {0};

void ErrorHandling(const char* ErrorType, const char* ErrorSource) {
    if (strcmp(ErrorType, SOURCEFILENULLERROR) == 0) {
        fprintf(stderr, "Unable to open the source file named '%s'!\n           > Make sure you have the file names '%s' ready to be opened,\n      and not some empty folder or none specified beforehand.\n\nErrorCode: %s", ErrorSource, ErrorSource, ErrorType);
        getchar();
    } if (strcmp(ErrorType, DESTINATIONFILENULLERROR) == 0) {
        fprintf(stderr, "Unable to create the destination file named '%s'!\n    > This maybe an error that occured if there's an error for having\n      permission to make and write to a file, error in naming the file,\n      and many more. Try to troubleshoot for the errors and try again!\n\nErrorCode: %s", ErrorSource, ErrorType);
        getchar();
    }
}

/* Program's CORE Functions Separator */
// NOTE: All structures and global variables below are initialized
//       ONLY for the CORE function, naming as: AccountRegistrationMenu.

struct AccountRegistrationMenuInputs {
    char FirstName[BUFSIZE07], LastName[BUFSIZE07], Email[BUFSIZE07], Username[BUFSIZE07], Password[BUFSIZE07], CSPFinancialAMEncryptionKey[BUFSIZE07];
    char DateOfBirth[BUFSIZE07], AgeOnPresent[BUFSIZE07], PhoneNumber[BUFSIZE07], Sex[BUFSIZE07], CareerProfiling[BUFSIZE07], AboutMe[BUFSIZE10];
    char AttendingCollege[BUFSIZE07], CompanyWorking[BUFSIZE07], DegreeIn[BUFSIZE07];
    char HiddenPasswordShown[BUFSIZE07];
} ARMInputs;
bool FN = false, LN = false, E = false, U = false, P = false;
bool B = false, A = false, PN = false, S = false, CPR = false, PD = false;
bool AC = false, CW = false, DI = false;
bool ARMShowThePassword = false;
int ARMSelected = 0, FlagARM = false;

struct AccountLoginMenuInputs {
    char Email[BUFSIZE07], PhoneNumber[BUFSIZE07], Username[BUFSIZE07], Password[BUFSIZE07];
    char HiddenPasswordShown[BUFSIZE07];
} ALMInputs;
char FirstName[BUFSIZE07], LastName[BUFSIZE07], Email[BUFSIZE07], Username[BUFSIZE07], Password[BUFSIZE07], DateOfBirth[BUFSIZE07], AgeOnPresent[BUFSIZE07], PhoneNumber[BUFSIZE07], Sex[BUFSIZE07];
char *ShowFirstName, *ShowLastName, *ShowEmail, *ShowUsername, *ShowPassword, *ShowDateOfBirth, *ShowAgeOnPresent, *ShowPhoneNumber, *ShowSex;
int GlobalAccount = 0, ALMSelected = 0, FlagALM = false;
bool LE = false, LPN = false, LU = false, LP = false;
bool ALMShowThePassword = false;

struct AccountRecoveryMenuInputs {
    char Email[BUFSIZE07], PhoneNumber[BUFSIZE07], Username[BUFSIZE07], Password[BUFSIZE07];
    char HiddenPasswordShown[BUFSIZE07];
} ACMInputs;
bool CE = false, CPN = false, CU = false, CP = false;
bool EmptyCE = false, EmptyCPN = false, EmptyCU = false, EmptyCP = false;
bool FlagCE = false, FlagCPN = false, FlagCU = false, FlagCP = false;
bool VisitedCE = false, VisitedCPN = false, VisitedCU = false, VisitedCP = false;
bool ACMShowThePassword = false;
bool FlagACM = false;
int ACMSelected = 0, AllEmpty = 0;

struct SaveFilesTxtName {
    char FileNames[BUFSIZE10];
} SaveFilesTxtName[BUFSIZE10];
signed int FilePathNameTraversalCounter = 0, CountSavedFiles = 0;
signed int Accounts = 0, SignedInAccountNo = 0;

// struct MainMenuApplicationFeaturesInputs {

// } MMAFInputs[BUFSIZE10];
int MMAFSelected = 0;

// struct MainMenuProfileManagerInputs {

// } MMPMInputs[BUFSIZE10];
int MMPMSelected = 0;

// struct HelpMenuInputs {

// } HMInputs[BUFSIZE10];
int HMSelected = 0;

struct MoneytoryTransactionsRegister {
    char *BankCharge[BUFSIZE10], *BillPayment[BUFSIZE10];
    char *CardRefund[BUFSIZE10], *CardTopUp[BUFSIZE10], *CashWithdrawal[BUFSIZE10], *CurrencyExchange[BUFSIZE10];
    char *FeePayment[BUFSIZE10], *IncomingCash[BUFSIZE10], *IncomingTransfer[BUFSIZE10], *Interest[BUFSIZE10];
    char *Loan[BUFSIZE10], *Loans[BUFSIZE10];
    char *OutgoingTransfer[BUFSIZE10];
    char *PaymentWithCard[BUFSIZE10], *PrepaidTopUp[BUFSIZE10], *PrincipalPlacement[BUFSIZE10], PrincipalRepayment[BUFSIZE10];
    char *QRPayment[BUFSIZE10], *QRPaymentRefund[BUFSIZE10];
    char *Reversal[BUFSIZE10];
    char *SalaryPayroll[BUFSIZE10], *SavingsWithdrawal[BUFSIZE10];
    char *TaxOnInterest[BUFSIZE10], *TopUpSavingsBalances[BUFSIZE10], *WalletCashback[BUFSIZE10];

    char TransactionDate[BUFSIZE07], IncomeOrExpenses[BUFSIZE07], TotalSpentMoney[BUFSIZE07];
    char FinancialUsesCategory[BUFSIZE07], MonthlyTotalBalance[BUFSIZE07], TransactionDescription[BUFSIZE07];
    char LocalTimeTransactionMade[BUFSIZE07];
} MTRInputs[BUFSIZE07];
int F1Selected = 0;
bool FlagF1MTR = false;
bool TBD = false, IOE = false, TSM = false, FUC = false, MTB = false, TD = false;

struct MoneytoryGroupingPerCategory {
    char *AccountReceiveable[BUFSIZE10], *AdditionalIncome[BUFSIZE10], *Allowance[BUFSIZE10];
    char *ElectricityWaterGas[BUFSIZE10], *HouseAndAppartmentRent[BUFSIZE10], *Household[BUFSIZE10], *Insurance[BUFSIZE10], *MobileAndData[BUFSIZE10], *HandheldElectricDevice[BUFSIZE10], *TVAndInternet[BUFSIZE10];
    char *Bonus[BUFSIZE10], *BusinessProfit[BUFSIZE10];
    char *ClassesAndWorkshops[BUFSIZE10], *SchoolSupplies[BUFSIZE10], *TuitionFee[BUFSIZE10];
    char *ChildrenFamilyNeeds[BUFSIZE10], *ParentFamilyNeeds[BUFSIZE10];
    char *DailyMeal[BUFSIZE10], *SnacksAndDrinks[BUFSIZE10];
    char *Gifting[BUFSIZE10], *Charity[BUFSIZE10];
    char *Groceries[BUFSIZE10];
    char *DoctorAndHospital[BUFSIZE10], *Medicines[BUFSIZE10], *PersonalCare[BUFSIZE10];
    char *Books[BUFSIZE10], *DiningOut[BUFSIZE10], *Games[BUFSIZE10], *Hobby[BUFSIZE10], *MoviesAndMusic[BUFSIZE10], *Pets[BUFSIZE10];
    char *Incomings[BUFSIZE10], *Interests[BUFSIZE10], *InvestmentsWithdrawal[BUFSIZE10];
    char *LoanDisbursements[BUFSIZE10];
    char *CarInstallments[BUFSIZE10], *CreditCard[BUFSIZE10], *HomeMortgage[BUFSIZE10];
    char *Refunds[BUFSIZE10], *Reimbursements[BUFSIZE10];
    char *Salary[BUFSIZE10];
    char *Investments[BUFSIZE10], *Savings[BUFSIZE10];
    char *Fashions[BUFSIZE10], *GadgetAndElectronics[BUFSIZE10], *HomeAppliances[BUFSIZE10];
    char *SportActivities[BUFSIZE10], *SportEquipments[BUFSIZE10];
    char *DailyTransportations[BUFSIZE10], *Gasolines[BUFSIZE10], *ParkingAndTollFee[BUFSIZE10], *VehicleMaintenance[BUFSIZE10];
    char *AttractionsAndTours[BUFSIZE10], *HotelAndVilla[BUFSIZE10], *TransportsOnVacations[BUFSIZE10];
    char *CashWithdrawal[BUFSIZE10], *CostAndTaxes[BUFSIZE10], *SendToBusiness[BUFSIZE10], *SendToPersonal[BUFSIZE10], *TopUpEWalletCards[BUFSIZE10];
    
    char *UncategorizedByUsers[BUFSIZE10];
    char *Others[BUFSIZE10];
} MGPCInputs[BUFSIZE07];
int F2Selected = 0;

struct BudgetCreationAndMonitoring {
    char MonthlyOrYearly[BUFSIZE07];
    char BudgetCreationPerMonth[BUFSIZE07], BudgetCreationPerYear[BUFSIZE07];
    char MonthlyFinancialCreationCategory[BUFSIZE07], YearlyFinancialCreationCategory[BUFSIZE07];
    char MonthlyLimitBudgetCreation[BUFSIZE07], YearlyLimitBudgetCreation[BUFSIZE07];
    char MonthlyBudgetCreationDescription[BUFSIZE07], YearlyBudgetCreationDescription[BUFSIZE07];
    char MonthlyBudgetTargeting[BUFSIZE07], YearlyBudgetTargeting[BUFSIZE07];
    bool AlwaysCheckForReminders;
} BCAMInputs[BUFSIZE07];
int F3Selected = 0;
bool MOR = false, BCC = false, BCL = false, BCT = false, BCD = false;
bool FlagF3BCAM = false;

struct FilterSearchingData {
    /*
    For now, there's no need to filter by the structures, since all the variables
    are already handled by the core program itself in a function call:
        > void DecryptTxtFile(const char*, bool, int, char ReadDecryptedKeyString[BUFSIZE16]);

    Need some future and furthermore updates on this structure, since basically the
    filtering and searching methods are just implemented already while decrypting the
    text file for more safety over valueable personal data.

    How this feature works, is just really open a text file that needs to be filtered
    or searched by letters or words or categories and more, even when being filtered
    is already unconciously being sorted along the way, and can be searched through
    anywhere, especially when the reading system is line-by-line, and the whole file
    being read without any filtering if the user wants to.
    */
    
    char FileName[BUFSIZE07];
} FSDInputs[BUFSIZE07];
int F4Selected = 0;
    
struct ReminderAndSetNotifications {
    /*
    For now, there's no need to filter by the structures, since all the variables
    are already handled by the core program itself in a function call:
        > int InfoMessageBox_OK(const char*, const char*);
        > int QuestionMessageBox_YESNOCANCEL(const char*, const char*);
        > int WarningMessageBox_CANCELTRYCONTINUE(const char*, const char*);
        > int ErrorMessageBox_OKCANCEL(const char*, const char*);

    1. The first one is an INFO MESSAGE BOX that appears with the tile of the info
    popup notification window and the messages written in, and it provides only
    a single OK button.
    2. The second one is a QUESTION MESSAGE BOX that appears with the title of the
    question popup notification window and the messages written in, and it provides
    three buttons, respectively naming as YES button, NO button, and CANCEL button.
    3. The third one is a WARNING MESSAGE BOX that appears with the title of the
    warning popup notification window and the messages written in, and it provides
    three buttons, respectively naming as CANCEL button, TRY button, and CONTINUE
    button.
    4. The fourth (last but not least) is a ERROR MESSAGE BOX that appears with the
    title of the error popup notification window and the messages written in, and it
    provides twoo buttons, respectively naming as OK button and CANCEL button.

    Need some future and furthermore updates on this structure, since basically the
    popup notification windows for all of those four describes above are already being
    implemented inside their own functions, with globally and locally accessible
    variables to handle each titles of the windows and the messages in it, based on
    the purpose of why the popup notification appears before the users, since that might
    be telling them for what to do and what to confirms based on what it takes to
    validate the required parameters of each notifications active within.

    How this feature works, is just really a written specific title of each notifications
    and the messages written in, as for example the popup notification about:
        a) Info about default changes and updates,
        b) Confirming the users on trying to changing something that may affects other
           configurations as well,
        c) Giving the users warnings about something they accidentally took a wrong turn
           over the program that might give them bugs and even un-encrypted written textfile
           data, and
        d) Catching all errors that the users made (like changing the core factors of the
           program) and telling the users that they're not allowed to do so, or might get
           banned if they keep ignoring the error messages.
    */

    char PopUpNotificationTitleWindow[BUFSIZE07];
    char PopUpNotificationMessageWindow[BUFSIZE10];
} RASNInputs[BUFSIZE07];
int F5Selected = 0;

struct DataVisualization {
    /*
    This feature is on development and not even being experimentally implemented yet,
    but the consideration of what could be displayed on a graph for something economically
    and statistically better to give the users more about the informations about their
    demanded search of configuration in displaying over their selected features, like
    a graph over a spesific whole month, a whole day recorded transactions, and more.

    How this works is by reading and filtered over a transaction history from a spesific
    text file, and sorted each by the transactions that had been made on that day or month
    or maybe even a year, and how many budgets or money that had been spent on into those
    transactions, and make a graph (by a line or long upward rectangles).
    */

    char FileName[BUFSIZE07];
    char XAxisTransactions[BUFSIZE07], YAxisMoneyOnSpent[BUFSIZE07];
    char GraphTitle[BUFSIZE07], GraphDescription[BUFSIZE07], GraphDefinitions[BUFSIZE07];
    char OtherAdditionalInformation[BUFSIZE07];
} DVInputs[BUFSIZE07];
int F6Selected = 0;

/* PROTOTYPE FUNCTIONS DEFINITION */
// Important Starting Features (CORE FEATURES)
// Core features available: 5

void LanguageMenu(void);
void AccountRegistrationMenu(int);
void AccountLoginMenu(int);
void AccountRecoveryMenu(int);
void MainMenuApplicationFeatures(int);
void MainMenuProfileManager(int);
void MainMenuApplicationInformations(int);
void HelpMenu(int);

void EncryptTxtFile(const char*, const char*, int, bool);
void DecryptTxtFile(const char*, bool, int, char ReadDecryptedKeyString[]);
void MatchSaveFileTxt(const char*, const char*);
void SaveDataInTxtFile(const char*, const int, bool);
void OverWriteStringAtLine(const char*, const char*, const int, signed int);
int  ArrowKeyChoiceDialog(const char*, char* MessagesShown[], size_t, size_t);
int  RandInt(int, int);
int  FindOccurences(const char*, char);
char *TrimWhiteSpaces(char*);
char *StringUppercase(char*);
char *StringLowercase(char*);
char *StringCapitalize(char*);
char *ReadAndPrintLine(const char*, intmax_t);

// Notifications Features (CORE FEATURES)
// Notification features available: 4

int InfoMessageBox_OK(const char*, const char*);
int QuestionMessageBox_YESNOCANCEL(const char*, const char*);
int WarningMessageBox_CANCELTRYCONTINUE(const char*, const char*);
int ErrorMessageBox_OKCANCEL(const char*, const char*);

// Available main application features: 6

void F1_MoneytoryTransactionsRegister(int);    // Easy     (PRIORITY)           -- DONE!
void F2_MoneytoryGroupingPerCategory(int);     // Medium   (LATER)              -- WIP
void F3_BudgetCreationAndMonitoring(int);      // Easy     (PRIORITY)           -- DONE! (Update soon)
void F4_FilterSearchingData(int);              // Medium   (LATER)              -- DONE! (Update soon)
void F5_ReminderAndSetNotifications(int);      // Hard     (LAST BUT NOT LEAST) -- DONE! (Update soon)
void F6_DataVisualization(int);                // Harder   (LAST BUT NOT LEAST) -- DONE!

void F1_FUC01_FinancialUsesCategoryUI(int);
void F1_FUC02_FinancialUsesCategoryUI(int);
void F1_FUC03_FinancialUsesCategoryUI(int);
void F1_FUC04_FinancialUsesCategoryUI(int);
void F1_FUC05_FinancialUsesCategoryUI(int);
void F1_FUC06_FinancialUsesCategoryUI(int);

void F2_FUC01_FinancialUsesCategoryUI(int);
void F2_FUC02_FinancialUsesCategoryUI(int);
void F2_FUC03_FinancialUsesCategoryUI(int);
void F2_FUC04_FinancialUsesCategoryUI(int);
void F2_FUC05_FinancialUsesCategoryUI(int);
void F2_FUC06_FinancialUsesCategoryUI(int);

void F3_FUC01_FinancialUsesCategoryUI(int);
void F3_FUC02_FinancialUsesCategoryUI(int);
void F3_FUC03_FinancialUsesCategoryUI(int);
void F3_FUC04_FinancialUsesCategoryUI(int);
void F3_FUC05_FinancialUsesCategoryUI(int);
void F3_FUC06_FinancialUsesCategoryUI(int);

// Building up features for Feature No. 6

void HorizontalHistogramUI_WEEK(const char*, signed long long int);
void HorizontalHistogramUI_MONTH(const char*, signed long long int);
void HorizontalHistogramUI_YEAR(const char*, signed long long int);

/* STARTING THE DECLARATIONS: REMINDER AND NOTIFICATIONS */
/* Initialize functions and classes (if needed) */

char* Title, Message, Description;
int InfoMessageBox_OK(const char* Title, const char* Message) {
    int MessageBoxID = MessageBox( \
        NULL, \
        (LPCSTR) Message, \
        (LPCSTR) Title, MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON1);
    
    switch (MessageBoxID) {
        case IDOK: break;
        default: break;
    } return MessageBoxID;
}

int QuestionMessageBox_YESNOCANCEL(const char* Title, const char* Message) {
    int MessageBoxID = MessageBox( \
        NULL, \
        (LPCSTR) Message, \
        (LPCSTR) Title, MB_ICONQUESTION | MB_YESNOCANCEL | MB_DEFBUTTON2);

    switch (MessageBoxID) {
        case IDYES: break;
        case IDNO: break;
        case IDCANCEL: break;
    } return MessageBoxID;
}

int WarningMessageBox_CANCELTRYCONTINUE(const char* Title, const char* Message) {
    int MessageBoxID = MessageBox( \
        NULL, \
        (LPCSTR) Message, \
        (LPCSTR) Title, MB_ICONEXCLAMATION | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);

    switch (MessageBoxID) {
        case IDCANCEL: break;
        case IDTRYAGAIN: break;
        case IDCONTINUE: break;
    } return MessageBoxID;
}

int ErrorMessageBox_OKCANCEL(const char* Title, const char* Message) {
    int MessageBoxID = MessageBox( \
        NULL, \
        (LPCSTR) Message, \
        (LPCSTR) Title, MB_ICONERROR | MB_OKCANCEL | MB_DEFBUTTON1);

    switch (MessageBoxID) {
        case IDOK: break;
        case IDCANCEL: break;
    } return MessageBoxID;
}

/* STARTING THE DECLARATIONS: ENCRYPTION AND DECRYPTION DATA */
/* Initialize functions and classes (if needed) */

char *TrimWhiteSpaces(char* SourceString) {
    char *EndString;

    while (isspace((unsigned char) *SourceString)) SourceString++;  // Trim leading space
    if (*SourceString == 0) return SourceString;                    // All spaces?
    EndString = SourceString + strlen(SourceString) - 1;            // Trim trailing space
    while (EndString > SourceString && isspace((unsigned char) *EndString)) EndString--;

    EndString[1] = '\0'; // Write new null terminator character
    return SourceString;
}

char *ReadAndPrintLine(const char* SourceTextFile, intmax_t Line) {
    FILE *FSource = fopen(SourceTextFile, "r");
    char FDBuffer[BUFSIZE10], *ReturnFDBuffer = malloc(BUFSIZE10);
    intmax_t Lines = 0;
    
    do {
        if (++Lines == Line) {
            fgets(FDBuffer, BUFSIZE10, FSource);
            break;
        }
    } while((fscanf(FSource, "%*[^\n]"), fscanf(FSource, "%*c")) != EOF);
    if (Lines == Line) { strcpy(ReturnFDBuffer, FDBuffer); fclose(FSource); return ReturnFDBuffer; }
    fclose(FSource); ReturnFDBuffer = "None"; return ReturnFDBuffer;
}

void OverWriteStringAtLine(const char* FSourceTxtFile, const char* NewOverWriteString, const int EncryptionKey, signed int AtSpesificLine) {
	FILE *FSource, *FDestination, *FCopyAndDecrypting, *FTempDestination;
	int AtLine = AtSpesificLine, LineControl = 0, BufLen = 0;
	char FDBuffer[BUFSIZE16], NewlyString[BUFSIZE16], FileName[BUFSIZE16];      
	char OverWriteStringLine[BUFSIZE16], FTempDestinationTxtFile[BUFSIZE16] = "TempDestination.txt", DeleteTempDestinationTxtFile[BUFSIZE16];
	
	FCopyAndDecrypting = fopen(FSourceTxtFile, "r");
	FTempDestination   = fopen("FTempDestination.txt", "w");
	while (fgets(FDBuffer, sizeof(FDBuffer), FCopyAndDecrypting) != 0) {
		BufLen = strlen(FDBuffer);
		for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
		fputs(FDBuffer, FTempDestination);
	} fclose(FCopyAndDecrypting); fclose(FTempDestination);

	strncpy(FileName, FSourceTxtFile, BUFSIZE16);
	FSource      = fopen("FTempDestination.txt", "r");
	FDestination = fopen(FTempDestinationTxtFile, "w");
	if (!FSource)      { }
	if (!FDestination) { }

	strncpy(OverWriteStringLine, NewOverWriteString, BUFSIZE16);
	strcat(OverWriteStringLine, "\n");

	while (!feof(FSource)) {
		strcpy(NewlyString, "\0");
		fgets(NewlyString, BUFSIZE16, FSource);

		if (!feof(FSource))  {
			LineControl++;
			if (LineControl != AtLine) { fputs(NewlyString, FDestination); }
			else { fputs(OverWriteStringLine, FDestination); }
		}
	} fclose(FSource);
	fclose(FDestination);
	remove(FileName); rename(FTempDestinationTxtFile, FileName);

    strcpy(DeleteTempDestinationTxtFile, "del ");
    strcat(DeleteTempDestinationTxtFile, "FTempDestination.txt");
    system(DeleteTempDestinationTxtFile);
}

char *StringUppercase(char* SourceString) {
    for (int i = 0; SourceString[i] != '\0'; i++) {
        if (SourceString[i] >= 'a' && SourceString[i] <= 'z') SourceString[i] -= 32;
    } return SourceString;
}

char *StringLowercase(char* SourceString) {
    for (int i = 0; SourceString[i] != '\0'; i++) {
        if (SourceString[i] >= 'A' && SourceString[i] <= 'Z') SourceString[i] += 32;
    } return SourceString;
}

char *StringCapitalize(char* SourceString) {
    for (int i = 0; SourceString[i] != '\0'; i++) {
        if      (SourceString[0] >= 'A' && SourceString[0] <= 'Z') NULL;
        else if (SourceString[0] >= 'a' && SourceString[0] <= 'z') SourceString[0] -= 32;
        else if (i != 0 && (SourceString[i] >= 'A' && SourceString[i] <= 'Z')) SourceString[i] += 32;
        else if (i != 0 && (SourceString[i] >= 'a' && SourceString[i] <= 'z')) NULL;
    } return SourceString;
}

int FindOccurences(const char* SourceString, char SearchedOccurence) {
    int CountOccurences;
    for (int i = 0; (long long unsigned int)i < strlen(SourceString) - 1; i++) {
        if (SourceString[i] == SearchedOccurence) CountOccurences++;
    } return CountOccurences;
}

/* Abbreviation of "Encrypt Text File" is one of the CORE FEATURES here in this application,
and the return type function is `void()`, and requires the program to accept:
`>>>` FOUR (4) arguments, accordingly as explained below.

`> const char *SourceTextFile`: A source text file that needs to be the source before being encrypted.
`> const char *DestinationTextFile`: A destination text file that needs to be the place of the after-encrypted.
`> int EncryptionKey`: A MUST required encryption key in order the text file to be encrypted. The code is spesific, and MUST be set in the program code before runtime, or included in the `**argv` parameter at command line before runtime. The encryption key HAS TO BE THE SAME for the decryption key, because one different in a single number will resulted in a non-correct encryption/decryption method.
`> bool SourceTextFileDeletion`: Mode for deleting the source text file right after the encryption, so the copy of the data will not get leaked if the source that's not get encrypted is stil intact on the folder.

`[Format: 4th argument] <TRUE> || <FALSE>`
*/
void EncryptTxtFile(const char* SourceTextFile, const char* DestinationTextFile, int EncryptionKey, bool SourceTextFileDeletion) {
    FILE *FSource, *FDestination;
    int BufLen;
    char FDBuffer[BUFSIZE16], DeleteSourceTxtFile[128];

    FSource         = fopen(SourceTextFile, "r");
    FDestination    = fopen(DestinationTextFile, "w");
    if (FSource == NULL)        ErrorHandling(SOURCEFILENULLERROR, SourceTextFile);
    if (FDestination == NULL)   ErrorHandling(DESTINATIONFILENULLERROR, DestinationTextFile);
    
    while (fgets(FDBuffer, sizeof(FDBuffer), FSource) != 0) {
        BufLen = strlen(FDBuffer);
        for (int i = 0; i < BufLen; i++) FDBuffer[i] -= EncryptionKey;
        fputs(FDBuffer, FDestination);
    }
    fclose(FSource); fclose(FDestination);

    if (SourceTextFileDeletion) {
        strcpy(DeleteSourceTxtFile, "del ");
        strcat(DeleteSourceTxtFile, SourceTextFile);
        system(DeleteSourceTxtFile);
    } else NULL;
}

/* Abbreviation of "Decrypt Text File" is one of the CORE FEATURES here in this application,
and the return type function is `void()`, and requires the program to accept:
`>>>` FOUR (4) arguments, accordingly as explained below.

`> const char *DestinationTextFile`: A destination text file that needs to be decrypted.
`> bool ReadDecryptedFile`: Mode for reading the whole contents of the decrypted file.
`> int DecryptionKey`: A MUST required decryption key in order the text file to be decrypted. The code is spesific, and MUST be set in the program code before runtime, or included in the `**argv` parameter at command line before runtime. The encryption key HAS TO BE THE SAME for the decryption key, because one different in a single number will resulted in a non-correct encryption/decryption method.
`> char ReadDecryptedKeyString[BUFSIZE16]`: Use to search and find a certain key of strings in the decrypted text file, and this argumen have a spesific format and delimiters, and this argument can be used to find more than one key strings, but in the same time can be only one text file at a time, and that's the file you chose to decrypted when assigning it to this argument. This argument has `65,536` or `2^16` FDBuffer size, meaning you can input a total of `65,536` characters inside as a string. 

`[Format: 2nd argument] <TRUE> || <FALSE>`
`[Format: 4th argument] <TEXTFILE.txt> > <STRINGKEY8LIST>`
*/
void DecryptTxtFile(const char* DestinationTextFile, bool ReadDecryptedFile, int DecryptionKey, char ReadDecryptedKeyString[]) {
    FILE *FDestination, *FTempDestination;
    int BufLen, Ptr = 0, KeyTracker = 0, LineTracker = 0, FTDPos = 0;
    char C, FDBuffer[BUFSIZE16], DeleteTempDestinationTxtFile[128], TxtFileName[128];
    char *SourceTextFileName, *SourceKeyStringValue, *SelectedKeyString;
    char *SourceKeyStringValues[BUFSIZE16], FTDestination[BUFSIZE10][BUFSIZE10];

    FDestination = fopen(DestinationTextFile, "r");
    if (FDestination == NULL) ErrorHandling(DESTINATIONFILENULLERROR, DestinationTextFile);
    if (ReadDecryptedFile) {
        while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
            BufLen = strlen(FDBuffer);
            for (int i = 0; i < BufLen; i++) FDBuffer[i] += DecryptionKey;
            fputs(FDBuffer, stdout);
        }
    } fclose(FDestination);

    if (strcmp(ReadDecryptedKeyString, "None") == 0) NULL;
    else {
        FDestination     = fopen(DestinationTextFile, "r");
        FTempDestination = fopen("TempDestination.txt", "w");

        while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
            BufLen = strlen(FDBuffer);
            for (int i = 0; i < BufLen; i++) FDBuffer[i] += DecryptionKey;
            fputs(FDBuffer, FTempDestination);
        } fclose(FDestination); fclose(FTempDestination);

        strcpy(TxtFileName, ReadDecryptedKeyString);
        strtok_r(TxtFileName, ">", &SelectedKeyString);
        SelectedKeyString = TrimWhiteSpaces(SelectedKeyString);
        SourceKeyStringValue = strtok(SelectedKeyString, ",");
        KeyTracker++;

        while (SourceKeyStringValue != NULL) {
            SourceKeyStringValues[Ptr] = SourceKeyStringValue;
            SourceKeyStringValues[Ptr] = TrimWhiteSpaces(SourceKeyStringValues[Ptr]);
            SourceKeyStringValue = strtok(NULL, ",");
            Ptr++; KeyTracker++;
        } SourceTextFileName = TrimWhiteSpaces(TxtFileName);
        
        if (strcmp(SourceTextFileName, DestinationTextFile) == 0) {
            if ((strchr(TxtFileName, ':') == NULL) && (strchr(SelectedKeyString, ':') == NULL)) {
                int FTDIndex = 0, SKSVIndex = 0;

                FDestination = fopen("TempDestination.txt", "r");
                for (C = getc(FDestination); C != EOF; C = getc(FDestination))
                    if (C == '\n') LineTracker++;
                fclose(FDestination);

                FDestination = fopen("TempDestination.txt", "r");
                while(fgets(FTDestination[FTDPos], BUFSIZE10, FDestination) != NULL) {
                    if (FTDPos < LineTracker)
                        FTDestination[FTDPos][strlen(FTDestination[FTDPos]) - 1] = '\0';
                    FTDPos++;
                } fclose(FDestination);

                while (FTDIndex <= LineTracker) {
                    while (SKSVIndex <= KeyTracker - 2) {
                        if (strstr(FTDestination[FTDIndex], SourceKeyStringValues[SKSVIndex]) != NULL) {
                            printf("%s\n", FTDestination[FTDIndex]); break;
                        } else if (strstr(FTDestination[FTDIndex], SourceKeyStringValues[SKSVIndex]) == NULL)
                            SKSVIndex++;
                    } FTDIndex++; SKSVIndex = 0;
                }
                strcpy(DeleteTempDestinationTxtFile, "del ");
                strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
                system(DeleteTempDestinationTxtFile);
            }
        } else {
            strcpy(DeleteTempDestinationTxtFile, "del ");
            strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
            system(DeleteTempDestinationTxtFile);
        }
    }
}

void MatchSaveFileTxt(const char *DirectoryPath, const char *FullFileNameOrSubstringFileName) {
    struct dirent *DIRFiles;
    char SaveFileTxtName[BUFSIZE07];
    DIR *DIRPath = opendir(DirectoryPath);
    
    if (DIRPath == NULL) { NULL; }
    while ((DIRFiles = readdir(DIRPath)) != NULL) {
        if (strstr(DIRFiles -> d_name, FullFileNameOrSubstringFileName)) {
            snprintf(SaveFileTxtName, BUFSIZE07, "%s", DIRFiles -> d_name);
            strcpy(SaveFilesTxtName[FilePathNameTraversalCounter].FileNames, SaveFileTxtName);
            FilePathNameTraversalCounter++;
        }
    } closedir(DIRPath);
}

void SaveDataInTxtFile(const char* DestinationTextFile, const int EncryptionKey, bool AutoRestart) {
    /*
        strcpy(ProfileSaveFileData, UserName); strcat(ProfileSaveFileData, "-SaveFile.txt");
        SaveDataInTxtFile(ProfileSaveFileData, EncryptionKey, false);
    */

    FILE *FDestination, *FTempDestination;
    char FDBuffer[BUFSIZE16];
    int BufLen;

    FDestination     = fopen("SKYR-FMSA-RegisteredAccounts.txt", "r");
    FTempDestination = fopen("TempDestination.txt", "w");

    while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
        BufLen = strlen(FDBuffer);
        for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
        fputs(FDBuffer, FTempDestination);
    } fclose(FDestination); fclose(FTempDestination);

    FDestination = fopen(DestinationTextFile, "w");
    fprintf(FDestination, "────────────────────────────────────────────────────────────────────────────────────────────────────\n%s%s\n%s(STATUS) Profile Account Linked to: %s.\n────────────────────────────────────────────────────────────────────────────────────────────────────\n", ApplicationTitle, ApplicationVersion, AppMainMenuUI, UserName);
    fprintf(FDestination, "%s",   ReadAndPrintLine("TempDestination.txt", 9));
    fprintf(FDestination, "────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    fprintf(FDestination, "%s",   ReadAndPrintLine("TempDestination.txt", (-3) + (14 * GlobalAccount)));
    fprintf(FDestination, "%s\n", ReadAndPrintLine("TempDestination.txt", (-2) + (14 * GlobalAccount)));
    fprintf(FDestination, "%s",   ReadAndPrintLine("TempDestination.txt", 0 + (14 * GlobalAccount)));
    fprintf(FDestination, "%s",   ReadAndPrintLine("TempDestination.txt", 1 + (14 * GlobalAccount)));
    // fprintf(FDestination, "%s",   ReadAndPrintLine("TempDestination.txt", 2 + (14 * GlobalAccount)));
    fprintf(FDestination, "... (%s's private e-mail address)\n", UserName);
    fprintf(FDestination, "%s",   ReadAndPrintLine("TempDestination.txt", 3 + (14 * GlobalAccount)));
    // fprintf(FDestination, "%s",   ReadAndPrintLine("TempDestination.txt", 4 + (14 * GlobalAccount)));
    fprintf(FDestination, "... (%s's private password account)\n\n", UserName);
    fprintf(FDestination, "%s",   ReadAndPrintLine("TempDestination.txt", 6 + (14 * GlobalAccount)));
    fprintf(FDestination, "%s",   ReadAndPrintLine("TempDestination.txt", 7 + (14 * GlobalAccount)));
    // fprintf(FDestination, "%s",   ReadAndPrintLine("TempDestination.txt", 8 + (14 * GlobalAccount)));
    fprintf(FDestination, "... (%s's private phone number)\n", UserName);
    fprintf(FDestination, "%s",   ReadAndPrintLine("TempDestination.txt", 9 + (14 * GlobalAccount)));
    fprintf(FDestination, "────────────────────────────────────────────────────────────────────────────────────────────────────\n");

    // strcpy(DeleteTempDestinationTxtFile, "del ");
    // strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
    // system(DeleteTempDestinationTxtFile);
    EncryptTxtFile("TempDestination.txt", DestinationTextFile, EncryptionKey, true);;
    fclose(FDestination);
    if (AutoRestart) exit(0);
}

int ArrowKeyChoiceDialog(const char* AppModeMenu, char* MessagesShown_ArrowKeyChoiceDialog[], size_t MessagesIndexBegin, size_t MessagesIndexEnd) {
    if (strcmp(AppModeMenu, ArrowKeyChoiceDialogModes[0]) == 0) {
        // Debug: Basic formula on W-A-S-D choice, but using arrow keys instead.

        // int Selected = 0;
        // int AvailableOptions = 3;
        // bool Selecting = true, Updated = false, FirstRun = true;
        // char AKDC;

        // while (Selecting) {
        //     if (!FirstRun) {
        //         if ((Selected + 1) == 1) {
        //             puts("Available Options:\n" ANSI_COLOR_BLUE"  1. Option 1\n"ANSI_COLOR_RESET  "  2. Option 2\n  3. Option 3\n");
        //             printf("Which one is your preferable input: ");
        //         } else if ((Selected + 1) == 2) {
        //             puts("Available Options:\n  1. Option 1\n" ANSI_COLOR_BLUE"  2. Option 2\n" ANSI_COLOR_RESET"  3. Option 3\n");
        //             printf("Which one is your preferable input: ");
        //         } else if ((Selected + 1) == 3) {
        //             puts("Available Options:\n  1. Option 1\n  2. Option 2\n" ANSI_COLOR_BLUE"  3. Option 3\n"ANSI_COLOR_RESET);
        //             printf("Which one is your preferable input: ");
        //         }
        //     } else {
        //         FirstRun = false;
        //         printf(ANSI_COLOR_GREEN"INFO: Option %d is selected by the user.\n"ANSI_COLOR_RESET, (Selected + 1));
        //         puts("Available Options:\n" ANSI_COLOR_BLUE"  1. Option 1\n"ANSI_COLOR_RESET  "  2. Option 2\n  3. Option 3\n");
        //         printf("Which one is your preferable input: ");
        //     }

        //     switch (AKDC = _getch()) {
        //         case KEY_LEFT:
        //             if (Selected > 0 && Selected < AvailableOptions) {
        //                 --Selected; Updated = true;
        //             } else if (Selected <= 0) {
        //                 Selected = (AvailableOptions - 1); Updated = true;
        //             } break;
        //         case KEY_RIGHT:
        //             if (Selected >= 0 && Selected < AvailableOptions - 1) {
        //                 ++Selected; Updated = true;
        //             } else if (Selected >= AvailableOptions - 1) {
        //                 Selected = 0; Updated = true;
        //             } break;
        //         case KEY_ENTER:
        //             Selecting = false; Updated = true;
        //             break;
                    
        //         case 49: Selected = 0; Updated = true; break;
        //         case 50: Selected = 1; Updated = true; break;
        //         case 51: Selected = 2; Updated = true; break;
        //         default: break;
        //     } ClearScreen();

        //     if (Updated) {
        //         printf(ANSI_COLOR_GREEN"INFO: Option %d is selected by the user.\n"ANSI_COLOR_RESET, (Selected + 1));
        //         Updated = false;
        //     } else {
        //         printf(ANSI_COLOR_YELLOW"INFO: Option %d is STILL being selected by the user.\n"ANSI_COLOR_RESET, (Selected + 1));
        //     }
        // } printf(ANSI_COLOR_WHITE"INFO: Final arrow input selection: Option %d.\n"ANSI_COLOR_RESET, (Selected + 1));
    
    } else if (strcmp(AppModeMenu, ArrowKeyChoiceDialogModes[1]) == 0) {
        int Selected = 0;
        int AvailableOptions = 2;
        bool Selecting = true, Updated = false, FirstRun = true;
        char AKDC;

        while (Selecting) {
            if (!FirstRun) {
                if ((Selected + 1) == 1) {
                    for (int i = MessagesIndexBegin; (long long unsigned int)i < MessagesIndexEnd; i++) {
                        puts(MessagesShown_ArrowKeyChoiceDialog[i]);
                    } puts("\t\t\t\t       " ANSI_COLOR_LIGHTGREEN"[Yes, I confirm!] <"ANSI_COLOR_RESET "> [No, I cancel...]");
                } else if ((Selected + 1) == 2) {
                    for (int i = MessagesIndexBegin; (long long unsigned int)i < MessagesIndexEnd; i++) {
                        puts(MessagesShown_ArrowKeyChoiceDialog[i]);
                    } puts("\t\t\t\t       [Yes, I confirm!] <" ANSI_COLOR_LIGHTRED"> [No, I cancel...]"ANSI_COLOR_RESET);
                }
            } else {
                FirstRun = false;
                puts("\t\t\t\t       " ANSI_COLOR_LIGHTGREEN"[Yes, I confirm!] <"ANSI_COLOR_RESET "> [No, I cancel...]");
            }

            switch (AKDC = _getch()) {
                case KEY_RIGHT:
                    if (Selected >= 0 && Selected < (AvailableOptions - 1)) {
                        ++Selected; Updated = true;
                    } else if (Selected < 0) {
                        Selected = 0; Updated = true;
                    } break;
                case KEY_LEFT:
                    if (Selected > 0 && Selected < AvailableOptions) {
                        --Selected; Updated = true;
                    } else if (Selected >= AvailableOptions - 1) {
                        Selected = (AvailableOptions - 1); Updated = true;
                    } break;
                case KEY_ENTER:
                    Selecting = false; Updated = true;
                    break;
                    
                case 121: Selected = 0; Updated = true; break;
                case 110: Selected = 1; Updated = true; break;
                default: break;
            } if (Selecting) ClearScreen();
            
            fflush(stdin);
            (Updated) ? Updated = false : true;
        
        } if (Selected == 0) { return true;  }
          else               { return false; }

    } else if (strcmp(AppModeMenu, ArrowKeyChoiceDialogModes[2]) == 0) {
        char WelcomingMessages[BUFSIZE11], CreditsAfterwards[BUFSIZE11];
        int Selected = 0;
        int AvailableOptions = 2;
        bool Selecting = true, Updated = false, FirstRun = true;
        char AKDC;
        int PreviousAKDC = 0;
        bool CatchDefaultAKDC = false;

        ClearScreen();
        while (Selecting) {
            
            /* Welcoming Page */
            /* Welcoming Page */
            /* Welcoming Page */
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n\t"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_BOLD"\t      Welcome to the: " ANSI_STYLE_UNDERLINE"SKYR Personal Financial Management Supports Application!\n\t"ANSI_COLOR_RESET BRIGHTPURPLE218 ANSI_STYLE_BOLD"\t\t   Save more for better future, and live happily ever after... :)\n\n\t"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLanguageUI, UserName);
            printf(BRIGHTBLUE159"Creation and Designing by: @EintsWaveX (Immanuel Eben); "ANSI_COLOR_RESET ANSI_COLOR_WHITE ANSI_STYLE_ITALIC"(support me on GitHub)!\n\t"ANSI_COLOR_RESET BRIGHTBLUE157"Ideas and Supporting by:\n\t    > @Ardia Pasha, @Arif Darmansyah, @Ilham Jamil, @Indah Natalia, and @Zaki Risqulah;\n\t      "ANSI_COLOR_RESET BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"(F3)          (F5)              (F4)          (F1, F2)            (F6)" BRIGHTBLUE159"\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET);
            if (CatchDefaultAKDC) printf(ANSI_COLOR_LIGHTRED"\tError: The auto-enter shortcut key labeled as '%c' (ID: 0x%02X) is not registered at the moment!\n\n"ANSI_COLOR_RESET, ((int)PreviousAKDC != 12) ? (char)PreviousAKDC : 10, (int)PreviousAKDC);
            /* Welcoming Page */
            /* Welcoming Page */
            /* Welcoming Page */
            
            if (!FirstRun) {
                if ((Selected + 1) == 1) {
                    puts("\tPlease select your prefered language mode:\n\tSilakan memilih mode bahasa berikut:\n\n\t" ANSI_COLOR_BLUE"> English"ANSI_COLOR_RESET "\tBahasa Indonesia\n\t" ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET ANSI_COLOR_ORANGE"       (to be implemented...)"ANSI_COLOR_RESET);
                } else if ((Selected + 1) == 2) {
                    puts("\tPlease select your prefered language mode:\n\tSilakan memilih mode bahasa berikut:\n\n\tEnglish" ANSI_COLOR_BLUE"\t\t> Bahasa Indonesia\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET ANSI_COLOR_ORANGE"       (to be implemented...)"ANSI_COLOR_RESET);
                }
            } else {
                FirstRun = false;
                puts("\tPlease select your prefered language mode:\n\tSilakan memilih mode bahasa berikut:\n\n\t" ANSI_COLOR_BLUE"> English"ANSI_COLOR_RESET "\tBahasa Indonesia\n\t" ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET ANSI_COLOR_ORANGE"       (to be implemented...)"ANSI_COLOR_RESET);
            }

            switch (AKDC = _getch()) {
                case KEY_RIGHT:
                    PreviousAKDC = 0; CatchDefaultAKDC = false;
                    if (Selected > 0 && Selected < AvailableOptions) {
                        --Selected; Updated = true;
                    } else if (Selected <= 0) {
                        Selected = (AvailableOptions - 1); Updated = true;
                    } break;
                case KEY_LEFT:
                    PreviousAKDC = 0; CatchDefaultAKDC = false;
                    if (Selected >= 0 && Selected < AvailableOptions - 1) {
                        ++Selected; Updated = true;
                    } else if (Selected >= AvailableOptions - 1) {
                        Selected = 0; Updated = true;
                    } break;
                case KEY_ENTER:
                    Selecting = false; Updated = true;
                    break;
                default: {
                    if (AKDC == KEY_UP || AKDC == KEY_DOWN || AKDC == KEY_LEFT || AKDC == KEY_RIGHT || AKDC == KEY_ENTER) { ClearScreen(); continue; }
                    (AKDC > 0) ? PreviousAKDC = (int)AKDC : 0;
                    (AKDC > 0) ? CatchDefaultAKDC = true : false;
                } break;
            } if (Selecting) ClearScreen();

            fflush(stdin);
            (Updated) ? Updated = false : true;

        } if (Selected == 0) {
            puts(ANSI_COLOR_WHITE"\n\tAre you sure that's your prefered language for the whole app usages?\n\tLanguage mode choice is: English.\n"ANSI_COLOR_RESET);
        } else {
            puts(ANSI_COLOR_WHITE"\n\tApakah Anda yakin penggunaan bahasa ini pada seluruh isi aplikasi?\n\tMode bahasa pilihan adalah: Bahasa Indonesia.\n"ANSI_COLOR_RESET);
        }

        snprintf(WelcomingMessages, BUFSIZE11, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n\t"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_BOLD"\t      Welcome to the: " ANSI_STYLE_UNDERLINE"SKYR Personal Financial Management Supports Application!\n\t"ANSI_COLOR_RESET BRIGHTPURPLE218 ANSI_STYLE_BOLD"\t\t   Save more for better future, and live happily ever after... :)\n\t"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLanguageUI, UserName);
        snprintf(CreditsAfterwards, BUFSIZE11, BRIGHTBLUE159"\tCreation and Designing by: @EintsWaveX (Immanuel Eben); "ANSI_COLOR_RESET ANSI_COLOR_WHITE ANSI_STYLE_ITALIC"(support me on GitHub)!\n\t"ANSI_COLOR_RESET BRIGHTBLUE157"Ideas and Supporting by:\n\t    > @Ardia Pasha, @Arif Darmansyah, @Ilham Jamil, @Indah Natalia, and @Zaki Risqulah;\n\t      "ANSI_COLOR_RESET BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"(F3)          (F5)              (F4)          (F1, F2)            (F6)" BRIGHTBLUE159"\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET);
        MessagesShown_ArrowKeyChoiceDialog[20] = WelcomingMessages;
        MessagesShown_ArrowKeyChoiceDialog[21] = CreditsAfterwards;
        MessagesShown_ArrowKeyChoiceDialog[22] = \
            (Selected == 0) ? \
            "\tPlease select your prefered language mode:\n\tSilakan memilih mode bahasa berikut:\n\n\t" ANSI_COLOR_BLUE"> English"ANSI_COLOR_RESET "\tBahasa Indonesia\n\t" ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET ANSI_COLOR_ORANGE"       (to be implemented...)"ANSI_COLOR_RESET : \
            "\tPlease select your prefered language mode:\n\tSilakan memilih mode bahasa berikut:\n\n\tEnglish" ANSI_COLOR_BLUE"\t\t> Bahasa Indonesia\n\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(default)"ANSI_COLOR_RESET ANSI_COLOR_ORANGE"       (to be implemented...)"ANSI_COLOR_RESET;
        MessagesShown_ArrowKeyChoiceDialog[23] = \
            (Selected == 0) ? \
            ANSI_COLOR_WHITE"\n\tAre you sure that's your prefered language for the whole app usages?\n\tLanguage mode choice is: English.\n"ANSI_COLOR_RESET : \
            ANSI_COLOR_WHITE"\n\tApakah Anda yakin penggunaan bahasa ini pada seluruh isi aplikasi?\n\tMode bahasa pilihan adalah: Bahasa Indonesia.\n"ANSI_COLOR_RESET;

        TruthConfirmation = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 20, 24);
        if (!TruthConfirmation) { ClearScreen(); LanguageMenu(); }
        else {
            puts((Selected == 0) ? \
                "\n\t" ANSI_COLOR_LIGHTMAGENTA"Please kindly wait while we setting up things..."ANSI_COLOR_RESET : \
                "\n\t" ANSI_COLOR_LIGHTMAGENTA"Mohon maaf, untuk pemilihan bahasa ini masih dalam proses pembaharuan..."ANSI_COLOR_RESET);
            
            sleep(RandInt(1, 3));
            puts((Selected == 0) ? \
                ANSI_COLOR_LIGHTMAGENTA"\tUser Application Language: #ENG [English] "ANSI_COLOR_RESET : \
                ANSI_COLOR_LIGHTMAGENTA"\tMenargetkan aplikasi ke dalam Bahasa Inggris, sekali lagi mohon maaf atas ketidaknyamanannya... ."ANSI_COLOR_RESET);
            
            printf(ANSI_COLOR_MAGENTA ANSI_STYLE_ITALIC"\n\t[ENTER] Go to the registration profile account process... . "ANSI_COLOR_RESET);
            getchar();
            AccountRegistrationMenu(0);
        }
    } return 0;
}

/* TRIAL PURPOSES */
/* TRIAL PURPOSES */
/* TRIAL PURPOSES */
void HorizontalHistogramUI_WEEK(const char* SourceFileTxtData, signed long long int PerMoneyExpenses) {
    fflush(stdout); fflush(stdin);

    char *HHMonday_X, *HHTuesday_X, *HHWednesday_X, *HHThursday_X, *HHFriday_X, *HHSaturday_X, *HHSunday_X;
    char *HHMonday_Y, *HHTuesday_Y, *HHWednesday_Y, *HHThursday_Y, *HHFriday_Y, *HHSaturday_Y, *HHSunday_Y;
    signed int HHMonday_NX, HHTuesday_NX, HHWednesday_NX, HHThursday_NX, HHFriday_NX, HHSaturday_NX, HHSunday_NX;
    signed int CountBars = 0, CountSpaces = 0;
    char SpacingCompletion[BUFSIZE07];

    HHMonday_Y = strtok(ReadAndPrintLine(SourceFileTxtData, 6), "=");       HHMonday_Y    = TrimWhiteSpaces(HHMonday_Y);
    HHTuesday_Y = strtok(ReadAndPrintLine(SourceFileTxtData, 7), "=");      HHTuesday_Y   = TrimWhiteSpaces(HHTuesday_Y);
    HHWednesday_Y = strtok(ReadAndPrintLine(SourceFileTxtData, 8), "=");    HHWednesday_Y = TrimWhiteSpaces(HHWednesday_Y);
    HHThursday_Y = strtok(ReadAndPrintLine(SourceFileTxtData, 9), "=");     HHThursday_Y  = TrimWhiteSpaces(HHThursday_Y);
    HHFriday_Y = strtok(ReadAndPrintLine(SourceFileTxtData, 10), "=");      HHFriday_Y    = TrimWhiteSpaces(HHFriday_Y);
    HHSaturday_Y = strtok(ReadAndPrintLine(SourceFileTxtData, 11), "=");    HHSaturday_Y  = TrimWhiteSpaces(HHSaturday_Y);
    HHSunday_Y = strtok(ReadAndPrintLine(SourceFileTxtData, 12), "=");      HHSunday_Y    = TrimWhiteSpaces(HHSunday_Y);

    strtok_r(ReadAndPrintLine(SourceFileTxtData, 6),  "=", &HHMonday_X);    HHMonday_X    = TrimWhiteSpaces(HHMonday_X);
    strtok_r(ReadAndPrintLine(SourceFileTxtData, 7),  "=", &HHTuesday_X);   HHTuesday_X   = TrimWhiteSpaces(HHTuesday_X);
    strtok_r(ReadAndPrintLine(SourceFileTxtData, 8),  "=", &HHWednesday_X); HHWednesday_X = TrimWhiteSpaces(HHWednesday_X);
    strtok_r(ReadAndPrintLine(SourceFileTxtData, 9),  "=", &HHThursday_X);  HHThursday_X  = TrimWhiteSpaces(HHThursday_X);
    strtok_r(ReadAndPrintLine(SourceFileTxtData, 10), "=", &HHFriday_X);    HHFriday_X    = TrimWhiteSpaces(HHFriday_X);
    strtok_r(ReadAndPrintLine(SourceFileTxtData, 11), "=", &HHSaturday_X);  HHSaturday_X  = TrimWhiteSpaces(HHSaturday_X);
    strtok_r(ReadAndPrintLine(SourceFileTxtData, 12), "=", &HHSunday_X);    HHSunday_X    = TrimWhiteSpaces(HHSunday_X);

    HHMonday_NX = atoi(HHMonday_X); HHTuesday_NX = atoi(HHTuesday_X); HHWednesday_NX = atoi(HHWednesday_X); HHThursday_NX = atoi(HHThursday_X); HHFriday_NX = atoi(HHFriday_X); HHSaturday_NX = atoi(HHSaturday_X); HHSunday_NX = atoi(HHSunday_X);
    puts(BRIGHTBLUE159"\t────────────────────────────────────────────────────────────────────────────────────────────────────");
    printf(BRIGHTBLUE159"\tMonday    │ "); strcpy(SpacingCompletion, " ");
    for (int PerExpenseCount = 0; PerExpenseCount < (HHMonday_NX * 1000); PerExpenseCount += PerMoneyExpenses) {
        if (CountBars == 40) { printf(" ➜ ➀  "); break; }
        if ((PerExpenseCount + PerMoneyExpenses) <= (HHMonday_NX * 1000)) { printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2; }
        else {
            for (int j = 0; j < (84 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
            printf("%s ✅", SpacingCompletion);
        }
    } if (CountBars == 40) { printf("❌"); }
    puts(""); CountBars = 0; CountSpaces = 0; SpacingCompletion[0] = 0;
    
    printf(BRIGHTBLUE159"\tTuesday   │ "); strcpy(SpacingCompletion, " ");
    for (int PerExpenseCount = 0; PerExpenseCount < (HHTuesday_NX * 1000); PerExpenseCount += PerMoneyExpenses) {
        if (CountBars == 40) { printf(" ➜ ➁  "); break; }
        if ((PerExpenseCount + PerMoneyExpenses) <= (HHTuesday_NX * 1000)) { printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2; }
        else {
            for (int j = 0; j < (84 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
            printf("%s ✅", SpacingCompletion);
        }
    } if (CountBars == 40) { printf("❌"); }
    puts(""); CountBars = 0; CountSpaces = 0; SpacingCompletion[0] = 0;
    
    printf(BRIGHTBLUE159"\tWednesday │ "); strcpy(SpacingCompletion, " ");
    for (int PerExpenseCount = 0; PerExpenseCount < (HHWednesday_NX * 1000); PerExpenseCount += PerMoneyExpenses) {
        if (CountBars == 40) { printf(" ➜ ➂  "); break; }
        if ((PerExpenseCount + PerMoneyExpenses) <= (HHWednesday_NX * 1000)) { printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2; }
        else {
            for (int j = 0; j < (84 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
            printf("%s ✅", SpacingCompletion);
        }
    } if (CountBars == 40) { printf("❌"); }
    puts(""); CountBars = 0; CountSpaces = 0; SpacingCompletion[0] = 0;
    
    printf(BRIGHTBLUE159"\tThursday  │ "); strcpy(SpacingCompletion, " ");
    for (int PerExpenseCount = 0; PerExpenseCount < (HHThursday_NX * 1000); PerExpenseCount += PerMoneyExpenses) {
        if (CountBars == 40) { printf(" ➜ ➃  "); break; }
        if ((PerExpenseCount + PerMoneyExpenses) <= (HHThursday_NX * 1000)) { printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2; }
        else {
            for (int j = 0; j < (84 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
            printf("%s ✅", SpacingCompletion);
        }
    } if (CountBars == 40) { printf("❌"); }
    puts(""); CountBars = 0; CountSpaces = 0; SpacingCompletion[0] = 0;
    
    printf(BRIGHTBLUE159"\tFriday    │ "); strcpy(SpacingCompletion, " ");
    for (int PerExpenseCount = 0; PerExpenseCount < (HHFriday_NX * 1000); PerExpenseCount += PerMoneyExpenses) {
        if (CountBars == 40) { printf(" ➜ ➄  "); break; }
        if ((PerExpenseCount + PerMoneyExpenses) <= (HHFriday_NX * 1000)) { printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2; }
        else {
            for (int j = 0; j < (84 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
            printf("%s ✅", SpacingCompletion);
        }
    } if (CountBars == 40) { printf("❌"); }
    puts(""); CountBars = 0; CountSpaces = 0; SpacingCompletion[0] = 0;
    
    printf(BRIGHTBLUE159"\tSaturday  │ "); strcpy(SpacingCompletion, " ");
    for (int PerExpenseCount = 0; PerExpenseCount < (HHSaturday_NX * 1000); PerExpenseCount += PerMoneyExpenses) {
        if (CountBars == 40) { printf(" ➜ ➅  "); break; }
        if ((PerExpenseCount + PerMoneyExpenses) <= (HHSaturday_NX * 1000)) { printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2; }
        else {
            for (int j = 0; j < (84 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
            printf("%s ✅", SpacingCompletion);
        }
    } if (CountBars == 40) { printf("❌"); }
    puts(""); CountBars = 0; CountSpaces = 0; SpacingCompletion[0] = 0;
    
    printf(BRIGHTBLUE159"\tSunday    │ "); strcpy(SpacingCompletion, " ");
    for (int PerExpenseCount = 0; PerExpenseCount < (HHSunday_NX * 1000); PerExpenseCount += PerMoneyExpenses) {
        if (CountBars == 40) { printf(" ➜ ➆  "); break; }
        if ((PerExpenseCount + PerMoneyExpenses) <= (HHSunday_NX * 1000)) { printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2; }
        else {
            for (int j = 0; j < (84 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
            printf("%s ✅", SpacingCompletion);
        }
    } if (CountBars == 40) { printf("❌"); }
    puts(""); CountBars = 0; CountSpaces = 0; SpacingCompletion[0] = 0;

    puts(BRIGHTBLUE159"\t────────────────────────────────────────────────────────────────────────────────────────────────────");
    printf("\t%s (%lldK): Rp%lld,00 each.\n", SQUARE_BAR, (PerMoneyExpenses / 1000), PerMoneyExpenses);
    printf("\t✅\t: Histogram complete without any exceeding values.\n");
    printf("\t❌\t: Histogram DOESN'T complete because of exceeding values.\n");
    printf("\t➜ N\t: Report the exceeding values separately (N-th position).");

    puts("");
}
/* TRIAL PURPOSES */
/* TRIAL PURPOSES */
/* TRIAL PURPOSES */

/* ACTUAL HISTOGRAM DISPLAY FEATURE */
/* ACTUAL HISTOGRAM DISPLAY FEATURE */
/* ACTUAL HISTOGRAM DISPLAY FEATURE */
void HorizontalHistogramUI_MONTH(const char* SourceFileTxtData, signed long long int PerMoneyExpenses) {
    fflush(stdout); fflush(stdin);

    time_t Time = time(NULL);
    struct tm ManageTime = *localtime(&Time);

    FILE *FDestination, *FTempDestination;
    signed int CountBars = 0, CountSpaces = 0, BufLen;
    char DisplayingSFTD[BUFSIZE07], FDBuffer[BUFSIZE16], SpacingCompletion[BUFSIZE07], TempRecordedTransactions[BUFSIZE07];
    char DeleteTempDestinationTxtFile[BUFSIZE07];
    char *FinalTempRecordedTransactions, *DisplayingMonth, *DisplayingYear;

    signed int RecordedTransactions = 0;
    signed long long int TotalExpensePerDay = 0;
    char SaveLastInputDate[BUFSIZE07], TempCurrentDate[BUFSIZE07], DisplayDateAtYAxis[BUFSIZE07];
    char TempTotalExpensePerDay[BUFSIZE07];
    char *FinalTempTotalExpensePerDay;
    char *CurrentDate;
    // bool IfExpense = true;

    strncpy(DisplayingSFTD, SourceFileTxtData, BUFSIZE07);
    strtok_r(DisplayingSFTD, "-", &DisplayingMonth); DisplayingMonth = TrimWhiteSpaces(DisplayingMonth);
    strtok_r(DisplayingMonth, "-", &DisplayingYear); DisplayingYear = TrimWhiteSpaces(DisplayingYear);
    strtok_r(DisplayingYear, "-", &DisplayingMonth); DisplayingMonth = TrimWhiteSpaces(DisplayingMonth);
    DisplayingMonth = strtok(DisplayingMonth, "-"); DisplayingYear = strtok(NULL, ".");

    FDestination     = fopen(SourceFileTxtData, "r");
    FTempDestination = fopen("TempDestination.txt", "w");

    while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
        BufLen = strlen(FDBuffer);
        for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
        fputs(FDBuffer, FTempDestination);
    } fclose(FDestination); fclose(FTempDestination);

    snprintf(TempRecordedTransactions, BUFSIZE07, "%s", ReadAndPrintLine("TempDestination.txt", 9));
    TempRecordedTransactions[strlen(TempRecordedTransactions) - 1] = '\0';
    strtok_r(TempRecordedTransactions, ":", &FinalTempRecordedTransactions);
    FinalTempRecordedTransactions = TrimWhiteSpaces(FinalTempRecordedTransactions);
    FinalTempRecordedTransactions = strtok(FinalTempRecordedTransactions, " ");
    RecordedTransactions = atoi(FinalTempRecordedTransactions);

    printf(BRIGHTPINK219"\tDisplaying " ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"%s's "ANSI_COLOR_RESET BRIGHTRED216"Histogram over THEIR Recorded Transaction History, \n\t"ANSI_COLOR_RESET BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"on (%s, %s); featuring for \"Expense(s)\" ONLY... .\n\n"ANSI_COLOR_RESET, UserName, DisplayingMonth, DisplayingYear);
    puts(BRIGHTBLUE159"\t────────────────────────────────────────────────────────────────────────────────────────────────────");
    
    for (int i = 0; i < RecordedTransactions; i++) {
        strncpy(TempCurrentDate, ReadAndPrintLine("TempDestination.txt", (i * 10) + 12), BUFSIZE07);
        strtok_r(TempCurrentDate, ":", &CurrentDate); CurrentDate = TrimWhiteSpaces(CurrentDate);
        strtok(CurrentDate, " "); CurrentDate = TrimWhiteSpaces(CurrentDate);
        strtok_r(CurrentDate, "-", &CurrentDate); strtok_r(CurrentDate, "-", &CurrentDate);
        // printf("%s || %s\n", SaveLastInputDate, CurrentDate);
        // printf("%d %d\n", i, RecordedTransactions - 1);

        if (strlen(SaveLastInputDate) == 0) {
            strcpy(SaveLastInputDate, CurrentDate);
            snprintf(DisplayDateAtYAxis, BUFSIZE07, "%s-%02d-%04d", CurrentDate, (ManageTime.tm_mon + 1), (1900 + ManageTime.tm_year));

            if (strstr(ReadAndPrintLine("TempDestination.txt", (i * 10) + 15), "Expense(s)") != NULL) {
                strcpy(TempTotalExpensePerDay, ReadAndPrintLine("TempDestination.txt", (i * 10) + 16)); TempTotalExpensePerDay[strlen(TempTotalExpensePerDay) - 1] = '\0';
                strtok_r(TempTotalExpensePerDay, ":", &FinalTempTotalExpensePerDay);
                FinalTempTotalExpensePerDay = TrimWhiteSpaces(FinalTempTotalExpensePerDay);
                strtok(FinalTempTotalExpensePerDay, ","); FinalTempTotalExpensePerDay = TrimWhiteSpaces(FinalTempTotalExpensePerDay);
                FinalTempTotalExpensePerDay = strtok(FinalTempTotalExpensePerDay, "Rp"); FinalTempTotalExpensePerDay = TrimWhiteSpaces(FinalTempTotalExpensePerDay);
                TotalExpensePerDay += (long long)atoi(FinalTempTotalExpensePerDay);
                // printf("%lld\n", TotalExpensePerDay);
            }
        
        } else if (strlen(SaveLastInputDate) != 0 && strcmp(SaveLastInputDate, CurrentDate) == 0) {
            strcpy(SaveLastInputDate, CurrentDate);
            snprintf(DisplayDateAtYAxis, BUFSIZE07, "%s-%02d-%04d", CurrentDate, (ManageTime.tm_mon + 1), (1900 + ManageTime.tm_year));

            if (strstr(ReadAndPrintLine("TempDestination.txt", (i * 10) + 15), "Expense(s)") != NULL) {
                strcpy(TempTotalExpensePerDay, ReadAndPrintLine("TempDestination.txt", (i * 10) + 16)); TempTotalExpensePerDay[strlen(TempTotalExpensePerDay) - 1] = '\0';
                strtok_r(TempTotalExpensePerDay, ":", &FinalTempTotalExpensePerDay);
                FinalTempTotalExpensePerDay = TrimWhiteSpaces(FinalTempTotalExpensePerDay);
                strtok(FinalTempTotalExpensePerDay, ","); FinalTempTotalExpensePerDay = TrimWhiteSpaces(FinalTempTotalExpensePerDay);
                FinalTempTotalExpensePerDay = strtok(FinalTempTotalExpensePerDay, "Rp"); FinalTempTotalExpensePerDay = TrimWhiteSpaces(FinalTempTotalExpensePerDay);
                TotalExpensePerDay += (long long)atoi(FinalTempTotalExpensePerDay);
                // printf("%lld\n", TotalExpensePerDay);
            }
        
        }
        
        if (strlen(SaveLastInputDate) != 0 && strcmp(SaveLastInputDate, CurrentDate) != 0 && i != (RecordedTransactions - 1)) {
            printf(BRIGHTBLUE159"\t %s │ ", DisplayDateAtYAxis); strcpy(SpacingCompletion, " ");
            for (int PerExpenseCount = 0; PerExpenseCount < (TotalExpensePerDay); PerExpenseCount += PerMoneyExpenses) {
                if (CountBars == 40) { printf(" ➜ "); break; }
                if ((PerExpenseCount + PerMoneyExpenses) < (TotalExpensePerDay)) { printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2; }
                if ((PerExpenseCount + PerMoneyExpenses) == (TotalExpensePerDay)) {
                    printf("%s", SQUARE_BAR); CountBars++; // CountSpaces += 2;
                    for (int j = 0; j < (79 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
                    printf("%s ✅", SpacingCompletion);
                    
                    puts("");
                    printf(BRIGHTGREEN156 ANSI_STYLE_ITALIC"\t      INFO: "ANSI_COLOR_RESET BRIGHTBLUE159"│"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_ITALIC" (B: %02d); (A: Rp%lld,00); (D: Rp%lld,00)\n"ANSI_COLOR_RESET BRIGHTBLUE159, CountBars, (PerExpenseCount + PerMoneyExpenses), (TotalExpensePerDay - (PerExpenseCount + PerMoneyExpenses)));
                } if ((PerExpenseCount + PerMoneyExpenses) > (TotalExpensePerDay)) {
                    // printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2;
                    for (int j = 0; j < (81 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
                    printf("%s ✅", SpacingCompletion);
                    
                    puts("");
                    printf(BRIGHTGREEN156 ANSI_STYLE_ITALIC"\t      INFO: "ANSI_COLOR_RESET BRIGHTBLUE159"│"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_ITALIC" (B: %02d); (A: Rp%lld,00); (D: Rp%lld,00)\n"ANSI_COLOR_RESET BRIGHTBLUE159, CountBars, ((PerMoneyExpenses * CountBars)), (TotalExpensePerDay - (PerMoneyExpenses * CountBars)));
                }
            } if (CountBars == 40) {
                printf("❌");
                
                puts("");
                printf(BRIGHTGREEN156 ANSI_STYLE_ITALIC"\t      INFO: "ANSI_COLOR_RESET BRIGHTBLUE159"│"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_ITALIC" (B: %02d); (A: Rp%lld,00); (D: Rp%lld,00)\n"ANSI_COLOR_RESET BRIGHTBLUE159, CountBars, ((PerMoneyExpenses * CountBars)), (TotalExpensePerDay - (PerMoneyExpenses * CountBars)));
            }
            // printf("%d %d\n", CountBars, CountSpaces);

            CountBars = 0; CountSpaces = 0; // SpacingCompletion[0] = 0;
            TotalExpensePerDay = 0; // RecordedTransactions = 0; SaveLastInputDate[0] = 0; TempTotalExpensePerDay[0] = 0;
            // FinalTempTotalExpensePerDay[0] = 0; DisplayDateAtYAxis[0] = 0; TempCurrentDate[0] = 0;
            
            strcpy(SaveLastInputDate, CurrentDate);
            snprintf(DisplayDateAtYAxis, BUFSIZE07, "%s-%02d-%04d", CurrentDate, (ManageTime.tm_mon + 1), (1900 + ManageTime.tm_year));

            if (strstr(ReadAndPrintLine("TempDestination.txt", (i * 10) + 15), "Expense(s)") != NULL) {
                strcpy(TempTotalExpensePerDay, ReadAndPrintLine("TempDestination.txt", (i * 10) + 16)); TempTotalExpensePerDay[strlen(TempTotalExpensePerDay) - 1] = '\0';
                strtok_r(TempTotalExpensePerDay, ":", &FinalTempTotalExpensePerDay);
                FinalTempTotalExpensePerDay = TrimWhiteSpaces(FinalTempTotalExpensePerDay);
                strtok(FinalTempTotalExpensePerDay, ","); FinalTempTotalExpensePerDay = TrimWhiteSpaces(FinalTempTotalExpensePerDay);
                FinalTempTotalExpensePerDay = strtok(FinalTempTotalExpensePerDay, "Rp"); FinalTempTotalExpensePerDay = TrimWhiteSpaces(FinalTempTotalExpensePerDay);
                TotalExpensePerDay += (long long)atoi(FinalTempTotalExpensePerDay);
                // printf("%lld\n", TotalExpensePerDay);
            }
        
        } else if (strlen(SaveLastInputDate) != 0 && strcmp(SaveLastInputDate, CurrentDate) != 0 && i == (RecordedTransactions - 1)) {
            printf(BRIGHTBLUE159"\t %s │ ", DisplayDateAtYAxis); strcpy(SpacingCompletion, " ");
            for (int PerExpenseCount = 0; PerExpenseCount < (TotalExpensePerDay); PerExpenseCount += PerMoneyExpenses) {
                if (CountBars == 40) { printf(" ➜ "); break; }
                if ((PerExpenseCount + PerMoneyExpenses) < (TotalExpensePerDay)) { printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2; }
                if ((PerExpenseCount + PerMoneyExpenses) == (TotalExpensePerDay)) {
                    printf("%s", SQUARE_BAR); CountBars++; // CountSpaces += 2;
                    for (int j = 0; j < (79 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
                    printf("%s ✅", SpacingCompletion);
                    
                    puts("");
                    printf(BRIGHTGREEN156 ANSI_STYLE_ITALIC"\t      INFO: "ANSI_COLOR_RESET BRIGHTBLUE159"│"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_ITALIC" (B: %02d); (A: Rp%lld,00); (D: Rp%lld,00)\n"ANSI_COLOR_RESET BRIGHTBLUE159, CountBars, (PerExpenseCount + PerMoneyExpenses), (TotalExpensePerDay - (PerExpenseCount + PerMoneyExpenses)));
                } if ((PerExpenseCount + PerMoneyExpenses) > (TotalExpensePerDay)) {
                    // printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2;
                    for (int j = 0; j < (81 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
                    printf("%s ✅", SpacingCompletion);
                    
                    puts("");
                    printf(BRIGHTGREEN156 ANSI_STYLE_ITALIC"\t      INFO: "ANSI_COLOR_RESET BRIGHTBLUE159"│"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_ITALIC" (B: %02d); (A: Rp%lld,00); (D: Rp%lld,00)\n"ANSI_COLOR_RESET BRIGHTBLUE159, CountBars, ((PerMoneyExpenses * CountBars)), (TotalExpensePerDay - (PerMoneyExpenses * CountBars)));
                }
            } if (CountBars == 40) {
                printf("❌");
                
                puts("");
                printf(BRIGHTGREEN156 ANSI_STYLE_ITALIC"\t      INFO: "ANSI_COLOR_RESET BRIGHTBLUE159"│"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_ITALIC" (B: %02d); (A: Rp%lld,00); (D: Rp%lld,00)\n"ANSI_COLOR_RESET BRIGHTBLUE159, CountBars, ((PerMoneyExpenses * CountBars)), (TotalExpensePerDay - (PerMoneyExpenses * CountBars)));
            }
            // printf("%d %d\n", CountBars, CountSpaces);

            CountBars = 0; CountSpaces = 0; // SpacingCompletion[0] = 0;
            TotalExpensePerDay = 0; RecordedTransactions = 0; SaveLastInputDate[0] = 0; TempTotalExpensePerDay[0] = 0;
            FinalTempTotalExpensePerDay[0] = 0; DisplayDateAtYAxis[0] = 0; TempCurrentDate[0] = 0;
            
            strcpy(SaveLastInputDate, CurrentDate);
            snprintf(DisplayDateAtYAxis, BUFSIZE07, "%s-%02d-%04d", CurrentDate, (ManageTime.tm_mon + 1), (1900 + ManageTime.tm_year));

            if (strstr(ReadAndPrintLine("TempDestination.txt", (i * 10) + 15), "Expense(s)") != NULL) {
                strcpy(TempTotalExpensePerDay, ReadAndPrintLine("TempDestination.txt", (i * 10) + 16)); TempTotalExpensePerDay[strlen(TempTotalExpensePerDay) - 1] = '\0';
                strtok_r(TempTotalExpensePerDay, ":", &FinalTempTotalExpensePerDay);
                FinalTempTotalExpensePerDay = TrimWhiteSpaces(FinalTempTotalExpensePerDay);
                strtok(FinalTempTotalExpensePerDay, ","); FinalTempTotalExpensePerDay = TrimWhiteSpaces(FinalTempTotalExpensePerDay);
                FinalTempTotalExpensePerDay = strtok(FinalTempTotalExpensePerDay, "Rp"); FinalTempTotalExpensePerDay = TrimWhiteSpaces(FinalTempTotalExpensePerDay);
                TotalExpensePerDay += (long long)atoi(FinalTempTotalExpensePerDay);
                // printf("%lld\n", TotalExpensePerDay);
            }

            printf(BRIGHTBLUE159"\t %s │ ", DisplayDateAtYAxis); strcpy(SpacingCompletion, " ");
            for (int PerExpenseCount = 0; PerExpenseCount < (TotalExpensePerDay); PerExpenseCount += PerMoneyExpenses) {
                if (CountBars == 40) { printf(" ➜ "); break; }
                if ((PerExpenseCount + PerMoneyExpenses) < (TotalExpensePerDay)) { printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2; }
                if ((PerExpenseCount + PerMoneyExpenses) == (TotalExpensePerDay)) {
                    printf("%s", SQUARE_BAR); CountBars++; // CountSpaces += 2;
                    for (int j = 0; j < (79 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
                    printf("%s ✅", SpacingCompletion);
                    
                    puts("");
                    printf(BRIGHTGREEN156 ANSI_STYLE_ITALIC"\t      INFO: "ANSI_COLOR_RESET BRIGHTBLUE159"│"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_ITALIC" (B: %02d); (A: Rp%lld,00); (D: Rp%lld,00)\n"ANSI_COLOR_RESET BRIGHTBLUE159, CountBars, (PerExpenseCount + PerMoneyExpenses), (TotalExpensePerDay - (PerExpenseCount + PerMoneyExpenses)));
                } if ((PerExpenseCount + PerMoneyExpenses) > (TotalExpensePerDay)) {
                    // printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2;
                    for (int j = 0; j < (81 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
                    printf("%s ✅", SpacingCompletion);
                    
                    puts("");
                    printf(BRIGHTGREEN156 ANSI_STYLE_ITALIC"\t      INFO: "ANSI_COLOR_RESET BRIGHTBLUE159"│"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_ITALIC" (B: %02d); (A: Rp%lld,00); (D: Rp%lld,00)\n"ANSI_COLOR_RESET BRIGHTBLUE159, CountBars, ((PerMoneyExpenses * CountBars)), (TotalExpensePerDay - (PerMoneyExpenses * CountBars)));
                }
            } if (CountBars == 40) {
                printf("❌");
                
                puts("");
                printf(BRIGHTGREEN156 ANSI_STYLE_ITALIC"\t      INFO: "ANSI_COLOR_RESET BRIGHTBLUE159"│"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_ITALIC" (B: %02d); (A: Rp%lld,00); (D: Rp%lld,00)\n"ANSI_COLOR_RESET BRIGHTBLUE159, CountBars, ((PerMoneyExpenses * CountBars)), (TotalExpensePerDay - (PerMoneyExpenses * CountBars)));
            }

            CountBars = 0; CountSpaces = 0; // SpacingCompletion[0] = 0;
            TotalExpensePerDay = 0; RecordedTransactions = 0; SaveLastInputDate[0] = 0; TempTotalExpensePerDay[0] = 0;
            FinalTempTotalExpensePerDay[0] = 0; DisplayDateAtYAxis[0] = 0; TempCurrentDate[0] = 0;
        
        } else if (strlen(SaveLastInputDate) != 0 && strcmp(SaveLastInputDate, CurrentDate) == 0 && i == (RecordedTransactions - 1)) {
            printf(BRIGHTBLUE159"\t %s │ ", DisplayDateAtYAxis); strcpy(SpacingCompletion, " ");
            for (int PerExpenseCount = 0; PerExpenseCount < (TotalExpensePerDay); PerExpenseCount += PerMoneyExpenses) {
                if (CountBars == 40) { printf(" ➜ "); break; }
                if ((PerExpenseCount + PerMoneyExpenses) < (TotalExpensePerDay)) { printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2; }
                if ((PerExpenseCount + PerMoneyExpenses) == (TotalExpensePerDay)) {
                    printf("%s", SQUARE_BAR); CountBars++; // CountSpaces += 2;
                    for (int j = 0; j < (79 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
                    printf("%s ✅", SpacingCompletion);
                    
                    puts("");
                    printf(BRIGHTGREEN156 ANSI_STYLE_ITALIC"\t      INFO: "ANSI_COLOR_RESET BRIGHTBLUE159"│"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_ITALIC" (B: %02d); (A: Rp%lld,00); (D: Rp%lld,00)\n"ANSI_COLOR_RESET BRIGHTBLUE159, CountBars, (PerExpenseCount + PerMoneyExpenses), (TotalExpensePerDay - (PerExpenseCount + PerMoneyExpenses)));
                } if ((PerExpenseCount + PerMoneyExpenses) > (TotalExpensePerDay)) {
                    // printf("%s", SQUARE_BAR); CountBars++; CountSpaces += 2;
                    for (int j = 0; j < (81 - CountSpaces); j++) { strcat(SpacingCompletion, " "); }
                    printf("%s ✅", SpacingCompletion);
                    
                    puts("");
                    printf(BRIGHTGREEN156 ANSI_STYLE_ITALIC"\t      INFO: "ANSI_COLOR_RESET BRIGHTBLUE159"│"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_ITALIC" (B: %02d); (A: Rp%lld,00); (D: Rp%lld,00)\n"ANSI_COLOR_RESET BRIGHTBLUE159, CountBars, ((PerMoneyExpenses * CountBars)), (TotalExpensePerDay - (PerMoneyExpenses * CountBars)));
                }
            } if (CountBars == 40) {
                printf("❌");
                
                puts("");
                printf(BRIGHTGREEN156 ANSI_STYLE_ITALIC"\t      INFO: "ANSI_COLOR_RESET BRIGHTBLUE159"│"ANSI_COLOR_RESET BRIGHTGREEN156 ANSI_STYLE_ITALIC" (B: %02d); (A: Rp%lld,00); (D: Rp%lld,00)\n"ANSI_COLOR_RESET BRIGHTBLUE159, CountBars, ((PerMoneyExpenses * CountBars)), (TotalExpensePerDay - (PerMoneyExpenses * CountBars)));
            }
            // printf("%d %d\n", CountBars, CountSpaces);
            
            CountBars = 0; CountSpaces = 0; // SpacingCompletion[0] = 0;
            TotalExpensePerDay = 0; RecordedTransactions = 0; SaveLastInputDate[0] = 0; TempTotalExpensePerDay[0] = 0;
            FinalTempTotalExpensePerDay[0] = 0; DisplayDateAtYAxis[0] = 0; TempCurrentDate[0] = 0;
        }
    }

    strcpy(DeleteTempDestinationTxtFile, "del ");
    strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
    system(DeleteTempDestinationTxtFile);

    // puts("");
    puts(BRIGHTBLUE159"\t────────────────────────────────────────────────────────────────────────────────────────────────────"ANSI_COLOR_RESET);
    puts(BRIGHTBLUE159 ANSI_STYLE_BOLD"\tImportant Status/Flags:"ANSI_COLOR_RESET);
    printf(BRIGHTBLUE159 ANSI_STYLE_BOLD"\t%s: (%.3lfK) ➜  Rp%lld,00 each bars (total 40 bars, at max.; uneditable)\n"ANSI_COLOR_RESET, SQUARE_BAR, ((double)PerMoneyExpenses / 1000), PerMoneyExpenses);
    printf(BRIGHTBLUE158"\t✅: Histogram DOES COMPLETE without any exceeding values present.\n");
    printf("\t❌: Histogram DOESN'T COMPLETE because of the exceeding values behind the next bars.\n");
    printf("\t        > (try to increase the each bars' divisor per money expenses in the CONFIGURATION file)\n");
    printf("\t        > (for example: BEFORE = %.3lfK ➜  AFTER = %.3lfK)\n"ANSI_COLOR_RESET, ((double)PerMoneyExpenses / 1000), ((double)PerMoneyExpenses / 1000) * RandInt(2, 11));

    puts(BRIGHTBLUE159 ANSI_STYLE_BOLD"\n\tAdditional Notes:"ANSI_COLOR_RESET);
    printf(BRIGHTBLUE158"\tB:  Total bars accumulated on each transactions' per day.\n");
    printf("\tA:  Each accumulated spending added definitely by the divisor of spent money on each bars.\n");
    printf("\t        > (see the definition of the 'white bar/square' above)\n");
    printf("\tD:  Leftover accumulated money that can't be represented enough in a single bar, but also because no\n");
    printf("\t    spaces left to be able to adding more bars, thus it's a difference in between the two.\n");
    printf("\t        > (accumulated spending - total spent on actual recorded transaction history)\n"ANSI_COLOR_RESET);

    puts("");
    getchar(); MainMenuApplicationFeatures(MMAFSelected);
}
/* ACTUAL HISTOGRAM DISPLAY FEATURE */
/* ACTUAL HISTOGRAM DISPLAY FEATURE */
/* ACTUAL HISTOGRAM DISPLAY FEATURE */

/* STARTING THE DECLARATIONS: RANDOM NUMBER GENERATOR */
/* Initialize functions and classes (if needed) */

int RandInt(int Lower, int Upper) {
    return (int)(rand() % ((Upper - Lower) + 1)) + Lower;
}

/* STARTING THE DECLARATIONS: F1 LIST OF FINANCIAL CATEGORIES */
/* Initialize functions and classes (if needed) */

void F1_FUC01_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 10; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI01, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 1 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 0 && (FUCSelected + 1) <= 10 && (AvailableOptions == 10)) {
                if ((FUCSelected + 1) == 1) {
                    printf("      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Account Receiveable\n\t"ANSI_COLOR_RESET "Additional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 2) {
                    printf("\tAccount Receiveable\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Additional Income\n\t"ANSI_COLOR_RESET "Allowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 3) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Allowance\n\t"ANSI_COLOR_RESET "Electricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 4) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Electricity, Water, and Gas\n\t"ANSI_COLOR_RESET "House and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 5) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> House and Appartment Rent\n\t"ANSI_COLOR_RESET "Household\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 6) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Household\n\t"ANSI_COLOR_RESET "Insurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 7) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Insurance\n\t"ANSI_COLOR_RESET "Mobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 8) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Mobile and Data\n\t"ANSI_COLOR_RESET "Handheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 9) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Handheld Electric Device\n\t"ANSI_COLOR_RESET "TV and Internet\n\n");
                } else if ((FUCSelected + 1) == 10) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> TV and Internet\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI01UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI01, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 1 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 0 && (FUCSelected + 1) <= 10 && (AvailableOptions == 10)) {
                if ((FUCSelected + 1) == 1) {
                    printf("      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Account Receiveable\n\t"ANSI_COLOR_RESET "Additional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 2) {
                    printf("\tAccount Receiveable\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Additional Income\n\t"ANSI_COLOR_RESET "Allowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 3) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Allowance\n\t"ANSI_COLOR_RESET "Electricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 4) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Electricity, Water, and Gas\n\t"ANSI_COLOR_RESET "House and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 5) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> House and Appartment Rent\n\t"ANSI_COLOR_RESET "Household\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 6) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Household\n\t"ANSI_COLOR_RESET "Insurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 7) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n      "BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Insurance\n\t"ANSI_COLOR_RESET "Mobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 8) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n      "BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Mobile and Data\n\t"ANSI_COLOR_RESET "Handheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 9) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n      "BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Handheld Electric Device\n\t"ANSI_COLOR_RESET "TV and Internet\n\n");
                } else if ((FUCSelected + 1) == 10) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n      "BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> TV and Internet\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI01UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 0 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 0) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 0 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 0; Updated = true;
                } break;
            case KEY_RIGHT:
                F1_FUC02_FinancialUsesCategoryUI(10);
                break;
            case KEY_LEFT:
                F1_FUC06_FinancialUsesCategoryUI(50);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } strncpy(MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, FinancialUsesCategoryListing[FUCSelected], BUFSIZE07);
    F1_MoneytoryTransactionsRegister(F1Selected);
}

void F1_FUC02_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 20; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI02, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 2 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 10 && (FUCSelected + 1) <= 20 && (AvailableOptions == 20)) {
                if ((FUCSelected + 1) == 11) {
                    printf("      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Bonus\n\t"ANSI_COLOR_RESET "Business Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 12) {
                    printf("\tBonus\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Business Profit\n\t"ANSI_COLOR_RESET "Classes and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 13) {
                    printf("\tBonus\n\tBusiness Profit\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Classes and Workshops\n\t"ANSI_COLOR_RESET "School Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 14) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> School Supplies\n\t"ANSI_COLOR_RESET "Tuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 15) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Tuition Fee\n\t"ANSI_COLOR_RESET "Children and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 16) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Children and Family Needs\n\t"ANSI_COLOR_RESET "Parents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 17) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Parents and Family Needs\n\t"ANSI_COLOR_RESET "Daily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 18) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Daily Meal\n\t"ANSI_COLOR_RESET "Snacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 19) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Snacks and Drinks\n\t"ANSI_COLOR_RESET "Gifting\n\n");
                } else if ((FUCSelected + 1) == 20) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Gifting\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI02UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI02, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 2 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 10 && (FUCSelected + 1) <= 20 && (AvailableOptions == 20)) {
                if ((FUCSelected + 1) == 11) {
                    printf("      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Bonus\n\t"ANSI_COLOR_RESET "Business Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 12) {
                    printf("\tBonus\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Business Profit\n\t"ANSI_COLOR_RESET "Classes and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 13) {
                    printf("\tBonus\n\tBusiness Profit\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Classes and Workshops\n\t"ANSI_COLOR_RESET "School Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 14) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> School Supplies\n\t"ANSI_COLOR_RESET "Tuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 15) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Tuition Fee\n\t"ANSI_COLOR_RESET "Children and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 16) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Children and Family Needs\n\t"ANSI_COLOR_RESET "Parents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 17) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Parents and Family Needs\n\t"ANSI_COLOR_RESET "Daily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 18) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Daily Meal\n\t"ANSI_COLOR_RESET "Snacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 19) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Snacks and Drinks\n\t"ANSI_COLOR_RESET "Gifting\n\n");
                } else if ((FUCSelected + 1) == 20) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Gifting\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI02UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 10 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 10) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 10 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 10; Updated = true;
                } break;
            case KEY_RIGHT:
                F1_FUC03_FinancialUsesCategoryUI(20);
                break;
            case KEY_LEFT:
                F1_FUC01_FinancialUsesCategoryUI(0);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } strncpy(MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, FinancialUsesCategoryListing[FUCSelected], BUFSIZE07);
    F1_MoneytoryTransactionsRegister(F1Selected);
}

void F1_FUC03_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 30; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI03, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 3 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 20 && (FUCSelected + 1) <= 30 && (AvailableOptions == 30)) {
                if ((FUCSelected + 1) == 21) {
                    printf("      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Charity\n\t"ANSI_COLOR_RESET "Groceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 22) {
                    printf("\tCharity\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Groceries\n\t"ANSI_COLOR_RESET "Doctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 23) {
                    printf("\tCharity\n\tGroceries\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Doctor and Hospital\n\t"ANSI_COLOR_RESET "Medicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 24) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Medicines\n\t"ANSI_COLOR_RESET "Personal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 25) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Personal Care\n\t"ANSI_COLOR_RESET "Books\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 26) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Books\n\t"ANSI_COLOR_RESET "Dining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 27) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Dining Out\n\t"ANSI_COLOR_RESET "Games\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 28) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Games\n\t"ANSI_COLOR_RESET "Hobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 29) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Hobby\n\t"ANSI_COLOR_RESET "Movies and Music\n\n");
                } else if ((FUCSelected + 1) == 30) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Movies and Music\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI03UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI03, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 3 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 20 && (FUCSelected + 1) <= 30 && (AvailableOptions == 30)) {
                if ((FUCSelected + 1) == 21) {
                    printf("      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Charity\n\t"ANSI_COLOR_RESET "Groceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 22) {
                    printf("\tCharity\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Groceries\n\t"ANSI_COLOR_RESET "Doctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 23) {
                    printf("\tCharity\n\tGroceries\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Doctor and Hospital\n\t"ANSI_COLOR_RESET "Medicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 24) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Medicines\n\t"ANSI_COLOR_RESET "Personal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 25) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Personal Care\n\t"ANSI_COLOR_RESET "Books\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 26) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Books\n\t"ANSI_COLOR_RESET "Dining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 27) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Dining Out\n\t"ANSI_COLOR_RESET "Games\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 28) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Games\n\t"ANSI_COLOR_RESET "Hobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 29) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Hobby\n\t"ANSI_COLOR_RESET "Movies and Music\n\n");
                } else if ((FUCSelected + 1) == 30) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Movies and Music\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI03UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 20 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 20) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 20 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 20; Updated = true;
                } break;
            case KEY_RIGHT:
                F1_FUC04_FinancialUsesCategoryUI(30);
                break;
            case KEY_LEFT:
                F1_FUC02_FinancialUsesCategoryUI(10);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } strncpy(MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, FinancialUsesCategoryListing[FUCSelected], BUFSIZE07);
    F1_MoneytoryTransactionsRegister(F1Selected);
}

void F1_FUC04_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 40; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI04, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 4 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 30 && (FUCSelected + 1) <= 40 && (AvailableOptions == 40)) {
                if ((FUCSelected + 1) == 31) {
                    printf("      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Pets\n\t"ANSI_COLOR_RESET "Incomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 32) {
                    printf("\tPets\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Incomings\n\t"ANSI_COLOR_RESET "Interests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 33) {
                    printf("\tPets\n\tIncomings\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Interests\n\t"ANSI_COLOR_RESET "Investments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 34) {
                    printf("\tPets\n\tIncomings\n\tInterests\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Investments Withdrawal\n\t"ANSI_COLOR_RESET "Loan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 35) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Loan Disbursements\n\t"ANSI_COLOR_RESET "Car Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 36) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Car Installments\n\t"ANSI_COLOR_RESET "Credit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 37) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Credit Card\n\t"ANSI_COLOR_RESET "Home Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 38) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Home Mortgage\n\t"ANSI_COLOR_RESET "Refunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 39) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Refunds\n\t"ANSI_COLOR_RESET "Reimbursements\n\n");
                } else if ((FUCSelected + 1) == 40) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Reimbursements\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI04UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI04, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 4 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 30 && (FUCSelected + 1) <= 40 && (AvailableOptions == 40)) {
                if ((FUCSelected + 1) == 31) {
                    printf("      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Pets\n\t"ANSI_COLOR_RESET "Incomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 32) {
                    printf("\tPets\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Incomings\n\t"ANSI_COLOR_RESET "Interests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 33) {
                    printf("\tPets\n\tIncomings\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Interests\n\t"ANSI_COLOR_RESET "Investments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 34) {
                    printf("\tPets\n\tIncomings\n\tInterests\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Investments Withdrawal\n\t"ANSI_COLOR_RESET "Loan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 35) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Loan Disbursements\n\t"ANSI_COLOR_RESET "Car Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 36) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Car Installments\n\t"ANSI_COLOR_RESET "Credit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 37) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Credit Card\n\t"ANSI_COLOR_RESET "Home Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 38) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Home Mortgage\n\t"ANSI_COLOR_RESET "Refunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 39) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Refunds\n\t"ANSI_COLOR_RESET "Reimbursements\n\n");
                } else if ((FUCSelected + 1) == 40) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Reimbursements\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI04UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 30 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 30) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 30 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 30; Updated = true;
                } break;
            case KEY_RIGHT:
                F1_FUC05_FinancialUsesCategoryUI(40);
                break;
            case KEY_LEFT:
                F1_FUC03_FinancialUsesCategoryUI(20);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } strncpy(MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, FinancialUsesCategoryListing[FUCSelected], BUFSIZE07);
    F1_MoneytoryTransactionsRegister(F1Selected);
}

void F1_FUC05_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 50; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI05, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 5 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 40 && (FUCSelected + 1) <= 50 && (AvailableOptions == 50)) {
                if ((FUCSelected + 1) == 41) {
                    printf("      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Salary\n\t"ANSI_COLOR_RESET "Investments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 42) {
                    printf("\tSalary\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Investments\n\t"ANSI_COLOR_RESET "Savings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 43) {
                    printf("\tSalary\n\tInvestments\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Savings\n\t"ANSI_COLOR_RESET "Fashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 44) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Fashions\n\t"ANSI_COLOR_RESET "Gadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 45) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Gadget and Electronics\n\t"ANSI_COLOR_RESET "Home Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 46) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Home Appliances\n\t"ANSI_COLOR_RESET "Sport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 47) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Sport Activities\n\t"ANSI_COLOR_RESET "Sport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 48) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Sport Equipments\n\t"ANSI_COLOR_RESET "Daily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 49) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Daily Transportations\n\t"ANSI_COLOR_RESET "Gasolines\n\n");
                } else if ((FUCSelected + 1) == 50) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Gasolines\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI05UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI05, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 5 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 40 && (FUCSelected + 1) <= 50 && (AvailableOptions == 50)) {
                if ((FUCSelected + 1) == 41) {
                    printf("      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Salary\n\t"ANSI_COLOR_RESET "Investments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 42) {
                    printf("\tSalary\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Investments\n\t"ANSI_COLOR_RESET "Savings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 43) {
                    printf("\tSalary\n\tInvestments\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Savings\n\t"ANSI_COLOR_RESET "Fashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 44) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Fashions\n\t"ANSI_COLOR_RESET "Gadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 45) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Gadget and Electronics\n\t"ANSI_COLOR_RESET "Home Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 46) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Home Appliances\n\t"ANSI_COLOR_RESET "Sport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 47) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Sport Activities\n\t"ANSI_COLOR_RESET "Sport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 48) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Sport Equipments\n\t"ANSI_COLOR_RESET "Daily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 49) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Daily Transportations\n\t"ANSI_COLOR_RESET "Gasolines\n\n");
                } else if ((FUCSelected + 1) == 50) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Gasolines\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI05UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 40 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 40) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 40 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 40; Updated = true;
                } break;
            case KEY_RIGHT:
                F1_FUC06_FinancialUsesCategoryUI(50);
                break;
            case KEY_LEFT:
                F1_FUC04_FinancialUsesCategoryUI(30);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } strncpy(MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, FinancialUsesCategoryListing[FUCSelected], BUFSIZE07);
    F1_MoneytoryTransactionsRegister(F1Selected);
}

void F1_FUC06_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 60; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI06, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 6 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 50 && (FUCSelected + 1) <= 60 && (AvailableOptions == 60)) {
                if ((FUCSelected + 1) == 51) {
                    printf("      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Parking and Toll Fee\n\t"ANSI_COLOR_RESET "Vehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 52) {
                    printf("\tParking and Toll Fee\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Vehicle Maintenance\n\t"ANSI_COLOR_RESET "Attractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 53) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Attractions and Tours\n\t"ANSI_COLOR_RESET "Hotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 54) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Hotel and Villa\n\t"ANSI_COLOR_RESET "Transports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 55) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Transports on Vacations\n\t"ANSI_COLOR_RESET "Cash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 56) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Cash Withdrawal\n\t"ANSI_COLOR_RESET "Cost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 57) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Cost and Taxes\n\t"ANSI_COLOR_RESET "Send to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 58) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Send to Business\n\t"ANSI_COLOR_RESET "Send to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 59) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Send to Personal\n\t"ANSI_COLOR_RESET "Top Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 60) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Top Up e-Wallets and/or Cards\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI06UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI06, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 6 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 50 && (FUCSelected + 1) <= 60 && (AvailableOptions == 60)) {
                if ((FUCSelected + 1) == 51) {
                    printf("      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Parking and Toll Fee\n\t"ANSI_COLOR_RESET "Vehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 52) {
                    printf("\tParking and Toll Fee\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Vehicle Maintenance\n\t"ANSI_COLOR_RESET "Attractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 53) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Attractions and Tours\n\t"ANSI_COLOR_RESET "Hotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 54) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Hotel and Villa\n\t"ANSI_COLOR_RESET "Transports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 55) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Transports on Vacations\n\t"ANSI_COLOR_RESET "Cash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 56) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Cash Withdrawal\n\t"ANSI_COLOR_RESET "Cost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 57) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Cost and Taxes\n\t"ANSI_COLOR_RESET "Send to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 58) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Send to Business\n\t"ANSI_COLOR_RESET "Send to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 59) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Send to Personal\n\t"ANSI_COLOR_RESET "Top Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 60) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Top Up e-Wallets and/or Cards\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI06UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 50 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 50) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 50 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 50; Updated = true;
                } break;
            case KEY_RIGHT:
                F1_FUC01_FinancialUsesCategoryUI(0);
                break;
            case KEY_LEFT:
                F1_FUC05_FinancialUsesCategoryUI(40);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } strncpy(MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, FinancialUsesCategoryListing[FUCSelected], BUFSIZE07);
    F1_MoneytoryTransactionsRegister(F1Selected);
}

/* STARTING THE DECLARATIONS: F2 LIST OF FINANCIAL CATEGORIES */
/* Initialize functions and classes (if needed) */

void F2_FUC01_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 10; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI01, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 1 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 0 && (FUCSelected + 1) <= 10 && (AvailableOptions == 10)) {
                if ((FUCSelected + 1) == 1) {
                    printf("      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Account Receiveable\n\t"ANSI_COLOR_RESET "Additional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 2) {
                    printf("\tAccount Receiveable\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Additional Income\n\t"ANSI_COLOR_RESET "Allowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 3) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Allowance\n\t"ANSI_COLOR_RESET "Electricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 4) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Electricity, Water, and Gas\n\t"ANSI_COLOR_RESET "House and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 5) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> House and Appartment Rent\n\t"ANSI_COLOR_RESET "Household\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 6) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Household\n\t"ANSI_COLOR_RESET "Insurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 7) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Insurance\n\t"ANSI_COLOR_RESET "Mobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 8) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Mobile and Data\n\t"ANSI_COLOR_RESET "Handheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 9) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Handheld Electric Device\n\t"ANSI_COLOR_RESET "TV and Internet\n\n");
                } else if ((FUCSelected + 1) == 10) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> TV and Internet\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI01UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI01, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 1 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 0 && (FUCSelected + 1) <= 10 && (AvailableOptions == 10)) {
                if ((FUCSelected + 1) == 1) {
                    printf("      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Account Receiveable\n\t"ANSI_COLOR_RESET "Additional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 2) {
                    printf("\tAccount Receiveable\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Additional Income\n\t"ANSI_COLOR_RESET "Allowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 3) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Allowance\n\t"ANSI_COLOR_RESET "Electricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 4) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Electricity, Water, and Gas\n\t"ANSI_COLOR_RESET "House and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 5) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> House and Appartment Rent\n\t"ANSI_COLOR_RESET "Household\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 6) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Household\n\t"ANSI_COLOR_RESET "Insurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 7) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n      "BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Insurance\n\t"ANSI_COLOR_RESET "Mobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 8) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n      "BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Mobile and Data\n\t"ANSI_COLOR_RESET "Handheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 9) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n      "BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Handheld Electric Device\n\t"ANSI_COLOR_RESET "TV and Internet\n\n");
                } else if ((FUCSelected + 1) == 10) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n      "BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> TV and Internet\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI01UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 0 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 0) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 0 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 0; Updated = true;
                } break;
            case KEY_RIGHT:
                F2_FUC02_FinancialUsesCategoryUI(10);
                break;
            case KEY_LEFT:
                F2_FUC06_FinancialUsesCategoryUI(50);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } MainMenuApplicationFeatures(MMAFSelected);
}

void F2_FUC02_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 20; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI02, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 2 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 10 && (FUCSelected + 1) <= 20 && (AvailableOptions == 20)) {
                if ((FUCSelected + 1) == 11) {
                    printf("      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Bonus\n\t"ANSI_COLOR_RESET "Business Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 12) {
                    printf("\tBonus\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Business Profit\n\t"ANSI_COLOR_RESET "Classes and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 13) {
                    printf("\tBonus\n\tBusiness Profit\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Classes and Workshops\n\t"ANSI_COLOR_RESET "School Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 14) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> School Supplies\n\t"ANSI_COLOR_RESET "Tuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 15) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Tuition Fee\n\t"ANSI_COLOR_RESET "Children and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 16) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Children and Family Needs\n\t"ANSI_COLOR_RESET "Parents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 17) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Parents and Family Needs\n\t"ANSI_COLOR_RESET "Daily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 18) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Daily Meal\n\t"ANSI_COLOR_RESET "Snacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 19) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Snacks and Drinks\n\t"ANSI_COLOR_RESET "Gifting\n\n");
                } else if ((FUCSelected + 1) == 20) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Gifting\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI02UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI02, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 2 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 10 && (FUCSelected + 1) <= 20 && (AvailableOptions == 20)) {
                if ((FUCSelected + 1) == 11) {
                    printf("      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Bonus\n\t"ANSI_COLOR_RESET "Business Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 12) {
                    printf("\tBonus\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Business Profit\n\t"ANSI_COLOR_RESET "Classes and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 13) {
                    printf("\tBonus\n\tBusiness Profit\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Classes and Workshops\n\t"ANSI_COLOR_RESET "School Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 14) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> School Supplies\n\t"ANSI_COLOR_RESET "Tuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 15) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Tuition Fee\n\t"ANSI_COLOR_RESET "Children and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 16) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Children and Family Needs\n\t"ANSI_COLOR_RESET "Parents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 17) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Parents and Family Needs\n\t"ANSI_COLOR_RESET "Daily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 18) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Daily Meal\n\t"ANSI_COLOR_RESET "Snacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 19) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Snacks and Drinks\n\t"ANSI_COLOR_RESET "Gifting\n\n");
                } else if ((FUCSelected + 1) == 20) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Gifting\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI02UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 10 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 10) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 10 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 10; Updated = true;
                } break;
            case KEY_RIGHT:
                F2_FUC03_FinancialUsesCategoryUI(20);
                break;
            case KEY_LEFT:
                F2_FUC01_FinancialUsesCategoryUI(0);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } MainMenuApplicationFeatures(MMAFSelected);
}

void F2_FUC03_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 30; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI03, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 3 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 20 && (FUCSelected + 1) <= 30 && (AvailableOptions == 30)) {
                if ((FUCSelected + 1) == 21) {
                    printf("      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Charity\n\t"ANSI_COLOR_RESET "Groceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 22) {
                    printf("\tCharity\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Groceries\n\t"ANSI_COLOR_RESET "Doctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 23) {
                    printf("\tCharity\n\tGroceries\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Doctor and Hospital\n\t"ANSI_COLOR_RESET "Medicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 24) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Medicines\n\t"ANSI_COLOR_RESET "Personal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 25) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Personal Care\n\t"ANSI_COLOR_RESET "Books\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 26) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Books\n\t"ANSI_COLOR_RESET "Dining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 27) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Dining Out\n\t"ANSI_COLOR_RESET "Games\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 28) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Games\n\t"ANSI_COLOR_RESET "Hobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 29) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Hobby\n\t"ANSI_COLOR_RESET "Movies and Music\n\n");
                } else if ((FUCSelected + 1) == 30) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Movies and Music\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI03UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI03, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 3 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 20 && (FUCSelected + 1) <= 30 && (AvailableOptions == 30)) {
                if ((FUCSelected + 1) == 21) {
                    printf("      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Charity\n\t"ANSI_COLOR_RESET "Groceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 22) {
                    printf("\tCharity\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Groceries\n\t"ANSI_COLOR_RESET "Doctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 23) {
                    printf("\tCharity\n\tGroceries\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Doctor and Hospital\n\t"ANSI_COLOR_RESET "Medicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 24) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Medicines\n\t"ANSI_COLOR_RESET "Personal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 25) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Personal Care\n\t"ANSI_COLOR_RESET "Books\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 26) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Books\n\t"ANSI_COLOR_RESET "Dining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 27) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Dining Out\n\t"ANSI_COLOR_RESET "Games\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 28) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Games\n\t"ANSI_COLOR_RESET "Hobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 29) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Hobby\n\t"ANSI_COLOR_RESET "Movies and Music\n\n");
                } else if ((FUCSelected + 1) == 30) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Movies and Music\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI03UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 20 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 20) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 20 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 20; Updated = true;
                } break;
            case KEY_RIGHT:
                F2_FUC04_FinancialUsesCategoryUI(30);
                break;
            case KEY_LEFT:
                F2_FUC02_FinancialUsesCategoryUI(10);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } MainMenuApplicationFeatures(MMAFSelected);
}

void F2_FUC04_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 40; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI04, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 4 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 30 && (FUCSelected + 1) <= 40 && (AvailableOptions == 40)) {
                if ((FUCSelected + 1) == 31) {
                    printf("      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Pets\n\t"ANSI_COLOR_RESET "Incomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 32) {
                    printf("\tPets\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Incomings\n\t"ANSI_COLOR_RESET "Interests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 33) {
                    printf("\tPets\n\tIncomings\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Interests\n\t"ANSI_COLOR_RESET "Investments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 34) {
                    printf("\tPets\n\tIncomings\n\tInterests\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Investments Withdrawal\n\t"ANSI_COLOR_RESET "Loan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 35) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Loan Disbursements\n\t"ANSI_COLOR_RESET "Car Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 36) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Car Installments\n\t"ANSI_COLOR_RESET "Credit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 37) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Credit Card\n\t"ANSI_COLOR_RESET "Home Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 38) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Home Mortgage\n\t"ANSI_COLOR_RESET "Refunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 39) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Refunds\n\t"ANSI_COLOR_RESET "Reimbursements\n\n");
                } else if ((FUCSelected + 1) == 40) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Reimbursements\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI04UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI04, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 4 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 30 && (FUCSelected + 1) <= 40 && (AvailableOptions == 40)) {
                if ((FUCSelected + 1) == 31) {
                    printf("      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Pets\n\t"ANSI_COLOR_RESET "Incomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 32) {
                    printf("\tPets\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Incomings\n\t"ANSI_COLOR_RESET "Interests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 33) {
                    printf("\tPets\n\tIncomings\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Interests\n\t"ANSI_COLOR_RESET "Investments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 34) {
                    printf("\tPets\n\tIncomings\n\tInterests\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Investments Withdrawal\n\t"ANSI_COLOR_RESET "Loan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 35) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Loan Disbursements\n\t"ANSI_COLOR_RESET "Car Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 36) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Car Installments\n\t"ANSI_COLOR_RESET "Credit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 37) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Credit Card\n\t"ANSI_COLOR_RESET "Home Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 38) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Home Mortgage\n\t"ANSI_COLOR_RESET "Refunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 39) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Refunds\n\t"ANSI_COLOR_RESET "Reimbursements\n\n");
                } else if ((FUCSelected + 1) == 40) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Reimbursements\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI04UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 30 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 30) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 30 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 30; Updated = true;
                } break;
            case KEY_RIGHT:
                F2_FUC05_FinancialUsesCategoryUI(40);
                break;
            case KEY_LEFT:
                F2_FUC03_FinancialUsesCategoryUI(20);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } MainMenuApplicationFeatures(MMAFSelected);
}

void F2_FUC05_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 50; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI05, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 5 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 40 && (FUCSelected + 1) <= 50 && (AvailableOptions == 50)) {
                if ((FUCSelected + 1) == 41) {
                    printf("      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Salary\n\t"ANSI_COLOR_RESET "Investments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 42) {
                    printf("\tSalary\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Investments\n\t"ANSI_COLOR_RESET "Savings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 43) {
                    printf("\tSalary\n\tInvestments\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Savings\n\t"ANSI_COLOR_RESET "Fashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 44) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Fashions\n\t"ANSI_COLOR_RESET "Gadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 45) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Gadget and Electronics\n\t"ANSI_COLOR_RESET "Home Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 46) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Home Appliances\n\t"ANSI_COLOR_RESET "Sport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 47) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Sport Activities\n\t"ANSI_COLOR_RESET "Sport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 48) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Sport Equipments\n\t"ANSI_COLOR_RESET "Daily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 49) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Daily Transportations\n\t"ANSI_COLOR_RESET "Gasolines\n\n");
                } else if ((FUCSelected + 1) == 50) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Gasolines\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI05UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI05, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 5 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 40 && (FUCSelected + 1) <= 50 && (AvailableOptions == 50)) {
                if ((FUCSelected + 1) == 41) {
                    printf("      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Salary\n\t"ANSI_COLOR_RESET "Investments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 42) {
                    printf("\tSalary\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Investments\n\t"ANSI_COLOR_RESET "Savings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 43) {
                    printf("\tSalary\n\tInvestments\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Savings\n\t"ANSI_COLOR_RESET "Fashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 44) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Fashions\n\t"ANSI_COLOR_RESET "Gadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 45) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Gadget and Electronics\n\t"ANSI_COLOR_RESET "Home Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 46) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Home Appliances\n\t"ANSI_COLOR_RESET "Sport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 47) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Sport Activities\n\t"ANSI_COLOR_RESET "Sport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 48) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Sport Equipments\n\t"ANSI_COLOR_RESET "Daily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 49) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Daily Transportations\n\t"ANSI_COLOR_RESET "Gasolines\n\n");
                } else if ((FUCSelected + 1) == 50) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Gasolines\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI05UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 40 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 40) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 40 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 40; Updated = true;
                } break;
            case KEY_RIGHT:
                F2_FUC06_FinancialUsesCategoryUI(50);
                break;
            case KEY_LEFT:
                F2_FUC04_FinancialUsesCategoryUI(30);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } MainMenuApplicationFeatures(MMAFSelected);
}

void F2_FUC06_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 60; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI06, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 6 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 50 && (FUCSelected + 1) <= 60 && (AvailableOptions == 60)) {
                if ((FUCSelected + 1) == 51) {
                    printf("      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Parking and Toll Fee\n\t"ANSI_COLOR_RESET "Vehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 52) {
                    printf("\tParking and Toll Fee\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Vehicle Maintenance\n\t"ANSI_COLOR_RESET "Attractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 53) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Attractions and Tours\n\t"ANSI_COLOR_RESET "Hotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 54) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Hotel and Villa\n\t"ANSI_COLOR_RESET "Transports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 55) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Transports on Vacations\n\t"ANSI_COLOR_RESET "Cash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 56) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Cash Withdrawal\n\t"ANSI_COLOR_RESET "Cost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 57) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Cost and Taxes\n\t"ANSI_COLOR_RESET "Send to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 58) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Send to Business\n\t"ANSI_COLOR_RESET "Send to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 59) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Send to Personal\n\t"ANSI_COLOR_RESET "Top Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 60) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Top Up e-Wallets and/or Cards\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI06UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI06, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 6 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 50 && (FUCSelected + 1) <= 60 && (AvailableOptions == 60)) {
                if ((FUCSelected + 1) == 51) {
                    printf("      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Parking and Toll Fee\n\t"ANSI_COLOR_RESET "Vehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 52) {
                    printf("\tParking and Toll Fee\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Vehicle Maintenance\n\t"ANSI_COLOR_RESET "Attractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 53) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Attractions and Tours\n\t"ANSI_COLOR_RESET "Hotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 54) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Hotel and Villa\n\t"ANSI_COLOR_RESET "Transports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 55) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Transports on Vacations\n\t"ANSI_COLOR_RESET "Cash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 56) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Cash Withdrawal\n\t"ANSI_COLOR_RESET "Cost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 57) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Cost and Taxes\n\t"ANSI_COLOR_RESET "Send to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 58) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Send to Business\n\t"ANSI_COLOR_RESET "Send to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 59) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Send to Personal\n\t"ANSI_COLOR_RESET "Top Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 60) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Top Up e-Wallets and/or Cards\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI06UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 50 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 50) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 50 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 50; Updated = true;
                } break;
            case KEY_RIGHT:
                F2_FUC01_FinancialUsesCategoryUI(0);
                break;
            case KEY_LEFT:
                F2_FUC05_FinancialUsesCategoryUI(40);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } MainMenuApplicationFeatures(MMAFSelected);
}

void F3_FUC01_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 10; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI01, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 1 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 0 && (FUCSelected + 1) <= 10 && (AvailableOptions == 10)) {
                if ((FUCSelected + 1) == 1) {
                    printf("      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Account Receiveable\n\t"ANSI_COLOR_RESET "Additional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 2) {
                    printf("\tAccount Receiveable\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Additional Income\n\t"ANSI_COLOR_RESET "Allowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 3) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Allowance\n\t"ANSI_COLOR_RESET "Electricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 4) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Electricity, Water, and Gas\n\t"ANSI_COLOR_RESET "House and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 5) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> House and Appartment Rent\n\t"ANSI_COLOR_RESET "Household\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 6) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Household\n\t"ANSI_COLOR_RESET "Insurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 7) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Insurance\n\t"ANSI_COLOR_RESET "Mobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 8) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Mobile and Data\n\t"ANSI_COLOR_RESET "Handheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 9) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Handheld Electric Device\n\t"ANSI_COLOR_RESET "TV and Internet\n\n");
                } else if ((FUCSelected + 1) == 10) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> TV and Internet\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI01UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI01, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 1 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 0 && (FUCSelected + 1) <= 10 && (AvailableOptions == 10)) {
                if ((FUCSelected + 1) == 1) {
                    printf("      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Account Receiveable\n\t"ANSI_COLOR_RESET "Additional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 2) {
                    printf("\tAccount Receiveable\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Additional Income\n\t"ANSI_COLOR_RESET "Allowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 3) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Allowance\n\t"ANSI_COLOR_RESET "Electricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 4) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Electricity, Water, and Gas\n\t"ANSI_COLOR_RESET "House and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 5) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> House and Appartment Rent\n\t"ANSI_COLOR_RESET "Household\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 6) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n      " BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Household\n\t"ANSI_COLOR_RESET "Insurance\n\tMobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 7) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n      "BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Insurance\n\t"ANSI_COLOR_RESET "Mobile and Data\n\tHandheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 8) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n      "BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Mobile and Data\n\t"ANSI_COLOR_RESET "Handheld Electric Device\n\tTV and Internet\n\n");
                } else if ((FUCSelected + 1) == 9) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n      "BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Handheld Electric Device\n\t"ANSI_COLOR_RESET "TV and Internet\n\n");
                } else if ((FUCSelected + 1) == 10) {
                    printf("\tAccount Receiveable\n\tAdditional Income\n\tAllowance\n\tElectricity, Water, and Gas\n\tHouse and Appartment Rent\n\tHousehold\n\tInsurance\n\tMobile and Data\n\tHandheld Electric Device\n      "BRIGHTRED216 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> TV and Internet\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI01UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 0 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 0) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 0 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 0; Updated = true;
                } break;
            case KEY_RIGHT:
                F3_FUC02_FinancialUsesCategoryUI(10);
                break;
            case KEY_LEFT:
                F3_FUC06_FinancialUsesCategoryUI(50);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } strncpy(BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, FinancialUsesCategoryListing[FUCSelected], BUFSIZE07);
    F3_BudgetCreationAndMonitoring(F3Selected);
}

void F3_FUC02_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 20; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI02, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 2 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 10 && (FUCSelected + 1) <= 20 && (AvailableOptions == 20)) {
                if ((FUCSelected + 1) == 11) {
                    printf("      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Bonus\n\t"ANSI_COLOR_RESET "Business Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 12) {
                    printf("\tBonus\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Business Profit\n\t"ANSI_COLOR_RESET "Classes and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 13) {
                    printf("\tBonus\n\tBusiness Profit\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Classes and Workshops\n\t"ANSI_COLOR_RESET "School Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 14) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> School Supplies\n\t"ANSI_COLOR_RESET "Tuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 15) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Tuition Fee\n\t"ANSI_COLOR_RESET "Children and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 16) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Children and Family Needs\n\t"ANSI_COLOR_RESET "Parents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 17) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Parents and Family Needs\n\t"ANSI_COLOR_RESET "Daily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 18) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Daily Meal\n\t"ANSI_COLOR_RESET "Snacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 19) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Snacks and Drinks\n\t"ANSI_COLOR_RESET "Gifting\n\n");
                } else if ((FUCSelected + 1) == 20) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Gifting\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI02UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI02, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 2 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 10 && (FUCSelected + 1) <= 20 && (AvailableOptions == 20)) {
                if ((FUCSelected + 1) == 11) {
                    printf("      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Bonus\n\t"ANSI_COLOR_RESET "Business Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 12) {
                    printf("\tBonus\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Business Profit\n\t"ANSI_COLOR_RESET "Classes and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 13) {
                    printf("\tBonus\n\tBusiness Profit\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Classes and Workshops\n\t"ANSI_COLOR_RESET "School Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 14) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> School Supplies\n\t"ANSI_COLOR_RESET "Tuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 15) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Tuition Fee\n\t"ANSI_COLOR_RESET "Children and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 16) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n      " BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Children and Family Needs\n\t"ANSI_COLOR_RESET "Parents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 17) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Parents and Family Needs\n\t"ANSI_COLOR_RESET "Daily Meal\n\tSnacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 18) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Daily Meal\n\t"ANSI_COLOR_RESET "Snacks and Drinks\n\tGifting\n\n");
                } else if ((FUCSelected + 1) == 19) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Snacks and Drinks\n\t"ANSI_COLOR_RESET "Gifting\n\n");
                } else if ((FUCSelected + 1) == 20) {
                    printf("\tBonus\n\tBusiness Profit\n\tClasses and Workshops\n\tSchool Supplies\n\tTuition Fee\n\tChildren and Family Needs\n\tParents and Family Needs\n\tDaily Meal\n\tSnacks and Drinks\n      "BRIGHTGREEN156 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Gifting\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI02UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 10 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 10) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 10 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 10; Updated = true;
                } break;
            case KEY_RIGHT:
                F3_FUC03_FinancialUsesCategoryUI(20);
                break;
            case KEY_LEFT:
                F3_FUC01_FinancialUsesCategoryUI(0);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } strncpy(BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, FinancialUsesCategoryListing[FUCSelected], BUFSIZE07);
    F3_BudgetCreationAndMonitoring(F3Selected);
}

void F3_FUC03_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 30; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI03, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 3 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 20 && (FUCSelected + 1) <= 30 && (AvailableOptions == 30)) {
                if ((FUCSelected + 1) == 21) {
                    printf("      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Charity\n\t"ANSI_COLOR_RESET "Groceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 22) {
                    printf("\tCharity\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Groceries\n\t"ANSI_COLOR_RESET "Doctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 23) {
                    printf("\tCharity\n\tGroceries\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Doctor and Hospital\n\t"ANSI_COLOR_RESET "Medicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 24) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Medicines\n\t"ANSI_COLOR_RESET "Personal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 25) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Personal Care\n\t"ANSI_COLOR_RESET "Books\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 26) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Books\n\t"ANSI_COLOR_RESET "Dining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 27) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Dining Out\n\t"ANSI_COLOR_RESET "Games\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 28) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Games\n\t"ANSI_COLOR_RESET "Hobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 29) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Hobby\n\t"ANSI_COLOR_RESET "Movies and Music\n\n");
                } else if ((FUCSelected + 1) == 30) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Movies and Music\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI03UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI03, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 3 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 20 && (FUCSelected + 1) <= 30 && (AvailableOptions == 30)) {
                if ((FUCSelected + 1) == 21) {
                    printf("      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Charity\n\t"ANSI_COLOR_RESET "Groceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 22) {
                    printf("\tCharity\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Groceries\n\t"ANSI_COLOR_RESET "Doctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 23) {
                    printf("\tCharity\n\tGroceries\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Doctor and Hospital\n\t"ANSI_COLOR_RESET "Medicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 24) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Medicines\n\t"ANSI_COLOR_RESET "Personal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 25) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Personal Care\n\t"ANSI_COLOR_RESET "Books\n\tDining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 26) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n      " BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Books\n\t"ANSI_COLOR_RESET "Dining Out\n\tGames\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 27) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Dining Out\n\t"ANSI_COLOR_RESET "Games\n\tHobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 28) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Games\n\t"ANSI_COLOR_RESET "Hobby\n\tMovies and Music\n\n");
                } else if ((FUCSelected + 1) == 29) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Hobby\n\t"ANSI_COLOR_RESET "Movies and Music\n\n");
                } else if ((FUCSelected + 1) == 30) {
                    printf("\tCharity\n\tGroceries\n\tDoctor and Hospital\n\tMedicines\n\tPersonal Care\n\tBooks\n\tDining Out\n\tGames\n\tHobby\n      "BRIGHTBLUE159 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Movies and Music\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI03UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 20 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 20) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 20 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 20; Updated = true;
                } break;
            case KEY_RIGHT:
                F3_FUC04_FinancialUsesCategoryUI(30);
                break;
            case KEY_LEFT:
                F3_FUC02_FinancialUsesCategoryUI(10);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } strncpy(BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, FinancialUsesCategoryListing[FUCSelected], BUFSIZE07);
    F3_BudgetCreationAndMonitoring(F3Selected);
}

void F3_FUC04_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 40; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI04, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 4 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 30 && (FUCSelected + 1) <= 40 && (AvailableOptions == 40)) {
                if ((FUCSelected + 1) == 31) {
                    printf("      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Pets\n\t"ANSI_COLOR_RESET "Incomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 32) {
                    printf("\tPets\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Incomings\n\t"ANSI_COLOR_RESET "Interests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 33) {
                    printf("\tPets\n\tIncomings\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Interests\n\t"ANSI_COLOR_RESET "Investments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 34) {
                    printf("\tPets\n\tIncomings\n\tInterests\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Investments Withdrawal\n\t"ANSI_COLOR_RESET "Loan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 35) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Loan Disbursements\n\t"ANSI_COLOR_RESET "Car Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 36) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Car Installments\n\t"ANSI_COLOR_RESET "Credit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 37) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Credit Card\n\t"ANSI_COLOR_RESET "Home Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 38) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Home Mortgage\n\t"ANSI_COLOR_RESET "Refunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 39) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Refunds\n\t"ANSI_COLOR_RESET "Reimbursements\n\n");
                } else if ((FUCSelected + 1) == 40) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Reimbursements\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI04UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI04, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 4 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 30 && (FUCSelected + 1) <= 40 && (AvailableOptions == 40)) {
                if ((FUCSelected + 1) == 31) {
                    printf("      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Pets\n\t"ANSI_COLOR_RESET "Incomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 32) {
                    printf("\tPets\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Incomings\n\t"ANSI_COLOR_RESET "Interests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 33) {
                    printf("\tPets\n\tIncomings\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Interests\n\t"ANSI_COLOR_RESET "Investments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 34) {
                    printf("\tPets\n\tIncomings\n\tInterests\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Investments Withdrawal\n\t"ANSI_COLOR_RESET "Loan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 35) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Loan Disbursements\n\t"ANSI_COLOR_RESET "Car Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 36) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n      " BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Car Installments\n\t"ANSI_COLOR_RESET "Credit Card\n\tHome Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 37) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Credit Card\n\t"ANSI_COLOR_RESET "Home Mortgage\n\tRefunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 38) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Home Mortgage\n\t"ANSI_COLOR_RESET "Refunds\n\tReimbursements\n\n");
                } else if ((FUCSelected + 1) == 39) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Refunds\n\t"ANSI_COLOR_RESET "Reimbursements\n\n");
                } else if ((FUCSelected + 1) == 40) {
                    printf("\tPets\n\tIncomings\n\tInterests\n\tInvestments Withdrawal\n\tLoan Disbursements\n\tCar Installments\n\tCredit Card\n\tHome Mortgage\n\tRefunds\n      "BRIGHTPINK219 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Reimbursements\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI04UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 30 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 30) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 30 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 30; Updated = true;
                } break;
            case KEY_RIGHT:
                F3_FUC05_FinancialUsesCategoryUI(40);
                break;
            case KEY_LEFT:
                F3_FUC03_FinancialUsesCategoryUI(20);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } strncpy(BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, FinancialUsesCategoryListing[FUCSelected], BUFSIZE07);
    F3_BudgetCreationAndMonitoring(F3Selected);
}

void F3_FUC05_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 50; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI05, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 5 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 40 && (FUCSelected + 1) <= 50 && (AvailableOptions == 50)) {
                if ((FUCSelected + 1) == 41) {
                    printf("      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Salary\n\t"ANSI_COLOR_RESET "Investments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 42) {
                    printf("\tSalary\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Investments\n\t"ANSI_COLOR_RESET "Savings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 43) {
                    printf("\tSalary\n\tInvestments\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Savings\n\t"ANSI_COLOR_RESET "Fashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 44) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Fashions\n\t"ANSI_COLOR_RESET "Gadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 45) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Gadget and Electronics\n\t"ANSI_COLOR_RESET "Home Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 46) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Home Appliances\n\t"ANSI_COLOR_RESET "Sport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 47) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Sport Activities\n\t"ANSI_COLOR_RESET "Sport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 48) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Sport Equipments\n\t"ANSI_COLOR_RESET "Daily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 49) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Daily Transportations\n\t"ANSI_COLOR_RESET "Gasolines\n\n");
                } else if ((FUCSelected + 1) == 50) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Gasolines\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI05UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI05, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 5 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 40 && (FUCSelected + 1) <= 50 && (AvailableOptions == 50)) {
                if ((FUCSelected + 1) == 41) {
                    printf("      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Salary\n\t"ANSI_COLOR_RESET "Investments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 42) {
                    printf("\tSalary\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Investments\n\t"ANSI_COLOR_RESET "Savings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 43) {
                    printf("\tSalary\n\tInvestments\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Savings\n\t"ANSI_COLOR_RESET "Fashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 44) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Fashions\n\t"ANSI_COLOR_RESET "Gadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 45) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Gadget and Electronics\n\t"ANSI_COLOR_RESET "Home Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 46) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n      " BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Home Appliances\n\t"ANSI_COLOR_RESET "Sport Activities\n\tSport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 47) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Sport Activities\n\t"ANSI_COLOR_RESET "Sport Equipments\n\tDaily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 48) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Sport Equipments\n\t"ANSI_COLOR_RESET "Daily Transportations\n\tGasolines\n\n");
                } else if ((FUCSelected + 1) == 49) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Daily Transportations\n\t"ANSI_COLOR_RESET "Gasolines\n\n");
                } else if ((FUCSelected + 1) == 50) {
                    printf("\tSalary\n\tInvestments\n\tSavings\n\tFashions\n\tGadget and Electronics\n\tHome Appliances\n\tSport Activities\n\tSport Equipments\n\tDaily Transportations\n      "BRIGHTMAGENTA217 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Gasolines\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI05UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 40 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 40) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 40 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 40; Updated = true;
                } break;
            case KEY_RIGHT:
                F3_FUC06_FinancialUsesCategoryUI(50);
                break;
            case KEY_LEFT:
                F3_FUC04_FinancialUsesCategoryUI(30);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } strncpy(BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, FinancialUsesCategoryListing[FUCSelected], BUFSIZE07);
    F3_BudgetCreationAndMonitoring(F3Selected);
}

void F3_FUC06_FinancialUsesCategoryUI(int FUCSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 60; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI06, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 6 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 50 && (FUCSelected + 1) <= 60 && (AvailableOptions == 60)) {
                if ((FUCSelected + 1) == 51) {
                    printf("      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Parking and Toll Fee\n\t"ANSI_COLOR_RESET "Vehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 52) {
                    printf("\tParking and Toll Fee\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Vehicle Maintenance\n\t"ANSI_COLOR_RESET "Attractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 53) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Attractions and Tours\n\t"ANSI_COLOR_RESET "Hotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 54) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Hotel and Villa\n\t"ANSI_COLOR_RESET "Transports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 55) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Transports on Vacations\n\t"ANSI_COLOR_RESET "Cash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 56) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Cash Withdrawal\n\t"ANSI_COLOR_RESET "Cost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 57) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Cost and Taxes\n\t"ANSI_COLOR_RESET "Send to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 58) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Send to Business\n\t"ANSI_COLOR_RESET "Send to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 59) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Send to Personal\n\t"ANSI_COLOR_RESET "Top Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 60) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Top Up e-Wallets and/or Cards\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI06UDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFUCUI06, UserName);
            puts(ANSI_COLOR_LIGHTWHITE ANSI_STYLE_BOLD"\t(Page 6 of 6) " ANSI_STYLE_ITALIC"List per Category: Shown for 10 out of 60 categories per pages... .\n"ANSI_COLOR_RESET);

            if ((FUCSelected + 1) > 50 && (FUCSelected + 1) <= 60 && (AvailableOptions == 60)) {
                if ((FUCSelected + 1) == 51) {
                    printf("      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Parking and Toll Fee\n\t"ANSI_COLOR_RESET "Vehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 52) {
                    printf("\tParking and Toll Fee\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Vehicle Maintenance\n\t"ANSI_COLOR_RESET "Attractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 53) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Attractions and Tours\n\t"ANSI_COLOR_RESET "Hotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 54) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Hotel and Villa\n\t"ANSI_COLOR_RESET "Transports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 55) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Transports on Vacations\n\t"ANSI_COLOR_RESET "Cash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 56) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n      " BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE"> Cash Withdrawal\n\t"ANSI_COLOR_RESET "Cost and Taxes\n\tSend to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 57) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Cost and Taxes\n\t"ANSI_COLOR_RESET "Send to Business\n\tSend to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 58) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Send to Business\n\t"ANSI_COLOR_RESET "Send to Personal\n\tTop Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 59) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Send to Personal\n\t"ANSI_COLOR_RESET "Top Up e-Wallets and/or Cards\n\n");
                } else if ((FUCSelected + 1) == 60) {
                    printf("\tParking and Toll Fee\n\tVehicle Maintenance\n\tAttractions and Tours\n\tHotel and Villa\n\tTransports on Vacations\n\tCash Withdrawal\n\tCost and Taxes\n\tSend to Business\n\tSend to Personal\n      "BRIGHTPURPLE218 ANSI_STYLE_BOLD ANSI_STYLE_UNDERLINE "> Top Up e-Wallets and/or Cards\n\n"ANSI_COLOR_RESET);
                }

                printf("\n\t%s", AppFUCUI06UDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (FUCSelected > 50 && FUCSelected < AvailableOptions) {
                    --FUCSelected; Updated = true;
                } else if (FUCSelected <= 50) {
                    FUCSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (FUCSelected >= 50 && FUCSelected < AvailableOptions - 1) {
                    ++FUCSelected; Updated = true;
                } else if (FUCSelected >= AvailableOptions - 1) {
                    FUCSelected = 50; Updated = true;
                } break;
            case KEY_RIGHT:
                F3_FUC01_FinancialUsesCategoryUI(0);
                break;
            case KEY_LEFT:
                F3_FUC05_FinancialUsesCategoryUI(40);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    } strncpy(BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, FinancialUsesCategoryListing[FUCSelected], BUFSIZE07);
    F3_BudgetCreationAndMonitoring(F3Selected);
}

///* DRIVER MAIN PROGRAM *///
///* NOTE: MUST USE FILE HANDLING IN ORDER TO BE WORKING *///

/*
Requirements:
    1. File Handling                    (save-load file handling)           VVV
    2. Windows Header File              ('windows.h')                       VVV
    3. Time Conversion                  (real-time conversion/tracking)     VVV
    4. Array and String Manipulations   ('string.h' 'wchar.h' 'wctype.h')   VVV
    5. Functions and Classes            (if needed, mostly private)         VVV
    6. Mathematical Visual Graph        (just use external ASCII code)      VVV
    7. Windows GUI for Several Usages   (if needed, complicated)            ---
*/

int main(void) {
    /* List of notifications, 4 on present */
    // InfoMessageBox_OK("Info Message: Update Changes in The Category 'Investments'.", "You have updated the limit of the money that you'd to spent on investments from Rp2.000.000.000,00 into Rp5.000.000.000,00. Make sure that you've enabled the limit on your debit/credit card transactions before doing some more investments in some company stocks, personal branding shares, and more.\n\nWe only manage your well-being financial managing personally in this app, and may not into the other main parties with your companies and such, so no obligation from us to take care of your \"punishments\" if there's ever a wrong doing thing happens!");
    // WarningMessageBox_CANCELTRYCONTINUE("Warning Message: D-3 Reminder for Paying Full of 'Debts'", "You have received a warning message about getting your hand to pay the full of your decieve debts far-far ago on November 7, 2023; and now ONLY THREE DAYS LEFT before the debt collector might be coming to you with your personal card bank manager to considering things over you.\nSo please, DO NOT FORGET THE DATE FOR FULL PAYMENTS FOR:\n\n\tRp290.172.984,19;\n\twith a total interest of: 6.58%.\n\nNOTE: Ignore this warning message if you had already pay the full debts, or if there's maybe a caught up error when finishing up your deletion over this warning message before!");
    // QuestionMessageBox_YESNOCANCEL("Question Message: Confirmation on Deletion Over a 'Transactions'.", "We've noticed that you want to delete all currently recorded transactions on:\n\tDate (by month): October 2022,\n\tTotal Recorded Transactions: 87 Transactions.\n\nAre you sure to continue and delete all transactions that happening in October 2022, from the October 1st until 31st October?\n\nNOTE: Anything after the deletions will be PERMANENTLY deleted and NEVER BE ABLE TO BE RECOVERED by any means and such. Please think twice, that you may have to know all the recorded transactions over the past month so you can do the budget monitoring better than before ever was!");
    // ErrorMessageBox_OKCANCEL("Error Message: Default 'Category' Changings Error.", "You may have received this error pop-up message because you've been trying to do some changes on a system's default categories made in this app's core already. Several times before you only get knocked out from the menu, and because now you've been trying so badly to do it so even though you already knew that ALL default variables CANNOT EVER BE CHANGED WHATSOEVER!\n\nPlease keep in mind to not spamming this error messages, because from the first you got this messages within three days will always pop-up this. If you insist, then unfortunately you have to be banned from this menu for a temporary time!");

    ClearScreen();
    SetConsoleOutputCP(65001);
    
    /*
    InfoMessageBox_OK("(Info) @SKYR-PFMSA; Application Features Availability", "Development Progress of Personal Financial Management Support Application:\n\n\t1. Moneytory Transaction Registration.\n\tSTATUS: Complete (100%)\n\tFuture Update: (able to work for yearly budget\n\ttoo).\n\n\t2. Moneytory Grouping per Category.\n\tSTATUS: In-progress (50%)\n\tReasoning: Delayed (not enough time left).\n\tFuture Update: (completing the basis first).\n\n\t3. Budget Creation and Monitoring.\n\tSTATUS: Completed (100%)\n\tFuture Update: (make the yearly budget creation\n\tand monitoring be working too).\n\n\t4. Filter and Searching Data.\n\tSTATUS: Completed (100%)\n\tFuture Update: (make the UI more understandable).\n\n\t5. Reminder and Notifications.\n\tSTATUS: Completed (100%)\n\tFuture Update: (make more pop-up notifications\n\tthoroughly).\n\n\t6. Data Visualization.\n\tSTATUS: Completed (100%)\n\tFuture Update: (better UI and histogram\n\tmechanism).");
    InfoMessageBox_OK("(Info) @SKYR-PFMSA; New Users' Data Appearance", "This message only appears on your screen when you start the app, or when you're logging out from a specific account.\n\nEverytime you upload a submission that does create a new save file, please note this in mind that we ONLY UPDATED the FILES EXISTENCE ONCE every this message DOES APPEAR\n\t(running at the very start, and when logged out).\n\nThus, please be sure to CLOSE THE APP first or RELOGGED IN by logging out and then logging in your account to make the file able to be detected!");
    InfoMessageBox_OK("(Info) @SKYR-PFMSA; Importance of File Systems", "All the file system you see on your folder where the application resites,\n\n\tMAKE SURE NOT TO CHANGE THE FILE'S SYSTEM NAME INTO ANYTHING BUT THE ORIGINAL ONE, AND DO NOT ATTEMPT TO DELETE THESE FILES;\n\nBecause it may lead into program crashing over some missing or incorrect type of files!");
    InfoMessageBox_OK("(Info) @SKYR-PFMSA; Configuration File System", "This specific configuration file system is for the SIXTH feature purposes ONLY (for now, but it can be more than just this feature), hence we:\n\n\tHIGHLY RECOMMEND you to ALSO NOT CHANGING ANY OF THE CONTENTS IN THE CONFIGURATION FILE;\n\nThus just changing the right value content on LINE 25 is enough, and see more of why only at LINE 25 in the configuration file itself!");
    */

    // puts("Hello, World!");
    
    //// INFO: Just adding a newline padding to the console while pre-testing encryption data file here.
    //// NOTE: Just for safety, use "return 0;" when debugging with these codes below!
    // puts("");
    // EncryptTxtFile("DecodedTextSample.txt", "EncodedTextSample.txt", EncryptionKey, false);
    // DecryptTxtFile("SKYR-FMSA-RegisteredAccounts.txt", true, EncryptionKey, "None");
    // DecryptTxtFile("aaa-F1-MTR-December-2023.txt", true, EncryptionKey, "None");
    // DecryptTxtFile("aaa-F1-MTR-December-2023.txt", false, EncryptionKey, "aaa-F1-MTR-December-2023.txt > :");
    // DecryptTxtFile("aaa-F3-BCAM-December-2023.txt", true, EncryptionKey, "None");
    // DecryptTxtFile("TemporaryDecProfile.txt", false, 0, "TemporaryDecProfile.txt > vers, ");
    // DecryptTxtFile("Updates.txt", false, 0, "Updates.txt > Change(s)");
    // return 0;

    FILE *FDestination, *FTempDestination;
    char FDBuffer[BUFSIZE16], DeleteTempDestinationTxtFile[BUFSIZE07];

    char SignedInFirstName[BUFSIZE07], SignedInLastName[BUFSIZE07], SignedInUsername[BUFSIZE07];
    char *SignedInFirstNamePTR, *SignedInLastNamePTR, *SignedInUsernamePTR;
    char *LoggedInEmail, *LoggedInPhoneNumber, *LoggedInUsername, *LoggedInHiddenShownPassword;
    // char TempLoggedInEmail[BUFSIZE07], TempLoggedInPhoneNumber[BUFSIZE07], TempLoggedInUsername[BUFSIZE07], TempLoggedInPassword[BUFSIZE07], LoggedInHiddenShownPassword[BUFSIZE07];
    char ListedAccounts[BUFSIZE07], AnotherTempListedAccounts[BUFSIZE07], *TempListedAccounts;
    char AccountNo[BUFSIZE07], AnotherTempAccountNo[BUFSIZE07], *TempAccountNo;
    long long int BufLen;
    
    if (access("SKYR-FMSA-RegisteredAccounts.txt", F_OK) != 0) { fflush(stdout); LanguageMenu(); }
    else {
        fflush(stdout);

        memset(SaveFilesTxtName, 0, sizeof(SaveFilesTxtName));
        MatchSaveFileTxt("./", "-SaveFile");    // Profile account save files for login purposes.
        MatchSaveFileTxt("./", "-F1-MTR-");     // ...
        MatchSaveFileTxt("./", "-F3-BCAM-");    // ...
        
        for (int i = 0; i < FilePathNameTraversalCounter; i++) { CountSavedFiles++; }
        if (CountSavedFiles >= 1) {
            // puts(SaveFilesTxtName[0].FileNames);
            if (strstr(SaveFilesTxtName[0].FileNames, "-SaveFile") == NULL) {
                fflush(stdout);
                AccountLoginMenu(0);
            }

            FDestination     = fopen(SaveFilesTxtName[0].FileNames, "r");
            FTempDestination = fopen("TempDestination.txt", "w");

            while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
                fputs(FDBuffer, FTempDestination);
            } fclose(FDestination); fclose(FTempDestination);

            strncpy(ListedAccounts, ReadAndPrintLine("TempDestination.txt", 8), BUFSIZE07);
            strtok_r(ListedAccounts, ":", &TempListedAccounts); TempListedAccounts = TrimWhiteSpaces(TempListedAccounts);
            strncpy(AnotherTempListedAccounts, TempListedAccounts, BUFSIZE07);
            strtok(AnotherTempListedAccounts, " ");
            GlobalSKYRFMSARegisteredAccounts = atoi(AnotherTempListedAccounts);

            strncpy(AccountNo, ReadAndPrintLine("TempDestination.txt", 10), BUFSIZE07);
            strtok_r(AccountNo, ".", &TempAccountNo); TempAccountNo = TrimWhiteSpaces(TempAccountNo);
            strncpy(AnotherTempAccountNo, TempAccountNo, BUFSIZE07);
            strtok(AnotherTempAccountNo, " ");
            SignedInAccountNo = atoi(AnotherTempAccountNo);

            strncpy(SignedInFirstName, ReadAndPrintLine("TempDestination.txt", 13), BUFSIZE07);
            strncpy(SignedInLastName,  ReadAndPrintLine("TempDestination.txt", 14), BUFSIZE07);
            strncpy(SignedInUsername,  ReadAndPrintLine("TempDestination.txt", 16), BUFSIZE07);

            strtok_r(SignedInFirstName, ":", &SignedInFirstNamePTR); SignedInFirstNamePTR = TrimWhiteSpaces(SignedInFirstNamePTR);
            strncpy(FullName, SignedInFirstNamePTR, BUFSIZE07); strcat(FullName, " ");
            strtok_r(SignedInLastName, ":", &SignedInLastNamePTR); SignedInLastNamePTR = TrimWhiteSpaces(SignedInLastNamePTR);
            strncat(FullName, SignedInLastNamePTR, BUFSIZE07);
            strtok_r(SignedInUsername, ":", &SignedInUsernamePTR); SignedInUsernamePTR = TrimWhiteSpaces(SignedInUsernamePTR);
            strncpy(UserName, SignedInUsernamePTR, BUFSIZE07);

            strcpy(DeleteTempDestinationTxtFile, "del ");
            strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
            system(DeleteTempDestinationTxtFile);

            FDestination     = fopen("SKYR-FMSA-RegisteredAccounts.txt", "r");
            FTempDestination = fopen("TempDestination.txt", "w");

            while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
                BufLen = strlen(FDBuffer);
                for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                fputs(FDBuffer, FTempDestination);
            } fclose(FDestination); fclose(FTempDestination);
            
            LoggedInEmail               = ReadAndPrintLine("TempDestination.txt", 2 + (14 * SignedInAccountNo)); strtok_r(LoggedInEmail, ":", &LoggedInEmail); LoggedInEmail = TrimWhiteSpaces(LoggedInEmail);
            LoggedInUsername            = ReadAndPrintLine("TempDestination.txt", 3 + (14 * SignedInAccountNo)); strtok_r(LoggedInUsername, ":", &LoggedInUsername); LoggedInUsername = TrimWhiteSpaces(LoggedInUsername);
            LoggedInHiddenShownPassword = ReadAndPrintLine("TempDestination.txt", 4 + (14 * SignedInAccountNo)); strtok_r(LoggedInHiddenShownPassword, ":", &LoggedInHiddenShownPassword); LoggedInHiddenShownPassword = TrimWhiteSpaces(LoggedInHiddenShownPassword);
            LoggedInPhoneNumber         = ReadAndPrintLine("TempDestination.txt", 8 + (14 * SignedInAccountNo)); strtok_r(LoggedInPhoneNumber, ":", &LoggedInPhoneNumber); LoggedInPhoneNumber = TrimWhiteSpaces(LoggedInPhoneNumber);
            strncpy(ALMInputs.Email, LoggedInEmail, BUFSIZE07);
            strncpy(ALMInputs.Username, LoggedInUsername, BUFSIZE07);
            strncpy(ALMInputs.HiddenPasswordShown, LoggedInHiddenShownPassword, BUFSIZE07);
            strncpy(ALMInputs.PhoneNumber, LoggedInPhoneNumber, BUFSIZE07);

            strcpy(DeleteTempDestinationTxtFile, "del ");
            strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
            system(DeleteTempDestinationTxtFile);

            SKYRApplicationRunning = true;
            MainMenuApplicationFeatures(0);

        } else {
            fflush(stdout);
            // InfoMessageBox_OK("(Info) @SKYR-PFMSA; Importance of The Safety Profile Account", "For the safety purposes while you're going registrating a new account, or when trying to logged into the application, or even when you're going to recover of your missing account,\n\n\tWE ARE GOING TO DEPLETED EVERY INPUT YOU'VE PROGRESSED SO FAR, SO PLEASE JUST STAY IN ONE UI MENU;\n\nIn order to be save and more secure, so don't blame us when you're missing on your inputs after switching to different UIs... .");
            AccountLoginMenu(0);
        }
    }
    
    return 0;
}

void MainMenuApplicationFeatures(int MMAFSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 6; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;
    int PreviousAKDC = 0;
    bool CatchDefaultAKDC = false;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppMainMenuUI, UserName);
            if (CatchDefaultAKDC) printf(ANSI_COLOR_LIGHTRED"\tError: The auto-enter shortcut key labeled as '%c' (ID: 0x%02X) is not registered at the moment!\n\n"ANSI_COLOR_RESET, ((int)PreviousAKDC != 12) ? (char)PreviousAKDC : 10, (int)PreviousAKDC);

            if ((MMAFSelected + 1) > 0 && (MMAFSelected + 1) <= 6 && (AvailableOptions == 6)) {
                if ((MMAFSelected + 1) == 1) {
                    printf("      " BRIGHTGREEN154 ANSI_STYLE_UNDERLINE"> Recording The Personal Financial Transactions.\n\t"ANSI_COLOR_RESET "Grouping Financial Transaction Types With Each Category.\n\tPersonal Budget Creation and Transaction Monitoring.\n\tFiltering and Searching Personal Financial Transaction Data.\n\tReminders and Notifications for Certain Important Transactions.\n\tVisualization of 2D Histogram Graphic Projections (CLI Based).\n\n");
                } else if ((MMAFSelected + 1) == 2) {
                    printf("\tRecording The Personal Financial Transactions.\n      " BRIGHTGREEN155 ANSI_STYLE_UNDERLINE"> Grouping Financial Transaction Types With Each Category.\n\t"ANSI_COLOR_RESET "Personal Budget Creation and Transaction Monitoring.\n\tFiltering and Searching Personal Financial Transaction Data.\n\tReminders and Notifications for Certain Important Transactions.\n\tVisualization of 2D Histogram Graphic Projections (CLI Based).\n\n");
                } else if ((MMAFSelected + 1) == 3) {
                    printf("\tRecording The Personal Financial Transactions.\n\tGrouping Financial Transaction Types With Each Category.\n      " BRIGHTGREEN156 ANSI_STYLE_UNDERLINE"> Personal Budget Creation and Transaction Monitoring.\n\t"ANSI_COLOR_RESET "Filtering and Searching Personal Financial Transaction Data.\n\tReminders and Notifications for Certain Important Transactions.\n\tVisualization of 2D Histogram Graphic Projections (CLI Based).\n\n");
                } else if ((MMAFSelected + 1) == 4) {
                    printf("\tRecording The Personal Financial Transactions.\n\tGrouping Financial Transaction Types With Each Category.\n\tPersonal Budget Creation and Transaction Monitoring.\n      " BRIGHTBLUE157 ANSI_STYLE_UNDERLINE"> Filtering and Searching Personal Financial Transaction Data.\n\t"ANSI_COLOR_RESET "Reminders and Notifications for Certain Important Transactions.\n\tVisualization of 2D Histogram Graphic Projections (CLI Based).\n\n");
                } else if ((MMAFSelected + 1) == 5) {
                    printf("\tRecording The Personal Financial Transactions.\n\tGrouping Financial Transaction Types With Each Category.\n\tPersonal Budget Creation and Transaction Monitoring.\n\tFiltering and Searching Personal Financial Transaction Data.\n      " BRIGHTBLUE158 ANSI_STYLE_UNDERLINE"> Reminders and Notifications for Certain Important Transactions.\n\t"ANSI_COLOR_RESET "Visualization of 2D Histogram Graphic Projections (CLI Based).\n\n");
                } else if ((MMAFSelected + 1) == 6) {
                    printf("\tRecording The Personal Financial Transactions.\n\tGrouping Financial Transaction Types With Each Category.\n\tPersonal Budget Creation and Transaction Monitoring.\n\tFiltering and Searching Personal Financial Transaction Data.\n\tReminders and Notifications for Certain Important Transactions.\n      " BRIGHTBLUE159 ANSI_STYLE_UNDERLINE"> Visualization of 2D Histogram Graphic Projections (CLI Based).\n\n"ANSI_COLOR_RESET);
                }

                (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\t%s", AppMainMenuUDRL) : printf("\n\n\n\n\t%s", AppMainMenuUDRL);
            }
        } else {
            FirstRun = false;

            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppMainMenuUI, UserName);
            if (CatchDefaultAKDC) printf(ANSI_COLOR_LIGHTRED"\tError: The auto-enter shortcut key labeled as '%c' (ID: 0x%02X) is not registered at the moment!\n\n"ANSI_COLOR_RESET, ((int)PreviousAKDC != 12) ? (char)PreviousAKDC : 10, (int)PreviousAKDC);

            if ((MMAFSelected + 1) > 0 && (MMAFSelected + 1) <= 6 && (AvailableOptions == 6)) {
                if ((MMAFSelected + 1) == 1) {
                    printf("      " BRIGHTGREEN154 ANSI_STYLE_UNDERLINE"> Recording The Personal Financial Transactions.\n\t"ANSI_COLOR_RESET "Grouping Financial Transaction Types With Each Category.\n\tPersonal Budget Creation and Transaction Monitoring.\n\tFiltering and Searching Personal Financial Transaction Data.\n\tReminders and Notifications for Certain Important Transactions.\n\tVisualization of 2D Histogram Graphic Projections (CLI Based).\n\n");
                } else if ((MMAFSelected + 1) == 2) {
                    printf("\tRecording The Personal Financial Transactions.\n      " BRIGHTGREEN155 ANSI_STYLE_UNDERLINE"> Grouping Financial Transaction Types With Each Category.\n\t"ANSI_COLOR_RESET "Personal Budget Creation and Transaction Monitoring.\n\tFiltering and Searching Personal Financial Transaction Data.\n\tReminders and Notifications for Certain Important Transactions.\n\tVisualization of 2D Histogram Graphic Projections (CLI Based).\n\n");
                } else if ((MMAFSelected + 1) == 3) {
                    printf("\tRecording The Personal Financial Transactions.\n\tGrouping Financial Transaction Types With Each Category.\n      " BRIGHTGREEN156 ANSI_STYLE_UNDERLINE"> Personal Budget Creation and Transaction Monitoring.\n\t"ANSI_COLOR_RESET "Filtering and Searching Personal Financial Transaction Data.\n\tReminders and Notifications for Certain Important Transactions.\n\tVisualization of 2D Histogram Graphic Projections (CLI Based).\n\n");
                } else if ((MMAFSelected + 1) == 4) {
                    printf("\tRecording The Personal Financial Transactions.\n\tGrouping Financial Transaction Types With Each Category.\n\tPersonal Budget Creation and Transaction Monitoring.\n      " BRIGHTBLUE157 ANSI_STYLE_UNDERLINE"> Filtering and Searching Personal Financial Transaction Data.\n\t"ANSI_COLOR_RESET "Reminders and Notifications for Certain Important Transactions.\n\tVisualization of 2D Histogram Graphic Projections (CLI Based).\n\n");
                } else if ((MMAFSelected + 1) == 5) {
                    printf("\tRecording The Personal Financial Transactions.\n\tGrouping Financial Transaction Types With Each Category.\n\tPersonal Budget Creation and Transaction Monitoring.\n\tFiltering and Searching Personal Financial Transaction Data.\n      " BRIGHTBLUE158 ANSI_STYLE_UNDERLINE"> Reminders and Notifications for Certain Important Transactions.\n\t"ANSI_COLOR_RESET "Visualization of 2D Histogram Graphic Projections (CLI Based).\n\n");
                } else if ((MMAFSelected + 1) == 6) {
                    printf("\tRecording The Personal Financial Transactions.\n\tGrouping Financial Transaction Types With Each Category.\n\tPersonal Budget Creation and Transaction Monitoring.\n\tFiltering and Searching Personal Financial Transaction Data.\n\tReminders and Notifications for Certain Important Transactions.\n      " BRIGHTBLUE159 ANSI_STYLE_UNDERLINE"> Visualization of 2D Histogram Graphic Projections (CLI Based).\n\n"ANSI_COLOR_RESET);
                }

                (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\t%s", AppMainMenuUDRL) : printf("\n\n\n\n\t%s", AppMainMenuUDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                if (MMAFSelected > 0 && MMAFSelected < AvailableOptions) {
                    --MMAFSelected; Updated = true;
                } else if (MMAFSelected <= 0) {
                    MMAFSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                if (MMAFSelected >= 0 && MMAFSelected < AvailableOptions - 1) {
                    ++MMAFSelected; Updated = true;
                } else if (MMAFSelected >= AvailableOptions - 1) {
                    MMAFSelected = 0; Updated = true;
                } break;
            case KEY_RIGHT:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                MainMenuProfileManager(0);
                break;
            case KEY_LEFT:
                PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '1': F1_MoneytoryTransactionsRegister(F1Selected); Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '2': F2_MoneytoryGroupingPerCategory(F2Selected); Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '3': F3_BudgetCreationAndMonitoring(F3Selected); Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '4': F4_FilterSearchingData(F4Selected); Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '5': F5_ReminderAndSetNotifications(F5Selected); Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '6': F6_DataVisualization(F6Selected); Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: {
                if (AKDC == KEY_UP || AKDC == KEY_DOWN || AKDC == KEY_LEFT || AKDC == KEY_RIGHT || AKDC == KEY_ENTER) { ClearScreen(); continue; }
                (AKDC > 0) ? PreviousAKDC = (int)AKDC : 0;
                (AKDC > 0) ? CatchDefaultAKDC = true : false;
            } break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    }

    if (MMAFSelected == 0) {
        F1_MoneytoryTransactionsRegister(F1Selected);
        MainMenuApplicationFeatures(MMAFSelected);
    } else if (MMAFSelected == 1) {
        F2_MoneytoryGroupingPerCategory(F2Selected);
        MainMenuApplicationFeatures(MMAFSelected);
    } else if (MMAFSelected == 2) {
        F3_BudgetCreationAndMonitoring(F3Selected);
        MainMenuApplicationFeatures(MMAFSelected);
    } else if (MMAFSelected == 3) {
        F4_FilterSearchingData(F4Selected);
        MainMenuApplicationFeatures(MMAFSelected);
    } else if (MMAFSelected == 4) {
        F5_ReminderAndSetNotifications(F5Selected);
        MainMenuApplicationFeatures(MMAFSelected);
    } else if (MMAFSelected == 5) {
        F6_DataVisualization(F6Selected);
        MainMenuApplicationFeatures(MMAFSelected);
    }
}

void MainMenuProfileManager(int MMPMSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 5; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    bool SubmitOrContinue;
    // bool ConfirmOrBackMMAF = false;
    char DeleteTempDestinationTxtFile[BUFSIZE07];
    char MessageID09[BUFSIZE10];

    char AKDC;
    int PreviousAKDC = 0;
    bool CatchDefaultAKDC = false;

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppProfileManagerUI, UserName);
            if (CatchDefaultAKDC) printf(ANSI_COLOR_LIGHTRED"\tError: The auto-enter shortcut key labeled as '%c' (ID: 0x%02X) is not registered at the moment!\n\n"ANSI_COLOR_RESET, ((int)PreviousAKDC != 12) ? (char)PreviousAKDC : 10, (int)PreviousAKDC);

            if ((MMPMSelected + 1) > 0 && (MMPMSelected + 1) <= 5 && (AvailableOptions == 5)) {
                if ((MMPMSelected + 1) == 1) {
                    printf("      " BRIGHTRED216 ANSI_STYLE_UNDERLINE"> SKYR Persona: NEW+ Account Registration\n\t"ANSI_COLOR_RESET "SKYR Persona: NEW+ Account Signing In\n\tSKYR Persona: NEW+ Account Personal Recovery\n\n\tSKYR Persona: NEW+ Account Signing Out\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\tSKYR Persona: DANGER+ Personal Account DELETION || Do this at your OWN risks! [PERMANENTLY Impacted]\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");
                } else if ((MMPMSelected + 1) == 2) {
                    printf("\tSKYR Persona: NEW+ Account Registration\n      " BRIGHTMAGENTA217 ANSI_STYLE_UNDERLINE"> SKYR Persona: NEW+ Account Signing In\n\t"ANSI_COLOR_RESET "SKYR Persona: NEW+ Account Personal Recovery\n\n\tSKYR Persona: NEW+ Account Signing Out\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\tSKYR Persona: DANGER+ Personal Account DELETION || Do this at your OWN risks! [PERMANENTLY Impacted]\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");
                } else if ((MMPMSelected + 1) == 3) {
                    printf("\tSKYR Persona: NEW+ Account Registration\n\tSKYR Persona: NEW+ Account Signing In\n      " BRIGHTPURPLE218 ANSI_STYLE_UNDERLINE"> SKYR Persona: NEW+ Account Personal Recovery\n\n\t"ANSI_COLOR_RESET "SKYR Persona: NEW+ Account Signing Out\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\tSKYR Persona: DANGER+ Personal Account DELETION || Do this at your OWN risks! [PERMANENTLY Impacted]\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");
                } else if ((MMPMSelected + 1) == 4) {
                    printf("\tSKYR Persona: NEW+ Account Registration\n\tSKYR Persona: NEW+ Account Signing In\n\tSKYR Persona: NEW+ Account Personal Recovery\n\n      " BRIGHTPINK219 ANSI_STYLE_UNDERLINE"> SKYR Persona: NEW+ Account Signing Out\n"ANSI_COLOR_RESET"\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\tSKYR Persona: DANGER+ Personal Account DELETION || Do this at your OWN risks! [PERMANENTLY Impacted]\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");
                } else if ((MMPMSelected + 1) == 5) {
                    printf("\tSKYR Persona: NEW+ Account Registration\n\tSKYR Persona: NEW+ Account Signing In\n\tSKYR Persona: NEW+ Account Personal Recovery\n\n\tSKYR Persona: NEW+ Account Signing Out\n" ANSI_COLOR_LIGHTRED"\t────────────────────────────────────────────────────────────────────────────────────────────────────\n      "ANSI_COLOR_RESET ANSI_COLOR_LIGHTRED ANSI_STYLE_BOLD"> SKYR Persona: DANGER+ Personal Account DELETION || Do this at your OWN risks! [PERMANENTLY Impacted]\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");
                }

                (!CatchDefaultAKDC) ? printf(ANSI_COLOR_RESET"\n\n\n\n\t%s", AppProfileManagerUDRL) : printf(ANSI_COLOR_RESET"\n\n\t%s", AppProfileManagerUDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppProfileManagerUI, UserName);
            if (CatchDefaultAKDC) printf(ANSI_COLOR_LIGHTRED"\tError: The auto-enter shortcut key labeled as '%c' (ID: 0x%02X) is not registered at the moment!\n\n"ANSI_COLOR_RESET, ((int)PreviousAKDC != 12) ? (char)PreviousAKDC : 10, (int)PreviousAKDC);

            if ((MMPMSelected + 1) > 0 && (MMPMSelected + 1) <= 5 && (AvailableOptions == 5)) {
                if ((MMPMSelected + 1) == 1) {
                    printf("      " BRIGHTRED216 ANSI_STYLE_UNDERLINE"> SKYR Persona: NEW+ Account Registration\n\t"ANSI_COLOR_RESET "SKYR Persona: NEW+ Account Signing In\n\tSKYR Persona: NEW+ Account Personal Recovery\n\n\tSKYR Persona: NEW+ Account Signing Out\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\tSKYR Persona: DANGER+ Personal Account DELETION || Do this at your OWN risks! [PERMANENTLY Impacted]\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");
                } else if ((MMPMSelected + 1) == 2) {
                    printf("\tSKYR Persona: NEW+ Account Registration\n      " BRIGHTMAGENTA217 ANSI_STYLE_UNDERLINE"> SKYR Persona: NEW+ Account Signing In\n\t"ANSI_COLOR_RESET "SKYR Persona: NEW+ Account Personal Recovery\n\n\tSKYR Persona: NEW+ Account Signing Out\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\tSKYR Persona: DANGER+ Personal Account DELETION || Do this at your OWN risks! [PERMANENTLY Impacted]\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");
                } else if ((MMPMSelected + 1) == 3) {
                    printf("\tSKYR Persona: NEW+ Account Registration\n\tSKYR Persona: NEW+ Account Signing In\n      " BRIGHTPURPLE218 ANSI_STYLE_UNDERLINE"> SKYR Persona: NEW+ Account Personal Recovery\n\n\t"ANSI_COLOR_RESET "SKYR Persona: NEW+ Account Signing Out\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\tSKYR Persona: DANGER+ Personal Account DELETION || Do this at your OWN risks! [PERMANENTLY Impacted]\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");
                } else if ((MMPMSelected + 1) == 4) {
                    printf("\tSKYR Persona: NEW+ Account Registration\n\tSKYR Persona: NEW+ Account Signing In\n\tSKYR Persona: NEW+ Account Personal Recovery\n\n      " BRIGHTPINK219 ANSI_STYLE_UNDERLINE"> SKYR Persona: NEW+ Account Signing Out\n"ANSI_COLOR_RESET"\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\tSKYR Persona: DANGER+ Personal Account DELETION || Do this at your OWN risks! [PERMANENTLY Impacted]\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");
                } else if ((MMPMSelected + 1) == 5) {
                    printf("\tSKYR Persona: NEW+ Account Registration\n\tSKYR Persona: NEW+ Account Signing In\n\tSKYR Persona: NEW+ Account Personal Recovery\n\n\tSKYR Persona: NEW+ Account Signing Out\n" ANSI_COLOR_LIGHTRED"\t────────────────────────────────────────────────────────────────────────────────────────────────────\n      "ANSI_COLOR_RESET ANSI_COLOR_LIGHTRED ANSI_STYLE_BOLD"> SKYR Persona: DANGER+ Personal Account DELETION || Do this at your OWN risks! [PERMANENTLY Impacted]\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTRED"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n");
                }

                (!CatchDefaultAKDC) ? printf(ANSI_COLOR_RESET"\n\n\n\n\t%s", AppProfileManagerUDRL) : printf(ANSI_COLOR_RESET"\n\n\t%s", AppProfileManagerUDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                if (MMPMSelected > 0 && MMPMSelected < AvailableOptions) {
                    --MMPMSelected; Updated = true;
                } else if (MMPMSelected <= 0) {
                    MMPMSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                if (MMPMSelected >= 0 && MMPMSelected < AvailableOptions - 1) {
                    ++MMPMSelected; Updated = true;
                } else if (MMPMSelected >= AvailableOptions - 1) {
                    MMPMSelected = 0; Updated = true;
                } break;
            case KEY_RIGHT:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                MainMenuApplicationInformations(0);
                break;
            case KEY_LEFT:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                MainMenuApplicationFeatures(0);
                break;
            case '1': AccountRegistrationMenu(0); Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '2': AccountLoginMenu(0); Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '3': AccountRecoveryMenu(0); Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '4': MMPMSelected = 3; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '5': MMPMSelected = 4; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: {
                if (AKDC == KEY_UP || AKDC == KEY_DOWN || AKDC == KEY_LEFT || AKDC == KEY_RIGHT || AKDC == KEY_ENTER) { ClearScreen(); continue; }
                (AKDC > 0) ? PreviousAKDC = (int)AKDC : 0;
                (AKDC > 0) ? CatchDefaultAKDC = true : false;
            } break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    }

    if (MMPMSelected == 0) {
        AccountRegistrationMenu(0);
        MainMenuApplicationFeatures(0);
    } else if (MMPMSelected == 1) {
        AccountLoginMenu(0);
        MainMenuApplicationFeatures(0);
    } else if (MMPMSelected == 2) {
        // MainMenuProfileManager(MMPMSelected);
        AccountRecoveryMenu(0);
        MainMenuApplicationFeatures(MMPMSelected);
    } else if (MMPMSelected == 3) {
        ClearScreen();
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppProfileManagerUI, UserName);
        
        printf("\tInfo: You are going to logout (signing out) from the application, resulting in deleting your save\n\t      file (as a privellege for auto-logged in). \n\t      Do you wish to continue to logout from the application?\n");
        printf("\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTGREEN"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_CYAN"Signing Out"ANSI_COLOR_RESET" from my profile account, or \n\t" ANSI_COLOR_LIGHTRED"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_RED"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_MAGENTA"Continue to stay Signed In"ANSI_COLOR_RESET " within the application!\n\n");
        
        snprintf(MessageID09, BUFSIZE10, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppProfileManagerUI, UserName);
        MessagesShown_ArrowKeyChoiceDialog[9] = MessageID09;
        MessagesShown_ArrowKeyChoiceDialog[10] = "\tInfo: You are going to logout (signing out) from the application, resulting in deleting your save\n\t      file (as a privellege for auto-logged in). \n\t      Do you wish to continue to logout from the application?";
        MessagesShown_ArrowKeyChoiceDialog[11] = "\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTGREEN"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_CYAN"Signing Out"ANSI_COLOR_RESET" from my profile account, or \n\t" ANSI_COLOR_LIGHTRED"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_RED"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_MAGENTA"Continue to stay Signed In"ANSI_COLOR_RESET " within the application!\n";
        SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 9, 12);
        
        // Check if the user is TRULY not going to logout!
        if (!SubmitOrContinue) MainMenuProfileManager(0);

        InfoMessageBox_OK("(Info) @SKYR-PFMSA; Account has Successfully Logged Out", "You've successfully logged out from your current account!\n\nNow you will be directed into the Account Login Menu right after you agreed to this message on your terminal... .");
        FullName[0] = 0; UserName[0] = 0;
        GlobalAccount = 0; ALMSelected = 0; FlagALM = false;
        LE = false; LPN = false; LU = false; LP = false;
        
        for (int i = 0; i < (int)GlobalSKYRFMSARegisteredAccounts; i++) {
            ALMInputs.Email[0] = 0; ALMInputs.PhoneNumber[0] = 0;
            ALMInputs.Username[0] = 0; ALMInputs.Password[0] = 0; ALMInputs.HiddenPasswordShown[0] = 0;

            if (access(SaveFilesTxtName[i].FileNames, F_OK) == 0 && strstr(SaveFilesTxtName[i].FileNames, "-SaveFile") != NULL) {
                strcpy(DeleteTempDestinationTxtFile, "del ");
                strcat(DeleteTempDestinationTxtFile, SaveFilesTxtName[i].FileNames);
                system(DeleteTempDestinationTxtFile);
            }
        } AccountLoginMenu(0);
    } else if (MMPMSelected == 4) {
        NULL;

    } // else if (MMPMSelected == 3) {
        // TODO: Create a function to manage the personal user profile account.
        //     MainMenuApplicationFeatures(0);
        // }
}

void MainMenuApplicationInformations(int MMAISelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    int AvailableOptions = 6; // , SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;
    int PreviousAKDC = 0;
    bool CatchDefaultAKDC = false;
    
    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppInformationsUI, UserName);
            if (CatchDefaultAKDC) printf(ANSI_COLOR_LIGHTRED"\tError: The auto-enter shortcut key labeled as '%c' (ID: 0x%02X) is not registered at the moment!\n\n"ANSI_COLOR_RESET, ((int)PreviousAKDC != 12) ? (char)PreviousAKDC : 10, (int)PreviousAKDC);

            if ((MMAISelected + 1) > 0 && (MMAISelected + 1) <= 6 && (AvailableOptions == 6)) {
                if ((MMAISelected + 1) == 1) {
                    printf("      " BRIGHTRED208 ANSI_STYLE_UNDERLINE"> Financial Moneytory Transaction(s) Registration\n\t"ANSI_COLOR_RESET "Financial Moneytory Transaction(s) Grouping per Category\n\tFinancial Moneytoring and Budget(s) Creations\n\tFinancial Moneytory Filtering and Searched History\n\tFinancial Moneytoring for Reminders and Notifications\n\tFinancial Moneytoring with Data and 2D Graphical Visualizations\n\n");
                } else if ((MMAISelected + 1) == 2) {
                    printf("\tFinancial Moneytory Transaction(s) Registration\n      " BRIGHTRED209 ANSI_STYLE_UNDERLINE"> Financial Moneytory Transaction(s) Grouping per Category\n\t"ANSI_COLOR_RESET "Financial Moneytoring and Budget(s) Creations\n\tFinancial Moneytory Filtering and Searched History\n\tFinancial Moneytoring for Reminders and Notifications\n\tFinancial Moneytoring with Data and 2D Graphical Visualizations\n\n");
                } else if ((MMAISelected + 1) == 3) {
                    printf("\tFinancial Moneytory Transaction(s) Registration\n\tFinancial Moneytory Transaction(s) Grouping per Category\n      " BRIGHTMAGENTA210 ANSI_STYLE_UNDERLINE"> Financial Moneytoring and Budget(s) Creations\n\t"ANSI_COLOR_RESET "Financial Moneytory Filtering and Searched History\n\tFinancial Moneytoring for Reminders and Notifications\n\tFinancial Moneytoring with Data and 2D Graphical Visualizations\n\n");
                } else if ((MMAISelected + 1) == 4) {
                    printf("\tFinancial Moneytory Transaction(s) Registration\n\tFinancial Moneytory Transaction(s) Grouping per Category\n\tFinancial Moneytoring and Budget(s) Creations\n      " BRIGHTMAGENTA211 ANSI_STYLE_UNDERLINE"> Financial Moneytory Filtering and Searched History\n\t"ANSI_COLOR_RESET "Financial Moneytoring for Reminders and Notifications\n\tFinancial Moneytoring with Data and 2D Graphical Visualizations\n\n");
                } else if ((MMAISelected + 1) == 5) {
                    printf("\tFinancial Moneytory Transaction(s) Registration\n\tFinancial Moneytory Transaction(s) Grouping per Category\n\tFinancial Moneytoring and Budget(s) Creations\n\tFinancial Moneytory Filtering and Searched History\n      " BRIGHTPURPLE212 ANSI_STYLE_UNDERLINE"> Financial Moneytoring for Reminders and Notifications\n\t"ANSI_COLOR_RESET "Financial Moneytoring with Data and 2D Graphical Visualizations\n\n");
                } else if ((MMAISelected + 1) == 6) {
                    printf("\tFinancial Moneytory Transaction(s) Registration\n\tFinancial Moneytory Transaction(s) Grouping per Category\n\tFinancial Moneytoring and Budget(s) Creations\n\tFinancial Moneytory Filtering and Searched History\n\tFinancial Moneytoring for Reminders and Notifications\n      " BRIGHTPURPLE213 ANSI_STYLE_UNDERLINE"> Financial Moneytoring with Data and 2D Graphical Visualizations\n\n"ANSI_COLOR_RESET);
                }

                (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\t%s", AppInformationsUDRL) : printf("\n\n\n\n\t%s", AppInformationsUDRL);
            }
        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppInformationsUI, UserName);
            if (CatchDefaultAKDC) printf(ANSI_COLOR_LIGHTRED"\tError: The auto-enter shortcut key labeled as '%c' (ID: 0x%02X) is not registered at the moment!\n\n"ANSI_COLOR_RESET, ((int)PreviousAKDC != 12) ? (char)PreviousAKDC : 10, (int)PreviousAKDC);

            if ((MMAISelected + 1) > 0 && (MMAISelected + 1) <= 6 && (AvailableOptions == 6)) {
                if ((MMAISelected + 1) == 1) {
                    printf("      " BRIGHTRED208 ANSI_STYLE_UNDERLINE"> Financial Moneytory Transaction(s) Registration\n\t"ANSI_COLOR_RESET "Financial Moneytory Transaction(s) Grouping per Category\n\tFinancial Moneytoring and Budget(s) Creations\n\tFinancial Moneytory Filtering and Searched History\n\tFinancial Moneytoring for Reminders and Notifications\n\tFinancial Moneytoring with Data and 2D Graphical Visualizations\n\n");
                } else if ((MMAISelected + 1) == 2) {
                    printf("\tFinancial Moneytory Transaction(s) Registration\n      " BRIGHTRED209 ANSI_STYLE_UNDERLINE"> Financial Moneytory Transaction(s) Grouping per Category\n\t"ANSI_COLOR_RESET "Financial Moneytoring and Budget(s) Creations\n\tFinancial Moneytory Filtering and Searched History\n\tFinancial Moneytoring for Reminders and Notifications\n\tFinancial Moneytoring with Data and 2D Graphical Visualizations\n\n");
                } else if ((MMAISelected + 1) == 3) {
                    printf("\tFinancial Moneytory Transaction(s) Registration\n\tFinancial Moneytory Transaction(s) Grouping per Category\n      " BRIGHTMAGENTA210 ANSI_STYLE_UNDERLINE"> Financial Moneytoring and Budget(s) Creations\n\t"ANSI_COLOR_RESET "Financial Moneytory Filtering and Searched History\n\tFinancial Moneytoring for Reminders and Notifications\n\tFinancial Moneytoring with Data and 2D Graphical Visualizations\n\n");
                } else if ((MMAISelected + 1) == 4) {
                    printf("\tFinancial Moneytory Transaction(s) Registration\n\tFinancial Moneytory Transaction(s) Grouping per Category\n\tFinancial Moneytoring and Budget(s) Creations\n      " BRIGHTMAGENTA211 ANSI_STYLE_UNDERLINE"> Financial Moneytory Filtering and Searched History\n\t"ANSI_COLOR_RESET "Financial Moneytoring for Reminders and Notifications\n\tFinancial Moneytoring with Data and 2D Graphical Visualizations\n\n");
                } else if ((MMAISelected + 1) == 5) {
                    printf("\tFinancial Moneytory Transaction(s) Registration\n\tFinancial Moneytory Transaction(s) Grouping per Category\n\tFinancial Moneytoring and Budget(s) Creations\n\tFinancial Moneytory Filtering and Searched History\n      " BRIGHTPURPLE212 ANSI_STYLE_UNDERLINE"> Financial Moneytoring for Reminders and Notifications\n\t"ANSI_COLOR_RESET "Financial Moneytoring with Data and 2D Graphical Visualizations\n\n");
                } else if ((MMAISelected + 1) == 6) {
                    printf("\tFinancial Moneytory Transaction(s) Registration\n\tFinancial Moneytory Transaction(s) Grouping per Category\n\tFinancial Moneytoring and Budget(s) Creations\n\tFinancial Moneytory Filtering and Searched History\n\tFinancial Moneytoring for Reminders and Notifications\n      " BRIGHTPURPLE213 ANSI_STYLE_UNDERLINE"> Financial Moneytoring with Data and 2D Graphical Visualizations\n\n"ANSI_COLOR_RESET);
                }

                (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\t%s", AppInformationsUDRL) : printf("\n\n\n\n\t%s", AppInformationsUDRL);
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                if (MMAISelected > 0 && MMAISelected < AvailableOptions) {
                    --MMAISelected; Updated = true;
                } else if (MMAISelected <= 0) {
                    MMAISelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                if (MMAISelected >= 0 && MMAISelected < AvailableOptions - 1) {
                    ++MMAISelected; Updated = true;
                } else if (MMAISelected >= AvailableOptions - 1) {
                    MMAISelected = 0; Updated = true;
                } break;
            case KEY_RIGHT:
                PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case KEY_LEFT:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                MainMenuProfileManager(0);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: {
                if (AKDC == KEY_UP || AKDC == KEY_DOWN || AKDC == KEY_LEFT || AKDC == KEY_RIGHT || AKDC == KEY_ENTER) { ClearScreen(); continue; }
                (AKDC > 0) ? PreviousAKDC = (int)AKDC : 0;
                (AKDC > 0) ? CatchDefaultAKDC = true : false;
            } break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    }

    if (MMAISelected == 0) {
        ClearScreen();
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);

    } else if (MMAISelected == 1) {
        ClearScreen();
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature02, UserName);

    } else if (MMAISelected == 2) {
        ClearScreen();
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

    } else if (MMAISelected == 3) {
        ClearScreen();
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature04, UserName);

    } else if (MMAISelected == 4) {
        ClearScreen();
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature05, UserName);

    } else if (MMAISelected == 5) {
        ClearScreen();
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature06, UserName);

    }
}

void F1_MoneytoryTransactionsRegister(int F1Selected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    FILE *FDestination, *FDestination02, *FSourceTemp, *FDestinationTemp, *FDestinationTemp02;
    time_t Time = time(NULL);
    struct tm ManageTime = *localtime(&Time);
    char F1LoggedInFileName[BUFSIZE07], TempF1LoggedInFileName[BUFSIZE07];

    int BufLen, Ptr = 0, KeyTracker = 0;
    char FDBuffer[BUFSIZE16], DeleteTempDestinationTxtFile[128], TxtFileName[128], TempCountRegisteredTransactions[BUFSIZE07];
    char *SourceKeyStringValue, *SelectedKeyString, *CountRegisteredTransactions;
    char *SourceKeyStringValues[BUFSIZE07];

    char RegMTRInsider[BUFSIZE07], MTR[BUFSIZE07];
    char TransactionByDate[BUFSIZE07], IncomeOrExpense[BUFSIZE07], TotalSpentMoney[BUFSIZE07], FinancialUsesCategory[BUFSIZE07], TransactionDescription[BUFSIZE07];
    char UpdateLocalTime[BUFSIZE07], LocalTime[BUFSIZE07], MTRMadeTime[BUFSIZE07], MadeTime[BUFSIZE07];

    int AvailableOptions = 6, SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true, FirstF1MTRUpgrade = false;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    long long int MonthlyBalanceBudget = 0, MonthlyTrackIncomes = 0, MonthlyTrackExpenses = 0, PerDaySpentMoney = 0;
    char TempBalanceBudget[BUFSIZE07], TempTrackIncomes[BUFSIZE07], TempTrackExpenses[BUFSIZE07], TempSpentMoney[BUFSIZE07];
    char DisplayBB[BUFSIZE07], DisplayTI[BUFSIZE07], DisplayTE[BUFSIZE07];
    char *BalanceBudget, *TrackIncomes, *TrackExpenses, *SpentMoney;
    char UserBudgetCreationTxtFile[BUFSIZE07], MessageID10[BUFSIZE10];
    char MonthsOfYear[12][BUFSIZE07] = {"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};

    snprintf(F1LoggedInFileName, BUFSIZE07, "%s-F1-MTR-%s-%d.txt", UserName, MonthsOfYear[ManageTime.tm_mon], (1900 + ManageTime.tm_year));
    snprintf(TempF1LoggedInFileName, BUFSIZE07, "TEMP-%s-F1-MTR-%s-%d.txt", UserName, MonthsOfYear[ManageTime.tm_mon], (1900 + ManageTime.tm_year));
    snprintf(UserBudgetCreationTxtFile, BUFSIZE07, "%s-F3-BCAM-%s-%d.txt", UserName, MonthsOfYear[ManageTime.tm_mon], (1900 + ManageTime.tm_year));
    
    if (access(UserBudgetCreationTxtFile, F_OK) != 0) {
        InfoMessageBox_OK("(Info) Moneytory Transaction Registration: No Monthly Budget(s) were Created", \
                          "We're truly sorry for the incoviniences, but right know you can't make any transactions be registered into the file system while having NO MONTHLY BUDGET for keep tracking the moneytory of your income(s) and/or expense(s) for the next 30 DAYS.\n\nSee right on your terminal for further informations, and if you still willingly to make any moneytory transaction be registered, make sure you already have the monthly budget on you!");

        ClearScreen();
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);
        
        printf(BRIGHTPURPLE212 ANSI_STYLE_BOLD"\tInfo: We've checked that for today's month, currently in " BRIGHTBLUE159 ANSI_STYLE_BOLD"%s %d, " BRIGHTMAGENTA217 ANSI_STYLE_BOLD"you've NOT YET created a\n", MonthsOfYear[ManageTime.tm_mon], (1900 + ManageTime.tm_year));
        printf("\t      " BRIGHTPINK219 ANSI_STYLE_BOLD"BUDGET MONITORING" BRIGHTMAGENTA217 ANSI_STYLE_BOLD" for this specific month and such, so please head up to the main menu first\n");
        printf("\t      after this interaction and SELECT the THIRD feature option, naming as:\n");
        printf(BRIGHTGREEN156 ANSI_STYLE_BOLD"\n\t\t  " ANSI_STYLE_UNDERLINE"> Personal Budget Creation and Transaction Monitoring.\n\n"ANSI_COLOR_RESET);

        printf(BRIGHTBLUE157 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"\tNote: Remember! If you already make a budget for a specific month, then you need to wait for at\n");
        printf("\t      max.: 30 DAYS, before you can create another budget monitoring and stuffs...\n");
        printf("\t      Happy Transactions, %s!\n\n", UserName);

        printf(ANSI_COLOR_MAGENTA ANSI_STYLE_ITALIC"\t[ENTER] Head back to main menu of the application... ");
        getchar(); MainMenuApplicationFeatures(MMAFSelected);
    }

    // strtok_r(ReadAndPrintLine(UserBudgetCreationTxtFile, 2 + (14 * SignedInAccountNo)), ":", &BalanceBudget);
    // BalanceBudget = TrimWhiteSpaces(BalanceBudget);
    strncpy(TxtFileName, F1LoggedInFileName, BUFSIZE07); strcat(TxtFileName, " > Recorded Financial Transaction History");

    if (access(F1LoggedInFileName, F_OK) != 0 && !FlagF1MTR) { GlobalRegisteredMTR = 0; }
    else if (access(F1LoggedInFileName, F_OK) == 0 && !FlagF1MTR) {
        FDestination       = fopen(F1LoggedInFileName, "r");
        FDestinationTemp   = fopen("TempDestination.txt", "w");

        while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
            BufLen = strlen(FDBuffer);
            for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
            fputs(FDBuffer, FDestinationTemp);
        } fclose(FDestination); fclose(FDestinationTemp);

        strtok_r(TxtFileName, ">", &SelectedKeyString);
        SelectedKeyString = TrimWhiteSpaces(SelectedKeyString);
        SourceKeyStringValue = strtok(SelectedKeyString, ",");
        KeyTracker++;

        while (SourceKeyStringValue != NULL) {
            SourceKeyStringValues[Ptr] = SourceKeyStringValue;
            SourceKeyStringValues[Ptr] = TrimWhiteSpaces(SourceKeyStringValues[Ptr]);
            SourceKeyStringValue = strtok(NULL, ",");
            Ptr++; KeyTracker++;
        } // SourceTextFileName = TrimWhiteSpaces(TxtFileName);
        
        strcpy(TempCountRegisteredTransactions, ReadAndPrintLine("TempDestination.txt", 9));

        strcpy(DeleteTempDestinationTxtFile, "del "); strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
        system(DeleteTempDestinationTxtFile);

        TempCountRegisteredTransactions[strlen(TempCountRegisteredTransactions) - 1] = '\0';
        strtok_r(TempCountRegisteredTransactions, ":", &CountRegisteredTransactions);
        
        CountRegisteredTransactions = TrimWhiteSpaces(CountRegisteredTransactions);
        CountRegisteredTransactions = strtok(CountRegisteredTransactions, " ");
        GlobalRegisteredMTR = atoi(CountRegisteredTransactions);
        FlagF1MTR = true;
    }

    FDestination02     = fopen(UserBudgetCreationTxtFile, "r");
    FDestinationTemp02 = fopen("TempDestination02.txt", "w");

    while (fgets(FDBuffer, sizeof(FDBuffer), FDestination02) != 0) {
        BufLen = strlen(FDBuffer);
        for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
        fputs(FDBuffer, FDestinationTemp02);
    } fclose(FDestination02); fclose(FDestinationTemp02);
    
    strncpy(TempBalanceBudget, ReadAndPrintLine("TempDestination02.txt", 15), BUFSIZE07);
    TempBalanceBudget[strlen(TempBalanceBudget) - 1] = '\0';
    strtok_r(TempBalanceBudget, ":", &BalanceBudget); BalanceBudget = TrimWhiteSpaces(BalanceBudget);
    BalanceBudget = strtok(BalanceBudget, ","); strtok_r(BalanceBudget, "p", &BalanceBudget);
    MonthlyBalanceBudget = (long long)atoi(BalanceBudget);
    
    strncpy(TempTrackIncomes, ReadAndPrintLine("TempDestination02.txt", 16), BUFSIZE07);
    TempTrackIncomes[strlen(TempTrackIncomes) - 1] = '\0';
    strtok_r(TempTrackIncomes, ":", &TrackIncomes); TrackIncomes = TrimWhiteSpaces(TrackIncomes);
    TrackIncomes = strtok(TrackIncomes, ","); strtok_r(TrackIncomes, "p", &TrackIncomes);
    MonthlyTrackIncomes = (long long)atoi(TrackIncomes);
    
    strncpy(TempTrackExpenses, ReadAndPrintLine("TempDestination02.txt", 17), BUFSIZE07);
    TempTrackExpenses[strlen(TempTrackExpenses) - 1] = '\0';
    strtok_r(TempTrackExpenses, ":", &TrackExpenses); TrackExpenses = TrimWhiteSpaces(TrackExpenses);
    TrackExpenses = strtok(TrackExpenses, ","); strtok_r(TrackExpenses, "p", &TrackExpenses);
    MonthlyTrackExpenses = (long long)atoi(TrackExpenses);

    strcpy(DeleteTempDestinationTxtFile, "del "); strcat(DeleteTempDestinationTxtFile, "TempDestination02.txt");
    system(DeleteTempDestinationTxtFile);

    if (MonthlyBalanceBudget <= 100000) {
        WarningMessageBox_CANCELTRYCONTINUE("(Warning) Moneytory Transaction Registration: Upcoming \"Debt\" in Monthly Budget Limit", "We're recommending you to stop record and doing anymore unnecessary transactions, since you're monthly limit got drained a lot and can/or be less than zero already!\n\nIf you insist to keep recording the transactions, do this on your own consent, since you're going exceed of your monthly budget limit.\n\nHighly recommended for record the INCOME(s) ONLY, in order to cover the exccesive EXPENSE(s)... .");
    }

    if ((TBD && IOE && TSM && FUC && TD) && !FirstF1MTRUpgrade) {
        InfoMessageBox_OK("(Info) Moneytory Transaction Registration: Completing The Pre-requisites and Submission", \
                          "You've completed all the pre-requisites for registering your moneytory transaction for today, and you actually can fill in more financial transaction every time WITHIN on that day only.\n\nBut remember, once you've submitted the pre-requisites down below, you CAN'T EDIT or DELETE ANYMORE since it will be saved onto the file system and will be displayed using the Histogram Graph for better lookup and maintaining your income(s) and/or expense(s) for the future!\n\nThis message may appear everytime you make changes, so make sure that whatever you're filling in the pre-requisites ARE INDEED on what actual transactions you've made along the way of the day!\n\nPROGRESS: Keep moving UPWARD or DOWNWARD until you see a complete different UI for SUBMITTING your Moneytory Transaction Registration!");
        AvailableOptions++; FirstF1MTRUpgrade = true;
    }

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);
            printf(BRIGHTBLUE159 ANSI_STYLE_BOLD"\t(Current Remaining Monthly Budget) %s %d: " ANSI_STYLE_UNDERLINE"Rp%lld,00\n"ANSI_COLOR_RESET, MonthsOfYear[ManageTime.tm_mon], (1900 + ManageTime.tm_year), MonthlyBalanceBudget);
            printf(BRIGHTGREEN156 ANSI_STYLE_BOLD"\t+++ Income(s):  " ANSI_STYLE_UNDERLINE"Rp%lld,00\n"ANSI_COLOR_RESET, MonthlyTrackIncomes);
            printf(BRIGHTRED216   ANSI_STYLE_BOLD"\t--- Expense(s): " ANSI_STYLE_UNDERLINE"Rp%lld,00\n\n"ANSI_COLOR_RESET, MonthlyTrackExpenses);

            if ((F1Selected + 1) > 0 && (F1Selected + 1) <= 6 && (AvailableOptions == 6)) {
                if ((F1Selected + 1) == 1) {
                    printf("      " BRIGHTGREEN154"> Transaction by Date:\t\t%s\n\t"ANSI_COLOR_RESET "Recorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 2) {
                    printf("\tTransaction by Date:\t\t%s\n      " BRIGHTGREEN155"> Recorded Transaction Type:\t%s\n\t"ANSI_COLOR_RESET "Nominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 3) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n      " BRIGHTGREEN156"> Nominal Fee (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Transaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 4) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Transaction Category:\t\t%s\n\t"ANSI_COLOR_RESET "Transaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 5) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n      " BRIGHTBLUE158"> Transaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 6) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET BRIGHTPURPLE213 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"      > (Back to the Main Menu)"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                }

                printf("\n\n\n\t%s", AppGuideOnUsageUDRL);
            
            } else if ((F1Selected + 1) > 0 && (F1Selected + 1) <= 7 && (AvailableOptions == 7)) {
                if ((F1Selected + 1) == 1) {
                    printf("      " BRIGHTGREEN154"> Transaction by Date:\t\t%s\n\t"ANSI_COLOR_RESET "Recorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 2) {
                    printf("\tTransaction by Date:\t\t%s\n      " BRIGHTGREEN155"> Recorded Transaction Type:\t%s\n\t"ANSI_COLOR_RESET "Nominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 3) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n      " BRIGHTGREEN156"> Nominal Fee (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Transaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 4) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Transaction Category:\t\t%s\n\t"ANSI_COLOR_RESET "Transaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 5) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n      " BRIGHTBLUE158"> Transaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 6) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET BRIGHTPURPLE213 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"      > (Back to the Main Menu)"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                }

                printf("\n\n\n\t%s", AppGuideOnUsageUDRL);
                
                if ((F1Selected + 1) > 6) {
                    ClearScreen();
                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);

                    printf("\tInfo: You've finished making your current pre-recorded transaction for today (or in the future), and \n\t      now you're ready to submit your recorded transaction history over the file system.\n");
                    printf("\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour current pre-recorded transaction history?\n\n");
                    
                    snprintf(MessageID10, BUFSIZE10, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);
                    MessagesShown_ArrowKeyChoiceDialog[10] = MessageID10;
                    MessagesShown_ArrowKeyChoiceDialog[11] = "\tInfo: You've finished making your current pre-recorded transaction for today (or in the future), and \n\t      now you're ready to submit your recorded transaction history over the file system.";
                    MessagesShown_ArrowKeyChoiceDialog[12] = "\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour current pre-recorded transaction history?\n";
                    SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 10, 13);

                    if (SubmitOrContinue) {
                        if (access(F1LoggedInFileName, F_OK) != 0 && !FlagF1MTR) {
                            FSourceTemp = fopen(TempF1LoggedInFileName, "w");

                            strcpy(MTR, "1");
                            snprintf(LocalTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                            strcpy(RegMTRInsider, "Recorded Financial Transaction History: "); strcat(RegMTRInsider, MTR); strcat(RegMTRInsider, " transaction(s) in total.\n");
                            strcpy(UpdateLocalTime, "PersonalFMSA | Last Updated: ");
                            strcat(UpdateLocalTime, LocalTime); strcat(UpdateLocalTime, "\n");
                            strcpy(MTRMadeTime, "Recorded Financial Transaction :: No. 1"); strcat(MTRMadeTime, "\n");
                            strcat(MTRMadeTime, "Created on: "); strcat(MTRMadeTime, MadeTime); strcat(MTRMadeTime, "\n");

                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                            fputs(ApplicationPresent, FSourceTemp);
                            fputs(ApplicationTitle, FSourceTemp);
                            fputs(ApplicationVersion, FSourceTemp); fputs("\n", FSourceTemp);
                            fputs(UpdateLocalTime, FSourceTemp);
                            fputs("Built-in Console Application [CLI-Win32], fundamentally C (100%)\n", FSourceTemp);
                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                            fputs(RegMTRInsider, FSourceTemp);
                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                            fclose(FSourceTemp);

                        } else if (access(F1LoggedInFileName, F_OK) == 0 && FlagF1MTR) {
                            FDestination     = fopen(F1LoggedInFileName, "r");
                            FDestinationTemp = fopen(TempF1LoggedInFileName, "w");

                            while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
                                BufLen = strlen(FDBuffer);
                                for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                                fputs(FDBuffer, FDestinationTemp);
                            } fclose(FDestination); fclose(FDestinationTemp);
                        }
                        
                        FDestination02     = fopen(UserBudgetCreationTxtFile, "r");
                        FDestinationTemp02 = fopen("TempDestination02.txt", "w");

                        while (fgets(FDBuffer, sizeof(FDBuffer), FDestination02) != 0) {
                            BufLen = strlen(FDBuffer);
                            for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                            fputs(FDBuffer, FDestinationTemp02);
                        } fclose(FDestination02); fclose(FDestinationTemp02);
                        
                        FSourceTemp = fopen(TempF1LoggedInFileName, "a+");

                        if (!FlagF1MTR) { strcpy(MTR, "1"); }
                        else if (FlagF1MTR && GlobalRegisteredMTR >= 1) { snprintf(MTR, BUFSIZE07, "%lld", (GlobalRegisteredMTR + 1)); }
                        
                        snprintf(MadeTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                        strcpy(MTRMadeTime, "Recorded Financial Transaction :: No. "); strcat(MTRMadeTime, MTR); strcat(MTRMadeTime, "\n");
                        strcat(MTRMadeTime, "Created on: "); strcat(MTRMadeTime, MadeTime); strcat(MTRMadeTime, "\n");

                        strcpy(TransactionByDate, "Transaction by Date:\t\t");        strcat(TransactionByDate, MTRInputs[GlobalRegisteredMTR].TransactionDate);             strcat(TransactionByDate, "\n");
                        strcpy(IncomeOrExpense, "Recorded Transaction Type:\t");      strcat(IncomeOrExpense, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses);              strcat(IncomeOrExpense, "\n");
                        strcpy(TotalSpentMoney, "Nominal Fee (in Rp.):\t\t");         strcat(TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney);               strcat(TotalSpentMoney, "\n");
                        strcpy(FinancialUsesCategory, "Transaction Category:\t\t");   strcat(FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory);   strcat(FinancialUsesCategory, "\n");
                        strcpy(TransactionDescription, "Transaction Description:\n"); strcat(TransactionDescription, MTRInputs[GlobalRegisteredMTR].TransactionDescription); strcat(TransactionDescription, "\n");

                        fputs(MTRMadeTime, FSourceTemp); fputs("\n", FSourceTemp);
                        fputs(TransactionByDate, FSourceTemp); fputs(IncomeOrExpense, FSourceTemp); fputs(TotalSpentMoney, FSourceTemp); fputs(FinancialUsesCategory, FSourceTemp); fputs(TransactionDescription, FSourceTemp);
                        fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                        fclose(FSourceTemp);

                        TBD = false; IOE = false; TSM = false; FUC = false, TD = false;
                        strncpy(TempSpentMoney, TotalSpentMoney, BUFSIZE07);
                        strtok_r(TempSpentMoney, ":", &SpentMoney); SpentMoney = TrimWhiteSpaces(SpentMoney);
                        strtok_r(SpentMoney, "p", &SpentMoney); SpentMoney = TrimWhiteSpaces(SpentMoney);
                        SpentMoney = strtok(SpentMoney, ","); SpentMoney = TrimWhiteSpaces(SpentMoney);
                        PerDaySpentMoney = (long long)atoi(SpentMoney);

                        snprintf(DisplayBB, BUFSIZE07, "Current Remaining Monthly Budget: Rp%lld,00", (strstr(IncomeOrExpense, "Income(s)") != NULL) ? (MonthlyBalanceBudget + PerDaySpentMoney) : (MonthlyBalanceBudget - PerDaySpentMoney));
                        snprintf(DisplayTI, BUFSIZE07, "+++ Income(s):  Rp%lld,00", (strstr(IncomeOrExpense, "Income(s)") != NULL) ? (MonthlyTrackIncomes + PerDaySpentMoney) : (MonthlyTrackIncomes + 0));
                        snprintf(DisplayTE, BUFSIZE07, "--- Expense(s): Rp%lld,00", (strstr(IncomeOrExpense, "Expense(s)") != NULL) ? (MonthlyTrackExpenses + PerDaySpentMoney) : (MonthlyTrackExpenses + 0));

                        strcpy(RegMTRInsider, "Recorded Financial Transaction History: "); strcat(RegMTRInsider, MTR); strcat(RegMTRInsider, " transaction(s) in total.");
                        OverWriteStringAtLine(TempF1LoggedInFileName, RegMTRInsider, 0, 9);
                        OverWriteStringAtLine("TempDestination02.txt", DisplayBB, 0, 15);
                        OverWriteStringAtLine("TempDestination02.txt", DisplayTI, 0, 16);
                        OverWriteStringAtLine("TempDestination02.txt", DisplayTE, 0, 17);
                        EncryptTxtFile(TempF1LoggedInFileName, F1LoggedInFileName, EncryptionKey, true);
                        EncryptTxtFile("TempDestination02.txt", UserBudgetCreationTxtFile, EncryptionKey, true);
                        
                        GlobalRegisteredMTR++; FlagF1MTR = false;
                        MainMenuApplicationFeatures(MMAFSelected);

                    } else {
                        F1_MoneytoryTransactionsRegister(0);
                    }
                }
            }

        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);
            printf(BRIGHTBLUE159 ANSI_STYLE_BOLD"\t(Current Remaining Monthly Budget) %s %d: " ANSI_STYLE_UNDERLINE"Rp%lld,00\n"ANSI_COLOR_RESET, MonthsOfYear[ManageTime.tm_mon], (1900 + ManageTime.tm_year), MonthlyBalanceBudget);
            printf(BRIGHTGREEN156 ANSI_STYLE_BOLD"\t+++ Income(s):  " ANSI_STYLE_UNDERLINE"Rp%lld,00\n"ANSI_COLOR_RESET, MonthlyTrackIncomes);
            printf(BRIGHTRED216   ANSI_STYLE_BOLD"\t--- Expense(s): " ANSI_STYLE_UNDERLINE"Rp%lld,00\n\n"ANSI_COLOR_RESET, MonthlyTrackExpenses);

            if ((F1Selected + 1) > 0 && (F1Selected + 1) <= 6 && (AvailableOptions == 6)) {
                if ((F1Selected + 1) == 1) {
                    printf("      " BRIGHTGREEN154"> Transaction by Date:\t\t%s\n\t"ANSI_COLOR_RESET "Recorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 2) {
                    printf("\tTransaction by Date:\t\t%s\n      " BRIGHTGREEN155"> Recorded Transaction Type:\t%s\n\t"ANSI_COLOR_RESET "Nominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 3) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n      " BRIGHTGREEN156"> Nominal Fee (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Transaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 4) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Transaction Category:\t\t%s\n\t"ANSI_COLOR_RESET "Transaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 5) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n      " BRIGHTBLUE158"> Transaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 6) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET BRIGHTPURPLE213 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"      > (Back to the Main Menu)"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                }

                printf("\n\n\n\t%s", AppGuideOnUsageUDRL);
            
            } else if ((F1Selected + 1) > 0 && (F1Selected + 1) <= 7 && (AvailableOptions == 7)) {
                if ((F1Selected + 1) == 1) {
                    printf("      " BRIGHTGREEN154"> Transaction by Date:\t\t%s\n\t"ANSI_COLOR_RESET "Recorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 2) {
                    printf("\tTransaction by Date:\t\t%s\n      " BRIGHTGREEN155"> Recorded Transaction Type:\t%s\n\t"ANSI_COLOR_RESET "Nominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 3) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n      " BRIGHTGREEN156"> Nominal Fee (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Transaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 4) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Transaction Category:\t\t%s\n\t"ANSI_COLOR_RESET "Transaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 5) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n      " BRIGHTBLUE158"> Transaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                } else if ((F1Selected + 1) == 6) {
                    printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET BRIGHTPURPLE213 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"      > (Back to the Main Menu)"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                }

                printf("\n\n\n\t%s", AppGuideOnUsageUDRL);
                
                if ((F1Selected + 1) > 6) {
                    ClearScreen();
                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);

                    printf("\tInfo: You've finished making your current pre-recorded transaction for today (or in the future), and \n\t      now you're ready to submit your recorded transaction history over the file system.\n");
                    printf("\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour current pre-recorded transaction history?\n\n");
                    
                    snprintf(MessageID10, BUFSIZE10, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);
                    MessagesShown_ArrowKeyChoiceDialog[10] = MessageID10;
                    MessagesShown_ArrowKeyChoiceDialog[11] = "\tInfo: You've finished making your current pre-recorded transaction for today (or in the future), and \n\t      now you're ready to submit your recorded transaction history over the file system.";
                    MessagesShown_ArrowKeyChoiceDialog[12] = "\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour current pre-recorded transaction history?\n";
                    SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 10, 13);

                    if (SubmitOrContinue) {
                        if (access(F1LoggedInFileName, F_OK) != 0 && !FlagF1MTR) {
                            FSourceTemp = fopen(TempF1LoggedInFileName, "w");

                            strcpy(MTR, "1");
                            snprintf(LocalTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                            strcpy(RegMTRInsider, "Recorded Financial Transaction History: "); strcat(RegMTRInsider, MTR); strcat(RegMTRInsider, " transaction(s) in total.\n");
                            strcpy(UpdateLocalTime, "PersonalFMSA | Last Updated: ");
                            strcat(UpdateLocalTime, LocalTime); strcat(UpdateLocalTime, "\n");
                            strcpy(MTRMadeTime, "Recorded Financial Transaction :: No. 1"); strcat(MTRMadeTime, "\n");
                            strcat(MTRMadeTime, "Created on: "); strcat(MTRMadeTime, MadeTime); strcat(MTRMadeTime, "\n");

                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                            fputs(ApplicationPresent, FSourceTemp);
                            fputs(ApplicationTitle, FSourceTemp);
                            fputs(ApplicationVersion, FSourceTemp); fputs("\n", FSourceTemp);
                            fputs(UpdateLocalTime, FSourceTemp);
                            fputs("Built-in Console Application [CLI-Win32], fundamentally C (100%)\n", FSourceTemp);
                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                            fputs(RegMTRInsider, FSourceTemp);
                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                            fclose(FSourceTemp);

                        } else if (access(F1LoggedInFileName, F_OK) == 0 && FlagF1MTR) {
                            FDestination     = fopen(F1LoggedInFileName, "r");
                            FDestinationTemp = fopen(TempF1LoggedInFileName, "w");

                            while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
                                BufLen = strlen(FDBuffer);
                                for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                                fputs(FDBuffer, FDestinationTemp);
                            } fclose(FDestination); fclose(FDestinationTemp);
                        }
                        
                        FDestination02     = fopen(UserBudgetCreationTxtFile, "r");
                        FDestinationTemp02 = fopen("TempDestination02.txt", "w");

                        while (fgets(FDBuffer, sizeof(FDBuffer), FDestination02) != 0) {
                            BufLen = strlen(FDBuffer);
                            for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                            fputs(FDBuffer, FDestinationTemp02);
                        } fclose(FDestination02); fclose(FDestinationTemp02);
                        
                        FSourceTemp = fopen(TempF1LoggedInFileName, "a+");

                        if (!FlagF1MTR) { strcpy(MTR, "1"); }
                        else if (FlagF1MTR && GlobalRegisteredMTR >= 1) { snprintf(MTR, BUFSIZE07, "%lld", (GlobalRegisteredMTR + 1)); }
                        
                        snprintf(MadeTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                        strcpy(MTRMadeTime, "Recorded Financial Transaction :: No. "); strcat(MTRMadeTime, MTR); strcat(MTRMadeTime, "\n");
                        strcat(MTRMadeTime, "Created on: "); strcat(MTRMadeTime, MadeTime); strcat(MTRMadeTime, "\n");

                        strcpy(TransactionByDate, "Transaction by Date:\t\t");        strcat(TransactionByDate, MTRInputs[GlobalRegisteredMTR].TransactionDate);             strcat(TransactionByDate, "\n");
                        strcpy(IncomeOrExpense, "Recorded Transaction Type:\t");      strcat(IncomeOrExpense, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses);              strcat(IncomeOrExpense, "\n");
                        strcpy(TotalSpentMoney, "Nominal Fee (in Rp.):\t\t");         strcat(TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney);               strcat(TotalSpentMoney, "\n");
                        strcpy(FinancialUsesCategory, "Transaction Category:\t\t");   strcat(FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory);   strcat(FinancialUsesCategory, "\n");
                        strcpy(TransactionDescription, "Transaction Description:\n"); strcat(TransactionDescription, MTRInputs[GlobalRegisteredMTR].TransactionDescription); strcat(TransactionDescription, "\n");

                        fputs(MTRMadeTime, FSourceTemp); fputs("\n", FSourceTemp);
                        fputs(TransactionByDate, FSourceTemp); fputs(IncomeOrExpense, FSourceTemp); fputs(TotalSpentMoney, FSourceTemp); fputs(FinancialUsesCategory, FSourceTemp); fputs(TransactionDescription, FSourceTemp);
                        fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                        fclose(FSourceTemp);

                        TBD = false; IOE = false; TSM = false; FUC = false, TD = false;
                        strncpy(TempSpentMoney, TotalSpentMoney, BUFSIZE07);
                        strtok_r(TempSpentMoney, ":", &SpentMoney); SpentMoney = TrimWhiteSpaces(SpentMoney);
                        strtok_r(SpentMoney, "p", &SpentMoney); SpentMoney = TrimWhiteSpaces(SpentMoney);
                        SpentMoney = strtok(SpentMoney, ","); SpentMoney = TrimWhiteSpaces(SpentMoney);
                        PerDaySpentMoney = (long long)atoi(SpentMoney);

                        snprintf(DisplayBB, BUFSIZE07, "Current Remaining Monthly Budget: Rp%lld,00", (strstr(IncomeOrExpense, "Income(s)") != NULL) ? (MonthlyBalanceBudget + PerDaySpentMoney) : (MonthlyBalanceBudget - PerDaySpentMoney));
                        snprintf(DisplayTI, BUFSIZE07, "+++ Income(s):  Rp%lld,00", (strstr(IncomeOrExpense, "Income(s)") != NULL) ? (MonthlyTrackIncomes + PerDaySpentMoney) : (MonthlyTrackIncomes + 0));
                        snprintf(DisplayTE, BUFSIZE07, "--- Expense(s): Rp%lld,00", (strstr(IncomeOrExpense, "Expense(s)") != NULL) ? (MonthlyTrackExpenses + PerDaySpentMoney) : (MonthlyTrackExpenses + 0));

                        strcpy(RegMTRInsider, "Recorded Financial Transaction History: "); strcat(RegMTRInsider, MTR); strcat(RegMTRInsider, " transaction(s) in total.");
                        OverWriteStringAtLine(TempF1LoggedInFileName, RegMTRInsider, 0, 9);
                        OverWriteStringAtLine("TempDestination02.txt", DisplayBB, 0, 15);
                        OverWriteStringAtLine("TempDestination02.txt", DisplayTI, 0, 16);
                        OverWriteStringAtLine("TempDestination02.txt", DisplayTE, 0, 17);
                        EncryptTxtFile(TempF1LoggedInFileName, F1LoggedInFileName, EncryptionKey, true);
                        EncryptTxtFile("TempDestination02.txt", UserBudgetCreationTxtFile, EncryptionKey, true);
                        
                        GlobalRegisteredMTR++; FlagF1MTR = false;
                        MainMenuApplicationFeatures(MMAFSelected);

                    } else {
                        F1_MoneytoryTransactionsRegister(0);
                    }
                }
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (F1Selected > 0 && F1Selected < AvailableOptions) {
                    --F1Selected; Updated = true;
                } else if (F1Selected <= 0) {
                    F1Selected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (F1Selected >= 0 && F1Selected < AvailableOptions - 1) {
                    ++F1Selected; Updated = true;
                } else if (F1Selected >= AvailableOptions - 1) {
                    F1Selected = 0; Updated = true;
                } break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    }

    if (F1Selected == 0) {
        ClearScreen();
        char   InputTransactionByDate[BUFSIZE07], InputTBDTemp[BUFSIZE07], NumericalPattern[BUFSIZE07];
        char   *TempTBDTempD, *TempTBDTempM, *TempTBDTempY, *TBDTempD, *TBDTempM, *TBDTempY;
        char   DaysOfWeek[7][BUFSIZE07]      = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        char   MonthsOfYear[12][BUFSIZE07]   = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        int    TimeCounterNumeric[12]        = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        int    DashesOccurences = 0;
        bool   EmptyTBDInput = false;
        size_t TempDate, TempMonth, TempYear, Day, Date, Month, Year;

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);

        if (TBD) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your transaction by date as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate);
            printf("      " BRIGHTGREEN154"> Transaction by Date:\t\t%s\n\t"ANSI_COLOR_RESET "Recorded Transaction Type:\t\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Transaction by Date."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your date of birth profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The transaction by date of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of transaction by date format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);
        } else {
            printf("      " BRIGHTGREEN154"> Transaction by Date:\t\t%s\n\t"ANSI_COLOR_RESET "Recorded Transaction Type:\t\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Transaction by Date."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your date of birth profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The transaction by date of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of transaction by date format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);
        }

        printf("\nTransaction by Date: ");
        fgets(InputTransactionByDate, BUFSIZE07, stdin);

        if (strlen(InputTransactionByDate) < 2) { EmptyTBDInput = true; }
        else {
            strcpy(InputTBDTemp, InputTransactionByDate);
            InputTBDTemp[strlen(InputTBDTemp) - 1] = '\0';
            DashesOccurences = FindOccurences(InputTBDTemp, '-');
            if (DashesOccurences == 2) {
                TempTBDTempD = strtok(InputTBDTemp, "-"); TempTBDTempM = strtok(NULL, "-"); TempTBDTempY = strtok(NULL, "-");
                TempDate = atoi(TempTBDTempD); TempMonth = atoi(TempTBDTempM); TempYear = atoi(TempTBDTempY);
            } EmptyTBDInput = false;
        }

        while (EmptyTBDInput || DashesOccurences != 2 || (((TempYear % 4) == 0 && (TempMonth == 2)) && TempDate > 29) || (((TempYear % 4) != 0 && (TempMonth == 2)) && TempDate > 28) || (TempDate < 1 || TempDate > 31) || (TempMonth < 1 || TempMonth > 12) || (TempYear < 1)) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your transaction by date as what the pre-requisites requested for!\n"ANSI_COLOR_RESET);
            printf("      " BRIGHTGREEN154"> Transaction by Date:\t\t%s\n\t"ANSI_COLOR_RESET "Recorded Transaction Type:\t\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Transaction by Date."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your date of birth profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The transaction by date of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of transaction by date format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);

            printf("\nTransaction by Date: ");
            fgets(InputTransactionByDate, BUFSIZE07, stdin);

            if (strlen(InputTransactionByDate) < 2) { EmptyTBDInput = true; }
            else {
                strcpy(InputTBDTemp, InputTransactionByDate);
                InputTBDTemp[strlen(InputTBDTemp) - 1] = '\0';
                DashesOccurences = FindOccurences(InputTBDTemp, '-');
                if (DashesOccurences == 2) {
                    TempTBDTempD = strtok(InputTBDTemp, "-"); TempTBDTempM = strtok(NULL, "-"); TempTBDTempY = strtok(NULL, "-");
                    TempDate = atoi(TempTBDTempD); TempMonth = atoi(TempTBDTempM); TempYear = atoi(TempTBDTempY);
                } EmptyTBDInput = false;
            }
        }
        
        InputTransactionByDate[strlen(InputTransactionByDate) - 1] = '\0';
        TBD = true;
        TBDTempD = strtok(InputTransactionByDate, "-"); TBDTempM = strtok(NULL, "-"); TBDTempY = strtok(NULL, "-");
        TBDTempD = TrimWhiteSpaces(TBDTempD); TBDTempM = TrimWhiteSpaces(TBDTempM); TBDTempY = TrimWhiteSpaces(TBDTempY);
        Date = atoi(TBDTempD); Month = atoi(TBDTempM); Year = atoi(TBDTempY);

        while (Date < (long long unsigned)ManageTime.tm_mday || Date > (long long unsigned)ManageTime.tm_mday || Month < ((long long unsigned)ManageTime.tm_mon + 1) || Month > ((long long unsigned)ManageTime.tm_mon + 1) || Year < (1900 + (long long unsigned)ManageTime.tm_year) || Year > (1900 + (long long unsigned)ManageTime.tm_year)) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: Recorded transaction MUST BE ONLY for today's transaction, and neither for YESTERDAY nor"ANSI_COLOR_RESET);
            puts(ANSI_COLOR_LIGHTRED"\t         TOMORROW! Thus, your current pre-recorded transaction MUST BE in the date of TODAY, it's:"ANSI_COLOR_RESET);
            printf(ANSI_COLOR_LIGHTRED ANSI_STYLE_BOLD"\t             > %d-%d-%d (%s).\n\n"ANSI_COLOR_RESET, ManageTime.tm_mday, (ManageTime.tm_mon + 1), (1900 + ManageTime.tm_year), DaysOfWeek[ManageTime.tm_wday]);

            printf("      " BRIGHTGREEN154"> Transaction by Date:\t\t%s\n\t"ANSI_COLOR_RESET "Recorded Transaction Type:\t\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Transaction by Date."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your date of birth profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The transaction by date of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of transaction by date format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);

            printf("\nTransaction by Date: ");
            fgets(InputTransactionByDate, BUFSIZE07, stdin);

            if (strlen(InputTransactionByDate) < 2) { EmptyTBDInput = true; }
            else {
                strcpy(InputTBDTemp, InputTransactionByDate);
                InputTBDTemp[strlen(InputTBDTemp) - 1] = '\0';
                DashesOccurences = FindOccurences(InputTBDTemp, '-');
                if (DashesOccurences == 2) {
                    TempTBDTempD = strtok(InputTBDTemp, "-"); TempTBDTempM = strtok(NULL, "-"); TempTBDTempY = strtok(NULL, "-");
                    TempDate = atoi(TempTBDTempD); TempMonth = atoi(TempTBDTempM); TempYear = atoi(TempTBDTempY);
                } EmptyTBDInput = false;
            }

            while (EmptyTBDInput || DashesOccurences != 2 || (((TempYear % 4) == 0 && (TempMonth == 2)) && TempDate > 29) || (((TempYear % 4) != 0 && (TempMonth == 2)) && TempDate > 28) || (TempDate < 1 || TempDate > 31) || (TempMonth < 1 || TempMonth > 12) || (TempYear < 1)) {
                ClearScreen();
                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);

                puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your transaction by date as what the pre-requisites requested for!\n"ANSI_COLOR_RESET);
                printf("      " BRIGHTGREEN154"> Transaction by Date:\t\t%s\n\t"ANSI_COLOR_RESET "Recorded Transaction Type:\t\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
                puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Transaction by Date."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your date of birth profile account.");
                puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The transaction by date of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of transaction by date format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);

                printf("\nTransaction by Date: ");
                fgets(InputTransactionByDate, BUFSIZE07, stdin);

                if (strlen(InputTransactionByDate) < 2) { EmptyTBDInput = true; }
                else {
                    strcpy(InputTBDTemp, InputTransactionByDate);
                    InputTBDTemp[strlen(InputTBDTemp) - 1] = '\0';
                    DashesOccurences = FindOccurences(InputTBDTemp, '-');
                    if (DashesOccurences == 2) {
                        TempTBDTempD = strtok(InputTBDTemp, "-"); TempTBDTempM = strtok(NULL, "-"); TempTBDTempY = strtok(NULL, "-");
                        TempDate = atoi(TempTBDTempD); TempMonth = atoi(TempTBDTempM); TempYear = atoi(TempTBDTempY);
                    } EmptyTBDInput = false;
                }
            }

            InputTransactionByDate[strlen(InputTransactionByDate) - 1] = '\0';
            TBD = true;
            TBDTempD = strtok(InputTransactionByDate, "-"); TBDTempM = strtok(NULL, "-"); TBDTempY = strtok(NULL, "-");
            TBDTempD = TrimWhiteSpaces(TBDTempD); TBDTempM = TrimWhiteSpaces(TBDTempM); TBDTempY = TrimWhiteSpaces(TBDTempY);
            Date = atoi(TBDTempD); Month = atoi(TBDTempM); Year = atoi(TBDTempY);
        }

        Year -= Month < 3;
        Day = (Year + (Year / 4) - (Year / 100) + (Year / 400) + TimeCounterNumeric[Month - 1] + Date) % 7;
        if (Date >= 11 && Date < 21)      { strcpy(NumericalPattern, "th"); }
        else {
            if (strlen(TBDTempD) < 2) {
                if      (TBDTempD[0] == '1') { strcpy(NumericalPattern, "st"); }
                else if (TBDTempD[0] == '2') { strcpy(NumericalPattern, "nd"); }
                else if (TBDTempD[0] == '3') { strcpy(NumericalPattern, "rd"); }
                else                         { strcpy(NumericalPattern, "th"); }
            } else {
                if      (TBDTempD[1] == '1') { strcpy(NumericalPattern, "st"); }
                else if (TBDTempD[1] == '2') { strcpy(NumericalPattern, "nd"); }
                else if (TBDTempD[1] == '3') { strcpy(NumericalPattern, "rd"); }
                else                         { strcpy(NumericalPattern, "th"); }
            }
        }

        strcpy(MTRInputs[GlobalRegisteredMTR].TransactionDate, DaysOfWeek[Day]);
        strcat(MTRInputs[GlobalRegisteredMTR].TransactionDate, ", ");
        strcat(MTRInputs[GlobalRegisteredMTR].TransactionDate, TBDTempD);
        strcat(MTRInputs[GlobalRegisteredMTR].TransactionDate, NumericalPattern);
        strcat(MTRInputs[GlobalRegisteredMTR].TransactionDate, " of ");
        strcat(MTRInputs[GlobalRegisteredMTR].TransactionDate, MonthsOfYear[Month - 1]);
        strcat(MTRInputs[GlobalRegisteredMTR].TransactionDate, " ");
        strcat(MTRInputs[GlobalRegisteredMTR].TransactionDate, TBDTempY);

        for (int i = 0; i < 7; i++)  { DaysOfWeek[i][0] = 0; }
        for (int j = 0; j < 12; j++) { MonthsOfYear[j][0] = 0; }
        NumericalPattern[0] = 0;
        F1_MoneytoryTransactionsRegister(F1Selected);

    } else if (F1Selected == 1) {
        ClearScreen();
        char InputRecordedTransactionType[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);

        if (IOE) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already asserted your recorded transaction type as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses);
            printf("\tTransaction by Date:\t\t%s\n      " BRIGHTGREEN155"> Recorded Transaction Type:\t%s\n\t"ANSI_COLOR_RESET "Nominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Recorded Transaction Type."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your recorded transactiom type again.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: Choose ONE either 'I' for Incomes, or 'E' for Expenses for your recorded\n\t      transaction type history!"ANSI_COLOR_RESET);
        } else {
            printf("\tTransaction by Date:\t\t%s\n      " BRIGHTGREEN155"> Recorded Transaction Type:\t%s\n\t"ANSI_COLOR_RESET "Nominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Recorded Transaction Type."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your recorded transactiom type again.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: Choose ONE either 'I' for Incomes, or 'E' for Expenses for your recorded\n\t      transaction type history!"ANSI_COLOR_RESET);
        }

        printf("\nRecorded Transaction Type: ");
        fgets(InputRecordedTransactionType, BUFSIZE07, stdin);
        strcpy(InputRecordedTransactionType, StringUppercase(InputRecordedTransactionType));
        InputRecordedTransactionType[strlen(InputRecordedTransactionType) - 1] = '\0';

        while (strcmp(StringUppercase(InputRecordedTransactionType), "I") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "IN") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "INC") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "INCO") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "INCOM") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "INCOME") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "INCOMES") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "E") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "EX") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "EXP") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "EXPE") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "EXPEN") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "EXPENS") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "EXPENSE") != 0 && \
               strcmp(StringUppercase(InputRecordedTransactionType), "EXPENSES") != 0) {
                    
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);
            
            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must assert your recorded transaction type as either 'I' or 'E' \n\t         for representing either your transaction type is an Income or an Expense!\n"ANSI_COLOR_RESET);
            printf("\tTransaction by Date:\t\t%s\n      " BRIGHTGREEN155"> Recorded Transaction Type:\t%s\n\t"ANSI_COLOR_RESET "Nominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Recorded Transaction Type."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your recorded transaction type again.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: Choose ONE either 'I' for Incomes, or 'E' for Expenses for your recorded\n\t      transaction type history!"ANSI_COLOR_RESET);

            printf("\nRecorded Transaction Type: ");
            fgets(InputRecordedTransactionType, BUFSIZE07, stdin);
            strcpy(InputRecordedTransactionType, StringUppercase(InputRecordedTransactionType));
            InputRecordedTransactionType[strlen(InputRecordedTransactionType) - 1] = '\0';
        }
        
        IOE = true;
        if (strcmp(StringUppercase(InputRecordedTransactionType), "I") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "IN") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "INC") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "INCO") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "INCOM") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "INCOME") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "INCOMES") == 0) {
                InputRecordedTransactionType[0] = 0;
                strncpy(InputRecordedTransactionType, "Income(s)", BUFSIZE07);
            }

        else if (strcmp(StringUppercase(InputRecordedTransactionType), "E") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "EX") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "EXP") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "EXPE") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "EXPEN") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "EXPENS") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "EXPENSE") == 0 || \
            strcmp(StringUppercase(InputRecordedTransactionType), "EXPENSES") == 0) {
                InputRecordedTransactionType[0] = 0;
                strncpy(InputRecordedTransactionType, "Expense(s)", BUFSIZE07);
            }

        strcpy(MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, InputRecordedTransactionType);
        InputRecordedTransactionType[0] = 0;
        F1_MoneytoryTransactionsRegister(F1Selected);

    } else if (F1Selected == 2) {
        ClearScreen();
        char FinalInputNominalFee[BUFSIZE07];
        signed long long int InputNominalFee;

        fflush(stdin);
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);

        if (TSM) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your nominal fee as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney);
            printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n      " BRIGHTGREEN156"> Nominal Fee (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Transaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Nominal Fee"ANSI_COLOR_RESET "\n\tPlease proceed to fill in the nominal fee of your current pre-recorded transaction.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The nominal fee of yours can be more than 4 digits of INTEGERS ONLY \n\t      (starting from Rp1.000,00, up to your saved budget balance)."ANSI_COLOR_RESET);
        } else {
            printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n      " BRIGHTGREEN156"> Nominal Fee (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Transaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Nominal Fee"ANSI_COLOR_RESET "\n\tPlease proceed to fill in the nominal fee of your current pre-recorded transaction.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The nominal fee of yours can be more than 4 digits of INTEGERS ONLY \n\t      (starting from Rp1.000,00, up to your saved budget balance)."ANSI_COLOR_RESET);
        }
        
        fflush(stdin);
        printf("\nNominal Fee (in Rp.): Rp");
        scanf("%lld", &InputNominalFee);

        while (InputNominalFee < 1000) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your nominal fee at least for 4 digits (min. Rp1.000,00+)!\n"ANSI_COLOR_RESET);
            printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n      " BRIGHTGREEN156"> Nominal Fee (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Transaction Category:\t\t%s\n\tTransaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Nominal Fee"ANSI_COLOR_RESET "\n\tPlease proceed to fill in the nominal fee of your current pre-recorded transaction.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The nominal fee of yours can be more than 4 digits of INTEGERS ONLY \n\t      (starting from Rp1.000,00, up to your saved budget balance)."ANSI_COLOR_RESET);

            printf("\nNominal Fee (in Rp.): Rp");
            scanf("%lld", &InputNominalFee);
        }
        
        TSM = true;
        snprintf(FinalInputNominalFee, BUFSIZE07, "%lld", InputNominalFee);
        strcpy(MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, "Rp");
        strcat(MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, FinalInputNominalFee);
        strcat(MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, ",00");
        InputNominalFee = 0;
        F1_MoneytoryTransactionsRegister(F1Selected);

    } else if (F1Selected == 3) {
        FUC = true;
        F1_FUC01_FinancialUsesCategoryUI(0);
        F1_MoneytoryTransactionsRegister(F1Selected);
        
    } else if (F1Selected == 4) {
        ClearScreen();
        char InputTransactionDescription[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);

        if (TD) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your nominal fee as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n      " BRIGHTBLUE158"> Transaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Transaction Description."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the description of your current pre-recorded transaction.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The description of your current pre-recorded transaction must not be more than 100 characters! \n\t(leave the input blank if no description providen)."ANSI_COLOR_RESET);
        } else {
            printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n      " BRIGHTBLUE158"> Transaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Transaction Description."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the description of your current pre-recorded transaction.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The description of your current pre-recorded transaction must not be more than 100 characters! \n\t(leave the input blank if no description providen)."ANSI_COLOR_RESET);
        }
        
        printf("\nTransaction Description:\n      > ");
        fgets(InputTransactionDescription, BUFSIZE07, stdin);

        while (strlen(InputTransactionDescription) > 101) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature01, UserName);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your current pre-recorded transaction's description accordingly (max. 100 characters)!\n"ANSI_COLOR_RESET);
            printf("\tTransaction by Date:\t\t%s\n\tRecorded Transaction Type:\t%s\n\tNominal Fee (in Rp.):\t\t%s\n\tTransaction Category:\t\t%s\n      " BRIGHTBLUE158"> Transaction Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate, MTRInputs[GlobalRegisteredMTR].IncomeOrExpenses, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney, MTRInputs[GlobalRegisteredMTR].FinancialUsesCategory, MTRInputs[GlobalRegisteredMTR].TransactionDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Transaction Description."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the description of your current pre-recorded transaction.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The description of your current pre-recorded transaction must not be more than 100 characters! \n\t(leave the input blank if no description providen)."ANSI_COLOR_RESET);

            printf("\nTransaction Description:\n      > ");
            fgets(InputTransactionDescription, BUFSIZE07, stdin);
        }
        
        InputTransactionDescription[strlen(InputTransactionDescription) - 1] = '\0';
        TD = true;
        (strlen(InputTransactionDescription) > 0) ? \
            strcpy(MTRInputs[GlobalRegisteredMTR].TransactionDescription, InputTransactionDescription) : \
            strcpy(MTRInputs[GlobalRegisteredMTR].TransactionDescription, "(no description provided)");
        InputTransactionDescription[0] = 0;
        F1_MoneytoryTransactionsRegister(F1Selected);
    
    } else if (F1Selected == 5) {
        MainMenuApplicationFeatures(MMAFSelected);
    }
}

void F2_MoneytoryGroupingPerCategory(int F2Selected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    InfoMessageBox_OK("(Info) Moneytory Grouping per Category: Unavailable Feature; (not ready yet)", "We're deeply sorry, but this feature may not be working until further notices on my GitHub account (@EintsWaveX)...\n\nBut don't worry, just stay tuned and you may proceed to use the FOURTH feature and look up by the filter keyword of the type of your Moneytory Category you'd like to find about!\n\nYou may proceed here to get knowing that there're\n\n\t> 60 DIFFERENT TYPES of Financial Category,\n\nand we divide each categories by ten per pages (meaning there're 6 pages in total).\n\nTrue fact, this feature is used for both FIRST feature and THIRD feature, it's just that the grouping automatically here doesn't being implemented yet...\n\nAlright then, you may just press the [ENTER] button key on your keyboard to go back to the main menu of this application... .");
    F2_FUC01_FinancialUsesCategoryUI(0);
    MainMenuApplicationFeatures(MMAFSelected);
}

void F3_BudgetCreationAndMonitoring(int F3Selected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    FILE *FDestination, *FSourceTemp, *FDestinationTemp;
    time_t Time = time(NULL);
    struct tm ManageTime = *localtime(&Time);
    char F3LoggedInFileName[BUFSIZE07], TempF3LoggedInFileName[BUFSIZE07];

    int BufLen, Ptr = 0, KeyTracker = 0;
    char FDBuffer[BUFSIZE16], DeleteTempDestinationTxtFile[128], TxtFileName[128], TempCountRegisteredBudgetCreations[BUFSIZE07];
    char *SourceKeyStringValue, *SelectedKeyString, *CountRegisteredBudgetCreations;
    char *SourceKeyStringValues[BUFSIZE07];

    char RegBCAMInsider[BUFSIZE07], BCAM[BUFSIZE07], MessageID23[BUFSIZE10], MessageID24[BUFSIZE10];
    char NextBudgetCreationOn[BUFSIZE07]; // , KeepTrackIncomes[BUFSIZE07], KeepTrackExpenses[BUFSIZE07];
    char MonthlyOrYearly[BUFSIZE07], MonthlyFinancialCreationCategory[BUFSIZE07], MonthlyLimitBudgetCreation[BUFSIZE07], MonthlyBudgetTargeting[BUFSIZE07], MonthlyBudgetCreationDescription[BUFSIZE07];
    char UpdateLocalTime[BUFSIZE07], LocalTime[BUFSIZE07], BCAMMadeTime[BUFSIZE07], MadeTime[BUFSIZE07];

    int AvailableOptions = 6, SubmitOrContinue, KeepContinue;
    bool Selecting = true, Updated = false, FirstRun = true, FirstF3BCAMUpgrade = false;
    // bool ConfirmOrBackMMAF = false;
    char AKDC;

    char TempCheckForTheNextBudgetCreationDate[BUFSIZE07];
    char *CheckForTheNextBudgetCreationDate, *CheckForTheNextBudgetCreationTime, *DisplayCFTNBC;
    char TempDisplayCFTNBC[BUFSIZE07];
    int  CFTNBC_Date, CFTNBC_Month, CFTNBC_Year;
    int  CFTNBC_Second, CFTNBC_Minute, CFTNBC_Hour;

    char MessageID13[BUFSIZE10];
    char MonthsOfYear[12][BUFSIZE07] = {"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};
    int  DateOfMonths[12]            = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int  DateOfMonths_LEAP[12]       = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    snprintf(F3LoggedInFileName, BUFSIZE07, "%s-F3-BCAM-%s-%d.txt", UserName, MonthsOfYear[ManageTime.tm_mon], (1900 + ManageTime.tm_year));
    snprintf(TempF3LoggedInFileName, BUFSIZE07, "TEMP-%s-F3-BCAM-%s-%d.txt", UserName, MonthsOfYear[ManageTime.tm_mon], (1900 + ManageTime.tm_year));
    // strncpy(UserBudgetCreationTxtFile, UserName, BUFSIZE07); strcat(UserBudgetCreationTxtFile, "-F3-BCAM-DECEMBER-2023.txt");
    // strtok_r(ReadAndPrintLine(UserBudgetCreationTxtFile, 2 + (14 * SignedInAccountNo)), ":", &BalanceBudget);
    // BalanceBudget = TrimWhiteSpaces(BalanceBudget);
    strncpy(TxtFileName, F3LoggedInFileName, BUFSIZE07); strcat(TxtFileName, " > Recorded Monitoring Budget Creation");

    if (ManageTime.tm_mday >= 21) {
        ClearScreen();

        WarningMessageBox_CANCELTRYCONTINUE("(Warning): Budget Creation and Monitoring: Creating Monthly Budget at The End of The Month", "You're going to make a monthly budget limit, but there's only few days up ahead before getting into the next month, and since in a new month IS THE SAME AS a new monthly limit budget, so then we need you to fill in the monthly budget every EARLY DATE of each month, so it will be refreshed every next 30 DAYS.\n\nSee right on your terminal screen right after you click any of the buttons of the pop-up notification here to get more details!");
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

        printf(BRIGHTRED216"\tWarning: It's the date at %02d on current month, %s. You're going to make a monthly budget\n\t         limit, but there's only few days up ahead before getting into the next month, and since in\n\t         a new month IS THE SAME AS a new monthly limit budget, so then we need you to fill in the\n\t         monthly budget every EARLY DATE of each month, so it will be refreshed every next 30\n\t         DAYS... .\n"ANSI_COLOR_RESET, ManageTime.tm_mday, MonthsOfYear[ManageTime.tm_mon]);
        printf("\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Ignore"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Continue"ANSI_COLOR_RESET" to fulfill in the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_CYAN"Wait"ANSI_COLOR_RESET " for next month came and at \n\tthe early date making the monthly budget creation?\n\n");
        
        snprintf(MessageID23, BUFSIZE10, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);
        snprintf(MessageID24, BUFSIZE10, BRIGHTRED216"\tWarning: It's the date at %02d on current month, %s. You're going to make a monthly budget\n\t         limit, but there's only few days up ahead before getting into the next month, and since in\n\t         a new month IS THE SAME AS a new monthly limit budget, so then we need you to fill in the\n\t         monthly budget every EARLY DATE of each month, so it will be refreshed every next 30\n\t         DAYS... ."ANSI_COLOR_RESET, ManageTime.tm_mday, MonthsOfYear[ManageTime.tm_mon]);
        MessagesShown_ArrowKeyChoiceDialog[24] = MessageID23;
        MessagesShown_ArrowKeyChoiceDialog[25] = MessageID24;
        MessagesShown_ArrowKeyChoiceDialog[26] = "\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Ignore"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Continue"ANSI_COLOR_RESET" to fulfill in the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_CYAN"Wait"ANSI_COLOR_RESET " for next month came and at \n\tthe early date making the monthly budget creation?\n";
        KeepContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 24, 27);

        if (KeepContinue) { ClearScreen(); NULL; }
        else {
            MainMenuApplicationFeatures(MMAFSelected);
        }
    }

    if (access(F3LoggedInFileName, F_OK) != 0 && !FlagF3BCAM) { GlobalRegisteredBCAM = 0; }
    else if (access(F3LoggedInFileName, F_OK) == 0 && !FlagF3BCAM) {
        FDestination     = fopen(F3LoggedInFileName, "r");
        FDestinationTemp = fopen("TempDestination.txt", "w");

        while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
            BufLen = strlen(FDBuffer);
            for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
            fputs(FDBuffer, FDestinationTemp);
        } fclose(FDestination); fclose(FDestinationTemp);

        strncpy(TempCheckForTheNextBudgetCreationDate, ReadAndPrintLine("TempDestination.txt", 13), BUFSIZE07);
        TempCheckForTheNextBudgetCreationDate[strlen(TempCheckForTheNextBudgetCreationDate) - 1] = '\0';
        strtok_r(TempCheckForTheNextBudgetCreationDate, ":", &CheckForTheNextBudgetCreationDate); CheckForTheNextBudgetCreationDate = TrimWhiteSpaces(CheckForTheNextBudgetCreationDate);
        strtok_r(CheckForTheNextBudgetCreationDate, " ", &CheckForTheNextBudgetCreationTime); CheckForTheNextBudgetCreationDate = TrimWhiteSpaces(CheckForTheNextBudgetCreationDate);
        
        strncpy(TempDisplayCFTNBC, ReadAndPrintLine("TempDestination.txt", 22), BUFSIZE07);
        TempDisplayCFTNBC[strlen(TempDisplayCFTNBC) - 1] = '\0';
        strtok_r(TempDisplayCFTNBC, ":", &DisplayCFTNBC); DisplayCFTNBC = TrimWhiteSpaces(DisplayCFTNBC);
        
        CFTNBC_Year   = atoi(TrimWhiteSpaces(strtok(CheckForTheNextBudgetCreationDate, "-")));
        CFTNBC_Month  = atoi(strtok(NULL, "-"));
        CFTNBC_Date   = atoi(strtok(NULL, "-"));
        CFTNBC_Hour   = atoi(TrimWhiteSpaces(strtok(CheckForTheNextBudgetCreationTime, ":")));
        CFTNBC_Minute = atoi(strtok(NULL, ":"));
        CFTNBC_Second = atoi(strtok(NULL, ":"));
        // CFTNBC_Year   = 2023; // atoi(TrimWhiteSpaces(strtok(CheckForTheNextBudgetCreationDate, "-")));
        // CFTNBC_Month  = 12; // atoi(strtok(NULL, "-"));
        // CFTNBC_Date   = 30; // atoi(strtok(NULL, "-"));
        // CFTNBC_Second = 30; // atoi(TrimWhiteSpaces(strtok(CheckForTheNextBudgetCreationTime, ":")));
        // CFTNBC_Minute = 40; // atoi(strtok(NULL, ":"));
        // CFTNBC_Hour   = 10; // atoi(strtok(NULL, ":"));
        // printf("%d-%d-%04d\n", CFTNBC_Date, CFTNBC_Month, CFTNBC_Year);
        // printf("%02d:%02d:%02d\n", CFTNBC_Second, CFTNBC_Minute, CFTNBC_Hour);
        // getchar();

        // (((ManageTime.tm_mon + 1) != 12) ? (1900 + ManageTime.tm_year) : ((1900 + ManageTime.tm_year) + 1)), (((ManageTime.tm_mon + 1) != 12) ? ((ManageTime.tm_mon + 1) + 1) : 1)
        if ((ManageTime.tm_mday == CFTNBC_Date) && ((((ManageTime.tm_mon + 1) != 12) ? ((ManageTime.tm_mon + 1) + 1) : 1) == CFTNBC_Month) && (ManageTime.tm_year == CFTNBC_Year)) {
            if ((ManageTime.tm_hour == CFTNBC_Hour) && (ManageTime.tm_min == CFTNBC_Minute)) {
                if (ManageTime.tm_sec >= CFTNBC_Second) {
                    NULL;
                }
            } else if ((ManageTime.tm_hour >= CFTNBC_Hour) && (ManageTime.tm_min > CFTNBC_Minute)) {
                NULL;
            }

        } else if ((ManageTime.tm_year > CFTNBC_Year) || ((ManageTime.tm_year == CFTNBC_Year) && ((((ManageTime.tm_mon + 1) != 12) ? ((ManageTime.tm_mon + 1) + 1) : 1) > CFTNBC_Month)) || \
                  ((ManageTime.tm_year == CFTNBC_Year) && ((((ManageTime.tm_mon + 1) != 12) ? ((ManageTime.tm_mon + 1) + 1) : 1) == CFTNBC_Month) && (ManageTime.tm_mday > CFTNBC_Date))) {   
                        NULL;

        } else {
            InfoMessageBox_OK("(Info) Budget Creation and Monitoring: Unavailable Budget Creation Time Period", \
                              "We're sorry to let you know, but as what the message says before while you're going to submit your monthly budget creation, you CAN'T CREATE any monthly budget at the moment, until the next 30 DAYS right after you submitted the monthly budget before.\n\nSee right on your terminal for further information, and remember the dates and times before you're going to submit another monthly budget creation!");

            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);
            printf(BRIGHTPURPLE218 ANSI_STYLE_BOLD"\tImportant Notice: It's not the time to create another monthly and/or yearly budget monitoring!\n"ANSI_COLOR_RESET);
            printf(BRIGHTPURPLE218 ANSI_STYLE_BOLD"\t                  Please kindly wait until the date of your budget creation and monitoring will\n"ANSI_COLOR_RESET);
            printf(BRIGHTPURPLE218 ANSI_STYLE_BOLD"\t                  be AVAILABLE again on the following mentioned date below... .\n\n"ANSI_COLOR_RESET);

            printf(BRIGHTBLUE159   ANSI_STYLE_BOLD"\tThank you for your patience and understanding... .\n");
            printf(BRIGHTGREEN156  ANSI_STYLE_BOLD"\t>>> The next budget creation date is AVAILABLE on: " ANSI_STYLE_UNDERLINE"%s,"ANSI_COLOR_RESET, DisplayCFTNBC);
            printf(BRIGHTPINK219   ANSI_STYLE_BOLD"\n\t    with the exact time at:                        " ANSI_STYLE_UNDERLINE"%02d:%02d:%02d.", CFTNBC_Hour, CFTNBC_Minute, CFTNBC_Second);

            puts("\n");
            printf(ANSI_COLOR_MAGENTA ANSI_STYLE_ITALIC"\t[ENTER] Head back to main menu of the application... "ANSI_COLOR_RESET);
            getchar(); MainMenuApplicationFeatures(MMAFSelected);
        }

        strtok_r(TxtFileName, ">", &SelectedKeyString);
        SelectedKeyString = TrimWhiteSpaces(SelectedKeyString);
        SourceKeyStringValue = strtok(SelectedKeyString, ",");
        KeyTracker++;

        while (SourceKeyStringValue != NULL) {
            SourceKeyStringValues[Ptr] = SourceKeyStringValue;
            SourceKeyStringValues[Ptr] = TrimWhiteSpaces(SourceKeyStringValues[Ptr]);
            SourceKeyStringValue = strtok(NULL, ",");
            Ptr++; KeyTracker++;
        } // SourceTextFileName = TrimWhiteSpaces(TxtFileName);
        
        strcpy(TempCountRegisteredBudgetCreations, ReadAndPrintLine("TempDestination.txt", 9));

        strcpy(DeleteTempDestinationTxtFile, "del ");
        strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
        system(DeleteTempDestinationTxtFile);

        TempCountRegisteredBudgetCreations[strlen(TempCountRegisteredBudgetCreations) - 1] = '\0';
        strtok_r(TempCountRegisteredBudgetCreations, ":", &CountRegisteredBudgetCreations);
        
        CountRegisteredBudgetCreations = TrimWhiteSpaces(CountRegisteredBudgetCreations);
        CountRegisteredBudgetCreations = strtok(CountRegisteredBudgetCreations, " ");
        GlobalRegisteredBCAM = atoi(CountRegisteredBudgetCreations);
        FlagF3BCAM = true;
    }

    if ((MOR && BCC && BCL && BCT && BCD) && !FirstF3BCAMUpgrade) {
        InfoMessageBox_OK("(Info) Budget Creation and Monitoring: Completing The Pre-requisites and Submission", \
                          "You've completed all the pre-requisites for registering your budget creation and monitoring for today's month, and for the fact that when you create the budget for the current month, it means that you CAN'T MAKE ANOTHER ONE until the NEXT 30 DAYS starting after you submitted the budget creation onto the file system.\n\nAlso remember, once you've submitted the pre-requisites down below, you CAN'T EDIT or DELETE ANYMORE since it will be saved onto the file system and will be used for keep tracking all of your income(s) and/or expense(s) by the Moneytory Transaction Registration feature, and also be displayed using the Histogram Graph for better lookup and maintaining your income(s) and/or expense(s) for the future!\n\nThis message may appear everytime you make changes, so make sure that whatever you're filling in the pre-requisites ARE INDEED on what actual budget you wanted to make for the whole month until the very next 30 DAYS coming ahead!\n\nPROGRESS: Keep moving UPWARD or DOWNWARD until you see a complete different UI for SUBMITTING your MONTHLY Budget Creation and Moneytory!");
        AvailableOptions++; FirstF3BCAMUpgrade = true;
    }

    while (Selecting) {
        if (!FirstRun) {
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);
            printf(BRIGHTRED209 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"\tImportant Notice: YEARLY Budget Creation Type is not supported yet... .\n\n"ANSI_COLOR_RESET);

            if ((F3Selected + 1) > 0 && (F3Selected + 1) <= 6 && (AvailableOptions == 6)) {
                if ((F3Selected + 1) == 1) {
                    printf("      " BRIGHTGREEN154"> Monthly or Yearly Budget Creation Type:\t%s\n\t"ANSI_COLOR_RESET "Financial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 2) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n      " BRIGHTGREEN155"> Financial Budget Creation Category:\t%s\n\t"ANSI_COLOR_RESET "Expenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 3) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n      " BRIGHTGREEN156"> Expenses Limit at (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 4) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Budget Usage Target (at month):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 5) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n      " BRIGHTBLUE158"> Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 6) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET BRIGHTPURPLE213 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"      > (Back to the Main Menu)"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                }

                printf("\n\n\n\n\n\t%s", AppGuideOnUsageUDRL);
            
            } else if ((F3Selected + 1) > 0 && (F3Selected + 1) <= 7 && (AvailableOptions == 7)) {
                if ((F3Selected + 1) == 1) {
                    printf("      " BRIGHTGREEN154"> Monthly or Yearly Budget Creation Type:\t%s\n\t"ANSI_COLOR_RESET "Financial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 2) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n      " BRIGHTGREEN155"> Financial Budget Creation Category:\t%s\n\t"ANSI_COLOR_RESET "Expenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 3) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n      " BRIGHTGREEN156"> Expenses Limit at (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 4) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Budget Usage Target (at month):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 5) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n      " BRIGHTBLUE158"> Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 6) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET BRIGHTPURPLE213 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"      > (Back to the Main Menu)"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                }

                printf("\n\n\n\n\n\t%s", AppGuideOnUsageUDRL);
                
                if ((F3Selected + 1) > 6) {
                    ClearScreen();
                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

                    printf("\tInfo: You've finished making your current monthly budget monitoring and creation (for the future), and \n\t      now you're ready to submit your monthly budget monitoring and creation over the file system.\n");
                    printf("\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour current pre-recorded transaction history?\n\n");
                    
                    snprintf(MessageID13, BUFSIZE10, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);
                    MessagesShown_ArrowKeyChoiceDialog[13] = MessageID13;
                    MessagesShown_ArrowKeyChoiceDialog[14] = "\tInfo: You've finished making your current monthly budget monitoring and creation (for the future), and \n\t      now you're ready to submit your monthly budget monitoring and creation over the file system.";
                    MessagesShown_ArrowKeyChoiceDialog[15] = "\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour current pre-recorded transaction history?\n";
                    SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 13, 16);

                    if (SubmitOrContinue) {
                        if (access(F3LoggedInFileName, F_OK) != 0 && !FlagF3BCAM) {
                            FSourceTemp = fopen(TempF3LoggedInFileName, "w");

                            strcpy(BCAM, "1");
                            snprintf(LocalTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                            strcpy(RegBCAMInsider, "Recorded Monitoring Budget Creation: "); strcat(RegBCAMInsider, BCAM); strcat(RegBCAMInsider, " budget(s) in total.\n");
                            strcpy(UpdateLocalTime, "PersonalFMSA | Last Updated: ");
                            strcat(UpdateLocalTime, LocalTime); strcat(UpdateLocalTime, "\n");
                            strcpy(BCAMMadeTime, "Budget Creation and Monitoring :: No. 1"); strcat(BCAMMadeTime, "\n");
                            strcat(BCAMMadeTime, "Created on: "); strcat(BCAMMadeTime, MadeTime); strcat(BCAMMadeTime, "\n");

                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                            fputs(ApplicationPresent, FSourceTemp);
                            fputs(ApplicationTitle, FSourceTemp);
                            fputs(ApplicationVersion, FSourceTemp); fputs("\n", FSourceTemp);
                            fputs(UpdateLocalTime, FSourceTemp);
                            fputs("Built-in Console Application [CLI-Win32], fundamentally C (100%)\n", FSourceTemp);
                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                            fputs(RegBCAMInsider, FSourceTemp);
                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                            fclose(FSourceTemp);

                        } else if (access(F3LoggedInFileName, F_OK) == 0 && FlagF3BCAM) {
                            FDestination     = fopen(F3LoggedInFileName, "r");
                            FDestinationTemp = fopen(TempF3LoggedInFileName, "w");

                            while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
                                BufLen = strlen(FDBuffer);
                                for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                                fputs(FDBuffer, FDestinationTemp);
                            } fclose(FDestination); fclose(FDestinationTemp);
                        }
                        
                        FSourceTemp = fopen(TempF3LoggedInFileName, "a+");

                        if (!FlagF3BCAM) { strcpy(BCAM, "1"); }
                        else if (FlagF3BCAM && GlobalRegisteredBCAM >= 1) { snprintf(BCAM, BUFSIZE07, "%lld", (GlobalRegisteredBCAM + 1)); }
                        
                        snprintf(MadeTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                        strcpy(BCAMMadeTime, "Budget Creation and Monitoring :: No. "); strcat(BCAMMadeTime, BCAM); strcat(BCAMMadeTime, "\n");
                        strcat(BCAMMadeTime, "Created on:\t\t "); strcat(BCAMMadeTime, MadeTime); strcat(BCAMMadeTime, "\n");
                        snprintf(NextBudgetCreationOn, BUFSIZE07, "Next Budget Creation on: %04d-%02d-%02d %02d:%02d:%02d", (((ManageTime.tm_mon + 1) != 12) ? (1900 + ManageTime.tm_year) : ((1900 + ManageTime.tm_year) + 1)), (((ManageTime.tm_mon + 1) != 12) ? ((ManageTime.tm_mon + 1) + 1) : 1), (((1900 + ManageTime.tm_year) % 4 != 0) ? ((ManageTime.tm_mday + 30) - DateOfMonths[ManageTime.tm_mon]) : ((ManageTime.tm_mday + 30) - DateOfMonths_LEAP[ManageTime.tm_mon])), ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);

                        // MonthlyOrYearly[BUFSIZE07], FinancialUsesCategory[BUFSIZE07], TotalBudgetCreation[BUFSIZE07], LastingBudgetCreation[BUFSIZE07], BudgetCreationDescription[BUFSIZE07]
                        strcpy(MonthlyOrYearly, "Monthly or Yearly Budget Creation Type:\t");              strcat(MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly);                                   strcat(MonthlyOrYearly, "\n");
                        strcpy(MonthlyFinancialCreationCategory, "Financial Budget Creation Category:\t"); strcat(MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory); strcat(MonthlyFinancialCreationCategory, "\n");
                        strcpy(MonthlyLimitBudgetCreation, "Expenses Limit at (in Rp.):\t\t");             strcat(MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation);             strcat(MonthlyLimitBudgetCreation, "\n");
                        strcpy(MonthlyBudgetTargeting, "Budget Usage Target (at month):\t\t");             strcat(MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting);                     strcat(MonthlyBudgetTargeting, "\n");
                        strcpy(MonthlyBudgetCreationDescription, "Budget Creation Description:\n");        strcat(MonthlyBudgetCreationDescription, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription); strcat(MonthlyBudgetCreationDescription, "\n");

                        fputs(BCAMMadeTime, FSourceTemp);
                        fputs(NextBudgetCreationOn, FSourceTemp); fputs("\n\n", FSourceTemp);
                        fputs("Current Remaining Monthly Budget: ", FSourceTemp); fputs(BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, FSourceTemp); fputs("\n", FSourceTemp);
                        fputs("+++ Income(s):  Rp0,00", FSourceTemp); fputs("\n", FSourceTemp);
                        fputs("--- Expense(s): Rp0,00", FSourceTemp); fputs("\n\n", FSourceTemp);
                        fputs(MonthlyOrYearly, FSourceTemp); fputs(MonthlyFinancialCreationCategory, FSourceTemp); fputs(MonthlyLimitBudgetCreation, FSourceTemp); fputs(MonthlyBudgetTargeting, FSourceTemp); fputs(MonthlyBudgetCreationDescription, FSourceTemp);
                        fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                        fclose(FSourceTemp);

                        MOR = false; BCC = false; BCL = false; BCT = false; BCD = false;
                        strcpy(RegBCAMInsider, "Recorded Monitoring Budget Creation: "); strcat(RegBCAMInsider, BCAM); strcat(RegBCAMInsider, " budget(s) in total.");
                        OverWriteStringAtLine(TempF3LoggedInFileName, RegBCAMInsider, 0, 9);
                        EncryptTxtFile(TempF3LoggedInFileName, F3LoggedInFileName, EncryptionKey, true);
                        
                        GlobalRegisteredBCAM++; FlagF3BCAM = false;
                        MainMenuApplicationFeatures(MMAFSelected);

                    } else {
                        F3_BudgetCreationAndMonitoring(0);
                    }
                }
            }

        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);
            printf(BRIGHTRED209 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"\tImportant Notice: YEARLY Budget Creation Type is not supported yet... .\n\n"ANSI_COLOR_RESET);

            if ((F3Selected + 1) > 0 && (F3Selected + 1) <= 6 && (AvailableOptions == 6)) {
                if ((F3Selected + 1) == 1) {
                    printf("      " BRIGHTGREEN154"> Monthly or Yearly Budget Creation Type:\t%s\n\t"ANSI_COLOR_RESET "Financial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 2) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n      " BRIGHTGREEN155"> Financial Budget Creation Category:\t%s\n\t"ANSI_COLOR_RESET "Expenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 3) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n      " BRIGHTGREEN156"> Expenses Limit at (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 4) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Budget Usage Target (at month):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 5) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n      " BRIGHTBLUE158"> Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 6) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET BRIGHTPURPLE213 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"      > (Back to the Main Menu)"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                }
                
                printf("\n\n\n\n\n\t%s", AppGuideOnUsageUDRL);
            
            } else if ((F3Selected + 1) > 0 && (F3Selected + 1) <= 7 && (AvailableOptions == 7)) {
                if ((F3Selected + 1) == 1) {
                    printf("      " BRIGHTGREEN154"> Monthly or Yearly Budget Creation Type:\t%s\n\t"ANSI_COLOR_RESET "Financial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 2) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n      " BRIGHTGREEN155"> Financial Budget Creation Category:\t%s\n\t"ANSI_COLOR_RESET "Expenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 3) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n      " BRIGHTGREEN156"> Expenses Limit at (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 4) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Budget Usage Target (at month):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 5) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n      " BRIGHTBLUE158"> Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET "\t(Back to the Main Menu)", BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                } else if ((F3Selected + 1) == 6) {
                    printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n\n"ANSI_COLOR_RESET BRIGHTPURPLE213 ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"      > (Back to the Main Menu)"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                }

                printf("\n\n\n\n\n\t%s", AppGuideOnUsageUDRL);
                
                if ((F3Selected + 1) > 6) {
                    ClearScreen();
                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

                    printf("\tInfo: You've finished making your current monthly budget monitoring and creation (for the future), and \n\t      now you're ready to submit your monthly budget monitoring and creation over the file system.\n");
                    printf("\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour current pre-recorded transaction history?\n\n");
                    
                    snprintf(MessageID13, BUFSIZE10, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);
                    MessagesShown_ArrowKeyChoiceDialog[13] = MessageID13;
                    MessagesShown_ArrowKeyChoiceDialog[14] = "\tInfo: You've finished making your current monthly budget monitoring and creation (for the future), and \n\t      now you're ready to submit your monthly budget monitoring and creation over the file system.";
                    MessagesShown_ArrowKeyChoiceDialog[15] = "\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour current pre-recorded transaction history?\n";
                    SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 13, 16);

                    if (SubmitOrContinue) {
                        if (access(F3LoggedInFileName, F_OK) != 0 && !FlagF3BCAM) {
                            FSourceTemp = fopen(TempF3LoggedInFileName, "w");

                            strcpy(BCAM, "1");
                            snprintf(LocalTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                            strcpy(RegBCAMInsider, "Recorded Monitoring Budget Creation: "); strcat(RegBCAMInsider, BCAM); strcat(RegBCAMInsider, " budget(s) in total.\n");
                            strcpy(UpdateLocalTime, "PersonalFMSA | Last Updated: ");
                            strcat(UpdateLocalTime, LocalTime); strcat(UpdateLocalTime, "\n");
                            strcpy(BCAMMadeTime, "Budget Creation and Monitoring :: No. 1"); strcat(BCAMMadeTime, "\n");
                            strcat(BCAMMadeTime, "Created on: "); strcat(BCAMMadeTime, MadeTime); strcat(BCAMMadeTime, "\n");

                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                            fputs(ApplicationPresent, FSourceTemp);
                            fputs(ApplicationTitle, FSourceTemp);
                            fputs(ApplicationVersion, FSourceTemp); fputs("\n", FSourceTemp);
                            fputs(UpdateLocalTime, FSourceTemp);
                            fputs("Built-in Console Application [CLI-Win32], fundamentally C (100%)\n", FSourceTemp);
                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                            fputs(RegBCAMInsider, FSourceTemp);
                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                            fclose(FSourceTemp);

                        } else if (access(F3LoggedInFileName, F_OK) == 0 && FlagF3BCAM) {
                            FDestination     = fopen(F3LoggedInFileName, "r");
                            FDestinationTemp = fopen(TempF3LoggedInFileName, "w");

                            while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
                                BufLen = strlen(FDBuffer);
                                for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                                fputs(FDBuffer, FDestinationTemp);
                            } fclose(FDestination); fclose(FDestinationTemp);
                        }
                        
                        FSourceTemp = fopen(TempF3LoggedInFileName, "a+");

                        if (!FlagF3BCAM) { strcpy(BCAM, "1"); }
                        else if (FlagF3BCAM && GlobalRegisteredBCAM >= 1) { snprintf(BCAM, BUFSIZE07, "%lld", (GlobalRegisteredBCAM + 1)); }
                        
                        snprintf(MadeTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                        strcpy(BCAMMadeTime, "Budget Creation and Monitoring :: No. "); strcat(BCAMMadeTime, BCAM); strcat(BCAMMadeTime, "\n");
                        strcat(BCAMMadeTime, "Created on:\t\t "); strcat(BCAMMadeTime, MadeTime); strcat(BCAMMadeTime, "\n");
                        snprintf(NextBudgetCreationOn, BUFSIZE07, "Next Budget Creation on: %04d-%02d-%02d %02d:%02d:%02d", (((ManageTime.tm_mon + 1) != 12) ? (1900 + ManageTime.tm_year) : ((1900 + ManageTime.tm_year) + 1)), (((ManageTime.tm_mon + 1) != 12) ? ((ManageTime.tm_mon + 1) + 1) : 1), (((1900 + ManageTime.tm_year) % 4 != 0) ? ((ManageTime.tm_mday + 30) - DateOfMonths[ManageTime.tm_mon]) : ((ManageTime.tm_mday + 30) - DateOfMonths_LEAP[ManageTime.tm_mon])), ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);

                        // MonthlyOrYearly[BUFSIZE07], FinancialUsesCategory[BUFSIZE07], TotalBudgetCreation[BUFSIZE07], LastingBudgetCreation[BUFSIZE07], BudgetCreationDescription[BUFSIZE07]
                        strcpy(MonthlyOrYearly, "Monthly or Yearly Budget Creation Type:\t");              strcat(MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly);                                   strcat(MonthlyOrYearly, "\n");
                        strcpy(MonthlyFinancialCreationCategory, "Financial Budget Creation Category:\t"); strcat(MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory); strcat(MonthlyFinancialCreationCategory, "\n");
                        strcpy(MonthlyLimitBudgetCreation, "Expenses Limit at (in Rp.):\t\t");             strcat(MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation);             strcat(MonthlyLimitBudgetCreation, "\n");
                        strcpy(MonthlyBudgetTargeting, "Budget Usage Target (at month):\t\t");             strcat(MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting);                     strcat(MonthlyBudgetTargeting, "\n");
                        strcpy(MonthlyBudgetCreationDescription, "Budget Creation Description:\n");        strcat(MonthlyBudgetCreationDescription, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription); strcat(MonthlyBudgetCreationDescription, "\n");

                        fputs(BCAMMadeTime, FSourceTemp);
                        fputs(NextBudgetCreationOn, FSourceTemp); fputs("\n\n", FSourceTemp);
                        fputs("Current Remaining Monthly Budget: ", FSourceTemp); fputs(BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, FSourceTemp); fputs("\n", FSourceTemp);
                        fputs("+++ Income(s):  Rp0,00", FSourceTemp); fputs("\n", FSourceTemp);
                        fputs("--- Expense(s): Rp0,00", FSourceTemp); fputs("\n\n", FSourceTemp);
                        fputs(MonthlyOrYearly, FSourceTemp); fputs(MonthlyFinancialCreationCategory, FSourceTemp); fputs(MonthlyLimitBudgetCreation, FSourceTemp); fputs(MonthlyBudgetTargeting, FSourceTemp); fputs(MonthlyBudgetCreationDescription, FSourceTemp);
                        fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", FSourceTemp);
                        fclose(FSourceTemp);

                        MOR = false; BCC = false; BCL = false; BCT = false; BCD = false;
                        strcpy(RegBCAMInsider, "Recorded Monitoring Budget Creation: "); strcat(RegBCAMInsider, BCAM); strcat(RegBCAMInsider, " budget(s) in total.");
                        OverWriteStringAtLine(TempF3LoggedInFileName, RegBCAMInsider, 0, 9);
                        EncryptTxtFile(TempF3LoggedInFileName, F3LoggedInFileName, EncryptionKey, true);
                        
                        GlobalRegisteredBCAM++; FlagF3BCAM = false;
                        MainMenuApplicationFeatures(MMAFSelected);

                    } else {
                        F3_BudgetCreationAndMonitoring(0);
                    }
                }
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                if (F3Selected > 0 && F3Selected < AvailableOptions) {
                    --F3Selected; Updated = true;
                } else if (F3Selected <= 0) {
                    F3Selected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                if (F3Selected >= 0 && F3Selected < AvailableOptions - 1) {
                    ++F3Selected; Updated = true;
                } else if (F3Selected >= AvailableOptions - 1) {
                    F3Selected = 0; Updated = true;
                } break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    }

    if (F3Selected == 0) {
        ClearScreen();
        char InputMonthlyOrYearly[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

        if (MOR) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already asserted your monthly or yearly budget type as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly);
            printf("      " BRIGHTGREEN154"> Monthly or Yearly Budget Creation Type:\t%s\n\t"ANSI_COLOR_RESET "Financial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Monthly or Yearly Budget Creation Type."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your recorded budget creation as for monthly or yearly again.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: Choose ONE either 'M' for Monthly, or 'Y' for Yearly for your recorded\n\t      budget monitoring and creation type!"ANSI_COLOR_RESET);
        } else {
            printf("      " BRIGHTGREEN154"> Monthly or Yearly Budget Creation Type:\t%s\n\t"ANSI_COLOR_RESET "Financial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Monthly or Yearly Budget Creation Type."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your recorded budget creation as for monthly or yearly again.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: Choose ONE either 'M' for Monthly, or 'Y' for Yearly for your recorded\n\t      budget monitoring and creation type!"ANSI_COLOR_RESET);
        }

        printf("\nMonthly or Yearly Budget Creation Type: ");
        fgets(InputMonthlyOrYearly, BUFSIZE07, stdin);
        strcpy(InputMonthlyOrYearly, StringUppercase(InputMonthlyOrYearly));
        InputMonthlyOrYearly[strlen(InputMonthlyOrYearly) - 1] = '\0';

        while (strcmp(StringUppercase(InputMonthlyOrYearly), "M") != 0 && \
               strcmp(StringUppercase(InputMonthlyOrYearly), "MO") != 0 && \
               strcmp(StringUppercase(InputMonthlyOrYearly), "MON") != 0 && \
               strcmp(StringUppercase(InputMonthlyOrYearly), "MONT") != 0 && \
               strcmp(StringUppercase(InputMonthlyOrYearly), "MONTH") != 0 && \
               strcmp(StringUppercase(InputMonthlyOrYearly), "MONTHL") != 0 && \
               strcmp(StringUppercase(InputMonthlyOrYearly), "MONTHLY") != 0) {

            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);
            
            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must assert your recorded budget creation type as either 'M' or 'Y' \n\t         for representing either your budget monitoring type is Monthly or Yearly!"ANSI_COLOR_RESET);
            puts(ANSI_COLOR_LIGHTORANGE"\tNote:    YEARLY Budget Creation and Monitoring feature is not supported yet... .\n");
            printf("      " BRIGHTGREEN154"> Monthly or Yearly Budget Creation Type:\t%s\n\t"ANSI_COLOR_RESET "Financial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Monthly or Yearly Budget Creation Type."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your recorded budget creation as for monthly or yearly again.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: Choose ONE either 'M' for Monthly, or 'Y' for Yearly for your recorded\n\t      budget monitoring and creation type!"ANSI_COLOR_RESET);

            printf("\nMonthly or Yearly Budget Creation Type: ");
            fgets(InputMonthlyOrYearly, BUFSIZE07, stdin);
            strcpy(InputMonthlyOrYearly, StringUppercase(InputMonthlyOrYearly));
            InputMonthlyOrYearly[strlen(InputMonthlyOrYearly) - 1] = '\0';
        }
        
        MOR = true;
        if (strcmp(StringUppercase(InputMonthlyOrYearly), "M") == 0 || \
            strcmp(StringUppercase(InputMonthlyOrYearly), "MO") == 0 || \
            strcmp(StringUppercase(InputMonthlyOrYearly), "MON") == 0 || \
            strcmp(StringUppercase(InputMonthlyOrYearly), "MONT") == 0 || \
            strcmp(StringUppercase(InputMonthlyOrYearly), "MONTH") == 0 || \
            strcmp(StringUppercase(InputMonthlyOrYearly), "MONTHL") == 0 || \
            strcmp(StringUppercase(InputMonthlyOrYearly), "MONTHLY") == 0) {
                InputMonthlyOrYearly[0] = 0;
                strncpy(InputMonthlyOrYearly, "Monthly", BUFSIZE07);
            }

        strcpy(BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, InputMonthlyOrYearly);
        InputMonthlyOrYearly[0] = 0;
        F3_BudgetCreationAndMonitoring(F3Selected);
    
    } else if (F3Selected == 1) {
        BCC = true;
        F3_FUC01_FinancialUsesCategoryUI(0);
        F3_BudgetCreationAndMonitoring(F3Selected);
    
    } else if (F3Selected == 2) {
        ClearScreen();
        char FinalInputNominalFee[BUFSIZE07];
        signed long long int InputNominalFee;

        fflush(stdin);
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

        if (BCL) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your expenses limit as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TotalSpentMoney);
            printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n      " BRIGHTGREEN156"> Expenses Limit at (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Expenses Limit (in Rp.)."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the expenses limit of your current monthly budget creation.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The expenses limit of yours can be more than 4 digits of INTEGERS ONLY \n\t      (starting from Rp1.000,00, up to your saved budget balance)."ANSI_COLOR_RESET);
        } else {
            printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n      " BRIGHTGREEN156"> Expenses Limit at (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Expenses Limit (in Rp.)."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the expenses limit of your current monthly budget creation.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The expenses limit of yours can be more than 4 digits of INTEGERS ONLY \n\t      (starting from Rp1.000,00, up to your saved budget balance)."ANSI_COLOR_RESET);
        }
        
        fflush(stdin);
        printf("\nExpenses Limit at (in Rp.): Rp");
        scanf("%lld", &InputNominalFee);

        while (InputNominalFee < 1000) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your expenses limit at least for 4 digits (min. Rp1.000,00+)!\n"ANSI_COLOR_RESET);
            printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n      " BRIGHTGREEN156"> Expenses Limit at (in Rp.):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Usage Target (at month):\t\t%s\n\tBudget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Expenses Limit (in Rp.)."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the expenses limit of your current monthly budget creation.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The expenses limit of yours can be more than 4 digits of INTEGERS ONLY \n\t      (starting from Rp1.000,00, up to your saved budget balance)."ANSI_COLOR_RESET);

            printf("\nExpenses Limit at (in Rp.): Rp");
            scanf("%lld", &InputNominalFee);
        }
        
        BCL = true;
        snprintf(FinalInputNominalFee, BUFSIZE07, "%lld", InputNominalFee);
        strcpy(BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, "Rp");
        strcat(BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, FinalInputNominalFee);
        strcat(BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, ",00");
        InputNominalFee = 0;
        F3_BudgetCreationAndMonitoring(F3Selected);

    } else if (F3Selected == 3) {
        ClearScreen();
        char   InputMonthlyBudgetTargeting[BUFSIZE07], InputMBTTemp[BUFSIZE07], NumericalPattern[BUFSIZE07];
        char   *TempTBDTempD, *TempTBDTempM, *TempTBDTempY, *TBDTempD, *TBDTempM, *TBDTempY;
        char   DaysOfWeek[7][BUFSIZE07]      = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        char   MonthsOfYear[12][BUFSIZE07]   = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        int    TimeCounterNumeric[12]        = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        int    DashesOccurences = 0;
        bool   EmptyMBTInput = false;
        size_t TempDate, TempMonth, TempYear, Day, Date, Month, Year;

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

        if (BCT) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your monthly budget target as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, MTRInputs[GlobalRegisteredMTR].TransactionDate);
            printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Budget Usage Target (at month):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Budget Usage Target (at month)."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your monthly budget target on your current monthly budget creation.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The monthly budget target of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of monthly budget target format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);
        } else {
            printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Budget Usage Target (at month):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Budget Usage Target (at month)."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your monthly budget target on your current monthly budget creation.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The monthly budget target of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of monthly budget target format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);
        }

        printf("\nBudget Usage Target (at month): ");
        fgets(InputMonthlyBudgetTargeting, BUFSIZE07, stdin);

        if (strlen(InputMonthlyBudgetTargeting) < 2) { EmptyMBTInput = true; }
        else {
            strcpy(InputMBTTemp, InputMonthlyBudgetTargeting);
            InputMBTTemp[strlen(InputMBTTemp) - 1] = '\0';
            DashesOccurences = FindOccurences(InputMBTTemp, '-');
            if (DashesOccurences == 2) {
                TempTBDTempD = strtok(InputMBTTemp, "-"); TempTBDTempM = strtok(NULL, "-"); TempTBDTempY = strtok(NULL, "-");
                TempDate = atoi(TempTBDTempD); TempMonth = atoi(TempTBDTempM); TempYear = atoi(TempTBDTempY);
            } EmptyMBTInput = false;
        }

        while (EmptyMBTInput || DashesOccurences != 2 || (((TempYear % 4) == 0 && (TempMonth == 2)) && TempDate > 29) || (((TempYear % 4) != 0 && (TempMonth == 2)) && TempDate > 28) || (TempDate < 1 || TempDate > 31) || (TempMonth < 1 || TempMonth > 12) || (TempYear < 1)) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your monthly budget target as what the pre-requisites requested\n\t\t for!\n"ANSI_COLOR_RESET);
            printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Budget Usage Target (at month):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Budget Usage Target (at month)."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your monthly budget target on your current monthly budget creation.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The monthly budget target of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of monthly budget target format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);

            printf("\nBudget Usage Target (at month): ");
            fgets(InputMonthlyBudgetTargeting, BUFSIZE07, stdin);

            if (strlen(InputMonthlyBudgetTargeting) < 2) { EmptyMBTInput = true; }
            else {
                strcpy(InputMBTTemp, InputMonthlyBudgetTargeting);
                InputMBTTemp[strlen(InputMBTTemp) - 1] = '\0';
                DashesOccurences = FindOccurences(InputMBTTemp, '-');
                if (DashesOccurences == 2) {
                    TempTBDTempD = strtok(InputMBTTemp, "-"); TempTBDTempM = strtok(NULL, "-"); TempTBDTempY = strtok(NULL, "-");
                    TempDate = atoi(TempTBDTempD); TempMonth = atoi(TempTBDTempM); TempYear = atoi(TempTBDTempY);
                } EmptyMBTInput = false;
            }
        }
        
        InputMonthlyBudgetTargeting[strlen(InputMonthlyBudgetTargeting) - 1] = '\0';
        BCT = true;
        TBDTempD = strtok(InputMonthlyBudgetTargeting, "-"); TBDTempM = strtok(NULL, "-"); TBDTempY = strtok(NULL, "-");
        TBDTempD = TrimWhiteSpaces(TBDTempD); TBDTempM = TrimWhiteSpaces(TBDTempM); TBDTempY = TrimWhiteSpaces(TBDTempY);
        Date = atoi(TBDTempD); Month = atoi(TBDTempM); Year = atoi(TBDTempY);
        
        size_t FinalDate  = (long long unsigned)(((1900 + ManageTime.tm_year) % 4 != 0) ? ((((ManageTime.tm_mday + 30) - DateOfMonths[ManageTime.tm_mon]) != 0) ? ((ManageTime.tm_mday + 30) - DateOfMonths[ManageTime.tm_mon]) : 31) : ((((ManageTime.tm_mday + 30) - DateOfMonths_LEAP[ManageTime.tm_mon]) != 0) ? ((ManageTime.tm_mday + 30) - DateOfMonths_LEAP[ManageTime.tm_mon]) : 31));
        size_t FinalMonth = (FinalDate != 31) ? (((ManageTime.tm_mon + 1) != 12) ? ((ManageTime.tm_mon + 1) + 1) : 1) : (((ManageTime.tm_mon + 1) == 12) ? ((ManageTime.tm_mon + 1)) : 1);
        size_t FinalYear  = 1900 + (long long unsigned)(((ManageTime.tm_mon + 1) != 12) ? (ManageTime.tm_year) : (ManageTime.tm_year + 1));

        while (Date != FinalDate || Month != FinalMonth || Year != FinalYear) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: Monthly budget creation MUST TARGET the next 30 DAYS from now, and neither for YESTERDAY"ANSI_COLOR_RESET);
            puts(ANSI_COLOR_LIGHTRED"\t         nor TOMORROW, even to non-other next 30 DAYS from now! Thus, your current monthly budget"ANSI_COLOR_RESET);
            puts(ANSI_COLOR_LIGHTRED"\t         MUST BE in the date of the NEXT 30 DAYS, it's on: ");
            printf(ANSI_COLOR_LIGHTRED ANSI_STYLE_BOLD"\t             > %02lld-%02lld-%04lld (%s).\n\n"ANSI_COLOR_RESET, (FinalDate), (FinalMonth), (FinalYear), DaysOfWeek[(ManageTime.tm_wday + 30) % 7]);

            printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Budget Usage Target (at month):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Budget Usage Target (at month)."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your monthly budget target on your current monthly budget creation.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The monthly budget target of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of monthly budget target format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);

            printf("\nBudget Usage Target (at month): ");
            fgets(InputMonthlyBudgetTargeting, BUFSIZE07, stdin);

            if (strlen(InputMonthlyBudgetTargeting) < 2) { EmptyMBTInput = true; }
            else {
                strcpy(InputMBTTemp, InputMonthlyBudgetTargeting);
                InputMBTTemp[strlen(InputMBTTemp) - 1] = '\0';
                DashesOccurences = FindOccurences(InputMBTTemp, '-');
                if (DashesOccurences == 2) {
                    TempTBDTempD = strtok(InputMBTTemp, "-"); TempTBDTempM = strtok(NULL, "-"); TempTBDTempY = strtok(NULL, "-");
                    TempDate = atoi(TempTBDTempD); TempMonth = atoi(TempTBDTempM); TempYear = atoi(TempTBDTempY);
                } EmptyMBTInput = false;
            }

            while (EmptyMBTInput || DashesOccurences != 2 || (((TempYear % 4) == 0 && (TempMonth == 2)) && TempDate > 29) || (((TempYear % 4) != 0 && (TempMonth == 2)) && TempDate > 28) || (TempDate < 1 || TempDate > 31) || (TempMonth < 1 || TempMonth > 12) || (TempYear < 1)) {
                ClearScreen();
                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

                puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your monthly budget target as what the pre-requisites requested\n\t\t for!\n"ANSI_COLOR_RESET);
                printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n      " BRIGHTBLUE157"> Budget Usage Target (at month):\t\t%s\n\t"ANSI_COLOR_RESET "Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
                puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Budget Usage Target (at month)."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your monthly budget target on your current monthly budget creation.");
                puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The monthly budget target of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of monthly budget target format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);

                printf("\nBudget Usage Target (at month): ");
                fgets(InputMonthlyBudgetTargeting, BUFSIZE07, stdin);

                if (strlen(InputMonthlyBudgetTargeting) < 2) { EmptyMBTInput = true; }
                else {
                    strcpy(InputMBTTemp, InputMonthlyBudgetTargeting);
                    InputMBTTemp[strlen(InputMBTTemp) - 1] = '\0';
                    DashesOccurences = FindOccurences(InputMBTTemp, '-');
                    if (DashesOccurences == 2) {
                        TempTBDTempD = strtok(InputMBTTemp, "-"); TempTBDTempM = strtok(NULL, "-"); TempTBDTempY = strtok(NULL, "-");
                        TempDate = atoi(TempTBDTempD); TempMonth = atoi(TempTBDTempM); TempYear = atoi(TempTBDTempY);
                    } EmptyMBTInput = false;
                }
            }

            InputMonthlyBudgetTargeting[strlen(InputMonthlyBudgetTargeting) - 1] = '\0';
            BCT = true;
            TBDTempD = strtok(InputMonthlyBudgetTargeting, "-"); TBDTempM = strtok(NULL, "-"); TBDTempY = strtok(NULL, "-");
            TBDTempD = TrimWhiteSpaces(TBDTempD); TBDTempM = TrimWhiteSpaces(TBDTempM); TBDTempY = TrimWhiteSpaces(TBDTempY);
            Date = atoi(TBDTempD); Month = atoi(TBDTempM); Year = atoi(TBDTempY);
        }

        Year -= Month < 3;
        Day = (Year + (Year / 4) - (Year / 100) + (Year / 400) + TimeCounterNumeric[Month - 1] + Date) % 7;
        if (Date >= 11 && Date < 21)      { strcpy(NumericalPattern, "th"); }
        else {
            if (strlen(TBDTempD) < 2) {
                if      (TBDTempD[0] == '1') { strcpy(NumericalPattern, "st"); }
                else if (TBDTempD[0] == '2') { strcpy(NumericalPattern, "nd"); }
                else if (TBDTempD[0] == '3') { strcpy(NumericalPattern, "rd"); }
                else                         { strcpy(NumericalPattern, "th"); }
            } else {
                if      (TBDTempD[1] == '1') { strcpy(NumericalPattern, "st"); }
                else if (TBDTempD[1] == '2') { strcpy(NumericalPattern, "nd"); }
                else if (TBDTempD[1] == '3') { strcpy(NumericalPattern, "rd"); }
                else                         { strcpy(NumericalPattern, "th"); }
            }
        }

        strcpy(BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, DaysOfWeek[Day]);
        strcat(BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, ", ");
        strcat(BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, TBDTempD);
        strcat(BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, NumericalPattern);
        strcat(BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, " of ");
        strcat(BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, MonthsOfYear[Month - 1]);
        strcat(BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, " ");
        strcat(BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, TBDTempY);

        for (int i = 0; i < 7; i++)  { DaysOfWeek[i][0]   = 0; }
        for (int j = 0; j < 12; j++) { MonthsOfYear[j][0] = 0; }
        NumericalPattern[0] = 0;
        F3_BudgetCreationAndMonitoring(F3Selected);
    
    } else if (F3Selected == 4) {
        ClearScreen();
        char InputTransactionDescription[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

        if (BCD) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your budget creation description as: \n     >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n      " BRIGHTBLUE158"> Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Budget Creation Description."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the description of your current pre-recorded transaction.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The description of your current monthly budget creation must not be more than 100 characters! \n\t(leave the input blank if no description providen)."ANSI_COLOR_RESET);
        } else {
            printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n      " BRIGHTBLUE158"> Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Budget Creation Description."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the description of your current pre-recorded transaction.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The description of your current monthly budget creation must not be more than 100 characters! \n\t(leave the input blank if no description providen)."ANSI_COLOR_RESET);
        }
        
        printf("\nBudget Creation Description:\n      > ");
        fgets(InputTransactionDescription, BUFSIZE07, stdin);

        while (strlen(InputTransactionDescription) > 101) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature03, UserName);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your current pre-recorded transaction's description accordingly (max. 100 characters)!\n"ANSI_COLOR_RESET);
            printf("\tMonthly or Yearly Budget Creation Type:\t%s\n\tFinancial Budget Creation Category:\t%s\n\tExpenses Limit at (in Rp.):\t\t%s\n\tBudget Usage Target (at month):\t\t%s\n      " BRIGHTBLUE158"> Budget Creation Description:\n" ANSI_STYLE_BOLD ANSI_STYLE_ITALIC"    ... %s\n"ANSI_COLOR_RESET, BCAMInputs[GlobalRegisteredBCAM].MonthlyOrYearly, BCAMInputs[GlobalRegisteredBCAM].MonthlyFinancialCreationCategory, BCAMInputs[GlobalRegisteredBCAM].MonthlyLimitBudgetCreation, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetTargeting, BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Budget Creation Description."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the description of your current pre-recorded transaction.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The description of your current monthly budget creation must not be more than 100 characters! \n\t(leave the input blank if no description providen)."ANSI_COLOR_RESET);

            printf("\nBudget Creation Description:\n      > ");
            fgets(InputTransactionDescription, BUFSIZE07, stdin);
        }
        
        InputTransactionDescription[strlen(InputTransactionDescription) - 1] = '\0';
        BCD = true;
        (strlen(InputTransactionDescription) > 0) ? \
            strcpy(BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription, InputTransactionDescription) : \
            strcpy(BCAMInputs[GlobalRegisteredBCAM].MonthlyBudgetCreationDescription, "(no description provided)");
        InputTransactionDescription[0] = 0;
        F3_BudgetCreationAndMonitoring(F3Selected);

    } else if (F3Selected == 5) {
        MainMenuApplicationFeatures(MMAFSelected);
    }
}

void F4_FilterSearchingData(int F4Selected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    // FILE *TempAccessVHTF;
    // FinancialAM-05-Histogram-2ndWeekInDecember2023.txt
    char MatchAnyListedTxtFile[BUFSIZE07], AnyListedTxtFile[BUFSIZE07], KeyFinderTxtFile[BUFSIZE10], DecryptAndReadFile[BUFSIZE10];
    
    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature04, UserName);
    printf(BRIGHTPURPLE218 ANSI_STYLE_BOLD"\tLists of availables Moneytory Transaction Registration file system:\n\n"ANSI_COLOR_RESET);
    // puts(ANSI_COLOR_LIGHTRED"\tComing Soon: This spesific main menu session is still on DEVELOPMENT, and will be updated in the \n\tfuture, soon enough before the 16th WEEK.");
    // puts(ANSI_COLOR_PINK"\tThank you for your attention, and pardon for the incoviniences... .");
    // puts(ANSI_COLOR_YELLOW"\n\tReason on Development (to be done soon): Require a in-depth more about the UI and showing the \n\ttextings further, and still need to figure out on how to graph calculation in C.");
    
    for (int i = 0; i < (int)sizeof(SaveFilesTxtName); i++) {
        if (strlen(SaveFilesTxtName[i].FileNames) != 0) {
            strncpy(MatchAnyListedTxtFile, SaveFilesTxtName[i].FileNames, BUFSIZE07);
            if (strstr(MatchAnyListedTxtFile, "-F1-MTR-") != NULL)
                printf(BRIGHTBLUE159"\t    [%04d] > %s\n"ANSI_COLOR_RESET, (i), SaveFilesTxtName[i].FileNames);
            else if (strstr(MatchAnyListedTxtFile, "-F3-BCAM-") != NULL)
                printf(BRIGHTBLUE159"\t    [%04d] > %s\n"ANSI_COLOR_RESET, (i), SaveFilesTxtName[i].FileNames);
        } else break;
    } fflush(stdin);

    printf(BRIGHTGREEN156"\n\tNotice on Use: Drag and copy the file name listed above that interests you enough to check the graph\n\t\t       and paste into the input section '>' there (full file name with its .txt format)... .\n\t" BRIGHTPINK219 ANSI_STYLE_BOLD"Info:\t       If you wanted to get back to the main menu, just leave the input blank.\n"ANSI_COLOR_RESET);
    printf("\n(Drag and Copy) > "); fgets(AnyListedTxtFile, BUFSIZE07, stdin); AnyListedTxtFile[strlen(AnyListedTxtFile) - 1] = '\0';

    if (strlen(AnyListedTxtFile) > 0) {
        ClearScreen();
        strcpy(AnyListedTxtFile, TrimWhiteSpaces(AnyListedTxtFile));
        
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature04, UserName);
        printf(BRIGHTBLUE159 ANSI_STYLE_BOLD"\tTo be Filtered and Searched system file name: " ANSI_STYLE_UNDERLINE"%s\n\n", AnyListedTxtFile);
        printf(BRIGHTPURPLE213    ANSI_STYLE_BOLD"\tNote: Type anything you want to search, doesn't matter how short or long your keyfinder here is... .\n\n" BRIGHTPINK219 ANSI_STYLE_BOLD"\tInfo (01): If you wanted to choose another file, just leave the input blank.\n" BRIGHTRED216 ANSI_STYLE_BOLD"\tInfo (02): If you want to read the whole file, type in \"None\" (without the quotes).\n" BRIGHTBLUE157 ANSI_STYLE_BOLD"\tInfo (03): You can stack the keywords you wanted to find in the file you're trying to filter and\n\t\t   searched for, but REMEMBER to separate each keyword by a COMMA, just like as shown below:\n\t\t       > Keyword A, Keyword B, Keyword C, ... (add as many as you like)!\n\t\t       > Transaction by Date, Income, Expense\n\n"ANSI_COLOR_RESET);
        printf(BRIGHTMAGENTA210 ANSI_STYLE_ITALIC"\tWarning: Pay attention for the writing though, differences in capital letters may fatal!\n\t         Consider reading the whole content first before playing with keywords!\n\n"ANSI_COLOR_RESET);
        printf("(Anything) Keyword Finder: "); fgets(KeyFinderTxtFile, BUFSIZE07, stdin); KeyFinderTxtFile[strlen(KeyFinderTxtFile) - 1] = '\0'; 

        if (strlen(KeyFinderTxtFile) > 0) {
            char *CopyKeyFinderTxtFile = "";

            strcpy(KeyFinderTxtFile, TrimWhiteSpaces(KeyFinderTxtFile));
            strncpy(DecryptAndReadFile, AnyListedTxtFile, BUFSIZE10); strcat(DecryptAndReadFile, " > "); strcat(DecryptAndReadFile, KeyFinderTxtFile);
            strcpy(CopyKeyFinderTxtFile, KeyFinderTxtFile); CopyKeyFinderTxtFile = StringUppercase(CopyKeyFinderTxtFile);

            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature04, UserName);
            if (strcmp(CopyKeyFinderTxtFile, "NONE") == 0) DecryptTxtFile(AnyListedTxtFile, true, EncryptionKey, "None");
            else DecryptTxtFile(AnyListedTxtFile, false, EncryptionKey, DecryptAndReadFile);
            
            printf(ANSI_COLOR_LIGHTBLUE"\n\t────────────────────────────────────────────────────────────────────────────────────────────────────"ANSI_COLOR_RESET);
            printf(ANSI_COLOR_MAGENTA ANSI_STYLE_ITALIC"\n\n\t[ENTER] Head back to the main menu... ");
            getchar(); MainMenuApplicationFeatures(0);
        
        } else {
            F4_FilterSearchingData(0);
        }
    
    } else {
        MainMenuApplicationFeatures(0);
    }
}

void F5_ReminderAndSetNotifications(int F5Selected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    // printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature05, UserName);
    // puts(ANSI_COLOR_LIGHTRED"\t(DEMO MODE) Updating Soon: This spesific main menu session is still on DEVELOPMENT, and will be \n\tupdated in the future, soon enough before the 16th WEEK.");
    // puts(ANSI_COLOR_PINK"\tThank you for your attention, and pardon for the incoviniences... .");
    // puts(ANSI_COLOR_YELLOW"\n\tReason on Development (to be done soon): Releasing an updated version of the current UI's \n\tsession, whilst already in DEMO FEATURE MODE.");
    // puts(ANSI_COLOR_ORANGE"\n\tIn order to try to use this feature, try to use the program manually from the 'int main()' section. \n\tRight there, comment the condition to try to register and log in, and un-comment the lines that have \n\tseveral naming functions starting with 'INFO', 'QUESTION', 'WARNING', and 'ERROR'.");
    // puts(ANSI_COLOR_LIGHTORANGE"\n\tExperimental demonstrations: Un-comment those 4 lines as stated above, and enjoy some Windows' old \n\tpop-up notifications, and make some changes for the titles and the messages for each notifications \n\tin order to experience the changes accordingly.");
    // puts(ANSI_COLOR_GREEN ANSI_STYLE_ITALIC"\n\tSee more at my GitHub project here: https://github.com/EintsWaveX/ALPRO-FinalAssessments-EL4705_03");
    // getchar();
    InfoMessageBox_OK("(Info) Reminder and Notifications: Notifications Only", "Just a pop-up notification here, what would you expect?\n\nOh yes, don't forget to keep updated the information when the next update for further customize-able notifications, with the toogle to whether turning on or off the notifications... .\n\nBut before you go, just to mention that all the pop-up notifications you see here are actually made for C++ code, but somehow are able to be translated into C code here (but of course I gotta make the changes first), and all features (even the profile manager section) must have their own type of notifications!");
    MainMenuApplicationFeatures(MMAFSelected);
}

void F6_DataVisualization(int F6Selected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    // FILE *TempAccessVHTF;
    // FinancialAM-05-Histogram-2ndWeekInDecember2023.txt
    char MatchHistogramTxtFile[BUFSIZE07], VisualizeHistogramTxtFile[BUFSIZE07], *PerMoneyExpenseLine;
    signed long long int PerMoneyExpenses = 0;
    
    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature06, UserName);
    printf(BRIGHTPURPLE218 ANSI_STYLE_BOLD"\tLists of availables Moneytory Transaction Registration file system:\n\n"ANSI_COLOR_RESET);
    // puts(ANSI_COLOR_LIGHTRED"\tComing Soon: This spesific main menu session is still on DEVELOPMENT, and will be updated in the \n\tfuture, soon enough before the 16th WEEK.");
    // puts(ANSI_COLOR_PINK"\tThank you for your attention, and pardon for the incoviniences... .");
    // puts(ANSI_COLOR_YELLOW"\n\tReason on Development (to be done soon): Require a in-depth more about the UI and showing the \n\ttextings further, and still need to figure out on how to graph calculation in C.");
    
    for (int i = 0; i < (int)sizeof(SaveFilesTxtName); i++) {
        if (strlen(SaveFilesTxtName[i].FileNames) != 0) {
            strncpy(MatchHistogramTxtFile, SaveFilesTxtName[i].FileNames, BUFSIZE07);
            if (strstr(MatchHistogramTxtFile, "-F1-MTR-") != NULL)
                printf(BRIGHTBLUE159"\t    [%04d] > %s\n"ANSI_COLOR_RESET, (i), SaveFilesTxtName[i].FileNames);
        } else break;
    } fflush(stdin);

    printf(BRIGHTGREEN156"\n\tNotice on Use: Drag and copy the file name listed above that interests you enough to check the graph\n\t\t       and paste into the input section '>' there (full file name with its .txt format)... .\n\t" BRIGHTPINK219 ANSI_STYLE_BOLD"Info:\t       If you wanted to get back to the main menu, just leave the input blank.\n"ANSI_COLOR_RESET);
    printf("\n(Drag and Copy) > "); fgets(VisualizeHistogramTxtFile, BUFSIZE07, stdin);
    
    if (strlen(VisualizeHistogramTxtFile) > 1) {
        VisualizeHistogramTxtFile[strlen(VisualizeHistogramTxtFile) - 1] = '\0';
        strcpy(VisualizeHistogramTxtFile, TrimWhiteSpaces(VisualizeHistogramTxtFile));
        ClearScreen();

        if (access(VisualizeHistogramTxtFile, F_OK) == 0) {
            strtok_r(ReadAndPrintLine("FinancialAM-05-CA-CONFIGURATIONS.txt", 25), "=", &PerMoneyExpenseLine);
            PerMoneyExpenseLine = TrimWhiteSpaces(PerMoneyExpenseLine);
            PerMoneyExpenses    = (long long)fabsl(atof(PerMoneyExpenseLine) * 1000);

            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t"ANSI_COLOR_RESET ANSI_COLOR_GREEN"(STATUS) Profile Account Linked to: "ANSI_COLOR_RESET ANSI_STYLE_BOLD BRIGHTBLUE158 ANSI_STYLE_ITALIC ANSI_STYLE_UNDERLINE"%s.\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppFeature06, UserName);
            HorizontalHistogramUI_MONTH(VisualizeHistogramTxtFile, PerMoneyExpenses);
            getchar(); MainMenuApplicationFeatures(F6Selected);
        } else {
            F6_DataVisualization(F6Selected);
        }
    
    } else {
        MainMenuApplicationFeatures(MMAFSelected);
    }
}

void LanguageMenu(void) {
    fflush(stdout); fflush(stdin);
    ArrowKeyChoiceDialog("Language Mode", MessagesShown_ArrowKeyChoiceDialog, 0, 2);
}

void AccountRegistrationMenu(int ARMSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    time_t Time = time(NULL);
    struct tm ManageTime = *localtime(&Time);

    FILE *FDestination, *FTempDestination;
    int BufLen, Ptr = 0, KeyTracker = 0;
    char FDBuffer[BUFSIZE16], DeleteTempDestinationTxtFile[128], TxtFileName[128] = "SKYR-FMSA-RegisteredAccounts.txt > Accounts";
    char *SourceKeyStringValue, *SelectedKeyString;
    char *SourceKeyStringValues[BUFSIZE07];

    FILE *TempARMInputs;
    char RegAccInsider[BUFSIZE07], GRA[BUFSIZE07];
    char FirstName[BUFSIZE07], LastName[BUFSIZE07], Email[BUFSIZE07], Username[BUFSIZE07], Password[BUFSIZE07];
    char DateOfBirth[BUFSIZE07], AgeOnPresent[BUFSIZE07], PhoneNumber[BUFSIZE07], Sex[BUFSIZE07];
    char UpdateLocalTime[BUFSIZE07], LocalTime[BUFSIZE07], AccountMadeTime[BUFSIZE07], MadeTime[BUFSIZE07];

    int AvailableOptions = 5, SubmitOrContinue, ExistingAccounts;
    bool Selecting = true, Updated = false, FirstRun = true;
    bool FirstARMUpgrade = false, SecondARMUpgrade = false;

    int PreviousAKDC = 0;
    bool CatchDefaultAKDC = false;

    // bool ConfirmOrBackARM = false;
    char MessageID02[BUFSIZE10];
    char TempCountSKYRFMSARegisteredAccounts[BUFSIZE10];
    char *CountSKYRFMSARegisteredAccounts, AKDC;

    if (access("SKYR-FMSA-RegisteredAccounts.txt", F_OK) != 0 && !FlagARM) { GlobalSKYRFMSARegisteredAccounts = 0; }
    else if (access("SKYR-FMSA-RegisteredAccounts.txt", F_OK) == 0 && !FlagARM) {
        FDestination     = fopen("SKYR-FMSA-RegisteredAccounts.txt", "r");
        FTempDestination = fopen("TempDestination.txt", "w");

        while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
            BufLen = strlen(FDBuffer);
            for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
            fputs(FDBuffer, FTempDestination);
        } fclose(FDestination); fclose(FTempDestination);

        strtok_r(TxtFileName, ">", &SelectedKeyString);
        SelectedKeyString = TrimWhiteSpaces(SelectedKeyString);
        SourceKeyStringValue = strtok(SelectedKeyString, ",");
        KeyTracker++;

        while (SourceKeyStringValue != NULL) {
            SourceKeyStringValues[Ptr] = SourceKeyStringValue;
            SourceKeyStringValues[Ptr] = TrimWhiteSpaces(SourceKeyStringValues[Ptr]);
            SourceKeyStringValue = strtok(NULL, ",");
            Ptr++; KeyTracker++;
        } // SourceTextFileName = TrimWhiteSpaces(TxtFileName);
        
        strcpy(TempCountSKYRFMSARegisteredAccounts, ReadAndPrintLine("TempDestination.txt", 9));

        strcpy(DeleteTempDestinationTxtFile, "del ");
        strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
        system(DeleteTempDestinationTxtFile);

        TempCountSKYRFMSARegisteredAccounts[strlen(TempCountSKYRFMSARegisteredAccounts) - 1] = '\0';
        strtok_r(TempCountSKYRFMSARegisteredAccounts, ":", &CountSKYRFMSARegisteredAccounts);
        
        CountSKYRFMSARegisteredAccounts = TrimWhiteSpaces(CountSKYRFMSARegisteredAccounts);
        CountSKYRFMSARegisteredAccounts = strtok(CountSKYRFMSARegisteredAccounts, " ");
        ExistingAccounts = atoi(CountSKYRFMSARegisteredAccounts);
        
        if (!SKYRApplicationRunning) { GlobalSKYRFMSARegisteredAccounts += ExistingAccounts; }
        else { GlobalSKYRFMSARegisteredAccounts++; }
        FlagARM = true;
    }
    
    if ((FN && LN && E && U && P) && !FirstARMUpgrade && !ARMNotificationEnabled_02) {
        InfoMessageBox_OK("(Info) @SKYR-PFMSA; First Profile Input Data Upgraded", "All right, new starters! Here now we've upgraded the Registration Menu UI with 4 (four) new profiles input, such as:\n\n\t1. Date of Birth (DD-MM-YYYY)\n\t2. Present Age\n\t3. Phone Number (+? ?)\n\t4. Sex/Gender (M/F)\n\nAfter you fulfilled in everything it asked for, you may see the pop-up message like this again, indicating you're ready to submit your profil account and be registered into the file system!");
        ARMNotificationEnabled_02 = true;
    } if ((FN && LN && E && U && P) && (B && A && PN && S) && !SecondARMUpgrade && !ARMNotificationEnabled_03) {
        InfoMessageBox_OK("(Info) @SKYR-PFMSA; Second Profile Input Data Upgraded", "All right, new starters! Here now we've upgraded the Registration Menu UI again, and now you can just keep going UPWARDS or DOWNWARDS until you see a complete different UI, making sure that you're ready to be registered as a new user using this application!");
        ARMNotificationEnabled_03 = true;
    }

    if ((FN && LN && E && U && P) && !FirstARMUpgrade) {
        AvailableOptions += 4; FirstARMUpgrade = true;
    } if ((FN && LN && E && U && P) && (B && A && PN && S) && !SecondARMUpgrade) {
        AvailableOptions += 5; SecondARMUpgrade = true;
    }

    if (!ARMNotificationEnabled_01) { InfoMessageBox_OK("(Info) @SKYR-PFMSA; Importance of The Safety Profile Account", "For the safety purposes while you're going registrating a new account, or when trying to logged into the application, or even when you're going to recover of your missing account,\n\n\tWE ARE GOING TO DEPLETED EVERY INPUT YOU'VE PROGRESSED SO FAR, SO PLEASE JUST STAY IN ONE UI MENU;\n\nIn order to be save and more secure, so don't blame us when you're missing on your inputs after switching to different UIs... ."); ARMNotificationEnabled_01 = true; }

    while (Selecting) {
        if (!FirstRun) {
            /*  Separated by one line to another, handling only the first
                FIVE (5) rows each parts.
            >   First Name, Last Name, Personal E-mail, SKYR Username, SKYR Password
            */

            /*  Separated by one line to another, handling both the first and second
                FOUR (4) + FIVE (5) rows both parts.
            >   Date of Birth, Age on Present, Phone  Number, Sex/Gender
            */
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);
            if (CatchDefaultAKDC) printf(ANSI_COLOR_LIGHTRED"\tError: The auto-enter shortcut key labeled as '%c' (ID: 0x%02X) is not registered at the moment!\n\n"ANSI_COLOR_RESET, ((int)PreviousAKDC != 12) ? (char)PreviousAKDC : 10, (int)PreviousAKDC);
            
            if ((ARMSelected + 1) > 0 && (ARMSelected + 1) <= 5 && (AvailableOptions == 5)) {
                if ((ARMSelected + 1) == 1) {
                    if (!FN) { printf("      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                    else     { printf("      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                } else if ((ARMSelected + 1) == 2) {
                    if (!LN) { printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                    else     { printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                } else if ((ARMSelected + 1) == 3) {
                    if (!E)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                } else if ((ARMSelected + 1) == 4) {
                    if (!U)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                } else if ((ARMSelected + 1) == 5) {
                    if (!P)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                }

                (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\n\t%s", AppRegistrationUDRL) : printf("\n\n\n\n\n\n\t%s", AppRegistrationUDRL);
            }
            
            if ((ARMSelected + 1) > 0 && (ARMSelected + 1) <= 9 && (AvailableOptions == 9)) {
                if ((ARMSelected + 1) == 1) {
                    if (!FN) { printf("      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 2) {
                    if (!LN) { printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 3) {
                    if (!E)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 4) {
                    if (!U)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 5) {
                    if (!P)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 6) {
                    if (!B)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTYELLOW"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTGREEN"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 7) {
                    if (!A)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 8) {
                    if (!PN) { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 9) {
                    if (!S)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                }

                (!CatchDefaultAKDC) ? printf("\n\n\n\n\t%s", AppRegistrationUDRL) : printf("\n\n\t%s", AppRegistrationUDRL);
            }

            if ((ARMSelected + 1) > 0 && (ARMSelected + 1) <= 14 && (AvailableOptions == 14)) {
                if ((ARMSelected + 1) == 1) {
                    if (!FN) { printf("      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 2) {
                    if (!LN) { printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 3) {
                    if (!E)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 4) {
                    if (!U)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 5) {
                    if (!P)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 6) {
                    if (!B)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTYELLOW"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTGREEN"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 7) {
                    if (!A)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 8) {
                    if (!PN) { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 9) {
                    if (!S)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                }

                (!CatchDefaultAKDC) ? printf("\n\n\n\n\t%s", AppRegistrationUDRL) : printf("\n\n\t%s", AppRegistrationUDRL);
                
                if ((ARMSelected + 1) > 9) {
                    ClearScreen();
                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

                    printf("\tInfo: You have all the main required information listing above of all \n\t      nine (9) personal infos, and you may proceed to the final step, and \n\t      it's about giving optional information about your career profiling, \n\t      degree of experience, and such else.\n");
                    printf("\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTGREEN"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_CYAN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTRED"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_RED"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_MAGENTA"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour personal profile infos?\n\n");
                    
                    snprintf(MessageID02, BUFSIZE10, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);
                    MessagesShown_ArrowKeyChoiceDialog[2] = MessageID02;
                    MessagesShown_ArrowKeyChoiceDialog[3] = "\tInfo: You have all the main required information listing above of all \n\t      nine (9) personal infos, and you may proceed to the final step, and \n\t      it's about giving optional information about your career profiling, \n\t      degree of experience, and such else.";
                    MessagesShown_ArrowKeyChoiceDialog[4] = "\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTGREEN"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_CYAN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTRED"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_RED"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_MAGENTA"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour personal profile infos?\n";
                    SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 2, 5);

                    if (SubmitOrContinue) {
                        if (access("SKYR-FMSA-RegisteredAccounts.txt", F_OK) != 0 && !FlagARM) {
                            TempARMInputs = fopen("TempSKYR-FMSA-RegisteredAccounts.txt", "w");

                            strcpy(GRA, "1");
                            snprintf(LocalTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                            strcpy(RegAccInsider, "Registered Accounts: "); strcat(RegAccInsider, GRA); strcat(RegAccInsider, " account(s) in total.\n");
                            strcpy(UpdateLocalTime, "PersonalFMSA | Last Updated: ");
                            strcat(UpdateLocalTime, LocalTime); strcat(UpdateLocalTime, "\n");
                            strcpy(AccountMadeTime, "Profile Account :: No. 1"); strcat(AccountMadeTime, "\n");
                            strcat(AccountMadeTime, "Created on: "); strcat(AccountMadeTime, MadeTime); strcat(AccountMadeTime, "\n");

                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", TempARMInputs);
                            fputs(ApplicationPresent, TempARMInputs);
                            fputs(ApplicationTitle, TempARMInputs);
                            fputs(ApplicationVersion, TempARMInputs); fputs("\n", TempARMInputs);
                            fputs(UpdateLocalTime, TempARMInputs);
                            fputs("Built-in Console Application [CLI-Win32], fundamentally C (100%)\n", TempARMInputs);
                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", TempARMInputs);
                            fputs(RegAccInsider, TempARMInputs);
                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", TempARMInputs);
                            fclose(TempARMInputs);
                        
                        } else if (access("SKYR-FMSA-RegisteredAccounts.txt", F_OK) == 0 && FlagARM) {
                            FDestination     = fopen("SKYR-FMSA-RegisteredAccounts.txt", "r");
                            FTempDestination = fopen("TempSKYR-FMSA-RegisteredAccounts.txt", "w");

                            while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
                                BufLen = strlen(FDBuffer);
                                for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                                fputs(FDBuffer, FTempDestination);
                            } fclose(FDestination); fclose(FTempDestination);
                        }

                        TempARMInputs = fopen("TempSKYR-FMSA-RegisteredAccounts.txt", "a+");

                        if (!FlagARM) { strcpy(GRA, "1"); }
                        else if (FlagARM && GlobalSKYRFMSARegisteredAccounts > 1) { itoa(GlobalSKYRFMSARegisteredAccounts, GRA, 10); }
                        
                        snprintf(MadeTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                        strcpy(AccountMadeTime, "Profile Account :: No. "); strcat(AccountMadeTime, GRA); strcat(AccountMadeTime, "\n");
                        strcat(AccountMadeTime, "Created on: "); strcat(AccountMadeTime, MadeTime); strcat(AccountMadeTime, "\n");

                        strcpy(FirstName, "First Name:\t\t");        strcat(FirstName, ARMInputs.FirstName);       strcat(FirstName, "\n");
                        strcpy(LastName, "Last Name:\t\t");          strcat(LastName, ARMInputs.LastName);         strcat(LastName, "\n");
                        strcpy(Email, "Personal E-mail:\t");         strcat(Email, ARMInputs.Email);               strcat(Email, "\n");
                        strcpy(Username, "SKYR Username:\t\t");      strcat(Username, ARMInputs.Username);         strcat(Username, "\n");
                        strcpy(Password, "SKYR Password:\t\t");      strcat(Password, ARMInputs.Password);         strcat(Password, "\n");
                        strcpy(DateOfBirth, "\nDate of Birth:\t\t"); strcat(DateOfBirth, ARMInputs.DateOfBirth);   strcat(DateOfBirth, "\n");
                        strcpy(AgeOnPresent, "Age on Present:\t\t"); strcat(AgeOnPresent, ARMInputs.AgeOnPresent); strcat(AgeOnPresent, "\n");
                        strcpy(PhoneNumber, "Phone Number:\t\t");    strcat(PhoneNumber, ARMInputs.PhoneNumber);   strcat(PhoneNumber, "\n");
                        strcpy(Sex, "Sex/Gender:\t\t");              strcat(Sex, ARMInputs.Sex);                   strcat(Sex, "\n");

                        fputs(AccountMadeTime, TempARMInputs); fputs("\n", TempARMInputs);
                        fputs(FirstName, TempARMInputs); fputs(LastName, TempARMInputs); fputs(Email, TempARMInputs); fputs(Username, TempARMInputs); fputs(Password, TempARMInputs);
                        fputs(DateOfBirth, TempARMInputs); fputs(AgeOnPresent, TempARMInputs); fputs(PhoneNumber, TempARMInputs); fputs(Sex, TempARMInputs);
                        fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", TempARMInputs);
                        fclose(TempARMInputs);

                        puts(BRIGHTBLUE159"\n\tInfo: Your account profile has been saved and ecrypted."ANSI_COLOR_RESET);
                        puts(BRIGHTGREEN156"\t      Now you may proceed to login (or sign-ing in) with your freshly new made account just by \n\t      pressing [ENTER] button key on your device to continue the login process in the Login Menu...\n"ANSI_COLOR_RESET);

                        LE = false; LPN = false; LU = false; LP = false;
                        FN = false; LN = false; E = false; U = false; P = false;
                        B = false; A = false; PN = false; S = false; CPR = false; PD = false;
                        AC = false; CW = false; DI = false;
                        ARMSelected = 0; FlagARM = false;

                        ARMInputs.FirstName[0] = 0; ARMInputs.LastName[0] = 0; ARMInputs.Email[0] = 0; ARMInputs.Username[0] = 0; ARMInputs.Password[0] = 0; ARMInputs.HiddenPasswordShown[0] = 0;
                        ARMInputs.DateOfBirth[0] = 0; ARMInputs.AgeOnPresent[0] = 0; ARMInputs.PhoneNumber[0] = 0; ARMInputs.Sex[0] = 0;

                        strcpy(RegAccInsider, "Registered Accounts: "); strcat(RegAccInsider, GRA); strcat(RegAccInsider, " account(s) in total.");
                        OverWriteStringAtLine("TempSKYR-FMSA-RegisteredAccounts.txt", RegAccInsider, 0, 9);
                        EncryptTxtFile("TempSKYR-FMSA-RegisteredAccounts.txt", "SKYR-FMSA-RegisteredAccounts.txt", EncryptionKey, true);
                        printf(BRIGHTGREEN154"\t[ENTER] Proceed to the Login Menu... "); getchar();
                        AccountLoginMenu(0);

                    } else { ARMSelected = 0; AccountRegistrationMenu(ARMSelected); }
                }
            }

        } else {
            FirstRun = false;
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

            if ((ARMSelected + 1) > 0 && (ARMSelected + 1) <= 5 && (AvailableOptions == 5)) {
                if ((ARMSelected + 1) == 1) {
                    if (!FN) { printf("      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                    else     { printf("      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                } else if ((ARMSelected + 1) == 2) {
                    if (!LN) { printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                    else     { printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                } else if ((ARMSelected + 1) == 3) {
                    if (!E)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                } else if ((ARMSelected + 1) == 4) {
                    if (!U)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                } else if ((ARMSelected + 1) == 5) {
                    if (!P)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password)); }
                }

                (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\n\t%s", AppRegistrationUDRL) : printf("\n\n\n\n\n\t%s", AppRegistrationUDRL);
            }

            if ((ARMSelected + 1) > 0 && (ARMSelected + 1) <= 9 && (AvailableOptions == 9)) {
                if ((ARMSelected + 1) == 1) {
                    if (!FN) { printf("      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 2) { 
                    if (!LN) { printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 3) {
                    if (!E)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 4) {
                    if (!U)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 5) {
                    if (!P)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 6) {
                    if (!B)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTYELLOW"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTGREEN"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 7) {
                    if (!A)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 8) {
                    if (!PN) { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 9) {
                    if (!S)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                }

                (!CatchDefaultAKDC) ? printf("\n\n\n\n\t%s", AppRegistrationUDRL) : printf("\n\n\t%s", AppRegistrationUDRL);
            }

            if ((ARMSelected + 1) > 0 && (ARMSelected + 1) <= 14 && (AvailableOptions == 14)) {
                if ((ARMSelected + 1) == 1) {
                    if (!FN) { printf("      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 2) {
                    if (!LN) { printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 3) {
                    if (!E)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 4) {
                    if (!U)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 5) {
                    if (!P)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n\n\t"ANSI_COLOR_RESET "Date of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 6) {
                    if (!B)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTYELLOW"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n      " ANSI_COLOR_LIGHTGREEN"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 7) {
                    if (!A)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 8) {
                    if (!PN) { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                } else if ((ARMSelected + 1) == 9) {
                    if (!S)  { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                    else     { printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n\n\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password), ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex); }
                }

                (!CatchDefaultAKDC) ? printf("\n\n\n\n\t%s", AppRegistrationUDRL) : printf("\n\n\t%s", AppRegistrationUDRL);
                
                if ((ARMSelected + 1) > 9) {
                    ClearScreen();
                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

                    printf("\tInfo: You have all the main required information listing above of all \n\t      nine (9) personal infos, and you may proceed to the final step, and \n\t      it's about giving optional information about your career profiling, \n\t      degree of experience, and such else.\n");
                    printf("\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTRED"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_RED"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_GREEN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTGREEN"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_CYAN"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour personal profile infos?\n\n");
                    
                    snprintf(MessageID02, BUFSIZE10, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);
                    MessagesShown_ArrowKeyChoiceDialog[2] = MessageID02;
                    MessagesShown_ArrowKeyChoiceDialog[3] = "\tInfo: You have all the main required information listing above of all \n\t      nine (9) personal infos, and you may proceed to the final step, and \n\t      it's about giving optional information about your career profiling, \n\t      degree of experience, and such else.";
                    MessagesShown_ArrowKeyChoiceDialog[4] = "\n\t" ANSI_COLOR_LIGHTBLUE"(Optional)"ANSI_COLOR_RESET " Here all are the given choices before you proceed... \n\t" ANSI_COLOR_LIGHTGREEN"> CONFIRM: "ANSI_COLOR_RESET ANSI_COLOR_GREEN"Stop Here"ANSI_COLOR_RESET " and " ANSI_COLOR_CYAN"Save All"ANSI_COLOR_RESET" the given informations, or \n\t" ANSI_COLOR_LIGHTRED"> CANCEL: "ANSI_COLOR_RESET ANSI_COLOR_RED"Keep All"ANSI_COLOR_RESET " the information and " ANSI_COLOR_MAGENTA"Continue to Fill In"ANSI_COLOR_RESET " the last section of \n\tyour personal profile infos?\n";
                    SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 2, 5);

                    if (SubmitOrContinue) {
                        if (access("SKYR-FMSA-RegisteredAccounts.txt", F_OK) != 0 && !FlagARM) {
                            TempARMInputs = fopen("TempSKYR-FMSA-RegisteredAccounts.txt", "w");

                            strcpy(GRA, "1");
                            snprintf(LocalTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                            strcpy(RegAccInsider, "Registered Accounts: "); strcat(RegAccInsider, GRA); strcat(RegAccInsider, " account(s) in total.\n");
                            strcpy(UpdateLocalTime, "PersonalFMSA | Last Updated: ");
                            strcat(UpdateLocalTime, LocalTime); strcat(UpdateLocalTime, "\n");
                            strcpy(AccountMadeTime, "Profile Account :: No. 1"); strcat(AccountMadeTime, "\n");
                            strcat(AccountMadeTime, "Created on: "); strcat(AccountMadeTime, MadeTime); strcat(AccountMadeTime, "\n");

                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", TempARMInputs);
                            fputs(ApplicationPresent, TempARMInputs);
                            fputs(ApplicationTitle, TempARMInputs);
                            fputs(ApplicationVersion, TempARMInputs); fputs("\n", TempARMInputs);
                            fputs(UpdateLocalTime, TempARMInputs);
                            fputs("Built-in Console Application [CLI-Win32], fundamentally C (100%)\n", TempARMInputs);
                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", TempARMInputs);
                            fputs(RegAccInsider, TempARMInputs);
                            fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", TempARMInputs);
                            fclose(TempARMInputs);
                        
                        } else if (access("SKYR-FMSA-RegisteredAccounts.txt", F_OK) == 0 && FlagARM) {
                            FDestination     = fopen("SKYR-FMSA-RegisteredAccounts.txt", "r");
                            FTempDestination = fopen("TempSKYR-FMSA-RegisteredAccounts.txt", "w");

                            while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
                                BufLen = strlen(FDBuffer);
                                for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                                fputs(FDBuffer, FTempDestination);
                            } fclose(FDestination); fclose(FTempDestination);
                        }

                        TempARMInputs = fopen("TempSKYR-FMSA-RegisteredAccounts.txt", "a+");

                        if (!FlagARM) { strcpy(GRA, "1"); }
                        else if (FlagARM && GlobalSKYRFMSARegisteredAccounts > 1) { itoa(GlobalSKYRFMSARegisteredAccounts, GRA, 10); }
                        
                        snprintf(MadeTime, BUFSIZE07, "%d-%02d-%02d %02d:%02d:%02d", ManageTime.tm_year + 1900, ManageTime.tm_mon + 1, ManageTime.tm_mday, ManageTime.tm_hour, ManageTime.tm_min, ManageTime.tm_sec);
                        strcpy(AccountMadeTime, "Profile Account :: No. "); strcat(AccountMadeTime, GRA); strcat(AccountMadeTime, "\n");
                        strcat(AccountMadeTime, "Created on: "); strcat(AccountMadeTime, MadeTime); strcat(AccountMadeTime, "\n");

                        strcpy(FirstName, "First Name:\t\t");        strcat(FirstName, ARMInputs.FirstName);       strcat(FirstName, "\n");
                        strcpy(LastName, "Last Name:\t\t");          strcat(LastName, ARMInputs.LastName);         strcat(LastName, "\n");
                        strcpy(Email, "Personal E-mail:\t");         strcat(Email, ARMInputs.Email);               strcat(Email, "\n");
                        strcpy(Username, "SKYR Username:\t\t");      strcat(Username, ARMInputs.Username);         strcat(Username, "\n");
                        strcpy(Password, "SKYR Password:\t\t");      strcat(Password, ARMInputs.Password);         strcat(Password, "\n");
                        strcpy(DateOfBirth, "\nDate of Birth:\t\t"); strcat(DateOfBirth, ARMInputs.DateOfBirth);   strcat(DateOfBirth, "\n");
                        strcpy(AgeOnPresent, "Age on Present:\t\t"); strcat(AgeOnPresent, ARMInputs.AgeOnPresent); strcat(AgeOnPresent, "\n");
                        strcpy(PhoneNumber, "Phone Number:\t\t");    strcat(PhoneNumber, ARMInputs.PhoneNumber);   strcat(PhoneNumber, "\n");
                        strcpy(Sex, "Sex/Gender:\t\t");              strcat(Sex, ARMInputs.Sex);                   strcat(Sex, "\n");

                        fputs(AccountMadeTime, TempARMInputs); fputs("\n", TempARMInputs);
                        fputs(FirstName, TempARMInputs); fputs(LastName, TempARMInputs); fputs(Email, TempARMInputs); fputs(Username, TempARMInputs); fputs(Password, TempARMInputs);
                        fputs(DateOfBirth, TempARMInputs); fputs(AgeOnPresent, TempARMInputs); fputs(PhoneNumber, TempARMInputs); fputs(Sex, TempARMInputs);
                        fputs("────────────────────────────────────────────────────────────────────────────────────────────────────\n", TempARMInputs);
                        fclose(TempARMInputs);

                        puts(BRIGHTBLUE159"\n\tInfo: Your account profile has been saved and ecrypted."ANSI_COLOR_RESET);
                        puts(BRIGHTGREEN156"\t      Now you may proceed to login (or sign-ing in) with your freshly new made account just by \n\t      pressing [ENTER] button key on your device to continue the login process in the Login Menu...\n"ANSI_COLOR_RESET);

                        LE = false; LPN = false; LU = false; LP = false;
                        FN = false; LN = false; E = false; U = false; P = false;
                        B = false; A = false; PN = false; S = false; CPR = false; PD = false;
                        AC = false; CW = false; DI = false;
                        ARMSelected = 0; FlagARM = false;

                        ARMInputs.FirstName[0] = 0; ARMInputs.LastName[0] = 0; ARMInputs.Email[0] = 0; ARMInputs.Username[0] = 0; ARMInputs.Password[0] = 0; ARMInputs.HiddenPasswordShown[0] = 0;
                        ARMInputs.DateOfBirth[0] = 0; ARMInputs.AgeOnPresent[0] = 0; ARMInputs.PhoneNumber[0] = 0; ARMInputs.Sex[0] = 0;
                        
                        strcpy(RegAccInsider, "Registered Accounts: "); strcat(RegAccInsider, GRA); strcat(RegAccInsider, " account(s) in total.");
                        OverWriteStringAtLine("TempSKYR-FMSA-RegisteredAccounts.txt", RegAccInsider, 0, 9);
                        EncryptTxtFile("TempSKYR-FMSA-RegisteredAccounts.txt", "SKYR-FMSA-RegisteredAccounts.txt", EncryptionKey, true);
                        printf(BRIGHTGREEN154"\t[ENTER] Proceed to the Login Menu... "); getchar();
                        AccountLoginMenu(0);

                    } else { ARMSelected = 0; AccountRegistrationMenu(ARMSelected); }
                }
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP: {
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                if (ARMSelected > 0 && ARMSelected < AvailableOptions) {
                    --ARMSelected; Updated = true;
                } else if (ARMSelected <= 0) {
                    ARMSelected = (AvailableOptions - 1); Updated = true;
                } break;
            } case KEY_DOWN: {
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                if (ARMSelected >= 0 && ARMSelected < AvailableOptions - 1) {
                    ++ARMSelected; Updated = true;
                } else if (ARMSelected >= AvailableOptions - 1) {
                    ARMSelected = 0; Updated = true;
                } break;
            } case KEY_RIGHT:
                AccountLoginMenu(0);
                break;
            case KEY_LEFT: break;
            case '1': ARMSelected = 0; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '2': ARMSelected = 1; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '3': ARMSelected = 2; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '4': ARMSelected = 3; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '5': ARMSelected = 4; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '6': {
                if (AvailableOptions != 9) { ClearScreen(); continue; }
                ARMSelected = 5; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false;
                break;
            } case '7': {
                if (AvailableOptions != 9) { ClearScreen(); continue; }
                ARMSelected = 6; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false;
                break;
            } case '8': {
                if (AvailableOptions != 9) { ClearScreen(); continue; }
                ARMSelected = 7; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false;
                break;
            } case '9': {
                if (AvailableOptions != 9) { ClearScreen(); continue; }
                ARMSelected = 8; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false;
                break;
            } case KEY_ENTER:
                Selecting = false; Updated = true; CatchDefaultAKDC = false;
                break;
            default: {
                if (AKDC == KEY_UP || AKDC == KEY_DOWN || AKDC == KEY_LEFT || AKDC == KEY_RIGHT || AKDC == KEY_ENTER) { ClearScreen(); continue; }
                (AKDC > 0) ? PreviousAKDC = (int)AKDC : 0;
                (AKDC > 0) ? CatchDefaultAKDC = true : false;
            } break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    }

    if (ARMSelected == 0) {
        ClearScreen();
        char InputFirstName[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

        if (FN) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your first name as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs.FirstName);
            printf("      " ANSI_COLOR_LIGHTGREEN"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"First Name."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the first name of your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The first name of yours can be more than one or two words."ANSI_COLOR_RESET);
        } else {
            printf("      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"First Name."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the first name of your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The first name of yours can be more than one or two words."ANSI_COLOR_RESET);
        }
        
        printf("\nFirst Name: ");
        fgets(InputFirstName, BUFSIZE07, stdin);

        if (strcmp(InputFirstName, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

        while (strlen(InputFirstName) <= 3) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your first name at least a single word (min. 3 characters)!\n"ANSI_COLOR_RESET);
            printf("      " ANSI_COLOR_LIGHTYELLOW"> First Name:\t\t%s\n\t"ANSI_COLOR_RESET "Last Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"First Name."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the first name of your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The first name of yours can be more than one or two words."ANSI_COLOR_RESET);

            printf("\nFirst Name: ");
            fgets(InputFirstName, BUFSIZE07, stdin);

            if (strcmp(InputFirstName, "...\n") == 0) AccountRegistrationMenu(ARMSelected);
        }
        
        InputFirstName[strlen(InputFirstName) - 1] = '\0';
        FN = true;
        strcpy(ARMInputs.FirstName, InputFirstName);
        InputFirstName[0] = 0;
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 1) {
        ClearScreen();
        char InputLastName[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

        if (LN) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your last name as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs.LastName);
            printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Last Name."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the last name of your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The last name of yours can be more than one or two words."ANSI_COLOR_RESET);
        } else {
            printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Last Name."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the last name of your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The last name of yours can be more than one or two words."ANSI_COLOR_RESET);
        }

        printf("\nLast Name: ");
        fgets(InputLastName, BUFSIZE07, stdin);

        if (strcmp(InputLastName, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

        while (strlen(InputLastName) <= 3) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your last n ame at least a single word (min. 3 characters)!\n"ANSI_COLOR_RESET);
            printf("\tFirst Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Last Name:\t\t%s\n\t"ANSI_COLOR_RESET "Personal E-mail:\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Last Name."ANSI_COLOR_RESET "\n\tPlease proceed to fill in the first name of your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The last name of yours can be more than one or two words."ANSI_COLOR_RESET);

            printf("\nLast Name: ");
            fgets(InputLastName, BUFSIZE07, stdin);

            if (strcmp(InputLastName, "...\n") == 0) AccountRegistrationMenu(ARMSelected);
        }
        
        InputLastName[strlen(InputLastName) - 1] = '\0';
        LN = true;
        strcpy(ARMInputs.LastName, InputLastName);
        InputLastName[0] = 0;
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 2) {
        ClearScreen();
        char InputEmail[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

        if (E) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your personal e-mail as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs.Email);
            printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating your own \n\t      e-mail, and make sure that NO SPACES in your inserted e-mail!"ANSI_COLOR_RESET);
        } else {
            printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating your own \n\t      e-mail, and make sure that NO SPACES in your inserted e-mail!"ANSI_COLOR_RESET);
        }

        printf("\nPersonal E-mail: ");
        fgets(InputEmail, BUFSIZE07, stdin);

        if (strcmp(InputEmail, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

        while (strlen(InputEmail) <= 3 || strchr(InputEmail, '@') == NULL || strchr(InputEmail, '.') == NULL || strchr(InputEmail, ' ') != NULL || FindOccurences(InputEmail, '@') > 2 || FindOccurences(InputEmail, '.') > 2) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your last name at least a single word (min. 3 characters)!\n\t         The valid E-mail format must have a '@' symbol, and the provider (authorized by) \n\t         with the domain itself (NO SPACES are allowed either)!\n"ANSI_COLOR_RESET);
            printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating your own \n\t      e-mail, and make sure that NO SPACES in your inserted e-mail!"ANSI_COLOR_RESET);

            printf("\nPersonal E-mail: ");
            fgets(InputEmail, BUFSIZE07, stdin);

            if (strcmp(InputEmail, "...\n") == 0) AccountRegistrationMenu(ARMSelected);
        }
        
        InputEmail[strlen(InputEmail) - 1] = '\0';
        E = true;
        strcpy(ARMInputs.Email, InputEmail);
        InputEmail[0] = 0;
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 3) {
        ClearScreen();
        char InputUsername[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

        if (U) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your username as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs.Username);
            printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, so use \n\t      underscores or dashes to represents the next characters."ANSI_COLOR_RESET);
        } else {
            printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, so use \n\t      underscores or dashes to represents the next characters."ANSI_COLOR_RESET);
        }

        printf("\nSKYR Username: ");
        fgets(InputUsername, BUFSIZE07, stdin);

        if (strcmp(InputUsername, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

        while (strlen(InputUsername) <= 3 || strchr(InputUsername, ' ') != NULL) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your username at least a single word (min. 3 characters)!\n"ANSI_COLOR_RESET);
            printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, so use \n\t      underscores or dashes to represents the next characters."ANSI_COLOR_RESET);

            printf("\nSKYR Username: ");
            fgets(InputUsername, BUFSIZE07, stdin);

            if (strcmp(InputUsername, "...\n") == 0) AccountRegistrationMenu(ARMSelected);
        }
        
        InputUsername[strlen(InputUsername) - 1] = '\0';
        U = true;
        strcpy(ARMInputs.Username, InputUsername);
        InputUsername[0] = 0;
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 4) {
        ClearScreen();
        char InputPassword[BUFSIZE07], HiddenPassword[BUFSIZE07];
        Selecting = true;
        
        while (Selecting) {
            ClearScreen();

            if (!ARMShowThePassword) {
                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

                if (P) {
                    printf(ANSI_COLOR_LIGHTYELLOW"\t[SHOW: Press [>] key button] "ANSI_COLOR_RESET ANSI_COLOR_YELLOW"View Mode: Hiding the (unshown) hidden password...\n"ANSI_COLOR_RESET);
                    printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your password as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
                    printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
                    puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
                    puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters and a maximum 16 letters for better cautions \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with: \n\t\t    "ANSI_COLOR_RESET BRIGHTPURPLE218"an OPTIONAL RIGHT-KEY BUTTON [>], then press [ENTER] to confirm!"ANSI_COLOR_RESET);
                } else {
                    printf(ANSI_COLOR_LIGHTYELLOW"\t[SHOW: Press [>] key button] "ANSI_COLOR_RESET ANSI_COLOR_YELLOW"View Mode: Hiding the (unshown) hidden password...\n\n"ANSI_COLOR_RESET);
                    printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
                    puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
                    puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters and a maximum 16 letters for better cautions \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with: \n\t\t    "ANSI_COLOR_RESET BRIGHTPURPLE218"an OPTIONAL RIGHT-KEY BUTTON [>], then press [ENTER] to confirm!"ANSI_COLOR_RESET);
                }
            } else {
                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

                if (P) {
                    printf(ANSI_COLOR_LIGHTORANGE"\t[HIDE: Press [<] key button] "ANSI_COLOR_RESET ANSI_COLOR_ORANGE"View Mode: Showing the hidden password...\n"ANSI_COLOR_RESET);
                    printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your password as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs.Password);
                    printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ARMInputs.Password);
                    puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
                    puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters and a maximum 16 letters for better cautions \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with: \n\t\t    "ANSI_COLOR_RESET BRIGHTPURPLE218"an OPTIONAL RIGHT-KEY BUTTON [>], then press [ENTER] to confirm!"ANSI_COLOR_RESET);
                } else {
                    printf(ANSI_COLOR_LIGHTORANGE"\t[HIDE: Press [<] key button] "ANSI_COLOR_RESET ANSI_COLOR_ORANGE"View Mode: Showing the hidden password...\n\n"ANSI_COLOR_RESET);
                    printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ARMInputs.Password);
                    puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
                    puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters and a maximum 16 letters for better cautions \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with: \n\t\t    "ANSI_COLOR_RESET BRIGHTPURPLE218"an OPTIONAL RIGHT-KEY BUTTON [>], then press [ENTER] to confirm!"ANSI_COLOR_RESET);
                }
            }

            switch (AKDC = _getch()) {
                case KEY_LEFT:  ARMShowThePassword = false; break;
                case KEY_RIGHT: ARMShowThePassword = true;  break;
                case KEY_ENTER: Selecting = false;
                default: break;
            } if (Selecting) ClearScreen();

            fflush(stdin);
            (Updated) ? Updated = false : true;
        }

        // if (P) {
        //     printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your password as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs.HiddenPasswordShown);
        //     printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ARMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations you'd like to \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);
        // } else {
        //     printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ARMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations you'd like to \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);
        // }

        printf("\nSKYR Password: ");
        fgets(InputPassword, BUFSIZE07, stdin);

        if (strcmp(InputPassword, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

        while (strlen(InputPassword) <= 8 || strlen(InputPassword) > 16) {
            ClearScreen();

            if (!ARMShowThePassword) {
                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);
                printf(ANSI_COLOR_LIGHTYELLOW"\t[SHOW: Press [>] key button] "ANSI_COLOR_RESET ANSI_COLOR_YELLOW"View Mode: Hiding the (unshown) hidden password...\n"ANSI_COLOR_RESET);
                
                puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your password in any unique way possible (min. 8 characters)!\n"ANSI_COLOR_RESET);
                printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ((!ARMShowThePassword) ? ARMInputs.HiddenPasswordShown : ARMInputs.Password));
                puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
                puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters and a maximum 16 letters for better cautions \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with: \n\t\t    "ANSI_COLOR_RESET BRIGHTPURPLE218"an OPTIONAL RIGHT-KEY BUTTON [>], then press [ENTER] to confirm!"ANSI_COLOR_RESET);
            } else {
                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);
                printf(ANSI_COLOR_LIGHTORANGE"\t[HIDE: Press [<] key button] "ANSI_COLOR_RESET ANSI_COLOR_ORANGE"View Mode: Showing the hidden password...\n"ANSI_COLOR_RESET);
                
                puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your password in any unique way possible (min. 8 characters)!\n"ANSI_COLOR_RESET);
                printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ARMInputs.Password);
                puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
                puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters and a maximum 16 letters for better cautions \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with: \n\t\t    "ANSI_COLOR_RESET BRIGHTPURPLE218"an OPTIONAL RIGHT-KEY BUTTON [>], then press [ENTER] to confirm!"ANSI_COLOR_RESET);
            }

            printf("\nSKYR Password: ");
            fgets(InputPassword, BUFSIZE07, stdin);

            if (strcmp(InputPassword, "...\n") == 0) AccountRegistrationMenu(ARMSelected);
        }

        InputPassword[strlen(InputPassword) - 1] = '\0';
        P = true;

        for (int i = 0; (long long unsigned int)i < strlen(InputPassword); i++) {
            if (i == 0) { strcpy(HiddenPassword, "*"); }
            else        { strcat(HiddenPassword, "*"); }
        } strcpy(ARMInputs.Password, InputPassword);
        strcpy(ARMInputs.HiddenPasswordShown, HiddenPassword);
        InputPassword[0] = 0; HiddenPassword[0] = 0;
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 5) {
        ClearScreen();
        char   InputDateOfBirth[BUFSIZE07], InputDOBTemp[BUFSIZE07], NumericalPattern[BUFSIZE07];
        char   *TempDOBTempD, *TempDOBTempM, *TempDOBTempY, *DOBTempD, *DOBTempM, *DOBTempY;
        char   DaysOfWeek[7][BUFSIZE07]      = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        char   MonthsOfYear[12][BUFSIZE07]   = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        int    TimeCounterNumeric[12]        = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        int    DashesOccurences = 0;
        bool   EmptyDOBInput = false;
        size_t TempDate, TempMonth, TempYear, Day, Date, Month, Year;

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

        if (B) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your date of birth as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs.DateOfBirth);
            printf("      " ANSI_COLOR_LIGHTGREEN"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Date of Birth."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your date of birth profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The date of birth of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of date of birth format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);
        } else {
            printf("      " ANSI_COLOR_LIGHTYELLOW"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Date of Birth."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your date of birth profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The date of birth of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of date of birth format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);
        }

        printf("\nDate of Birth: ");
        fgets(InputDateOfBirth, BUFSIZE07, stdin);

        if (strcmp(InputDateOfBirth, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

        if (strlen(InputDateOfBirth) < 2) { EmptyDOBInput = true; }
        else {
            strcpy(InputDOBTemp, InputDateOfBirth);
            InputDOBTemp[strlen(InputDOBTemp) - 1] = '\0';
            DashesOccurences = FindOccurences(InputDOBTemp, '-');
            if (DashesOccurences == 2) {
                TempDOBTempD = strtok(InputDOBTemp, "-"); TempDOBTempM = strtok(NULL, "-"); TempDOBTempY = strtok(NULL, "-");
                TempDate = atoi(TempDOBTempD); TempMonth = atoi(TempDOBTempM); TempYear = atoi(TempDOBTempY);
            } EmptyDOBInput = false;
        }

        while (EmptyDOBInput || DashesOccurences != 2 || (((TempYear % 4) == 0 && (TempMonth == 2)) && TempDate > 29) || (((TempYear % 4) != 0 && (TempMonth == 2)) && TempDate > 28) || (TempDate < 1 || TempDate > 31) || (TempMonth < 1 || TempMonth > 12) || (TempYear < 1)) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your birth of date as what the pre-requisites requested for!\n"ANSI_COLOR_RESET);
            printf("      " ANSI_COLOR_LIGHTYELLOW"> Date of Birth:\t\t%s\n\t"ANSI_COLOR_RESET "Age on Present:\t\t%s\n\tPhone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Date of Birth."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your date of birth profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The date of birth of yours must be a valid format as written down below: \n\t      DATE-MONTH-YEAR (no spaces needed)! \n\t      The valid example of date of birth format's shown here: 1-1-2005 \n\n\t      <DATE>  must be a number from 1 to 31 (based of the total days in a spesific month). \n\t      <MONTH> must be a number from 1 to 12 (a number that represents the current month). \n\t      <YEAR>  must be a valid number up to the current (present time) year on a calender."ANSI_COLOR_RESET);

            printf("\nDate of Birth: ");
            fgets(InputDateOfBirth, BUFSIZE07, stdin);

            if (strcmp(InputDateOfBirth, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

            if (strlen(InputDateOfBirth) < 2) { EmptyDOBInput = true; }
            else {
                strcpy(InputDOBTemp, InputDateOfBirth);
                InputDOBTemp[strlen(InputDOBTemp) - 1] = '\0';
                DashesOccurences = FindOccurences(InputDOBTemp, '-');
                if (DashesOccurences == 2) {
                    TempDOBTempD = strtok(InputDOBTemp, "-"); TempDOBTempM = strtok(NULL, "-"); TempDOBTempY = strtok(NULL, "-");
                    TempDate = atoi(TempDOBTempD); TempMonth = atoi(TempDOBTempM); TempYear = atoi(TempDOBTempY);
                } EmptyDOBInput = false;
            }
        }
        
        InputDateOfBirth[strlen(InputDateOfBirth) - 1] = '\0';
        B = true;
        DOBTempD = strtok(InputDateOfBirth, "-"); DOBTempM = strtok(NULL, "-"); DOBTempY = strtok(NULL, "-");
        DOBTempD = TrimWhiteSpaces(DOBTempD); DOBTempM = TrimWhiteSpaces(DOBTempM); DOBTempY = TrimWhiteSpaces(DOBTempY);
        Date = atoi(DOBTempD); Month = atoi(DOBTempM); Year = atoi(DOBTempY);

        Year -= Month < 3;
        Day = (Year + (Year / 4) - (Year / 100) + (Year / 400) + TimeCounterNumeric[Month - 1] + Date) % 7;
        if (Date >= 11 && Date < 21)      { strcpy(NumericalPattern, "th"); }
        else {
            if (strlen(DOBTempD) < 2) {
                if      (DOBTempD[0] == '1') { strcpy(NumericalPattern, "st"); }
                else if (DOBTempD[0] == '2') { strcpy(NumericalPattern, "nd"); }
                else if (DOBTempD[0] == '3') { strcpy(NumericalPattern, "rd"); }
                else                         { strcpy(NumericalPattern, "th"); }
            } else {
                if      (DOBTempD[1] == '1') { strcpy(NumericalPattern, "st"); }
                else if (DOBTempD[1] == '2') { strcpy(NumericalPattern, "nd"); }
                else if (DOBTempD[1] == '3') { strcpy(NumericalPattern, "rd"); }
                else                         { strcpy(NumericalPattern, "th"); }
            }
        }

        strcpy(ARMInputs.DateOfBirth, DaysOfWeek[Day]);
        strcat(ARMInputs.DateOfBirth, ", ");
        strcat(ARMInputs.DateOfBirth, DOBTempD);
        strcat(ARMInputs.DateOfBirth, NumericalPattern);
        strcat(ARMInputs.DateOfBirth, " of ");
        strcat(ARMInputs.DateOfBirth, MonthsOfYear[Month - 1]);
        strcat(ARMInputs.DateOfBirth, " ");
        strcat(ARMInputs.DateOfBirth, DOBTempY);

        for (int i = 0; i < 7; i++)  { DaysOfWeek[i][0] = 0; }
        for (int j = 0; j < 12; j++) { MonthsOfYear[j][0] = 0; }
        NumericalPattern[0] = 0;
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 6) {
        if (!B) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);
            
            printf(ANSI_COLOR_LIGHTRED"\tWarning: Before inserting your present age in here, make sure to fill in your \n\t\t date of birth, considering that there'll be a checking if your present \n\t\t age is a valid!\n\n"ANSI_COLOR_RESET);
            printf(ANSI_COLOR_LIGHTORANGE"\tDate of Birth:\t\t(your birthdate)\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            printf(ANSI_COLOR_LIGHTMAGENTA"\n\tPlease proceed back to the registration menu by pressing your [ENTER] button \n\tkey on the keyboard. "ANSI_COLOR_RESET); getchar();
            AccountRegistrationMenu(ARMSelected);
        } ClearScreen();

        char   InputAgeOnPresent[4], StatedBirthDate[BUFSIZE07];
        char   *TempStatedBirthYear;
        size_t InputAOP, StatedBirthYear;
        
        strcpy(StatedBirthDate, ARMInputs.DateOfBirth);
        TempStatedBirthYear = strtok(StatedBirthDate, " ");
        TempStatedBirthYear = strtok(NULL, " "); TempStatedBirthYear = strtok(NULL, " ");
        TempStatedBirthYear = strtok(NULL, " "); TempStatedBirthYear = strtok(NULL, " ");

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

        if (A) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your present age as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs.AgeOnPresent);
            printf("\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Age on Present."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your present age profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The present age must be a rightful age as the same in your personal date of birth, and it will \n\t      be checked whether if your current age make up to your birth year until the current year \n\t      in the calendar system."ANSI_COLOR_RESET);
        } else {
            printf("\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Age on Present."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your present age profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The present age must be a rightful age as the same in your personal date of birth, and it will \n\t      be checked whether if your current age make up to your birth year until the current year \n\t      in the calendar system."ANSI_COLOR_RESET);
        }

        printf("\nAge on Present: ");
        fgets(InputAgeOnPresent, 4, stdin);
        
        if (strcmp(InputAgeOnPresent, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

        InputAOP        = atoi(InputAgeOnPresent);
        StatedBirthYear = atoi(TempStatedBirthYear);

        while (strlen(InputAgeOnPresent) < 1 || InputAOP < 13 || (StatedBirthYear + InputAOP != (long long unsigned int)(ManageTime.tm_year + 1900))) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your present age rightfully and honestly (min. 13 years old)!\n"ANSI_COLOR_RESET);
            printf("\tDate of Birth:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Age on Present:\t\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSex/Gender:\t\t%s\n", ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Age on Present."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your present age profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The present age must be a rightful age as the same in your personal date of birth, and it will \n\t      be checked whether if your current age make up to your birth year until the current year \n\t      in the calendar system."ANSI_COLOR_RESET);

            printf("\nAge on Present: ");
            fgets(InputAgeOnPresent, BUFSIZE07, stdin);
            
            if (strcmp(InputAgeOnPresent, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

            InputAOP        = atoi(InputAgeOnPresent);
            StatedBirthYear = atoi(TempStatedBirthYear);
        }
        
        InputAgeOnPresent[strlen(InputAgeOnPresent) - 1] = '\0';
        A = true;
        strcpy(ARMInputs.AgeOnPresent, InputAgeOnPresent);
        InputAgeOnPresent[0] = 0;
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 7) {
        ClearScreen();
        char InputPhoneNumber[BUFSIZE07], TempCountryCode[BUFSIZE07], TempDigitsNumber[BUFSIZE07], TempDigitsNumberTemp[BUFSIZE07], TempFinalPhoneNumber[BUFSIZE07];
        char *CountryCode, *DigitsNumber;

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

        if (PN) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your phone number as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs.PhoneNumber);
            printf("\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +[COUNTRYCODE, 1 to 3 DIGITS] [XXXXYYYYZZZZ, 4 to 13 DIGITS] \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);
        } else {
            printf("\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +[COUNTRYCODE, 1 to 3 DIGITS] [XXXXYYYYZZZZ, 4 to 13 DIGITS] \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);
        }

        printf("\nPhone Number: ");
        fgets(InputPhoneNumber, BUFSIZE07, stdin);

        if (strcmp(InputPhoneNumber, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

        InputPhoneNumber[strlen(InputPhoneNumber) - 1] = '\0';

        if (strlen(InputPhoneNumber) > 1 && strchr(InputPhoneNumber, '+') != NULL && strchr(InputPhoneNumber, ' ') != NULL && strlen(InputPhoneNumber) > 4) {
            strcpy(TempCountryCode, InputPhoneNumber);
            if (strchr(TempCountryCode, ' ') != NULL) {
                CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
                CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
            }
        } else {
            strcpy(InputPhoneNumber, "+0 0"); strcpy(TempCountryCode, InputPhoneNumber);
            if (strchr(TempCountryCode, ' ') != NULL) {
                CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
                CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
            }
        }

        while ((strlen(CountryCode) < 2 || strlen(CountryCode) > 4) || (strlen(DigitsNumber) < 4 || strlen(DigitsNumber) > 13) || CountryCode[0] != '+' || strchr(InputPhoneNumber, ' ') == NULL || (strchr(InputPhoneNumber, ' ') != NULL && FindOccurences(InputPhoneNumber, ' ') > 1) || strchr(InputPhoneNumber, '-') != NULL) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your with a starting phone country code and for at least 4 to 13 \n\t         digits (min. 4 digits), and make sure the SPACE count ONLY 1!\n\t         Lastly, please re-assure your inserted phone number DOESN'T CONSIST any of '-' (dashes)\n\t         numerical sign whatsoever!\n"ANSI_COLOR_RESET);
            printf("\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "Sex/Gender:\t\t%s\n", ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+ABC', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a SINGLE space, and for the digits you can \n\t      insert thoroughly (without spaces, dashes, or so). \n\n\t      Phone number format insertion: +[COUNTRYCODE, 1 to 3 DIGITS] [XXXXYYYYZZZZ, 4 to 13 DIGITS] \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);

            printf("\nPhone Number: ");
            fgets(InputPhoneNumber, BUFSIZE07, stdin);

            if (strcmp(InputPhoneNumber, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

            InputPhoneNumber[strlen(InputPhoneNumber) - 1] = '\0';

            if (strlen(InputPhoneNumber) > 1 && strchr(InputPhoneNumber, '+') != NULL && strchr(InputPhoneNumber, ' ') != NULL && strlen(InputPhoneNumber) > 4) {
                strcpy(TempCountryCode, InputPhoneNumber);
                if (strchr(TempCountryCode, ' ') != NULL) {
                    CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
                    CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
                }
            } else {
                strcpy(InputPhoneNumber, "+0 0"); strcpy(TempCountryCode, InputPhoneNumber);
                if (strchr(TempCountryCode, ' ') != NULL) {
                    CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
                    CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
                }
            }
        }
        
        InputPhoneNumber[strlen(InputPhoneNumber) - 1] = '\0';
        PN = true;

        strcpy(TempDigitsNumber, DigitsNumber);
        strcpy(TempFinalPhoneNumber, CountryCode);
        strcpy(TempDigitsNumberTemp, " ");
        for (int i = 1; (long long unsigned int)i <= strlen(TempDigitsNumber); i++) {
            if (i == 3)                        { strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); strcat(TempDigitsNumberTemp, "-"); }
            else if ((i % 4) == 0 && (i != 4)) { strcat(TempDigitsNumberTemp, "-"); strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); }
            else                               { strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); }
        } strcat(TempFinalPhoneNumber, TempDigitsNumberTemp);
        strcpy(ARMInputs.PhoneNumber, TempFinalPhoneNumber);
        
        TempDigitsNumber[0]     = 0;
        TempFinalPhoneNumber[0] = 0;
        TempDigitsNumberTemp[0] = 0;
        AccountRegistrationMenu(ARMSelected);
    }

    else if (ARMSelected == 8) {
        ClearScreen();
        char InputSex[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);

        if (S) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already asserted your sex as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then please don't be stupid enough to be confused.\n\n"ANSI_COLOR_RESET, ARMInputs.Sex);
            printf("\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Sex/Gender."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your biological sex (or not), into the profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: ONLY two (2) sexes that defines the human biology, and that is whether a \n\t      'Male' or a 'Female'. But nothing to worry, if you prefer not to say about it, \n\t      so just leave the input on blank."ANSI_COLOR_RESET);
        } else {
            printf("\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Sex/Gender."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your biological sex (or not), into the profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: ONLY two (2) sexes that defines the human biology, and that is whether a \n\t      'Male' or a 'Female'. But nothing to worry, if you prefer not to say about it, \n\t      so just leave the input on blank."ANSI_COLOR_RESET);
        }

        printf("\nSex/Gender: ");
        fgets(InputSex, BUFSIZE07, stdin);

        if (strcmp(InputSex, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

        if (strlen(InputSex) == 1) {
            S = true;
            strcpy(ARMInputs.Sex, "Prefer not to say...");
            AccountRegistrationMenu(ARMSelected);
        } strcpy(InputSex, StringUppercase(InputSex));
        InputSex[strlen(InputSex) - 1] = '\0';

        while (strcmp(InputSex, "MALE") != 0 && strcmp(InputSex, "FEMALE") != 0) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRegisterUI);
            
            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must assert your biological sex as either a 'Male' or 'Female' \n\t         (leave blank for prefering not to say)!\n"ANSI_COLOR_RESET);
            printf("\tDate of Birth:\t\t%s\n\tAge on Present:\t\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Sex/Gender:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.DateOfBirth, ARMInputs.AgeOnPresent, ARMInputs.PhoneNumber, ARMInputs.Sex);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Sex/Gender."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your biological sex (or not), into the profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: ONLY two (2) sexes that defines the human biology, and that is whether a \n\t      'Male' or a 'Female'. But nothing to worry, if you prefer not to say about it, \n\t      so just leave the input on blank."ANSI_COLOR_RESET);

            printf("\nSex/Gender: ");
            fgets(InputSex, BUFSIZE07, stdin);

            if (strcmp(InputSex, "...\n") == 0) AccountRegistrationMenu(ARMSelected);

            if (strlen(InputSex) == 1) {
                S = true;
                strcpy(ARMInputs.Sex, "Prefer not to say...");
                AccountRegistrationMenu(ARMSelected);
            } strcpy(InputSex, StringUppercase(InputSex));
            InputSex[strlen(InputSex) - 1] = '\0';
        }
        
        S = true;
        if (strcmp(InputSex, "M") == 0 || strcmp(InputSex, "MA") == 0 || strcmp(InputSex, "MAL") == 0 || strcmp(InputSex, "MALE") == 0) 
            { strcpy(InputSex, "Male"); }
        if (strcmp(InputSex, "F") == 0 || strcmp(InputSex, "FE") == 0 || strcmp(InputSex, "FEM") == 0 || strcmp(InputSex, "FEMA") == 0 || strcmp(InputSex, "FEMAL") == 0 || strcmp(InputSex, "FEMALE") == 0)
            { strcpy(InputSex, "Female"); }
        strcpy(ARMInputs.Sex, InputSex);
        InputSex[0] = 0;
        AccountRegistrationMenu(ARMSelected);
    }
}

void AccountLoginMenu(int ALMSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    FILE *FDestination, *FTempDestination;
    int BufLen, Ptr = 0, KeyTracker = 0;
    char FDBuffer[BUFSIZE16], DeleteTempDestinationTxtFile[BUFSIZE08], TxtFileName[BUFSIZE08] = "SKYR-FMSA-RegisteredAccounts.txt > First Name, Last Name, Personal E-mail, Phone Number, SKYR Username, SKYR Password";
    char *SourceKeyStringValue, *SelectedKeyString;
    char *SourceKeyStringValues[BUFSIZE07];

    int AvailableOptions = 4, SubmitOrContinue;
    int ExistingAccounts = 0;
    bool Selecting = true, Updated = false, FirstRun = true;
    bool ALMUpgrade = false;

    int PreviousAKDC = 0;
    bool CatchDefaultAKDC = false;

    char AKDC;
    char MessageID05[BUFSIZE10], MessageID06[BUFSIZE10], MessageID07[BUFSIZE10];
    char TempCountSKYRFMSARegisteredAccounts[BUFSIZE10], *CountSKYRFMSARegisteredAccounts;

    if (access("SKYR-FMSA-RegisteredAccounts.txt", F_OK) != 0 && !FlagALM) { GlobalSKYRFMSARegisteredAccounts = 0; }
    else if (access("SKYR-FMSA-RegisteredAccounts.txt", F_OK) == 0 && !FlagALM) {
        FDestination     = fopen("SKYR-FMSA-RegisteredAccounts.txt", "r");
        FTempDestination = fopen("TempDestination.txt", "w");

        while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
            BufLen = strlen(FDBuffer);
            for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
            fputs(FDBuffer, FTempDestination);
        } fclose(FDestination); fclose(FTempDestination);

        strtok_r(TxtFileName, ">", &SelectedKeyString);
        SelectedKeyString = TrimWhiteSpaces(SelectedKeyString);
        SourceKeyStringValue = strtok(SelectedKeyString, ",");
        KeyTracker++;

        while (SourceKeyStringValue != NULL) {
            SourceKeyStringValues[Ptr] = SourceKeyStringValue;
            SourceKeyStringValues[Ptr] = TrimWhiteSpaces(SourceKeyStringValues[Ptr]);
            SourceKeyStringValue = strtok(NULL, ",");
            Ptr++; KeyTracker++;
        } // SourceTextFileName = TrimWhiteSpaces(TxtFileName);
        
        strcpy(TempCountSKYRFMSARegisteredAccounts, ReadAndPrintLine("TempDestination.txt", 9));

        strcpy(DeleteTempDestinationTxtFile, "del ");
        strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
        system(DeleteTempDestinationTxtFile);

        TempCountSKYRFMSARegisteredAccounts[strlen(TempCountSKYRFMSARegisteredAccounts) - 1] = '\0';
        strtok_r(TempCountSKYRFMSARegisteredAccounts, ":", &CountSKYRFMSARegisteredAccounts);
        
        CountSKYRFMSARegisteredAccounts = TrimWhiteSpaces(CountSKYRFMSARegisteredAccounts);
        CountSKYRFMSARegisteredAccounts = strtok(CountSKYRFMSARegisteredAccounts, " ");
        ExistingAccounts = atoi(CountSKYRFMSARegisteredAccounts);

        if (!SKYRApplicationRunning) { GlobalSKYRFMSARegisteredAccounts += ExistingAccounts; }
        else { GlobalSKYRFMSARegisteredAccounts++; }; 
        FlagALM = true;
    }

    SKYRApplicationRunning = true;
    if ((LE && LPN && LU && LP) && !ALMUpgrade && !ALMNotificationEnabled_02) {
        InfoMessageBox_OK("(Info) @SKYR-PFMSA; Login Menu Upgraded", "All right, new starters! Here now we've upgraded the Login Menu UI, and now you can just keep going UPWARDS or DOWNWARDS until you see a complete different UI, making sure that you're ready to be logged in into this application!");
        ALMNotificationEnabled_02 = true;
    }

    if ((LE && LPN && LU && LP) && !ALMUpgrade) {
        AvailableOptions += 1; ALMUpgrade = true;
    }

    if (strlen(FullName) != 0 && strlen(UserName) != 0) {
        InfoMessageBox_OK("(Info): @SKYR-PFMSA; Account's Still Logged In", "We've detected that you're still logged into your current account (with the details on your terminal afterwards), so please logged out from your account first, then you may hop into login another account you had on the registered accounts list.");

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);
        printf(BRIGHTGREEN156"\tInfo: We checked that you're still logged into an account as:\n\t      "ANSI_COLOR_RESET BRIGHTBLUE158 ANSI_STYLE_BOLD"Full Name: %s\n\t      "ANSI_COLOR_RESET BRIGHTBLUE159 ANSI_STYLE_BOLD"Username:  %s\n"ANSI_COLOR_RESET, FullName, UserName);
        puts(BRIGHTPINK219 ANSI_STYLE_BOLD"\n\tNote: Consider to signing out from this account first before continuing to signing in into another \n\t      account you've registered beforehand!\n");
        printf(ANSI_COLOR_MAGENTA ANSI_STYLE_ITALIC"\t[ENTER] Proceed to go back to the profile managing menu in the main menu... ");
        
        getchar();
        MainMenuProfileManager(MMPMSelected);
    }

    if (!ALMNotificationEnabled_01) { InfoMessageBox_OK("(Info) @SKYR-PFMSA; Importance of The Safety Profile Account", "For the safety purposes while you're going registrating a new account, or when trying to logged into the application, or even when you're going to recover of your missing account,\n\n\tWE ARE GOING TO DEPLETED EVERY INPUT YOU'VE PROGRESSED SO FAR, SO PLEASE JUST STAY IN ONE UI MENU;\n\nIn order to be save and more secure, so don't blame us when you're missing on your inputs after switching to different UIs... ."); ALMNotificationEnabled_01 = true; }

    while (Selecting) {
        if (!FirstRun) {
        /*  Separated by one line to another, handling ONLY THREE (3) rows each parts.
        >   Personal E-mail, SKYR Username, SKYR Password
        */
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);
        if (CatchDefaultAKDC) printf(ANSI_COLOR_LIGHTRED"\tError: The auto-enter shortcut key labeled as '%c' (ID: 0x%02X) is not registered at the moment!\n\n"ANSI_COLOR_RESET, ((int)PreviousAKDC != 12) ? (char)PreviousAKDC : 10, (int)PreviousAKDC);

        if ((ALMSelected + 1) > 0 && (ALMSelected + 1) <= 4 && (AvailableOptions == 4)) {
            if ((ALMSelected + 1) == 1) {
                if (!LE)  { printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                else      { printf("      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
            } else if ((ALMSelected + 1) == 2) {
                if (!LPN) { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                else      { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
            } else if ((ALMSelected + 1) == 3) {
                if (!LU)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
            } else if ((ALMSelected + 1) == 4) {
                if (!LP)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
            }

            (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\n\n\n\t%s", AppLoginUDRL) : printf("\n\n\n\n\n\n\n\n\t%s", AppLoginUDRL);
        }
        
        else if ((ALMSelected + 1) > 0 && (ALMSelected + 1) <= 5 && (AvailableOptions == 5)) {
            if ((ALMSelected + 1) == 1) {
                if (!LE)  { printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                else      { printf("      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
            } else if ((ALMSelected + 1) == 2) {
                if (!LPN) { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                else      { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
            } else if ((ALMSelected + 1) == 3) {
                if (!LU)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
            } else if ((ALMSelected + 1) == 4) {
                if (!LP)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
            }
            
            (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\n\n\n\t%s", AppLoginUDRL) : printf("\n\n\n\n\n\n\n\n\t%s", AppLoginUDRL);
            
            if ((ALMSelected + 1) == 5) {
                ClearScreen();
                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

                printf("\tInfo: You've completed inserting the required main data about your profile  \n\t      account, and now you're ready to login into your account.\n");
                printf(ANSI_COLOR_BLUE"\n\tProceed to give a rightful checking on your inserted profile data \n\tright here and there before get logged in? \n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"Account to be linked: %s\n\n"ANSI_COLOR_RESET, ALMInputs.Email);
                
                snprintf(MessageID05, BUFSIZE10, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);
                snprintf(MessageID06, BUFSIZE10, "\tInfo: You've completed inserting the required main data about your profile  \n\t      account, and now you're ready to login into your account.");
                snprintf(MessageID07, BUFSIZE10, ANSI_COLOR_BLUE"\n\tProceed to give a rightful checking on your inserted profile data \n\tright here and there before get logged in? \n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"Account to be linked: %s\n"ANSI_COLOR_RESET, ALMInputs.Email);
                MessagesShown_ArrowKeyChoiceDialog[5] = MessageID05;
                MessagesShown_ArrowKeyChoiceDialog[6] = MessageID06;
                MessagesShown_ArrowKeyChoiceDialog[7] = MessageID07;
                SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 5, 8);

                if (SubmitOrContinue) {
                    FDestination     = fopen("SKYR-FMSA-RegisteredAccounts.txt", "r");
                    FTempDestination = fopen("TempDestination.txt", "w");

                    while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
                        BufLen = strlen(FDBuffer);
                        for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                        fputs(FDBuffer, FTempDestination);
                    } fclose(FDestination); fclose(FTempDestination);
                    
                    for (int GRA = 1; (long long unsigned int)GRA <= GlobalSKYRFMSARegisteredAccounts; GRA++) {
                        strncpy(FirstName,    ReadAndPrintLine("TempDestination.txt", 0 + (14 * GRA)), BUFSIZE07);
                        strncpy(LastName,     ReadAndPrintLine("TempDestination.txt", 1 + (14 * GRA)), BUFSIZE07);
                        strncpy(Email,        ReadAndPrintLine("TempDestination.txt", 2 + (14 * GRA)), BUFSIZE07);
                        strncpy(Username,     ReadAndPrintLine("TempDestination.txt", 3 + (14 * GRA)), BUFSIZE07);
                        strncpy(Password,     ReadAndPrintLine("TempDestination.txt", 4 + (14 * GRA)), BUFSIZE07);
                        strncpy(DateOfBirth,  ReadAndPrintLine("TempDestination.txt", 6 + (14 * GRA)), BUFSIZE07);
                        strncpy(AgeOnPresent, ReadAndPrintLine("TempDestination.txt", 7 + (14 * GRA)), BUFSIZE07);
                        strncpy(PhoneNumber,  ReadAndPrintLine("TempDestination.txt", 8 + (14 * GRA)), BUFSIZE07);
                        strncpy(Sex,          ReadAndPrintLine("TempDestination.txt", 9 + (14 * GRA)), BUFSIZE07);

                        FirstName[strlen(FirstName) - 1] = '\0'; LastName[strlen(LastName) - 1] = '\0';
                        Email[strlen(Email) - 1] = '\0'; Username[strlen(Username) - 1] = '\0'; Password[strlen(Password) - 1] = '\0';
                        DateOfBirth[strlen(DateOfBirth) - 1] = '\0'; AgeOnPresent[strlen(AgeOnPresent) - 1] = '\0';
                        PhoneNumber[strlen(PhoneNumber) - 1] = '\0'; Sex[strlen(Sex) - 1] = '\0';
                        strtok_r(FirstName, ":", &ShowFirstName);       ShowFirstName = TrimWhiteSpaces(ShowFirstName);
                        strtok_r(LastName, ":", &ShowLastName);         ShowLastName = TrimWhiteSpaces(ShowLastName);
                        strtok_r(Email, ":", &ShowEmail);               ShowEmail = TrimWhiteSpaces(ShowEmail);
                        strtok_r(Username, ":", &ShowUsername);         ShowUsername = TrimWhiteSpaces(ShowUsername);
                        strtok_r(Password, ":", &ShowPassword);         ShowPassword = TrimWhiteSpaces(ShowPassword);
                        strtok_r(DateOfBirth, ":", &ShowDateOfBirth);   ShowDateOfBirth = TrimWhiteSpaces(ShowDateOfBirth);
                        strtok_r(AgeOnPresent, ":", &ShowAgeOnPresent); ShowAgeOnPresent = TrimWhiteSpaces(ShowAgeOnPresent);
                        strtok_r(PhoneNumber, ":", &ShowPhoneNumber);   ShowPhoneNumber = TrimWhiteSpaces(ShowPhoneNumber);
                        strtok_r(Sex, ":", &ShowSex);                   ShowSex = TrimWhiteSpaces(ShowSex);

                        if ((strcmp(ShowEmail, ALMInputs.Email)             == 0) && \
                            (strcmp(ShowPhoneNumber, ALMInputs.PhoneNumber) == 0) && \
                            (strcmp(ShowUsername, ALMInputs.Username)       == 0) && \
                            (strcmp(ShowPassword, ALMInputs.Password)       == 0)) {   
                                strcpy(DeleteTempDestinationTxtFile, "del ");
                                strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
                                system(DeleteTempDestinationTxtFile);

                                ClearScreen();
                                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

                                puts(ANSI_COLOR_LIGHTBLUE"\tNote: You've successfully logged into your profile account!"ANSI_COLOR_RESET);
                                puts(ANSI_COLOR_LIGHTBLUE"\tWelcome to: Personal Financial Management System [CLI-Win32] Application!"ANSI_COLOR_RESET);
                                printf(ANSI_COLOR_LIGHTGREEN"\n\tLogged in as: \n\t          >>  %s %s.\n\t              "ANSI_COLOR_RESET ANSI_COLOR_GREEN"(Account No. %d)\n\n"ANSI_COLOR_RESET, ShowFirstName, ShowLastName, GRA);
                                puts(ANSI_COLOR_LIGHTMAGENTA"\tNow you may proceed to the main menu by pressing the [ENTER] button key on \n\tyour keyboard right away."ANSI_COLOR_RESET);

                                GlobalAccount = GRA;
                                getchar();

                                strcpy(FullName, ShowFirstName); strcat(FullName, " "); strcat(FullName, ShowLastName);
                                strcpy(UserName, ShowUsername);
                                strcpy(ProfileSaveFileData, UserName); strcat(ProfileSaveFileData, "-SaveFile.txt");
                                SaveDataInTxtFile(ProfileSaveFileData, EncryptionKey, false);
                                MainMenuApplicationFeatures(0);
                            } else {
                                FirstName[0] = 0; LastName[0] = 0, Email[0] = 0, Username[0] = 0, Password[0] = 0;
                                DateOfBirth[0] = 0, AgeOnPresent[0] = 0; PhoneNumber[0] = 0, Sex[0] = 0;
                                
                                strcpy(DeleteTempDestinationTxtFile, "del ");
                                strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
                                system(DeleteTempDestinationTxtFile);

                                ClearScreen();
                                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);
                                
                                puts(ANSI_COLOR_LIGHTRED"\tError: We checked that it seems like one or more inserted profile account(s) you \n\t       provide before isn't validating the same as the original registered \n\t       profile account(s) of yours that you're trying to logged in as by now.\n"ANSI_COLOR_RESET ANSI_COLOR_LIGHTYELLOW"\n\tConsider to re-check your logged in profile data and make sure that if you forget \n\tsomething, then you may to look for a recovery account by tapping [9] button \n\tkey on your keyboard, then proceed to fulfill-in important things afterwards.\n"ANSI_COLOR_RESET);
                                getchar();
                                ALMSelected = 0; AccountLoginMenu(ALMSelected);
                            }
                        }
                    } else { ALMSelected = 0; AccountLoginMenu(ALMSelected); }
                }
            }

        } else {
            FirstRun = false;
            
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);
            if (CatchDefaultAKDC) printf(ANSI_COLOR_LIGHTRED"\tError: The auto-enter shortcut key labeled as '%c' (ID: 0x%02X) is not registered at the moment!\n\n"ANSI_COLOR_RESET, ((int)PreviousAKDC != 12) ? (char)PreviousAKDC : 10, (int)PreviousAKDC);

            if ((ALMSelected + 1) > 0 && (ALMSelected + 1) <= 4 && (AvailableOptions == 4)) {
                if ((ALMSelected + 1) == 1) {
                    if (!LE)  { printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                    else      { printf("      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                } else if ((ALMSelected + 1) == 2) {
                    if (!LPN) { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                    else      { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                } else if ((ALMSelected + 1) == 3) {
                    if (!LU)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                    else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                } else if ((ALMSelected + 1) == 4) {
                    if (!LP)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                    else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                }

                (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\n\n\n\t%s", AppLoginUDRL) : printf("\n\n\n\n\n\n\n\n\t%s", AppLoginUDRL);
            }
            
            else if ((ALMSelected + 1) > 0 && (ALMSelected + 1) <= 5 && (AvailableOptions == 5)) {
                if ((ALMSelected + 1) == 1) {
                    if (!LE)  { printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                    else      { printf("      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                } else if ((ALMSelected + 1) == 2) {
                    if (!LPN) { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                    else      { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                } else if ((ALMSelected + 1) == 3) {
                    if (!LU)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                    else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                } else if ((ALMSelected + 1) == 4) {
                    if (!LP)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                    else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password); }
                }
                
                (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\n\n\n\t%s", AppLoginUDRL) : printf("\n\n\n\n\n\n\n\t%s", AppLoginUDRL);
                
                if ((ALMSelected + 1) == 5) {
                    ClearScreen();
                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

                    printf("\tInfo: You've completed inserting the required main data about your profile  \n\t      account, and now you're ready to login into your account.\n");
                    printf(ANSI_COLOR_BLUE"\n\tProceed to give a rightful checking on your inserted profile data \n\tright here and there before get logged in? \n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"Account to be linked: %s\n\n"ANSI_COLOR_RESET, ALMInputs.Email);
                    
                    snprintf(MessageID05, BUFSIZE10, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);
                    snprintf(MessageID06, BUFSIZE10, "\tInfo: You've completed inserting the required main data about your profile  \n\t      account, and now you're ready to login into your account.");
                    snprintf(MessageID07, BUFSIZE10, ANSI_COLOR_BLUE"\n\tProceed to give a rightful checking on your inserted profile data \n\tright here and there before get logged in? \n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTCYAN"Account to be linked: %s\n"ANSI_COLOR_RESET, ALMInputs.Email);
                    MessagesShown_ArrowKeyChoiceDialog[5] = MessageID05;
                    MessagesShown_ArrowKeyChoiceDialog[6] = MessageID06;
                    MessagesShown_ArrowKeyChoiceDialog[7] = MessageID07;
                    SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 5, 8);

                    if (SubmitOrContinue) {
                        FDestination     = fopen("SKYR-FMSA-RegisteredAccounts.txt", "r");
                        FTempDestination = fopen("TempDestination.txt", "w");

                        while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
                            BufLen = strlen(FDBuffer);
                            for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                            fputs(FDBuffer, FTempDestination);
                        } fclose(FDestination); fclose(FTempDestination);
                        
                        for (int GRA = 1; (long long unsigned int)GRA <= GlobalSKYRFMSARegisteredAccounts; GRA++) {
                            strncpy(FirstName,    ReadAndPrintLine("TempDestination.txt", 0 + (14 * GRA)), BUFSIZE07);
                            strncpy(LastName,     ReadAndPrintLine("TempDestination.txt", 1 + (14 * GRA)), BUFSIZE07);
                            strncpy(Email,        ReadAndPrintLine("TempDestination.txt", 2 + (14 * GRA)), BUFSIZE07);
                            strncpy(Username,     ReadAndPrintLine("TempDestination.txt", 3 + (14 * GRA)), BUFSIZE07);
                            strncpy(Password,     ReadAndPrintLine("TempDestination.txt", 4 + (14 * GRA)), BUFSIZE07);
                            strncpy(DateOfBirth,  ReadAndPrintLine("TempDestination.txt", 6 + (14 * GRA)), BUFSIZE07);
                            strncpy(AgeOnPresent, ReadAndPrintLine("TempDestination.txt", 7 + (14 * GRA)), BUFSIZE07);
                            strncpy(PhoneNumber,  ReadAndPrintLine("TempDestination.txt", 8 + (14 * GRA)), BUFSIZE07);
                            strncpy(Sex,          ReadAndPrintLine("TempDestination.txt", 9 + (14 * GRA)), BUFSIZE07);

                            FirstName[strlen(FirstName) - 1] = '\0'; LastName[strlen(LastName) - 1] = '\0';
                            Email[strlen(Email) - 1] = '\0'; Username[strlen(Username) - 1] = '\0'; Password[strlen(Password) - 1] = '\0';
                            DateOfBirth[strlen(DateOfBirth) - 1] = '\0'; AgeOnPresent[strlen(AgeOnPresent) - 1] = '\0';
                            PhoneNumber[strlen(PhoneNumber) - 1] = '\0'; Sex[strlen(Sex) - 1] = '\0';
                            strtok_r(FirstName, ":", &ShowFirstName);       ShowFirstName = TrimWhiteSpaces(ShowFirstName);
                            strtok_r(LastName, ":", &ShowLastName);         ShowLastName = TrimWhiteSpaces(ShowLastName);
                            strtok_r(Email, ":", &ShowEmail);               ShowEmail = TrimWhiteSpaces(ShowEmail);
                            strtok_r(Username, ":", &ShowUsername);         ShowUsername = TrimWhiteSpaces(ShowUsername);
                            strtok_r(Password, ":", &ShowPassword);         ShowPassword = TrimWhiteSpaces(ShowPassword);
                            strtok_r(DateOfBirth, ":", &ShowDateOfBirth);   ShowDateOfBirth = TrimWhiteSpaces(ShowDateOfBirth);
                            strtok_r(AgeOnPresent, ":", &ShowAgeOnPresent); ShowAgeOnPresent = TrimWhiteSpaces(ShowAgeOnPresent);
                            strtok_r(PhoneNumber, ":", &ShowPhoneNumber);   ShowPhoneNumber = TrimWhiteSpaces(ShowPhoneNumber);
                            strtok_r(Sex, ":", &ShowSex);                   ShowSex = TrimWhiteSpaces(ShowSex);

                            if ((strcmp(ShowEmail, ALMInputs.Email)             == 0) && \
                                (strcmp(ShowPhoneNumber, ALMInputs.PhoneNumber) == 0) && \
                                (strcmp(ShowUsername, ALMInputs.Username)       == 0) && \
                                (strcmp(ShowPassword, ALMInputs.Password)       == 0)) {   
                                    strcpy(DeleteTempDestinationTxtFile, "del ");
                                    strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
                                    system(DeleteTempDestinationTxtFile);

                                    ClearScreen();
                                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

                                    puts(ANSI_COLOR_LIGHTBLUE"\tNote: You've successfully logged into your profile account!"ANSI_COLOR_RESET);
                                    puts(ANSI_COLOR_LIGHTBLUE"\tWelcome to: Personal Financial Management System [CLI-Win32] Application!"ANSI_COLOR_RESET);
                                    printf(ANSI_COLOR_LIGHTGREEN"\n\tLogged in as: \n\t          >>  %s %s.\n\t              "ANSI_COLOR_RESET ANSI_COLOR_GREEN"(Account No. %d)\n\n"ANSI_COLOR_RESET, ShowFirstName, ShowLastName, GRA);
                                    puts(ANSI_COLOR_LIGHTMAGENTA"\tNow you may proceed to the main menu by pressing the [ENTER] button key on \n\tyour keyboard right away."ANSI_COLOR_RESET);

                                    GlobalAccount = GRA;
                                    getchar();

                                    strcpy(FullName, ShowFirstName); strcat(FullName, " "); strcat(FullName, ShowLastName);
                                    strcpy(UserName, ShowUsername);
                                    strcpy(ProfileSaveFileData, UserName); strcat(ProfileSaveFileData, "-SaveFile.txt");
                                    SaveDataInTxtFile(ProfileSaveFileData, EncryptionKey, false);
                                    MainMenuApplicationFeatures(0);
                                } else {
                                    FirstName[0] = 0; LastName[0] = 0, Email[0] = 0, Username[0] = 0, Password[0] = 0;
                                    DateOfBirth[0] = 0, AgeOnPresent[0] = 0; PhoneNumber[0] = 0, Sex[0] = 0;

                                    strcpy(DeleteTempDestinationTxtFile, "del ");
                                    strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
                                    system(DeleteTempDestinationTxtFile);

                                    ClearScreen();
                                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);
                                    
                                    puts(ANSI_COLOR_LIGHTRED"\tError: We checked that it seems like one or more inserted profile account(s) you \n\t       provide before isn't validating the same as the original registered \n\t       profile account(s) of yours that you're trying to logged in as by now.\n"ANSI_COLOR_RESET ANSI_COLOR_LIGHTYELLOW"\n\tConsider to re-check your logged in profile data and make sure that if you forget \n\tsomething, then you may to look for a recovery account by tapping [9] button \n\tkey on your keyboard, then proceed to fulfill-in important things afterwards.\n"ANSI_COLOR_RESET);
                                    getchar();
                                    ALMSelected = 0; AccountLoginMenu(ALMSelected);
                                }
                            }
                        } else { ALMSelected = 0; AccountLoginMenu(ALMSelected);
                    }
                }
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                if (ALMSelected > 0 && ALMSelected < AvailableOptions) {
                    --ALMSelected; Updated = true;
                } else if (ALMSelected <= 0) {
                    ALMSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                if (ALMSelected >= 0 && ALMSelected < AvailableOptions - 1) {
                    ++ALMSelected; Updated = true;
                } else if (ALMSelected >= AvailableOptions - 1) {
                    ALMSelected = 0; Updated = true;
                } break;
            case KEY_RIGHT:
                PreviousAKDC = 0; CatchDefaultAKDC = false;

                ALMInputs.Email[0] = 0;
                ALMInputs.PhoneNumber[0] = 0;
                ALMInputs.Username[0] = 0;
                ALMInputs.Password[0] = 0;
                ALMInputs.HiddenPasswordShown[0] = 0;
                LE = false; LPN = false; LU = false; LP = false;

                AccountRecoveryMenu(0);
                break;
            case KEY_LEFT:
                PreviousAKDC = 0; CatchDefaultAKDC = false;

                ALMInputs.Email[0] = 0;
                ALMInputs.PhoneNumber[0] = 0;
                ALMInputs.Username[0] = 0;
                ALMInputs.Password[0] = 0;
                ALMInputs.HiddenPasswordShown[0] = 0;
                LE = false; LPN = false; LU = false; LP = false;

                AccountRegistrationMenu(0);
                break;
            case '1': ALMSelected = 0; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '2': ALMSelected = 1; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '3': ALMSelected = 2; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '4': ALMSelected = 3; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            default: {
                if (AKDC == KEY_UP || AKDC == KEY_DOWN || AKDC == KEY_LEFT || AKDC == KEY_RIGHT || AKDC == KEY_ENTER) { ClearScreen(); continue; }
                (AKDC > 0) ? PreviousAKDC = (int)AKDC : 0;
                (AKDC > 0) ? CatchDefaultAKDC = true : false;
            } break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    }

    if (ALMSelected == 0) {
        // ClearScreen();
        // char InputEmail[BUFSIZE07];

        // printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

        // if (LE) {
        //     printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your personal e-mail as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ALMInputs.Email);
        //     printf("      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating \n\t      your own e-mail."ANSI_COLOR_RESET);
        // } else {
        //     printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating \n\t      your own e-mail."ANSI_COLOR_RESET);
        // }

        // printf("\nPersonal E-mail: ");
        // fgets(InputEmail, BUFSIZE07, stdin);

        // if (strcmp(InputEmail, "...\n") == 0) AccountLoginMenu(ALMSelected);

        // while (strlen(InputEmail) <= 3 || strchr(InputEmail, '@') == NULL || strchr(InputEmail, '.') == NULL) {
        //     ClearScreen();
        //     printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

        //     puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your last name at least a single word (min. 3 characters)!\n\t         The valid E-mail format must have a '@' symbol, and the provider (authorized by) \n\t         with the domain itself.\n"ANSI_COLOR_RESET);
        //     printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating \n\t      your own e-mail."ANSI_COLOR_RESET);

        //     printf("\nPersonal E-mail: ");
        //     fgets(InputEmail, BUFSIZE07, stdin);

        //     if (strcmp(InputEmail, "...\n") == 0) AccountLoginMenu(ALMSelected);
        // }
        
        // InputEmail[strlen(InputEmail) - 1] = '\0';
        // LE = true;
        // strcpy(ALMInputs.Email, InputEmail);
        // InputEmail[0] = 0;
        // AccountLoginMenu(ALMSelected);

        ClearScreen();
        char InputEmail[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

        if (LE) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your personal e-mail as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ALMInputs.Email);
            printf("      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating your own \n\t      e-mail, and make sure that NO SPACES in your inserted e-mail!"ANSI_COLOR_RESET);
        } else {
            printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating your own \n\t      e-mail, and make sure that NO SPACES in your inserted e-mail!"ANSI_COLOR_RESET);
        }

        printf("\nPersonal E-mail: ");
        fgets(InputEmail, BUFSIZE07, stdin);

        if (strcmp(InputEmail, "...\n") == 0) AccountLoginMenu(ARMSelected);

        while (strlen(InputEmail) <= 3 || strchr(InputEmail, '@') == NULL || strchr(InputEmail, '.') == NULL || strchr(InputEmail, ' ') != NULL || FindOccurences(InputEmail, '@') > 2 || FindOccurences(InputEmail, '.') > 2) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your last name at least a single word (min. 3 characters)!\n\t         The valid E-mail format must have a '@' symbol, and the provider (authorized by) \n\t         with the domain itself (NO SPACES are allowed either)!\n"ANSI_COLOR_RESET);
            printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating your own \n\t      e-mail, and make sure that NO SPACES in your inserted e-mail!"ANSI_COLOR_RESET);

            printf("\nPersonal E-mail: ");
            fgets(InputEmail, BUFSIZE07, stdin);

            if (strcmp(InputEmail, "...\n") == 0) AccountLoginMenu(ARMSelected);
        }
        
        InputEmail[strlen(InputEmail) - 1] = '\0';
        LE = true;
        strcpy(ALMInputs.Email, InputEmail);
        InputEmail[0] = 0;
        AccountLoginMenu(ALMSelected);
    }

    else if (ALMSelected == 1) {
        // ClearScreen();
        // char InputPhoneNumber[BUFSIZE07], TempCountryCode[BUFSIZE07], TempDigitsNumber[BUFSIZE07], TempDigitsNumberTemp[BUFSIZE07], TempFinalPhoneNumber[BUFSIZE07];
        // char *CountryCode, *DigitsNumber;

        // printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

        // if (LPN) {
        //     printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your phone number as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ALMInputs.PhoneNumber);
        //     printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +[COUNTRYCODE, 1 to 3 DIGITS] [XXXXYYYYZZZZ, 4 to 13 DIGITS] \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);
        // } else {
        //     printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +[COUNTRYCODE, 1 to 3 DIGITS] [XXXXYYYYZZZZ, 4 to 13 DIGITS] \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);
        // }

        // printf("\nPhone Number: ");
        // fgets(InputPhoneNumber, BUFSIZE07, stdin);

        // if (strcmp(InputPhoneNumber, "...\n") == 0) AccountLoginMenu(ALMSelected);

        // InputPhoneNumber[strlen(InputPhoneNumber) - 1] = '\0';

        // if (strlen(InputPhoneNumber) > 1 && strchr(InputPhoneNumber, '+') != NULL && strchr(InputPhoneNumber, ' ') != NULL && strlen(InputPhoneNumber) > 4) {
        //     strcpy(TempCountryCode, InputPhoneNumber);
        //     if (strchr(TempCountryCode, ' ') != NULL) {
        //         CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
        //         CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
        //     }
        // } else {
        //     strcpy(InputPhoneNumber, "+0 0"); strcpy(TempCountryCode, InputPhoneNumber);
        //     if (strchr(TempCountryCode, ' ') != NULL) {
        //         CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
        //         CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
        //     }
        // }

        // while ((strlen(DigitsNumber) <= 4 || strlen(DigitsNumber) > 13) || CountryCode[0] != '+' || strchr(InputPhoneNumber, ' ') == NULL) {
        //     ClearScreen();
        //     printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

        //     puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your with a starting phone country code and \n\t         for at least 4 to 13 digits (min. 4 digits)!\n"ANSI_COLOR_RESET);
        //     printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +[COUNTRYCODE, 1 to 3 DIGITS] [XXXXYYYYZZZZ, 4 to 13 DIGITS] \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);

        //     printf("\nPhone Number: ");
        //     fgets(InputPhoneNumber, BUFSIZE07, stdin);

        //     if (strcmp(InputPhoneNumber, "...\n") == 0) AccountLoginMenu(ALMSelected);

        //     InputPhoneNumber[strlen(InputPhoneNumber) - 1] = '\0';

        //     if (strlen(InputPhoneNumber) > 1 && strchr(InputPhoneNumber, '+') != NULL && strchr(InputPhoneNumber, ' ') != NULL && strlen(InputPhoneNumber) > 4) {
        //         strcpy(TempCountryCode, InputPhoneNumber);
        //         if (strchr(TempCountryCode, ' ') != NULL) {
        //             CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
        //             CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
        //         }
        //     } else {
        //         strcpy(InputPhoneNumber, "+0 0"); strcpy(TempCountryCode, InputPhoneNumber);
        //         if (strchr(TempCountryCode, ' ') != NULL) {
        //             CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
        //             CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
        //         }
        //     }
        // }
        
        // InputPhoneNumber[strlen(InputPhoneNumber) - 1] = '\0';
        // LPN = true;

        // strcpy(TempDigitsNumber, DigitsNumber);
        // strcpy(TempFinalPhoneNumber, CountryCode);
        // strcpy(TempDigitsNumberTemp, " ");
        // for (int i = 1; (long long unsigned int)i <= strlen(TempDigitsNumber); i++) {
        //     if (i == 3)                        { strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); strcat(TempDigitsNumberTemp, "-"); }
        //     else if ((i % 4) == 0 && (i != 4)) { strcat(TempDigitsNumberTemp, "-"); strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); }
        //     else                               { strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); }
        // } strcat(TempFinalPhoneNumber, TempDigitsNumberTemp);
        // strcpy(ALMInputs.PhoneNumber, TempFinalPhoneNumber);
        
        // TempDigitsNumber[0] = 0;
        // TempFinalPhoneNumber[0] = 0;
        // TempDigitsNumberTemp[0] = 0;
        // AccountLoginMenu(ALMSelected);

        ClearScreen();
        char InputPhoneNumber[BUFSIZE07], TempCountryCode[BUFSIZE07], TempDigitsNumber[BUFSIZE07], TempDigitsNumberTemp[BUFSIZE07], TempFinalPhoneNumber[BUFSIZE07];
        char *CountryCode, *DigitsNumber;

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

        if (LPN) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your phone number as: %s.\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ALMInputs.PhoneNumber);
            printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +[COUNTRYCODE, 1 to 3 DIGITS] [XXXXYYYYZZZZ, 4 to 13 DIGITS] \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);
        } else {
            printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +[COUNTRYCODE, 1 to 3 DIGITS] [XXXXYYYYZZZZ, 4 to 13 DIGITS] \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);
        }

        printf("\nPhone Number: ");
        fgets(InputPhoneNumber, BUFSIZE07, stdin);

        if (strcmp(InputPhoneNumber, "...\n") == 0) AccountLoginMenu(ALMSelected);

        InputPhoneNumber[strlen(InputPhoneNumber) - 1] = '\0';

        if (strlen(InputPhoneNumber) > 1 && strchr(InputPhoneNumber, '+') != NULL && strchr(InputPhoneNumber, ' ') != NULL && strlen(InputPhoneNumber) > 4) {
            strcpy(TempCountryCode, InputPhoneNumber);
            if (strchr(TempCountryCode, ' ') != NULL) {
                CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
                CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
            }
        } else {
            strcpy(InputPhoneNumber, "+0 0"); strcpy(TempCountryCode, InputPhoneNumber);
            if (strchr(TempCountryCode, ' ') != NULL) {
                CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
                CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
            }
        }

        while ((strlen(CountryCode) < 2 || strlen(CountryCode) > 4) || (strlen(DigitsNumber) < 4 || strlen(DigitsNumber) > 13) || CountryCode[0] != '+' || strchr(InputPhoneNumber, ' ') == NULL || (strchr(InputPhoneNumber, ' ') != NULL && FindOccurences(InputPhoneNumber, ' ') > 1) || strchr(InputPhoneNumber, '-') != NULL) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your with a starting phone country code and for at least 4 to 13 \n\t         digits (min. 4 digits), and make sure the SPACE count ONLY 1!\n\t         Lastly, please re-assure your inserted phone number DOESN'T CONSIST any of '-' (dashes)\n\t         numerical sign whatsoever!\n"ANSI_COLOR_RESET);
            printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+ABC', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a SINGLE space, and for the digits you can \n\t      insert thoroughly (without spaces, dashes, or so). \n\n\t      Phone number format insertion: +[COUNTRYCODE, 1 to 3 DIGITS] [XXXXYYYYZZZZ, 4 to 13 DIGITS] \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);

            printf("\nPhone Number: ");
            fgets(InputPhoneNumber, BUFSIZE07, stdin);

            if (strcmp(InputPhoneNumber, "...\n") == 0) AccountLoginMenu(ALMSelected);

            InputPhoneNumber[strlen(InputPhoneNumber) - 1] = '\0';

            if (strlen(InputPhoneNumber) > 1 && strchr(InputPhoneNumber, '+') != NULL && strchr(InputPhoneNumber, ' ') != NULL && strlen(InputPhoneNumber) > 4) {
                strcpy(TempCountryCode, InputPhoneNumber);
                if (strchr(TempCountryCode, ' ') != NULL) {
                    CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
                    CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
                }
            } else {
                strcpy(InputPhoneNumber, "+0 0"); strcpy(TempCountryCode, InputPhoneNumber);
                if (strchr(TempCountryCode, ' ') != NULL) {
                    CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
                    CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
                }
            }
        }
        
        InputPhoneNumber[strlen(InputPhoneNumber) - 1] = '\0';
        LPN = true;

        strcpy(TempDigitsNumber, DigitsNumber);
        strcpy(TempFinalPhoneNumber, CountryCode);
        strcpy(TempDigitsNumberTemp, " ");
        for (int i = 1; (long long unsigned int)i <= strlen(TempDigitsNumber); i++) {
            if (i == 3)                        { strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); strcat(TempDigitsNumberTemp, "-"); }
            else if ((i % 4) == 0 && (i != 4)) { strcat(TempDigitsNumberTemp, "-"); strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); }
            else                               { strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); }
        } strcat(TempFinalPhoneNumber, TempDigitsNumberTemp);
        strcpy(ALMInputs.PhoneNumber, TempFinalPhoneNumber);
        
        TempDigitsNumber[0]     = 0;
        TempFinalPhoneNumber[0] = 0;
        TempDigitsNumberTemp[0] = 0;
        AccountLoginMenu(ALMSelected);
    }

    else if (ALMSelected == 2) {
        // ClearScreen();
        // char InputUsername[BUFSIZE07];

        // printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

        // if (LU) {
        //     printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your username as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ALMInputs.Username);
        //     printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, \n\t      so use underscores or dashes to represents the next characters."ANSI_COLOR_RESET);
        // } else {
        //     printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, \n\t      so use underscores or dashes to represents the next characters."ANSI_COLOR_RESET);
        // }

        // printf("\nSKYR Username: ");
        // fgets(InputUsername, BUFSIZE07, stdin);

        // if (strcmp(InputUsername, "...\n") == 0) AccountLoginMenu(ALMSelected);

        // while (strlen(InputUsername) <= 3 || strchr(InputUsername, ' ') != NULL) {
        //     ClearScreen();
        //     printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

        //     puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your username at least a single word (min. 3 characters)!\n"ANSI_COLOR_RESET);
        //     printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, \n\t      so use underscores or dashes to represents the next characters."ANSI_COLOR_RESET);

        //     printf("\nSKYR Username: ");
        //     fgets(InputUsername, BUFSIZE07, stdin);

        //     if (strcmp(InputUsername, "...\n") == 0) AccountLoginMenu(ALMSelected);
        // }
        
        // InputUsername[strlen(InputUsername) - 1] = '\0';
        // LU = true;
        // strcpy(ALMInputs.Username, InputUsername);
        // InputUsername[0] = 0;
        // AccountLoginMenu(ALMSelected);

        ClearScreen();
        char InputUsername[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

        if (LU) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your username as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ALMInputs.Username);
            printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, so use \n\t      underscores or dashes to represents the next characters."ANSI_COLOR_RESET);
        } else {
            printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, so use \n\t      underscores or dashes to represents the next characters."ANSI_COLOR_RESET);
        }

        printf("\nSKYR Username: ");
        fgets(InputUsername, BUFSIZE07, stdin);

        if (strcmp(InputUsername, "...\n") == 0) AccountLoginMenu(ALMSelected);

        while (strlen(InputUsername) <= 3 || strchr(InputUsername, ' ') != NULL) {
            ClearScreen();
            printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

            puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your username at least a single word (min. 3 characters)!\n"ANSI_COLOR_RESET);
            printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, so use \n\t      underscores or dashes to represents the next characters."ANSI_COLOR_RESET);

            printf("\nSKYR Username: ");
            fgets(InputUsername, BUFSIZE07, stdin);

            if (strcmp(InputUsername, "...\n") == 0) AccountLoginMenu(ALMSelected);
        }
        
        InputUsername[strlen(InputUsername) - 1] = '\0';
        LU = true;
        strcpy(ALMInputs.Username, InputUsername);
        InputUsername[0] = 0;
        AccountLoginMenu(ALMSelected);
    }

    else if (ALMSelected == 3) {
        // ClearScreen();
        // char InputPassword[BUFSIZE07], HiddenPassword[BUFSIZE07];

        // printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

        // if (LP) {
        //     printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your password as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ALMInputs.HiddenPasswordShown);
        //     printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations \n\t      you'd like to insert with. The password insertion is censored, and you can peek \n\t      the password you've inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);
        // } else {
        //     printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations \n\t      you'd like to insert with. The password insertion is censored, and you can peek \n\t      the password you've inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);
        // }

        // printf("\nSKYR Password: ");
        // fgets(InputPassword, BUFSIZE07, stdin);

        // if (strcmp(InputPassword, "...\n") == 0) AccountLoginMenu(ALMSelected);

        // while (strlen(InputPassword) <= 8) {
        //     ClearScreen();
        //     printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

        //     puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your password in any unique way possible (min. 8 characters)!\n"ANSI_COLOR_RESET);
        //     printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations \n\t      you'd like to insert with. The password insertion is censored, and you can peek \n\t      the password you've inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);

        //     printf("\nSKYR Password: ");
        //     fgets(InputPassword, BUFSIZE07, stdin);

        //     if (strcmp(InputPassword, "...\n") == 0) AccountLoginMenu(ALMSelected);
        // }
        
        // InputPassword[strlen(InputPassword) - 1] = '\0';
        // LP = true;

        // for (int i = 0; (long long unsigned int)i < strlen(InputPassword); i++) {
        //     if (i == 0) { strcpy(HiddenPassword, "*"); }
        //     else        { strcat(HiddenPassword, "*"); }
        // } strcpy(ALMInputs.Password, InputPassword);
        // strcpy(ALMInputs.HiddenPasswordShown, HiddenPassword);
        // InputPassword[0] = 0; HiddenPassword[0] = 0;
        // AccountLoginMenu(ALMSelected);

        ClearScreen();
        char InputPassword[BUFSIZE07], HiddenPassword[BUFSIZE07];
        Selecting = true;
        
        while (Selecting) {
            ClearScreen();

            if (!ALMShowThePassword) {
                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

                if (LP) {
                    printf(ANSI_COLOR_LIGHTYELLOW"\t[SHOW: Press [>] key button] "ANSI_COLOR_RESET ANSI_COLOR_YELLOW"View Mode: Hiding the (unshown) hidden password...\n"ANSI_COLOR_RESET);
                    printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your password as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ALMInputs.HiddenPasswordShown);
                    printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
                    puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
                    puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters and a maximum 16 letters for better cautions \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with: \n\t\t    "ANSI_COLOR_RESET BRIGHTPURPLE218"an OPTIONAL RIGHT-KEY BUTTON [>], then press [ENTER] to confirm!"ANSI_COLOR_RESET);
                } else {
                    printf(ANSI_COLOR_LIGHTYELLOW"\t[SHOW: Press [>] key button] "ANSI_COLOR_RESET ANSI_COLOR_YELLOW"View Mode: Hiding the (unshown) hidden password...\n\n"ANSI_COLOR_RESET);
                    printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.HiddenPasswordShown);
                    puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
                    puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters and a maximum 16 letters for better cautions \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with: \n\t\t    "ANSI_COLOR_RESET BRIGHTPURPLE218"an OPTIONAL RIGHT-KEY BUTTON [>], then press [ENTER] to confirm!"ANSI_COLOR_RESET);
                }
            } else {
                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);

                if (LP) {
                    printf(ANSI_COLOR_LIGHTORANGE"\t[HIDE: Press [<] key button] "ANSI_COLOR_RESET ANSI_COLOR_ORANGE"View Mode: Showing the hidden password...\n"ANSI_COLOR_RESET);
                    printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your password as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ALMInputs.Password);
                    printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.Password);
                    puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
                    puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters and a maximum 16 letters for better cautions \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with: \n\t\t    "ANSI_COLOR_RESET BRIGHTPURPLE218"an OPTIONAL RIGHT-KEY BUTTON [>], then press [ENTER] to confirm!"ANSI_COLOR_RESET);
                } else {
                    printf(ANSI_COLOR_LIGHTORANGE"\t[HIDE: Press [<] key button] "ANSI_COLOR_RESET ANSI_COLOR_ORANGE"View Mode: Showing the hidden password...\n\n"ANSI_COLOR_RESET);
                    printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, ALMInputs.Password);
                    puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
                    puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters and a maximum 16 letters for better cautions \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with: \n\t\t    "ANSI_COLOR_RESET BRIGHTPURPLE218"an OPTIONAL RIGHT-KEY BUTTON [>], then press [ENTER] to confirm!"ANSI_COLOR_RESET);
                }
            }

            switch (AKDC = _getch()) {
                case KEY_LEFT:  ALMShowThePassword = false; break;
                case KEY_RIGHT: ALMShowThePassword = true;  break;
                case KEY_ENTER: Selecting = false;
                default: break;
            } if (Selecting) ClearScreen();

            fflush(stdin);
            (Updated) ? Updated = false : true;
        }

        // if (P) {
        //     printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your password as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ARMInputs.HiddenPasswordShown);
        //     printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ARMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations you'd like to \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);
        // } else {
        //     printf("\tFirst Name:\t\t%s\n\tLast Name:\t\t%s\n\tPersonal E-mail:\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ARMInputs.FirstName, ARMInputs.LastName, ARMInputs.Email, ARMInputs.Username, ARMInputs.HiddenPasswordShown);
        //     puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
        //     puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations you'd like to \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);
        // }

        printf("\nSKYR Password: ");
        fgets(InputPassword, BUFSIZE07, stdin);

        if (strcmp(InputPassword, "...\n") == 0) AccountLoginMenu(ALMSelected);

        while (strlen(InputPassword) <= 8 || strlen(InputPassword) > 16) {
            ClearScreen();

            if (!ARMShowThePassword) {
                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);
                printf(ANSI_COLOR_LIGHTYELLOW"\t[SHOW: Press [>] key button] "ANSI_COLOR_RESET ANSI_COLOR_YELLOW"View Mode: Hiding the (unshown) hidden password...\n"ANSI_COLOR_RESET);
                
                puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your password in any unique way possible (min. 8 characters)!\n"ANSI_COLOR_RESET);
                printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password);
                puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
                puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters and a maximum 16 letters for better cautions \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with: \n\t\t    "ANSI_COLOR_RESET BRIGHTPURPLE218"an OPTIONAL RIGHT-KEY BUTTON [>], then press [ENTER] to confirm!"ANSI_COLOR_RESET);
            } else {
                printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppLoginUI);
                printf(ANSI_COLOR_LIGHTORANGE"\t[HIDE: Press [<] key button] "ANSI_COLOR_RESET ANSI_COLOR_ORANGE"View Mode: Showing the hidden password...\n"ANSI_COLOR_RESET);
                
                puts(ANSI_COLOR_LIGHTRED"\tWarning: You must have to insert your password in any unique way possible (min. 8 characters)!\n"ANSI_COLOR_RESET);
                printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ALMInputs.Email, ALMInputs.PhoneNumber, ALMInputs.Username, (!ALMShowThePassword) ? ALMInputs.HiddenPasswordShown : ALMInputs.Password);
                puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
                puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters and a maximum 16 letters for better cautions \n\t      insert with. The password insertion is censored, and you can peek the password you've \n\t      inserted with: \n\t\t    "ANSI_COLOR_RESET BRIGHTPURPLE218"an OPTIONAL RIGHT-KEY BUTTON [>], then press [ENTER] to confirm!"ANSI_COLOR_RESET);
            }

            printf("\nSKYR Password: ");
            fgets(InputPassword, BUFSIZE07, stdin);

            if (strcmp(InputPassword, "...\n") == 0) AccountLoginMenu(ALMSelected);
        }

        InputPassword[strlen(InputPassword) - 1] = '\0';
        LP = true;

        for (int i = 0; (long long unsigned int)i < strlen(InputPassword); i++) {
            if (i == 0) { strcpy(HiddenPassword, "*"); }
            else        { strcat(HiddenPassword, "*"); }
        } strcpy(ALMInputs.Password, InputPassword);
        strcpy(ALMInputs.HiddenPasswordShown, HiddenPassword);
        InputPassword[0] = 0; HiddenPassword[0] = 0;
        AccountLoginMenu(ALMSelected);
    }
}

void AccountRecoveryMenu(int ACMSelected) {
    ClearScreen();
    fflush(stdout); fflush(stdin);

    FILE *FDestination, *FTempDestination;
    int BufLen;
    char FDBuffer[BUFSIZE16], DeleteTempDestinationTxtFile[128]; // TxtFileName[128] = "SKYR-FMSA-RegisteredAccounts.txt > First Name, Last Name, Personal E-mail, Phone Number, SKYR Username, SKYR Password";

    int AvailableOptions = 4, SubmitOrContinue;
    bool Selecting = true, Updated = false, FirstRun = true;
    bool ACMUpgrade = false;

    int PreviousAKDC = 0;
    bool CatchDefaultAKDC = false;

    char AKDC, MessageID6[BUFSIZE10], MessageID8[BUFSIZE10];
    char FirstName[BUFSIZE07], LastName[BUFSIZE07], Email[BUFSIZE07], Username[BUFSIZE07], Password[BUFSIZE07], DateOfBirth[BUFSIZE07], AgeOnPresent[BUFSIZE07], PhoneNumber[BUFSIZE07], Sex[BUFSIZE07];
    char *ShowFirstName, *ShowLastName, *ShowEmail, *ShowUsername, *ShowPassword, *ShowDateOfBirth, *ShowAgeOnPresent, *ShowPhoneNumber, *ShowSex;

    if ((CE && CPN && CU && CP) && !ACMUpgrade && AllEmpty != 4) { AvailableOptions += 1; }

    if (!ACMNotificationEnabled_01) { InfoMessageBox_OK("(Info) @SKYR-PFMSA; Importance of The Safety Profile Account", "For the safety purposes while you're going registrating a new account, or when trying to logged into the application, or even when you're going to recover of your missing account,\n\n\tWE ARE GOING TO DEPLETED EVERY INPUT YOU'VE PROGRESSED SO FAR, SO PLEASE JUST STAY IN ONE UI MENU;\n\nIn order to be save and more secure, so don't blame us when you're missing on your inputs after switching to different UIs... ."); ACMNotificationEnabled_01 = true; }
    if ((CE && CPN && CU && CP) && AllEmpty != 4 && !ACMNotificationEnabled_02) { InfoMessageBox_OK("(Info) @SKYR-PFMSA; Recovery Menu Upgraded", "All right, fellow lost users! Here now we've upgraded the Recovery Menu UI, and now you can just keep going UPWARDS or DOWNWARDS until you see a complete different UI, making sure that you're ready find your lost/missing accounts right away!"); ACMNotificationEnabled_02 = true; ACMUpgrade = true; }

    while (Selecting) {
        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);
        if (CatchDefaultAKDC) { (AllEmpty != 4) ? printf(ANSI_COLOR_LIGHTRED"\tError: The auto-enter shortcut key labeled as '%c' (ID: 0x%02X) is not registered at the moment!\n\n"ANSI_COLOR_RESET, ((int)PreviousAKDC != 12) ? (char)PreviousAKDC : 10, (int)PreviousAKDC) : printf(ANSI_COLOR_LIGHTRED"\tError:   The auto-enter shortcut key labeled as '%c' (ID: 0x%02X) is not registered at the moment!\n"ANSI_COLOR_RESET, ((int)PreviousAKDC != 12) ? (char)PreviousAKDC : 10, (int)PreviousAKDC); }
        
        if (AllEmpty == 4 && !ACMNotificationEnabled_03) {
            WarningMessageBox_CANCELTRYCONTINUE("(Warning): @SKYR-PFMSA; Empty Pre-requisites for Recovery Process", "Unfortunately, we can't process on the recovery account here because you've not providing anything but empty inputs, meaning you didn't know anything on what you're trying to revocer for about the little details on your missing account.\n\nPlease make sure you at least remember something about your missing profile account, at least from the phone number or the username you used when you're creating the account for the first time... .");
            ACMNotificationEnabled_03 = true;
        } if (AllEmpty == 4) printf(ANSI_COLOR_LIGHTORANGE"\tWarning: Recovery procedure can't be completed because you're not providing at least ONE (1) \n\t         information about your profile data!\n\n"ANSI_COLOR_RESET);

        if (!FirstRun) {
        /*  Separated by one line to another, handling ONLY FOUR (4) rows each parts.
        >   Personal E-mail, Phone Number, SKYR Username, SKYR Password
        */

            if ((ACMSelected + 1) > 0 && (ACMSelected + 1) <= 4 && (AvailableOptions == 4)) {
                if ((ACMSelected + 1) == 1) {
                    if (!CE)  { printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                } else if ((ACMSelected + 1) == 2) {
                    if (!CPN) { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                } else if ((ACMSelected + 1) == 3) {
                    if (!CU)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                } else if ((ACMSelected + 1) == 4) {
                    if (!CP)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                }

                if (AllEmpty != 4) { (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\n\n\n\t%s", AppRecoveryUDRL) : printf("\n\n\n\n\n\n\n\n\t%s", AppRecoveryUDRL); ACMNotificationEnabled_02 = false; ACMNotificationEnabled_03 = false; ACMUpgrade = false; }
                else { (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\t%s", AppRecoveryUDRL) : printf("\n\n\n\n\n\t%s", AppRecoveryUDRL); }
            }
            
            else if ((ACMSelected + 1) > 0 && (ACMSelected + 1) <= 5 && (AvailableOptions == 5)) {
                if ((ACMSelected + 1) == 1) {
                    if (!CE)  { printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                } else if ((ACMSelected + 1) == 2) {
                    if (!CPN) { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                } else if ((ACMSelected + 1) == 3) {
                    if (!CU)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                } else if ((ACMSelected + 1) == 4) {
                    if (!CP)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                }
                
                if (AllEmpty != 4) { (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\n\n\n\t%s", AppRecoveryUDRL) : printf("\n\n\n\n\n\n\n\n\t%s", AppRecoveryUDRL); ACMNotificationEnabled_02 = false; ACMNotificationEnabled_03 = false; ACMUpgrade = false; }
                else { (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\t%s", AppRecoveryUDRL) : printf("\n\n\n\n\n\t%s", AppRecoveryUDRL); }
                
                if ((ACMSelected + 1) == 5 && AllEmpty != 4) {
                    ClearScreen();
                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);
                    
                    printf("\tInfo: You may have inserted a few remembrance of your profile account, and  \n\t      willing to do some recovery in order to get logged in back.\n");
                    printf(ANSI_COLOR_LIGHTCYAN"\n\tProceed to do the recovery account process?\n\n"ANSI_COLOR_RESET);
                    snprintf(MessageID6, BUFSIZE10, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);
                    snprintf(MessageID8, BUFSIZE10, ANSI_COLOR_LIGHTCYAN"\n\tProceed to do the recovery account process?\n"ANSI_COLOR_RESET);
                    
                    MessagesShown_ArrowKeyChoiceDialog[6] = MessageID6;
                    MessagesShown_ArrowKeyChoiceDialog[7] = "\tInfo: You may have inserted a few remembrance of your profile account, and  \n\t      willing to do some recovery in order to get logged in back.";
                    MessagesShown_ArrowKeyChoiceDialog[8] = MessageID8;
                    SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 6, 9);

                    if (SubmitOrContinue) {
                        FDestination     = fopen("SKYR-FMSA-RegisteredAccounts.txt", "r");
                        FTempDestination = fopen("TempDestination.txt", "w");

                        while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
                            BufLen = strlen(FDBuffer);
                            for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                            fputs(FDBuffer, FTempDestination);
                        } fclose(FDestination); fclose(FTempDestination);

                        ClearScreen();
                        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);
                        printf(ANSI_COLOR_GREEN"\tInfo: We've founded a valid profile account data from the list of \n\t      your provided recovery account requirements here, as of:\n\n"ANSI_COLOR_RESET);
                        
                        for (int i = 1; i <= (4 - AllEmpty); i++) {
                            if (!EmptyCE && !FlagCE)        { printf(ANSI_COLOR_BLUE"\t      [%d / %d] Provided Personal E-mail:\t\t%s\n"ANSI_COLOR_RESET, i, (4 - AllEmpty), ACMInputs.Email); FlagCE = true; }
                            else if (!EmptyCPN && !FlagCPN) { printf(ANSI_COLOR_BLUE"\t      [%d / %d] Provided Phone Number:\t\t%s\n"ANSI_COLOR_RESET, i, (4 - AllEmpty), ACMInputs.PhoneNumber); FlagCPN = true; }
                            else if (!EmptyCU && !FlagCU)   { printf(ANSI_COLOR_BLUE"\t      [%d / %d] Provided Username:\t\t%s\n"ANSI_COLOR_RESET, i, (4 - AllEmpty), ACMInputs.Username); FlagCU = true; }
                            else if (!EmptyCP && !FlagCP)   { printf(ANSI_COLOR_BLUE"\t      [%d / %d] Provided Password:\t\t%s\n"ANSI_COLOR_RESET, i, (4 - AllEmpty), ACMInputs.HiddenPasswordShown); FlagCP = true; }
                        } FlagCE = false; FlagCPN = false; FlagCU = false; FlagCP = false;
                        
                        printf(ANSI_COLOR_ORANGE"\n\tNote: What you want to recover is all listed down here:\n\n"ANSI_COLOR_RESET);
                        for (int i = 1; i <= AllEmpty; i++) {
                            if (EmptyCE && !FlagCE)         { printf(ANSI_COLOR_YELLOW"\t      [%d / %d] Recover Personal E-mail:\t\t%s\n"ANSI_COLOR_RESET, i, AllEmpty, ACMInputs.Email); FlagCE = true; }
                            else if (EmptyCPN && !FlagCPN)  { printf(ANSI_COLOR_YELLOW"\t      [%d / %d] Recover Phone Number:\t\t%s\n"ANSI_COLOR_RESET, i, AllEmpty, ACMInputs.PhoneNumber); FlagCPN = true; }
                            else if (EmptyCU && !FlagCU)    { printf(ANSI_COLOR_YELLOW"\t      [%d / %d] Recover Username:\t\t\t%s\n"ANSI_COLOR_RESET, i, AllEmpty, ACMInputs.Username); FlagCU = true; }
                            else if (EmptyCP && !FlagCP)    { printf(ANSI_COLOR_YELLOW"\t      [%d / %d] Recover Password:\t\t\t%s\n"ANSI_COLOR_RESET, i, AllEmpty, ACMInputs.HiddenPasswordShown); FlagCP = true; }
                        } getchar();
                        
                        for (int GRA = 1; (long long unsigned int)GRA <= GlobalSKYRFMSARegisteredAccounts; GRA++) {
                            strncpy(FirstName,    ReadAndPrintLine("TempDestination.txt", 0 + (14 * GRA)), BUFSIZE07);
                            strncpy(LastName,     ReadAndPrintLine("TempDestination.txt", 1 + (14 * GRA)), BUFSIZE07);
                            strncpy(Email,        ReadAndPrintLine("TempDestination.txt", 2 + (14 * GRA)), BUFSIZE07);
                            strncpy(Username,     ReadAndPrintLine("TempDestination.txt", 3 + (14 * GRA)), BUFSIZE07);
                            strncpy(Password,     ReadAndPrintLine("TempDestination.txt", 4 + (14 * GRA)), BUFSIZE07);
                            strncpy(DateOfBirth,  ReadAndPrintLine("TempDestination.txt", 6 + (14 * GRA)), BUFSIZE07);
                            strncpy(AgeOnPresent, ReadAndPrintLine("TempDestination.txt", 7 + (14 * GRA)), BUFSIZE07);
                            strncpy(PhoneNumber,  ReadAndPrintLine("TempDestination.txt", 8 + (14 * GRA)), BUFSIZE07);
                            strncpy(Sex,          ReadAndPrintLine("TempDestination.txt", 9 + (14 * GRA)), BUFSIZE07);

                            FirstName[strlen(FirstName) - 1] = '\0'; LastName[strlen(LastName) - 1] = '\0';
                            Email[strlen(Email) - 1] = '\0'; Username[strlen(Username) - 1] = '\0'; Password[strlen(Password) - 1] = '\0';
                            DateOfBirth[strlen(DateOfBirth) - 1] = '\0'; AgeOnPresent[strlen(AgeOnPresent) - 1] = '\0';
                            PhoneNumber[strlen(PhoneNumber) - 1] = '\0'; Sex[strlen(Sex) - 1] = '\0';
                            strtok_r(FirstName, ":", &ShowFirstName);       ShowFirstName = TrimWhiteSpaces(ShowFirstName);
                            strtok_r(LastName, ":", &ShowLastName);         ShowLastName = TrimWhiteSpaces(ShowLastName);
                            strtok_r(Email, ":", &ShowEmail);               ShowEmail = TrimWhiteSpaces(ShowEmail);
                            strtok_r(Username, ":", &ShowUsername);         ShowUsername = TrimWhiteSpaces(ShowUsername);
                            strtok_r(Password, ":", &ShowPassword);         ShowPassword = TrimWhiteSpaces(ShowPassword);
                            strtok_r(DateOfBirth, ":", &ShowDateOfBirth);   ShowDateOfBirth = TrimWhiteSpaces(ShowDateOfBirth);
                            strtok_r(AgeOnPresent, ":", &ShowAgeOnPresent); ShowAgeOnPresent = TrimWhiteSpaces(ShowAgeOnPresent);
                            strtok_r(PhoneNumber, ":", &ShowPhoneNumber);   ShowPhoneNumber = TrimWhiteSpaces(ShowPhoneNumber);
                            strtok_r(Sex, ":", &ShowSex);                   ShowSex = TrimWhiteSpaces(ShowSex);

                            if (strstr(ShowEmail, ACMInputs.Email)                  != NULL || \
                                strstr(ShowPhoneNumber, ACMInputs.PhoneNumber)      != NULL || \
                                strstr(ShowUsername, ACMInputs.Username)            != NULL || \
                                strstr(ShowPassword, ACMInputs.HiddenPasswordShown) != NULL) {
                                    ClearScreen();
                                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);

                                    printf(ANSI_COLOR_LIGHTPINK"\tInfo: Below here are listed the profile data, linked from your specific account recovery first step \n\t      by providing what can you remembered the least about your forgotten account.\n\n"ANSI_COLOR_RESET);
                                    puts(ANSI_COLOR_LIGHTCYAN"\t────────────────────────────────────────────────────────────────────────────────────────────────────"ANSI_COLOR_RESET);
                                    printf("\t%s",   ReadAndPrintLine("TempDestination.txt", (-3) + (14 * GRA)));
                                    printf("\t%s\n", ReadAndPrintLine("TempDestination.txt", (-2) + (14 * GRA)));
                                    printf("\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\n\t%s\n\t%s\n\t%s\n\t%s\n", \
                                            ShowFirstName, ShowLastName, ShowEmail, ShowUsername, ShowPassword, \
                                            ShowDateOfBirth, ShowAgeOnPresent, ShowPhoneNumber, ShowSex);
                                    puts(ANSI_COLOR_LIGHTCYAN"\t────────────────────────────────────────────────────────────────────────────────────────────────────"ANSI_COLOR_RESET);
                                    
                            if ((long long unsigned int)GRA < GlobalSKYRFMSARegisteredAccounts) { printf(ANSI_COLOR_LIGHTGREEN"\n\tPress [ENTER] button key on your keyboard to continue... "ANSI_COLOR_RESET); getchar(); }
                            else { printf(ANSI_COLOR_GREEN"\tPress [ENTER] button key on your keyboard to go back to the previous menu... "ANSI_COLOR_RESET); getchar(); }
                                    
                            } else {
                                FirstName[0] = 0; LastName[0] = 0, Email[0] = 0, Username[0] = 0, Password[0] = 0;
                                DateOfBirth[0] = 0, AgeOnPresent[0] = 0; PhoneNumber[0] = 0, Sex[0] = 0;
                            }
                        }

                        strcpy(DeleteTempDestinationTxtFile, "del ");
                        strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
                        system(DeleteTempDestinationTxtFile);

                        ACMInputs.Email[0] = 0;
                        ACMInputs.PhoneNumber[0] = 0;
                        ACMInputs.Username[0] = 0;
                        ACMInputs.Password[0] = 0;
                        ACMInputs.HiddenPasswordShown[0] = 0;
                        CE = false; CPN = false; CU = false; CP = false;
                        EmptyCE = false; EmptyCPN = false; EmptyCU = false; EmptyCP = false;
                        FlagCE = false; FlagCPN = false; FlagCU = false; FlagCP = false;
                        VisitedCE = false; VisitedCPN = false; VisitedCU = false; VisitedCP = false;
                        ACMSelected = 0; AllEmpty = 0;
                        FlagACM = false;
                        if (strlen(FullName) != 0 && strlen(UserName) != 0) { MainMenuProfileManager(MMPMSelected); }
                        else { AccountLoginMenu(0); }

                    } else { ACMSelected = 0; AccountRecoveryMenu(ACMSelected); }
                }
            }

        } else {
            FirstRun = false;

            if ((ACMSelected + 1) > 0 && (ACMSelected + 1) <= 4 && (AvailableOptions == 4)) {
                if ((ACMSelected + 1) == 1) {
                    if (!CE)  { printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                } else if ((ACMSelected + 1) == 2) {
                    if (!CPN) { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                } else if ((ACMSelected + 1) == 3) {
                    if (!CU)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                } else if ((ACMSelected + 1) == 4) {
                    if (!CP)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                }

                if (AllEmpty != 4) { (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\n\n\n\t%s", AppRecoveryUDRL) : printf("\n\n\n\n\n\n\n\n\t%s", AppRecoveryUDRL); ACMNotificationEnabled_02 = false; ACMNotificationEnabled_03 = false; ACMUpgrade = false; }
                else { (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\t%s", AppRecoveryUDRL) : printf("\n\n\n\n\n\t%s", AppRecoveryUDRL); }
            }
            
            else if ((ACMSelected + 1) > 0 && (ACMSelected + 1) <= 5 && (AvailableOptions == 5)) {
                if ((ACMSelected + 1) == 1) {
                    if (!CE)  { printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                } else if ((ACMSelected + 1) == 2) {
                    if (!CPN) { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                } else if ((ACMSelected + 1) == 3) {
                    if (!CU)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                } else if ((ACMSelected + 1) == 4) {
                    if (!CP)  { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                    else      { printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown); }
                }
                
                if (AllEmpty != 4) { (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\n\n\n\t%s", AppRecoveryUDRL) : printf("\n\n\n\n\n\n\n\n\t%s", AppRecoveryUDRL); ACMNotificationEnabled_02 = false; ACMNotificationEnabled_03 = false; ACMUpgrade = false; }
                else { (!CatchDefaultAKDC) ? printf("\n\n\n\n\n\n\n\t%s", AppRecoveryUDRL) : printf("\n\n\n\n\n\t%s", AppRecoveryUDRL); }
                
                if ((ACMSelected + 1) == 5 && AllEmpty != 4) {
                    ClearScreen();
                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);
                    
                    printf("\tInfo: You may have inserted a few remembrance of your profile account, and  \n\t      willing to do some recovery in order to get logged in back.\n");
                    printf(ANSI_COLOR_LIGHTCYAN"\n\tProceed to do the recovery account process?\n\n"ANSI_COLOR_RESET);
                    snprintf(MessageID6, BUFSIZE10, ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);
                    snprintf(MessageID8, BUFSIZE10, ANSI_COLOR_LIGHTCYAN"\n\tProceed to do the recovery account process?\n"ANSI_COLOR_RESET);
                    
                    MessagesShown_ArrowKeyChoiceDialog[6] = MessageID6;
                    MessagesShown_ArrowKeyChoiceDialog[7] = "\tInfo: You may have inserted a few remembrance of your profile account, and  \n\t      willing to do some recovery in order to get logged in back.";
                    MessagesShown_ArrowKeyChoiceDialog[8] = MessageID8;
                    SubmitOrContinue = ArrowKeyChoiceDialog("Truth Confirmation", MessagesShown_ArrowKeyChoiceDialog, 6, 9);

                    if (SubmitOrContinue) {
                        FDestination     = fopen("SKYR-FMSA-RegisteredAccounts.txt", "r");
                        FTempDestination = fopen("TempDestination.txt", "w");

                        while (fgets(FDBuffer, sizeof(FDBuffer), FDestination) != 0) {
                            BufLen = strlen(FDBuffer);
                            for (int i = 0; i < BufLen; i++) FDBuffer[i] += EncryptionKey;
                            fputs(FDBuffer, FTempDestination);
                        } fclose(FDestination); fclose(FTempDestination);

                        ClearScreen();
                        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);
                        printf(ANSI_COLOR_GREEN"\tInfo: We've founded a valid profile account data from the list of \n\t      your provided recovery account requirements here, as of:\n\n"ANSI_COLOR_RESET);
                        
                        for (int i = 1; i <= (4 - AllEmpty); i++) {
                            if (!EmptyCE && !FlagCE)        { printf(ANSI_COLOR_BLUE"\t      [%d / %d] Provided Personal E-mail:\t\t%s\n"ANSI_COLOR_RESET, i, (4 - AllEmpty), ACMInputs.Email); FlagCE = true; }
                            else if (!EmptyCPN && !FlagCPN) { printf(ANSI_COLOR_BLUE"\t      [%d / %d] Provided Phone Number:\t\t%s\n"ANSI_COLOR_RESET, i, (4 - AllEmpty), ACMInputs.PhoneNumber); FlagCPN = true; }
                            else if (!EmptyCU && !FlagCU)   { printf(ANSI_COLOR_BLUE"\t      [%d / %d] Provided Username:\t\t%s\n"ANSI_COLOR_RESET, i, (4 - AllEmpty), ACMInputs.Username); FlagCU = true; }
                            else if (!EmptyCP && !FlagCP)   { printf(ANSI_COLOR_BLUE"\t      [%d / %d] Provided Password:\t\t%s\n"ANSI_COLOR_RESET, i, (4 - AllEmpty), ACMInputs.HiddenPasswordShown); FlagCP = true; }
                        } FlagCE = false; FlagCPN = false; FlagCU = false; FlagCP = false;
                        
                        printf(ANSI_COLOR_ORANGE"\n\tNote: What you want to recover is all listed down here:\n\n"ANSI_COLOR_RESET);
                        for (int i = 1; i <= AllEmpty; i++) {
                            if (EmptyCE && !FlagCE)         { printf(ANSI_COLOR_YELLOW"\t      [%d / %d] Recover Personal E-mail:\t\t%s\n"ANSI_COLOR_RESET, i, AllEmpty, ACMInputs.Email); FlagCE = true; }
                            else if (EmptyCPN && !FlagCPN)  { printf(ANSI_COLOR_YELLOW"\t      [%d / %d] Recover Phone Number:\t\t%s\n"ANSI_COLOR_RESET, i, AllEmpty, ACMInputs.PhoneNumber); FlagCPN = true; }
                            else if (EmptyCU && !FlagCU)    { printf(ANSI_COLOR_YELLOW"\t      [%d / %d] Recover Username:\t\t\t%s\n"ANSI_COLOR_RESET, i, AllEmpty, ACMInputs.Username); FlagCU = true; }
                            else if (EmptyCP && !FlagCP)    { printf(ANSI_COLOR_YELLOW"\t      [%d / %d] Recover Password:\t\t\t%s\n"ANSI_COLOR_RESET, i, AllEmpty, ACMInputs.HiddenPasswordShown); FlagCP = true; }
                        } getchar();
                        
                        for (int GRA = 1; (long long unsigned int)GRA <= GlobalSKYRFMSARegisteredAccounts; GRA++) {
                            strncpy(FirstName,    ReadAndPrintLine("TempDestination.txt", 0 + (14 * GRA)), BUFSIZE07);
                            strncpy(LastName,     ReadAndPrintLine("TempDestination.txt", 1 + (14 * GRA)), BUFSIZE07);
                            strncpy(Email,        ReadAndPrintLine("TempDestination.txt", 2 + (14 * GRA)), BUFSIZE07);
                            strncpy(Username,     ReadAndPrintLine("TempDestination.txt", 3 + (14 * GRA)), BUFSIZE07);
                            strncpy(Password,     ReadAndPrintLine("TempDestination.txt", 4 + (14 * GRA)), BUFSIZE07);
                            strncpy(DateOfBirth,  ReadAndPrintLine("TempDestination.txt", 6 + (14 * GRA)), BUFSIZE07);
                            strncpy(AgeOnPresent, ReadAndPrintLine("TempDestination.txt", 7 + (14 * GRA)), BUFSIZE07);
                            strncpy(PhoneNumber,  ReadAndPrintLine("TempDestination.txt", 8 + (14 * GRA)), BUFSIZE07);
                            strncpy(Sex,          ReadAndPrintLine("TempDestination.txt", 9 + (14 * GRA)), BUFSIZE07);

                            FirstName[strlen(FirstName) - 1] = '\0'; LastName[strlen(LastName) - 1] = '\0';
                            Email[strlen(Email) - 1] = '\0'; Username[strlen(Username) - 1] = '\0'; Password[strlen(Password) - 1] = '\0';
                            DateOfBirth[strlen(DateOfBirth) - 1] = '\0'; AgeOnPresent[strlen(AgeOnPresent) - 1] = '\0';
                            PhoneNumber[strlen(PhoneNumber) - 1] = '\0'; Sex[strlen(Sex) - 1] = '\0';
                            strtok_r(FirstName, ":", &ShowFirstName);       ShowFirstName = TrimWhiteSpaces(ShowFirstName);
                            strtok_r(LastName, ":", &ShowLastName);         ShowLastName = TrimWhiteSpaces(ShowLastName);
                            strtok_r(Email, ":", &ShowEmail);               ShowEmail = TrimWhiteSpaces(ShowEmail);
                            strtok_r(Username, ":", &ShowUsername);         ShowUsername = TrimWhiteSpaces(ShowUsername);
                            strtok_r(Password, ":", &ShowPassword);         ShowPassword = TrimWhiteSpaces(ShowPassword);
                            strtok_r(DateOfBirth, ":", &ShowDateOfBirth);   ShowDateOfBirth = TrimWhiteSpaces(ShowDateOfBirth);
                            strtok_r(AgeOnPresent, ":", &ShowAgeOnPresent); ShowAgeOnPresent = TrimWhiteSpaces(ShowAgeOnPresent);
                            strtok_r(PhoneNumber, ":", &ShowPhoneNumber);   ShowPhoneNumber = TrimWhiteSpaces(ShowPhoneNumber);
                            strtok_r(Sex, ":", &ShowSex);                   ShowSex = TrimWhiteSpaces(ShowSex);

                            if (strstr(ShowEmail, ACMInputs.Email)                  != NULL || \
                                strstr(ShowPhoneNumber, ACMInputs.PhoneNumber)      != NULL || \
                                strstr(ShowUsername, ACMInputs.Username)            != NULL || \
                                strstr(ShowPassword, ACMInputs.HiddenPasswordShown) != NULL) {
                                    ClearScreen();
                                    printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);

                                    printf(ANSI_COLOR_LIGHTPINK"\tInfo: Below here are listed the profile data, linked from your specific account recovery first step \n\t      by providing what can you remembered the least about your forgotten account.\n\n"ANSI_COLOR_RESET);
                                    printf(BRIGHTRED216 ANSI_STYLE_BOLD"      (hiding all left-value, need more recognition over the user themselves)");
                                    puts(ANSI_COLOR_LIGHTCYAN"\t────────────────────────────────────────────────────────────────────────────────────────────────────"ANSI_COLOR_RESET);
                                    printf("\t%s",   ReadAndPrintLine("TempDestination.txt", (-3) + (14 * GRA)));
                                    printf("\t%s\n", ReadAndPrintLine("TempDestination.txt", (-2) + (14 * GRA)));
                                    printf("\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\n\t%s\n\t%s\n\t%s\n\t%s\n", \
                                            ShowFirstName, ShowLastName, ShowEmail, ShowUsername, ShowPassword, \
                                            ShowDateOfBirth, ShowAgeOnPresent, ShowPhoneNumber, ShowSex);
                                    puts(ANSI_COLOR_LIGHTCYAN"\t────────────────────────────────────────────────────────────────────────────────────────────────────"ANSI_COLOR_RESET);
                                    getchar();
                            
                            if ((long long unsigned int)GRA < GlobalSKYRFMSARegisteredAccounts) { printf(ANSI_COLOR_LIGHTGREEN"\n\tPress [ENTER] button key on your keyboard to continue... "ANSI_COLOR_RESET); getchar(); }
                        else { printf(ANSI_COLOR_GREEN"\tPress [ENTER] button key on your keyboard to go back to the previous menu... "ANSI_COLOR_RESET); getchar(); }
                                    
                            } else {
                                FirstName[0] = 0; LastName[0] = 0, Email[0] = 0, Username[0] = 0, Password[0] = 0;
                                DateOfBirth[0] = 0, AgeOnPresent[0] = 0; PhoneNumber[0] = 0, Sex[0] = 0;
                            }
                        }

                        strcpy(DeleteTempDestinationTxtFile, "del ");
                        strcat(DeleteTempDestinationTxtFile, "TempDestination.txt");
                        system(DeleteTempDestinationTxtFile);

                        ACMInputs.Email[0] = 0;
                        ACMInputs.PhoneNumber[0] = 0;
                        ACMInputs.Username[0] = 0;
                        ACMInputs.Password[0] = 0;
                        ACMInputs.HiddenPasswordShown[0] = 0;
                        CE = false; CPN = false; CU = false; CP = false;
                        EmptyCE = false; EmptyCPN = false; EmptyCU = false; EmptyCP = false;
                        FlagCE = false; FlagCPN = false; FlagCU = false; FlagCP = false;
                        VisitedCE = false; VisitedCPN = false; VisitedCU = false; VisitedCP = false;
                        ACMSelected = 0; AllEmpty = 0;
                        FlagACM = false;
                        if (strlen(FullName) != 0 && strlen(UserName) != 0) { MainMenuProfileManager(MMPMSelected); }
                        else { AccountLoginMenu(0); }

                    } else { ACMSelected = 0; AccountRecoveryMenu(ACMSelected); }
                }
            }
        }

        switch (AKDC = _getch()) {
            case KEY_UP:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                if (ACMSelected > 0 && ACMSelected < AvailableOptions) {
                    --ACMSelected; Updated = true;
                } else if (ACMSelected <= 0) {
                    ACMSelected = (AvailableOptions - 1); Updated = true;
                } break;
            case KEY_DOWN:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                if (ACMSelected >= 0 && ACMSelected < AvailableOptions - 1) {
                    ++ACMSelected; Updated = true;
                } else if (ACMSelected >= AvailableOptions - 1) {
                    ACMSelected = 0; Updated = true;
                } break;
            case KEY_RIGHT:
                PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case KEY_LEFT:
                PreviousAKDC = 0; CatchDefaultAKDC = false;
                ACMInputs.Email[0] = 0;
                ACMInputs.PhoneNumber[0] = 0;
                ACMInputs.Username[0] = 0;
                ACMInputs.Password[0] = 0;
                ACMInputs.HiddenPasswordShown[0] = 0;
                CE = false; CPN = false; CU = false; CP = false;
                EmptyCE = false; EmptyCPN = false; EmptyCU = false; EmptyCP = false;
                FlagCE = false; FlagCPN = false; FlagCU = false; FlagCP = false;
                VisitedCE = false; VisitedCPN = false; VisitedCU = false; VisitedCP = false;
                ACMSelected = 0; AllEmpty = 0;
                FlagACM = false;

                AccountLoginMenu(0);
                break;
            case KEY_ENTER:
                Selecting = false; Updated = true;
                break;
            case '1': ACMSelected = 0; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '2': ACMSelected = 1; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '3': ACMSelected = 2; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            case '4': ACMSelected = 3; Selecting = false; Updated = true; PreviousAKDC = 0; CatchDefaultAKDC = false; break;
            default: {
                if (AKDC == KEY_UP || AKDC == KEY_DOWN || AKDC == KEY_LEFT || AKDC == KEY_RIGHT || AKDC == KEY_ENTER) { ClearScreen(); continue; }
                (AKDC > 0) ? PreviousAKDC = (int)AKDC : 0;
                (AKDC > 0) ? CatchDefaultAKDC = true : false;
            } break;
        } if (Selecting) ClearScreen();
        
        fflush(stdin);
        (Updated) ? Updated = false : true;
    }

    if (ACMSelected == 0) {
        ClearScreen();
        char InputEmail[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);

        if (CE) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your personal e-mail as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ACMInputs.Email);
            printf("      " ANSI_COLOR_LIGHTGREEN"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating \n\t      your own e-mail."ANSI_COLOR_RESET);
        } else {
            printf("      " ANSI_COLOR_LIGHTYELLOW"> Personal E-mail:\t%s\n\t"ANSI_COLOR_RESET "Phone Number:\t\t%s\n\tSKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Personal E-mail."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your personal e-mail into your profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The e-mail format must have a '@' symbol, and the domain you used while creating \n\t      your own e-mail."ANSI_COLOR_RESET);
        }

        printf("\nPersonal E-mail: ");
        fgets(InputEmail, BUFSIZE07, stdin);

        while (strlen(InputEmail) <= 3 || strchr(InputEmail, '@') == NULL || strchr(InputEmail, '.') == NULL) {
            CE = true;
            if (AllEmpty >= 0 && AllEmpty <= 4 && !VisitedCE) { AllEmpty += 1; EmptyCE = true; VisitedCE = true; }
            strcpy(ACMInputs.Email, "... (Unknown)?");
            AccountRecoveryMenu(ACMSelected);
        }
        
        InputEmail[strlen(InputEmail) - 1] = '\0';
        CE = true;
        if (AllEmpty >= 0 && AllEmpty <= 4 && VisitedCE)  { AllEmpty -= 1; EmptyCE = false; VisitedCE = false; }
        strcpy(ACMInputs.Email, InputEmail);
        AccountRecoveryMenu(ACMSelected);
    }

    else if (ACMSelected == 1) {
        ClearScreen();
        char InputPhoneNumber[BUFSIZE07], TempCountryCode[BUFSIZE07], TempDigitsNumber[BUFSIZE07], TempDigitsNumberTemp[BUFSIZE07], TempFinalPhoneNumber[BUFSIZE07];
        char *CountryCode, *DigitsNumber;

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);

        if (CPN) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your phone number as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ACMInputs.PhoneNumber);
            printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTGREEN"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +[COUNTRYCODE, 1 to 3 DIGITS] [XXXXYYYYZZZZ, 4 to 13 DIGITS] \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);
        } else {
            printf("\tPersonal E-mail:\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> Phone Number:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Username:\t\t%s\n\tSKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"Phone Number."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your phone number profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The phone number must be started with the country code '+XXX', and the next 4 to 13 \n\t      digits are for the phone number you owned. \n\t      Separate the country code and the digits by a single space, and for the digits you can \n\t      insert thoroughly (without spaces or so). \n\n\t      Phone number format insertion: +[COUNTRYCODE, 1 to 3 DIGITS] [XXXXYYYYZZZZ, 4 to 13 DIGITS] \n\t      Example: +62 12345678901"ANSI_COLOR_RESET);
        }

        printf("\nPhone Number: ");
        fgets(InputPhoneNumber, BUFSIZE07, stdin);

        strcpy(TempCountryCode, InputPhoneNumber);
        TempCountryCode[strlen(TempCountryCode) - 1] = '\0';
        if (strchr(TempCountryCode, ' ') != NULL) {
            CountryCode = strtok(TempCountryCode, " "); DigitsNumber = strtok(NULL, " ");
            CountryCode = TrimWhiteSpaces(CountryCode); DigitsNumber = TrimWhiteSpaces(DigitsNumber);
        }

        while ((strlen(DigitsNumber) <= 4 || strlen(DigitsNumber) > 13) || CountryCode[0] != '+' || strchr(InputPhoneNumber, ' ') == NULL) {
            CPN = true;
            if (AllEmpty >= 0 && AllEmpty <= 4 && !VisitedCPN) { AllEmpty += 1; EmptyCPN = true; VisitedCPN = true; }
            strcpy(ACMInputs.PhoneNumber, "... (Unknown)?");
            AccountRecoveryMenu(ACMSelected);
        }
        
        InputPhoneNumber[strlen(InputPhoneNumber) - 1] = '\0';
        CPN = true;
        if (AllEmpty >= 0 && AllEmpty <= 4 && VisitedCPN)  { AllEmpty -= 1; EmptyCPN = false; VisitedCPN = false; }

        strcpy(TempDigitsNumber, DigitsNumber);
        strcpy(TempFinalPhoneNumber, CountryCode);
        strcpy(TempDigitsNumberTemp, " ");
        for (int i = 1; (long long unsigned int)i <= strlen(TempDigitsNumber); i++) {
            if (i == 3)                        { strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); strcat(TempDigitsNumberTemp, "-"); }
            else if ((i % 4) == 0 && (i != 4)) { strcat(TempDigitsNumberTemp, "-"); strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); }
            else                               { strncat(TempDigitsNumberTemp, &TempDigitsNumber[i - 1], 1); }
        } strcat(TempFinalPhoneNumber, TempDigitsNumberTemp);
        strcpy(ACMInputs.PhoneNumber, TempFinalPhoneNumber);
        AccountRecoveryMenu(ACMSelected);
    }

    else if (ACMSelected == 2) {
        ClearScreen();
        char InputUsername[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);

        if (CU) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your username as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ACMInputs.Username);
            printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, \n\t      so use underscores or dashes to represents the next characters."ANSI_COLOR_RESET);
        } else {
            printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Username:\t\t%s\n\t"ANSI_COLOR_RESET "SKYR Password:\t\t%s\n", ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Username."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your username profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The username must starts with a character and shall not contains a single space, \n\t      so use underscores or dashes to represents the next characters."ANSI_COLOR_RESET);
        }

        printf("\nSKYR Username: ");
        fgets(InputUsername, BUFSIZE07, stdin);

        while (strlen(InputUsername) <= 3 || strchr(InputUsername, ' ') != NULL) {
            CU = true;
            if (AllEmpty >= 0 && AllEmpty <= 4 && !VisitedCU) { AllEmpty += 1; EmptyCU = true; VisitedCU = true; }
            strcpy(ACMInputs.Username, "... (Unknown)?");
            AccountRecoveryMenu(ACMSelected);
        }
        
        InputUsername[strlen(InputUsername) - 1] = '\0';
        CU = true;
        if (AllEmpty >= 0 && AllEmpty <= 4 && VisitedCU)  { AllEmpty -= 1; EmptyCU = false; VisitedCU = false; }
        strcpy(ACMInputs.Username, InputUsername);
        AccountRecoveryMenu(ACMSelected);
    }

    else if (ACMSelected == 3) {
        ClearScreen();
        char InputPassword[BUFSIZE07], HiddenPassword[BUFSIZE07];

        printf(ANSI_COLOR_LIGHTBLUE"\n\n\n\n\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\t%s\t%s\t\n\t"ANSI_COLOR_RESET ANSI_COLOR_LIGHTMAGENTA"%s\t────────────────────────────────────────────────────────────────────────────────────────────────────\n\n"ANSI_COLOR_RESET, ApplicationTitle, ApplicationVersion, AppRecoveryUI);

        if (CP) {
            printf(ANSI_COLOR_GREEN"\tInfo: We'd checked that you earlier had already insert your password as: \n\t          >> %s.\n\n\t      But don't worry, if you want to make a change, then you may proceed to do so.\n\n"ANSI_COLOR_RESET, ACMInputs.HiddenPasswordShown);
            printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTGREEN"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTGREEN"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations \n\t      you'd like to insert with. The password insertion is censored, and you can peek \n\t      the password you've inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);
        } else {
            printf("\tPersonal E-mail:\t%s\n\tPhone Number:\t\t%s\n\tSKYR Username:\t\t%s\n      " ANSI_COLOR_LIGHTYELLOW"> SKYR Password:\t\t%s\n"ANSI_COLOR_RESET, ACMInputs.Email, ACMInputs.PhoneNumber, ACMInputs.Username, ACMInputs.HiddenPasswordShown);
            puts("\n\tYou have chosen to fill the part in " ANSI_COLOR_LIGHTYELLOW"SKYR Password."ANSI_COLOR_RESET "\n\tPlease proceed to fill in your password profile account.");
            puts(ANSI_COLOR_LIGHTMAGENTA"\tNote: The password must contains at least 8 characters, with any kind of combinations \n\t      you'd like to insert with. The password insertion is censored, and you can peek \n\t      the password you've inserted with an optional right-side choice ONLY in here."ANSI_COLOR_RESET);
        }

        printf("\nSKYR Password: ");
        fgets(InputPassword, BUFSIZE07, stdin);

        while (strlen(InputPassword) <= 8) {
            CP = true;
            if (AllEmpty >= 0 && AllEmpty <= 4 && !VisitedCP) { AllEmpty += 1; EmptyCP = true; VisitedCP = true; }
            strcpy(ACMInputs.HiddenPasswordShown, "... (Unknown)?");
            AccountRecoveryMenu(ACMSelected);
        }
        
        InputPassword[strlen(InputPassword) - 1] = '\0';
        CP = true;
        if (AllEmpty >= 0 && AllEmpty <= 4 && VisitedCP)  { AllEmpty -= 1; EmptyCP = false; VisitedCP = false; }

        for (int i = 0; (long long unsigned int)i < strlen(InputPassword); i++) {
            if (i == 0) { strcpy(HiddenPassword, "*"); }
            else        { strcat(HiddenPassword, "*"); }
        } strcpy(ACMInputs.Password, InputPassword);
        strcpy(ACMInputs.HiddenPasswordShown, HiddenPassword);
        AccountRecoveryMenu(ACMSelected);
    }
}