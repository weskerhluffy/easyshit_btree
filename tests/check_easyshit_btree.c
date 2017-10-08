#define INCLUIDO_PRUEBA
#include "../src/easyshit_btree.c"
#include "/Users/ernesto/programas/check/include/check.h"

int cagada_compara_entero(void *pa, void *pb) {
	int a = pa;
	int b = pb;

	return a - b;
}
arbol_verga_ctx *ctx = NULL;

void setup() {
	ctx = arbol_verga_init(cagada_compara_entero);
	caca_log_debug("se creo el arbol de mierda");
}

void teardown() {
	arbol_verga_fini(ctx);
	caca_log_debug("alv el arbol");
}

START_TEST( test_arbol_verga_init)
	{
		caca_log_debug("Una puta mierda");
		ck_assert_msg(ctx, "no se construyo la mierda");
	}END_TEST

void crea_nodo() {
	arbol_verga_nodo *nodo = NULL;
	nodo = arbol_verga_alloca_nodo(ctx);

	arbol_verga_pon_llave_en_pos(nodo, 0, 11);
	arbol_verga_pon_llave_en_pos(nodo, 1, 21);
	arbol_verga_pon_llave_en_pos(nodo, 2, 31);
	arbol_verga_pon_llave_en_pos(nodo, 3, 41);

	arbol_verga_pon_hijo_en_pos(nodo, 0, 10);
	arbol_verga_pon_hijo_en_pos(nodo, 1, 20);
	arbol_verga_pon_hijo_en_pos(nodo, 2, 30);
	arbol_verga_pon_hijo_en_pos(nodo, 3, 40);
	arbol_verga_pon_hijo_en_pos(nodo, 4, 50);
	nodo->llaves_cnt_arbol_verga_nodo = 4;

	ctx->raiz_arbol_verga_ctx = nodo;
	ck_assert_msg(nodo, "no se construyo el puto nodo");
}

void nada() {
}

START_TEST( test_arbol_verga_borra_llave_inicial)
	{
		arbol_verga_nodo *nodo = NULL;
		arbol_verga_nodo *hijo_borrado = NULL;
		arbol_verga_nodo *hijo_borrado_real = NULL;
		bool primer_hijo_correcto = falso;
		bool primer_llave_correcta = falso;

		nodo = ctx->raiz_arbol_verga_ctx;
		caca_log_debug("q verga %p", nodo);
		hijo_borrado = arbol_verga_obten_primer_hijo(nodo);
		hijo_borrado_real = arbol_verga_borra_llave_en_nodo(ctx, nodo, 11,
				falso);
		caca_log_debug("boorado primer ijo");
		primer_hijo_correcto = arbol_verga_obten_primer_hijo(nodo) == 20;
		primer_llave_correcta = nodo->llaves_arbol_verga_nodo[0] == 21;

		ck_assert_msg(
				primer_hijo_correcto && primer_llave_correcta
						&& hijo_borrado == hijo_borrado_real,
				"la primer llave %u, l primer ijo %u",
				nodo->llaves_arbol_verga_nodo[0],
				arbol_verga_obten_primer_hijo(nodo));
	}END_TEST

START_TEST( test_arbol_verga_borra_llave_final)
	{
		arbol_verga_nodo *nodo = NULL;
		arbol_verga_nodo *hijo_borrado = NULL;
		arbol_verga_nodo *hijo_borrado_real = NULL;
		bool ultimo_hijo_correcto = falso;
		bool ultimo_llave_correcta = falso;

		nodo = ctx->raiz_arbol_verga_ctx;
		caca_log_debug("q verga %p", nodo);
		hijo_borrado = arbol_verga_obten_ultimo_hijo(nodo);
		hijo_borrado_real = arbol_verga_borra_llave_en_nodo(ctx, nodo, 41,
				verdadero);
		caca_log_debug("boorado ultimo ijo");
		ultimo_hijo_correcto = arbol_verga_obten_ultimo_hijo(nodo) == 40;
		ultimo_llave_correcta =
				nodo->llaves_arbol_verga_nodo[nodo->llaves_cnt_arbol_verga_nodo
						- 1] == 31;

		ck_assert_msg(
				ultimo_hijo_correcto && ultimo_llave_correcta
						&& hijo_borrado == hijo_borrado_real,
				"la ultimo llave %u, l ultimo ijo %u",
				nodo->llaves_arbol_verga_nodo[nodo->llaves_cnt_arbol_verga_nodo
						- 1], arbol_verga_obten_ultimo_hijo(nodo));
	}END_TEST

START_TEST( test_arbol_verga_borra_llave_medio)
	{
		arbol_verga_nodo *nodo = NULL;
		arbol_verga_nodo *hijo_borrado = NULL;
		arbol_verga_nodo *hijo_borrado_real = NULL;
		bool medio_hijo_correcto = falso;
		bool medio_llave_correcta = falso;

		nodo = ctx->raiz_arbol_verga_ctx;
		caca_log_debug("q verga %p", nodo);
		hijo_borrado = arbol_verga_obten_hijo_der(nodo, 1);
		hijo_borrado_real = arbol_verga_borra_llave_en_nodo(ctx, nodo, 21,
				verdadero);
		caca_log_debug("boorado medio ijo el borrado sperado %p el real %p",
				hijo_borrado, hijo_borrado_real);
		medio_hijo_correcto = arbol_verga_obten_hijo_der(nodo,1) == 40;
		medio_llave_correcta =
		arbol_verga_obten_llave_en_pos(nodo,1) == 31;

		ck_assert_msg(
				medio_hijo_correcto && medio_llave_correcta
						&& hijo_borrado == hijo_borrado_real,
				"la medio llave %u, l medio ijo %u",
				arbol_verga_obten_llave_en_pos(nodo,1),
				arbol_verga_obten_hijo_der(nodo,1));
	}END_TEST

void crea_tercia_de_nodos() {
	arbol_verga_nodo *padre = NULL;
	arbol_verga_nodo *hijos[5];
	padre = arbol_verga_alloca_nodo(ctx);

	natural cont_llaves = 10;

	for (int i = 0; i < 5; i++) {
		hijos[i] = arbol_verga_alloca_nodo(ctx);
		for (int j = 0; j < 4; j++) {
			arbol_verga_pon_llave_en_pos(hijos[i], j, cont_llaves);
			arbol_verga_pon_hijo_en_pos(hijos[i], j, cont_llaves * 10);
			cont_llaves += 10;
		}
		arbol_verga_pon_hijo_en_pos(hijos[i], 4, cont_llaves * 10);
		cont_llaves += 10;
		hijos[i]->llaves_cnt_arbol_verga_nodo = 4;
	}

	arbol_verga_pon_hijo_en_pos(padre, 0, hijos[0]);
	for (int i = 1; i < 5; i++) {
		arbol_verga_pon_llave_en_pos(padre, i - 1,
				arbol_verga_obten_llave_en_pos(hijos[i],0)-5);
		arbol_verga_pon_hijo_en_pos(padre, i, hijos[i]);
	}
	padre->llaves_cnt_arbol_verga_nodo = 4;

	ctx->raiz_arbol_verga_ctx = padre;
	ck_assert_msg(padre, "no se construyo el puto nodo");
}

