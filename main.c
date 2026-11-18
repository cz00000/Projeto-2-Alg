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

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

#define MAX 1000

int carregarUnidades(const char nomeArquivo[], int unidadeIds[], char descricoes[][50], int max) {

    int lidos = 0;

    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        return -1;
    }

    while (lidos < max &&
           fscanf(arquivo, "%d ;%49[^\n]", &unidadeIds[lidos], descricoes[lidos]) == 2) {
        lidos++;
    }

    fclose(arquivo);

    return lidos;
}

int carregarLeituras(const char nomeArquivo[], int ids[], int unidadeIds[], int meses[], int anos[],
                     float consumos[], int max) {

    int lidos = 0;

    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        return -1;
    }

    while (lidos < max && fscanf(arquivo, "%d %d %d %d %f", &ids[lidos], &unidadeIds[lidos],
                                 &meses[lidos], &anos[lidos], &consumos[lidos]) == 5) {
        lidos++;
    }

    fclose(arquivo);

    return lidos;
}

int buscaLinear(int ids[], int n, int idProcurado) {
    int i;
    for (i = 0; i < n; i++) {
        if (ids[i] == idProcurado) {
            return i;
        }
    }

    return -1;
}

int buscaBinaria(int ids[], int n, int idProcurado) {

    int esq = 0;
    int dir = n - 1;

    while (esq <= dir) {
        int meio = (esq + dir) / 2;

        if (ids[meio] == idProcurado) {
            return meio;
        } else if (ids[meio] < idProcurado) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return -1;
}

void bubbleSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                            int n) {
    int i;
    int j;

    for (i = 1; i < n; i++) {
        bool ordenado = true;
        for (j = 0; j < n - i; j++) {
            if (ids[j] > ids[j + 1]) {
                trocarItensLeitura(ids, unidadeIds, meses, anos, consumos, j, j + 1);
                ordenado = false;
            }
        }

        if (ordenado) {
            return;
        }
    }
}

void selectionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[],
                               float consumos[], int n) {
    int i;
    int j;

    for (i = 0; i < n - 1; i++) {
        int min = i;
        for (j = i + 1; j < n; j++) {
            if (ids[j] < ids[min]) {
                min = j;
            }
        }
        if (min != i) {
            trocarItensLeitura(ids, unidadeIds, meses, anos, consumos, i, min);
        }
    }
}

void insertionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[],
                               float consumos[], int n) {
    int i;

    for (i = 1; i < n; i++) {

        int elementoId = ids[i];
        int elementoUnidade = unidadeIds[i];
        int elementoMes = meses[i];
        int elementoAno = anos[i];
        float elementoConsumo = consumos[i];

        int j = i - 1;

        while (j >= 0 && ids[j] > elementoId) {
            ids[j + 1] = ids[j];
            unidadeIds[j + 1] = unidadeIds[j];
            meses[j + 1] = meses[j];
            anos[j + 1] = anos[j];
            consumos[j + 1] = consumos[j];
            j--;
        }

        ids[j + 1] = elementoId;
        unidadeIds[j + 1] = elementoUnidade;
        meses[j + 1] = elementoMes;
        anos[j + 1] = elementoAno;
        consumos[j + 1] = elementoConsumo;
    }
}

int particionarLeituras(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                        int inicio, int fim) {
    int j;

    int pivo = ids[fim];
    int i = inicio - 1;

    for (j = inicio; j < fim; j++) {
        if (ids[j] < pivo) {
            i++;
            trocarItensLeitura(ids, unidadeIds, meses, anos, consumos, i, j);
        }
    }

    trocarItensLeitura(ids, unidadeIds, meses, anos, consumos, i + 1, fim);

    return i + 1;
}

void quickSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                           int inicio, int fim) {

    if (inicio < fim) {
        int posicaoPivo = particionarLeituras(ids, unidadeIds, meses, anos, consumos, inicio, fim);

        quickSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, inicio, posicaoPivo - 1);
        quickSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, posicaoPivo + 1, fim);
    }
}

