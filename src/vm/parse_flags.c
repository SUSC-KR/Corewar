#include "corewar.h"

// 숫자인지 확인하는 함수 (기수 radix는 항상 10으로 가정)
bool is_number(const char *str, int radix)
{
    if (!str || radix != 10)
        return false;

    // 음수 허용
    if (*str == '-' || *str == '+')
        ++str;

    if (*str == '\0') // 부호만 있는 경우
        return false;

    while (*str)
    {
        if (!isdigit((unsigned char)*str))
            return false;
        ++str;
    }
    return true;
}

// 문자열이 동일한지 확인하는 함수
bool str_equal(const char *s1, const char *s2)
{
    return strcmp(s1, s2) == 0;
}

// -dump 플래그 처리
void init_dump_flag(int *argc, char ***argv, t_corewar *cw)
{
    // dump_mode가 0이고, 첫 번째 인자가 숫자일 경우 dump 모드 설정
    if (cw->dump_mode == 0 && (*argc > 1) && is_number((*argv)[1], 10))
    {
        // -dump 플래그가 있으면 32로 설정, 아니면 64로 설정
        cw->dump_mode = (str_equal(**argv, "-dump")) ? 32 : 64;

        // dump_cycles 값을 받아옴
        if ((cw->dump_cycles = atoi((*argv)[1])) < 0)
            cw->dump_cycles = -1; // 잘못된 값이면 -1로 설정
        *argv += 2; // 인자 두 개 처리
        *argc -= 2; // 인자 두 개 감소
    }
    else
    {
        display_usage(); // 잘못된 형식의 입력이 있을 경우 사용법을 출력
    }
}

// -aff 플래그 처리 (aff 출력 활성화)
void init_aff_flag(int *argc, char ***argv, t_corewar *cw)
{
    // 이미 aff가 활성화 되어 있으면 잘못된 입력
    if (cw->aff == true)
        display_usage();
    cw->aff = true; // aff 활성화
    ++(*argv);      // 다음 인자로 넘어감
    --(*argc);      // 인자 수 감소
}

// -verbose 플래그 처리
void init_verbose_flag(int *argc, char ***argv, t_corewar *cw)
{
    // verbose가 0이고, 다음 인자가 숫자일 경우 verbose 모드 설정
    if (cw->verbose == 0 && (*argc > 1) && is_number((*argv)[1], 10))
    {
        if ((cw->verbose = atoi((*argv)[1])) < 0)
            display_usage(); // 잘못된 값이면 사용법 출력
        *argv += 2; // 인자 두 개 처리
        *argc -= 2; // 인자 두 개 감소
    }
    else
    {
        display_usage(); // 잘못된 형식의 입력이 있을 경우 사용법을 출력
    }
}

// -debug 플래그 처리
void init_debug_flag(int *argc, char ***argv, t_corewar *cw)
{
    // debug_mode가 0이고, 첫 번째 인자가 숫자일 경우 debug 모드 설정
    if (cw->debug_mode == 0 && (*argc > 1) && is_number((*argv)[1], 10))
    {
        // -debug32가 있으면 32로, -debug64가 있으면 64로 설정
        cw->debug_mode = (str_equal(**argv, "-debug32")) ? 32 : 64;

        // debug_cycles 값을 받아옴
        if ((cw->debug_cycles = atoi((*argv)[1])) < 0)
            cw->debug_cycles = -1; // 잘못된 값이면 -1로 설정
        *argv += 2; // 인자 두 개 처리
        *argc -= 2; // 인자 두 개 감소
    }
    else
    {
        display_usage(); // 잘못된 형식의 입력이 있을 경우 사용법을 출력
    }
}

// 챔피언 처리 함수
void proc_champ(int *argc, char ***argv, t_champ **lst, t_corewar *cw)
{
    int id;

    // 최대 플레이어 수를 초과하면 종료
    if (cw->champs_num == MAX_PLAYERS)
        terminate(CHAMPS_NUM);
    // -n 플래그가 있고, 인자가 두 개 이상이고, 첫 번째 인자가 숫자일 경우
    if (str_equal(**argv, "-n") && (*argc > 2) && !(id = 0))
    {
        // -n 뒤의 값이 숫자가 아니거나, id가 범위를 초과하거나 이미 있는 id일 경우 에러
        if (!is_number((*argv)[1], 10) || (id = atoi((*argv)[1])) > MAX_PLAYERS || id < 1 || find_champ(*lst, id) || !check_file_extension((*argv)[2], "core"))
        {
            display_usage();
        }
        // 챔피언 추가
        add_champ(lst, new_champ((*argv)[2], id));
        ++(cw->champs_num); // 챔피언 수 증가
        *argv += 3;         // 인자 세 개 처리
        *argc -= 3;         // 인자 세 개 감소
    }
    // core 확장자가 있는 파일을 챔피언으로 추가
    else if (check_file_extension(**argv, "core"))
    {
        add_champ(lst, new_champ(**argv, 0)); // ID는 0으로 설정
        ++(cw->champs_num);                  // 챔피언 수 증가
        ++(*argv);                           // 인자 하나 처리
        --(*argc);                           // 인자 하나 감소
    }
    else
    {
        display_usage(); // 잘못된 형식의 입력이 있을 경우 사용법을 출력
    }
}
