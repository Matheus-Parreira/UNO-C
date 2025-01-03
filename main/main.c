#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"..\lib\uno.h"

int main()
{
	int qtd_lidas, i = 0, m_monte, m_desc = 0, opcao = 0;
	Carta cartas[108], monte[108], descarte[108], carta_atual[2];
	Jogador jogadores[4];
	
	while(opcao != 3)
	{
		system("cls");
		printf("UNO-C\nO jogo de cartas, agora diretamente do terminal de seu computador!\n\nCriado por Matheus Henrique Parreira (@Matheus-Parreira no Github).\nDistribuido sob a licenca MIT\nVersao 1.0.0.\n");
		printf("\n1 - Iniciar partida\n2 - Regras e sobre o jogo\n3 - Sair\nSelecione uma opcao: ");
		scanf("%i", &opcao);
		
		system("cls");
		switch(opcao) 
		{
			case 1:
				qtd_lidas = ler_cartas(qtd_lidas, cartas);					
				embaralhar_cartas(qtd_lidas, cartas);				
				m_monte = qtd_lidas-1;	
				m_monte = distribuir_cartas_jogadores(m_monte, cartas, jogadores);
				passar_cartas_monte(m_monte, monte, cartas);
				
				partida(i, m_monte, m_desc, carta_atual, monte, descarte, jogadores);
			break;
			case 2:
				ler_regras();
				continuar();
			break;
			case 3:
				printf("Encerrando...\n");
				return 0;
			break;
			default:
				printf("Opcao invalida.\nPressione Enter para retornar ao menu.");
				continuar();
			break;
		}
	}			
}