void intercalarLeituras(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                        int inicio, int meio, int fim) {
    int t;

    int auxIds[MAX];
    int auxUnidadeIds[MAX];
    int auxMeses[MAX];
    int auxAnos[MAX];
    float auxConsumos[MAX];

    int i = inicio;
    int j = meio + 1;
    int k = 0;

    while (i <= meio && j <= fim) {
        if (ids[i] <= ids[j]) {
            auxIds[k] = ids[i];
            auxUnidadeIds[k] = unidadeIds[i];
            auxMeses[k] = meses[i];
            auxAnos[k] = anos[i];
            auxConsumos[k] = consumos[i];
            i++;
        } else {
            auxIds[k] = ids[j];
            auxUnidadeIds[k] = unidadeIds[j];
            auxMeses[k] = meses[j];
            auxAnos[k] = anos[j];
            auxConsumos[k] = consumos[j];
            j++;
        }
        k++;
    }

    while (i <= meio) {
        auxIds[k] = ids[i];
        auxUnidadeIds[k] = unidadeIds[i];
        auxMeses[k] = meses[i];
        auxAnos[k] = anos[i];
        auxConsumos[k] = consumos[i];
        i++;
        k++;
    }

    while (j <= fim) {
        auxIds[k] = ids[j];
        auxUnidadeIds[k] = unidadeIds[j];
        auxMeses[k] = meses[j];
        auxAnos[k] = anos[j];
        auxConsumos[k] = consumos[j];
        j++;
        k++;
    }

    for (t = 0; t < k; t++) {
        ids[inicio + t] = auxIds[t];
        unidadeIds[inicio + t] = auxUnidadeIds[t];
        meses[inicio + t] = auxMeses[t];
        anos[inicio + t] = auxAnos[t];
        consumos[inicio + t] = auxConsumos[t];
    }
}

void mergeSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                           int inicio, int fim) {

    if (inicio < fim) {
        int meio = (inicio + fim) / 2;

        mergeSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, inicio, meio);
        mergeSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, meio + 1, fim);
        intercalarLeituras(ids, unidadeIds, meses, anos, consumos, inicio, meio, fim);
    }
}

float calcularConsumoUnidade(int unidadeIds[], float consumos[], int n, int unidadeId) {
    int i;

    float total = 0;

    for (i = 0; i < n; i++) {
        if (unidadeIds[i] == unidadeId) {
            total = total + consumos[i];
        }
    }

    return total;
}

float calcularConsumoPeriodo(int meses[], int anos[], float consumos[], int n, int mesInicial,
                             int anoInicial, int mesFinal, int anoFinal) {
    int i;

    float total = 0;
    int inicio = anoInicial * 12 + mesInicial;
    int fim = anoFinal * 12 + mesFinal;

    for (i = 0; i < n; i++) {
        int data = anos[i] * 12 + meses[i];
        if (data >= inicio && data <= fim) {
            total = total + consumos[i];
        }
    }

    return total;
}

int encontrarUnidadeMaiorConsumo(int unidadeIds[], float consumos[], int n) {
    int i;

    int idMaior = -1;
    float maior = -1;

    for (i = 0; i < n; i++) {
        float total = calcularConsumoUnidade(unidadeIds, consumos, n, unidadeIds[i]);
        if (total > maior || (total == maior && unidadeIds[i] < idMaior)) {
            maior = total;
            idMaior = unidadeIds[i];
        }
    }

    return idMaior;
}

void trocarItensLeitura(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                        int a, int b) {
    int tempId = ids[a];
    int tempUnidadeId = unidadeIds[a];
    int tempMes = meses[a];
    int tempAno = anos[a];
    float tempConsumo = consumos[a];

    ids[a] = ids[b];
    ids[b] = tempId;

    unidadeIds[a] = unidadeIds[b];
    unidadeIds[b] = tempUnidadeId;

    meses[a] = meses[b];
    meses[b] = tempMes;

    anos[a] = anos[b];
    anos[b] = tempAno;

    consumos[a] = consumos[b];
    consumos[b] = tempConsumo;
}

