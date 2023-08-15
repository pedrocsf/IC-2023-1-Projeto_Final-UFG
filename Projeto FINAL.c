            
            
            
            
            //PROJETO DE INCOM. PARTICIPANTES: MARCOS PAULO CAETANO MENDES QUEIROZ, PEDRO CÉZAR SILVA FERREIRA, FERNANDO MALTEZ BEZERRA       




#include <stdio.h>
#include <string.h>

#define COLUNAS 30  //valor pra coluna de strings


//verificando e pegando o index das formas de pagamento na matriz primária de pagamento e passando os nomes dos pagamentos que serão usados pelo cliente

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



//cadastrando todas as formas de pagamento do estabelecimento
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
    float valorFinalDaCompra = 0;  
    float valorTotalDoPro = 0;   
    int qtd = 0;
    float troco;
    float somaDosPagamentos;  
    int qtd_tipo_produtos=0;

    printf("\t\t VENDEDOR - CADASTRO DAS FORMAS DE VENDA\n\n\n");    // Nessa parte o vendedor irá cadastrar as formas de pagamento que serão aceitas. 

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

    printf("\t\t VENDEDOR - CADASTRO DOS PRODUTOS\n\n\n");      // Nessa parte o vendedor cadastra quais produtos estarão disponíveis para compra no seu comércio


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

    printf("\n\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n\n");

    printf("\t\t\t\t PROCESSO DE VENDA\n\n");      // A partir dessa parte, tem-se o início da venda, onde o consumidor escolhe quantos e quais produtos irá comprar

    printf("Quantos produtos diferentes serao comprados:"); 
    scanf("%d", &qtd_tipo_produtos);

    while(qtd_tipo_produtos<=0 || qtd_tipo_produtos>qtd_produtos)
    {
        printf("\n\nO valor inserido é invalido! Insira uma quantidade que seja maior do que 0 e menor que q quantidade total disponivel");  //Condicional que impossibilita o cliente de comprar uma quantia de produtos 
        scanf("%d", &qtd_tipo_produtos);                                                                                                     //maior do que a loja tem a oferecer
    }

    int j, w=0, referencia; 
    float lista_compra[qtd_tipo_produtos][4];
    char lista_compra_nomes[qtd_tipo_produtos][50];
    int index_produto;

    for(int x=0;x<qtd_tipo_produtos;x++){
        referencia = 0;
        
        //TELA DE VENDA                                        //Inicia-se o processo onde o cliente, digitando um código, escolhe qual produto vai querer.         
        printf("\nInsira o código do produto:  ");             //Esse processo se repetirá de acordo com a quantidade de produtos que o cliente resolveu comprar
        scanf("%d", &codProd);

        printf("\nInsira o número de unidades desejadas desse produto:  ");   //Cliente escolhe quantas unidades daquele produto em específico ele deseja comprar
        scanf("%d", &qtd);

        while(qtd<=0)
        {
            printf("\n\nO valor inserido é inválido! Insira uma quantidade que seja maior do que 0");  //Condicional que previne o cliente de comprar um número menor ou igual a 0 de produtos
            scanf("%d", &qtd);
        }

        for(int i=0;i<qtd_produtos; i++){
            if(codProd==codigo_produtos[i]){
                valorFinalDaCompra=valorFinalDaCompra+(preco_produtos[i]*qtd);
                referencia=i;
                valorTotalDoPro=preco_produtos[i]*qtd;
                break;
            }
            
            else {
                continue;
            }
        }

        printf("%s \n",nome_produtos[referencia]);
        strcpy(lista_compra_nomes[x], nome_produtos[referencia]);
        printf("%s \n",nome_produtos[referencia]);
        printf("%s \n",lista_compra_nomes[x]);
        lista_compra[x][1]=codProd;
        lista_compra[x][2]=preco_produtos[referencia];
        lista_compra[x][3]=qtd;
        lista_compra[x][4]=valorTotalDoPro;

        printf("\n\n\n");                              //Aqui se encontra uma interface parcial, onde, no display, é mostrado o valor daquele produto que o cliente resolveu comprar,  
                                                       //a quantidade, e o valor total relativo a esse produto em específico.
        printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");

        printf("\t \t Valor \t Quantidade \t Valor Total");  

        printf("\t \n\n\t \t %.2f \t %d \t\t %.2f", preco_produtos[referencia], qtd, valorTotalDoPro);

        printf("\n\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    }

    //caso o código chegue nessa parte, é sinal de que todos os produtos desejados já foram cadastrados, portanto agora deve-se efetuar o pagamento

    

    printf("\n\n\n\t\t\t\t EFETUANDO O PAGAMENTO....\n\n\n");    //Nessa parte haverá o processo de pagamento da compra

    printf("CODIGO DAS FORMAS DE PAGAMENTO");

    for (int i = 0; i < qty_pagamento; i++) {
        printf("\n\n\nCódigo do: %s \t %d",ptrMatriz[i],ptr_numero_pag[i]);  //Motra-se quais são os tipos de pagamento aceitos pelo estabelecimento
    }


    while (1==1)
    {
        printf("\n\nQuantas formas de pagamento você quer usar? ");     //Pergunta ao cliente quantas formas de pagamento ele irá usar para efetuar o pagamento da compra
        scanf("%d", &qty_pagar_cliente);

        if(qty_pagamento < qty_pagar_cliente){
            printf("Por favor, pague com menos ou igual que %d formas de pagamento",qty_pagamento); //Condicional que impossibilita o comprador de escolher um número de formas de pagamento maior 
        }                                                                                           //que a quantidade que o estabelecimento oferece

        else{
            break;
        }
    }

    int numeros_formas_pag_cliente[qty_pagar_cliente];
    int *ponteiro_pagar_cliente = numeros_formas_pag_cliente;

    for (int i = 0; i < qty_pagar_cliente; i++) {
        printf("\nColoque o código da forma de pagamento %d: ", i + 1);          //Nessa parte, o cliente irá inserir o código da(s) forma(s) de pagamento desejada(s)   
        scanf("%d", &numeros_formas_pag_cliente[i]);
    }


    char formas_de_pagamento_do_cliente_str[qty_pagar_cliente][COLUNAS];
    char (*ptr_formas_de_pagamento_do_cliente_str)[COLUNAS] = formas_de_pagamento_do_cliente_str;

    formas_de_pagamento_cliente(qty_pagamento, ponteiro_pagar_cliente, ptr_numero_pag, ptrMatriz, ptr_formas_de_pagamento_do_cliente_str);

    /* as formas de pagamento pra utilizar na nota fiscal final estão armazenadas na matriz
    formas_de_pagamento_do_cliente_str, pra escrevê-las certinho, o código abaixo faz isso*/

    float matrizSomaDosPagamentos[qty_pagar_cliente];   

    printf("\nFormas de pagamento do cliente:\n");              //Display das formas de pagamento escolhidas pelo cliente
    for (int i = 0; i < qty_pagar_cliente; i++) {
        printf("%d: %s\n",i+1, formas_de_pagamento_do_cliente_str[i]);
    }

    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

    printf("\n\n\n");

    printf("\n\nO VALOR TOTAL A SER PAGO É: %.2f", valorFinalDaCompra);    //Apresenta o valor final da compra.

    printf("\n\n\n\n");

    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

    printf("\n\n\n");

    for (int i = 0; i < qty_pagar_cliente; i++) {
        printf("\n\nINSIRA O VALOR A SER PAGO NO: %s", formas_de_pagamento_do_cliente_str[i]);   //Essa parte permite que o cliente decida quanto será pago em cada uma das formas de pagamentos escolhidas.
        scanf("%f", &matrizSomaDosPagamentos[i]);

        somaDosPagamentos += matrizSomaDosPagamentos[i];

    }

    if(somaDosPagamentos==valorFinalDaCompra)   //Condicional para quando o valor pago pelo cliente é igual ao valor final da compra.
    {

        printf("\n\n\n");

        printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

        printf("\n\n\n");

        printf("PAGAMENTO REALIZADO COM SUCESSO!\n\n\nAGRADECEMOS PELA PREFERÊNCIA!");       //Display confirmando que a transação foi completa

        printf("\n\n\n");

        printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    }

    else if(somaDosPagamentos<valorFinalDaCompra)   //Condicional para quando os valores pagos pelo cliente somam uma quantia menor que o valor final da compra
    {


        while(somaDosPagamentos<valorFinalDaCompra)  //Enquanto o somatório dos valores pagos for menor que o valor final, o pagamento será reiniciado.
        {
            printf("\n\nO SOMATÓRIO DOS VALORES PAGO PELO CLIENTE É MENOR QUE O VALOR TOTAL DA COMPRA!\n\n\nREALIZE O PAGAMENTO NOVAMENTE!\n");

            somaDosPagamentos = 0;


           for (int i = 0; i < qty_pagar_cliente; i++)
           {
            printf("\n\nINSIRA O VALOR A SER PAGO NO: %s", formas_de_pagamento_do_cliente_str[i]);  //Pedindo novamente ao consumidor quanto ele irá pagar em cada uma das formas de pagamento escolhidas
            scanf("%f", &matrizSomaDosPagamentos[i]);

            somaDosPagamentos += matrizSomaDosPagamentos[i];

           }
        }

        if(somaDosPagamentos==valorFinalDaCompra)    //Assim que o valor pago for o correto, o display de confirmação da transação será mostrado.
        {

            printf("\n\n\n");

            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

            printf("\n\n\n");

            printf("PAGAMENTO REALIZADO COM SUCESSO!\n\n\nAGRADECEMOS PELA PREFERÊNCIA!");

            printf("\n\n\n");

            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
        }

        else if(somaDosPagamentos>valorFinalDaCompra)   //Condicional para caso o cliente pague mais do que ele deveria. Nesse caso o display irá mostrar quanto ele deverá receber de troco,
        {                                               //juntamente com o display de transação aprovada
            troco = somaDosPagamentos-valorFinalDaCompra;

            printf("\n\nO CLIENTE DEVE RECEBER %.2f REAIS DE TROCO.", troco);     //Valor que o cliente deverá receber de troco

            printf("\n\n\n");

            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

            printf("\n\n\n");

            printf("PAGAMENTO REALIZADO COM SUCESSO!\n\n\nAGRADECEMOS PELA PREFERÊNCIA!");

            printf("\n\n\n");

            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");


        }

    }

    else if(somaDosPagamentos>valorFinalDaCompra)   //Condicional para caso o cliente pague mais do que ele deveria. Nesse caso o display irá mostrar quanto ele deverá receber de troco,
    {                                               //juntamente com o display de transação aprovada
        troco = somaDosPagamentos-valorFinalDaCompra;

        printf("\n\nO CLIENTE DEVE RECEBER %.2f REAIS DE TROCO.", troco);

        printf("\n\n\n");

        printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");

        printf("\n\n\n");

        printf("PAGAMENTO REALIZADO COM SUCESSO!\n\n\nAGRADECEMOS PELA PREFERÊNCIA!");

        printf("\n\n\n");

        printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");


    }

    //Início do processo de impressão do comprovante de compra
    
                
    printf("\n\nCódigo do produto\tNome do produto \tValor unit.\tQuantidade\tValor total do produto\n");  //A partir dos nomes e dos valores salvos anteriormente,
                                                                                                           //será mostrado o código, nome, quantidade, valor total e valor final da compra
    

    int y;
    for(y=0;y<qtd_tipo_produtos;y++){
        printf("\t %.0f \t\t %s \t\t %.2f \t\t %.0f \t\t    %.2f \n", lista_compra[y][1], lista_compra_nomes[y], lista_compra[y][2], lista_compra[y][3], lista_compra[y][4]); //Esse printf possui algum bug de formatação, possivelmente atrelado ao %s, onde a 
    }                                                                                                                                                                         //primeira linha fica sempre desalinhada em comparação com as seguintes     

    
    for (int i = 0; i < qty_pagar_cliente; i++) {
        printf("\n\n\nCodigo do %s%d \nValor: %.2f \t",ptr_formas_de_pagamento_do_cliente_str[i], ptr_numero_pag[i],matrizSomaDosPagamentos[i]);  //Mostrando quais foram as formas de pagamento escolhidas pelo consumidor
    }


    printf("\n\nValor total da compra: %.2f", valorFinalDaCompra);  //Mostrando, agora no comprovante de compra, o valor final da compra


    return 0;
}