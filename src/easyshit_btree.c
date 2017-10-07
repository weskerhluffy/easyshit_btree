/*
 ============================================================================
 Name        : easyshit_btree.c
 Author      : 
 Version     :
 Copyright   : a veces siento que
 Description : Hello World in C, Ansi-style
 ============================================================================
 XXX: https://www.hackerrank.com/contests/quora-haqathon/challenges/sortedset
 XXX: https://shehack.hackerearth.com/es/problem/algorithm/micro-and-strings/
 */
#if 1
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <stdint.h>

#ifdef CACA_COMUN_LOG
#include <execinfo.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include <time.h>
#include <stdarg.h>
#endif

#if 1
#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX LONG_MAX
#endif

#define CACA_COMUN_TAM_MAX_LINEA (16*200000)
#define CACA_LOG_MAX_TAM_CADENA 2000

#define CACA_COMUN_BUF_STATICO (char[1000] ) { '\0' }

#define BITCH_VECTOR_NUM_BITS (sizeof(bitch_vector) * 8)

#define CACA_COMUN_ASSERT_DUROTE 0
#define CACA_COMUN_ASSERT_SUAVECITO 1
#define CACA_COMUN_ASSERT_NIMADRES 2

#define CACA_COMUN_VALOR_INVALIDO ((tipo_dato)UINT_MAX)
#define CACA_COMUN_IDX_INVALIDO ((natural)CACA_COMUN_VALOR_INVALIDO)

typedef unsigned int natural;
typedef natural tipo_dato;
typedef long long entero_largo;
typedef unsigned long long entero_largo_sin_signo;
typedef long long bitch_vector;
typedef char byteme;

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;

/*
 #define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_SUAVECITO
 */
#define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_DUROTE

#define assert_timeout_dummy(condition) 0;

#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_DUROTE
#define assert_timeout(condition) assert(condition);
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_SUAVECITO
#define assert_timeout(condition) if(!(condition)){sleep(10);abort();}
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_NIMADRES
#define assert_timeout(condition) 0
#endif

#ifdef CACA_COMUN_LOG
#define caca_log_debug(formato, args...) \
		do \
		{ \
			size_t profundidad = 0; \
			void *array[CACA_LOG_MAX_TAM_CADENA]; \
 			profundidad = backtrace(array, CACA_LOG_MAX_TAM_CADENA); \
			caca_log_debug_func(formato,__FILE__, __func__, __LINE__,profundidad,##args); \
		} \
		while(0);
#else
#define caca_log_debug(formato, args...) 0;
#endif

#define caca_comun_max(x,y) ((x) < (y) ? (y) : (x))
#define caca_comun_min(x,y) ((x) < (y) ? (x) : (y))

void caca_log_debug_func(const char *format, ...);

void caca_comun_current_utc_time(struct timespec *ts) {

#ifdef __MACH__
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
#else
#ifdef CACA_COMUN_LOG
	clock_gettime(CLOCK_REALTIME, ts);
#endif
#endif

}

void caca_comun_timestamp(char *stime) {
	time_t ltime;
	struct tm result;
	long ms;
#ifndef ONLINE_JUDGE
	struct timespec spec;
#endif
	char parte_milisecundos[50];

	ltime = time(NULL);

#ifndef ONLINE_JUDGE
	localtime_r(&ltime, &result);
	asctime_r(&result, stime);
#endif

	*(stime + strlen(stime) - 1) = ' ';

#ifndef ONLINE_JUDGE
	caca_comun_current_utc_time(&spec);
	ms = round(spec.tv_nsec / 1.0e3);
#endif
	sprintf(parte_milisecundos, "%ld", ms);
	strcat(stime, parte_milisecundos);
}
#ifdef CACA_COMUN_LOG
void caca_log_debug_func(const char *format, ...) {

	va_list arg;
	va_list arg2;
	const char *PEDAZO_TIMESTAMP_HEADER = "tiempo: %s; ";
	const char *HEADER =
	"archivo: %s; funcion: %s; linea %d; nivel: %zd caca 8====D ";
	char formato[CACA_LOG_MAX_TAM_CADENA + sizeof(HEADER)
	+ sizeof(PEDAZO_TIMESTAMP_HEADER)] = {'\0'};
	char pedazo_timestamp[sizeof(PEDAZO_TIMESTAMP_HEADER) + 100] = {'\0'};
	char cadena_timestamp[100] = {'\0'};

	caca_comun_timestamp(cadena_timestamp);
	sprintf(pedazo_timestamp, PEDAZO_TIMESTAMP_HEADER, cadena_timestamp);

	strcpy(formato, pedazo_timestamp);
	strcat(formato, HEADER);
	strcat(formato, format);
	strcat(formato, "\n");

	va_start(arg, format);
	va_copy(arg2, arg);
	vprintf(formato, arg2);
	va_end(arg2);
	va_end(arg);
	setbuf(stdout, NULL);
}
#endif

#ifdef CACA_COMUN_LOG
static char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo, int tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos,
				"%12d", *(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}

static char *caca_comun_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2u",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
char *caca_comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	int i, j;
	natural inicio_buffer_act = 0;
	for (int i = 0; i < filas_tam; i++) {
		caca_comun_arreglo_a_cadena(matrix + i * columas_tam, columas_tam,
				buffer + inicio_buffer_act);
		inicio_buffer_act += strlen(buffer + inicio_buffer_act);
		buffer[inicio_buffer_act++] = '\n';
		/*		caca_log_debug("pero q mierda inicio buffer act %u %s",inicio_buffer_act,buffer);*/
	}
	return buffer;
}
#else
static char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo, int tam_arreglo,
		char *buffer) {
	return NULL;
}
static char *caca_comun_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	return NULL;
}
char *caca_comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	return NULL;
}
#endif
void caca_comun_strreplace(char s[], char chr, char repl_chr) {
	int i = 0;
	while (s[i] != '\0') {
		if (s[i] == chr) {
			s[i] = repl_chr;
		}
		i++;
	}
}

static int caca_comun_lee_matrix_long_stdin(tipo_dato *matrix, int *num_filas,
		int *num_columnas, int num_max_filas, int num_max_columnas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	tipo_dato numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char *linea = NULL;

	linea = calloc(CACA_COMUN_TAM_MAX_LINEA, sizeof(char));

	while (indice_filas < num_max_filas
			&& fgets(linea, CACA_COMUN_TAM_MAX_LINEA, stdin)) {
		indice_columnas = 0;
		cadena_numero_actual = linea;
		caca_comun_strreplace(linea, '\n', '\0');
		if (!strlen(linea)) {
			caca_log_debug("weird, linea vacia");
			continue;
		}
		for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
				cadena_numero_actual) {
			numero = strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
			if (cadena_numero_actual == siguiente_cadena_numero) {
				break;
			}
			*(matrix + indice_filas * num_max_columnas + indice_columnas) =
					numero;
			indice_columnas++;
		}
		if (num_columnas) {
			num_columnas[indice_filas] = indice_columnas;
		}
		indice_filas++;
		caca_log_debug("las filas son %d, con clos %d", indice_filas,
				indice_columnas);
	}

	*num_filas = indice_filas;
	free(linea);
	return 0;
}

