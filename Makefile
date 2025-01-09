INCLUDE:=	include
SRC:=	src
OBJECT:=	objects

CMPL:=	gcc $(addprefix -W, all extra error) 

#==========VM==================================================================#

CRWB=	corewar
VMD=	vm
CRWH=	$(addprefix $(INCLUDE)/,\
			common.h\
			corewar.h\
			corewar_instructions.h\
			op.h\
			terminate_errors.h)
CRWSD=	$(SRC)/$(VMD)
CRWOD=	$(OBJECT)/$(VMD)
CRWS=	auxiliary.c\
		battle.c\
		carriage_kill.c\
		common.c\
		counting.c\
		data_add_to_lst.c\
		data_creation.c\
		display.c\
		inst_add.c\
		inst_aff.c\
		inst_and.c\
		inst_fork.c\
		inst_ld.c\
		inst_ldi.c\
		inst_lfork.c\
		inst_live.c\
		inst_lld.c\
		inst_lldi.c\
		inst_or.c\
		inst_st.c\
		inst_sti.c\
		inst_sub.c\
		inst_xor.c\
		inst_zjmp.c\
		parse_flags.c\
		parse_flags1.c\
		reading_bytecode.c\
		validation.c\
		verbose.c\
		visualize.c\
		visualize_auxiliary.c\
		visualize_prepare.c\
		visualize_proc.c\
		visualize_win.c\
		visualize_menu.c\
		visualize_info.c\
		vm.c
CRWO=	$(addprefix $(CRWOD)/, $(patsubst %.c, %.o, $(CRWS)))

#==========ASM=================================================================#

ASMB=	asm
ASMH=	$(addprefix $(INCLUDE)/,\
			asm.h\
			asm_instructions.h\
			common.h\
			op.h\
			terminate_errors.h)
ASMSD=	$(SRC)/$(ASMB)
ASMOD=	$(OBJECT)/$(ASMB)
ASMS=	asm.c\
		common.c\
		data_creation.c\
		data_processing_arguments.c\
		terminates.c\
		asm_to_bytecode.c\
		auxiliary.c\
		data_add_to_lst.c\
		data_free.c\
		data_processing.c\
		data_processing_classes.c\
		pasring.c\
		writing.c
ASMO=	$(addprefix $(ASMOD)/, $(patsubst %.c, %.o, $(ASMS)))

#==========DEPENDENCIES========================================================#
all: $(ASMB) $(CRWB)

$(ASMB): $(ASMO)
	@$(CMPL) -o $@ $^ $(addprefix -I, $(INCLUDE))
	@printf "\r\33[2K$@\t   \033[32;1mcreated\033[0m\n"

$(CRWB): $(CRWO)
	@$(CMPL) -o $@ $^ $(addprefix -I, $(INCLUDE)) -lncurses
	@printf "\r\33[2K$@\t   \033[32;1mcreated\033[0m\n"

$(ASMOD)/%.o: $(ASMSD)/%.c $(ASMH)
	@$(CMPL) -o $@ -c $< $(addprefix -I, $(INCLUDE))
	@printf "\r\33[2K$(ASMB)\t   \033[33;1mcompile \033[0m$(<:$(ASMSD)/%.c=%) "

$(CRWOD)/%.o: $(CRWSD)/%.c $(CRWH)
	@$(CMPL) -o $@ -c $< $(addprefix -I, $(INCLUDE))
	@printf "\r\33[2K$(CRWB)\t   \033[33;1mcompile \033[0m$(<:$(CRWSD)/%.c=%) "

$(ASMO): | $(ASMOD)

$(CRWO): | $(CRWOD)

#==========PRERESQUISITES======================================================#

$(CRWOD):
	@mkdir -p $@

$(ASMOD):
	@mkdir -p $@

clean:
	@rm -rf $(OBJECT)
	@printf "  $(OBJECT)\t   \033[31;1mdeleted\033[0m\n"

fclean: clean
	@rm -f $(ASMB) $(CRWB)
	@printf "   $(ASMB)\t   \033[31;1mdeleted\033[0m\n"
	@printf "   $(CRWB) \033[31;1mdeleted\033[0m\n"

test: $(CRWO)
	@echo $^

re: fclean all

.PHONY: all clean fclean re