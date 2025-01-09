#include "asm.h"

void insert_ints_instead_mentions(t_pars *pars)
{
    t_mention *mention;
    t_label *label;

    label = pars->labels;
    while (label)
    {
        if (label->op_pos != -1)
        {
            mention = label->mentions;
            while (mention)
            {
                write_to_bytecode(pars->code, mention->pos,
                                  (label->op_pos - mention->op_pos), mention->size);
                mention = mention->next;
            }
        }
        else
            terminate_label(label);
        label = label->next;
    }
}

void read_file(t_pars *pars)
{
    char *line;
    int res;

    pars->end = new_entity(pars, END);
    while ((res = read_next_line(pars->fd, &line)) > 0
           && !(pars->col = 0)
           && (++pars->row))
    {
        while (line[pars->col])
            skip_whitespaces(&(pars->col), line)
            && skip_comment(&(pars->col), line)
            && (line[pars->col] != '\0')
            && get_entities(pars, &line);
        free(line); // free를 사용하여 메모리 해제
    }
    add_entity(&(pars->entities), pars->end);
    res == -1 ? terminate("An error occurred while opening file") : 0;
}

int reverse_file_fd(t_pars *pars, char *file)
{
    int fd;
    char *new;
    char *ext;
    char *old;

    ext = strrchr(file, '.');
    if (!(old = strndup(file, ext - file)))
        terminate("Memory allocation failed");
    if (!(new = malloc(strlen(old) + (ext && strcmp(ext, ".s") == 0 ? 4 : 3))))
        terminate("Memory allocation failed");

    // 파일 확장자에 따라 적절한 이름을 생성
    if (ext && strcmp(ext, ".s") == 0)
    {
        strcpy(new, old);
        strcat(new, ".core");
    }
    else
    {
        strcpy(new, old);
        strcat(new, ".s");
    }

    free(old);

    fd = open(new, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
        terminate("Can not create file =(");

    if (strlen(pars->name) == 0)
        printf("WARNING : Champion without name!\n");
    if (strlen(pars->comment) == 0)
        printf("WARNING : Champion without comment!\n");
    if (pars->pos == 0)
        printf("WARNING : Champion without code!\n");

    printf("Writing output program to %s\n", new);
    free(new);
    return fd;
}

int asm_to_bytecode(char *file)
{
    t_entity *curr;
    t_pars *pars;
    int fd;

    fd = open(file, O_RDONLY);
    if (fd < 0) terminate("Invalid file");

    pars = new_pars(fd);
    read_file(pars);
    curr = pars->entities;
    get_champ_bio(pars, &curr);
    read_and_proc_entities(pars, &curr);
    fd = reverse_file_fd(pars, file);
    write_code_to_bytecode(pars, fd);
    free_pars(&pars);
    return 1;
}
