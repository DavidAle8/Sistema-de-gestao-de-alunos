#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LIMITE 4 // define que � o limite do vetor do registro.

typedef struct{
	
	char nome[80];
	int matricula; 
	float notas[4];
	int CodTurma;
	int faltas;
	float media;
	
}registro;


FILE *ArqAluno;
registro alunos[LIMITE];
int AccAlunos = 0; 

void RegistroVazio();
void CadastrarAluno();
void RemoverAluno();
void AtualizarDados();
void ListarAlunos();
void ListarAprovados();
void ReprovadosMedia();
void ReprovadosFaltas();
void ListagemTurma();

void escrever_aluno ();
void leitura_aluno ();

void SortNome();
void SortMatricula();
void SortFaltas();
void SortMedia();
void troca (int pos_max, int pos2);

void MenuDoSort();
void menu();

int main(){
	setlocale(LC_ALL,"portuguese");
	
	RegistroVazio(); //chamada da fun��o pra ter os alunos sem nada logo de in�cio.
	leitura_aluno(); // puxar o banco de dados dos alunos dentro do arquivo logo antes do RegistroVazio pra ele receber os alunos vazios
	//e tamb�m pra cada acontecimento que envolva os alunos como atualizar e remover, ele vir pra c� com esses novos dados digamos assim, e se manter atualizado
	
	int escolha;
	int op;
	
	do{
	
		menu();
		scanf ("%d", &escolha);
		system("cls");
		
		switch(escolha){
			case 1:{
				CadastrarAluno();
				break;
			}
	
			case 2:{
				RemoverAluno();
				break;
			}
		
			case 3:{
				AtualizarDados();
				break;
			}
		
			case 4:{
				ListarAlunos();
				break;
			}
			
			case 5:{
				ListarAprovados();
				break;
			}
			
			case 6:{
				ReprovadosMedia();
				break;
			}
			
			case 7:{
				ReprovadosFaltas();
				break;
			}
			
			case 8:{
				ListagemTurma();
				break;
			}
				
			case 9:{ // escolhido ordenar os alunos, abre uma op��o de como deseja ordena-los
			
				if (AccAlunos == 0){ //Mostrar a imagem de erro caso queira fazer a ordena��o sem nimguem cadastrado.
					printf ("N�o h� alunos cadastrados para poder fazer a ordena��o. \n\n");
					break;
				}
				
				MenuDoSort();
				scanf("%d",&op);
				system("cls");
			
				switch(op){	
				
					case 1:{
										
						SortNome();
						printf ("Alunos organizados por nome com sucesso!! \n\n");	
						break;
					}	
				
					case 2:{
						
						SortMatricula();
						printf ("Alunos organizados por matr�cula com sucesso!! \n\n");	
						break;
					}	
					
					case 3:{
					
						SortFaltas();
						printf ("Alunos organizados por faltas com sucesso!! \n\n");	
						break;
					}
					
					case 4:{
						
						SortMedia();
						printf ("Alunos organizados por m�dia com sucesso!! \n\n");	
						break;
					}	
					
					default:{
						printf("Op��o inv�lida!! \n\n");
						break;
					}	
				}
			
				break;
			}
			
			case 10:{	
				break;
			}
		
			default :{
				printf ("Op��o inv�lida!\n\n");
				break;
			}
		}	
	}while (escolha != 10);
	
return 0;
}


void RegistroVazio(){ // fun��o que deixa os dados dos alunos vaios. 
	
	int i,j;
	
	for (i=0; i<LIMITE; i++){
		
		alunos[i].nome[0] = '\0';
		alunos[i].matricula = 0;
	
		for (j=0; j<4; j++){
			alunos[i].notas[j] = 0;
		}
		
		alunos[i].CodTurma = 0;
		alunos[i].faltas = 0;
		alunos[i].media = 0;
	}
}

