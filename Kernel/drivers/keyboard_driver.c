#include <keyboard_driver.h>
#include <scheduler.h>
#include <defs.h>

#define ENCODER_PORT 0x60
#define CTRL_PORT 0x64

enum CTRL_MASK {

    KBD_CTRL_MASK_OUT_BUF = 1,    // 00000001
    KBD_CTRL_MASK_IN_BUF = 2,     // 00000010
    KBD_CTRL_MASK_SYSTEM = 4,     // 00000100
    KBD_CTRL_MASK_CMD_DATA = 8,   // 00001000
    KBD_CTRL_MASK_LOCKED = 0x10,  // 00010000
    KBD_CTRL_MASK_AUX_BUF = 0x20, // 00100000
    KBD_CTRL_MASK_TIMEOUT = 0x40, // 01000000
    KBD_CTRL_MASK_PARITY = 0x80   // 10000000
};
enum CTRL_CMD {
    KBD_CTRL_CMD_DISABLE = 0xAD,
    KBD_CTRL_CMD_ENABLE = 0xAE
};

#define KBD_SIZE           256

#define MAYUS_OFFSET       ('a' - 'A')
#define IS_ASCII_LETTER(l) ((l) >= 'a' && (l) <= 'z')

#define LSHIFT_MK          0x2A
#define LSHIFT_BK          0xAA
#define RSHIFT_MK          0x36
#define RSHIFT_BK          0xB6
#define CAPS_MK            0x3A
#define LCNTRL_MK          0x1D
#define LCNTRL_BK          0X9D

// CONTROL + R save registers
#define SAVE_REG_KEY 'R'

static char buffer[BUFFER_SIZE];
static uint16_t index = 0;
static uint8_t caps_locked = 0;
static uint8_t shift_pressed = 0;
static uint8_t cntrl_pressed = 0;
static uint8_t *cntrl_listener = &cntrl_pressed;

static uint8_t ctrl_d_flag = 0;