static inline natural caca_comun_cuenta_bitchs(tipo_dato num) {
	natural bitch_cnt = 0;
	tipo_dato num_mod = 0;
	num_mod = num;
	while (num_mod) {
		num_mod &= ~(num_mod & (-num_mod));
		bitch_cnt++;
	}
	return bitch_cnt;
}

#endif
#endif

#if 1

// XXX: https://lispmachine.wordpress.com/2009/05/13/queue-in-c/
struct my_struct {
	void *valor;
	struct my_struct* next;
};

typedef struct my_list {
	struct my_struct* head;
	struct my_struct* tail;
} listilla_fifo;

/* Will always return the pointer to my_list */
struct my_list* list_add_element(struct my_list* s, void *valor) {
	struct my_struct* p = malloc(1 * sizeof(*p));

	if ( NULL == p) {
		fprintf(stderr, "IN %s, %s: malloc() failed\n", __FILE__, "list_add");
		return s;
	}

	p->valor = valor;
	p->next = NULL;

	if ( NULL == s) {
		printf("Queue not initialized\n");
		free(p);
		return s;
	} else if ( NULL == s->head && NULL == s->tail) {
		/* printf("Empty list, adding p->num: %d\n\n", p->num);  */
		s->head = s->tail = p;
		return s;
	} else if ( NULL == s->head || NULL == s->tail) {
		fprintf(stderr,
				"There is something seriously wrong with your assignment of head/tail to the list\n");
		free(p);
		return NULL;
	} else {
		/* printf("List not empty, adding element to tail\n"); */
		s->tail->next = p;
		s->tail = p;
	}

	return s;
}

/* This is a queue and it is FIFO, so we will always remove the first element */
static inline void *list_remove_element(struct my_list* s) {
	struct my_struct* h = NULL;
	struct my_struct* p = NULL;
	void *valor = NULL;

	if ( NULL == s) {
		printf("List is empty\n");
		return s;
	} else if ( NULL == s->head && NULL == s->tail) {
		printf("Well, List is empty\n");
		return s;
	} else if ( NULL == s->head || NULL == s->tail) {
		printf("There is something seriously wrong with your list\n");
		printf("One of the head/tail is empty while other is not \n");
		abort();
	}

	h = s->head;
	valor = h->valor;
	p = h->next;
	free(h);
	s->head = p;
	if ( NULL == s->head)
		s->tail = s->head; /* The element tail was pointing to is free(), so we need an update */

	return valor;
}

/* ---------------------- small helper fucntions ---------------------------------- */
struct my_list* list_free(struct my_list* s) {
	while (s->head) {
		list_remove_element(s);
	}

	return s;
}

struct my_list* list_new(void) {
	struct my_list* p = malloc(1 * sizeof(*p));

	assert_timeout(p);

	p->head = p->tail = NULL;

	return p;
}

void list_print_element(const struct my_struct* p) {
	if (p) {
		printf("Num = %p\n", p->valor);
	} else {
		printf("Can not print NULL struct \n");
	}
}

void list_print(const struct my_list* ps) {
	struct my_struct* p = NULL;

	if (ps) {
		for (p = ps->head; p; p = p->next) {
			list_print_element(p);
		}
	}

	printf("------------------\n");
}

static inline bool list_empty(struct my_list *s) {
	return !s->head;
}

#endif

#if 1

#define ARBOL_VERGA_VALOR_INVALIDO CACA_COMUN_VALOR_INVALIDO
#define ARBOL_VERGA_MAX_LLAVES 5
#define ARBOL_VERGA_MAX_HIJOS ARBOL_VERGA_MAX_LLAVES+1
#define ARBOL_VERGA_MAX_NODOS_LIBRES 100000
#define ARBOL_VERGA_IDX_INVALIDO CACA_COMUN_IDX_INVALIDO
#define ARBOL_VERGA_APUNTADOR_INVALIDO ((void*)ULONG_LONG_MAX)
#define ARBOL_VERGA_MIN_LLAVES (ARBOL_VERGA_MAX_LLAVES/2)
#define ARBOL_VERGA_POSICION_MEDIA_LLAVES ARBOL_VERGA_MIN_LLAVES

typedef int (*arbol_verga_compara_llave_fn)(void *, void *);

typedef struct arbol_verga_nodo {
	void *llaves_arbol_verga_nodo[ARBOL_VERGA_MAX_LLAVES];
	struct arbol_verga_nodo *hijos_arbol_verga_nodo[ARBOL_VERGA_MAX_HIJOS];
	natural llaves_cnt_arbol_verga_nodo;
} arbol_verga_nodo;

typedef struct arbol_verga_ctx {
	arbol_verga_nodo *raiz_arbol_verga_ctx;
	listilla_fifo *nodos_libres_arbol_verga_ctx;
	natural nodos_libres_cnt_arbol_verga_ctx;
	arbol_verga_nodo nodos_libres_mem_arbol_verga_ctx[ARBOL_VERGA_MAX_NODOS_LIBRES];
	arbol_verga_compara_llave_fn funcion_cmp_arbol_verga_ctx;
} arbol_verga_ctx;

typedef struct arbol_verga_datos_llave {
	void *llave_arbol_verga_datos_llave;
	natural posicion_arbol_verga_datos_llave;
} arbol_verga_datos_llave;

typedef struct arbol_verga_resultado_separar {
	arbol_verga_nodo *nodo_nuevo_arbol_verga_resultado_separar;
	tipo_dato *llave_para_promover_arbol_verga_resultado_separar;
} arbol_verga_resultado_separar;

static inline arbol_verga_ctx *arbol_verga_init(
		arbol_verga_compara_llave_fn funcion_cmp) {
	arbol_verga_ctx *ctx = NULL;

	ctx = calloc(1, sizeof(arbol_verga_ctx));
	assert_timeout(ctx);

	ctx->nodos_libres_arbol_verga_ctx = list_new();

	memset(ctx->nodos_libres_mem_arbol_verga_ctx, ARBOL_VERGA_VALOR_INVALIDO,
			sizeof(ctx->nodos_libres_mem_arbol_verga_ctx));

	for (int i = 0; i < ARBOL_VERGA_MAX_NODOS_LIBRES; i++) {
		list_add_element(ctx->nodos_libres_arbol_verga_ctx,
				ctx->nodos_libres_mem_arbol_verga_ctx + i);
	}
	ctx->nodos_libres_cnt_arbol_verga_ctx = ARBOL_VERGA_MAX_NODOS_LIBRES;

	ctx->funcion_cmp_arbol_verga_ctx = funcion_cmp;
	return ctx;
}

static inline void arbol_verga_fini(arbol_verga_ctx *ctx) {
	list_free(ctx->nodos_libres_arbol_verga_ctx);
	free(ctx);
}

