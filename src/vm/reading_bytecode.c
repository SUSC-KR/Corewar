#include "corewar.h"

// 바이트 배열을 정수로 변환하는 함수
static int convert_bytes_to_int(uint8_t *bytes, size_t size, bool neg)
{
    int res = 0;
    int move = 0;

    while (size)
    {
        // 음수인 경우 보수 계산
        res += (!neg) ?
            bytes[size - 1] << (move++ * 8) :
            (bytes[size - 1] ^ 0xFF) << (move++ * 8);
        --size;
    }
    // 음수라면 보수 취소
    return (neg) ? ~res : res;
}

// 바이트 배열을 정수로 변환
int convert_to_int(uint8_t *bytes, size_t size)
{
    bool neg;

    neg = bytes[0] & 0x80; // 부호 비트 확인
    return convert_bytes_to_int(bytes, size, neg);
}

// 맵에서 데이터를 읽어와 정수로 변환
int get_int(uint8_t *map, int address, int size)
{
    bool neg;
    int res;

    neg = map[calculate_address(address)] & 0x80; // 부호 비트 확인
    res = convert_bytes_to_int(map + calculate_address(address), size, neg);
    return res;
}

// 바이트코드 파일에서 4바이트를 읽고 정수로 변환
int read_from_bytecode(int fd)
{
    uint8_t buff[4];
    int size;

    // 4바이트 읽기
    size = read(fd, &buff, 4);
    if (size == -1)
    {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }
    else if (size < 4)
    {
        fprintf(stderr, "Invalid file\n");
        exit(EXIT_FAILURE);
    }
    return (convert_to_int(buff, 4)); // 정수로 변환
}

// 주어진 길이만큼 바이트코드를 읽어서 문자열로 반환
char *read_str_from_bytecode(int fd, int length)
{
    int size;
    char *buff;

    // 메모리 할당
    buff = malloc(length + 1);  // +1 for null terminator
    if (!buff)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // 파일에서 문자열 읽기
    size = read(fd, buff, length);
    if (size != length)
    {
        fprintf(stderr, "Invalid file\n");
        free(buff);
        exit(EXIT_FAILURE);
    }
    buff[size] = '\0'; // null terminator 추가
    return buff;
}

// 코드 크기만큼 바이트코드를 읽어서 반환
uint8_t *read_code(int fd, int code_size)
{
    uint8_t *code;
    int size;
    uint8_t tmp;

    // 코드 메모리 할당
    code = malloc(sizeof(uint8_t) * code_size);
    if (!code)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // 파일에서 코드 읽기
    size = read(fd, code, code_size);
    if (size != code_size)
    {
        fprintf(stderr, "Invalid file\n");
        free(code);
        exit(EXIT_FAILURE);
    }

    // 남은 데이터가 있으면 잘못된 파일
    if (read(fd, &tmp, 1))
    {
        fprintf(stderr, "Invalid file\n");
        free(code);
        exit(EXIT_FAILURE);
    }

    return code;
}
