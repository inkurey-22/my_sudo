/*
** EPITECH PROJECT, 2024
** myprintf
** File description:
** my_printf
*/

#ifndef MY_PRINTF_H_
    #define MY_PRINTF_H_

    #include <stdarg.h>

// Buffer structure
typedef struct buffer_s {
    char buffer[1024];
    int pos;
    int len;
} buffer_t;

// Format structure
typedef struct format_s {
    int flags;
    int width;
    int precision;
    int length;
} format_t;

// Printf function pointer structure
typedef struct printf_s {
    char c;
    void (*func)(va_list, buffer_t *, format_t *);
} printf_t;

// Main printf functions
int my_printf(char const *, ...);
int my_sprintf(char *, char const *, ...);
int my_dprintf(int, char const *, ...);
void put_buffer(buffer_t *, int);

// Specifier management
void manage_specifiers(char, va_list, buffer_t *, format_t *);

// Character and string output
void printf_putchar(char, buffer_t *);
void printf_putstr(char const *, buffer_t *, format_t *);

// Number output
int printf_putnbr(int, buffer_t *, format_t *);
void printf_putfloat(double, buffer_t *, format_t *);
void printf_decimal(int, buffer_t *, format_t *);
void printf_scientific(double, buffer_t *, format_t *, int);
void printf_g_spec(double, buffer_t *, format_t *, int);

// Conversion functions
char *convert_hex(long);
char *convert_oct(long);
char *printf_pointer(void *);

// Utility functions
int number_len(int);
void printf_n_spec(int *, buffer_t *);
void printf_tab(char **, buffer_t *);
void parse_format(char const *, int *, format_t *, va_list);

// Linkers
void print_char(va_list args, buffer_t *, format_t *);
void print_string(va_list args, buffer_t *, format_t *);
void print_int(va_list args, buffer_t *, format_t *);
void print_mudulo(va_list args, buffer_t *, format_t *);
void print_float(va_list args, buffer_t *, format_t *);
void print_puthexmin(va_list args, buffer_t *, format_t *);
void print_puthexmaj(va_list args, buffer_t *, format_t *);
void print_octal(va_list args, buffer_t *, format_t *);
void print_pointer(va_list args, buffer_t *, format_t *);
void print_nspec(va_list args, buffer_t *, format_t *);
void print_capscientific(va_list args, buffer_t *, format_t *);
void print_scientific(va_list args, buffer_t *, format_t *);
void print_g_low(va_list args, buffer_t *, format_t *);
void print_g_up(va_list args, buffer_t *, format_t *);
void print_decimal(va_list args, buffer_t *, format_t *);
void print_tab(va_list args, buffer_t *, format_t *);

#endif /* !MY_PRINTF_H_ */
