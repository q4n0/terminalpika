#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/utsname.h>

#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

char* get_current_time() {
    time_t t;
    struct tm *tm_info;
    static char buffer[26];
    time(&t);
    tm_info = localtime(&t);
    strftime(buffer, 26, "%a %b %d %H:%M:%S", tm_info);
    return buffer;
}

char* get_distro() {
    static char distro[256];
    FILE *fp = fopen("/etc/os-release", "r");
    if (fp) {
        while (fgets(distro, sizeof(distro), fp)) {
            if (strncmp(distro, "PRETTY_NAME=", 12) == 0) {
                char *start = strchr(distro, '"') + 1;
                char *end = strrchr(distro, '"');
                if (end) {
                    *end = '\0';
                }
                fclose(fp);
                return start;
            }
        }
        fclose(fp);
    }
    return "Unknown Distro";
}

void print_banner_and_info(const char *user, const char *host, const char *timeStr, const char *kernel, const char *distro) {
    const char *ascii_art[] = {
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠶⠤⢤⣀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡤⠶⠾⠷⠶⠶⣤⣈⣷",
        "⠀⠀⠀⠀⠀⠀⣠⠾⢀⣤⣴⣶⣶⣶⣶⣦⣤⡉⠛⢦⡀",
        "⠀⠀⠀⠀⢀⡾⢡⠞⠻⣿⣿⡿⢻⣿⣿⣿⣿⡿⠃⠀⠻⣆",
        "⠀⠀⠀⠀⣾⢡⣿⠀⠀⣿⡟⠀⠀⣿⣿⣿⣿⣇⠀⠀⡀⢻⣆⣤⠶⠒⠒⠶⣤⡀",
        "⠀⠀⠀⠀⣿⣾⣿⣄⣴⣿⣷⡀⣠⣿⣿⣿⣿⣿⣿⣿⣷⠘⣿⠧⣤⠻⠽⠂⢈⣿",
        "⠀⠀⣠⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⢸⣿⡛⠛⣴⣲⠄⢸⡇",
        "⢰⡟⠁⠀⠈⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢡⡿⠙⢿⣦⣤⣤⣤⠾⠃",
        "⢸⡇⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢛⣵⠟⠀⠀⣼⠃",
        "⠈⠻⣆⠀⠀⠀⠀⠀⣻⠾⢿⣿⣛⣛⣻⣯⣵⡾⠛⠁⠀⠀⢀⣿",
        "⠀⠀⠙⠷⣄⣀⣀⣠⡿⠀⠀⠀⠀⠀⠀⠀⠀⢷⡀⠀⠀⢀⣾⠃",
        "⠀⠀⠀⠀⠈⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠳⠾⠛⠁"
    };

    char info[5][50];
    snprintf(info[0], 50, "USER: %s", user);
    snprintf(info[1], 50, "HOST: %s", host);
    snprintf(info[2], 50, "TIME: %s", timeStr);
    snprintf(info[3], 50, "KERNEL: %s", kernel);
    snprintf(info[4], 50, "DISTRO: %s", distro);

    int art_lines = sizeof(ascii_art) / sizeof(ascii_art[0]);
    int info_lines = sizeof(info) / sizeof(info[0]);
    int start_info = 3;  // Start the info from the 4th line of ASCII art

    for (int i = 0; i < art_lines; i++) {
        printf(CYAN "%-55s" RESET, ascii_art[i]);
        if (i >= start_info && i < start_info + info_lines) {
            printf(WHITE "%-40s" RESET, info[i - start_info]);
        }
        printf("\n");
    }
}

int main() {
    struct utsname unameData;
    char *timeStr = get_current_time();
    char *user = getenv("USER");
    uname(&unameData);
    char *distro = get_distro();
    print_banner_and_info(user, unameData.nodename, timeStr, unameData.release, distro);
    return 0;
}