static char US_1[KBD_SIZE] = {
    0,    // 0x00 - Null
    27,    // 0x01 - Escape
    '1',  // 0x02 - '1'
    '2',  // 0x03 - '2'
    '3',  // 0x04 - '3'
    '4',  // 0x05 - '4'
    '5',  // 0x06 - '5'
    '6',  // 0x07 - '6'
    '7',  // 0x08 - '7'
    '8',  // 0x09 - '8'
    '9',  // 0x0A - '9'
    '0',  // 0x0B - '0'
    '-',  // 0x0C - '-'
    '=',  // 0x0D - '='
    '\b', // 0x0E - Backspace
    '\t', // 0x0F - Tab
    'q',  // 0x10 - 'Q'
    'w',  // 0x11 - 'W'
    'e',  // 0x12 - 'E'
    'r',  // 0x13 - 'R'
    't',  // 0x14 - 'T'
    'y',  // 0x15 - 'Y'
    'u',  // 0x16 - 'U'
    'i',  // 0x17 - 'I'
    'o',  // 0x18 - 'O'
    'p',  // 0x19 - 'P'
    '[',  // 0x1A - '['
    ']',  // 0x1B - ']'
    '\n', // 0x1C - Enter
    0,    // 0x1D - Control (Left Ctrl)
    'a',  // 0x1E - 'A'
    's',  // 0x1F - 'S'
    'd',  // 0x20 - 'D'
    'f',  // 0x21 - 'F'
    'g',  // 0x22 - 'G'
    'h',  // 0x23 - 'H'
    'j',  // 0x24 - 'J'
    'k',  // 0x25 - 'K'
    'l',  // 0x26 - 'L'
    ';',    // 0x27 - (Unused)
    '\'', // 0x28 - '''
    '`',  // 0x29 - '`'
    0,    // 0x2A - Shift (Left Shift)
    '\\', // 0x2B - '\'
    'z',  // 0x2C - 'Z'
    'x',  // 0x2D - 'X'
    'c',  // 0x2E - 'C'
    'v',  // 0x2F - 'V'
    'b',  // 0x30 - 'B'
    'n',  // 0x31 - 'N'
    'm',  // 0x32 - 'M'
    ',',  // 0x33 - ',' (comma)
    '.',    // 0x34 - '.' (period)
    '/',    // 0x35 - '/' (forward slash)
    0,    // 0x36 - Shift (Right Shift)
    '*',    // 0x37 - (Print Screen)
    0,    // 0x38 - Alt (Left Alt)
    ' ',  // 0x39 - Space
    0,    // 0x3A - Caps Lock
    0,    // 0x3B - (F1)
    0,    // 0x3C - (F2)
    0,    // 0x3D - (F3)
    0,    // 0x3E - (F4)
    0,    // 0x3F - (F5)
    0,    // 0x40 - (F6)
    0,    // 0x41 - (F7)
    0,    // 0x42 - (F8)
    0,    // 0x43 - (F9)
    0,    // 0x44 - (F10)
    0,    // 0x45 - Num Lock
    0,    // 0x46 - Scroll Lock
    '7',  // 0x47 - Numpad 7
    '^',  // 0x48 - Numpad 8
    '9',  // 0x49 - Numpad 9
    '-',  // 0x4A - Numpad '-'
    '4',  // 0x4B - Numpad 4
    '5',  // 0x4C - Numpad 5
    '6',  // 0x4D - Numpad 6
    '+',  // 0x4E - Numpad '+'
    '1',  // 0x4F - Numpad 1
    'v',  // 0x50 - Numpad 2
    '3',  // 0x51 - Numpad 3
    '0',  // 0x52 - Numpad 0
    '.',  // 0x53 - Numpad '.'
    0,    // 0x54 - (Unused)
    0,    // 0x55 - (Unused)
    0,    // 0x56 - (Unused)
    0,    // 0x57 - (F11)
    0,    // 0x58 - (F12)
    0,    // 0x59 - (Unused)
    0,    // 0x5A - (Unused)
    0,    // 0x5B - (Unused)
    0,    // 0x5C - (Unused)
    0,    // 0x5D - (Unused)
    0,    // 0x5E - (Unused)
    0,    // 0x5F - (Unused)
    0,    // 0x60 - (Unused)
    0,    // 0x61 - (Unused)
    0,    // 0x62 - (Unused)
    0,    // 0x63 - (Unused)
    0,    // 0x64 - (Unused)
    0,    // 0x65 - (Unused)
    0,    // 0x66 - (Unused)
    0,    // 0x67 - (Unused)
    0,    // 0x68 - (Unused)
    0,    // 0x69 - (Unused)
    0,    // 0x6A - (Unused)
    0,    // 0x6B - (Unused)
    0,    // 0x6C - (Unused)
    0,    // 0x6D - (Unused)
    0,    // 0x6E - (Unused)
    0,    // 0x6F - (Unused)
    0,    // 0x70 - (Unused)
    0,    // 0x71 - (Unused)
    0,    // 0x72 - (Unused)
    0,    // 0x73 - (Unused)
    0,    // 0x74 - (Unused)
    0,    // 0x75 - (Unused)
    0,    // 0x76 - (Unused)
    0,    // 0x77 - (Unused)
    0,    // 0x78 - (Unused)
    0,    // 0x79 - (Unused)
    0,    // 0x7A - (Unused)
    0,    // 0x7B - (Unused)
    0,    // 0x7C - (Unused)
    0,    // 0x7D - (Unused)
    0,    // 0x7E - (Unused)
    0     // 0x7F - (Unused)
};

static char shift_US_1[KBD_SIZE] = {
    0,   0,   /*Numbers shift locked*/ '|',
    '@', '#', '$',
    '%', '^', '&',
    '*', '(', ')',
    '_', '+', 0,
    0, /* Backspace and tab */
    'Q', 'W', 'E',
    'R', 'T', 'Y',
    'U', 'I', 'O',
    'P', '{', '}',
    0,   0, /*Enter and control key*/
    'A', 'S', 'D',
    'F', 'G', 'H',
    'J', 'K', 'L',
    ':', '"', '~',
    0,   0,   'Z',
    'X', 'C', 'V',
    'B', 'N', 'M',
    '<', '>', '?',
    0,   0,   0, /* Alt */
    ' ',         /* Space bar */
    0,           /* Caps lock */
    0,   0,   0,
    0,   0,   0,
    0,   0,   0,
    0,      /* F1 ... F10 keys */
    0,      /* Num lock */
    0,      /* Scroll Lock */
    0,      /* Home key */
    0,      /* Up Arrow */
    0,      /* Page Up */
    0,   0, /* Left Arrow */
    0,   0, /* Right Arrow */
    0,   0, /* End key*/
    0,      /* Down Arrow */
    0,      /* Page Down */
    0,      /* Insert Key */
    0,      /* Delete Key */
    0,   0,   0,
    0, /* F11 Key */
    0, /* F12 Key */
    0, /* Undefined Keys*/
};

