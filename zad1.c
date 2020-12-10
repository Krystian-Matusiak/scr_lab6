#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>



int main() {


	// Zmienne typu char
	char nazwa_p1[100];
	char nazwa_p2[100];
	char * adres;

	struct stat struct_stat;

	int fd1;
	int fd2;


	 while(1) {

	 	// Pobieranie pliku
		printf("Podaj nazwe pliku z  :\n");
	    scanf("%s", nazwa_p1);
	  	if(( fd1 = open(nazwa_p1, O_RDWR, S_IRUSR | S_IWUSR)) < 0 ) 
	  		printf("Nie mozna otworzyc pliku\n");


		printf("Podaj nazwe pliku do ktory chcesz utworzyc :\n");
	    scanf("%s", nazwa_p2);
	  	fd2 = open(nazwa_p2, O_RDWR | O_CREAT);  

	  	// Pobranie rozmiaru pliku
	  	if(fstat(fd1, &struct_stat) < 0) { 	
			printf("Problem z pobraniem rozmiaru");
			return(1);
	    }


		ftruncate( fd2, struct_stat.st_size );  

		adres = mmap(NULL, struct_stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0 );
		read(fd1, adres ,struct_stat.st_size);

		for (int i = 0; i < struct_stat.st_size; ++i){
			printf("%c", adres[i]);
		}


		close(fd1);
		close(fd2);
	}
	return 0;
}


