#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"uno.h"

int ler_cartas(int qtd_lidas, Carta cartas[])
{
	// Carrega os dados das cartas a partir do arquivo Cartas.txt.
	qtd_lidas = 0;
	int i;
	char linha[80];
	
	FILE *fcartas;
	fcartas = fopen("Cartas.txt", "r");
	
	for(i=0; i<2; i++)
		fgets(linha, 80, fcartas);		
	
	while(fscanf(fcartas, "%i| %[^|]| %[^|]| %[^|]|\n", &cartas[qtd_lidas].id, cartas[qtd_lidas].tipo, cartas[qtd_lidas].cor, cartas[qtd_lidas].valor) != EOF)
		qtd_lidas++; 
	
	fclose(fcartas);
	return qtd_lidas;
}

void ler_regras()
{
	// Lê o texto do arquivo Regras e sobre o jogo.txt, e o exibe na tela.
	char linha[120];
	
	FILE *fregras;
	fregras = fopen("Regras e sobre o jogo.txt", "r");	
	
	while(fgets(linha, 120, fregras))
		printf("%s", linha);
		
	fclose(fregras);
	
	printf("\n\nPressione Enter para retornar ao menu.");
}

void passar_cartas_monte(int n, Carta monte[], Carta cartas[])
{
	// Após distribuir as cartas para os jogadores, passa o restante para o monte.
	int j;
	for(j=0; j<n+1; j++)
	{
		monte[j].id = cartas[j].id;
  		strcpy(monte[j].tipo, cartas[j].tipo);
  		strcpy(monte[j].cor, cartas[j].cor);
  		strcpy(monte[j].valor, cartas[j].valor);
	}
}

void carta_recebe_carta(int i, int j, Carta carta_1[], Carta carta_2[])
{
	// Passa os dados de uma carta de um vetor Carta para outro.
	carta_1[i].id = carta_2[j].id;
  	strcpy(carta_1[i].tipo, carta_2[j].tipo);
  	strcpy(carta_1[i].cor, carta_2[j].cor);
  	strcpy(carta_1[i].valor, carta_2[j].valor);
}

void carta_recebe_jogador_disponiveis(int i, int j, Carta carta_atual[], Jogador jogadores[])
{
	// Passa para o vetor carta_atual a carta escolhida pelo jogador.
	carta_atual[0].id = jogadores[i].disponiveis[j].id;
	strcpy(carta_atual[0].tipo, jogadores[i].disponiveis[j].tipo);
	strcpy(carta_atual[0].cor, jogadores[i].disponiveis[j].cor);
	strcpy(carta_atual[0].valor, jogadores[i].disponiveis[j].valor);
}

void jogador_recebe_carta(int i, int j, int k, Carta cartas[], Jogador jogadores[])
{
	// Passa a carta no topo do Monte para a mão do jogador.
	jogadores[i].mao[j].id = cartas[k].id;
	strcpy(jogadores[i].mao[j].tipo, cartas[k].tipo);
	strcpy(jogadores[i].mao[j].cor, cartas[k].cor);
	strcpy(jogadores[i].mao[j].valor, cartas[k].valor);
}

void jogador_disponiveis_recebe_jogador_mao(int i, int j, int k, Jogador jogadores[])
{
	// Passa para o vetor Cartas Disponiveis as cartas que o jogador pode jogar na sua vez.
	jogadores[i].disponiveis[j].id = jogadores[i].mao[k].id;
	strcpy(jogadores[i].disponiveis[j].tipo, jogadores[i].mao[k].tipo);
	strcpy(jogadores[i].disponiveis[j].cor, jogadores[i].mao[k].cor);
	strcpy(jogadores[i].disponiveis[j].valor, jogadores[i].mao[k].valor);
}

void diminuir_mao(int i, int cart, Jogador jogadores[])
{
	// "Tira" a carta jogada da mão do jogador, deslocando para a direita as cartas que estavam a sua esquerda no vetor.
	int j;
	for(j=cart; j<jogadores[i].num_cartas; j++)
	{
		jogadores[i].mao[j].id = jogadores[i].mao[j+1].id;
		strcpy(jogadores[i].mao[j].tipo, jogadores[i].mao[j+1].tipo);
		strcpy(jogadores[i].mao[j].cor, jogadores[i].mao[j+1].cor);
		strcpy(jogadores[i].mao[j].valor, jogadores[i].mao[j+1].valor);
	}
}