static inline void arbol_verga_valida_hijos_invalidos(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo, natural inicio_hijos_invalidos) {
	for (int i = inicio_hijos_invalidos; i < ARBOL_VERGA_MAX_HIJOS; i++) {
		assert_timeout(
				nodo->hijos_arbol_verga_nodo[i]==ARBOL_VERGA_APUNTADOR_INVALIDO);
	}
}
static inline arbol_verga_nodo *arbol_verga_alloca_nodo(arbol_verga_ctx *ctx) {
	arbol_verga_nodo *nodo = NULL;

	nodo = list_remove_element(ctx->nodos_libres_arbol_verga_ctx);

	assert_timeout(
			nodo->llaves_cnt_arbol_verga_nodo==ARBOL_VERGA_VALOR_INVALIDO);

	arbol_verga_valida_hijos_invalidos(ctx, nodo, 0);
	ctx->nodos_libres_cnt_arbol_verga_ctx--;
	nodo->llaves_cnt_arbol_verga_nodo = 0;

	return nodo;
}

static inline void arbol_verga_libera_nodo(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo) {

	memset(nodo, ARBOL_VERGA_VALOR_INVALIDO, sizeof(arbol_verga_nodo));
	arbol_verga_valida_hijos_invalidos(ctx, nodo, 0);
	list_add_element(ctx->nodos_libres_arbol_verga_ctx, nodo);
	ctx->nodos_libres_cnt_arbol_verga_ctx++;
}

static inline arbol_verga_nodo *arbol_verga_borra_llave_datos_llave(
		arbol_verga_ctx *ctx, arbol_verga_nodo *nodo,
		arbol_verga_datos_llave *datos_llave) {
	natural pos_llave = 0;
	natural offset_hijo = 0;
	void *(*llaves)[ARBOL_VERGA_MAX_LLAVES] = NULL;
	arbol_verga_nodo *(*hijos)[ARBOL_VERGA_MAX_HIJOS] = NULL;
	arbol_verga_nodo *huerfano = NULL;

	llaves = &nodo->llaves_arbol_verga_nodo;
	hijos = &nodo->hijos_arbol_verga_nodo;

	pos_llave = datos_llave->posicion_arbol_verga_datos_llave;
	if (!pos_llave && nodo->llaves_cnt_arbol_verga_nodo > 1) {
		offset_hijo = 0;
	} else {
		offset_hijo = 1;
	}

	caca_log_debug(
			"la llave a borrar %p, supone estar en pos %u, lo q realmente ai %p",
			datos_llave->llave_arbol_verga_datos_llave, pos_llave,
			(*llaves)[pos_llave]);
	assert_timeout(
			datos_llave->llave_arbol_verga_datos_llave == (*llaves)[pos_llave]);

	caca_log_debug("borrando llave %p de pos %u",
			datos_llave->llave_arbol_verga_datos_llave, pos_llave);

	for (int i = pos_llave; i < nodo->llaves_cnt_arbol_verga_nodo - 1; i++) {
		caca_log_debug("llave en pos %u antes era %p aora %p", i, (*llaves)[i],
				(*llaves)[i+1]);
		assert_timeout((*llaves)[i+1]!=ARBOL_VERGA_APUNTADOR_INVALIDO);
		(*llaves)[i] = (*llaves)[i + 1];
	}
	(*llaves)[nodo->llaves_cnt_arbol_verga_nodo - 1] =
	ARBOL_VERGA_APUNTADOR_INVALIDO;

	caca_log_debug("borrada llave %p en pos %u",
			datos_llave->llave_arbol_verga_datos_llave, pos_llave);

	huerfano = (*hijos)[pos_llave + offset_hijo];
	for (int i = pos_llave + offset_hijo;
			i < nodo->llaves_cnt_arbol_verga_nodo + 1 - 1; i++) {
		(*hijos)[i] = (*hijos)[i + 1];
	}
	(*hijos)[nodo->llaves_cnt_arbol_verga_nodo + 1 - 1] =
	ARBOL_VERGA_APUNTADOR_INVALIDO;

	nodo->llaves_cnt_arbol_verga_nodo--;

	arbol_verga_valida_hijos_invalidos(ctx, nodo,
			nodo->llaves_cnt_arbol_verga_nodo + 1);

	return huerfano;
}

static inline void arbol_verga_inserta_llave_datos_llave(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo, arbol_verga_datos_llave *datos_llave,
		arbol_verga_nodo *nuevo_hijo) {
	void *(*llaves)[ARBOL_VERGA_MAX_LLAVES] = NULL;
	arbol_verga_nodo *(*hijos)[ARBOL_VERGA_MAX_HIJOS] = NULL;
	natural offset_hijo = 0;

	caca_log_debug("insertando %p en pos %u",
			datos_llave->llave_arbol_verga_datos_llave,
			datos_llave->posicion_arbol_verga_datos_llave);

	assert_timeout(nodo->llaves_cnt_arbol_verga_nodo<ARBOL_VERGA_MAX_HIJOS);

	llaves = &nodo->llaves_arbol_verga_nodo;
	hijos = &nodo->hijos_arbol_verga_nodo;

	if (datos_llave->posicion_arbol_verga_datos_llave
			|| !nodo->llaves_cnt_arbol_verga_nodo) {
		offset_hijo = 1;
	} else {
		offset_hijo = 0;
	}

	for (int i = nodo->llaves_cnt_arbol_verga_nodo;
			i > datos_llave->posicion_arbol_verga_datos_llave; i--) {
		caca_log_debug("pos %u tenia %p aora tiene llave %p", i, (*llaves)[i],
				(*llaves)[i-1]);
		assert_timeout((*llaves)[i-1]!=ARBOL_VERGA_APUNTADOR_INVALIDO);
		(*llaves)[i] = (*llaves)[i - 1];
	}

	assert_timeout(nodo->llaves_cnt_arbol_verga_nodo<ARBOL_VERGA_MAX_HIJOS);

	(*llaves)[datos_llave->posicion_arbol_verga_datos_llave] =
			datos_llave->llave_arbol_verga_datos_llave;

	assert_timeout(nodo->llaves_cnt_arbol_verga_nodo<ARBOL_VERGA_MAX_HIJOS);

	caca_log_debug("llave %p insertada en %u",
			datos_llave->llave_arbol_verga_datos_llave,
			datos_llave->posicion_arbol_verga_datos_llave);

	for (int i = nodo->llaves_cnt_arbol_verga_nodo + 1;
			i > datos_llave->posicion_arbol_verga_datos_llave + offset_hijo;
			i--) {
		(*hijos)[i] = (*hijos)[i - 1];
	}

	assert_timeout(nodo->llaves_cnt_arbol_verga_nodo<ARBOL_VERGA_MAX_HIJOS);

	(*hijos)[datos_llave->posicion_arbol_verga_datos_llave + offset_hijo] =
			nuevo_hijo;

	nodo->llaves_cnt_arbol_verga_nodo++;
	assert_timeout(nodo->llaves_cnt_arbol_verga_nodo<=ARBOL_VERGA_MAX_LLAVES);
	arbol_verga_valida_hijos_invalidos(ctx, nodo,
			nodo->llaves_cnt_arbol_verga_nodo + 1);
}

