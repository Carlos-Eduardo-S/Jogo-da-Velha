#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h> 

/*
*
* @author: Carlos Eduardo
* Jogo da Velha em C
*
*/

// Declara��o de um registro 
typedef struct {
	
	char nome[20];
	char simbolo;
	
}dados_jogadores;


void definicao_posicoes(char posicoes[3][3]);
void cadastro_jogadores(dados_jogadores *jogadores);
int tabuleiro(char posicoes[3][3], int exibicao_necessaria);
int jogada(char posicoes[3][3], int posicao_jogada,dados_jogadores *dados,int jogador);
int posicao_valida(char posicoes[3][3], int posi);
int verificacao_gahador(char posicoes[3][3]);

void limpar_buffer();
void limpa_tela();
void pause ();

int main() 
{
	setlocale (LC_ALL,"");
	
	int i,definicao_jogador=0, ganhou=0,numero_jogadas=0, jogada_valida, exibicao=1;
	dados_jogadores jogadores[2];
	char posicoes_tabuleiro[3][3];
	int posicao;
	
	definicao_posicoes(posicoes_tabuleiro);	
	
	cadastro_jogadores (jogadores);

	srand(time(NULL));
	
	definicao_jogador = rand()%2;
	
	while ((ganhou != 1) && numero_jogadas < 9)
	{
		
		limpa_tela();
		printf ("\t\t\t\t\t\t    Vez de %s\n\n\n\n\n\n",jogadores[definicao_jogador].nome);
		posicao = tabuleiro(posicoes_tabuleiro,exibicao);	
		
		jogada_valida = jogada(posicoes_tabuleiro, posicao,jogadores,definicao_jogador);
		
		// loop que ser� executado enquanto o usu�rio n�o digita uma op��o valida 
		while(jogada_valida != 1)
		{
			
			limpa_tela();
			printf ("\t\t\t\t\t\t    Vez de %s\n\n\n\n\n\n",jogadores[definicao_jogador].nome);
			posicao = tabuleiro(posicoes_tabuleiro,exibicao);	
			
			jogada_valida = jogada(posicoes_tabuleiro, posicao,jogadores,definicao_jogador);
		}	
		
		if (jogada_valida == 1)
		{
			
			numero_jogadas++;
			
		}
		
		ganhou = verificacao_gahador(posicoes_tabuleiro);
		
		// Teste que indicar� a vez dos jogadores 
		if (definicao_jogador == 0 && ganhou != 1)
		{
				
			definicao_jogador++;
				
		}else if (ganhou != 1)
		{
				
			definicao_jogador--;
				
		}
		limpa_tela();
		
	}
	
	
	if (ganhou == 1)
	{
		printf ("\n\n\n\t\t\t\t\t\t   PARAB�NS %s\n\n", jogadores[definicao_jogador].nome);
		exibicao = 0;
		tabuleiro(posicoes_tabuleiro,exibicao);
			
	}else 
	{
		
		printf ("\n\n\n\t\t\t\t\t\t       EMPATE!!\n\n\n");
		exibicao = 0;
		tabuleiro(posicoes_tabuleiro,exibicao);
		
	}

	pause();

	return 0;
}

// Fun��o que armazena os n�meros relativos a posi��o de jogada no tabuleiro 
void definicao_posicoes(char posicoes[3][3])
{
	  
	int i, j,k=0;
	
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			k++;
			
			// k+'0' transforma o n�mero inteiro num char
			posicoes[i][j] = k+'0'; 
			
		}
	}
}

// Procediemnto que cadastra os jogadores da partida 
void cadastro_jogadores(dados_jogadores *jogadores)
{
	
	int i;
	
	(jogadores + 0)->simbolo = 'x';
	(jogadores + 1)->simbolo = 'o';
	
	for (i=0; i<2; i++)
	{
		
		printf ("Digite o nome do %d� jogador: ",i+1);
		fgets ((jogadores + i)->nome,20,stdin);
		limpar_buffer();
		
	}
}

// Fun��o que exibe o tabuleiro para o usu�rio e retorna a posi��o digitada
int tabuleiro(char posicoes[3][3], int exibicao_necessaria)
{
	
	int jogada;
	
	
	printf ("\t\t\t\t\t          |              |           \n");
	printf ("\t\t\t\t\t     %c    |       %c      |	%c   \n",posicoes[0][0],posicoes[0][1],posicoes[0][2]);
	printf ("\t\t\t\t\t          |              |           \n");
	printf ("\t\t\t\t\t__________|______________|____________\n");
	printf ("\t\t\t\t\t          |              |           \n");
	printf ("\t\t\t\t\t     %c    |       %c      |	%c   \n",posicoes[1][0],posicoes[1][1],posicoes[1][2]);
	printf ("\t\t\t\t\t          |              |           \n");
	printf ("\t\t\t\t\t__________|______________|____________\n");
	printf ("\t\t\t\t\t          |              |           \n");
	printf ("\t\t\t\t\t          |              |           \n");
	printf ("\t\t\t\t\t     %c    |       %c      |	%c   \n",posicoes[2][0],posicoes[2][1],posicoes[2][2]);
	printf ("\t\t\t\t\t          |              |           \n");
	
	// Teste condicional parar saber se a impress�o � necessaria
	if (exibicao_necessaria == 1)
	{
		
		printf ("\n\n\nDigite em qual casa voc� quer colocar a pe�a: ");
		scanf ("%d",&jogada);
		limpar_buffer();
		
	}
	
	return jogada;
}