void continuar() 
{
	// "Pausa" o código a cada ação executada, para que o programa não tente rodar tudo de uma vez.
	fflush(stdin);
	getchar();
}

void tela_anterior(Carta carta_atual[], Jogador jogadores[])
{
	// Mostra as cartas que o Usuário recebeu na distribuição antes do inicio da partida.
	int j;
	printf("Cartas embaralhadas e distribuidas para os jogadores.\n\nVoce recebeu as seguintes cartas:\n");
	for(j=0; j<7; j++)
		printf("%s %s\n", jogadores[3].mao[j].valor, jogadores[3].mao[j].cor);			
	printf("\nA carta que vai comecar a partida e um %s %s.\n", carta_atual[0].valor, carta_atual[0].cor);
	printf("\n> Pressione Enter ao final de cada jogada para executar a proxima.\n");
	printf("\nPressione Enter para iniciar a partida.");
	continuar();
	system("cls");					
}

void mensagem_inicial(int i, Jogador jogadores[])
{
	// Mostra as cartas que o Usuário tem em sua mão na sua vez, antes de jogar.
	int k;
	printf("\nVoce tem as seguintes cartas em sua mao:\n");		
	for(k=0; k<jogadores[i].num_cartas; k++)
		printf("%s %s\n", jogadores[i].mao[k].valor, jogadores[i].mao[k].cor);
}

void mensagem_carta_jogada(int i, Carta carta_atual[], Jogador jogadores[])
{
	// Mostra a carta que os jogadores jogaram, e no caso do Usuário, as que restaram em sua mão.	
	int k;
	if(i != 3)
		printf("O jogador %i jogou um %s %s.\n", i+1, carta_atual[0].valor, carta_atual[0].cor);				
	else
	{
		printf("Voce jogou um %s %s.\n", carta_atual[0].valor, carta_atual[0].cor);	
		if(jogadores[i].num_cartas != 0)
		{				
			printf("\nAgora voce tem as seguintes cartas em sua mao:\n");		
			for(k=0; k<jogadores[i].num_cartas; k++)
			printf("%s %s\n", jogadores[i].mao[k].valor, jogadores[i].mao[k].cor);
		}
	}			
}

void mensagem_carta_monte(int i, Jogador jogadores[])
{
	/* Informa que os jogadores ficaram com a carta que pegaram do Monte na rodada; no  
	caso do Usuário, mostra a carta que ele pegou, e as que tem em sua mão agora. */
	int k;
	if(i != 3)
		printf("\nO jogador %i nao pode jogar nenhuma carta nessa rodada.\nEle pegou uma carta do Monte.\n", i+1);
	else
	{
		int j = jogadores[i].num_cartas - 1;
		printf("\nVoce nao pode jogar nenhuma carta nessa rodada.\nVoce pegou um %s %s do Monte.\n", jogadores[i].mao[j].valor, jogadores[i].mao[j].cor);
		printf("\nAgora voce tem as seguintes cartas em sua mao:\n");		
		for(k=0; k<jogadores[i].num_cartas; k++)
			printf("%s %s\n", jogadores[i].mao[k].valor, jogadores[i].mao[k].cor);
	}				
}

void mensagem_carta_jogada_monte(int i, Carta carta_atual[], Jogador jogadores[])
{
	/* Informa que os jogadores jogaram imediatamente a carta que pegaram do Monte; no caso 
	do Usuário, mostra a carta que ele pegou (e jogou), e as que tem em sua mão agora. */
	int k;
	if(i != 3)
		printf("O jogador %i pegou uma carta %s %s do Monte e a jogou.\n", i+1, carta_atual[0].valor, carta_atual[0].cor);				
	else
	{
		printf("Voce pegou uma carta %s %s do Monte e a jogou.\n", carta_atual[0].valor, carta_atual[0].cor);	
		if(jogadores[i].num_cartas != 0)
		{				
			printf("\nAgora voce tem as seguintes cartas em sua mao:\n");		
			for(k=0; k<jogadores[i].num_cartas; k++)
			printf("%s %s\n", jogadores[i].mao[k].valor, jogadores[i].mao[k].cor);
		}
	}			
}

