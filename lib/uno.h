#ifndef UNO_H
#define UNO_H

typedef struct
{
	int id;
	char tipo[10];
	char cor[10];
	char valor[10];
}Carta; //Struct para as variáveis relacionadas as cartas.

typedef struct
{
	int num_cartas;
	Carta disponiveis[30];
	Carta mao[30]; 
}Jogador; // Struct para a variável jogadores.

int ler_cartas(int, Carta[]);
void ler_regras();
void passar_cartas_monte(int, Carta[], Carta[]);
void carta_recebe_carta(int, int, Carta[], Carta[]);
void carta_recebe_jogador_disponiveis(int, int, Carta[], Jogador[]);
void jogador_recebe_carta(int, int, int, Carta[], Jogador[]);
void jogador_disponiveis_recebe_jogador_mao(int, int, int, Jogador[]);
void diminuir_mao(int, int, Jogador[]);
void continuar();
void tela_anterior(Carta[], Jogador[]);
void mensagem_inicial(int, Jogador[]);
void mensagem_carta_jogada(int, Carta[], Jogador[]);
void mensagem_carta_monte(int, Jogador[]);
void mensagem_carta_jogada_monte(int, Carta[], Jogador[]);
void coringa(int, Carta[], Jogador[]);
void pular(int);
void uno_ou_vencedor(int, int***, Jogador[]);
int qtd_comprar(int, int***, int***, Carta[], Carta[], Jogador[]);
int proximo_inverter(int, int);
void embaralhar_cartas(int, Carta[]);
int distribuir_cartas_jogadores(int, Carta[], Jogador[]);
void passar_descarte_para_monte(int***, int ***, Carta[], Carta[]);
void pegar_monte(int, int**, int**, Carta[], Carta[], Jogador[]);
void passar_vez(int, int**, int**, int**, Carta[], Carta[], Carta[], Jogador[]);
void final_jogada(int, int**, int**, int**, int**, int**, int**, int**, Carta[], Carta[], Carta[], Jogador[]);
void finalizar_jogar_carta(int, int***, Carta[], Jogador[]);
void escolher_carta(int, int, int***, Carta[], Carta[], Jogador[]);
void jogar_carta(int, int, int***, Carta[], Carta[], Jogador[]);
void jogada(int, int, int**, Carta[], Carta[], Jogador[]);
int cartas_disponiveis(int, int**, Carta[], Jogador[]);
void acao_jogador(int, int*, int*, int*, int*, int*, int*, int*, Jogador[], Carta[], Carta[], Carta[]);
void primeira_jogada(int, int*, Carta[], Carta[], Jogador[]);
void partida(int, int, int, Carta[], Carta[], Carta[], Jogador[]);

#endif