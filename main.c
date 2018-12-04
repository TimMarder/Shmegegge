#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>

int main() {

    char * memory;
    int shmid;
    key_t key;
    char memoryinput[256];
    char yesnoinput[256];
    char yesnoinput2[256];

    key = ftok("./keyholder", 'R');
    shmid = shmget( key , 256 , 0644 | IPC_CREAT );
    memory = shmat( shmid, (void *) 0, 0 );

    if (memory[0]) {

        printf("Shared memory: %s\n", memory);

    }
    else {

        printf("Shared memory created.\n");

    }

    while ( (strncmp(yesnoinput,"yes",3)) & (strncmp(yesnoinput,"no",2)) ) {

        printf("Do you want to change the shared memory?\n");
    	fgets(yesnoinput, 256, stdin);

        if( !strncmp( yesnoinput,"yes",3 ) ) {

            printf("Enter what you want to put in the shared memory: \n");
    		fgets( memoryinput, 256, stdin );
    		memoryinput[ strlen( memoryinput ) - 1 ] = 0;
    		strcpy( memory,memoryinput );
            printf("Shared memory changed to %s\n", memoryinput);

        }
        else {

            if ( memoryinput ) {

                printf("Shared memory with '%s' will remain unchanged\n", memoryinput);

            }
            else {

                printf("Empty shared memory will remain empty\n");

            }

        }

    }
    printf("Do you want to delete the shared memory?\n");
    fgets( yesnoinput, 256, stdin );

    if( !strncmp( yesnoinput,"yes",3 ) ) {

        shmdt( memory );
        shmctl( shmid, IPC_RMID, NULL );
        printf("Shared memory with '%s' has been deleted\n", memoryinput);

    }
    else {

        printf("Shared memory will not be deleted\n");

    }
	return 0;

}
