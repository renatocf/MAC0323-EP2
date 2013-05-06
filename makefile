#***********************************************#
#**  MAC 0323  -  Estrutura de Dados          **#
#**  IME-USP   -  Primeiro  Semestre de 2013  **#
#**  Turma 45  -  Yoshiharu Kohayakawa        **#
#**                                           **#
#**  Segundo   Exercício-Programa             **#
#**  Arquivo:  makefile                       **#
#**                                           **#
#**  Renato Cordeiro Ferreira        7990933  **#
#***********************************************# 

# SOURCE ###############################################################
SRC := main.c getopt.c Dimension.c queue.c
OBJ := $(patsubst %.c,%.o,$(SRC))
DEP := dependencies.mk

BIN    := connectivity
CUBE   := Point.C.o
SPHERE := Point.S.o

# PROGRAMS #############################################################
CC  := gcc
RM  := rm -f
SED := sed
CAT := cat

CFLAGS := -ansi -pedantic -Wall -g -I. -pg

# LINKER ###############################################################
LDLIBS  := -L. 
LDFLAGS := -lm -lc -pg

# BUILD ################################################################
cube: $(OBJ) $(CUBE) | $(DEP)
	$(CC) $^ -o $(BIN) $(LDLIBS) $(LDFLAGS)
	@-$(RM) $(DEP)

sphere: $(OBJ) $(SPHERE) | $(DEP)
	$(CC) $^ -o $(BIN) $(LDLIBS) $(LDFLAGS)
	@-$(RM) $(DEP)

# DEPENDENCIES #########################################################
$(DEP):
	@$(CC) $(SRC) -MM > $@
	@$(SED) -e 's/\.o/\.c/' -e 's/: .*c /: /' $@ | $(CAT) > $@
-include dependencies.mk

# RULES ################################################################
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# OTHER OPTIONS ########################################################
.PHONY: clean
clean:
	$(RM) *.o *~ $(DEP) gmon.out
