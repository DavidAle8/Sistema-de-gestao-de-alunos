#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LIMITE 4 // define que é o limite do vetor do registro.

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
	
	RegistroVazio(); //chamada da função pra ter os alunos sem nada logo de início.
	leitura_aluno(); // puxar o banco de dados dos alunos dentro do arquivo logo antes do RegistroVazio pra ele receber os alunos vazios
	//e também pra cada acontecimento que envolva os alunos como atualizar e remover, ele vir pra cá com esses novos dados digamos assim, e se manter atualizado
	
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
				
			case 9:{ // escolhido ordenar os alunos, abre uma opção de como deseja ordena-los
			
				if (AccAlunos == 0){ //Mostrar a imagem de erro caso queira fazer a ordenação sem nimguem cadastrado.
					printf ("Não há alunos cadastrados para poder fazer a ordenação. \n\n");
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
						printf ("Alunos organizados por matrícula com sucesso!! \n\n");	
						break;
					}	
					
					case 3:{
					
						SortFaltas();
						printf ("Alunos organizados por faltas com sucesso!! \n\n");	
						break;
					}
					
					case 4:{
						
						SortMedia();
						printf ("Alunos organizados por média com sucesso!! \n\n");	
						break;
					}	
					
					default:{
						printf("Opção inválida!! \n\n");
						break;
					}	
				}
			
				break;
			}
			
			case 10:{	
				break;
			}
		
			default :{
				printf ("Opção inválida!\n\n");
				break;
			}
		}	
	}while (escolha != 10);
	
return 0;
}


void RegistroVazio(){ // função que deixa os dados dos alunos vaios. 
	
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
		
		//variavel que vão permanecer assim até que um aluno não existente seja encontrado
		int MatriculaEncontrada = 0;
			
	//	alunos[i].nome[80] = toupper(alunos[i].nome[80]); caso queira comparar minúsculo com maiúsculo no sort.
			
		if (alunos[i].nome[0] == '\0'){
			
			fflush(stdin); //Função pré definida que limpar o buffer de teclado, para ele limpar o enter que digitamos.
			printf (">> Informe o nome do %d° aluno: ",i+1);
			fgets (alunos[i].nome,80, stdin); // pondo o nome no campo usando fgets (que considera espaços e impede o estouro de limites de caracteres). 
			
			printf("\n");
			
			printf (">> Informe o número de matricula: ");
			scanf("%d", &matricula); // mesma lógica, ponho o número de matricula na variavel 'matricula'
		
			for (k=0; k<AccAlunos; k++){
			
				if (alunos[k].matricula == matricula){ // uma varredura por todo aluno é feita e verifica se for igual a um que ja exista no campo de algum aluno,
				// 'zero' a sua string (ponho final de string na primeira letra pra deixar ele como um espaço vazio para outro aluno), a variavel
				//'MatriculaEncontrada' recebe 1 e emite a menssagem de que existe essa matricula.
					
					alunos[i].nome[0] = '\0';
					MatriculaEncontrada = 1;
					
					system("cls");
					printf ("já existe aluno com este número de matrícula. \n");
					break;	
				}	
			}
			
			if (MatriculaEncontrada){ // se 'MatriculaEncontrada' mantiver seu valor, é porquê o if n foi executado e o aluno não foi encontrado, logo, só quebro
			//a linha de comando e continuo o resto do preenchimento de dados.
				break;
			}
			
			alunos[i].matricula = matricula; // ALuno com seu número de matrícula diferente, ponho em seu campo de matrícula.
			
			printf ("\n");
			
			AccNotas = 0;// inicio com 0 a variavel AccNotas.
			
			for (n=0; n<4; n++){
		
				printf (">> Informe a sua %d° nota: ",n+1);
				scanf("%f", &alunos[i].notas[n]);
			
				AccNotas += alunos[i].notas[n]; // que vai acumular as notas de cada aluno cada vez que o for fazer seu laço fazendo a soma cada vez.
			}
			
			alunos[i].media = AccNotas/4; // logo eu faço o campo da media do registro do aluno receber todas essas notas somadas e divididas por 4 para ter a média
			
			printf ("\n");
			
			printf (">> Informe o código da turma: ");
			scanf("%d", &alunos[i].CodTurma);
			
			printf ("\n");
			
			printf (">> Informe as quantidades de faltas: ");
			scanf("%d", &alunos[i].faltas);
			
			AccAlunos++; //Cada aluno cadastrado, faço a variável AccAlunos ser acrescentada pra ela atualizar cada vez que um aluno é cadastrado.
			//por isso vemos que certos for, o limte vai até 'AccAlunos' parajustamente mexer só com quem ja foi cadastrado. 
			escrever_aluno(); // Após o aluno cadastrado, mostro ele no arquvio. 
			system("cls");	
			break;
		}	
	}
	
	if (i == LIMITE){ //Caso o usuário querer cadastrar mais alunos quano se ja excedeu o limte, uma mensagem de erro é apresentada justamente quando o for passa
	// a ter sua condição falsa, que é i >= LIMITE, com LIMITE indo até 4, logo, i >= 4.
		
		system("cls");
		printf ("Cadastro de alunos excedido!! \n\n");	
	}
}

