#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char get_char(FILE *file) {
    if (!file) {
        return '\0';
    }

    char symbol = '\0';
    int result = 0;

    do {
        result = fscanf(file, "%c", &symbol);
    } while (result != 1);
    return symbol;
}

char *read_string(FILE *file) {
    if (!file) {
        return NULL;
    }

    struct String {
        char *str_;
        size_t size_;
        int capacity_;
    } string = {NULL, 0, 0};

    int symbol = '\0';
    char *copy_str = NULL;

    while (symbol = get_char(file), symbol != EOF && symbol != '\n') {
        bool is_memory_allocate = 0;

        /*if buffer is empty*/
        if (string.capacity_ == 0) {
            string.capacity_ = 1;
            is_memory_allocate = 1;
            /*if size more than capacity*/
        } else if (string.capacity_ > 0 &&
                   string.size_ + 1 >= string.capacity_) {
            string.capacity_ *= 2;
            is_memory_allocate = 1;
        } else {
            is_memory_allocate = 0;
        }

        if (is_memory_allocate) {
            copy_str = (char *)malloc((string.capacity_ + 1) * sizeof(char));
            if (copy_str) {
                if (string.str_) {
                    copy_str = strncpy(copy_str, string.str_,
                                       string.size_ * sizeof(char));
                    free(string.str_);
                    string.str_ = NULL;
                }
                string.str_ = copy_str;
            } else {
                if (string.str_) {
                    free(string.str_);
                }
                perror("Incorrect allocation of memory\n");
                return NULL;
            }
        }
        string.str_[string.size_++] = symbol;
        string.str_[string.size_] = '\0';
    }
    return string.str_;
}

int read_integer(FILE *file) {
    if (!file) {
        return 0;
    }

    int symbol = '\0';
    int result = 0;

    while (symbol = get_char(file), symbol != EOF && symbol != '\n') {
        if (symbol >= '0' && symbol <= '9') {
            result = result * 10 + symbol - '0';
        } else {
            char *str_to_delete = read_string(file);
            free(str_to_delete);
            return 0;
        }
    }

    return result;
}

double read_double(FILE *file) {
    if (!file) {
        return 0;
    }

    int symbol = '\0';
    double result = 0;
    bool is_after_point = 0;
    double exp = 10;

    while (symbol = get_char(file), symbol != EOF && symbol != '\n') {
        if ((symbol >= '0' && symbol <= '9') && !is_after_point) {
            result = result * 10 + symbol - '0';
        } else if ((symbol == '.' || symbol == ',') && !is_after_point) {
            is_after_point = 1;
        } else if (is_after_point) {
            result = result + (double)((symbol - '0') / exp);
            exp *= 10;
        } else {
            char *str_to_delete = read_string(file);
            free(str_to_delete);
            return 0;
        }
    }
    return result;
}