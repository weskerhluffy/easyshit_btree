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

/*
 START_TEST( test_arbol_verga_init)
 {
 }END_TEST
 */

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
		hijo_borrado_real = arbol_verga_borra_llave_en_nodo(ctx, nodo, 11);
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
		hijo_borrado_real = arbol_verga_borra_llave_en_nodo(ctx, nodo, 41);
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
		hijo_borrado_real = arbol_verga_borra_llave_en_nodo(ctx, nodo, 21);
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

Suite *
cacacomun_suite(void) {

	Suite *s = suite_create("cagada");

	/* Core test case */
	TCase *tc_core = tcase_create("puta");
	tcase_add_unchecked_fixture(tc_core, setup, teardown);
	tcase_add_checked_fixture(tc_core, crea_nodo, nada);

	tcase_set_timeout(tc_core, 10);
	tcase_add_test(tc_core, test_arbol_verga_init);
//	tcase_add_test(tc_core, test_arbol_verga_construye_nodo);
	tcase_add_test(tc_core, test_arbol_verga_borra_llave_inicial);
	tcase_add_test(tc_core, test_arbol_verga_borra_llave_final);
	tcase_add_test(tc_core, test_arbol_verga_borra_llave_medio);
	suite_add_tcase(s, tc_core);

	TCase *tc_rota = tcase_create("rotaciones");
	tcase_add_unchecked_fixture(tc_rota, setup, teardown);
	tcase_add_checked_fixture(tc_rota, crea_tercia_de_nodos, nada);
	tcase_add_test(tc_rota, test_arbol_verga_rotacion_izq_primer);
	suite_add_tcase(s, tc_rota);

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