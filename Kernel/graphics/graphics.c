// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <graphics.h>

#define LEFT_TOP_CORNER     0xDA
#define RIGHT_TOP_CORNER    0xBF
#define LEFT_BOTTOM_CORNER  0xC0
#define RIGHT_BOTTOM_CORNER 0XD9
#define HZ_LINE             0xC4
#define VT_LINE             0xB3
#define MIDDLE_TOP          0xC2
#define MIDDLE_BOTTOM       0xC1
#define SQUARE              0xFE

typedef struct gcontext {
    area_t area;
    position_t last_cursor_pos;
} gcontext_t;

typedef enum {
    FULL_DISTRIBUTION = 0,
    SPLIT_DISTRIBUTION
} distribution_t;

static int allocated_windows_count = 0;
distribution_t current_distribution = FULL_DISTRIBUTION;

gcontext_t contexts[3];

area_t create_window(area_t area) {
    enable_cursor(15, 16);
    disable_scroll();

    move_cursor((position_t){area.first_row, area.first_col});
    set_working_area(area);
    set_foreground_color(area.first_row, area.first_col,
                         area.first_row + area.height - 1,
                         area.first_col + area.width - 1, BLACK);
    // draw_bottom_line(area);
    // draw_top_line(area);
    for (int i = area.first_row + 1; i < (area.first_row + area.height - 1);
         i++) {
        for (int j = 0; j < 2; j++) {
            if (j % 2) {
                move_cursor((position_t){i, area.first_col + area.width - 1});
                print_char(VT_LINE);
            } else {
                move_cursor((position_t){i, area.first_col});
                print_char(VT_LINE);
            }
        }
    }
    area_t new_area = {area.width - 2, area.height - 2, area.first_col + 1,
                       area.first_row + 1};
    set_working_area(new_area);
    set_foreground_color(new_area.first_row, new_area.first_col,
                         new_area.first_row + new_area.height - 1,
                         new_area.first_col + new_area.width - 1, GREEN);
    move_cursor((position_t){new_area.first_row, new_area.first_col});
    enable_scroll();
    return new_area;
}

void create_line(area_t area, enum colors color) {
    if (area.height > 1)
        return;
    enable_cursor(15, 16);
    move_cursor((position_t){area.first_row, area.first_col});

    set_working_area(area);
    set_background_color(area.first_row, area.first_col,
                         area.first_row + area.height - 1,
                         area.first_col + area.width - 1, color);
}

void create_bottom_module() {

    area_t bottom_line = {MAX_COLS, 1, 0, MAX_ROWS - 1};
    enable_cursor(15, 16);
    move_cursor((position_t){bottom_line.first_row, bottom_line.first_col});
    set_foreground_color(bottom_line.first_row, 0, bottom_line.first_row,
                         MAX_COLS - 1, WHITE);
    int col = 0;
    print_string(" CTRL+C ");
    col = strlen(" CTRL+C ");
    set_background_color(bottom_line.first_row, col, bottom_line.first_row,
                         col + strlen(" KILL PROCESS"), CYAN);
    print_string(" KILL PROCESS ");

    col += strlen(" KILL PROCESS ");
    col += 5;
    move_cursor((position_t){bottom_line.first_row, col});
    print_string(" CTRL+R ");
    col += strlen(" CTRL+R ");
    set_background_color(bottom_line.first_row, col, bottom_line.first_row,
                         col + strlen(" REG SNAPSHOT"), CYAN);
    print_string(" REG SNAPSHOT ");

    col += strlen(" REG SNAPSHOT ");
    col += 6;
    move_cursor((position_t){bottom_line.first_row, col});
    print_string(" CTRL+D ");
    col += strlen(" CTRL+D ");
    set_background_color(bottom_line.first_row, col, bottom_line.first_row,
                         col + strlen(" SEND EOF"), CYAN);
    print_string(" SEND EOF ");
}

context_id_t get_context_id() {
    switch (current_distribution) {
        case SPLIT_DISTRIBUTION:
            if (allocated_windows_count == 0) {
                allocated_windows_count++;
                return LEFT;
            } else
                return RIGHT;
        default:
            return FULL;
    }
}