void coringa(int i, Carta carta_atual[], Jogador jogadores[])
{
	// Implementa a função da carta Coringa.
	srand(time(NULL)); // Define seed de acordo com data e hora da máquina.
	int j, k, l, m, cor_disp = 0, opcao = 0, sel = 0, tem_mao_esp[4] = {0, 0, 0, 0}, tem_mao = 0;
	char cores[4][10] = {"Amarelo", "Azul", "Verde", "Vermelho"}, cores_aux[4][10];

	/* cores: contem as cores tradicionais das cartas.
	   cores_aux: recebe as cores que podem ser jogadas naquele instante.
	   tem_mao: sinaliza se o jogador tem alguma carta colorida na mão dele.
	   tem_mao_esp: sinaliza quais cores em especifico o jogador tem.
	*/

	j = jogadores[i].num_cartas;

	for(k=0; k<4; k++)
	{
		for(l=0; l<j; l++)
		{
			if(strcmp(jogadores[i].mao[l].cor, cores[k]) == 0)
			{
				tem_mao_esp[k] = 1;
				tem_mao = 1;
			}
		}	
		/* Percorre a mão do jogador analisando as cores das cartas dele; ao encontrar qualquer cor,
		define o marcador tem_mao para 1, e a cada cor especifica encontrada, define o elemento
		na posição correspondente a ela no vetor tem_mao_esp para 1. */	
	}

	if(tem_mao == 1) // Se encontrar qualquer cor na mão dele
	{
		for(k=0; k<4; k++)
		{
			if(tem_mao_esp[k] == 1)
			{
				strcpy(cores_aux[cor_disp], cores[k]);
				cor_disp++;
			}
			// Passa as cores encontradas para o vetor cores_aux, para que o jogador escolha apenas entre elas.	
		}	
	}
	else // Se não tiver nenhuma carta colorida
	{
		for(k=0; k<4; k++)
		{
			strcpy(cores_aux[cor_disp], cores[k]);
			cor_disp++;	
		}
		// Passa todas as cores para o vetor cores_aux, para que o jogador possa escolher qualquer uma delas.
	}

if(i !=3) // Se for qualquer um dos outros jogadores
{
	m = rand() % cor_disp;
	printf("Ele escolheu a cor %s\n", cores_aux[m]);
	// Escolhe a cor para a próxima carta aleatóriamente dentre as cores no vetor cores_aux.
}
else // Se for o Usuário
{
	if(cor_disp != 1) // Caso possa jogar mais de uma cor
	{
		// Menu para selecionar a cor que deseja escolher.
		printf("\n");
		for(k=0; k<cor_disp; k++)
		printf("%i - %s \n", k+1, cores_aux[k]);
		printf("Escolha uma cor para continuar a partida digitando o numero correspondente: ");
		scanf("%i", &opcao);
		printf("\n");
		
		while(sel == 0)
		{
			if(opcao <= cor_disp)
			{
				for(k=0; k<cor_disp; k++)
				{
					if(opcao-1 == k)
					{
						m = k;
						sel = 1;
					}
					// Procura o indice da cor selecionada.
				}
			}
			else // Caso digite um valor invalido.
			{
				printf("Por favor, digite um valor valido: "); 
				scanf("%i", &opcao);
				printf("\n");
			}
		}
	}
	else // Se puder jogar apenas uma cor
		m = 0;	
	printf("Voce escolheu a cor %s\n", cores_aux[m]); // A escolhe automáticamente.
}
	strcpy(carta_atual[1].cor, cores_aux[m]); // Passa a cor escolhida para o campo cor do elemento 1 do vetor carta_atual.
}

void pular(int i)
{
	// Informa que o próximo jogador não poderá jogar na rodada, caso tenha "recebido" uma carta Pular.
	if(i!=3)
		printf("\nO jogador %i nao joga nessa rodada.\n", i+1);
	else
		printf("\nVoce nao joga nessa rodada.\n", i+1);
}