#define arbol_verga_obten_hijo_en_pos(nodo,pos) ((nodo)->hijos_arbol_verga_nodo[pos])
#define arbol_verga_obten_hijo_izq(nodo, pos_llave) arbol_verga_obten_hijo_en_pos(nodo,pos_llave)
#define arbol_verga_obten_hijo_der(nodo, pos_llave) arbol_verga_obten_hijo_en_pos(nodo,pos_llave+1)
#define arbol_verga_obten_primer_hijo(nodo) (arbol_verga_obten_hijo_izq(nodo, 0))
#define arbol_verga_obten_ultimo_hijo(nodo) (arbol_verga_obten_hijo_der(nodo,(nodo)->llaves_cnt_arbol_verga_nodo-1))
#define arbol_verga_obten_llave_en_pos(nodo,pos) ((nodo)->llaves_arbol_verga_nodo[pos])
#define arbol_verga_pon_llave_en_pos(nodo,pos,llave) (nodo)->llaves_arbol_verga_nodo[pos]=(llave)
#define arbol_verga_pon_hijo_en_pos(nodo,pos,hijo) (nodo)->hijos_arbol_verga_nodo[pos]=(hijo)
#define arbol_verga_obten_primer_hijo(nodo) (arbol_verga_obten_hijo_izq(nodo, 0))
#define arbol_verga_obten_primer_llave(nodo) (arbol_verga_obten_llave_en_pos(nodo,0))
#define arbol_verga_obten_ultima_llave(nodo) (arbol_verga_obten_llave_en_pos(nodo,(nodo)->llaves_cnt_arbol_verga_nodo-1))
#define arbol_verga_obten_ultima_pos_llave(nodo) ((nodo)->llaves_cnt_arbol_verga_nodo-1)
#define arbol_verga_pon_hijo_izq_en_pos(nodo,pos,hijo) arbol_verga_pon_hijo_en_pos(nodo,pos,hijo)
#define arbol_verga_pon_hijo_der_en_pos(nodo,pos,hijo) arbol_verga_pon_hijo_en_pos(nodo,pos+1,hijo)
#define arbol_verga_datos_genera_datos_llave_local(llave,pos_llave) &(arbol_verga_datos_llave){.llave_arbol_verga_datos_llave=llave,.posicion_arbol_verga_datos_llave=pos_llave}
#define arbol_verga_nodo_tiene_suficientes_llaves(nodo) ((nodo)->llaves_cnt_arbol_verga_nodo>ARBOL_VERGA_MIN_LLAVES)
#define arbol_verga_nodo_tiene_llaves_llenas(nodo) ((nodo)->llaves_cnt_arbol_verga_nodo==ARBOL_VERGA_MAX_LLAVES)

static inline void arbol_verga_rota_izquierda(arbol_verga_ctx *ctx,
		arbol_verga_nodo *hijo_izq, arbol_verga_nodo *padre,
		arbol_verga_nodo *hijo_der, arbol_verga_datos_llave *datos_llave) {
	arbol_verga_nodo *hijo_de_llave_en_padre = NULL;

	assert_timeout(hijo_der->llaves_cnt_arbol_verga_nodo>ARBOL_VERGA_MIN_LLAVES);
	caca_log_debug("insertando en ijo izq");
	arbol_verga_inserta_llave_datos_llave(ctx, hijo_izq,
			&(arbol_verga_datos_llave ) { .llave_arbol_verga_datos_llave =
							datos_llave->llave_arbol_verga_datos_llave,
							.posicion_arbol_verga_datos_llave =
									hijo_izq->llaves_cnt_arbol_verga_nodo },
			arbol_verga_obten_primer_hijo(hijo_der));

	if (datos_llave->posicion_arbol_verga_datos_llave
			|| padre->llaves_cnt_arbol_verga_nodo < 2) {
		hijo_de_llave_en_padre = arbol_verga_obten_hijo_der(padre,
				datos_llave->posicion_arbol_verga_datos_llave);
	} else {
		hijo_de_llave_en_padre = arbol_verga_obten_hijo_izq(padre,
				datos_llave->posicion_arbol_verga_datos_llave);
	}

	caca_log_debug("borrando de padre");
	arbol_verga_nodo *hijo_de_llave_en_padre_tmp =
			arbol_verga_borra_llave_datos_llave(ctx, padre, datos_llave);

	caca_log_debug("el hijo de llave esperado %p, el real %p",
			hijo_de_llave_en_padre, hijo_de_llave_en_padre_tmp);

	assert_timeout(hijo_de_llave_en_padre == hijo_de_llave_en_padre_tmp);

	caca_log_debug("reinsertando en padre");
	arbol_verga_inserta_llave_datos_llave(ctx, padre,
			&(arbol_verga_datos_llave ) { .llave_arbol_verga_datos_llave =
							arbol_verga_obten_llave_en_pos(hijo_der, 0),
							.posicion_arbol_verga_datos_llave =
									datos_llave->posicion_arbol_verga_datos_llave },
			hijo_de_llave_en_padre);

	arbol_verga_nodo *tmp = arbol_verga_obten_primer_hijo(hijo_der);
	caca_log_debug("borrando de hijo der");
	arbol_verga_nodo *tmp1 = arbol_verga_borra_llave_datos_llave(ctx, hijo_der,
			&(arbol_verga_datos_llave ) { .llave_arbol_verga_datos_llave =
							arbol_verga_obten_llave_en_pos(hijo_der, 0),
							.posicion_arbol_verga_datos_llave = 0 });

	assert_timeout(tmp == tmp1);

}