void CadastrarAluno(){
	
	int matricula;
	int i,j,k,n;
	float AccNotas;
	
	printf ("\t\t\t\t ********** CADASTRO DOS ALUNOS ********** \n");
	printf ("\t\t\t\t _________________________________________ \n\n");
	printf ("\n");
	
	for (i=0; i<LIMITE; i++){
		
		//variavel que v�o permanecer assim at� que um aluno n�o existente seja encontrado
		int MatriculaEncontrada = 0;
			
	//	alunos[i].nome[80] = toupper(alunos[i].nome[80]); caso queira comparar min�sculo com mai�sculo no sort.
			
		if (alunos[i].nome[0] == '\0'){
			
			fflush(stdin); //Fun��o pr� definida que limpar o buffer de teclado, para ele limpar o enter que digitamos.
			printf (">> Informe o nome do %d� aluno: ",i+1);
			fgets (alunos[i].nome,80, stdin); // pondo o nome no campo usando fgets (que considera espa�os e impede o estouro de limites de caracteres). 
			
			printf("\n");
			
			printf (">> Informe o n�mero de matricula: ");
			scanf("%d", &matricula); // mesma l�gica, ponho o n�mero de matricula na variavel 'matricula'
		
			for (k=0; k<AccAlunos; k++){
			
				if (alunos[k].matricula == matricula){ // uma varredura por todo aluno � feita e verifica se for igual a um que ja exista no campo de algum aluno,
				// 'zero' a sua string (ponho final de string na primeira letra pra deixar ele como um espa�o vazio para outro aluno), a variavel
				//'MatriculaEncontrada' recebe 1 e emite a menssagem de que existe essa matricula.
					
					alunos[i].nome[0] = '\0';
					MatriculaEncontrada = 1;
					
					system("cls");
					printf ("j� existe aluno com este n�mero de matr�cula. \n");
					break;	
				}	
			}
			
			if (MatriculaEncontrada){ // se 'MatriculaEncontrada' mantiver seu valor, � porqu� o if n foi executado e o aluno n�o foi encontrado, logo, s� quebro
			//a linha de comando e continuo o resto do preenchimento de dados.
				break;
			}
			
			alunos[i].matricula = matricula; // ALuno com seu n�mero de matr�cula diferente, ponho em seu campo de matr�cula.
			
			printf ("\n");
			
			AccNotas = 0;// inicio com 0 a variavel AccNotas.
			
			for (n=0; n<4; n++){
		
				printf (">> Informe a sua %d� nota: ",n+1);
				scanf("%f", &alunos[i].notas[n]);
			
				AccNotas += alunos[i].notas[n]; // que vai acumular as notas de cada aluno cada vez que o for fazer seu la�o fazendo a soma cada vez.
			}
			
			alunos[i].media = AccNotas/4; // logo eu fa�o o campo da media do registro do aluno receber todas essas notas somadas e divididas por 4 para ter a m�dia
			
			printf ("\n");
			
			printf (">> Informe o c�digo da turma: ");
			scanf("%d", &alunos[i].CodTurma);
			
			printf ("\n");
			
			printf (">> Informe as quantidades de faltas: ");
			scanf("%d", &alunos[i].faltas);
			
			AccAlunos++; //Cada aluno cadastrado, fa�o a vari�vel AccAlunos ser acrescentada pra ela atualizar cada vez que um aluno � cadastrado.
			//por isso vemos que certos for, o limte vai at� 'AccAlunos' parajustamente mexer s� com quem ja foi cadastrado. 
			escrever_aluno(); // Ap�s o aluno cadastrado, mostro ele no arquvio. 
			system("cls");	
			break;
		}	
	}
	
	if (i == LIMITE){ //Caso o usu�rio querer cadastrar mais alunos quano se ja excedeu o limte, uma mensagem de erro � apresentada justamente quando o for passa
	// a ter sua condi��o falsa, que � i >= LIMITE, com LIMITE indo at� 4, logo, i >= 4.
		
		system("cls");
		printf ("Cadastro de alunos excedido!! \n\n");	
	}
}

