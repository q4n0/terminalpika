#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <unistd.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREY    "\033[90m"
#define WHITE   "\033[37m"

// [Previous utility functions remain the same]
char* get_current_time() {
    time_t t;
    struct tm *tm_info;
    static char buffer[26];
    time(&t);
    tm_info = localtime(&t);
    strftime(buffer, 26, "%a %b %d %H:%M:%S", tm_info);
    return buffer;
}

char* get_shell() {
    char* shell = getenv("SHELL");
    if (!shell) return "Unknown Shell";
    return strrchr(shell, '/') ? strrchr(shell, '/') + 1 : shell;
}

char* get_cpu_info() {
    static char cpu_info[256];
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (fp) {
        char line[256];
        char model_name[256] = "";
        float mhz = 0.0;
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "model name", 10) == 0) {
                char* value = strchr(line, ':');
                if (value) {
                    strcpy(model_name, value + 2);
                    model_name[strlen(model_name)-1] = '\0';
                }
            }
            if (strncmp(line, "cpu MHz", 7) == 0) {
                sscanf(line, "cpu MHz : %f", &mhz);
            }
        }
        snprintf(cpu_info, sizeof(cpu_info), "%.1f GHz %s", mhz/1000, model_name);
        fclose(fp);
        return cpu_info;
    }
    return "Unknown CPU";
}

char* get_memory_info() {
    static char mem_info[64];
    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        unsigned long total_ram = si.totalram * si.mem_unit / (1024 * 1024 * 1024);
        unsigned long free_ram = si.freeram * si.mem_unit / (1024 * 1024 * 1024);
        unsigned long used_ram = total_ram - free_ram;
        snprintf(mem_info, sizeof(mem_info), "%luGB/%luGB", used_ram, total_ram);
        return mem_info;
    }
    return "Unknown RAM";
}

char* get_distro() {
    static char distro[256];
    FILE *fp = fopen("/etc/os-release", "r");
    if (fp) {
        while (fgets(distro, sizeof(distro), fp)) {
            if (strncmp(distro, "PRETTY_NAME=", 12) == 0) {
                char *start = strchr(distro, '"') + 1;
                char *end = strrchr(distro, '"');
                if (end) *end = '\0';
                fclose(fp);
                return start;
            }
        }
        fclose(fp);
    }
    return "Unknown Distro";
}

void print_banner_and_info(const char *user, const char *host, const char *timeStr, 
                          const char *kernel, const char *distro, const char *shell,
                          const char *cpu, const char *ram) {
    const char *ascii_art[] = {
        "⠀⠀⠀⠀⢀⡠⠤⠔⢲⢶⡖⠒⠤⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⣠⡚⠁⢀⠀⠀⢄⢻⣿⠀⠀⠀⡙⣷⢤⡀⠀⠀⠀⠀⠀⠀",
        "⠀⡜⢱⣇⠀⣧⢣⡀⠀⡀⢻⡇⠀⡄⢰⣿⣷⡌⣢⡀⠀⠀⠀⠀",
        "⠸⡇⡎⡿⣆⠹⣷⡹⣄⠙⣽⣿⢸⣧⣼⣿⣿⣿⣶⣼⣆⠀⠀⠀",
        "⣷⡇⣷⡇⢹⢳⡽⣿⡽⣷⡜⣿⣾⢸⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀",
        "⣿⡇⡿⣿⠀⠣⠹⣾⣿⣮⠿⣞⣿⢸⣿⣛⢿⣿⡟⠯⠉⠙⠛⠓",
        "⣿⣇⣷⠙⡇⠀⠁⠀⠉⣽⣷⣾⢿⢸⣿⠀⢸⣿⢿⠀⠀⠀⠀⠀",
        "⡟⢿⣿⣷⣾⣆⠀⠀⠘⠘⠿⠛⢸⣼⣿⢖⣼⣿⠘⡆⠀⠀⠀⠀",
        "⠃⢸⣿⣿⡘⠋⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⡆⠇⠀⠀⠀⠀",
        "⠀⢸⡿⣿⣇⠀⠈⠀⠤⠀⠀⢀⣿⣿⣿⣿⣿⣿⣧⢸⠀⠀⠀⠀",
        "⠀⠈⡇⣿⣿⣷⣤⣀⠀⣀⠔⠋⣿⣿⣿⣿⣿⡟⣿⡞⡄⠀⠀⠀",
        "⠀⠀⢿⢸⣿⣿⣿⣿⣿⡇⠀⢠⣿⡏⢿⣿⣿⡇⢸⣇⠇⠀⠀⠀",
        "⠀⠀⢸⡏⣿⣿⣿⠟⠋⣀⠠⣾⣿⠡⠀⢉⢟⠷⢼⣿⣿⠀⠀⠀",
        "⠀⠀⠈⣷⡏⡱⠁⠀⠊⠀⠀⣿⣏⣀⡠⢣⠃⠀⠀⢹⣿⡄⠀⠀",
        "⠀⠀⠘⢼⣿⠀⢠⣤⣀⠉⣹⡿⠀⠁⠀⡸⠀⠀⠀⠈⣿⡇⠀⠀"
    };

    char info[8][100];
    snprintf(info[0], 100, "USER: %s", user);
    snprintf(info[1], 100, "HOST: %s", host);
    snprintf(info[2], 100, "SHELL: %s", shell);
    snprintf(info[3], 100, "DISTRO: %s", distro);
    snprintf(info[4], 100, "KERNEL: %s", kernel);
    snprintf(info[5], 100, "CPU: %s", cpu);
    snprintf(info[6], 100, "RAM: %s", ram);
    snprintf(info[7], 100, "TIME: %s", timeStr);

    int art_lines = sizeof(ascii_art) / sizeof(ascii_art[0]);
    int info_lines = sizeof(info) / sizeof(info[0]);
    int start_info = 3;  // Starting position for info text

    const char* colors[] = {RED, YELLOW, GREY};
    int color_count = sizeof(colors) / sizeof(colors[0]);

    for (int i = 0; i < art_lines; i++) {
        printf("%s%s" RESET, colors[i % color_count], ascii_art[i]);
        if (i >= start_info && i < start_info + info_lines) {
            printf(WHITE "  %s" RESET, info[i - start_info]);
        }
        printf("\n");
    }
}

int main() {
    struct utsname unameData;
    char *timeStr = get_current_time();
    char *user = getenv("USER");
    char *shell = get_shell();
    char *cpu = get_cpu_info();
    char *ram = get_memory_info();
    uname(&unameData);
    char *distro = get_distro();
    
    print_banner_and_info(user, unameData.nodename, timeStr, unameData.release, 
                         distro, shell, cpu, ram);
    return 0;
}
