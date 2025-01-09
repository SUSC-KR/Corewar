#ifndef COREWAR_INSTRUCTIONS_H
# define COREWAR_INSTRUCTIONS_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include "corewar.h"

typedef struct s_inst	t_inst;

struct	s_inst
{
	char		*name;
	uint8_t		code;
	uint8_t		args_num;
	bool		args_types_code;
	uint8_t		args_types[3];
	bool		modify_carry;
	uint8_t		t_dir_size;
	uint32_t	cycles;
	void		(*func)(t_corewar *cw, t_carriage *carriage);
};

void	inst_live(t_corewar *cw, t_carriage *carriage);
void	inst_ld(t_corewar *cw, t_carriage *carriage);
void	inst_st(t_corewar *cw, t_carriage *carriage);
void	inst_add(t_corewar *cw, t_carriage *carriage);
void	inst_sub(t_corewar *cw, t_carriage *carriage);
void	inst_and(t_corewar *cw, t_carriage *carriage);
void	inst_or(t_corewar *cw, t_carriage *carriage);
void	inst_xor(t_corewar *cw, t_carriage *carriage);
void	inst_zjmp(t_corewar *cw, t_carriage *carriage);
void	inst_ldi(t_corewar *cw, t_carriage *carriage);
void	inst_sti(t_corewar *cw, t_carriage *carriage);
void	inst_fork(t_corewar *cw, t_carriage *carriage);
void	inst_lld(t_corewar *cw, t_carriage *carriage);
void	inst_lldi(t_corewar *cw, t_carriage *carriage);
void	inst_lfork(t_corewar *cw, t_carriage *carriage);
void	inst_aff(t_corewar *cw, t_carriage *carriage);

// 명령어 테이블 정의
static t_inst		g_inst[16] = {
	{
		.name = "live",
		.code = 0x01,
		.args_num = 1,
		.args_types_code = false,
		.args_types = {T_DIR, 0, 0},
		.modify_carry = false,
		.t_dir_size = 4,
		.cycles = 10,
		.func = &inst_live // live 명령어: 프로세스가 살아있음을 알리고 실행 중인 프로세스를 유지
	},
	{
		.name = "ld",
		.code = 0x02,
		.args_num = 2,
		.args_types_code = true,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 5,
		.func = &inst_ld // ld 명령어: 메모리에서 값을 읽어 레지스터에 저장
	},
	{
		.name = "st",
		.code = 0x03,
		.args_num = 2,
		.args_types_code = true,
		.args_types = {T_REG, T_REG | T_IND, 0},
		.modify_carry = false,
		.t_dir_size = 4,
		.cycles = 5,
		.func = &inst_st // st 명령어: 레지스터 값을 메모리에 저장
	},
	{
		.name = "add",
		.code = 0x04,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG, T_REG, T_REG},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 10,
		.func = &inst_add // add 명령어: 두 레지스터 값을 더하여 결과를 레지스터에 저장
	},
	{
		.name = "sub",
		.code = 0x05,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG, T_REG, T_REG},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 10,
		.func = &inst_sub // sub 명령어: 두 레지스터 값을 빼고 결과를 레지스터에 저장
	},
	{
		.name = "and",
		.code = 0x06,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 6,
		.func = &inst_and // and 명령어: 논리 AND 연산 수행
	},
	{
		.name = "or",
		.code = 0x07,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 6,
		.func = &inst_or // or 명령어: 논리 OR 연산 수행
	},
	{
		.name = "xor",
		.code = 0x08,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 6,
		.func = &inst_xor // xor 명령어: 논리 XOR 연산 수행
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.args_num = 1,
		.args_types_code = false,
		.args_types = {T_DIR, 0, 0},
		.modify_carry = false,
		.t_dir_size = 2,
		.cycles = 20,
		.func = &inst_zjmp // zjmp 명령어: carry가 설정되어 있으면 인덱스를 점프
	},
	{
		.name = "ldi",
		.code = 0x0A,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.modify_carry = false,
		.t_dir_size = 2,
		.cycles = 25,
		.func = &inst_ldi // ldi 명령어: 메모리 값을 읽어 레지스터에 저장 (간접 인덱스)
	},
	{
		.name = "sti",
		.code = 0x0B,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.modify_carry = false,
		.t_dir_size = 2,
		.cycles = 25,
		.func = &inst_sti // sti 명령어: 레지스터 값을 메모리에 저장 (간접 인덱스)
	},
	{
		.name = "fork",
		.code = 0x0C,
		.args_num = 1,
		.args_types_code = false,
		.args_types = {T_DIR, 0, 0},
		.modify_carry = false,
		.t_dir_size = 2,
		.cycles = 800,
		.func = &inst_fork // fork 명령어: 현재 프로세스를 복제 (간접 점프)
	},
	{
		.name = "lld",
		.code = 0x0D,
		.args_num = 2,
		.args_types_code = true,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.modify_carry = true,
		.t_dir_size = 4,
		.cycles = 10,
		.func = &inst_lld // lld 명령어: 메모리 값을 읽어 레지스터에 저장 (carry 갱신)
	},
	{
		.name = "lldi",
		.code = 0x0E,
		.args_num = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.modify_carry = true,
		.t_dir_size = 2,
		.cycles = 50,
		.func = &inst_lldi // lldi 명령어: 메모리 값을 읽어 레지스터에 저장 (간접, carry 갱신)
	},
	{
		.name = "lfork",
		.code = 0x0F,
		.args_num = 1,
		.args_types_code = false,
		.args_types = {T_DIR, 0, 0},
		.modify_carry = false,
		.t_dir_size = 2,
		.cycles = 1000,
		.func = &inst_lfork // lfork 명령어: fork와 유사하나, 인덱스 제한 없음
	},
	{
		.name = "aff",
		.code = 0x10,
		.args_num = 1,
		.args_types_code = true,
		.args_types = {T_REG, 0, 0},
		.modify_carry = false,
		.t_dir_size = 4,
		.cycles = 2,
		.func = &inst_aff // aff 명령어: 레지스터 값을 문자로 출력
	}
};
#endif
