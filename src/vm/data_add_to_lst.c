#include "corewar.h"

void add_champ(t_champ **lst, t_champ *new)
{
    t_champ *curr;

    if (*lst == NULL)
    {
        *lst = new;
    }
    else
    {
        curr = *lst;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = new;
    }
}

void add_carriage(t_carriage **lst, t_carriage *new)
{
    new->next = *lst;
    *lst = new;
}