START_TEST( test_arbol_verga_rotacion_izq_primer)
	{
		arbol_verga_nodo *padre;
		arbol_verga_nodo *hijo_izq;
		arbol_verga_nodo *hijo_der;

		natural pos_llave = 0;
		padre = ctx->raiz_arbol_verga_ctx;
		hijo_izq = arbol_verga_obten_hijo_izq(padre, pos_llave);
		hijo_der = arbol_verga_obten_hijo_der(padre, pos_llave);

		arbol_verga_datos_llave *datos_llave = &(arbol_verga_datos_llave ) {
						.llave_arbol_verga_datos_llave =
								arbol_verga_obten_llave_en_pos(padre,
										pos_llave),
						.posicion_arbol_verga_datos_llave = pos_llave };

		void *ultima_llave_hijo_izq_esperada = NULL;
		arbol_verga_nodo *ultimo_hijo_hijo_izq_esperado = NULL;
		void *llave_padre_esperada = NULL;
		void *primer_llave_hijo_der_esperada = NULL;
		arbol_verga_nodo *primer_hijo_hijo_der_esperado = NULL;

		void *ultima_llave_hijo_izq = NULL;
		arbol_verga_nodo *ultimo_hijo_hijo_izq = NULL;
		void *llave_padre = NULL;
		void *primer_llave_hijo_der = NULL;
		arbol_verga_nodo *primer_hijo_hijo_der = NULL;

		bool hijo_izq_bien;
		bool hijo_der_bien;
		bool padre_bien;

		ultima_llave_hijo_izq_esperada =
				datos_llave->llave_arbol_verga_datos_llave;
		ultimo_hijo_hijo_izq_esperado = arbol_verga_obten_primer_hijo(hijo_der);

		llave_padre_esperada = arbol_verga_obten_primer_llave(hijo_der);

		primer_llave_hijo_der_esperada = arbol_verga_obten_llave_en_pos(
				hijo_der, 1);
		primer_hijo_hijo_der_esperado = arbol_verga_obten_hijo_der(hijo_der, 1);

		// ACA sta lo meor bueno
		arbol_verga_rota_izquierda(ctx, hijo_izq, padre, hijo_der, datos_llave);

		ultima_llave_hijo_izq = arbol_verga_obten_ultima_llave(hijo_izq);
		ultimo_hijo_hijo_izq = arbol_verga_obten_ultimo_hijo(hijo_izq);

		llave_padre = arbol_verga_obten_primer_llave(hijo_der);

		primer_llave_hijo_der = arbol_verga_obten_primer_llave(hijo_der);
		primer_hijo_hijo_der = arbol_verga_obten_primer_hijo(hijo_der);

		hijo_izq_bien = ultima_llave_hijo_izq == ultima_llave_hijo_izq_esperada
				&& ultimo_hijo_hijo_izq_esperado == ultimo_hijo_hijo_izq;

		caca_log_debug("ijo izq llave esp %p real %p, hijo esp %p real %p",
				ultima_llave_hijo_izq_esperada, ultima_llave_hijo_izq,
				ultimo_hijo_hijo_izq_esperado, ultimo_hijo_hijo_izq);

		padre_bien = llave_padre == llave_padre_esperada;

		caca_log_debug("llave padre %u", padre_bien);

		hijo_der_bien = primer_hijo_hijo_der = primer_hijo_hijo_der_esperado
				&& primer_llave_hijo_der == primer_llave_hijo_der_esperada;

		caca_log_debug("ijo der %u", hijo_der_bien);

		ck_assert_msg(hijo_izq_bien && padre && hijo_der_bien,
				"la concha de la lora");
	}END_TEST

START_TEST( test_arbol_verga_rotacion_izq_final)
	{
		arbol_verga_nodo *padre;
		arbol_verga_nodo *hijo_izq;
		arbol_verga_nodo *hijo_der;

		padre = ctx->raiz_arbol_verga_ctx;
		natural pos_llave = padre->llaves_cnt_arbol_verga_nodo - 1;
		hijo_izq = arbol_verga_obten_hijo_izq(padre, pos_llave);
		hijo_der = arbol_verga_obten_hijo_der(padre, pos_llave);
		caca_log_debug("obtenidos ijos");

		arbol_verga_datos_llave *datos_llave = &(arbol_verga_datos_llave ) {
						.llave_arbol_verga_datos_llave =
								arbol_verga_obten_llave_en_pos(padre,
										pos_llave),
						.posicion_arbol_verga_datos_llave = pos_llave };

		void *ultima_llave_hijo_izq_esperada = NULL;
		arbol_verga_nodo *ultimo_hijo_hijo_izq_esperado = NULL;
		void *llave_padre_esperada = NULL;
		void *primer_llave_hijo_der_esperada = NULL;
		arbol_verga_nodo *primer_hijo_hijo_der_esperado = NULL;

		void *ultima_llave_hijo_izq = NULL;
		arbol_verga_nodo *ultimo_hijo_hijo_izq = NULL;
		void *llave_padre = NULL;
		void *primer_llave_hijo_der = NULL;
		arbol_verga_nodo *primer_hijo_hijo_der = NULL;

		bool hijo_izq_bien;
		bool hijo_der_bien;
		bool padre_bien;

		ultima_llave_hijo_izq_esperada =
				datos_llave->llave_arbol_verga_datos_llave;
		ultimo_hijo_hijo_izq_esperado = arbol_verga_obten_primer_hijo(hijo_der);

		llave_padre_esperada = arbol_verga_obten_primer_llave(hijo_der);

		primer_llave_hijo_der_esperada = arbol_verga_obten_llave_en_pos(
				hijo_der, 1);
		primer_hijo_hijo_der_esperado = arbol_verga_obten_hijo_der(hijo_der, 1);

		// ACA sta lo meor bueno
		arbol_verga_rota_izquierda(ctx, hijo_izq, padre, hijo_der, datos_llave);

		ultima_llave_hijo_izq = arbol_verga_obten_ultima_llave(hijo_izq);
		ultimo_hijo_hijo_izq = arbol_verga_obten_ultimo_hijo(hijo_izq);

		llave_padre = arbol_verga_obten_primer_llave(hijo_der);

		primer_llave_hijo_der = arbol_verga_obten_primer_llave(hijo_der);
		primer_hijo_hijo_der = arbol_verga_obten_primer_hijo(hijo_der);

		hijo_izq_bien = ultima_llave_hijo_izq == ultima_llave_hijo_izq_esperada
				&& ultimo_hijo_hijo_izq_esperado == ultimo_hijo_hijo_izq;

		caca_log_debug("ijo izq llave esp %p real %p, hijo esp %p real %p",
				ultima_llave_hijo_izq_esperada, ultima_llave_hijo_izq,
				ultimo_hijo_hijo_izq_esperado, ultimo_hijo_hijo_izq);

		padre_bien = llave_padre == llave_padre_esperada;

		caca_log_debug("llave padre %u", padre_bien);

		hijo_der_bien = primer_hijo_hijo_der = primer_hijo_hijo_der_esperado
				&& primer_llave_hijo_der == primer_llave_hijo_der_esperada;

		caca_log_debug("ijo der %u", hijo_der_bien);

		ck_assert_msg(hijo_izq_bien && padre && hijo_der_bien,
				"la concha de la lora");
	}END_TEST

