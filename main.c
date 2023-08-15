#include <stdio.h>
#include <string.h>

#define COLUNAS 30  //valor pra coluna de strings
void formas_de_pagamento_cliente(int qty_pagamento, int *ponteiro_pagar_cliente, int *ptr_numero_pag, char (*ptrMatriz)[COLUNAS], char (*ptr_formas_de_pagamento_do_cliente_str)[COLUNAS]) {
    for (int i = 0; i < qty_pagamento; i++){
        int a = *(ponteiro_pagar_cliente + i);
        int index = -1; // Inicializa com -1 para indicar que não encontrou nenhuma forma de pagamento
        for (int x = 0; x < qty_pagamento; x++) {
            int b = *(ptr_numero_pag + x);
            if (b == a) {
                index = x;
                break;
            }
        }

        if (index != -1) {
            // Copiar a forma de pagamento do índice correspondente para a matriz do cliente
            for (int j = 0; j < COLUNAS; j++) {
                ptr_formas_de_pagamento_do_cliente_str[i][j] = ptrMatriz[index][j];
            }
        }
    }
}

void forma_de_pagamento(int qty_pagamento, char (*ptrMatriz)[COLUNAS], int *ptr_numero_pag) {
    for (int i = 0; i < qty_pagamento; i++) {
        printf("Coloque o nome da %d forma de pagamento: ", i + 1);
        fgets(ptrMatriz[i], COLUNAS, stdin);

        printf("Coloque o número de cadastro dessa forma de pagamento: ");
        scanf("%d", &ptr_numero_pag[i]);
        getchar();
    }
}