void ListarAlunos(){

	int i,j;
	
	if (AccAlunos == 0){ // Caso o usu�rio queira listar os alunos sem cadastrar algum, deve-se mostrar uma mensagem de erro, j� que se A fun��o CadastrarAluno
		//n�o foi executada, AccAlunos n�o ser� acrescentada, logo ela parmenecer� ao seu valor de origem que � 0.
		printf ("Nenhum aluno foi cadastrado at� o momento. \n\n");
	}
	
	else {
	
		printf ("\t\t\t\t ********** DADOS DOS ALUNOS ********** \n");
		printf ("\t\t\t\t ______________________________________ \n\n");
		
		for (i=0; i<LIMITE; i++){ // pra cada aluno cadastrado at� ent�o, mostro seus dados.
			
			if (alunos[i].nome[0] != '\0'){
				
				printf (">>> %d� Aluno \n",i+1);
				printf ("------------- \n\n");
				
				printf ("- Nome do Aluno: %s \n",alunos[i].nome);

				printf ("- Matr�cula do Aluno: %d \n\n",alunos[i].matricula);
	
				printf ("- Notas do Aluno: ");
				
				for (j=0; j<4; j++){
					printf (" %.1f ",alunos[i].notas[j]);
				}	
		
				printf ("\n\n");
				
				printf ("- C�digo da turma do Aluno: %d \n\n",alunos[i].CodTurma);

				printf ("- Faltas do Aluno: %d \n\n",alunos[i].faltas);

				printf ("- M�dia: %.1f \n\n", alunos[i].media);
				printf ("____________________________________________ \n\n\n");
			}
		}		
	}
}


void AtualizarDados(){
	
	int matricula;
	int	NovasFaltas;
	int i,j;
	float acc=0,NovaNota[4],NovaMedia;
	int encontrado = 0;
	
	if (AccAlunos == 0){ 
	
		printf("Nenhum aluno foi cadastrado at� o momento. \n\n\n");
		return;
	}
	
	else {
			
		printf ("\t\t\t\t ********** ATUALIZA��O DOS DADOS DO ALUNO ********** \n");
		printf ("\t\t\t\t ____________________________________________________ \n\n");
		printf ("\n\n");
	
		printf ("Informe o n�mero de matr�cula: "); //mesma logica, coloco a matricula do aluno que quero atualizar
		scanf("%d", &matricula);
		
		printf("\n");
		
		for (i=0; i<LIMITE; i++){
	
			if (alunos[i].matricula == matricula){ // se ele existir, informo os novos dados de acordo com o que foi pedido pra ser alterado
			
				encontrado = 1;
				
				printf (">> Informe a nova quantidade de faltas: ");
				scanf("%d",&NovasFaltas); //ap�s colocado
				
				alunos[i].faltas = NovasFaltas; // ponho nos demais campos especificado pelos dados que ser�o alterados
				
				printf ("\n");
				
				for (j=0; j<4; j++){
					
					printf (">> Informe a nova %d� nota: ",j+1);
					scanf("%f", &NovaNota[j]);
				
					acc += NovaNota[j];
				}
				
				alunos[i].notas[0] = NovaNota[0];
				alunos[i].notas[1] = NovaNota[1];
				alunos[i].notas[2] = NovaNota[2];
				alunos[i].notas[3] = NovaNota[3];
								
				NovaMedia = acc/4;
				alunos[i].media = NovaMedia;
				
				printf ("dados do aluno atualizado!! \n\n\n");
				
				escrever_aluno(); // e mostro no arquivo
				system("cls");
				break;
			}	
		}	
		
		if (encontrado == 0) { // se o que est� no campo for diferente do que foi digitado, o aluno ent�o n�o existe.
		
			system("cls");
			printf ("N�o existe aluno com esse n�mero de matr�cula. \n\n\n");
		}	
	}	
}


void RemoverAluno(){
	
	long int matricula;
	int encontrado = 0;
	int i,j;
	
	if (AccAlunos == 0){ 
	
		printf("Nenhum aluno foi cadastrado at� o momento. \n\n\n");
		return;
	}
	
	else {
			
		printf("Informe a matr�cula do aluno: "); //Informo a matr�cula de um aluno que desejo remover.
		scanf("%d", &matricula);
		
		printf ("\n");
		
		for (i=0; i<LIMITE; i++){
	
			if (alunos[i].matricula == matricula){ // Se ele existe, ou seja, se a matricula digitada acima for igual a que ja est� no campo, limpo os seus dados.
				
				encontrado = 1; // variavel 'encontrado' rcebe 1 quando o aluno � achado.
				
				alunos[i].nome[0] = '\0';
				alunos[i].matricula = 0;
			
				for (j=0; j<LIMITE; j++){
			
					alunos[i].notas[j] = 0;
				}
		
				alunos[i].CodTurma = 0;
				alunos[i].faltas = 0;
				
				alunos[i].media = 0;
				
				system("cls");
				printf ("Aluno Removido!! \n\n");
				
				escrever_aluno(); //E atualizo no arquivo esse aluno que acabou de ser removido colocabndo ele logo ap�s dele ser removido.
				break;
			}	
		}
		
		if (encontrado == 0){
			
			system("cls"); 
			printf ("N�o foi encontrado aluno com este n�mero de matr�cula!!\n\n");	
		}	
	}
}


