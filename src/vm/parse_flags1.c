#include "corewar.h"

bool strings_are_equal(const char *s1, const char *s2) {
    return strcmp(s1, s2) == 0;
}

void parse_args(int argc, char **argv, t_corewar *cw) {
    t_champ *lst;

    lst = NULL;
    argv++;
    argc--;
    while (argc > 0) {
        if (strings_are_equal(*argv, "-dump") || strings_are_equal(*argv, "-d")) {
            init_dump_flag(&argc, &argv, cw);
        } else if (strings_are_equal(*argv, "-debug32") || strings_are_equal(*argv, "-debug64")) {
            init_debug_flag(&argc, &argv, cw);
        } else if (strings_are_equal(*argv, "-a")) {
            init_aff_flag(&argc, &argv, cw);
        } else if (strings_are_equal(*argv, "-verbose")) {
            init_verbose_flag(&argc, &argv, cw);
        } else if (strings_are_equal(*argv, "-visual")) {
            init_visual_flag(&argc, &argv, cw);
        } else if (check_file_extension(*argv, "core") || strings_are_equal(*argv, "-n")) {
            proc_champ(&argc, &argv, &lst, cw);
        } else {
            display_usage();
        }
    }
    list_to_array(lst, cw);
}

void init_visual_flag(int *argc, char ***argv, t_corewar *cw) {
    if (cw->visual != NULL) {
        display_usage();
    }
    cw->visual = new_visual();
    ++(*argv);
    --(*argc);
}
