#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

const char SIZE_NAME = 50;
const char NUM_ADRESSES = 50;

int find_file ( char **adresses, int level, int *adress_num, char **argv, char *dir_name );

int find_file ( char **adresses, int level, int *adress_num, char **argv, char *dir_name ) {

	DIR* dir = opendir ( dir_name );

	while ( 1 ) {

		if ( dir == NULL )

			printf ( " Can't open directory!\n" );

		char *pathname = ( char* ) calloc ( SIZE_NAME, sizeof ( char ) );

		strcpy ( pathname, dir_name );

		struct dirent *dir_str = ( struct dirent* ) calloc ( 1 , sizeof ( struct dirent ) );

		dir_str = readdir ( dir );

		if ( dir_str == NULL ) {

			break;
			closedir ( dir );
			return 0;

		}

		strcat ( pathname, "/" );
		strcat ( pathname, dir_str->d_name );

		if ( dir_str->d_type == DT_REG  ) {

			if ( strcmp ( dir_str->d_name, argv[3] ) == 0 ) {

				adresses [ *adress_num ] = pathname;
				printf ( " Yeap, file %s have been founded at adress: %s\n", argv[3], adresses[ *adress_num ] );
				*adress_num ++;

			}

			else;

		}

		else

			if ( dir_str->d_type ==  DT_DIR && level > 0 && ( strcmp( dir_str->d_name,".") != 0 ) && ( strcmp( dir_str->d_name,".." )  != 0 ) ) {

				find_file ( adresses, level - 1, adress_num, argv, pathname );

			}

			else

				continue;

	}

	closedir( dir );

}


int main ( int argc, char** argv ) {

	char *file_name = ( char* ) calloc ( SIZE_NAME, sizeof ( char ) );

	int level = atoi(argv[2]), adress_num = 0, a = 0;

	char **adresses = ( char ** ) calloc ( NUM_ADRESSES, sizeof ( char *) );

	for ( int i = 0; i < NUM_ADRESSES; i++ )

		adresses[i] = ( char *) calloc ( SIZE_NAME, sizeof ( char ) );

	find_file ( adresses, level-1, &adress_num, argv, argv[1] );

	for ( int i = 0; i < adress_num; i++ )

		free ( adresses[i] );

	free ( adresses );
	free ( file_name );

	return 0;

}