void ListarAprovados(){
	
	int turma,encontrado = 0;
	int i,j,freq = 36, qtd=0; // freq serve s� pra receber q quantidade maxima de aulas pra poder subtrair com as faltas do aluno e mostrar sua frequ�ncia
	
	int faltas;
	float media;

	if (AccAlunos == 0){ 
	
		printf("Nenhum aluno foi cadastrado at� o momento. \n\n\n");
		return;
	}
		
	else {
		
		printf ("Informe a turma: ");
		scanf("%d", &turma); // mesma id�ia, pesquiso pela turma dessa vez.
		
		system("cls");
		
		printf ("\t\t\t\t ********** DADOS DOS ALUNOS APROVADOS ********** \n");
		printf ("\t\t\t\t ________________________________________________ \n\n");
		printf ("\n\n");
		
		for (i=0; i<LIMITE; i++){
		
			faltas = alunos[i].faltas;
			media = alunos[i].media;
		
			if (alunos[i].CodTurma == turma){ // Caso essa turma exista, mostro apenas dados desses alunos pela turma
				
				encontrado=1;
				
				if (media >= 7 && faltas <= 14){ //Condi��o de aprova��o, ter sua nota >= 7 e falts menor que 14 (40% de 36 aluas arrendondei pra 14)
					
					printf (">>> %d� Aluno \n",i+1); // alunos com a condi��o de aprovado confere, mostro seus dados requisitados
					printf ("----------- \n");
					printf ("\n");
					
					printf ("- Nome: %s \n\n",alunos[i].nome);
				
					printf ("- Matr�cula do aluno: %d \n\n", alunos[i].matricula);
					
					printf ("- M�dia do aluno: %.1f \n\n", alunos[i].media);
	
					printf ("- Frequ�ncia do aluno: %d \n\n", freq - alunos[i].faltas);
				
					printf ("______________________________________\n\n\n");	
				}	
			}		
		}
	}
	
	
	if (encontrado == 0){ // caso a turma n�o exista, encontrado mant�m seu valor de origem e � mostrado a menssagem de turma inexistente.
		
		system("cls"); 
		printf ("Turma ainda n�o cadastrada pelo sistema!! \n\n");
	}			
}


void ReprovadosMedia (){
	
	int i,j,turma;
	int encontrado = 0;
	float media;
	
	if (AccAlunos == 0){ 
	
		printf("Nenhum aluno foi cadastrado at� o momento. \n\n\n");
		return;
	}
	
	else{
		
		printf ("Informe turma do aluno: ");
		scanf("%d", &turma); // mesma id�ia, ponho a turma.
		
		system("cls");
		
		printf ("\t\t\t\t ********** DADOS DOS ALUNOS REPROVADOS POR M�DIA ********** \n");
		printf ("\t\t\t\t ___________________________________________________________ \n\n");
		printf ("\n\n");
		
		for (i=0; i<LIMITE; i++){
			
			media = alunos[i].media; //aqui eu s� quis mesmo colocar o campo da m�dia na vari�vel m�dia.
				
			if (alunos[i].CodTurma == turma){ // se ela existe, ou seja, se a turma colocada foi uma cadastradado nos campos, mostre os alunos reprovados por m�dia dessa turma. 
			
				encontrado = 1; //encontrado muda seu valor para 1
				
				if (media < 7){ // E nesse caso, mostrar os alunos reporvados por m�dia, ou seja, ter a m�dia inferior a 7.
					
					printf (">>> %d� Aluno \n",i+1);
					printf ("----------- \n");
					printf ("\n");
					
					printf ("- Nome: %s \n",alunos[i].nome);
					
					printf ("- Matricula do aluno: %d \n\n",alunos[i].matricula);	
		
					printf ("- M�dia do aluno: %.1f\n\n", alunos[i].media);
					
					printf ("______________________________________\n\n\n");
				}	
			}
		}
		
		if (encontrado == 0){ //se a turma n�o for igual, � porqu� o if n ocorreu, logo, ancontrado mant�m o valor de origem apago o que vem antes
			// e exibo a menssagem de erro.
			system("cls"); 
			printf ("Turma ainda n�o cadastrada pelo sistema!! \n\n");
		}	
	}
}