void uno_ou_vencedor(int i, int ***m_fim, Jogador jogadores[])
{
	// Informa quando o jogador tem apenas uma carta em sua mão, ou então quando vence a partida.
	if(jogadores[i].num_cartas == 1)
	{
		if(i != 3)
			printf("\nUNO! O Jogador %i tem apenas uma carta em sua mao!\n", i+1);
		else
			printf("\nUNO! Voce tem apenas uma carta em sua mao!\n");
	}
	else
	{
		if(i != 3)
			printf("\nFim de partida! O Jogador %i e o grande vencedor!\n", i+1);
		else
			printf("\nFim de partida! Voce e o grande vencedor!\n");
	
		***m_fim = 1; // Sinaliza que a partida acabou.
	}
}

int qtd_comprar(int i, int ***m_monte, int ***m_desc, Carta carta_atual[], Carta monte[], Jogador jogadores[])
{
	// Retorna quantas cartas o próximo jogador terá que pegar do Monte, ao ser jogada uma carta +2 ou +4.
	int qtd_cart;
	
	if(strcmp(carta_atual[0].valor,"+2") == 0)
	{
		if(i != 3)
			printf("\nO jogador %i pegou duas cartas do Monte.\n", i+1);
		else
			printf("\nVoce pegou as seguintes cartas do Monte:\n");
		qtd_cart = 2;
	}
	else
	{
		if(i != 3)
			printf("\nO jogador %i pegou quatro cartas do Monte.\n", i+1);
		else
			printf("\nVoce pegou as seguintes cartas do Monte:\n");
		qtd_cart = 4;
	}
	return qtd_cart;
}

int proximo_inverter(int pos_inverter, int m_inverter)
{
	// Define quem será o próximo jogador quando uma carta Inverter é jogada.
	int i;
	if(m_inverter == 1) // Se a ordem atual de jogo for crescente (indice 0 a 3)
	{
		if(pos_inverter == 0)
			i = 3;
		else if(pos_inverter == 1)
			i = 0;
		else if(pos_inverter == 2)
			i = 1;
		else if(pos_inverter == 3)
			i = 2;		 
	}
	else // Se a ordem atual de jogo for decrescente (indice 3 a 0)
	{
		if(pos_inverter == 0)
			i = 1;
		else if(pos_inverter == 1)
			i = 2;
		else if(pos_inverter == 2)
			i = 3;
		else if(pos_inverter == 3)
			i = 0;
	}
	return i;
}

void embaralhar_cartas(int n, Carta cartas[])
{
	// "Embaralha" as cartas no inicio da partida.
	srand(time(NULL));
	
	int i, aleat;
	Carta aux[1]; // Variável para auxiliar nas trocas de posição.
	
	for(i=0; i<n; i++) 
	{
		carta_recebe_carta(0, i, aux, cartas); 
		aleat = rand() % n;
		carta_recebe_carta(i, aleat, cartas, cartas);
		carta_recebe_carta(aleat, 0, cartas, aux);
		// Troca cada carta de lugar com outra em uma posição do vetor escolhida aleatóriamente.
	}
}

int distribuir_cartas_jogadores(int n, Carta cartas[], Jogador jogadores[])
{
	// Após embaralhar as cartas, as distribui para cada jogador, retornando a quantidade de cartas que restaram.
	int i, j;
	for(i=0; i<4; i++)
	{
		jogadores[i].num_cartas = 0;
		for(j=0; j<7; j++)
		{
			jogador_recebe_carta(i, j, n, cartas, jogadores); 		
			jogadores[i].num_cartas++;
  			n--;
		}
	}
	return n;
}

void passar_descarte_para_monte(int ***m_monte, int ***m_desc, Carta monte[], Carta descarte[])
{
	// Passa as cartas do Descarte para o Monte.
	int j, dc = ***m_desc;
	for(j=0; j<dc; j++)
	{
		int car_mon = ***m_monte +1;
		carta_recebe_carta(car_mon, j, monte, descarte);
		***m_desc = ***m_desc - 1;
 		***m_monte = ***m_monte + 1;
	}
}