static inline void arbol_verga_rota_derecha(arbol_verga_ctx *ctx,
		arbol_verga_nodo *hijo_izq, arbol_verga_nodo *padre,
		arbol_verga_nodo *hijo_der, arbol_verga_datos_llave *datos_llave) {
	arbol_verga_nodo *hijo_de_llave_en_padre = NULL;

	assert_timeout(hijo_izq->llaves_cnt_arbol_verga_nodo>ARBOL_VERGA_MIN_LLAVES);
	arbol_verga_inserta_llave_datos_llave(ctx, hijo_der,
			&(arbol_verga_datos_llave ) { .llave_arbol_verga_datos_llave =
							datos_llave->llave_arbol_verga_datos_llave,
							.posicion_arbol_verga_datos_llave = 0 },
			arbol_verga_obten_ultimo_hijo(hijo_izq));

	if (datos_llave->posicion_arbol_verga_datos_llave
			|| padre->llaves_cnt_arbol_verga_nodo < 2) {
		hijo_de_llave_en_padre = arbol_verga_obten_hijo_der(padre,
				datos_llave->posicion_arbol_verga_datos_llave);
	} else {
		hijo_de_llave_en_padre = arbol_verga_obten_hijo_izq(padre,
				datos_llave->posicion_arbol_verga_datos_llave);
	}

	arbol_verga_nodo *hijo_de_llave_en_padre_tmp =
			arbol_verga_borra_llave_datos_llave(ctx, padre, datos_llave);

	assert_timeout(hijo_de_llave_en_padre == hijo_de_llave_en_padre_tmp);

	arbol_verga_inserta_llave_datos_llave(ctx, padre,
			&(arbol_verga_datos_llave ) { .llave_arbol_verga_datos_llave =
							arbol_verga_obten_ultima_llave(hijo_izq),
							.posicion_arbol_verga_datos_llave =
									datos_llave->posicion_arbol_verga_datos_llave },
			hijo_de_llave_en_padre);

	arbol_verga_nodo *tmp = arbol_verga_obten_ultimo_hijo(hijo_izq);
	arbol_verga_nodo *tmp1 =
			arbol_verga_borra_llave_datos_llave(ctx, hijo_izq,
					&(arbol_verga_datos_llave ) {
									.llave_arbol_verga_datos_llave =
											arbol_verga_obten_ultima_llave(
													hijo_izq),
									.posicion_arbol_verga_datos_llave =
											hijo_izq->llaves_cnt_arbol_verga_nodo
													- 1 });

	assert_timeout(tmp == tmp1);
}

static inline bool arbol_verga_encuentra_llave_en_nodo(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo, void *llave,
		arbol_verga_datos_llave *datos_llave) {
	bool encontrada = falso;
	natural idx = 0;

	for (idx = 0; idx < nodo->llaves_cnt_arbol_verga_nodo; idx++) {
		// TODO: usar callback
		if (arbol_verga_obten_llave_en_pos(nodo,idx) >= llave) {
			if (arbol_verga_obten_llave_en_pos(nodo,idx) == llave) {
				encontrada = verdadero;
			}
			break;
		}
	}

//	assert_timeout(idx < nodo->llaves_cnt_arbol_verga_nodo);

	datos_llave->llave_arbol_verga_datos_llave = llave;
	datos_llave->posicion_arbol_verga_datos_llave = idx;

	return encontrada;
}

static inline void arbol_verga_inserta_llave_en_nodo(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo, void *llave, arbol_verga_nodo *nuevo_hijo) {
	arbol_verga_datos_llave *datos_llave = &(arbol_verga_datos_llave ) {
					.llave_arbol_verga_datos_llave =
					ARBOL_VERGA_APUNTADOR_INVALIDO,
					.posicion_arbol_verga_datos_llave =
					ARBOL_VERGA_IDX_INVALIDO };
	bool encontrada_llave = falso;

	encontrada_llave = arbol_verga_encuentra_llave_en_nodo(ctx, nodo, llave,
			datos_llave);

	assert_timeout(!encontrada_llave);

	arbol_verga_inserta_llave_datos_llave(ctx, nodo, datos_llave, nuevo_hijo);
}

static inline arbol_verga_nodo *arbol_verga_borra_llave_en_nodo(
		arbol_verga_ctx *ctx, arbol_verga_nodo *nodo, void *llave) {
	arbol_verga_datos_llave *datos_llave = &(arbol_verga_datos_llave ) {
					.llave_arbol_verga_datos_llave =
					ARBOL_VERGA_APUNTADOR_INVALIDO,
					.posicion_arbol_verga_datos_llave =
					ARBOL_VERGA_IDX_INVALIDO };
	bool encontrada_llave = falso;

	encontrada_llave = arbol_verga_encuentra_llave_en_nodo(ctx, nodo, llave,
			datos_llave);

	assert_timeout(encontrada_llave);

	caca_log_debug("la llave %p se encontro en %u", llave,
			datos_llave->posicion_arbol_verga_datos_llave);

	return arbol_verga_borra_llave_datos_llave(ctx, nodo, datos_llave);
}

#define arbol_verga_inserta_al_final_con_datos_llave(ctx,nodo,llave, nuevo_hijo) \
	arbol_verga_inserta_llave_datos_llave(ctx, nodo, \
										 &(arbol_verga_datos_llave ) { .llave_arbol_verga_datos_llave = llave, \
																	  .posicion_arbol_verga_datos_llave =arbol_verga_obten_ultima_pos_llave(nodo) +1}, \
										 nuevo_hijo)

static inline void arbol_verga_mergea_nodos(arbol_verga_ctx *ctx,
		arbol_verga_nodo *hijo_izq, arbol_verga_nodo *padre,
		arbol_verga_nodo *hijo_der, arbol_verga_datos_llave *datos_llave) {

	assert_timeout(
			hijo_izq->llaves_cnt_arbol_verga_nodo<=ARBOL_VERGA_MIN_LLAVES);
	assert_timeout(
			hijo_der->llaves_cnt_arbol_verga_nodo<=ARBOL_VERGA_MIN_LLAVES);

	arbol_verga_inserta_al_final_con_datos_llave(ctx, hijo_izq,
			datos_llave->llave_arbol_verga_datos_llave,
			arbol_verga_obten_primer_hijo(hijo_der));

	for (int i = 0; i <= arbol_verga_obten_ultima_pos_llave(hijo_der); i++) {
		arbol_verga_inserta_al_final_con_datos_llave(ctx, hijo_izq,
				arbol_verga_obten_llave_en_pos(hijo_der,i),
				arbol_verga_obten_hijo_der(hijo_der,i));
	}

	arbol_verga_borra_llave_datos_llave(ctx, padre, datos_llave);

	arbol_verga_pon_hijo_izq_en_pos(padre,
			datos_llave->posicion_arbol_verga_datos_llave, hijo_izq);

	arbol_verga_libera_nodo(ctx, hijo_der);
}

static inline void *arbol_verga_encuentra_siguiente_llave(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo) {
	void *resu = NULL;
	while (nodo != ARBOL_VERGA_APUNTADOR_INVALIDO) {
		resu = arbol_verga_obten_primer_llave(nodo);
		nodo = arbol_verga_obten_primer_hijo(nodo);
	}

	return resu;
}

static inline void *arbol_verga_encuentra_anterior_llave(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo) {
	void *resu = NULL;
	while (nodo != ARBOL_VERGA_APUNTADOR_INVALIDO) {
		resu = arbol_verga_obten_ultima_llave(nodo);
		nodo = arbol_verga_obten_ultimo_hijo(nodo);
	}

	return resu;
}

typedef enum arbol_verga_caso_prestador {
	izq_arbol_verga_caso_prestador,
	der_arbol_verga_caso_prestador,
	ninguno_presta_izq_existe_arbol_verga_caso_prestador,
	ninguno_presta_der_existe_arbol_verga_caso_prestador,
	ninguno_arbol_verga_caso_prestador
} arbol_verga_caso_prestador;
#define ninguno_arbol_verga_caso_prestador ninguno_presta_izq_existe_arbol_verga_caso_prestador