void ReprovadosFaltas (){
	
	int i,j,turma;
	int freq=36;
	int encontrado = 0;
	
	if (AccAlunos == 0){ //Caso a pessoa deseje verificar sem cadastrar algum aluno 
	
		printf("Nenhum aluno foi cadastrado at� o momento. \n\n\n");
		return;
	}
	
	else {

		printf ("Informe a turma: ");
		scanf ("%d", &turma);
		
		system("cls");
		
		printf ("\t\t\t\t ********** DADOS DOS ALUNOS REPROVADOS POR FALTAS ********** \n");
		printf ("\t\t\t\t ____________________________________________________________ \n\n");
		printf ("\n\n");
		
		for (i=0; i<LIMITE; i++){
		
			if (alunos[i].CodTurma == turma){ //A turma dos alunos existindo, mostro os dados
				
				encontrado = 1;
		
				if (alunos[i].faltas > 14){//Nesse caso o dos alunos que reprovaram por faltas, que tem faltas > que o limite que � 14
						
					printf (">>> %d� Aluno \n",i+1);
					printf ("------------- \n\n");
		
					printf ("- Nome: %s \n",alunos[i].nome);
		
					printf ("- Matricula do aluno: %d \n\n",alunos[i].matricula);
				
					printf ("- Frequencia do aluno: %d \n\n",freq - alunos[i].faltas);
		
					printf ("______________________________________\n\n\n");
				}
			}
		
			if (encontrado == 0){ //N�o encontrado, exibo o erro.

				system("cls"); 
				printf ("Turma ainda n�o cadastrada pelo sistema!! \n\n");
			}
		}
	}	
}

void ListagemTurma(){
	
	int i,j,turma;
	int encontrado = 0;
		
	if (AccAlunos == 0){ 
	
		printf("Nenhum aluno foi cadastrado at� o momento. \n\n\n");
		return;
	}
	
	else{
		
		printf ("Informe a turma: ");
		scanf("%d", &turma);	
		
		system("cls");
		
		printf ("\t\t\t\t ********** DADOS DOS ALUNOS DA TURMA %d ********** \n",turma);
		printf ("\t\t\t\t __________________________________________________ \n\n");
		printf ("\n\n");
		
		for (i=0; i<LIMITE; i++){
		
			if (alunos[i].CodTurma == turma){ //achando a turma dos alunos ap�s colocado, mostro os dados dos alunos dessa turma.
				
				encontrado = 1;
				
				printf (">>> %d� Aluno \n",i+1);
				printf ("------------- \n\n");
		
				printf ("- Nome: %s \n",alunos[i].nome);
				
				printf ("- Matricula do aluno: %d \n\n",alunos[i].matricula);
			
				printf ("- M�dia do aluno: %.1f \n\n", alunos[i].media);
				
				printf ("______________________________________\n");
				printf("\n\n");	
			}
		
			if (encontrado == 0){

				system("cls"); 
				printf ("Turma ainda n�o cadastrada pelo sistema!! \n\n");
			}	
	 	}
	}
}
	
void leitura_aluno (){
	//A fun��o por onde ela passa durante o c�digo, l� os alunos que foram colocados no registro, ou seja, ela l� no arquivo os dados desses alunos.
	// Acaba sendo um banco de dados desses alunos que foram colocados no registro, no arquivo.
	int i;
	ArqAluno = fopen ("arquivo-aluno.txt","r"); //Abro o arquivo com a fun��o fopen pondo a vari�vel de arquivo (ArqAluno) pre recebe-la e ponho o tipo
	//do arquivo (no caso o txt) e a letrinha � o que vai ser feito com esse arquivo, logo, com o "r" ser� feito a leitura apenas do arquivo.
	
	if (ArqAluno == NULL){ // se o arquivo for NULL, ou seja, se n�o existir o arquivo, ele exibir� uma manssagem de erro.
		printf ("ERRO! N�o foi poss�vel abrir arquivo! \n");
	}
	
	else{ //Se n�o, leio os dados dos alunos cadastrados at� ent�o pondo o fscanf espec�fico de leitura pra arquvio e leito cada campo pra guardar no arquivo.
		
		for (i=0; i < LIMITE; i++){ // pra mexer at� os alunos que foram cadastrados at� ent�o.
			
			if (alunos[i].nome[0] == '\0'){ //Mesma id�ia de cadastrar alunos
			
				//Lida de cada registro no arquivo.
				fscanf (ArqAluno," %s", &alunos[i].nome);
				fscanf (ArqAluno," %d" ,&alunos[i].matricula);
				fscanf (ArqAluno," %f", &alunos[i].notas[0]);
				fscanf (ArqAluno," %f", &alunos[i].notas[1]);
				fscanf (ArqAluno," %f", &alunos[i].notas[3]);
				fscanf (ArqAluno," %f", &alunos[i].notas[2]);
				fscanf (ArqAluno," %d", &alunos[i].CodTurma);
				fscanf (ArqAluno," %d", &alunos[i].faltas);	
			}
		}
			
	}
	fclose(ArqAluno); // E fecho meu arquvi dando a fun��o pre definida fclose na variavel ponteiro do tipo arquivo (FILE)
}