void pegar_monte(int i, int **m_monte, int **m_desc, Carta descarte[], Carta monte[], Jogador jogadores[])
{
	// Passa a carta no topo do Monte para a mão do jogador.
	int j = jogadores[i].num_cartas;
	jogadores[i].num_cartas++;
	int k = **m_monte;
	jogador_recebe_carta(i, j, k, monte, jogadores);
	**m_monte = **m_monte - 1;

	if(**m_monte <= 1) // Se restarem poucas cartas no Monte ao final
	{
		passar_descarte_para_monte(&m_monte, &m_desc, monte, descarte);
		int mon = **m_monte+1;
		embaralhar_cartas(mon, monte); // Reembaralha o Monte após receber as cartas do Descarte.
	}
}

void passar_vez(int i, int **m_monte, int **m_desc, int **m_passar_vez, Carta carta_atual[], Carta monte[], Carta descarte[], Jogador jogadores[])
{
	/* Para quando o jogador "recebe" uma carta Pular, +2 ou +4 e fica sem jogar na rodada.
	Analisa qual delas foi jogada, e executa suas respectivas funções.*/
	int j, k, l;
	if(strcmp(carta_atual[0].valor, "Pular") == 0) // Se foi uma carta Pular
		pular(i);
	else if(strcmp(carta_atual[0].valor, "+4") == 0 || strcmp(carta_atual[0].valor, "+2") == 0) // Se foi uma carta +2 ou +4
	{
		if(**m_monte <= 4) // Caso possa não haver cartas o suficiente no Monte antes do jogador pega-las
		{
			passar_descarte_para_monte(&m_monte, &m_desc, monte, descarte);
			int mon = **m_monte+1;
			embaralhar_cartas(mon, monte);
		}
		int qtd_cart = qtd_comprar(i, &m_monte, &m_desc, carta_atual, monte, jogadores); // Vê quantas cartas o jogador irá pegar.
			
		for(l=0; l<qtd_cart; l++) // Pega do Monte a quantidade de cartas correspondente a carta jogada.
		{
			j = jogadores[i].num_cartas;
			jogadores[i].num_cartas++;
			k = **m_monte;
			jogador_recebe_carta(i, j, k, monte, jogadores);
			**m_monte = **m_monte - 1;
			if(i == 3)
				printf("%s %s\n",jogadores[i].mao[j].valor, jogadores[i].mao[j].cor); // Para o Usuário, mostra as cartas que ele pegou.
		}		
	}
	**m_passar_vez = 0; // Muda marcador para que o jogador seguinte possa jogar normalmente.
}

void final_jogada(int i, int **m_monte, int **m_desc, int **m_fim, int **m_passar_vez, int **m_coringa, int **m_inverter, int **pos_invert, Carta carta_atual[], Carta descarte[], Carta monte[], Jogador jogadores[])
{
	// Verifica a carta jogada e as cartas na mão do jogador ao final de sua vez.
	if(jogadores[i].num_cartas <= 1) // Se tiver apenas uma (ou então não tiver mais nenhuma) carta
		uno_ou_vencedor(i, &m_fim, jogadores);
	
	if(strcmp(carta_atual[0].tipo, "Acao") == 0) // Se a carta jogada for de ação (Pular, Inverter, +2, Coringa ou +4)
	{
		if(strcmp(carta_atual[0].cor, "Especial") == 0) // Se for uma carta de cor Especial (Coringa ou +4)
		{
			coringa(i, carta_atual, jogadores); // Executa função para que o jogador selecione uma cor para continuar a partida.
			**m_coringa = 1; // Define marcador para que a próxima carta jogada seja da cor escolhida.
			if(strcmp(carta_atual[0].valor, "+4") == 0) // Se for uma +4
				**m_passar_vez = 1; // Define marcador para que o próximo jogador fique sem jogar (e tenha que pegar as quatro cartas do monte).
		}
		else if(strcmp(carta_atual[0].valor, "Inverter") == 0) // Se for uma carta inverter
		{
			if(**m_inverter == 0)
				**m_inverter = 1;
			else
				**m_inverter = 0; 
			// Define o novo valor do marcador conforme a ordem atual dos jogadores, para determinar a nova ordem.	
			**pos_invert = i; // Marca o jogador que jogou a carta.
			int j = proximo_inverter(**pos_invert, **m_inverter);
			if(**m_fim == 0) // Se carta jogada não tiver sido a última
			{
				if(j != 3)
					printf("O proximo a jogar agora sera o jogador %i.\n", j+1);
				else
					printf("Voce sera o proximo a jogar agora.\n");
				// Mostra quem será o próximo a jogar.
			}
				
		}	
		else // Se for uma das outras carta de ação (Pular ou +2)
			**m_passar_vez = 1;	// Apenas define marcador.
	}	
}

