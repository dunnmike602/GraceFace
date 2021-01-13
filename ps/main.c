#include "../lib/lib.h"

#define NUM_PROC 10

struct ProcessInfo {
    int pid;
	uint8_t name[8];
    int state;
	int time;
	int64_t stacksize;
	uint32_t filesize;
};

#define NUM_PROC 10
#define PROC_UNUSED 0
#define PROC_INIT 1
#define PROC_RUNNING 2
#define PROC_READY 3
#define PROC_SLEEP 4
#define PROC_KILLED 5

struct ProcessInfo buffer[NUM_PROC];

static int copystring(uint8_t src1[], uint8_t src2[], int size)
{
    for (int j = 0; j < size; j++)
    {
        if(src2[j] != 0)
        {
            src1[j] = src2[j];
        }
    }
}


int main(void)
{
    int count;
       
    char init[] =  "INIT       \0" ;
    char running[] =  "RUNNING    \0" ;
    char ready[] =  "READY      \0" ;
    char sleeping[] =  "SLEEPING   \0" ;
    char killed[] =  "KILLED     \0" ;

    count = read_process_info(buffer);
    
    printf("\nNAME      STATE      PID     TIME (ms)   MEMORY (Bytes) STACK (Bytes)\n");
    printf("-----------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) 
    {
      if(buffer[i].state != 0)
      {
            char state[12] = "          \0";

            switch (buffer[i].state)
            {
                case  PROC_INIT:
                    memcpy(state, init, 12);
                    break;

                case  PROC_RUNNING:
                    memcpy(state, running, 12);
                    break;

                case  PROC_READY:
                    memcpy(state, ready, 12);
                    break;

                case  PROC_SLEEP:
                    memcpy(state, sleeping, 12);
                    break;

                case  PROC_KILLED:
                    memcpy(state,killed, 12);
                    break;

                default:
                break;
            }
         
            char name[12] = "          \0";
            copystring(name, buffer[i].name, 8);

            char pid[12] = "        \0";
            udecimal_to_string(pid, 0, buffer[i].pid);

            char time[14] = "            \0";
            udecimal_to_string(time, 0, buffer[i].time);

            char mem[17] = "               \0";
            udecimal_to_string(mem, 0, buffer[i].filesize);

            char stack[14] = "            \0";
            udecimal_to_string(stack, 0, buffer[i].stacksize);

            printf("%s%s%s%s%s%s\n", name, state, pid, time, mem, stack);
     }
   }

    return 0;
}
