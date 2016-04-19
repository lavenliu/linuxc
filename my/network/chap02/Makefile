#include ../Makefile.inc

#GEN_EXE = t_uname myinfo

LINUX_EXE = 2-2 2-4 2-4_ex 2-5 2-6

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${LPLIB}		# True as a rough approximation