void kbd_send_enc_cmd(uint8_t cmd) {
    while (1) {
        if ((inb(CTRL_PORT) & KBD_CTRL_MASK_IN_BUF) == 0)
            break;
    }
    outb(ENCODER_PORT, cmd);
}

void kbd_send_ctrl_cmd(uint8_t cmd) {
    while (1) {
        if ((inb(CTRL_PORT) & KBD_CTRL_MASK_IN_BUF) == 0)
            break;
    }
    outb(CTRL_PORT, cmd);
}

void kbd_disable() {
    kbd_send_ctrl_cmd(KBD_CTRL_CMD_DISABLE);
}

void kbd_enable() {
    kbd_send_ctrl_cmd(KBD_CTRL_CMD_ENABLE);
}

static void ctrl_c_handler() {
    process_t *foreground_process = get_foreground_process();
    if (foreground_process == NULL)
        return;

    kill_process(foreground_process->pid);
}

static void ctrl_d_handler() {
    ctrl_d_flag = 1;
}

void keyboard_handler() {

    uint8_t scan_code = inb(ENCODER_PORT);
    if ((scan_code == LSHIFT_MK) || (scan_code == RSHIFT_MK)) {
        shift_pressed = 1;
        return;
    }
    if ((scan_code == LSHIFT_BK) || (scan_code == RSHIFT_BK)) {
        shift_pressed = 0;
        return;
    }
    if (scan_code == LCNTRL_MK) {
        cntrl_pressed = 1;
        (*cntrl_listener) = cntrl_pressed;
        return;
    }
    if (scan_code == LCNTRL_BK) {
        cntrl_pressed = 0;
        (*cntrl_listener) = cntrl_pressed;
        return;
    }
    if (scan_code == CAPS_MK) {
        caps_locked = !caps_locked;
        return;
    }
    if (index >= BUFFER_SIZE || scan_code >= KBD_SIZE) {
        return;
    }
    uint8_t character;
    if (shift_pressed) {
        character = shift_US_1[scan_code];
    } else {
        character = US_1[scan_code];
    }
    if (character == 0) {
        return; // no character to map
    }
    if (caps_locked && IS_ASCII_LETTER(character)) {
        buffer[index] = character - MAYUS_OFFSET;
    } else if (cntrl_pressed) {
        switch (character) {
            case 'c':
                ctrl_c_handler();
                break;

            case 'd':
                ctrl_d_handler();

            default:
                break;
        }

    } else {
        buffer[index] = character;
    }
    index++;
    buffer[index] = 0;
}

int kbd_get_buffer(char *buffer_ret) {
    if (ctrl_d_flag) {
        ctrl_d_flag = 0;
        return EOF;
    }
    memcpy(buffer_ret, buffer, index);
    return 0;
}

void kbd_clear_buffer() {
    buffer[0] = 0;
    index = 0;
}

uint16_t kbd_get_current_index() {
    return index;
}

char kbd_get_last_key() {
    if (index > 0) {
        return buffer[index - 1];
    }
    return 0;
}

char kbd_get_rm_last_key() {
    if (index > 0) {
        char toReturn = buffer[index - 1];
        index--;
        buffer[index] = 0;
        return toReturn;
    }
    return 0;
}

void kbd_sets_cntrl_listener(uint8_t *listener) {
    cntrl_listener = listener;
}

uint8_t kbd_is_cntrl_pressed() {
    return cntrl_pressed;
}

uint8_t kbd_is_save_reg_shortcut() {
    if (cntrl_pressed &&
        ((kbd_get_last_key() == SAVE_REG_KEY) ||
         ((kbd_get_last_key() - MAYUS_OFFSET) == SAVE_REG_KEY))) {
        kbd_get_rm_last_key();
        return 1;
    }
    return 0;
}