void limparEntrada() {
    int c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int lerInteiro() {
    int valor = 0;
    if (scanf("%d", &valor) != 1) {
        limparEntrada();
        valor = 0;
    }
    return valor;
}

void obterDescricao(int unidadeIdsCatalogo[], char descricoes[][50], int totalUnidades, int id,
                    char destino[]) {
    int k = buscaLinear(unidadeIdsCatalogo, totalUnidades, id);

    if (k == -1) {
        strcpy(destino, "(nao cadastrada)");
    } else {
        strcpy(destino, descricoes[k]);
    }
}

int main() {
    int i;
    char arquivoLeituras[] = "leituras.txt";
    char arquivoUnidades[] = "unidades.csv";

    int unidadeIdsCatalogo[MAX];
    char descricoes[MAX][50];

    int ids[MAX];
    int unidadeIds[MAX];
    int meses[MAX];
    int anos[MAX];
    float consumos[MAX];

    int totalUnidades = carregarUnidades(arquivoUnidades, unidadeIdsCatalogo, descricoes, MAX);

    if (totalUnidades == -1) {
        printf("Erro ao abrir o arquivo unidades.csv.\nEncerrando o programa.\n");
        return 1;
    }

    int totalLeituras =
        carregarLeituras(arquivoLeituras, ids, unidadeIds, meses, anos, consumos, MAX);

    if (totalLeituras == -1) {
        printf("Erro ao abrir o arquivo leituras.txt.\nEncerrando o programa.\n");
        return 1;
    }

    bool ordenado = false;
    bool algoritmoEscolhido = false;
    int opcao = 0;

    while (opcao != 6) {
        printf("\n===== SISTEMA DE ANALISE DE CONSUMO DE ENERGIA =====\n");
        printf("1. Mostrar leituras ordenadas por ID\n");
        printf("2. Buscar leitura por ID\n");
        printf("3. Calcular consumo de uma unidade\n");
        printf("4. Calcular consumo em um periodo\n");
        printf("5. Identificar unidade com maior consumo\n");
        printf("6. Sair da aplicacao\n");
        printf("Escolha uma opcao: ");

        int lido = scanf("%d", &opcao);
        if (lido == EOF) {
            opcao = 6;
        } else if (lido != 1) {
            limparEntrada();
            opcao = 0;
        }

        if (opcao == 1) {
            if (!algoritmoEscolhido) {
                int algoritmo = 0;
                printf("Escolha o algoritmo de ordenacao:\n");
                printf("1. Bubble Sort\n");
                printf("2. Insertion Sort\n");
                printf("3. Selection Sort\n");
                printf("4. Quick Sort\n");
                printf("5. Merge Sort\n");
                printf("Opcao: ");
                algoritmo = lerInteiro();

                if (algoritmo == 1) {
                    bubbleSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, totalLeituras);
                    algoritmoEscolhido = true;
                } else if (algoritmo == 2) {
                    insertionSortLeituraPorId(ids, unidadeIds, meses, anos, consumos,
                                              totalLeituras);
                    algoritmoEscolhido = true;
                } else if (algoritmo == 3) {
                    selectionSortLeituraPorId(ids, unidadeIds, meses, anos, consumos,
                                              totalLeituras);
                    algoritmoEscolhido = true;
                } else if (algoritmo == 4) {
                    quickSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, 0,
                                          totalLeituras - 1);
                    algoritmoEscolhido = true;
                } else if (algoritmo == 5) {
                    mergeSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, 0,
                                          totalLeituras - 1);
                    algoritmoEscolhido = true;
                } else {
                    printf("Opcao invalida. Tente novamente.\n");
                }
            }

            if (algoritmoEscolhido) {
                ordenado = true;
                printf("Leituras ordenadas por ID:\n");
                printf("ID | Unidade | Descricao                  | Mes | Ano | Consumo (kWh)\n");
                printf("-----------------------------------------------------------------------\n");
                for (i = 0; i < totalLeituras; i++) {
                    char descricao[50];
                    obterDescricao(unidadeIdsCatalogo, descricoes, totalUnidades,
                                   unidadeIds[i], descricao);
                    printf("%-2d | %-7d | %-26s | %-3d | %-4d | %.2f\n", ids[i], unidadeIds[i],
                           descricao, meses[i], anos[i], consumos[i]);
                }
            }
        } else if (opcao == 2) {
            int idProcurado = 0;
            int algoritmo = 0;
            int posicao = -1;
            bool buscou = false;

            printf("Digite o ID da leitura: ");
            idProcurado = lerInteiro();

            printf("Escolha o algoritmo de busca:\n");
            printf("1. Busca linear\n");
            printf("2. Busca binaria\n");
            printf("Opcao: ");
            algoritmo = lerInteiro();

            if (algoritmo == 1) {
                posicao = buscaLinear(ids, totalLeituras, idProcurado);
                buscou = true;
            } else if (algoritmo == 2) {
                if (!ordenado) {
                    insertionSortLeituraPorId(ids, unidadeIds, meses, anos, consumos,
                                              totalLeituras);
                    ordenado = true;
                }
                posicao = buscaBinaria(ids, totalLeituras, idProcurado);
                buscou = true;
            } else {
                printf("Opcao invalida. Tente novamente.\n");
            }

            if (buscou) {
                if (posicao == -1) {
                    printf("Leitura nao encontrada.\n");
                } else {
                    char descricao[50];
                    obterDescricao(unidadeIdsCatalogo, descricoes, totalUnidades,
                                   unidadeIds[posicao], descricao);
                    printf("Leitura encontrada:\n");
                    printf("ID Leitura: %d\n", ids[posicao]);
                    printf("Unidade: %d\n", unidadeIds[posicao]);
                    printf("Descricao: %s\n", descricao);
                    printf("Mes: %d\n", meses[posicao]);
                    printf("Ano: %d\n", anos[posicao]);
                    printf("Consumo: %.2f kWh\n", consumos[posicao]);
                }
            }
        } else if (opcao == 3) {
            int unidadeId = 0;

            printf("Digite o ID da unidade: ");
            unidadeId = lerInteiro();

            int k = buscaLinear(unidadeIdsCatalogo, totalUnidades, unidadeId);

            if (k == -1) {
                printf("Unidade nao encontrada.\n");
            } else {
                printf("Consumo da unidade:\n");
                printf("Unidade: %d\n", unidadeId);
                printf("Descricao: %s\n", descricoes[k]);
                printf("Consumo total: %.2f kWh\n",
                       calcularConsumoUnidade(unidadeIds, consumos, totalLeituras, unidadeId));
            }
        } else if (opcao == 4) {
            int mesInicial = 0;
            int anoInicial = 0;
            int mesFinal = 0;
            int anoFinal = 0;

            printf("Digite o mes inicial: ");
            mesInicial = lerInteiro();
            printf("Digite o ano inicial: ");
            anoInicial = lerInteiro();
            printf("Digite o mes final: ");
            mesFinal = lerInteiro();
            printf("Digite o ano final: ");
            anoFinal = lerInteiro();

            if (mesInicial < 1 || mesInicial > 12 || mesFinal < 1 || mesFinal > 12 ||
                anoInicial * 12 + mesInicial > anoFinal * 12 + mesFinal) {
                printf("Periodo invalido.\n");
            } else {
                printf("Consumo no periodo:\n");
                printf("Periodo: %02d/%d ate %02d/%d\n", mesInicial, anoInicial, mesFinal,
                       anoFinal);
                printf("Consumo total: %.2f kWh\n",
                       calcularConsumoPeriodo(meses, anos, consumos, totalLeituras, mesInicial,
                                              anoInicial, mesFinal, anoFinal));
            }
        } else if (opcao == 5) {
            int unidadeId = encontrarUnidadeMaiorConsumo(unidadeIds, consumos, totalLeituras);
            char descricao[50];

            if (unidadeId == -1) {
                printf("Unidade nao encontrada.\n");
            } else {
                obterDescricao(unidadeIdsCatalogo, descricoes, totalUnidades, unidadeId, descricao);
                printf("Unidade com maior consumo:\n");
                printf("Unidade: %d\n", unidadeId);
                printf("Descricao: %s\n", descricao);
                printf("Consumo total: %.2f kWh\n",
                       calcularConsumoUnidade(unidadeIds, consumos, totalLeituras, unidadeId));
            }
        } else if (opcao == 6) {
            printf("Encerrando o programa.\n");
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