START_TEST( test_arbol_verga_rotacion_der_primer)
	{
		arbol_verga_nodo *padre;
		arbol_verga_nodo *hijo_izq;
		arbol_verga_nodo *hijo_der;

		caca_log_debug("rotande der prime");
		natural pos_llave = 0;
		padre = ctx->raiz_arbol_verga_ctx;
		hijo_izq = arbol_verga_obten_hijo_izq(padre, pos_llave);
		hijo_der = arbol_verga_obten_hijo_der(padre, pos_llave);

		arbol_verga_datos_llave *datos_llave = &(arbol_verga_datos_llave ) {
						.llave_arbol_verga_datos_llave =
								arbol_verga_obten_llave_en_pos(padre,
										pos_llave),
						.posicion_arbol_verga_datos_llave = pos_llave };

		void *primer_llave_hijo_der_esperada = NULL;
		arbol_verga_nodo *primer_hijo_hijo_der_esperado = NULL;
		void *llave_padre_esperada = NULL;
		void *ultima_llave_hijo_izq_esperada = NULL;
		arbol_verga_nodo *ultimo_hijo_hijo_izq_esperado = NULL;

		void *primer_llave_hijo_der = NULL;
		arbol_verga_nodo *primer_hijo_hijo_der = NULL;
		void *llave_padre = NULL;
		void *ultima_llave_hijo_izq = NULL;
		arbol_verga_nodo *ultimo_hijo_hijo_izq = NULL;

		bool hijo_izq_bien;
		bool hijo_der_bien;
		bool padre_bien;

		primer_llave_hijo_der_esperada =
				datos_llave->llave_arbol_verga_datos_llave;
		primer_hijo_hijo_der_esperado = arbol_verga_obten_ultimo_hijo(hijo_izq);

		llave_padre_esperada = arbol_verga_obten_primer_llave(hijo_der);

		ultima_llave_hijo_izq_esperada = arbol_verga_obten_llave_en_pos(
				hijo_izq, hijo_izq->llaves_cnt_arbol_verga_nodo - 2);
		ultimo_hijo_hijo_izq_esperado = arbol_verga_obten_hijo_der(hijo_izq,
				hijo_izq->llaves_cnt_arbol_verga_nodo - 2);

		// ACA sta lo meor bueno
		arbol_verga_rota_derecha(ctx, hijo_izq, padre, hijo_der, datos_llave);

		ultima_llave_hijo_izq = arbol_verga_obten_ultima_llave(hijo_izq);
		ultimo_hijo_hijo_izq = arbol_verga_obten_ultimo_hijo(hijo_izq);

		llave_padre = arbol_verga_obten_primer_llave(hijo_der);

		primer_llave_hijo_der = arbol_verga_obten_primer_llave(hijo_der);
		primer_hijo_hijo_der = arbol_verga_obten_primer_hijo(hijo_der);

		hijo_izq_bien = ultima_llave_hijo_izq == ultima_llave_hijo_izq_esperada
				&& ultimo_hijo_hijo_izq_esperado == ultimo_hijo_hijo_izq;

		caca_log_debug("ijo izq llave esp %p real %p, hijo esp %p real %p",
				ultima_llave_hijo_izq_esperada, ultima_llave_hijo_izq,
				ultimo_hijo_hijo_izq_esperado, ultimo_hijo_hijo_izq);

		padre_bien = llave_padre == llave_padre_esperada;

		caca_log_debug("llave padre %u", padre_bien);

		hijo_der_bien = primer_hijo_hijo_der = primer_hijo_hijo_der_esperado
				&& primer_llave_hijo_der == primer_llave_hijo_der_esperada;

		caca_log_debug("ijo der %u", hijo_der_bien);

		ck_assert_msg(hijo_izq_bien && padre && hijo_der_bien,
				"la concha de la lora");
	}END_TEST