static inline arbol_verga_caso_prestador arbol_verga_encuentra_prestador(
		arbol_verga_ctx *ctx, arbol_verga_nodo *padre, natural nodo_izq_idx,
		natural nodo_der_idx, arbol_verga_nodo **hijo_prestador) {
	arbol_verga_caso_prestador cacaso = ninguno_arbol_verga_caso_prestador;
	natural tam_izq = 0;
	natural tam_der = 0;

	*hijo_prestador = NULL;
	if (((int) nodo_izq_idx) >= 0
			&& nodo_izq_idx <= padre->llaves_cnt_arbol_verga_nodo) {
		arbol_verga_nodo *nodo_prestador = arbol_verga_obten_hijo_en_pos(padre,
				nodo_izq_idx);
		tam_izq = nodo_prestador->llaves_cnt_arbol_verga_nodo;
		cacaso = ninguno_presta_izq_existe_arbol_verga_caso_prestador;
		caca_log_debug("existe ijo izq con %u llaves", tam_izq);
		if (tam_izq > ARBOL_VERGA_MIN_LLAVES) {
			cacaso = izq_arbol_verga_caso_prestador;
			*hijo_prestador = nodo_prestador;
		}
	}
	if (nodo_der_idx <= padre->llaves_cnt_arbol_verga_nodo) {
		arbol_verga_nodo *nodo_prestador = arbol_verga_obten_hijo_en_pos(padre,
				nodo_der_idx);
		tam_der = nodo_prestador->llaves_cnt_arbol_verga_nodo;
		if (cacaso == ninguno_arbol_verga_caso_prestador) {
			cacaso = ninguno_presta_der_existe_arbol_verga_caso_prestador;
		}
		caca_log_debug("existe ijo der con %u llaves", tam_der);
		if (tam_der > ARBOL_VERGA_MIN_LLAVES && tam_der > tam_izq) {
			cacaso = der_arbol_verga_caso_prestador;
			*hijo_prestador = nodo_prestador;
		}
	}

	return cacaso;
}

static inline bool arbol_verga_nodo_es_hoja(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo) {
	bool es_hoja = falso;

	es_hoja = arbol_verga_obten_primer_hijo(
			nodo) == ARBOL_VERGA_APUNTADOR_INVALIDO;

	if (es_hoja) {
		for (int i = 0; i <= nodo->llaves_cnt_arbol_verga_nodo; i++) {
			assert_timeout(
					arbol_verga_obten_hijo_en_pos(nodo,i)==ARBOL_VERGA_APUNTADOR_INVALIDO);
		}
	}

	return es_hoja;
}

static inline void arbol_verga_borra_llave(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo, void *llave) {
	bool llave_encontrada = falso;
	arbol_verga_datos_llave *datos_llave = &(arbol_verga_datos_llave ) { 0 };

	llave_encontrada = arbol_verga_encuentra_llave_en_nodo(ctx, nodo, llave,
			datos_llave);

	if (!llave_encontrada) {
		if (!arbol_verga_nodo_es_hoja(ctx, nodo)) {
			bool liberar_nodo = falso;
			natural posicion_siguiente_nodo =
					datos_llave->posicion_arbol_verga_datos_llave;

			if (!arbol_verga_nodo_tiene_suficientes_llaves(
					arbol_verga_obten_hijo_en_pos(nodo,posicion_siguiente_nodo))) {
				natural posicion_prestador_izq = posicion_siguiente_nodo - 1;
				natural posicion_prestador_der = posicion_siguiente_nodo + 1;
				arbol_verga_nodo *nodo_prestador = NULL;

				arbol_verga_caso_prestador cacaso =
						arbol_verga_encuentra_prestador(ctx, nodo,
								posicion_prestador_izq, posicion_prestador_der,
								&nodo_prestador);

				switch (cacaso) {
				case izq_arbol_verga_caso_prestador:
					arbol_verga_rota_derecha(ctx, nodo_prestador, nodo,
							arbol_verga_obten_hijo_en_pos(nodo,
									posicion_siguiente_nodo),
							arbol_verga_datos_genera_datos_llave_local(
									arbol_verga_obten_llave_en_pos(nodo,posicion_prestador_izq),
									posicion_prestador_izq));
					break;
				case der_arbol_verga_caso_prestador:
					arbol_verga_rota_izquierda(ctx,
							arbol_verga_obten_hijo_en_pos(nodo,
									posicion_siguiente_nodo), nodo,
							nodo_prestador,
							arbol_verga_datos_genera_datos_llave_local(
									arbol_verga_obten_llave_en_pos(nodo,posicion_siguiente_nodo),
									posicion_siguiente_nodo));
					break;
				default:
					switch (cacaso) {
					case ninguno_presta_izq_existe_arbol_verga_caso_prestador:
						arbol_verga_mergea_nodos(ctx,
								arbol_verga_obten_hijo_en_pos(nodo,
										posicion_prestador_izq), nodo,
								arbol_verga_obten_hijo_en_pos(nodo,
										posicion_siguiente_nodo),
								arbol_verga_datos_genera_datos_llave_local(
										arbol_verga_obten_llave_en_pos(nodo,posicion_prestador_izq),
										posicion_prestador_izq));

						posicion_siguiente_nodo = posicion_prestador_izq;
						break;
					case ninguno_presta_der_existe_arbol_verga_caso_prestador:
						arbol_verga_mergea_nodos(ctx,
								arbol_verga_obten_hijo_en_pos(nodo,
										posicion_siguiente_nodo), nodo,
								arbol_verga_obten_hijo_en_pos(nodo,
										posicion_prestador_der),
								arbol_verga_datos_genera_datos_llave_local(
										arbol_verga_obten_llave_en_pos(nodo,posicion_siguiente_nodo),
										posicion_siguiente_nodo));
						break;
					default:
						abort();
						break;
					}
					if (!nodo->llaves_cnt_arbol_verga_nodo) {
						ctx->raiz_arbol_verga_ctx =
								arbol_verga_obten_primer_hijo(nodo);
						liberar_nodo = verdadero;
					}
					break;
				}
			}
			arbol_verga_borra_llave(ctx,
					arbol_verga_obten_hijo_en_pos(nodo,
							posicion_siguiente_nodo), llave);
			if (liberar_nodo) {
				arbol_verga_libera_nodo(ctx, nodo);
			}

		} else {
			abort();
		}
	} else {
		natural posicion_llave = datos_llave->posicion_arbol_verga_datos_llave;
		if (!arbol_verga_nodo_es_hoja(ctx, nodo)) {
			natural posicion_prestador_izq = posicion_llave;
			natural posicion_prestador_der = posicion_llave + 1;
			arbol_verga_nodo *nodo_prestador = NULL;

			arbol_verga_caso_prestador cacaso = arbol_verga_encuentra_prestador(
					ctx, nodo, posicion_prestador_izq, posicion_prestador_der,
					&nodo_prestador);

			switch (cacaso) {
			case izq_arbol_verga_caso_prestador:
			case der_arbol_verga_caso_prestador: {
				arbol_verga_nodo *nodo_a_restaurar = NULL;
				natural pos_a_restaurar = 0;
				void *llave_nueva = NULL;
				if (cacaso == izq_arbol_verga_caso_prestador) {
					llave_nueva = arbol_verga_encuentra_anterior_llave(ctx,
							nodo_prestador);
				} else {
					llave_nueva = arbol_verga_encuentra_siguiente_llave(ctx,
							nodo_prestador);
				}

				if (nodo->llaves_cnt_arbol_verga_nodo < 2
						|| datos_llave->posicion_arbol_verga_datos_llave) {
					pos_a_restaurar = posicion_llave + 1;
				} else {
					pos_a_restaurar = posicion_llave;
				}
				nodo_a_restaurar = arbol_verga_borra_llave_datos_llave(ctx,
						nodo, datos_llave);

				arbol_verga_inserta_llave_datos_llave(ctx, nodo,
						arbol_verga_datos_genera_datos_llave_local(llave_nueva,
								posicion_llave), nodo_a_restaurar);

				arbol_verga_borra_llave(ctx, nodo_prestador, llave_nueva);
			}
				break;
			default:
				if (cacaso
						== ninguno_presta_der_existe_arbol_verga_caso_prestador
						|| cacaso
								== ninguno_presta_izq_existe_arbol_verga_caso_prestador) {
					arbol_verga_mergea_nodos(ctx,
							arbol_verga_obten_hijo_en_pos(nodo,
									posicion_prestador_izq), nodo,
							arbol_verga_obten_hijo_en_pos(nodo,
									posicion_prestador_der), datos_llave);

					arbol_verga_borra_llave(ctx,
							arbol_verga_obten_hijo_en_pos(nodo,
									posicion_prestador_izq), llave);

				} else {
					abort();
				}
				break;
			}
		} else {
			arbol_verga_borra_llave_datos_llave(ctx, nodo, datos_llave);
		}
	}
	arbol_verga_valida_hijos_invalidos(ctx, nodo,
			nodo->llaves_cnt_arbol_verga_nodo + 1);
}

