# `struct termios` Overview

The `termios` structure is used for terminal I/O configuration in POSIX systems.

## Main Fields

| Field      | Type       | Description |
|------------|------------|-------------|
| `c_iflag`  | `tcflag_t` | Input mode flags |
| `c_oflag`  | `tcflag_t` | Output mode flags |
| `c_cflag`  | `tcflag_t` | Control mode flags |
| `c_lflag`  | `tcflag_t` | Local mode flags |
| `c_cc`     | `cc_t[]`   | Special control characters |
| `c_ispeed` | `speed_t`  | Input baud rate |
| `c_ospeed` | `speed_t`  | Output baud rate |

---

## Input Flags (`c_iflag`)

| Flag      | Description |
|-----------|-------------|
| `IGNBRK`  | Ignore break condition |
| `BRKINT`  | Signal interrupt on break |
| `IGNPAR`  | Ignore characters with parity errors |
| `PARMRK`  | Mark parity errors |
| `INPCK`   | Enable input parity checking |
| `ISTRIP`  | Strip 8th bit off characters |
| `INLCR`   | Map NL to CR on input |
| `IGNCR`   | Ignore CR |
| `ICRNL`   | Map CR to NL on input |
| `IXON`    | Enable XON/XOFF flow control on output |
| `IXOFF`   | Enable XON/XOFF flow control on input |
| `IXANY`   | Allow any character to restart output |
| `IMAXBEL` | Ring bell when input buffer full |

---

## Output Flags (`c_oflag`)

| Flag      | Description |
|-----------|-------------|
| `OPOST`   | Enable output processing |
| `ONLCR`   | Map NL to CR-NL on output |
| `OCRNL`   | Map CR to NL on output |
| `ONOCR`   | Don't output CR at column 0 |
| `ONLRET`  | NL performs CR function |
| `OFILL`   | Use fill characters for delay |
| `OFDEL`   | Fill character is DEL |
| `NLDLY`   | Newline delay mask |
| `CRDLY`   | Carriage-return delay mask |
| `TABDLY`  | Tab delay mask |
| `BSDLY`   | Backspace delay mask |
| `VTDLY`   | Vertical-tab delay mask |
| `FFDLY`   | Form-feed delay mask |

---

## Control Flags (`c_cflag`)

| Flag       | Description |
|------------|-------------|
| `CSIZE`    | Character size mask |
| `CS5`–`CS8`| Set character size (5 to 8 bits) |
| `CSTOPB`   | Use two stop bits |
| `CREAD`    | Enable receiver |
| `PARENB`   | Enable parity generation and checking |
| `PARODD`   | Use odd parity instead of even |
| `HUPCL`    | Hang up on last close |
| `CLOCAL`   | Ignore modem control lines |

---

## Local Flags (`c_lflag`)

| Flag       | Description |
|------------|-------------|
| `ISIG`     | Enable signals (INTR, QUIT, SUSP) |
| `ICANON`   | Enable canonical input |
| `ECHO`     | Echo input characters |
| `ECHOE`    | Echo ERASE as BS-SP-BS |
| `ECHOK`    | Echo KILL |
| `ECHONL`   | Echo NL |
| `NOFLSH`   | Disable flush after interrupt or quit |
| `TOSTOP`   | Send SIGTTOU for background output |
| `IEXTEN`   | Enable extended functions |

---

## Control Characters (`c_cc[]`)

| Macro      | Description |
|------------|-------------|
| `VINTR`    | Interrupt character |
| `VQUIT`    | Quit character |
| `VERASE`   | Erase character |
| `VKILL`    | Kill line |
| `VEOF`     | End-of-file |
| `VTIME`    | Timeout for non-canonical read |
| `VMIN`     | Minimum chars for non-canonical read |
| `VSTART`   | Start (XON) |
| `VSTOP`    | Stop (XOFF) |
| `VSUSP`    | Suspend |
| `VEOL`     | End-of-line |
| `VREPRINT` | Reprint line |
| `VDISCARD` | Discard output |
| `VWERASE`  | Word erase |
| `VLNEXT`   | Literal next |

---

## Speed Fields

| Field       | Description |
|-------------|-------------|
| `c_ispeed`  | Input speed (baud rate) |
| `c_ospeed`  | Output speed (baud rate) |
