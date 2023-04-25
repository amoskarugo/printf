#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
    int i, printed = 0, printed_chars = 0;
    int flags, width, precision, size, buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(list, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            printed_chars++;
        }
        else
        {
            print_buffer(buffer, &buff_ind);

            flags = get_flags(format, &i);
            width = get_width(format, &i, list);
            precision = get_precision(format, &i, list);
            size = get_size(format, &i);

            if (format[i] == 'p')
                printed = handle_pointer(list, buffer, buff_ind);
            else
                printed = handle_print(format, &i, list, buffer, flags, width, precision, size);

            if (printed == -1)
                return (-1);

            printed_chars += printed;
        }
    }

    print_buffer(buffer, &buff_ind);

    va_end(list);

    return (printed_chars);
}

/**
 * handle_pointer - Handles the %p conversion specifier
 * @list: Argument list
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 * Return: Number of characters printed
 */
int handle_pointer(va_list list, char buffer[], int buff_ind)
{
    void *ptr = va_arg(list, void *);
    char ptr_string[20];

    sprintf(ptr_string, "%p", ptr);
    int ptr_len = strlen(ptr_string);

    if (buff_ind + ptr_len >= BUFF_SIZE)
        print_buffer(buffer, &buff_ind);

    for (int i = 0; i < ptr_len; i++)
        buffer[buff_ind++] = ptr_string[i];

    return ptr_len;
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
        write(1, &buffer[0], *buff_ind);

    *buff_ind = 0;
}