void escrever_aluno(){ 
		
	int j,i;
	
	ArqAluno = fopen ("arquivo-aluno.txt","w+"); //	Mesma coisa do leitura_alunos. e 'w+' serve para leitura e grava��o dos dados que estar�o no arquivo.
	
		for (i=0; i < LIMITE; i++){ //pra mexer at� os alunos que foram cadastrados at� ent�o e printo no arquvio
			
			if (alunos[i].nome[0] != '\0'){
				
				fprintf (ArqAluno,">>> %d� Aluno\n",i+1);
				fprintf (ArqAluno,"--------------\n\n");
				
				fprintf (ArqAluno, "- Nome do aluno: %s \n", alunos[i].nome);
				fprintf (ArqAluno, "- Matr�cula do aluno: %d \n\n", alunos[i].matricula);
				
				fprintf(ArqAluno, "- Notas do aluno: ");
				
				for (j=0; j<4; j++){
					fprintf(ArqAluno,"%.1f ", alunos[i].notas[j]);
				}
				
				fprintf(ArqAluno,"\n\n");
			
				fprintf(ArqAluno, "- Turma do aluno: %d \n\n", alunos[i].CodTurma);
				fprintf(ArqAluno, "- Faltas do aluno: %d \n\n", alunos[i].faltas);
				fprintf(ArqAluno, "- M�dia do aluno: %.1f \n\n", alunos[i].media);
				fprintf(ArqAluno, "___________________________________\n\n");
			}	
		}
	fclose(ArqAluno); // e fecho o arquivo.
}

void SortNome(){
	
	int i,j;
	int pos_max;
	
	for (i=0; i<AccAlunos - 1; i++){
		pos_max = 0;
		
		for (j=1; j<AccAlunos - i; j++){
		
			if (strcmp(alunos[j].nome , alunos[pos_max].nome) > 0){
				pos_max = j;	
			}
	
			troca(pos_max, AccAlunos-1-i);		
		}
	}
}

void SortMatricula(){
	
	//Na fun��o dos sorts que usam selection sort, vai pegando as pessoas que tem o dado com um valor maior que o outro e puxa pro fim do vetor.
	
	int i,j;
	int pos_max;
	
	for(i=0; i<AccAlunos-1; i++){ //pra cada vez que isso passa, colocamos o pos_max pra receber 0,
		pos_max = 0;
		
		for(j=1; j<AccAlunos-i; j++){
			
// logo eu verifico: j recebe 1 e pos_max 0. Com isso, o segundo aluno (alunos[j].matricula com j = 1) tem sua matricula maior que a do primeiro? 
//(alunos[pos_max].matricula com pos_max = 0) se sim, pe�o pra esse primeiro tomar a posi��o do maior, nesse caso o segundo aluno (alunos[j].matricula)
//fazendo assim com que ele v� recebendo a posi��o dos maiores at� ele n poder mais, ou seja, o aluno ap�s a ele for maior que ele ou ele
//ser o maior de todos e ficar na extremidade do vetor, logo, ele permanecer� al� mesmo.
			if (alunos[j].matricula > alunos[pos_max].matricula){
				pos_max = j;
			}
			
			troca(pos_max, AccAlunos-1-i);//Contudo, aplico a fun��o de troca pra fazer uma transitividade com os dados entre os alunos que v�o estar sendo trocados.
		}	
	}	
}