START_TEST( test_arbol_verga_rotacion_der_final)
	{
		arbol_verga_nodo *padre;
		arbol_verga_nodo *hijo_izq;
		arbol_verga_nodo *hijo_der;

		caca_log_debug("rotande der prime");
		padre = ctx->raiz_arbol_verga_ctx;
		natural pos_llave = padre->llaves_cnt_arbol_verga_nodo - 1;
		hijo_izq = arbol_verga_obten_hijo_izq(padre, pos_llave);
		hijo_der = arbol_verga_obten_hijo_der(padre, pos_llave);

		arbol_verga_datos_llave *datos_llave = &(arbol_verga_datos_llave ) {
						.llave_arbol_verga_datos_llave =
								arbol_verga_obten_llave_en_pos(padre,
										pos_llave),
						.posicion_arbol_verga_datos_llave = pos_llave };

		void *primer_llave_hijo_der_esperada = NULL;
		arbol_verga_nodo *primer_hijo_hijo_der_esperado = NULL;
		void *llave_padre_esperada = NULL;
		void *ultima_llave_hijo_izq_esperada = NULL;
		arbol_verga_nodo *ultimo_hijo_hijo_izq_esperado = NULL;

		void *primer_llave_hijo_der = NULL;
		arbol_verga_nodo *primer_hijo_hijo_der = NULL;
		void *llave_padre = NULL;
		void *ultima_llave_hijo_izq = NULL;
		arbol_verga_nodo *ultimo_hijo_hijo_izq = NULL;

		bool hijo_izq_bien;
		bool hijo_der_bien;
		bool padre_bien;

		primer_llave_hijo_der_esperada =
				datos_llave->llave_arbol_verga_datos_llave;
		primer_hijo_hijo_der_esperado = arbol_verga_obten_ultimo_hijo(hijo_izq);

		llave_padre_esperada = arbol_verga_obten_primer_llave(hijo_der);

		ultima_llave_hijo_izq_esperada = arbol_verga_obten_llave_en_pos(
				hijo_izq, hijo_izq->llaves_cnt_arbol_verga_nodo - 2);
		ultimo_hijo_hijo_izq_esperado = arbol_verga_obten_hijo_der(hijo_izq,
				hijo_izq->llaves_cnt_arbol_verga_nodo - 2);

		// ACA sta lo meor bueno
		arbol_verga_rota_derecha(ctx, hijo_izq, padre, hijo_der, datos_llave);

		ultima_llave_hijo_izq = arbol_verga_obten_ultima_llave(hijo_izq);
		ultimo_hijo_hijo_izq = arbol_verga_obten_ultimo_hijo(hijo_izq);

		llave_padre = arbol_verga_obten_primer_llave(hijo_der);

		primer_llave_hijo_der = arbol_verga_obten_primer_llave(hijo_der);
		primer_hijo_hijo_der = arbol_verga_obten_primer_hijo(hijo_der);

		hijo_izq_bien = ultima_llave_hijo_izq == ultima_llave_hijo_izq_esperada
				&& ultimo_hijo_hijo_izq_esperado == ultimo_hijo_hijo_izq;

		caca_log_debug("ijo izq llave esp %p real %p, hijo esp %p real %p",
				ultima_llave_hijo_izq_esperada, ultima_llave_hijo_izq,
				ultimo_hijo_hijo_izq_esperado, ultimo_hijo_hijo_izq);

		padre_bien = llave_padre == llave_padre_esperada;

		caca_log_debug("llave padre %u", padre_bien);

		hijo_der_bien = primer_hijo_hijo_der = primer_hijo_hijo_der_esperado
				&& primer_llave_hijo_der == primer_llave_hijo_der_esperada;

		caca_log_debug("ijo der %u", hijo_der_bien);

		ck_assert_msg(hijo_izq_bien && padre && hijo_der_bien,
				"la concha de la lora");
	}END_TEST

START_TEST( test_arbol_verga_mergear_primera_llave)
	{
		arbol_verga_nodo *padre;
		arbol_verga_nodo *hijo_izq;
		arbol_verga_nodo *hijo_der;

		caca_log_debug("mergeando");
		padre = ctx->raiz_arbol_verga_ctx;
		natural pos_llave = 0;
		hijo_izq = arbol_verga_obten_hijo_izq(padre, pos_llave);
		hijo_der = arbol_verga_obten_hijo_der(padre, pos_llave);

		arbol_verga_datos_llave *datos_llave = &(arbol_verga_datos_llave ) {
						.llave_arbol_verga_datos_llave =
								arbol_verga_obten_llave_en_pos(padre,
										pos_llave),
						.posicion_arbol_verga_datos_llave = pos_llave };

		natural pos_a_borrar = 2;
		arbol_verga_borra_llave_datos_llave(ctx, hijo_izq,
				&(arbol_verga_datos_llave ) {
								.llave_arbol_verga_datos_llave =
										arbol_verga_obten_llave_en_pos(hijo_izq,
												pos_a_borrar),
								.posicion_arbol_verga_datos_llave = pos_a_borrar },
				verdadero);

		pos_a_borrar = arbol_verga_obten_ultima_pos_llave(hijo_izq);
		arbol_verga_borra_llave_datos_llave(ctx, hijo_izq,
				&(arbol_verga_datos_llave ) {
								.llave_arbol_verga_datos_llave =
										arbol_verga_obten_llave_en_pos(hijo_izq,
												pos_a_borrar),
								.posicion_arbol_verga_datos_llave = pos_a_borrar },
				verdadero);

		pos_a_borrar = 2;
		arbol_verga_borra_llave_datos_llave(ctx, hijo_der,
				&(arbol_verga_datos_llave ) {
								.llave_arbol_verga_datos_llave =
										arbol_verga_obten_llave_en_pos(hijo_der,
												pos_a_borrar),
								.posicion_arbol_verga_datos_llave = pos_a_borrar },
				verdadero);

		pos_a_borrar = 0;
		arbol_verga_borra_llave_datos_llave(ctx, hijo_der,
				&(arbol_verga_datos_llave ) {
								.llave_arbol_verga_datos_llave =
										arbol_verga_obten_llave_en_pos(hijo_der,
												pos_a_borrar),
								.posicion_arbol_verga_datos_llave = pos_a_borrar },
				falso);

		arbol_verga_nodo *hijo_der_orig = arbol_verga_alloca_nodo(ctx);
		arbol_verga_nodo *hijo_izq_orig = arbol_verga_alloca_nodo(ctx);

		*hijo_der_orig = *hijo_der;
		*hijo_izq_orig = *hijo_izq;

		arbol_verga_mergea_nodos(ctx, hijo_izq, padre, hijo_der, datos_llave);

		bool llave_media_bien = verdadero;
		bool llaves_hijo_izq_bien = verdadero;
		bool llaves_hijo_der_bien = verdadero;
		int i = 0;

		for (i = 0; i <= arbol_verga_obten_ultima_pos_llave(hijo_izq_orig);
				i++) {
			llaves_hijo_izq_bien = llaves_hijo_izq_bien
					&& (arbol_verga_obten_llave_en_pos(hijo_izq, i)
							== arbol_verga_obten_llave_en_pos(hijo_izq_orig, i)
							&& arbol_verga_obten_hijo_izq(hijo_izq, i)
									== arbol_verga_obten_hijo_izq(hijo_izq, i));
			caca_log_debug("hijo izq en idx %u %u", i, llaves_hijo_izq_bien);
		}

		llaves_hijo_izq_bien = llaves_hijo_izq_bien
				&& (arbol_verga_obten_hijo_izq(hijo_izq, i)
						== arbol_verga_obten_hijo_izq(hijo_izq, i));
		caca_log_debug("hijo izq en idx %u %u", i, llaves_hijo_izq_bien);

		llave_media_bien = datos_llave->llave_arbol_verga_datos_llave
				== arbol_verga_obten_llave_en_pos(hijo_izq, i);

		caca_log_debug("llave media %u", llave_media_bien);

		i++;

		int j = 0;

		for (j = 0; j <= arbol_verga_obten_ultima_pos_llave(hijo_der_orig);
				j++) {
			llaves_hijo_der_bien = llaves_hijo_der_bien
					&& (arbol_verga_obten_llave_en_pos(hijo_izq, i)
							== arbol_verga_obten_llave_en_pos(hijo_der_orig, j)
							&& arbol_verga_obten_hijo_izq(hijo_izq, i)
									== arbol_verga_obten_hijo_izq(hijo_der_orig,
											j));
			caca_log_debug("hijo der en idx %u %u", i, llaves_hijo_der_bien);

			i++;
		}
		assert_timeout(i==arbol_verga_obten_ultima_pos_llave(hijo_izq)+1);

		llaves_hijo_der_bien = llaves_hijo_der_bien
				&& (arbol_verga_obten_hijo_izq(hijo_izq, i)
						== arbol_verga_obten_hijo_izq(hijo_der_orig, j));
		caca_log_debug("hijo der en idx %u %u", i, llaves_hijo_der_bien);

		arbol_verga_datos_llave *datos_llave_tmp = &(arbol_verga_datos_llave ) {
						0 };

		bool llave_enc = arbol_verga_encuentra_llave_en_nodo(ctx, padre,
				datos_llave->llave_arbol_verga_datos_llave, datos_llave_tmp);

		ck_assert_msg(
				llaves_hijo_izq_bien && llave_media_bien
						&& llaves_hijo_der_bien, "caca");

	}END_TEST

