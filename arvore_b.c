//Matheus Oliveira B de Melo, UNIFAN. 4° Períofdo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3
#define MIN 2

struct BTreeNode {
    char val[MAX + 1][50]; // Armazena nome dos arquivos °°°
    int count;
    struct BTreeNode *link[MAX + 1];
};

struct BTreeNode *root = NULL;

// Cria um nó novo (*-*)
struct BTreeNode *createNode(char *val, struct BTreeNode *child) {
    struct BTreeNode *newNode;
    newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    strcpy(newNode->val[1], val);
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

// Insere em um nó que ja existe ('-')
void insertNode(char *val, int pos, struct BTreeNode *node, struct BTreeNode *child) {
    int j = node->count;
    while (j > pos) {
        strcpy(node->val[j + 1], node->val[j]);
        node->link[j + 1] = node->link[j];
        j--;
    }
    strcpy(node->val[j + 1], val);
    node->link[j + 1] = child;
    node->count++;
}

// Divide o nó *(^o^)*
void splitNode(char *val, char *pval, int pos, struct BTreeNode *node,
               struct BTreeNode *child, struct BTreeNode **newNode) {
    int median, j;

    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    j = median + 1;
    while (j <= MAX) {
        strcpy((*newNode)->val[j - median], node->val[j]);
        (*newNode)->link[j - median] = node->link[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN) {
        insertNode(val, pos, node, child);
    } else {
        insertNode(val, pos - median, *newNode, child);
    }
    strcpy(pval, node->val[node->count]);
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}

//
int setValue(char *val, char *pval, struct BTreeNode *node, struct BTreeNode **child) {
    int pos;
    if (!node) {
        strcpy(pval, val);
        *child = NULL;
        return 1;
    }

    if (strcmp(val, node->val[1]) < 0) {
        pos = 0;
    } else {
        for (pos = node->count; (strcmp(val, node->val[pos]) < 0 && pos > 1); pos--)
            ;
        if (strcmp(val, node->val[pos]) == 0) {
            printf("Arquivo já existe na árvore.\n");
            return 0;
        }
    }
    if (setValue(val, pval, node->link[pos], child)) {
        if (node->count < MAX) {
            insertNode(pval, pos, node, *child);
        } else {
            splitNode(pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

  // insere um novo aquivivo  (o_O)
void insert(char *val) {
    char pval[50];
    int flag;
    struct BTreeNode *child;

    flag = setValue(val, pval, root, &child);
    if (flag)
        root = createNode(pval, child);
}

// Busca o Arquivo (._.)
void search(char *val, int *pos, struct BTreeNode *myNode) {
    if (!myNode) {
        printf("Arquivo não encontrado.\n");
        return;
    }

    if (strcmp(val, myNode->val[1]) < 0) {
        *pos = 0;
    } else {
        for (*pos = myNode->count;
             (strcmp(val, myNode->val[*pos]) < 0 && *pos > 1); (*pos)--)
            ;
        if (strcmp(val, myNode->val[*pos]) == 0) {
            printf("Arquivo \"%s\" encontrado.\n", val);
            return;
        }
    }
    search(val, pos, myNode->link[*pos]);
}

// Mostrar os arquivos armazenados (u_u)
void traversal(struct BTreeNode *myNode) {
    int i;
    if (myNode) {
        for (i = 0; i < myNode->count; i++) {
            traversal(myNode->link[i]);
            printf("%s\n", myNode->val[i + 1]);
        }
        traversal(myNode->link[i]);
    }
}

// Main (-_-;)
int main() {
    int escolha;
    char filename[50];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir um arquivo\n");
        printf("2. Buscar um arquivo\n");
        printf("3. Listar arquivos\n");
        printf("4. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        getchar();  

        switch (escolha) {
            case 1:
                printf("Digite o nome do arquivo: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;  //
                insert(filename);
                printf("Arquivo \"%s\" inserido!\n", filename);
                break;

            case 2:
                printf("Digite o nome do arquivo para buscar: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;
                int pos;
                search(filename, &pos, root);
                break;

            case 3:
                printf("Arquivos armazenados:\n");
                traversal(root);
                break;

            case 4:
                printf("Saindo...\n");
                exit(0);

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}