void SortFaltas (){ 
	
	int i,j;
	int pos_max;
	
	for(i=0; i<AccAlunos-1; i++){
		pos_max = 0;
	
		for(j=1; j<AccAlunos-i; j++){
		
			if (alunos[j].faltas > alunos[pos_max].faltas){
				pos_max = j;
			}
			
			troca(pos_max, AccAlunos-1-i);
		}	
	}	
}

void SortMedia (){ 
	
	int i,j;
	int pos_max;
	
	for(i=0; i<AccAlunos-1; i++){
		pos_max = 0;
		
		for(j=1; j<AccAlunos-i; j++){
		
			if (alunos[j].media > alunos[pos_max].media){
				pos_max = j;
			}
		
			troca(pos_max, AccAlunos-1-i);
		}	
	}	
}

void troca (int pos_max, int pos2){
	
	registro temp; //aqui � onde ocorre a transitividade de dados dos alunos que v�o sendo trocados nas fun��es de sort.
	//Os dados do aluno que rcebeu a pos��o do maior (alunos[pos_max]) s�o colocaldos em uma vari�vel tempor�ria, depois do alunos[pos_max]
	// recebe a dos alunos.[pos2] e por fim alunos.[pos2] � guarado na variavel tempor�ria que fez a troca inicialmente.

	strcpy (temp.nome , alunos[pos_max].nome);
	temp.matricula = alunos[pos_max].matricula;
	temp.notas[0] = alunos[pos_max].notas[0];
	temp.notas[1] = alunos[pos_max].notas[1];
	temp.notas[2] = alunos[pos_max].notas[2];
	temp.notas[3] = alunos[pos_max].notas[3];
	temp.CodTurma = alunos[pos_max].CodTurma;
	temp.faltas = alunos[pos_max].faltas;
	temp.media = alunos[pos_max].media;
	
	strcpy(alunos[pos_max].nome , alunos[pos2].nome);
	alunos[pos_max].matricula =  alunos[pos2].matricula;
	alunos[pos_max].notas[0] =  alunos[pos2].notas[0];
	alunos[pos_max].notas[1] =  alunos[pos2].notas[1];
	alunos[pos_max].notas[2] =  alunos[pos2].notas[2];
	alunos[pos_max].notas[3] =  alunos[pos2].notas[3];
	alunos[pos_max].CodTurma = alunos[pos2].CodTurma;
	alunos[pos_max].faltas = alunos[pos2].faltas;
	alunos[pos_max].media = alunos[pos2].media;
	
	strcpy(alunos[pos2].nome , temp.nome);
	alunos[pos2].matricula = temp.matricula;
	alunos[pos2].notas[0] = temp.notas[0];
	alunos[pos2].notas[1] = temp.notas[1];
	alunos[pos2].notas[2] = temp.notas[2];
	alunos[pos2].notas[3] = temp.notas[3];
	alunos[pos2].CodTurma = temp.CodTurma;
	alunos[pos2].faltas = temp.faltas;
	alunos[pos2].media = temp.media;
	
}
	
void MenuDoSort(){ 
	
	printf("Informe as op�oes de acordo com as iniciais de cada op�ao.\n\n");
	
	printf("(Obs: a ordem dos dados ser�o de forma crescente, do menor pro maior) \n\n");
	
	printf (">> Organizar alunos por nome - (1)\n");
	printf (">> Organizar alunos por matr�cula - (2)\n");
	printf (">> Organizar alunos por faltas - (3)\n");
	printf (">> Organizar alunos por media - (4)\n");
	printf ("Resposta: ");
	
}

void menu(){ 
	
	printf ("\t\t\t\t\t ********** GEST�O DE ALUNOS ********** \n");
	printf ("\t\t\t\t\t ______________________________________ \n\n");
	
	printf("Informe as op�oes de acordo com a numera��o de cada op�ao. \n\n");
	
	printf (">> Cadastrar aluno - (1) \n");
	printf (">> Remover aluno - (2) \n");
	printf (">> Atualizar dados do aluno - (3) \n");
	printf (">> Listar alunos - (4) \n");
	printf (">> Listar aprovados - (5) \n");
	printf (">> Alunos reporvados por m�dia - (6) \n");
	printf (">> Alunos reprovados por falta - (7) \n");
	printf (">> Listar alunos por turma - (8) \n");
	printf (">> Organizar alunos cadastrados - (9) \n");
	printf (">> Sair - (10) \n");
	printf ("Resposta: ");	
}
