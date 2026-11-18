/*
 * UNIVERSIDADE PRESBITERIANA MACKENZIE
 * Faculdade de Computação e Informática
 * Disciplina: Algoritmos e Programação II
 *
 * Projeto 2 - Sistema de Análise de Consumo de Energia
 *
 * Integrantes do grupo:
 *   Nome: IGOR R BRIZOLA RA: 10730402
 *   Nome: CALVIN ZHOU RA: 10752968
 */

int carregarUnidades(const char nomeArquivo[], int unidadeIds[], char descricoes[][50], int max);

int carregarLeituras(const char nomeArquivo[], int ids[], int unidadeIds[], int meses[], int anos[],
                     float consumos[], int max);

int buscaLinear(int ids[], int n, int idProcurado);

int buscaBinaria(int ids[], int n, int idProcurado);

void bubbleSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                            int n);

void insertionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[],
                               float consumos[], int n);

void selectionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[],
                               float consumos[], int n);

int particionarLeituras(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                        int inicio, int fim);

void quickSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                           int inicio, int fim);

void intercalarLeituras(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                        int inicio, int meio, int fim);

void mergeSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                           int inicio, int fim);

float calcularConsumoUnidade(int unidadeIds[], float consumos[], int n, int unidadeId);

float calcularConsumoPeriodo(int meses[], int anos[], float consumos[], int n, int mesInicial,
                             int anoInicial, int mesFinal, int anoFinal);

int encontrarUnidadeMaiorConsumo(int unidadeIds[], float consumos[], int n);

void trocarItensLeitura(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                        int a, int b);

void limparEntrada();

int lerInteiro();