// Fun��o que salva o simbolo conrespoindente ao usu�rio (x ou o)
// na matriz na posic�o digitada pelo usu�rio
// OBS: a fun��o retorna se a posi��o digita � valida ou n�o 
int jogada(char posicoes[3][3], int posicao_jogada,dados_jogadores *dados,int jogador)
{
	
	int opcao_valida, teste;
	
	// Camamento da fun��o para saber se na posi��o digitada j� n�o est� com um simbolo dentro 
	teste = posicao_valida(posicoes,posicao_jogada);
	
	// teste para saber se a posi��o � valida
	// se n�o for ela atribuir� 10 a posi��o_jogada 
	// fazendo cair no default
	if (teste == 0)
	{
		
		posicao_jogada = 10;
		
	}
	
	switch (posicao_jogada)
	{
		
		case 1:
			
			posicoes[0][0] = (dados +jogador)->simbolo;
			opcao_valida = 1; 
			break;
			
		case 2:
			
			posicoes[0][1] = (dados +jogador)->simbolo;
			opcao_valida = 1;
			break;
		
		case 3:
			
			posicoes[0][2] = (dados +jogador)->simbolo;
			opcao_valida = 1;
			break;
		
		case 4:
			
			posicoes[1][0] = (dados +jogador)->simbolo;
			opcao_valida = 1;
			break;
		
		case 5:
			
			posicoes[1][1] = (dados +jogador)->simbolo;
			opcao_valida = 1;
			break;
		
		case 6:
			
			posicoes[1][2] = (dados +jogador)->simbolo;
			opcao_valida = 1;
			break;
		
		case 7:
			
			posicoes[2][0] = (dados +jogador)->simbolo;
			opcao_valida = 1;
			break;
		
		case 8:
			
			posicoes[2][1] = (dados +jogador)->simbolo;
			opcao_valida = 1;
			break;
		
		case 9:
			
			posicoes[2][2] = (dados +jogador)->simbolo;
			opcao_valida = 1;
			break;
		
		default:
			
			fflush (stdout);
			printf ("\n\n\t\t\t\t\t\t   POSI��O INV�LIDA!\n\n");
			opcao_valida = 0;
			break;	
	}
	
	pause ();
	
	return opcao_valida;
}

// Fun��o para saber se na posi��o digitada j� n�o est� com um simbolo dentro
// Retornar� 1 se a posi��o for valida e 0 se for invalida
int posicao_valida(char posicoes[3][3], int posi)
{
	
	int valida=1;
	
	switch (posi)
	{
		
		case 1:
			
			if (posicoes[0][0] == 'x' || posicoes[0][0] == 'o')
			{
				
				valida = 0;	
				
			} 
			break;
			
		case 2:
			
			if (posicoes[0][1] == 'x' || posicoes[0][1] == 'o')
			{
				
				valida = 0;	
				
			} 
			break;
		
		case 3:
			
			if (posicoes[0][2] == 'x' || posicoes[0][2] == 'o')
			{
				
				valida = 0;	
				
			} 
			break;
		
		case 4:
			
			if (posicoes[1][0] == 'x' || posicoes[1][0] == 'o')
			{
				
				valida = 0;	
				
			}
			break;
		
		case 5:
			
			if (posicoes[1][1] == 'x' || posicoes[1][1] == 'o')
			{
				
				valida = 0;	
			
			}
			break;
		
		case 6:
			
			if (posicoes[1][2] == 'x' || posicoes[1][2] == 'o')
			{
				
				valida = 0;	
			
			}
			break;
		
		case 7:
			
			if (posicoes[2][0] == 'x' || posicoes[2][0] == 'o')
			{
				
				valida = 0;	
			
			}
			break;
		
		case 8:
			
			if (posicoes[2][1] == 'x' || posicoes[2][1] == 'o')
			{
				
				valida = 0;	
			
			}
			break;
		
		case 9:
			
			if (posicoes[2][2] == 'x' || posicoes[2][2] == 'o')
			{
				
				valida = 0;	
			
			}
			break;
	}
	
	return valida;
	
}

// Fun��o que verifica se existe algum ganhador
// Retornar� 0 se n�o houver ganhador e 1 se houver 
int verificacao_gahador(char posicoes[3][3])
{
	
	int i,ganhou=0;
	
	for (i=0; i<3; i++)
	{
		if ((posicoes[i][0] == posicoes[i][1]) && (posicoes[i][1] == posicoes[i][2]))
		{
			
			ganhou = 1;
			
		}
	}
	
	for (i=0; i<3; i++)
	{
		if ((posicoes[0][i] == posicoes[1][i]) && (posicoes[1][i] == posicoes[2][i]))
		{
			
			ganhou = 1;
			
		}
	}
	
	if ((posicoes[0][0] == posicoes[1][1]) && (posicoes[1][1] == posicoes[2][2]))
	{
			
		ganhou = 1;
			
	}
	
	if ((posicoes[0][2] == posicoes[1][1]) && (posicoes[1][1] == posicoes[2][0]))
	{
			
		ganhou = 1;
			
	}
	

	return ganhou;
	
}

// Fun��o para limpar o buffer do teclado
void limpar_buffer()
{
	
	char c;
	
	while ((c = getchar()) != '\n');
	
}

// Fun��o que simula uma limpase de tela
void limpa_tela()
{

	printf ("\n\n\n\n\n\n");
	
	
}

// Fun��o que pausa o sistema at� o usu�rio digitar uma tecla
void pause ()
{
	
	printf ("\n\nPressione enter para continuar. . .");
	getchar();
	
}
