
#include "system.h"
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '-', '=', 0,  /* Backspace */
  0,      /* Tab */
  'q', 'w', 'e', 'r', /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0,    /* Enter key */
    0,      /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 '\'', '`',   0,    /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',      /* 49 */
  'm', ',', '.', '/',   0,          /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    '\0', /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

unsigned int shift_flag = 0;
void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);
    // addToBuffer('c', 0, 0);

    switch (scancode) {
        //backspace
        case 14: {
            backspace_char(csr_x - init_len);
        }
        break;
        //enter
        case 28: {
            putch('\0');
            csr_y++;
            csr_x = 0;
            move_csr();
            makefunc(line,com_len);
            for (int i = 0; i < 256; i++) line[i] = 0;
            com_len = 0;
            wait_com();
        }
        break;
        //shift
        case 42: {
            // shift_flag = 1;
            // putch((char)1);
            // csr_x = 0;
            // csr_y = 0;
            // move_csr();
        }
        //home
        case 71: {
            csr_y = start_line;
            csr_x = init_len;
            move_csr();
        }
        break;
        //arrow left
        case 75: {
            int temp = 80 * (csr_y - start_line) + csr_x;
            if (temp > init_len) {
                csr_x--;
                move_csr();
            }
        }
        break;
        //arrow right
        case 77: {
            int temp = 80 * (csr_y - start_line) + csr_x;
            if (temp < com_len + init_len) {
                csr_x++;
                move_csr();    
            }            
        }
        break;
        //end
        case 79: {
            csr_y = (com_len + init_len) / 80 + start_line;
            csr_x = (com_len + init_len) % 80;
            move_csr();
        }
        break;
        //delete
        case 83: {
            delete_char(csr_x - init_len);
            // refresh_com();
        }
        break;
        default: {

        }
        break;
    }
    
    if (scancode & 0x80)
    {

    }
    else
    {
        if (kbdus[scancode] != 0) {

            insert_char(kbdus[scancode], csr_x - init_len);
        }
    }
}

void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
}