void ListarAlunos(){

	int i,j;
	
	if (AccAlunos == 0){ // Caso o usuário queira listar os alunos sem cadastrar algum, deve-se mostrar uma mensagem de erro, já que se A função CadastrarAluno
		//não foi executada, AccAlunos não será acrescentada, logo ela parmenecerá ao seu valor de origem que é 0.
		printf ("Nenhum aluno foi cadastrado até o momento. \n\n");
	}
	
	else {
	
		printf ("\t\t\t\t ********** DADOS DOS ALUNOS ********** \n");
		printf ("\t\t\t\t ______________________________________ \n\n");
		
		for (i=0; i<LIMITE; i++){ // pra cada aluno cadastrado até então, mostro seus dados.
			
			if (alunos[i].nome[0] != '\0'){
				
				printf (">>> %d° Aluno \n",i+1);
				printf ("------------- \n\n");
				
				printf ("- Nome do Aluno: %s \n",alunos[i].nome);

				printf ("- Matrícula do Aluno: %d \n\n",alunos[i].matricula);
	
				printf ("- Notas do Aluno: ");
				
				for (j=0; j<4; j++){
					printf (" %.1f ",alunos[i].notas[j]);
				}	
		
				printf ("\n\n");
				
				printf ("- Código da turma do Aluno: %d \n\n",alunos[i].CodTurma);

				printf ("- Faltas do Aluno: %d \n\n",alunos[i].faltas);

				printf ("- Média: %.1f \n\n", alunos[i].media);
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
	
		printf("Nenhum aluno foi cadastrado até o momento. \n\n\n");
		return;
	}
	
	else {
			
		printf ("\t\t\t\t ********** ATUALIZAÇÃO DOS DADOS DO ALUNO ********** \n");
		printf ("\t\t\t\t ____________________________________________________ \n\n");
		printf ("\n\n");
	
		printf ("Informe o número de matrícula: "); //mesma logica, coloco a matricula do aluno que quero atualizar
		scanf("%d", &matricula);
		
		printf("\n");
		
		for (i=0; i<LIMITE; i++){
	
			if (alunos[i].matricula == matricula){ // se ele existir, informo os novos dados de acordo com o que foi pedido pra ser alterado
			
				encontrado = 1;
				
				printf (">> Informe a nova quantidade de faltas: ");
				scanf("%d",&NovasFaltas); //após colocado
				
				alunos[i].faltas = NovasFaltas; // ponho nos demais campos especificado pelos dados que serão alterados
				
				printf ("\n");
				
				for (j=0; j<4; j++){
					
					printf (">> Informe a nova %d° nota: ",j+1);
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
		
		if (encontrado == 0) { // se o que está no campo for diferente do que foi digitado, o aluno então não existe.
		
			system("cls");
			printf ("Não existe aluno com esse número de matrícula. \n\n\n");
		}	
	}	
}


void RemoverAluno(){
	
	long int matricula;
	int encontrado = 0;
	int i,j;
	
	if (AccAlunos == 0){ 
	
		printf("Nenhum aluno foi cadastrado até o momento. \n\n\n");
		return;
	}
	
	else {
			
		printf("Informe a matrícula do aluno: "); //Informo a matrícula de um aluno que desejo remover.
		scanf("%d", &matricula);
		
		printf ("\n");
		
		for (i=0; i<LIMITE; i++){
	
			if (alunos[i].matricula == matricula){ // Se ele existe, ou seja, se a matricula digitada acima for igual a que ja está no campo, limpo os seus dados.
				
				encontrado = 1; // variavel 'encontrado' rcebe 1 quando o aluno é achado.
				
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
				
				escrever_aluno(); //E atualizo no arquivo esse aluno que acabou de ser removido colocabndo ele logo após dele ser removido.
				break;
			}	
		}
		
		if (encontrado == 0){
			
			system("cls"); 
			printf ("Não foi encontrado aluno com este número de matrícula!!\n\n");	
		}	
	}
}


void ListarAprovados(){
	
	int turma,encontrado = 0;
	int i,j,freq = 36, qtd=0; // freq serve só pra receber q quantidade maxima de aulas pra poder subtrair com as faltas do aluno e mostrar sua frequência
	
	int faltas;
	float media;

	if (AccAlunos == 0){ 
	
		printf("Nenhum aluno foi cadastrado até o momento. \n\n\n");
		return;
	}
		
	else {
		
		printf ("Informe a turma: ");
		scanf("%d", &turma); // mesma idéia, pesquiso pela turma dessa vez.
		
		system("cls");
		
		printf ("\t\t\t\t ********** DADOS DOS ALUNOS APROVADOS ********** \n");
		printf ("\t\t\t\t ________________________________________________ \n\n");
		printf ("\n\n");
		
		for (i=0; i<LIMITE; i++){
		
			faltas = alunos[i].faltas;
			media = alunos[i].media;
		
			if (alunos[i].CodTurma == turma){ // Caso essa turma exista, mostro apenas dados desses alunos pela turma
				
				encontrado=1;
				
				if (media >= 7 && faltas <= 14){ //Condição de aprovação, ter sua nota >= 7 e falts menor que 14 (40% de 36 aluas arrendondei pra 14)
					
					printf (">>> %d° Aluno \n",i+1); // alunos com a condição de aprovado confere, mostro seus dados requisitados
					printf ("----------- \n");
					printf ("\n");
					
					printf ("- Nome: %s \n\n",alunos[i].nome);
				
					printf ("- Matrícula do aluno: %d \n\n", alunos[i].matricula);
					
					printf ("- Média do aluno: %.1f \n\n", alunos[i].media);
	
					printf ("- Frequência do aluno: %d \n\n", freq - alunos[i].faltas);
				
					printf ("______________________________________\n\n\n");	
				}	
			}		
		}
	}
	
	
	if (encontrado == 0){ // caso a turma não exista, encontrado mantém seu valor de origem e é mostrado a menssagem de turma inexistente.
		
		system("cls"); 
		printf ("Turma ainda não cadastrada pelo sistema!! \n\n");
	}			
}


void ReprovadosMedia (){
	
	int i,j,turma;
	int encontrado = 0;
	float media;
	
	if (AccAlunos == 0){ 
	
		printf("Nenhum aluno foi cadastrado até o momento. \n\n\n");
		return;
	}
	
	else{
		
		printf ("Informe turma do aluno: ");
		scanf("%d", &turma); // mesma idéia, ponho a turma.
		
		system("cls");
		
		printf ("\t\t\t\t ********** DADOS DOS ALUNOS REPROVADOS POR MÉDIA ********** \n");
		printf ("\t\t\t\t ___________________________________________________________ \n\n");
		printf ("\n\n");
		
		for (i=0; i<LIMITE; i++){
			
			media = alunos[i].media; //aqui eu só quis mesmo colocar o campo da média na variável média.
				
			if (alunos[i].CodTurma == turma){ // se ela existe, ou seja, se a turma colocada foi uma cadastradado nos campos, mostre os alunos reprovados por média dessa turma. 
			
				encontrado = 1; //encontrado muda seu valor para 1
				
				if (media < 7){ // E nesse caso, mostrar os alunos reporvados por média, ou seja, ter a média inferior a 7.
					
					printf (">>> %d° Aluno \n",i+1);
					printf ("----------- \n");
					printf ("\n");
					
					printf ("- Nome: %s \n",alunos[i].nome);
					
					printf ("- Matricula do aluno: %d \n\n",alunos[i].matricula);	
		
					printf ("- Média do aluno: %.1f\n\n", alunos[i].media);
					
					printf ("______________________________________\n\n\n");
				}	
			}
		}
		
		if (encontrado == 0){ //se a turma não for igual, é porquê o if n ocorreu, logo, ancontrado mantém o valor de origem apago o que vem antes
			// e exibo a menssagem de erro.
			system("cls"); 
			printf ("Turma ainda não cadastrada pelo sistema!! \n\n");
		}	
	}
}

void ReprovadosFaltas (){
	
	int i,j,turma;
	int freq=36;
	int encontrado = 0;
	
	if (AccAlunos == 0){ //Caso a pessoa deseje verificar sem cadastrar algum aluno 
	
		printf("Nenhum aluno foi cadastrado até o momento. \n\n\n");
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
		
				if (alunos[i].faltas > 14){//Nesse caso o dos alunos que reprovaram por faltas, que tem faltas > que o limite que é 14
						
					printf (">>> %d° Aluno \n",i+1);
					printf ("------------- \n\n");
		
					printf ("- Nome: %s \n",alunos[i].nome);
		
					printf ("- Matricula do aluno: %d \n\n",alunos[i].matricula);
				
					printf ("- Frequencia do aluno: %d \n\n",freq - alunos[i].faltas);
		
					printf ("______________________________________\n\n\n");
				}
			}
		
			if (encontrado == 0){ //Não encontrado, exibo o erro.

				system("cls"); 
				printf ("Turma ainda não cadastrada pelo sistema!! \n\n");
			}
		}
	}	
}

void ListagemTurma(){
	
	int i,j,turma;
	int encontrado = 0;
		
	if (AccAlunos == 0){ 
	
		printf("Nenhum aluno foi cadastrado até o momento. \n\n\n");
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
		
			if (alunos[i].CodTurma == turma){ //achando a turma dos alunos após colocado, mostro os dados dos alunos dessa turma.
				
				encontrado = 1;
				
				printf (">>> %d° Aluno \n",i+1);
				printf ("------------- \n\n");
		
				printf ("- Nome: %s \n",alunos[i].nome);
				
				printf ("- Matricula do aluno: %d \n\n",alunos[i].matricula);
			
				printf ("- Média do aluno: %.1f \n\n", alunos[i].media);
				
				printf ("______________________________________\n");
				printf("\n\n");	
			}
		
			if (encontrado == 0){

				system("cls"); 
				printf ("Turma ainda não cadastrada pelo sistema!! \n\n");
			}	
	 	}
	}
}
	
void leitura_aluno (){
	//A função por onde ela passa durante o código, lê os alunos que foram colocados no registro, ou seja, ela lê no arquivo os dados desses alunos.
	// Acaba sendo um banco de dados desses alunos que foram colocados no registro, no arquivo.
	int i;
	ArqAluno = fopen ("arquivo-aluno.txt","r"); //Abro o arquivo com a função fopen pondo a variável de arquivo (ArqAluno) pre recebe-la e ponho o tipo
	//do arquivo (no caso o txt) e a letrinha é o que vai ser feito com esse arquivo, logo, com o "r" será feito a leitura apenas do arquivo.
	
	if (ArqAluno == NULL){ // se o arquivo for NULL, ou seja, se não existir o arquivo, ele exibirá uma manssagem de erro.
		printf ("ERRO! Não foi possível abrir arquivo! \n");
	}
	
	else{ //Se não, leio os dados dos alunos cadastrados até então pondo o fscanf específico de leitura pra arquvio e leito cada campo pra guardar no arquivo.
		
		for (i=0; i < LIMITE; i++){ // pra mexer até os alunos que foram cadastrados até então.
			
			if (alunos[i].nome[0] == '\0'){ //Mesma idéia de cadastrar alunos
			
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
	fclose(ArqAluno); // E fecho meu arquvi dando a função pre definida fclose na variavel ponteiro do tipo arquivo (FILE)
}

void escrever_aluno(){ 
		
	int j,i;
	
	ArqAluno = fopen ("arquivo-aluno.txt","w+"); //	Mesma coisa do leitura_alunos. e 'w+' serve para leitura e gravação dos dados que estarão no arquivo.
	
		for (i=0; i < LIMITE; i++){ //pra mexer até os alunos que foram cadastrados até então e printo no arquvio
			
			if (alunos[i].nome[0] != '\0'){
				
				fprintf (ArqAluno,">>> %d° Aluno\n",i+1);
				fprintf (ArqAluno,"--------------\n\n");
				
				fprintf (ArqAluno, "- Nome do aluno: %s \n", alunos[i].nome);
				fprintf (ArqAluno, "- Matrícula do aluno: %d \n\n", alunos[i].matricula);
				
				fprintf(ArqAluno, "- Notas do aluno: ");
				
				for (j=0; j<4; j++){
					fprintf(ArqAluno,"%.1f ", alunos[i].notas[j]);
				}
				
				fprintf(ArqAluno,"\n\n");
			
				fprintf(ArqAluno, "- Turma do aluno: %d \n\n", alunos[i].CodTurma);
				fprintf(ArqAluno, "- Faltas do aluno: %d \n\n", alunos[i].faltas);
				fprintf(ArqAluno, "- Média do aluno: %.1f \n\n", alunos[i].media);
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
	
	//Na função dos sorts que usam selection sort, vai pegando as pessoas que tem o dado com um valor maior que o outro e puxa pro fim do vetor.
	
	int i,j;
	int pos_max;
	
	for(i=0; i<AccAlunos-1; i++){ //pra cada vez que isso passa, colocamos o pos_max pra receber 0,
		pos_max = 0;
		
		for(j=1; j<AccAlunos-i; j++){
			
// logo eu verifico: j recebe 1 e pos_max 0. Com isso, o segundo aluno (alunos[j].matricula com j = 1) tem sua matricula maior que a do primeiro? 
//(alunos[pos_max].matricula com pos_max = 0) se sim, peço pra esse primeiro tomar a posição do maior, nesse caso o segundo aluno (alunos[j].matricula)
//fazendo assim com que ele vá recebendo a posição dos maiores até ele n poder mais, ou seja, o aluno após a ele for maior que ele ou ele
//ser o maior de todos e ficar na extremidade do vetor, logo, ele permanecerá alí mesmo.
			if (alunos[j].matricula > alunos[pos_max].matricula){
				pos_max = j;
			}
			
			troca(pos_max, AccAlunos-1-i);//Contudo, aplico a função de troca pra fazer uma transitividade com os dados entre os alunos que vão estar sendo trocados.
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
	
	registro temp; //aqui é onde ocorre a transitividade de dados dos alunos que vão sendo trocados nas funções de sort.
	//Os dados do aluno que rcebeu a posção do maior (alunos[pos_max]) são colocaldos em uma variável temporária, depois do alunos[pos_max]
	// recebe a dos alunos.[pos2] e por fim alunos.[pos2] é guarado na variavel temporária que fez a troca inicialmente.

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
	
	printf("Informe as opçoes de acordo com as iniciais de cada opçao.\n\n");
	
	printf("(Obs: a ordem dos dados serão de forma crescente, do menor pro maior) \n\n");
	
	printf (">> Organizar alunos por nome - (1)\n");
	printf (">> Organizar alunos por matrícula - (2)\n");
	printf (">> Organizar alunos por faltas - (3)\n");
	printf (">> Organizar alunos por media - (4)\n");
	printf ("Resposta: ");
	
}

void menu(){ 
	
	printf ("\t\t\t\t\t ********** GESTÃO DE ALUNOS ********** \n");
	printf ("\t\t\t\t\t ______________________________________ \n\n");
	
	printf("Informe as opçoes de acordo com a numeração de cada opçao. \n\n");
	
	printf (">> Cadastrar aluno - (1) \n");
	printf (">> Remover aluno - (2) \n");
	printf (">> Atualizar dados do aluno - (3) \n");
	printf (">> Listar alunos - (4) \n");
	printf (">> Listar aprovados - (5) \n");
	printf (">> Alunos reporvados por média - (6) \n");
	printf (">> Alunos reprovados por falta - (7) \n");
	printf (">> Listar alunos por turma - (8) \n");
	printf (">> Organizar alunos cadastrados - (9) \n");
	printf (">> Sair - (10) \n");
	printf ("Resposta: ");	
}