START_TEST( test_arbol_verga_mergear_ultima_llave)
	{
		arbol_verga_nodo *padre;
		arbol_verga_nodo *hijo_izq;
		arbol_verga_nodo *hijo_der;

		caca_log_debug("mergeando");
		padre = ctx->raiz_arbol_verga_ctx;
		natural pos_llave = arbol_verga_obten_ultima_pos_llave(padre);
		hijo_izq = arbol_verga_obten_hijo_izq(padre, pos_llave);
		hijo_der = arbol_verga_obten_hijo_der(padre, pos_llave);

		arbol_verga_datos_llave *datos_llave = &(arbol_verga_datos_llave ) {
						.llave_arbol_verga_datos_llave =
								arbol_verga_obten_llave_en_pos(padre,
										pos_llave),
						.posicion_arbol_verga_datos_llave = pos_llave };

		natural pos_a_borrar = 2;
		arbol_verga_borra_llave_datos_llave(ctx, hijo_izq,
				&(arbol_verga_datos_llave ) {
								.llave_arbol_verga_datos_llave =
										arbol_verga_obten_llave_en_pos(hijo_izq,
												pos_a_borrar),
								.posicion_arbol_verga_datos_llave = pos_a_borrar },
				verdadero);

		pos_a_borrar = arbol_verga_obten_ultima_pos_llave(hijo_izq);
		arbol_verga_borra_llave_datos_llave(ctx, hijo_izq,
				&(arbol_verga_datos_llave ) {
								.llave_arbol_verga_datos_llave =
										arbol_verga_obten_llave_en_pos(hijo_izq,
												pos_a_borrar),
								.posicion_arbol_verga_datos_llave = pos_a_borrar },
				verdadero);

		pos_a_borrar = 2;
		arbol_verga_borra_llave_datos_llave(ctx, hijo_der,
				&(arbol_verga_datos_llave ) {
								.llave_arbol_verga_datos_llave =
										arbol_verga_obten_llave_en_pos(hijo_der,
												pos_a_borrar),
								.posicion_arbol_verga_datos_llave = pos_a_borrar },
				verdadero);

		pos_a_borrar = 0;
		arbol_verga_borra_llave_datos_llave(ctx, hijo_der,
				&(arbol_verga_datos_llave ) {
								.llave_arbol_verga_datos_llave =
										arbol_verga_obten_llave_en_pos(hijo_der,
												pos_a_borrar),
								.posicion_arbol_verga_datos_llave = pos_a_borrar },
				falso);

		arbol_verga_nodo *hijo_der_orig = arbol_verga_alloca_nodo(ctx);
		arbol_verga_nodo *hijo_izq_orig = arbol_verga_alloca_nodo(ctx);

		*hijo_der_orig = *hijo_der;
		*hijo_izq_orig = *hijo_izq;

		arbol_verga_mergea_nodos(ctx, hijo_izq, padre, hijo_der, datos_llave);

		bool llave_media_bien = verdadero;
		bool llaves_hijo_izq_bien = verdadero;
		bool llaves_hijo_der_bien = verdadero;
		int i = 0;

		for (i = 0; i <= arbol_verga_obten_ultima_pos_llave(hijo_izq_orig);
				i++) {
			llaves_hijo_izq_bien = llaves_hijo_izq_bien
					&& (arbol_verga_obten_llave_en_pos(hijo_izq, i)
							== arbol_verga_obten_llave_en_pos(hijo_izq_orig, i)
							&& arbol_verga_obten_hijo_izq(hijo_izq, i)
									== arbol_verga_obten_hijo_izq(hijo_izq, i));
			caca_log_debug("hijo izq en idx %u %u", i, llaves_hijo_izq_bien);
		}

		llaves_hijo_izq_bien = llaves_hijo_izq_bien
				&& (arbol_verga_obten_hijo_izq(hijo_izq, i)
						== arbol_verga_obten_hijo_izq(hijo_izq, i));
		caca_log_debug("hijo izq en idx %u %u", i, llaves_hijo_izq_bien);

		llave_media_bien = datos_llave->llave_arbol_verga_datos_llave
				== arbol_verga_obten_llave_en_pos(hijo_izq, i);

		caca_log_debug("llave media %u", llave_media_bien);

		i++;

		int j = 0;

		for (j = 0; j <= arbol_verga_obten_ultima_pos_llave(hijo_der_orig);
				j++) {
			llaves_hijo_der_bien = llaves_hijo_der_bien
					&& (arbol_verga_obten_llave_en_pos(hijo_izq, i)
							== arbol_verga_obten_llave_en_pos(hijo_der_orig, j)
							&& arbol_verga_obten_hijo_izq(hijo_izq, i)
									== arbol_verga_obten_hijo_izq(hijo_der_orig,
											j));
			caca_log_debug("hijo der en idx %u %u", i, llaves_hijo_der_bien);

			i++;
		}
		assert_timeout(i==arbol_verga_obten_ultima_pos_llave(hijo_izq)+1);

		llaves_hijo_der_bien = llaves_hijo_der_bien
				&& (arbol_verga_obten_hijo_izq(hijo_izq, i)
						== arbol_verga_obten_hijo_izq(hijo_der_orig, j));
		caca_log_debug("hijo der en idx %u %u", i, llaves_hijo_der_bien);

		arbol_verga_datos_llave *datos_llave_tmp = &(arbol_verga_datos_llave ) {
						0 };

		bool llave_enc = arbol_verga_encuentra_llave_en_nodo(ctx, padre,
				datos_llave->llave_arbol_verga_datos_llave, datos_llave_tmp);

		ck_assert_msg(
				llaves_hijo_izq_bien && llave_media_bien
						&& llaves_hijo_der_bien, "caca");

	}END_TEST

