#include <stdio.h>
#include <string.h>

int splitter,i=0;
char total[];
int main(void) {

			FILE *ptr_file;
    		char buf[1000];

    		ptr_file =fopen("map","r");
    		if (!ptr_file)
        		return 1;

    		while (fgets(buf,1000, ptr_file)!=NULL) {
                printf("%s", buf);
            }
		fclose(ptr_file);
    return 0;
	}	