void finalizar_jogar_carta(int i, int ***m_desc, Carta carta_atual[], Jogador jogadores[])
{
	// Encontra a carta jogada para "tirá-la" da mão do jogador.
	int j;
	int cart;
	for(j=0; j<jogadores[i].num_cartas; j++)
	{
		if(jogadores[i].mao[j].id == carta_atual[0].id)
			cart = j;
	}

	diminuir_mao(i, cart, jogadores);
	jogadores[i].num_cartas--;
	
	***m_desc = ***m_desc + 1;
}

void escolher_carta(int i, int d, int ***m_desc, Carta carta_atual[], Carta descarte[], Jogador jogadores[])
{
	// Menu para o Usuário escolher a carta que irá jogar.
	int opcao = 0, sel = 0, j, desc = ***m_desc;
	
	printf("\nVoce pode jogar as seguintes cartas nessa rodada:\n");
	for(j=0; j<d; j++)
	printf("%i - %s %s\n", j+1, jogadores[i].disponiveis[j].valor, jogadores[i].disponiveis[j].cor);
	printf("Escolha uma carta digitando o numero correspondente: ");
	scanf("%i", &opcao);
	
	while(sel == 0)
	{
		if(opcao <= d)
		{
			for(j=0; j<d; j++) 
			{
				// Procura o indice da carta selecionada
				if(opcao-1 == j) // Ao encontrá-la
				{
					carta_recebe_carta(desc, 0, descarte, carta_atual); // Passa a Carta Atual para o Descarte.
					carta_recebe_jogador_disponiveis(i, j, carta_atual, jogadores); // "Joga" a carta escolhida, fazendo dela a nova Carta Atual.
					sel = 1;
				}		
			}
		}
		else // Caso digite um valor inválido
		{
			printf("\nPor favor, digite um valor valido: "); 
			scanf("%i", &opcao);
		}
	}		
}

void jogar_carta(int i, int d, int ***m_desc, Carta carta_atual[], Carta descarte[], Jogador jogadores[]) 
{
	// Escolhe aleatóriamente uma carta do vetor Cartas Disponiveis e a joga.
	int desc, aleat;
	desc = ***m_desc;
	srand(time(NULL));
	aleat = rand() % d;
	carta_recebe_carta(desc, 0, descarte, carta_atual);
	carta_recebe_jogador_disponiveis(i, aleat, carta_atual, jogadores);	
}

void jogada(int i, int d, int **m_desc, Carta carta_atual[], Carta descarte[], Jogador jogadores[])
{
	// Reune todas as funções para quando um jogador joga uma carta.
	if(i == 3) // Se for o Usuário
	{
		if(d == 1) // Se puder jogar apenas uma carta
			jogar_carta(i, d, &m_desc, carta_atual, descarte, jogadores); // A joga automáticamente.
		else // Se puder jogar mais de uma
			escolher_carta(i, d, &m_desc, carta_atual, descarte, jogadores); // Ele escolhe qual irá jogar.	
	}
	else // Se for um dos outros jogadores
		jogar_carta(i, d, &m_desc, carta_atual, descarte, jogadores); // Escolhe aleatóriamente uma carta para jogar.
	finalizar_jogar_carta(i, &m_desc, carta_atual, jogadores);
	printf("\n");
}

