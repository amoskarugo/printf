#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - custom printf function
 * @format: format string
 *
 * Return: number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;

            switch (*format)
            {
                case 'c':
                    {
                        char c = va_arg(args, int);
                        write(1, &c, 1);
                        count++;
                        break;
                    }
                case 's':
                    {
                        char *str = va_arg(args, char *);
                        while (*str)
                        {
                            write(1, str, 1);
                            str++;
                            count++;
                        }
                        break;
                    }
                case '%':
                    write(1, "%", 1);
                    count++;
                    break;
                default:
                    write(1, &(*format), 1);
                    count++;
                    break;
            }
        }
        else
        {
            write(1, &(*format), 1);
            count++;
        }

        format++;
    }

    va_end(args);

    return count;
}

