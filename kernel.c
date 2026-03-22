int cursor_row = 0;
int cursor_col = 0;

void clear_screen() {
    char *video = (char*)0xB8000;

    for(int i = 0; i < 80 * 25; i++) {
        video[i*2] = ' ';
        video[i*2 + 1] = 0x07;
    }

    cursor_row = 0;
    cursor_col = 0;
}

void scroll() {
    char *video = (char*)0xB8000;

    for(int i=0; i< 24 * 80 * 2;i++) {
        video[i] = video[i + 160];
    }

    for(int i=24 * 80 * 2;i <25 * 80 * 2; i += 2) {
        video[i] = ' ';
        video[i+1] =0x07;
    }
    cursor_row = 24;
}

void print_char(char c) {
    char *video = (char*)0xB8000;

    int index = (cursor_row * 80 + cursor_col) * 2;

    video[index]=c;
    video[index + 1] = 0x07;

    cursor_col++;

    if(cursor_col >= 80) {
        cursor_col = 0;
        cursor_row++;
    }

    if(cursor_row >= 25) {
        scroll();
    }
}

void print_string(char *msg) {
    for(int i = 0; msg[i] != '\0'; i++) {
        if(msg[i] == '\n') {
            cursor_row++;
            cursor_col = 0;
         }else{
             print_char(msg[i]);
         }
   }
}

void main() {
    clear_screen();

    for(int i = 0;i < 30; i++) {
        print_string("Scrolling working line\n");
    }
}