START_TEST( test_arbol_verga_mergea_y_promueve_primero)
	{
		natural pos_split = 0;
		natural pos_media_hijo_split = ARBOL_VERGA_POSICION_MEDIA_LLAVES;

		caca_log_debug("separando caca en pos %u, la pos media es %u",
				pos_split, pos_media_hijo_split);

		arbol_verga_nodo *nodo_split = NULL;
		arbol_verga_nodo *hijo_izq = NULL;
		arbol_verga_nodo *hijo_der = NULL;

		nodo_split = arbol_verga_obten_hijo_en_pos(ctx->raiz_arbol_verga_ctx,
				pos_split);

		arbol_verga_inserta_llave_datos_llave(ctx, nodo_split,
				arbol_verga_datos_genera_datos_llave_local(
						arbol_verga_obten_ultima_llave(nodo_split)+1,
						nodo_split->llaves_cnt_arbol_verga_nodo),
				arbol_verga_obten_ultimo_hijo(nodo_split) + 1, verdadero);

		arbol_verga_nodo *hijo_izq_ultima_llave_esp = NULL;
		void *hijo_izq_ultimo_hijo_esp = NULL;
		arbol_verga_nodo *padre_llave_promovida_esp = NULL;
		arbol_verga_nodo *hijo_der_primer_llave_esp = NULL;
		void *hijo_der_primer_hijo_esp = NULL;

		arbol_verga_nodo *hijo_izq_ultima_llave = NULL;
		void *hijo_izq_ultimo_hijo = NULL;
		arbol_verga_nodo *padre_llave_promovida = NULL;
		arbol_verga_nodo *hijo_der_primer_llave = NULL;
		void *hijo_der_primer_hijo = NULL;

		hijo_izq_ultima_llave_esp = arbol_verga_obten_llave_en_pos(nodo_split,
				pos_media_hijo_split - 1);
		hijo_izq_ultimo_hijo_esp = arbol_verga_obten_hijo_der(nodo_split,
				pos_media_hijo_split - 1);

		padre_llave_promovida_esp = arbol_verga_obten_llave_en_pos(nodo_split,
				pos_media_hijo_split);

		hijo_der_primer_llave_esp = arbol_verga_obten_llave_en_pos(nodo_split,
				pos_media_hijo_split + 1);
		hijo_der_primer_hijo_esp = arbol_verga_obten_hijo_izq(nodo_split,
				pos_media_hijo_split + 1);

		arbol_verga_separa_y_promueve(ctx, ctx->raiz_arbol_verga_ctx,
				pos_split);

		hijo_izq = arbol_verga_obten_hijo_izq(ctx->raiz_arbol_verga_ctx,
				pos_split);
		hijo_der = arbol_verga_obten_hijo_der(ctx->raiz_arbol_verga_ctx,
				pos_split);

		hijo_izq_ultima_llave = arbol_verga_obten_ultima_llave(hijo_izq);
		hijo_izq_ultimo_hijo = arbol_verga_obten_ultimo_hijo(hijo_izq);
		ck_assert_msg(
				hijo_izq_ultima_llave == hijo_izq_ultima_llave_esp
						&& hijo_izq_ultimo_hijo == hijo_izq_ultimo_hijo_esp,
				"hijo izq faio, llave %p, esp %p, hijo %p, esp %p",
				hijo_izq_ultima_llave, hijo_izq_ultima_llave_esp,
				hijo_izq_ultimo_hijo, hijo_izq_ultimo_hijo_esp);

		padre_llave_promovida = arbol_verga_obten_llave_en_pos(
				ctx->raiz_arbol_verga_ctx, pos_split);
		ck_assert_msg(padre_llave_promovida == padre_llave_promovida_esp,
				"llave promovida faio %p esp %p", padre_llave_promovida,
				padre_llave_promovida_esp);

		hijo_der_primer_llave = arbol_verga_obten_primer_llave(hijo_der);
		hijo_der_primer_hijo = arbol_verga_obten_primer_hijo(hijo_der);
		ck_assert_msg(
				hijo_der_primer_llave == hijo_der_primer_llave_esp
						&& hijo_der_primer_hijo == hijo_der_primer_hijo_esp,
				"hijo der faio");

	}END_TEST

