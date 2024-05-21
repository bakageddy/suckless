/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 5000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cat                 read arbitrary file             path
 * cpu_freq            cpu frequency in MHz            NULL
 * cpu_perc            cpu usage in percent            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/)
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD/FreeBSD
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 */

#define GRAYSCALE_BG "#F7F7F7"
#define GRAYSCALE_FG "#141414"
#define GRAYSCALE_GRAY "#A0A0A0"

#define GRUVBOX_BLACK "#1d2021"
#define GRUVBOX_RED "#fb4934"
#define GRUVBOX_GREEN "#b8bb26"
#define GRUVBOX_YELLOW "#fabd2f"
#define GRUVBOX_BLUE "#83a598"
#define GRUVBOX_MAGENTA "#d3869b"
#define GRUVBOX_CYAN "#8ec07c"
#define GRUVBOX_WHITE "#d4be98"
#define GRUVBOX_ORANGE "#fe8019"

#define SOLARIZED_BLACK		"#002b36"
#define SOLARIZED_WHITE		"#839496"
#define SOLARIZED_RED		"#dc3545"
#define SOLARIZED_ORANGE	"#cb4b16"
#define SOLARIZED_YELLOW	"#b58900"
#define SOLARIZED_GREEN		"#859900"
#define SOLARIZED_BLUE		"#268bd2"
#define SOLARIZED_CYAN		"#2aa198"
#define SOLARIZED_PURPLE	"#6c71c4"
#define SOLARIZED_PINK		"#d33682"

static const struct arg args[] = {
	/* function format          argument */
	{ username, "^b" SOLARIZED_RED "^^c" SOLARIZED_BLACK "^  : %s ^d^ ", NULL},
	{ cpu_perc, "^b" SOLARIZED_ORANGE "^^c" SOLARIZED_BLACK "^ 🖥 : %s ^d^ ", NULL},
	{ run_command,  "^b" SOLARIZED_YELLOW "^^c" SOLARIZED_BLACK "^  : %s ^d^ ", "amixer sget Master | tail -1 | awk '{print $5 }' | sed 's@\\(\\[\\|\\]\\)@@g'"},
	{ ram_perc, "^b" SOLARIZED_GREEN "^^c" SOLARIZED_BLACK "^  : %s ^d^ ", NULL},
	{ netspeed_rx, "^b" SOLARIZED_CYAN "^^c" SOLARIZED_BLACK "^ ⇅: %s ^d^ ", "enp2s0"},
	{ datetime, "^b" SOLARIZED_BLUE "^^c" SOLARIZED_BLACK "^ %s ^d^ ", "%d-%b-%y %H-%M" },
	{ weather, "^b" SOLARIZED_PURPLE "^^c" SOLARIZED_BLACK "^ %s ^d^ ", NULL },
};
