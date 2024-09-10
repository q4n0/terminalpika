#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <time.h>

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define WHITE   "\033[37m"
#define GREEN   "\033[32m"

// Function to get the current time as a string
char* get_current_time() {
    time_t t;
    struct tm *tm_info;
    static char buffer[26];

    time(&t);
    tm_info = localtime(&t);
    strftime(buffer, 26, "%a %b %d %H:%M:%S %Y", tm_info);

    return buffer;
}

int main() {
    struct utsname unameData;
    char *timeStr = get_current_time();
    char *user = getenv("USER");
    uname(&unameData);

    // Banner with user, host, and time information
    printf(RED
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠶⠤⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡤⠶⠾⠷⠶⠶⣤⣈⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⣠⠾⢁⣤⣴⣶⣶⣶⣶⣦⣤⡉⠛⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⢀⡾⢡⠞⠻⣿⣿⡿⢻⣿⣿⣿⣿⡿⠃⠀⠻⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⣾⢡⣿⠀⠀⣿⡟⠀⠀⣿⣿⣿⣿⣇⠀⠀⡀⢻⣆⣤⠶⠒⠒⠶⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⣿⣾⣿⣄⣴⣿⣷⡀⣠⣿⣿⣿⣿⣿⣿⣿⣷⠘⣿⠧⣤⠻⠽⠂⢈⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⣠⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⢸⣿⡛⠛⣴⣲⠄⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⢰⡟⠁⠀⠈⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢡⡿⠙⢿⣦⣤⣤⣤⠾⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⢸⡇⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢛⣵⠟⠀⠀⣼⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠈⠻⣆⠀⠀⠀⠀⠀⣻⠾⢿⣿⣛⣛⣻⣯⣵⡾⠛⠁⠀⠀⢀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠙⠷⣄⣀⣀⣠⡿⠀⠀⠀⠀⠀⠀⠀⠀⢷⡀⠀⠀⢀⣾⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠈⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠳⠾⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           RESET WHITE
           "                             USER: %s\n"
           "                             HOST: %s\n"
           "                             TIME: %s\n"
           RESET,
           user, unameData.nodename, timeStr);

    return 0;
}
