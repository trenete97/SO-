all: apuesta_ppt_1 ppt_N apuesta_ppt_1_KILL ppt_N_KILL 
apuesta_ppt_1: apuesta_ppt_1.c
	gcc -g -Wall apuesta_ppt_1.c -o apuesta_ppt_1
ppt_N: ppt_N.c
	gcc -g -Wall ppt_N.c -o ppt_N
apuesta_ppt_1_KILL: apuesta_ppt_1_KILL.c
	gcc -g -Wall apuesta_ppt_1_KILL.c -o apuesta_ppt_1_KILL
ppt_N_KILL: ppt_N_KILL.c
	gcc -g -Wall ppt_N_KILL.c -o ppt_N_KILL
clean:
	rm -f *.o apuesta_ppt_1 ppt_N apuesta_ppt_1_KILL ppt_N_KILL
