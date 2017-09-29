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

#endif

#if 1

#define ARBOL_VERGA_VALOR_INVALIDO CACA_COMUN_VALOR_INVALIDO
#define ARBOL_VERGA_MAX_LLAVES 5
#define ARBOL_VERGA_MAX_HIJOS ARBOL_VERGA_MAX_LLAVES+1
#define ARBOL_VERGA_MAX_NODOS_LIBRES 100000
#define ARBOL_VERGA_IDX_INVALIDO CACA_COMUN_IDX_INVALIDO
#define ARBOL_VERGA_APUNTADOR_INVALIDO ((void*)ULONG_LONG_MAX)

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

static inline arbol_verga_nodo *arbol_verga_alloca_nodo(arbol_verga_ctx *ctx) {
	arbol_verga_nodo *nodo = NULL;

	nodo = list_remove_element(ctx->nodos_libres_arbol_verga_ctx);

	assert_timeout(
			nodo->llaves_cnt_arbol_verga_nodo==ARBOL_VERGA_VALOR_INVALIDO);
	ctx->nodos_libres_cnt_arbol_verga_ctx--;

	return nodo;
}

static inline void arbol_verga_libera_nodo(arbol_verga_ctx *ctx,
		arbol_verga_nodo *nodo) {
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

	llaves = &nodo->llaves_arbol_verga_nodo;
	hijos = &nodo->hijos_arbol_verga_nodo;

	if (datos_llave->posicion_arbol_verga_datos_llave) {
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
	(*llaves)[datos_llave->posicion_arbol_verga_datos_llave] =
			datos_llave->llave_arbol_verga_datos_llave;

	caca_log_debug("llave %p insertada en %u",
			datos_llave->llave_arbol_verga_datos_llave,
			datos_llave->posicion_arbol_verga_datos_llave);

	for (int i = nodo->llaves_cnt_arbol_verga_nodo + 1;
			i > datos_llave->posicion_arbol_verga_datos_llave + offset_hijo;
			i--) {
		(*hijos)[i] = (*hijos)[i - 1];
	}

	(*hijos)[datos_llave->posicion_arbol_verga_datos_llave + offset_hijo] =
			nuevo_hijo;

	nodo->llaves_cnt_arbol_verga_nodo++;
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

static inline void arbol_verga_rota_izquierda(arbol_verga_ctx *ctx,
		arbol_verga_nodo *hijo_izq, arbol_verga_nodo *padre,
		arbol_verga_nodo *hijo_der, arbol_verga_datos_llave *datos_llave) {
	arbol_verga_nodo *hijo_de_llave_en_padre = NULL;

	caca_log_debug("insertando en ijo izq");
	arbol_verga_inserta_llave_datos_llave(ctx, hijo_izq,
			&(arbol_verga_datos_llave ) { .llave_arbol_verga_datos_llave =
							datos_llave->llave_arbol_verga_datos_llave,
							.posicion_arbol_verga_datos_llave =
									hijo_izq->llaves_cnt_arbol_verga_nodo },
			arbol_verga_obten_primer_hijo(hijo_der));

	if (datos_llave->posicion_arbol_verga_datos_llave) {
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

	arbol_verga_inserta_llave_datos_llave(ctx, hijo_der,
			&(arbol_verga_datos_llave ) { .llave_arbol_verga_datos_llave =
							datos_llave->llave_arbol_verga_datos_llave,
							.posicion_arbol_verga_datos_llave = 0 },
			arbol_verga_obten_ultimo_hijo(hijo_izq));

	if (datos_llave->posicion_arbol_verga_datos_llave) {
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
		if (arbol_verga_obten_llave_en_pos(nodo,idx) >= llave) {
			if (arbol_verga_obten_llave_en_pos(nodo,idx) == llave) {
				encontrada = verdadero;
				break;
			}
		}
	}

	assert_timeout(idx < nodo->llaves_cnt_arbol_verga_nodo);

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

#endif

#ifndef INCLUIDO_PRUEBA
int main(void) {
	puts("he corrido con algo de suerte"); /* prints he corrido con algo de suerte */
	return EXIT_SUCCESS;
}
#endif
