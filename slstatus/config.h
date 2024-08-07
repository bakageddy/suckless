/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 5000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048
#define GRUVBOX_BLACK		"#1d2021"
#define GRUVBOX_RED			"#ff5f5f"
#define GRUVBOX_ORANGE		"#fe8019"
#define GRUVBOX_YELLOW		"#fabd2f"
#define GRUVBOX_GREEN		"#b8bb26"
#define GRUVBOX_CYAN		"#8ec07c"
#define GRUVBOX_BLUE		"#83a598"
#define GRUVBOX_MAGENTA		"#d3869b"
#define GRUVBOX_WHITE		"#d4be98"

#define GRAYSCALE_BG		"#101010"
#define GRAYSCALE FG		"#e3e3e3"
#define GRAYSCALE_GRAY		"#ababab"

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

#define ICEBERG_BLACK "#161821"
#define ICEBERG_WHITE "#c6c8d1"
#define ICEBERG_RED   "#e27878"
#define ICEBERG_GREEN "#b4be82"
#define ICEBERG_ORANGE "#e2a478"
#define ICEBERG_BLUE "#84a0c6"
#define ICEBERG_MAGENTA "#a093c7"
#define ICEBERG_CYAN "#89b8c2"

static const struct arg args[] = {
    /* function format          argument */
    {wifi_essid, "^b" GRUVBOX_WHITE "^^c" GRUVBOX_BLACK "^ 󰤥 : %s ^d^ ", "wlp3s0"},
    {wifi_perc, "^b" GRUVBOX_RED "^^c" GRUVBOX_BLACK "^ 󰤥 : %s ^d^ ", "wlp3s0"},
    {run_command, "^b" GRUVBOX_ORANGE "^^c" GRUVBOX_BLACK "^ 󰕾 : %s ^d^ ",
     "amixer sget Master | tail -1 | awk '{print $5 }' | sed "
     "'s@\\(\\[\\|\\]\\)@@g'"},

    {ram_perc, "^b" GRUVBOX_GREEN "^^c" GRUVBOX_BLACK "^ 󰍛 : %s ^d^ ", NULL},
    {netspeed_rx, "^b" GRUVBOX_CYAN "^^c" GRUVBOX_BLACK "^ ⇅: %s ^d^ ", "wlp3s0"},

    {run_command, "^b" GRUVBOX_BLUE "^^c" GRUVBOX_BLACK "^   %s ^d^ ",
     "~/.software/scripts/elektric_script"},

    {datetime, "^b" GRUVBOX_MAGENTA "^^c" GRUVBOX_BLACK "^ %s ^d^ ", "%d-%b-%y %H-%M"},
};