static inline void arbol_verga_separa(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo, arbol_verga_resultado_separar *resultado_sep) {
	arbol_verga_nodo *nuevo_nodo = NULL;
	arbol_verga_nodo *nodo_a_separar = nodo;

	nuevo_nodo = arbol_verga_alloca_nodo(ctx);

	resultado_sep->llave_para_promover_arbol_verga_resultado_separar =
			arbol_verga_obten_llave_en_pos(nodo_a_separar,
					ARBOL_VERGA_POSICION_MEDIA_LLAVES);

	caca_log_debug("la llave a promover %p",
			resultado_sep->llave_para_promover_arbol_verga_resultado_separar);

	arbol_verga_inserta_llave_datos_llave(ctx, nuevo_nodo,
			arbol_verga_datos_genera_datos_llave_local(
					arbol_verga_obten_llave_en_pos(nodo_a_separar,ARBOL_VERGA_POSICION_MEDIA_LLAVES+1),
					0),
			arbol_verga_obten_hijo_en_pos(nodo_a_separar,
					ARBOL_VERGA_POSICION_MEDIA_LLAVES+1));

	caca_log_debug(
			"en nueov nodo_a_separar insertada llave %p hijo %p en pos %u",
			arbol_verga_obten_primer_llave(nuevo_nodo),
			arbol_verga_obten_primer_hijo(nuevo_nodo), 0);

	arbol_verga_pon_hijo_en_pos(nuevo_nodo,
			nuevo_nodo->llaves_cnt_arbol_verga_nodo,
			arbol_verga_obten_hijo_en_pos(nodo_a_separar,ARBOL_VERGA_POSICION_MEDIA_LLAVES+2));

	caca_log_debug("aora en nuevo nodo_a_separar seteado segundo hijo %p ",
			arbol_verga_obten_ultimo_hijo(nuevo_nodo));

	caca_log_debug("se empezara copia de %u, terminando en %u",
			ARBOL_VERGA_POSICION_MEDIA_LLAVES+2,
			arbol_verga_obten_ultima_pos_llave(nodo_a_separar));
	for (int i = ARBOL_VERGA_POSICION_MEDIA_LLAVES + 2;
			i <= arbol_verga_obten_ultima_pos_llave(nodo_a_separar); i++) {
		void *llave_actual = arbol_verga_obten_llave_en_pos(nodo_a_separar, i);
		arbol_verga_inserta_llave_datos_llave(ctx, nuevo_nodo,
				arbol_verga_datos_genera_datos_llave_local(llave_actual,
						nuevo_nodo->llaves_cnt_arbol_verga_nodo),
				arbol_verga_obten_hijo_der(nodo_a_separar, i));
		caca_log_debug(
				"insertando llave %p hijo %p en pos orig %u en nuevo en pos %u",
				llave_actual, arbol_verga_obten_hijo_der(nodo_a_separar,i), i,
				nuevo_nodo->llaves_cnt_arbol_verga_nodo);
	}

	while (nodo_a_separar->llaves_cnt_arbol_verga_nodo > ARBOL_VERGA_MIN_LLAVES) {
		void *llave_actual = arbol_verga_obten_ultima_llave(nodo_a_separar);
		caca_log_debug("borrando llave %p de pos %u de oroginal", llave_actual,
				arbol_verga_obten_ultima_pos_llave(nodo_a_separar));

		arbol_verga_borra_llave_datos_llave(ctx, nodo_a_separar,
				arbol_verga_datos_genera_datos_llave_local(llave_actual,
						arbol_verga_obten_ultima_pos_llave(nodo_a_separar)));
	}

	resultado_sep->nodo_nuevo_arbol_verga_resultado_separar = nuevo_nodo;
}

static inline void arbol_verga_separa_y_promueve(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo, natural posicion_hijo_a_separar) {
	arbol_verga_nodo *nodo_a_separar = NULL;
	arbol_verga_nodo *nodo_nuevo = NULL;
	arbol_verga_resultado_separar *resultado_sep =
			&(arbol_verga_resultado_separar ) { 0 };

	nodo_a_separar = arbol_verga_obten_hijo_en_pos(nodo,
			posicion_hijo_a_separar);

	arbol_verga_separa(ctx, nodo_a_separar, resultado_sep);

	caca_log_debug("separado hijo %u", posicion_hijo_a_separar);

	arbol_verga_inserta_llave_datos_llave(ctx, nodo,
			arbol_verga_datos_genera_datos_llave_local(
					resultado_sep->llave_para_promover_arbol_verga_resultado_separar,
					posicion_hijo_a_separar),
			resultado_sep->nodo_nuevo_arbol_verga_resultado_separar);

	caca_log_debug("insertada llave %p en pos %u de padre",
			resultado_sep->llave_para_promover_arbol_verga_resultado_separar,
			posicion_hijo_a_separar);

	if (!posicion_hijo_a_separar) {
		caca_log_debug("swapeando al max");
		arbol_verga_nodo *hijo_izq = arbol_verga_obten_hijo_der(nodo,
				posicion_hijo_a_separar);
		arbol_verga_nodo *hijo_der = arbol_verga_obten_hijo_izq(nodo,
				posicion_hijo_a_separar);

		arbol_verga_pon_hijo_izq_en_pos(nodo, posicion_hijo_a_separar,
				hijo_izq);
		arbol_verga_pon_hijo_der_en_pos(nodo, posicion_hijo_a_separar,
				hijo_der);
	}
}