START_TEST( test_arbol_verga_mergea_y_promueve_ultimo)
	{
		natural pos_split = arbol_verga_obten_ultima_pos_llave(
				ctx->raiz_arbol_verga_ctx);
		natural pos_media_hijo_split = ARBOL_VERGA_POSICION_MEDIA_LLAVES;

		caca_log_debug("separando caca en pos %u, la pos media es %u",
				pos_split, pos_media_hijo_split);

		arbol_verga_nodo *nodo_split = NULL;
		arbol_verga_nodo *hijo_izq = NULL;
		arbol_verga_nodo *hijo_der = NULL;

		nodo_split = arbol_verga_obten_hijo_en_pos(ctx->raiz_arbol_verga_ctx,
				pos_split);

		arbol_verga_inserta_llave_datos_llave(ctx, nodo_split,
				arbol_verga_datos_genera_datos_llave_local(
						arbol_verga_obten_ultima_llave(nodo_split)+1,
						nodo_split->llaves_cnt_arbol_verga_nodo),
				arbol_verga_obten_ultimo_hijo(nodo_split) + 1, verdadero);

		arbol_verga_nodo *hijo_izq_ultima_llave_esp = NULL;
		void *hijo_izq_ultimo_hijo_esp = NULL;
		arbol_verga_nodo *padre_llave_promovida_esp = NULL;
		arbol_verga_nodo *hijo_der_primer_llave_esp = NULL;
		void *hijo_der_primer_hijo_esp = NULL;

		arbol_verga_nodo *hijo_izq_ultima_llave = NULL;
		void *hijo_izq_ultimo_hijo = NULL;
		arbol_verga_nodo *padre_llave_promovida = NULL;
		arbol_verga_nodo *hijo_der_primer_llave = NULL;
		void *hijo_der_primer_hijo = NULL;

		hijo_izq_ultima_llave_esp = arbol_verga_obten_llave_en_pos(nodo_split,
				pos_media_hijo_split - 1);
		hijo_izq_ultimo_hijo_esp = arbol_verga_obten_hijo_der(nodo_split,
				pos_media_hijo_split - 1);

		padre_llave_promovida_esp = arbol_verga_obten_llave_en_pos(nodo_split,
				pos_media_hijo_split);

		hijo_der_primer_llave_esp = arbol_verga_obten_llave_en_pos(nodo_split,
				pos_media_hijo_split + 1);
		hijo_der_primer_hijo_esp = arbol_verga_obten_hijo_izq(nodo_split,
				pos_media_hijo_split + 1);

		arbol_verga_separa_y_promueve(ctx, ctx->raiz_arbol_verga_ctx,
				pos_split);

		hijo_izq = arbol_verga_obten_hijo_izq(ctx->raiz_arbol_verga_ctx,
				pos_split);
		hijo_der = arbol_verga_obten_hijo_der(ctx->raiz_arbol_verga_ctx,
				pos_split);

		hijo_izq_ultima_llave = arbol_verga_obten_ultima_llave(hijo_izq);
		hijo_izq_ultimo_hijo = arbol_verga_obten_ultimo_hijo(hijo_izq);
		ck_assert_msg(
				hijo_izq_ultima_llave == hijo_izq_ultima_llave_esp
						&& hijo_izq_ultimo_hijo == hijo_izq_ultimo_hijo_esp,
				"hijo izq faio, llave %p, esp %p, hijo %p, esp %p",
				hijo_izq_ultima_llave, hijo_izq_ultima_llave_esp,
				hijo_izq_ultimo_hijo, hijo_izq_ultimo_hijo_esp);

		padre_llave_promovida = arbol_verga_obten_llave_en_pos(
				ctx->raiz_arbol_verga_ctx, pos_split);
		ck_assert_msg(padre_llave_promovida == padre_llave_promovida_esp,
				"llave promovida faio %p esp %p", padre_llave_promovida,
				padre_llave_promovida_esp);

		hijo_der_primer_llave = arbol_verga_obten_primer_llave(hijo_der);
		hijo_der_primer_hijo = arbol_verga_obten_primer_hijo(hijo_der);
		ck_assert_msg(
				hijo_der_primer_llave == hijo_der_primer_llave_esp
						&& hijo_der_primer_hijo == hijo_der_primer_hijo_esp,
				"hijo der faio");

	}END_TEST

START_TEST( test_arbol_verga_mergea_y_promueve_medio)
	{
		natural pos_split = arbol_verga_obten_ultima_pos_llave(
				ctx->raiz_arbol_verga_ctx) / 2;
		natural pos_media_hijo_split = ARBOL_VERGA_POSICION_MEDIA_LLAVES;

		caca_log_debug("separando caca en pos %u, la pos media es %u",
				pos_split, pos_media_hijo_split);

		arbol_verga_nodo *nodo_split = NULL;
		arbol_verga_nodo *hijo_izq = NULL;
		arbol_verga_nodo *hijo_der = NULL;

		nodo_split = arbol_verga_obten_hijo_en_pos(ctx->raiz_arbol_verga_ctx,
				pos_split);

		arbol_verga_inserta_llave_datos_llave(ctx, nodo_split,
				arbol_verga_datos_genera_datos_llave_local(
						arbol_verga_obten_ultima_llave(nodo_split)+1,
						nodo_split->llaves_cnt_arbol_verga_nodo),
				arbol_verga_obten_ultimo_hijo(nodo_split) + 1, verdadero);

		arbol_verga_nodo *hijo_izq_ultima_llave_esp = NULL;
		void *hijo_izq_ultimo_hijo_esp = NULL;
		arbol_verga_nodo *padre_llave_promovida_esp = NULL;
		arbol_verga_nodo *hijo_der_primer_llave_esp = NULL;
		void *hijo_der_primer_hijo_esp = NULL;

		arbol_verga_nodo *hijo_izq_ultima_llave = NULL;
		void *hijo_izq_ultimo_hijo = NULL;
		arbol_verga_nodo *padre_llave_promovida = NULL;
		arbol_verga_nodo *hijo_der_primer_llave = NULL;
		void *hijo_der_primer_hijo = NULL;

		hijo_izq_ultima_llave_esp = arbol_verga_obten_llave_en_pos(nodo_split,
				pos_media_hijo_split - 1);
		hijo_izq_ultimo_hijo_esp = arbol_verga_obten_hijo_der(nodo_split,
				pos_media_hijo_split - 1);

		padre_llave_promovida_esp = arbol_verga_obten_llave_en_pos(nodo_split,
				pos_media_hijo_split);

		hijo_der_primer_llave_esp = arbol_verga_obten_llave_en_pos(nodo_split,
				pos_media_hijo_split + 1);
		hijo_der_primer_hijo_esp = arbol_verga_obten_hijo_izq(nodo_split,
				pos_media_hijo_split + 1);

		arbol_verga_separa_y_promueve(ctx, ctx->raiz_arbol_verga_ctx,
				pos_split);

		hijo_izq = arbol_verga_obten_hijo_izq(ctx->raiz_arbol_verga_ctx,
				pos_split);
		hijo_der = arbol_verga_obten_hijo_der(ctx->raiz_arbol_verga_ctx,
				pos_split);

		hijo_izq_ultima_llave = arbol_verga_obten_ultima_llave(hijo_izq);
		hijo_izq_ultimo_hijo = arbol_verga_obten_ultimo_hijo(hijo_izq);
		ck_assert_msg(
				hijo_izq_ultima_llave == hijo_izq_ultima_llave_esp
						&& hijo_izq_ultimo_hijo == hijo_izq_ultimo_hijo_esp,
				"hijo izq faio, llave %p, esp %p, hijo %p, esp %p",
				hijo_izq_ultima_llave, hijo_izq_ultima_llave_esp,
				hijo_izq_ultimo_hijo, hijo_izq_ultimo_hijo_esp);

		padre_llave_promovida = arbol_verga_obten_llave_en_pos(
				ctx->raiz_arbol_verga_ctx, pos_split);
		ck_assert_msg(padre_llave_promovida == padre_llave_promovida_esp,
				"llave promovida faio %p esp %p", padre_llave_promovida,
				padre_llave_promovida_esp);

		hijo_der_primer_llave = arbol_verga_obten_primer_llave(hijo_der);
		hijo_der_primer_hijo = arbol_verga_obten_primer_hijo(hijo_der);
		ck_assert_msg(
				hijo_der_primer_llave == hijo_der_primer_llave_esp
						&& hijo_der_primer_hijo == hijo_der_primer_hijo_esp,
				"hijo der faio");

	}END_TEST