int cartas_disponiveis(int i, int **m_coringa, Carta carta_atual[], Jogador jogadores[])
{
	// Procura na mão do jogador as cartas que ele pode jogar na rodada.
	int d = 0, j;
	Carta aux[1]; // Variável que recebe a cor que a carta deverá ter para poder ser jogada.
	if(**m_coringa == 0) // Se a Carta Atual não for uma Coringa
	{
		strcpy(aux[0].cor, carta_atual[0].cor);
		strcpy(aux[0].valor, carta_atual[0].valor);
		// Função vai procurar por cartas com mesma cor ou valor que a Carta Atual.
	}
	else // Se for uma Coringa
	{
		strcpy(aux[0].cor, carta_atual[1].cor);
		// Função vai procurar por cartas com a cor escolhida pelo jogador que jogou a carta Coringa.
	}
	for(j=0; j<jogadores[i].num_cartas; j++)
	{
		// Percorre a mão do jogador.
		if(strcmp(jogadores[i].mao[j].cor, aux[0].cor) == 0 || strcmp(jogadores[i].mao[j].valor, aux[0].valor) == 0 || strcmp(jogadores[i].mao[j].valor, "Coringa") == 0)
		{
			// Se carta tiver a mesma cor, valor, ou for uma carta Coringa
			jogador_disponiveis_recebe_jogador_mao(i, d, j, jogadores); // Passa carta para o vetor Cartas Disponiveis.
			d++;
		}
	}
	if(d == 0) // Se não encontrar nenhuma carta com essas condições
	{
		for(j=0; j<jogadores[i].num_cartas; j++)
		{
			if(strcmp(jogadores[i].mao[j].valor, "+4") == 0) // Procura por alguma carta +4 que o jogador possa ter
			{
				jogador_disponiveis_recebe_jogador_mao(i, d, j, jogadores);
				d++;
			}
		}	
	}
	
	if(**m_coringa == 1 && d != 0) // Se Carta Atual for uma Coriga e o jogador puder jogar alguma carta
		**m_coringa = 0; // "Desativa" marcador para que o próximo jogador tenha que jogar uma carta com a cor/valor da que for jogada.
	return d; // Retorna quantas cartas o jogador pode jogar.
}

void acao_jogador(int i, int *m_fim, int *m_monte, int *m_desc, int *m_passar_vez, int *m_coringa, int *m_inverter, int *pos_invert, Jogador jogadores[], Carta carta_atual[], Carta monte[], Carta descarte[])
{
	// As ações que os jogadores podem tomar em sua vez.
	int d;
	printf("Jogador %i\n", i+1);
	if(*m_passar_vez == 0) // Se jogador puder jogar na rodada
	{
		d = cartas_disponiveis(i, &m_coringa, carta_atual, jogadores); // Procura as cartas que ele pode jogar (e quantas).
		if (d != 0) // Se puder jogar alguma
		{
			if(i == 3)
				mensagem_inicial(i, jogadores);
			jogada(i, d, &m_desc, carta_atual, descarte, jogadores); 
			mensagem_carta_jogada(i, carta_atual, jogadores);
			final_jogada(i, &m_monte, &m_desc, &m_fim, &m_passar_vez, &m_coringa, &m_inverter, &pos_invert, carta_atual, descarte, monte, jogadores);
			// Executa as funções para jogar a carta escolhida.								
		}		
		else // Se não puder jogar nenhuma
		{
			pegar_monte(i, &m_monte, &m_desc, descarte, monte, jogadores);
			d = cartas_disponiveis(i, &m_coringa, carta_atual, jogadores);
			// Pega uma carta do Monte, e analisa se ela pode ser jogada imediatamente.
			if(d == 0) // Se não puder ser jogada
				mensagem_carta_monte(i, jogadores); // Fica com ela.
			else // Se puder
			{
				jogada(i, d, &m_desc, carta_atual, descarte, jogadores);
				mensagem_carta_jogada_monte(i, carta_atual, jogadores);
				final_jogada(i, &m_monte, &m_desc, &m_fim, &m_passar_vez, &m_coringa, &m_inverter, &pos_invert, carta_atual, descarte, monte, jogadores);
				// Joga a carta.	
			}								
		}
	}
	else // Se não puder jogar na rodada (tiver "recebido" uma carta Pular, +2 ou +4)
	{
		if(*m_fim == 0) // Caso partida não tenha acabado
			passar_vez(i, &m_monte, &m_desc, &m_passar_vez, carta_atual, monte, descarte, jogadores); 
			// Determina qual dessas cartas foi jogada para executar sua função.
	}
	if(i != 3 && *m_fim == 0 && jogadores[i].num_cartas > 1)
		printf("\nCartas na mao: %i\n", jogadores[i].num_cartas);
		// Mostra quantas cartas os demais jogadores tem em suas mãos ao final de suas jogadas.				
	printf("-------------------------------");	
}