static inline void arbol_verga_inserta_recursivo(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo, void *llave) {

	assert_timeout(nodo->llaves_cnt_arbol_verga_nodo<ARBOL_VERGA_MAX_LLAVES);
	if (arbol_verga_nodo_es_hoja(ctx, nodo)) {
		arbol_verga_inserta_llave_en_nodo(ctx, nodo, llave,
		ARBOL_VERGA_APUNTADOR_INVALIDO);
	} else {
		natural pos_sig_nodo_para_buscar = 0;
		arbol_verga_nodo *sig_nodo_para_buscar = NULL;
		arbol_verga_datos_llave *datos_llave =
				arbol_verga_datos_genera_datos_llave_local(
						ARBOL_VERGA_APUNTADOR_INVALIDO,
						ARBOL_VERGA_APUNTADOR_INVALIDO);
		bool llave_enc = arbol_verga_encuentra_llave_en_nodo(ctx, nodo, llave,
				datos_llave);
		assert_timeout(!llave_enc);
		pos_sig_nodo_para_buscar =
				datos_llave->posicion_arbol_verga_datos_llave;

		sig_nodo_para_buscar = arbol_verga_obten_hijo_en_pos(nodo,
				pos_sig_nodo_para_buscar);

		if (arbol_verga_nodo_tiene_llaves_llenas(sig_nodo_para_buscar)) {
			arbol_verga_nodo *hijo_izq = NULL;
			arbol_verga_nodo *hijo_der = NULL;
			void *llave_promovida = NULL;
			arbol_verga_separa_y_promueve(ctx, nodo, pos_sig_nodo_para_buscar);

			llave_promovida = arbol_verga_obten_llave_en_pos(nodo,
					pos_sig_nodo_para_buscar);
			hijo_izq = arbol_verga_obten_hijo_izq(nodo,
					pos_sig_nodo_para_buscar);
			hijo_der = arbol_verga_obten_hijo_der(nodo,
					pos_sig_nodo_para_buscar);

			// TODO: usar callback
			if (llave < llave_promovida) {
				sig_nodo_para_buscar = hijo_izq;
			} else {
				sig_nodo_para_buscar = hijo_der;
			}
		}

		arbol_verga_inserta_recursivo(ctx, sig_nodo_para_buscar, llave);
	}

	arbol_verga_valida_hijos_invalidos(ctx, nodo,
			nodo->llaves_cnt_arbol_verga_nodo + 1);
}

static inline void arbol_verga_inserta(arbol_verga_ctx *ctx, void *llave) {
	arbol_verga_nodo *raiz = NULL;

	raiz = ctx->raiz_arbol_verga_ctx;

	caca_log_debug("insertando llave %p", llave);

	if (!raiz) {
		raiz = arbol_verga_alloca_nodo(ctx);
		arbol_verga_inserta_llave_datos_llave(ctx, raiz,
				arbol_verga_datos_genera_datos_llave_local(llave, 0),
				ARBOL_VERGA_APUNTADOR_INVALIDO);
		ctx->raiz_arbol_verga_ctx = raiz;
		caca_log_debug("insertada directo en la raiz");

	} else {
		if (arbol_verga_nodo_tiene_llaves_llenas(raiz)) {
			arbol_verga_nodo *nueva_raiz = NULL;
			arbol_verga_resultado_separar *resu_sep =
					&(arbol_verga_resultado_separar ) { 0 };

			arbol_verga_separa(ctx, raiz, resu_sep);

			nueva_raiz = arbol_verga_alloca_nodo(ctx);

			arbol_verga_inserta_llave_datos_llave(ctx, nueva_raiz,
					arbol_verga_datos_genera_datos_llave_local(
							resu_sep->llave_para_promover_arbol_verga_resultado_separar,
							0),
					resu_sep->nodo_nuevo_arbol_verga_resultado_separar);
			arbol_verga_pon_hijo_izq_en_pos(nueva_raiz, 0, raiz);

			raiz = ctx->raiz_arbol_verga_ctx = nueva_raiz;
			caca_log_debug("separada raiz, nueva tiene %u",
					raiz->llaves_cnt_arbol_verga_nodo);
		}
		arbol_verga_inserta_recursivo(ctx, raiz, llave);
	}
}

static inline void arbol_verga_dumpea_inorder_recursivo(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo, void *llaves, natural *llaves_cnt) {
	int i;
	if (nodo == ARBOL_VERGA_APUNTADOR_INVALIDO) {
		return;
	}
	for (i = 0; i < nodo->llaves_cnt_arbol_verga_nodo; i++) {
		arbol_verga_dumpea_inorder_recursivo(ctx,
				arbol_verga_obten_hijo_en_pos(nodo, i), llaves, llaves_cnt);
		printf("%u ", arbol_verga_obten_llave_en_pos(nodo, i));
	}
	arbol_verga_dumpea_inorder_recursivo(ctx,
			arbol_verga_obten_hijo_en_pos(nodo, i), llaves, llaves_cnt);
}

static inline void arbol_verga_dumpea_llaves_nodo(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo) {
	for (int i = 0; i < nodo->llaves_cnt_arbol_verga_nodo; i++) {
		printf("%d ", arbol_verga_obten_llave_en_pos(nodo, i));
	}
//	printf("\n");
}

static inline void arbol_verga_dumpea_bfs(arbol_verga_ctx *ctx, void *llaves,
		natural *llaves_cnt) {
	listilla_fifo *cola = NULL;

	cola = list_new();

	list_add_element(cola, ctx->raiz_arbol_verga_ctx);

	while (!list_empty(cola)) {
		arbol_verga_nodo *nodo = list_remove_element(cola);
		arbol_verga_dumpea_llaves_nodo(ctx, nodo);
		for (int i = 0; i <= nodo->llaves_cnt_arbol_verga_nodo; i++) {
			list_add_element(cola, arbol_verga_obten_hijo_en_pos(nodo, i));
		}
	}

	list_free(cola);
}

static inline void arbol_verga_dumpea_inorder(arbol_verga_ctx *ctx,
		void *llaves, natural *llaves_cnt) {
	arbol_verga_dumpea_inorder_recursivo(ctx, ctx->raiz_arbol_verga_ctx, llaves,
			llaves_cnt);
	printf("\n");
}

#endif

#ifndef INCLUIDO_PRUEBA
int main(void) {
	puts("he corrido con algo de suerte"); /* prints he corrido con algo de suerte */
	return EXIT_SUCCESS;
}
#endif