void split_screen_distribution() {

    allocated_windows_count = 0;
    current_distribution = SPLIT_DISTRIBUTION;

    area_t screen = {MAX_COLS, MAX_ROWS - 2, 0, 1};

    set_working_area(screen);
    create_window(screen);
    clear_screen();

    set_foreground_color(1, MAX_COLS / 2, MAX_ROWS - 2, MAX_COLS / 2,
                         LIGHT_GRAY);
    move_cursor((position_t){1, MAX_COLS / 2});
    print_char(MIDDLE_TOP);
    for (int i = 2; i < MAX_ROWS - 2; i++) {
        move_cursor((position_t){i, MAX_COLS / 2});
        print_char(VT_LINE);
    }
    move_cursor((position_t){MAX_ROWS - 2, MAX_COLS / 2});
    print_char(MIDDLE_BOTTOM);

    area_t left = {MAX_COLS / 2 - 2, MAX_ROWS - 4, 1, 2};
    contexts[0].area = left;
    move_cursor((position_t){left.first_row, left.first_col});
    contexts[0].last_cursor_pos = get_cursor_position();

    area_t right = {MAX_COLS / 2 - 2, MAX_ROWS - 4, MAX_COLS / 2 + 1, 2};
    contexts[1].area = right;
    move_cursor((position_t){right.first_row, right.first_col});
    contexts[1].last_cursor_pos = get_cursor_position();

    create_bottom_module();
    move_cursor(contexts[0].last_cursor_pos);
}

void full_screen_distribution() {
    allocated_windows_count = 0;
    current_distribution = FULL;

    area_t screen = {MAX_COLS, MAX_ROWS - 2, 0, 1};
    screen = create_window(screen);
    contexts[2].area = screen;
    contexts[2].last_cursor_pos = get_cursor_position();

    clear_screen();

    // create_line(top_line, CYAN);
    // set_foreground_color(0, 0, 0, MAX_COLS - 1, WHITE);
    // print_string(" KerberOS");

    // create_bottom_module();
    move_cursor(contexts[2].last_cursor_pos);
}

static void load_context(context_id_t id) {
    set_working_area(contexts[id].area);
    move_cursor(contexts[id].last_cursor_pos);
}

void gprint_char(const char c, context_id_t id) {
    load_context(id);
    print_char(c);
    contexts[id].last_cursor_pos = get_cursor_position();
}

void gprint_string(const char *str, context_id_t id) {
    load_context(id);
    print_string(str);
    contexts[id].last_cursor_pos = get_cursor_position();
}

void gprint_new_line(context_id_t id) {
    load_context(id);
    print_new_line();
    contexts[id].last_cursor_pos = get_cursor_position();
}

void gdelete_char(context_id_t id) {
    load_context(id);
    delete_char();
    contexts[id].last_cursor_pos = get_cursor_position();
}

void gclear_screen(context_id_t id) {
    load_context(id);
    clear_screen();
    contexts[id].last_cursor_pos = get_cursor_position();
}

void gsnapshot() {
    position_t pos = get_cursor_position();
    area_t current = get_current_working_area();
    char *msg = "TAKING SNAPSHOT";
    int len = strlen(msg);
    set_working_area((area_t){16, 1, MAX_COLS / 2 - len / 2, 0});
    print_string(msg);
    disable_cursor();
    set_working_area((area_t){MAX_COLS, MAX_ROWS - 2, 0, 1});
    set_background_color(1, 0, MAX_ROWS - 2, MAX_COLS - 1, LIGHT_GRAY);

    uint64_t seconds = get_seconds();
    uint64_t last_seconds;
    while ((last_seconds = get_seconds()) - seconds < 2)
        ;
    set_working_area((area_t){16, 1, MAX_COLS / 2 - len / 2, 0});
    enable_cursor(15, 16);
    clear_line(0);
    set_background_color(1, 0, MAX_ROWS - 2, MAX_COLS - 1, BLACK);
    set_working_area(current);
    move_cursor(pos);
}

void gfocus(context_id_t target) {
    if (target == FULL)
        return;

    context_id_t other_screen;
    if (target == LEFT)
        other_screen = RIGHT;
    else
        other_screen = LEFT;

    area_t bkup = contexts[target].area;
    area_t other_area = {contexts[other_screen].area.width + 2,
                         contexts[other_screen].area.height + 2,
                         contexts[other_screen].area.first_col - 1,
                         contexts[other_screen].area.first_row - 1};

    set_working_area(other_area);
    move_cursor((position_t){other_area.first_row, other_area.first_col + 1});
    set_foreground_color(other_area.first_row, other_area.first_col + 1,
                         other_area.first_row, other_area.first_col + 1 + 3,
                         LIGHT_GRAY);
    print_char(HZ_LINE);
    print_char(HZ_LINE);
    print_char(HZ_LINE);

    area_t new_area = {bkup.width + 2, bkup.height + 2, bkup.first_col - 1,
                       bkup.first_row - 1};
    set_working_area(new_area);

    move_cursor((position_t){new_area.first_row, new_area.first_col + 1});
    set_foreground_color(new_area.first_row, new_area.first_col + 1,
                         new_area.first_row, new_area.first_col + 1 + 2, CYAN);
    print_char(SQUARE);
    print_char(SQUARE);
    print_char(SQUARE);

    set_working_area(bkup);
    move_cursor(contexts[target].last_cursor_pos);
}