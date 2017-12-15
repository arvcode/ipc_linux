#include<stdio.h>
/* mkfifo 
 * cat <
 * cat > 
 * mkfifo();
 int fd = open (fifo_path, O_WRONLY);
 write (fd, data, data_length);
 close (fd);
 FILE* fifo = fopen (fifo_path, "r");
 fscanf (fifo, "%s", buffer);
 fclose (fifo);
*/
main() {
	FILE *fp;
	fp=popen("sort","w");
	fprintf(fp,"500\n");
	fprintf(fp,"200\n");
	pclose(fp);
}