START_TEST( test_arbol_verga_inserta)
	{
		arbol_verga_inserta(ctx, 10);
		arbol_verga_inserta(ctx, 20);
		arbol_verga_inserta(ctx, 30);
		arbol_verga_inserta(ctx, 40);
		arbol_verga_inserta(ctx, 50);
		arbol_verga_inserta(ctx, 60);
		arbol_verga_inserta(ctx, 70);
		arbol_verga_inserta(ctx, 80);
		arbol_verga_inserta(ctx, 90);

		arbol_verga_nodo *raiz;
		arbol_verga_nodo *hijo1;
		arbol_verga_nodo *hijo2;
		arbol_verga_nodo *hijo3;

		raiz = ctx->raiz_arbol_verga_ctx;
		hijo1 = arbol_verga_obten_hijo_en_pos(raiz, 0);
		hijo2 = arbol_verga_obten_hijo_en_pos(raiz, 1);
		hijo3 = arbol_verga_obten_hijo_en_pos(raiz, 2);

		ck_assert_msg(
				arbol_verga_obten_llave_en_pos(raiz,0)==30 && arbol_verga_obten_llave_en_pos(raiz,1)==60,
				"mierda raiz mala, esp en 0 30, real %d, espe en 1 60, real %p",
				arbol_verga_obten_llave_en_pos(raiz,0),
				arbol_verga_obten_llave_en_pos(raiz,1));

	}END_TEST

START_TEST( test_arbol_verga_borrar_para_nuva_raiz)
	{
		arbol_verga_inserta(ctx, 10);
		arbol_verga_inserta(ctx, 20);
		arbol_verga_inserta(ctx, 30);
		arbol_verga_inserta(ctx, 40);
		arbol_verga_inserta(ctx, 50);

		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 30);

		arbol_verga_nodo *nueva_raiz = ctx->raiz_arbol_verga_ctx;

		natural pos_act = 0;
		ck_assert_msg(arbol_verga_obten_llave_en_pos(nueva_raiz,pos_act)==10,
				"posicion 0 no sta bien exp %d encontrada %d (%p)", 10,
				arbol_verga_obten_llave_en_pos(nueva_raiz,pos_act),
				arbol_verga_obten_llave_en_pos(nueva_raiz,pos_act));

		pos_act = 1;
		void *llave_esp = 20;
		ck_assert_msg(
				arbol_verga_obten_llave_en_pos(nueva_raiz,pos_act)==llave_esp,
				"posicion %u no sta bien exp %d encontrada %d (%p)", pos_act,
				llave_esp, arbol_verga_obten_llave_en_pos(nueva_raiz,pos_act),
				arbol_verga_obten_llave_en_pos(nueva_raiz,pos_act));

		pos_act = 2;
		llave_esp = 40;
		ck_assert_msg(
				arbol_verga_obten_llave_en_pos(nueva_raiz,pos_act)==llave_esp,
				"posicion %u no sta bien exp %d encontrada %d (%p)", pos_act,
				llave_esp, arbol_verga_obten_llave_en_pos(nueva_raiz,pos_act),
				arbol_verga_obten_llave_en_pos(nueva_raiz,pos_act));

		pos_act = 3;
		llave_esp = 50;
		ck_assert_msg(
				arbol_verga_obten_llave_en_pos(nueva_raiz,pos_act)==llave_esp,
				"posicion %u no sta bien exp %d encontrada %d (%p)", pos_act,
				llave_esp, arbol_verga_obten_llave_en_pos(nueva_raiz,pos_act),
				arbol_verga_obten_llave_en_pos(nueva_raiz,pos_act));

	}END_TEST

START_TEST( test_arbol_verga_borrar_intermedio)
	{
		void *llaves[100] = { NULL };
		natural llaves_cnt=0;
		for (int i = 50; i >= 1; i--) {
			arbol_verga_inserta(ctx, i);
		}
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 12);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 18);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 9);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 33);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 32);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 42);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 21);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 22);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 50);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 7);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 36);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 20);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 23);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 11);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 14);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 17);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 1);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 4);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 10);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 5);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 3);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 8);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 16);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 43);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 6);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 29);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 45);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 39);
		arbol_verga_borra_llave(ctx, ctx->raiz_arbol_verga_ctx, 31);
		arbol_verga_dumpea_inorder(ctx, llaves, &llaves_cnt);
		arbol_verga_dumpea_bfs(ctx, NULL, NULL);
	}END_TEST

Suite *
cacacomun_suite(void) {

	Suite *s = suite_create("cagada");

	/* Core test case */
	TCase *tc_core = tcase_create("puta");
	tcase_add_unchecked_fixture(tc_core, setup, teardown);
	tcase_add_checked_fixture(tc_core, crea_nodo, nada);

	tcase_set_timeout(tc_core, 10);
	tcase_add_test(tc_core, test_arbol_verga_init);
	tcase_add_test(tc_core, test_arbol_verga_borra_llave_inicial);
	tcase_add_test(tc_core, test_arbol_verga_borra_llave_final);
	tcase_add_test(tc_core, test_arbol_verga_borra_llave_medio);
	suite_add_tcase(s, tc_core);

	TCase *tc_rota = tcase_create("rotaciones");
	tcase_add_unchecked_fixture(tc_rota, setup, teardown);
	tcase_add_checked_fixture(tc_rota, crea_tercia_de_nodos, nada);
	tcase_add_test(tc_rota, test_arbol_verga_rotacion_izq_primer);
	tcase_add_test(tc_rota, test_arbol_verga_rotacion_izq_final);
	tcase_add_test(tc_rota, test_arbol_verga_rotacion_der_primer);
	tcase_add_test(tc_rota, test_arbol_verga_rotacion_der_final);
	tcase_add_test(tc_rota, test_arbol_verga_mergear_primera_llave);
	tcase_add_test(tc_rota, test_arbol_verga_mergear_ultima_llave);
	tcase_add_test(tc_rota, test_arbol_verga_mergea_y_promueve_primero);
	tcase_add_test(tc_rota, test_arbol_verga_mergea_y_promueve_ultimo);
	tcase_add_test(tc_rota, test_arbol_verga_mergea_y_promueve_medio);
	suite_add_tcase(s, tc_rota);

	TCase *tc_i_b = tcase_create("inserciones,borrados");
	tcase_add_unchecked_fixture(tc_i_b, setup, teardown);
	tcase_add_test(tc_i_b, test_arbol_verga_inserta);
	tcase_add_test(tc_i_b, test_arbol_verga_borrar_para_nuva_raiz);
	tcase_add_test(tc_i_b, test_arbol_verga_borrar_intermedio);
	suite_add_tcase(s, tc_i_b);

	return s;
}

int main(void) {
	int number_failed;
	Suite *s = cacacomun_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
