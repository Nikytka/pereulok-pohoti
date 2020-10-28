#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>
#include <sys/sysinfo.h>

struct matr {

    int n;
    int* matrix;

};

struct mult_data {

    struct matr *a, *b, *result;

    int start, end;

    pthread_t pthid;

};

void gen_write_matr ( struct matr* matrix, FILE* f ) {

  char enter = '\n';
  matrix->matrix = ( int* ) calloc ( ( matrix->n ) * ( matrix->n ), sizeof( int ) );

  for ( int i = 0; i < matrix->n * matrix->n; i++ ) {

    *( matrix->matrix + i ) = rand() % 10;

    fprintf ( f, "%d ", *( matrix->matrix + i ) );

    if ( ( i + 1 ) % matrix->n == 0 )

      fprintf ( f, "%c", enter );

  }

}

void print_matr ( struct matr matrix, FILE* f ) {

  char enter = '\n';

  for ( int i = 0; i < matrix.n; i++ ) {

    for ( int j = 0; j < matrix.n; j++ )

      fprintf( f, "%d ", *( matrix.matrix + i * matrix.n + j ) );

    fprintf( f, "%c", enter );

  }

}

void* mult_calc ( void* data ) {

  struct mult_data* info = ( struct mult_data* ) data;

  for ( int i = info->start; (i < info->end) && (i < info->a->n); i++ )

    for ( int j = 0; j < info->a->n; j++ )

      for ( int l = 0; l < info->a->n; l++ )

        info->result->matrix[ i * info->a->n + j ] += info->a->matrix[ info->a->n * i + l ] * info->b->matrix[ info->b->n * l + j];

}

struct matr mult ( struct matr a, struct matr b ) {

  struct matr result;
  result.n = a.n;

  result.matrix = ( int* ) calloc ( result.n * result.n, sizeof ( int ) );

  int num_core = get_nprocs() * 2;

  //printf ("%d", num_core);

  struct mult_data* data = ( struct mult_data* ) calloc ( num_core, sizeof ( struct mult_data ) );

  int thr_len = result.n / num_core;

  if ( result.n % num_core != 0 )

    thr_len++;

  int ost = result.n;

  for ( int i = 0; i < result.n; i+=thr_len ) {

    data[i].a = &a;
    data[i].b = &b;
    data[i].result = &result;
    data[i].start = i;
    data[i].end = i + thr_len;

    ost -= thr_len;

    pthread_create ( &data[i].pthid, NULL, mult_calc, &data[i] );

    if ( ost <= 0)
      break;

  }

  for( int i = 0; i < num_core; i++ )

    pthread_join ( data[i].pthid, NULL );

  return result;

}

int main() {

  struct matr matr1, matr2, res_matr;
  int N;

  scanf ( "%d", &N );
  matr1.n = matr2.n = N;

  FILE* in = fopen ( "input.txt", "w+" ), *out = fopen ( "output.txt", "w+" );

  srand(time(NULL));
  gen_write_matr ( &matr1, in );
  char enter = '\n';
  fprintf ( in, "%c", enter );
  gen_write_matr ( &matr2, in );

  res_matr = mult ( matr1, matr2 );

  print_matr ( res_matr, out );

  return 0;
}
