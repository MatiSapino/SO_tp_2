#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <lib.h>
#include <rtc.h>
#include <video.h>

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

typedef enum {
    LEFT = 0,
    RIGHT,
    FULL
} context_id_t;

/**
 * @brief Create a window object
 * 
 * @param area 
 * @return area_t 
 */
area_t create_window(area_t area);

/**
 * @brief 
 * 
 */
void full_screen_distribution();

/**
 * @brief 
 * 
 */
void split_screen_distribution();

/**
 * @brief 
 * 
 * @param c 
 * @param id 
 */
void gprint_char(const char c, context_id_t id);

/**
 * @brief 
 * 
 * @param str 
 * @param id 
 */
void gprint_string(const char *str, context_id_t id);

/**
 * @brief 
 * 
 * @param id 
 */
void gprint_new_line(context_id_t id);

/**
 * @brief 
 * 
 * @param id 
 */
void gdelete_char(context_id_t id);

/**
 * @brief 
 * 
 * @param id 
 */
void gclear_screen(context_id_t id);

/**
 * @brief Get the context id object
 * 
 * @return context_id_t 
 */
context_id_t get_context_id();

/**
 * @brief 
 * 
 */
void gsnapshot();

/**
 * @brief 
 * 
 * @param target 
 */
void gfocus(context_id_t target);

#endif /* _GRAPHICS_H_ */