void primeira_jogada(int i, int *m_monte, Carta carta_atual[], Carta monte[], Jogador jogadores[])
{
	// Pega a carta no topo do Monte para dar inicio a partida
	int m = *m_monte, com_top = 0;	
	while(com_top == 0)
	{
		if(strcmp(monte[m].tipo, "Acao") == 0)
			embaralhar_cartas(m+1, monte); // Se for uma carta de ação, o Monte será reembaralhado até que a carta no topo seja uma carta Comum.
		else
			com_top = 1;	
	}
	carta_recebe_carta(0, m, carta_atual, monte); // Passa a carta em questão para a Carta Atual.
	*m_monte = *m_monte - 1;
	
	tela_anterior(carta_atual, jogadores);
}

void partida(int i, int m_monte, int m_desc, Carta carta_atual[], Carta monte[], Carta descarte[], Jogador jogadores[])
{
	// A função que executará toda a partida.
	int j, pos_invert, m_fim = 0, m_passar_vez = 0, m_coringa = 0, m_inverter = 0, rod = 1;
	// Marcadores para as cartas de ação, a quantidade de rodadas disputadas, e o final da partida.
	
	primeira_jogada(i, &m_monte, carta_atual, monte, jogadores); // Pega a carta no topo do monte para iniciar a partida.
	
	while(m_fim == 0) // Inicia a partida, executando todas as ações e rodadas até última carta ser jogada.
	{
		if(m_inverter == 0) // Se a ordem de jogo for crescente (indice 0 a 3)
		{
			if(i != 0) // Se o próximo a jogar não for o Jogador 1 (indice 0)
			{
				for(j=i; j<4; j++)
				{
					if(m_fim == 0 && m_inverter == 0) 
					{
						acao_jogador(j, &m_fim, &m_monte, &m_desc, &m_passar_vez, &m_coringa, &m_inverter, &pos_invert, jogadores, carta_atual, monte, descarte);	
						continuar();
						// Tenta completar a rodada, indo até o Jogador 3.				
					}
				}
				system("cls");
				rod++;
			}				
			while(m_fim == 0 && m_inverter == 0)
			{
				printf("----------<Rodada %.2i>----------\n", rod);
				for(i=0; i<4; i++)
				{
					if(m_fim == 0 && m_inverter == 0) 
					{
						acao_jogador(i, &m_fim, &m_monte, &m_desc, &m_passar_vez, &m_coringa, &m_inverter, &pos_invert, jogadores, carta_atual, monte, descarte);
						continuar();				
					}
					// Executa cada rodada na ordem crescente, até carta Inverter ser jogada ou a partida acabar.					
				}
				system("cls");
				if(m_inverter == 0)
					rod++;
			}	
			i = proximo_inverter(pos_invert, m_inverter); // Caso carta Inverter seja jogada, muda a ordem de jogo e define quem será o próximo a jogar.
		}
		else // Se a ordem de jogo for decrescente (indice 3 a 0)
		{
			if(i != 3) // Se o próximo a jogar não for o Usuário (indice 3)
			{
				for(j=i; j>= 0; j--)
				{
					if(m_fim == 0 && m_inverter == 1) 
					{
						acao_jogador(j, &m_fim, &m_monte, &m_desc, &m_passar_vez, &m_coringa, &m_inverter, &pos_invert, jogadores, carta_atual, monte, descarte );	
						continuar();
						// Tenta completar a rodada, indo até o Jogador 1.				
					}
				}
				system("cls");
				rod++;
			}					
			while(m_fim == 0 && m_inverter == 1)
			{
				printf("----------<Rodada %i>----------\n", rod);
				for(i=3; i>= 0; i--)
				{
					if(m_fim == 0 && m_inverter == 1) 
					{
						acao_jogador(i, &m_fim, &m_monte, &m_desc, &m_passar_vez, &m_coringa, &m_inverter, &pos_invert, jogadores, carta_atual, monte, descarte );	
						continuar();				
					}
					// Executa cada rodada na ordem decrescente, até uma nova carta Inverter ser jogada ou a partida acabar.
				}
				system("cls");
				if(m_inverter == 1)	
					rod++;
			}						
			i = proximo_inverter(pos_invert, m_inverter);		
		}		 	
	}
	printf("Partida finalizada.\nPressione Enter para retornar ao menu.");
	continuar();
	system("cls");
}