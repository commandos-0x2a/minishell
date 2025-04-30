#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

// Struct to hold each flag's value, name, and description
struct flag_desc {
    tcflag_t flag;
    const char *name;
    const char *desc;
};

// Generic function to print flags
void print_flags(tcflag_t flags, const struct flag_desc *defs, int count) {
    for (int i = 0; i < count; ++i) {
        printf("  %-10s : %-3s - %s\n", defs[i].name, (flags & defs[i].flag) ? "ON" : "OFF", defs[i].desc);
    }
}

int main() {
    struct termios tio;

    if (tcgetattr(STDIN_FILENO, &tio) != 0) {
        perror("tcgetattr");
        return 1;
    }

    printf("=== Input Flags (c_iflag) ===\n");
    const struct flag_desc input_flags[] = {
        {IGNBRK, "IGNBRK", "Ignore break condition"},
        {BRKINT, "BRKINT", "Signal interrupt on break"},
        {IGNPAR, "IGNPAR", "Ignore characters with parity errors"},
        {PARMRK, "PARMRK", "Mark parity errors"},
        {INPCK,  "INPCK",  "Enable input parity checking"},
        {ISTRIP, "ISTRIP", "Strip 8th bit off characters"},
        {INLCR,  "INLCR",  "Map NL to CR on input"},
        {IGNCR,  "IGNCR",  "Ignore CR"},
        {ICRNL,  "ICRNL",  "Map CR to NL on input"},
        {IXON,   "IXON",   "Enable XON/XOFF output control"},
        {IXOFF,  "IXOFF",  "Enable XON/XOFF input control"},
        {IXANY,  "IXANY",  "Any character restarts output"},
        {IMAXBEL,"IMAXBEL","Ring bell on input overflow"}
    };
    print_flags(tio.c_iflag, input_flags, sizeof(input_flags) / sizeof(input_flags[0]));

    printf("\n=== Output Flags (c_oflag) ===\n");
    const struct flag_desc output_flags[] = {
        {OPOST,  "OPOST",  "Enable output processing"},
        {ONLCR,  "ONLCR",  "Map NL to CR-NL on output"},
        {OCRNL,  "OCRNL",  "Map CR to NL on output"},
        {ONOCR,  "ONOCR",  "Don't output CR at column 0"},
        {ONLRET, "ONLRET", "NL performs CR function"},
        {OFILL,  "OFILL",  "Use fill characters for delay"},
        {OFDEL,  "OFDEL",  "Fill character is DEL"}
    };
    print_flags(tio.c_oflag, output_flags, sizeof(output_flags) / sizeof(output_flags[0]));

    printf("\n=== Control Flags (c_cflag) ===\n");
    const struct flag_desc control_flags[] = {
        {CS5,    "CS5",    "Character size: 5 bits"},
        {CS6,    "CS6",    "Character size: 6 bits"},
        {CS7,    "CS7",    "Character size: 7 bits"},
        {CS8,    "CS8",    "Character size: 8 bits"},
        {CSTOPB, "CSTOPB", "Use two stop bits"},
        {CREAD,  "CREAD",  "Enable receiver"},
        {PARENB, "PARENB", "Enable parity generation/checking"},
        {PARODD, "PARODD", "Use odd parity"},
        {HUPCL,  "HUPCL",  "Hang up on last close"},
        {CLOCAL, "CLOCAL", "Ignore modem control lines"}
    };
    print_flags(tio.c_cflag, control_flags, sizeof(control_flags) / sizeof(control_flags[0]));

    printf("\n=== Local Flags (c_lflag) ===\n");
    const struct flag_desc local_flags[] = {
        {ISIG,   "ISIG",   "Enable INTR, QUIT, SUSP"},
        {ICANON, "ICANON", "Canonical input (line mode)"},
        {ECHO,   "ECHO",   "Echo input characters"},
        {ECHOE,  "ECHOE",  "Echo ERASE as BS-SP-BS"},
        {ECHOK,  "ECHOK",  "Echo KILL"},
        {ECHONL, "ECHONL", "Echo NL"},
        {NOFLSH, "NOFLSH", "Disable flush on INTR/QUIT/SUSP"},
        {TOSTOP, "TOSTOP", "Send SIGTTOU for background output"},
        {IEXTEN, "IEXTEN", "Enable extended input functions"}
    };
    print_flags(tio.c_lflag, local_flags, sizeof(local_flags) / sizeof(local_flags[0]));

    printf("\n=== Control Characters (c_cc[]) ===\n");
    const char *cc_names[] = {
        "VINTR", "VQUIT", "VERASE", "VKILL", "VEOF",
        "VTIME", "VMIN", "VSTART", "VSTOP", "VSUSP",
        "VEOL", "VREPRINT", "VDISCARD", "VWERASE", "VLNEXT"
    };
    int cc_indices[] = {
        VINTR, VQUIT, VERASE, VKILL, VEOF,
        VTIME, VMIN, VSTART, VSTOP, VSUSP,
        VEOL, VREPRINT, VDISCARD, VWERASE, VLNEXT
    };
    for (int i = 0; i < sizeof(cc_indices)/sizeof(cc_indices[0]); ++i) {
        unsigned char val = tio.c_cc[cc_indices[i]];
        printf("  %-10s : %-3d (ASCII: %s)\n", cc_names[i], val,
               (val >= 32 && val < 127) ? (char[]){val, 0} : "CTRL/non-printable");
    }

    printf("\n=== Baud Rates ===\n");
    printf("  Input Speed  : %lu\n", tio.c_ispeed);
    printf("  Output Speed : %lu\n", tio.c_ospeed);

    return 0;
}