int main()
{
    int qtd_produtos, i;
    int codProd,qty_pagamento, qty_pagar_cliente;  
    float valorFinalDaCompra = 0;  //quanto deverá ser pago pelo consumidor
    float valorTotalDoPro = 0;   //valor resultante da multiplicação entre o preço do produto e a quantidade desejada
    int qtd = 0;
    float troco;
    float somaDosPagamentos;  //soma os pagamentos parciais do clinte
    int qtd_tipo_produtos=0;

    printf("\t\t VENDEDOR - CADASTRO DAS FORMAS DE VENDA\n\n\n");

    printf("VENDEDOR, Quantas formas de pagamento você irá cadastrar? ");
    scanf("%d", &qty_pagamento);
    getchar();

    char matriz[qty_pagamento][COLUNAS];
    int numero_pag[qty_pagamento];

    char (*ptrMatriz)[COLUNAS];
    int *ptr_numero_pag;

    ptrMatriz = matriz;
    ptr_numero_pag = numero_pag;

    forma_de_pagamento(qty_pagamento, ptrMatriz, ptr_numero_pag);

    printf("\n\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n\n");

    printf("\t\t VENDEDOR - CADASTRO DOS PRODUTOS\n\n\n");


    //OBTENDO QUANTIDADE DE PRODUTOS CADASTRADOS
        do {
            printf("Quantos produtos serão cadastrados? ");
            scanf("%d", &qtd_produtos);
        
        if (qtd_produtos <= 0) {
            printf("Valor inválido. Insira um valor maior que 0.\n");
        }
        } while (qtd_produtos <= 0);

        int codigo_produtos[qtd_produtos]; //VETOR PARA ARMAZENAR CÓDIGOS DOS PRODUTOS
        float preco_produtos[qtd_produtos]; //VETOR PARA ARMAZENAR PREÇO DOS PRODUTOS
        char nome_produtos[qtd_produtos][50]; //VETOR PARA ARMAZENAR NOME DOS PRODUTOS

        //OBTENDO CÓDIGO DO PRODUTOS
        for (int i = 0; i < qtd_produtos; i++) {
            printf("\nInsira o código do produto que se deseja cadastrar: \n");
            scanf("%d", &codigo_produtos[i]);

            while (getchar() != '\n');

            do {
                printf("\nInsira o preço do produto que se deseja cadastrar: \n");
                scanf("%f", &preco_produtos[i]);
        
            if (preco_produtos <= 0) {
                printf("Valor inválido. Insira um valor maior que 0.\n");
            }
            } while (preco_produtos <= 0);

            while (getchar() != '\n');

            printf("\nInsira o nome do produto que se deseja cadastrar: \n");
            fgets(nome_produtos[i], sizeof(nome_produtos[i]), stdin);
            nome_produtos[i][strcspn(nome_produtos[i], "\n")] = '\0';
        }
        

    printf("\t\t\t\t PROCESSO DE VENDA");

    printf("Quantos produtos diferentes serão comprados:");
    scanf("%d", &qtd_tipo_produtos);

    while(qtd_tipo_produtos<=0 || qtd_tipo_produtos>qtd_produtos)
    {
        printf("\n\nO valor inserido é inválido! Insira uma quantidade que seja maior do que 0 e menor que q quantidade total disponível");
        scanf("%d", &qtd_tipo_produtos);
    }

    int j, x, w=0, referencia; 
    float lista_compra[qtd_tipo_produtos][4];
    char lista_compra_nomes[qtd_tipo_produtos][50];
    int index_produto;

    for(x=0;x<qtd_tipo_produtos;x++){
        index_produto = 0;
        
        //TELA DE VENDA
        printf("\nInsira o código do produto:  ");
        scanf("%d", &codProd);

        printf("\nInsira o número de unidades desejadas desse produto:  ");
        scanf("%d", &qtd);

        while(qtd<=0)
        {
            printf("\n\nO valor inserido é inválido! Insira uma quantidade que seja maior do que 0");
            scanf("%d", &qtd);
        }

        for(i=0;i<qtd_produtos; i++){
            if(codProd==codigo_produtos[i]){
                valorFinalDaCompra=valorFinalDaCompra+(preco_produtos[i]*qtd);
                referencia=i;
                valorTotalDoPro=preco_produtos[i]*qtd;
                index_produto = i;
                break;
            }
        }


        lista_compra[w][1]=codProd;
        lista_compra[w][2]=preco_produtos[referencia];
        lista_compra[w][3]=qtd;
        lista_compra[w][4]=valorTotalDoPro;
        
        for (int z = 0; z < 50; z++) {
            lista_compra_nomes[w][z] = nome_produtos[index_produto][z];
        }
        
        w++;

        printf("\n\n\n");
        
        printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");

        printf("\t \t Valor \t Quantidade \t Valor Total");  //interface

        printf("\t \n\n\t \t %.2f \t %d \t\t %.2f", preco_produtos[referencia], qtd, valorTotalDoPro);

        printf("\n\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    }

    //caso o código chegue nessa parte, é sinal de que todos os produtos desejados já foram cadastrados, portanto agora deve-se efetuar o pagamento

    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

    printf("\n\n\n\t\t\t\t EFETUANDO O PAGAMENTO....\n\n\n");

    printf("CÓDIGO DAS FORMAS DE PAGAMENTO");

    for (int i = 0; i < qty_pagamento; i++) {
        printf("\n\n\nCódigo do: %s \t %d",ptrMatriz[i],ptr_numero_pag[i]);
    }


    while (1==1)
    {
        printf("\n\nQuantas formas de pagamento você quer usar? ");
        scanf("%d", &qty_pagar_cliente);

        if(qty_pagamento < qty_pagar_cliente){
            printf("Por favor, pague com menos ou igual que %d formas de pagamento",qty_pagamento);
        }

        else{
            break;
        }
    }

    int numeros_formas_pag_cliente[qty_pagar_cliente];
    int *ponteiro_pagar_cliente = numeros_formas_pag_cliente;

    for (int i = 0; i < qty_pagar_cliente; i++) {
        printf("\nColoque o código da forma de pagamento %d: ", i + 1);
        scanf("%d", &numeros_formas_pag_cliente[i]);
    }


    char formas_de_pagamento_do_cliente_str[qty_pagar_cliente][COLUNAS];
    char (*ptr_formas_de_pagamento_do_cliente_str)[COLUNAS] = formas_de_pagamento_do_cliente_str;

    formas_de_pagamento_cliente(qty_pagamento, ponteiro_pagar_cliente, ptr_numero_pag, ptrMatriz, ptr_formas_de_pagamento_do_cliente_str);

    /* as formas de pagamento pra utilizar na nota fiscal final estão armazenadas na matriz
    formas_de_pagamento_do_cliente_str, pra escrevê-las certinho, o código abaixo faz isso

    */

    float matrizSomaDosPagamentos[qty_pagar_cliente];   //mostrará todas as formas de pagamento escolhidas pelo cliente

    printf("\nFormas de pagamento do cliente:\n");
    for (int i = 0; i < qty_pagar_cliente; i++) {
        printf("%d: %s\n",i+1, formas_de_pagamento_do_cliente_str[i]);
    }

    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

    printf("\n\n\n");

    printf("\n\nO VALOR TOTAL A SER PAGO É: %.2f", valorFinalDaCompra);

    printf("\n\n\n\n");

    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

    printf("\n\n\n");

    for (int i = 0; i < qty_pagar_cliente; i++) {
        printf("\n\nINSIRA O VALOR A SER PAGO NO: %s", formas_de_pagamento_do_cliente_str[i]);
        scanf("%f", &matrizSomaDosPagamentos[i]);

        somaDosPagamentos += matrizSomaDosPagamentos[i];

    }

    if(somaDosPagamentos==valorFinalDaCompra)
    {

        printf("\n\n\n");

        printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

        printf("\n\n\n");

        printf("PAGAMENTO REALIZADO COM SUCESSO!\n\n\nAGRADECEMOS PELA PREFERÊNCIA!");

        printf("\n\n\n");

        printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    }

    else if(somaDosPagamentos<valorFinalDaCompra)
    {


        while(somaDosPagamentos<valorFinalDaCompra)
        {
            printf("\n\nO SOMATÓRIO DOS VALORES PAGO PELO CLIENTE É MENOR QUE O VALOR TOTAL DA COMPRA!\n\n\nREALIZE O PAGAMENTO NOVAMENTE!\n");

            somaDosPagamentos = 0;


           for (int i = 0; i < qty_pagar_cliente; i++)
           {
            printf("\n\nINSIRA O VALOR A SER PAGO NO: %s", formas_de_pagamento_do_cliente_str[i]);
            scanf("%f", &matrizSomaDosPagamentos[i]);

            somaDosPagamentos += matrizSomaDosPagamentos[i];

           }
        }

        if(somaDosPagamentos==valorFinalDaCompra)
        {

            printf("\n\n\n");

            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

            printf("\n\n\n");

            printf("PAGAMENTO REALIZADO COM SUCESSO!\n\n\nAGRADECEMOS PELA PREFERÊNCIA!");

            printf("\n\n\n");

            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
        }

        else if(somaDosPagamentos>valorFinalDaCompra)
        {
            troco = somaDosPagamentos-valorFinalDaCompra;

            printf("\n\nO CLIENTE DEVE RECEBER %.2f REAIS DE TROCO.", troco);

            printf("\n\n\n");

            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

            printf("\n\n\n");

            printf("PAGAMENTO REALIZADO COM SUCESSO!\n\n\nAGRADECEMOS PELA PREFERÊNCIA!");

            printf("\n\n\n");

            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");


        }

    }

    else if(somaDosPagamentos>valorFinalDaCompra)
    {
        troco = somaDosPagamentos-valorFinalDaCompra;

        printf("\n\nO CLIENTE DEVE RECEBER %.2f REAIS DE TROCO.", troco);

        printf("\n\n\n");

        printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

        printf("\n\n\n");

        printf("PAGAMENTO REALIZADO COM SUCESSO!\n\n\nAGRADECEMOS PELA PREFERÊNCIA!");

        printf("\n\n\n");

        printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");


    }

    printf("Código do produto  Nome do produto  Valor unit.  Quantidade  Valor total do produto\n");
    
    int y;
    for(y=0;y<qtd_tipo_produtos;y++){
        printf("%.2f   %s   %.2f   %.2f   %.2f\n", lista_compra[y][1], lista_compra_nomes[y], lista_compra[y][2], lista_compra[y][3], lista_compra[y][4]);
    }

    //colocar as formas de pagamento que usa juntamente com os valores
    for (int i = 0; i < qty_pagar_cliente; i++) {
        printf("\n\n\nCódigo do %d: %s \nValor: %.2f \t",ptr_numero_pag[i], ptr_formas_de_pagamento_do_cliente_str[i],matrizSomaDosPagamentos[i]);
    }
    

    printf("\nValor total da compra: %.2f", valorFinalDaCompra);
    
    
    return 0;
}
