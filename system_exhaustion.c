#include <stdio.h>
#include <stdlib.h>
#include <shlobj.h>
#include <time.h>



//Diretiva de Pré-processamento evitando que o programa seja rodado em um Sistema Operacional diferente de Windows
#ifdef _WIN32
    #include <windows.h>

#else
    #error Sistema Operacional nao suportado!

#endif



//Limite de RAM desejado responsável por barrar a abertura de pastas e guias do navegador, a fim de não travar completamente o computador
#define THRESHOLDRAMMB 20

//Tempo até a reinicialização do computador a partir do momento que o limite de memória RAM livre for atingido
#define TEMPOREINICIALIZACAO 60

//URLs desejadas que serão abertas
#define URL1 "https://www.youtube.com/watch?v=dQw4w9WgXcQ&ab_channel=RickAstley"
#define URL2 "https://www.kaspersky.com.br/resource-center/preemptive-safety/what-is-malware-and-how-to-protect-against-it"
#define URL3 "https://www.google.com.br"



typedef unsigned long long ull;

//Protótipos das funções
void WIN32disclaimer();
int  WIN32verificaQuantidadeDisponivelMemoriaRAM();
void WIN32buscaCaminhoPastas(char *caminhoDocumentos, char *caminhoImagens, char *caminhoSystem32);
void WIN32sonsAvisos();
int  WIN32numeroAleatorio1a3();
void WIN32abrePastasENavegador(char *caminhoDocumentos, char *caminhoImagens, char *caminhoSystem32);
void WIN32reiniciaComputador();



int main() {

    //Descobrimento do nome do usuário que está rodando o programa
    char WIN32nomeUsuario[257]; //Variável que armazena o nome do usuário
    DWORD WIN32sizeNomeUsuario = 257; //Tamanho do nome do usuário
    GetUserNameA(WIN32nomeUsuario, &WIN32sizeNomeUsuario); // Obtém o nome do usuário

    printf("\nOi, %s, tenha certeza de que todo trabalho foi salvo e se prepare!\n", WIN32nomeUsuario);
    
    WIN32disclaimer();
    
    //Inicialização da Seed cronológica
    srand((unsigned int)time(NULL)); 

    //Strings que guardam os caminhos para as Pastas de Documentos, Imagens e System32
    char WIN32caminhoPastaDocumentos[MAX_PATH];  
    char WIN32caminhoPastaImagens[MAX_PATH];
    char WIN32caminhoPastaSystem32[MAX_PATH];

    WIN32buscaCaminhoPastas(WIN32caminhoPastaDocumentos, WIN32caminhoPastaImagens, WIN32caminhoPastaSystem32);
    WIN32abrePastasENavegador(WIN32caminhoPastaDocumentos, WIN32caminhoPastaImagens, WIN32caminhoPastaSystem32);
    Sleep(5000);
    WIN32abrePastasENavegador(WIN32caminhoPastaDocumentos, WIN32caminhoPastaImagens, WIN32caminhoPastaSystem32);
    Sleep(5000);
    WIN32abrePastasENavegador(WIN32caminhoPastaDocumentos, WIN32caminhoPastaImagens, WIN32caminhoPastaSystem32);

    WIN32reiniciaComputador();

    return 0;
}



//Função de abertura do arquivo disclaimer
void WIN32disclaimer()
{
    system("start notepad Disclaimer.txt");

    printf("\nPressione Enter para continuar:\n");
    getchar();
}



//Função que descobre a quantidade que não está sendo utilizada de RAM com a utilidade de não travar completamente o computador
int  WIN32verificaQuantidadeDisponivelMemoriaRAM()
{
    MEMORYSTATUSEX WIN32statusMemoriaRAM;
    WIN32statusMemoriaRAM.dwLength = sizeof(WIN32statusMemoriaRAM);

    GlobalMemoryStatusEx(&WIN32statusMemoriaRAM);

    return WIN32statusMemoriaRAM.ullAvailPhys;
}



//Função que formata os caminhos escolhidos por meio da variável de ambiente
void WIN32buscaCaminhoPastas(char *caminhoDocumentos, char *caminhoImagens, char *caminhoSystem32)
{
    SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, caminhoDocumentos);
    SHGetFolderPathA(NULL, CSIDL_MYPICTURES, NULL, 0, caminhoImagens);
    SHGetFolderPathA(NULL, CSIDL_SYSTEM, NULL, 0, caminhoSystem32); 
}



//Função que toca o som de aviso do Windows
void WIN32sonsAvisos()
{
    MessageBeep(MB_ICONWARNING);
}



//Função que retorna um número pseudo-aleatório no intervalo [1,3]
int  WIN32numeroAleatorio1a3()
{
    return (rand() % 3) + 1;
}



//Função que abre as pastas e guias do navegador  até o limite de RAM definido no início do programa ser atingido
void WIN32abrePastasENavegador(char *caminhoDocumentos, char *caminhoImagens, char *caminhoSystem32)
{
    char comandoAberturaDocumentos[MAX_PATH + 12]; //Tamanho maximo de um caminho + 12 para acomodar "explorer \%s\\0"
    char comandoAberturaImagens[MAX_PATH + 12]; 
    char comandoAberturaSystem32[MAX_PATH + 12]; 

    sprintf(comandoAberturaDocumentos, "explorer \"%s\"", caminhoDocumentos); //Formatação da string no formato "explorer "C:\Users\Usuário\Pasta""
    sprintf(comandoAberturaImagens, "explorer \"%s\"", caminhoImagens);
    sprintf(comandoAberturaSystem32, "explorer \"%s\"", caminhoSystem32);

    //Variável de contagem
    int i = 0;

    //Variável responsável pelo tempo de Sleep entre aberturas das pastas
    int j = 3150;
    
    //Variável que vai guardar o valor da memória RAM não utilizada a cada iteração do laço
    ull memoriaRAM = WIN32verificaQuantidadeDisponivelMemoriaRAM();


    //Laço para ao atingir o valor limítrofe de memória RAM restante
    while((memoriaRAM / (1024 * 1024)) > THRESHOLDRAMMB)
    {
        switch(WIN32numeroAleatorio1a3())
        {   
        case 1:

            //Abre o link URL1 definido no inicio do programa na primeira iteração do laço
            if(i == 0)
            {
                WIN32sonsAvisos();
                ShellExecuteA(NULL, "open", URL1, NULL, NULL, SW_SHOWNORMAL);
                Sleep(5000);
            }

            //Abre o link URL2 definido no inicio do programa na segunda iteração do laço
            if(i == 1)
            {
                WIN32sonsAvisos();
                ShellExecuteA(NULL, "open", URL2, NULL, NULL, SW_SHOWNORMAL);
                Sleep(3000);
            }

            //Abre o link URL3 definido no início do programa repetitivamente
            if(i > 1)
            {
                WIN32sonsAvisos();
                ShellExecuteA(NULL, "open", URL3, NULL, NULL, SW_SHOWNORMAL);
                Sleep(j);
            }

            //Abre a pasta Documentos e toca um som de alerta do próprio Windows
            system(comandoAberturaDocumentos);
            WIN32sonsAvisos();

            //Diminui o tempo de espera entre uma abertura e outra da janela em 500ms, até um limite de j % 500
            if(j > 500) j -= 500;
            Sleep(j);
            i++;
            break;
        

        case 2:

            //Abre o link URL1 definido no inicio do programa na primeira iteração do laço
            if(i == 0)
            {
                WIN32sonsAvisos();
                ShellExecuteA(NULL, "open", URL1, NULL, NULL, SW_SHOWNORMAL);
                Sleep(5000);
            }

            //Abre o link URL2 definido no inicio do programa na segunda iteração do laço
            if(i == 1)
            {
                WIN32sonsAvisos();
                ShellExecuteA(NULL, "open", URL2, NULL, NULL, SW_SHOWNORMAL);
                Sleep(3000);
            }

            //Abre o link URL3 definido no início do programa repetitivamente
            if(i > 1)
            {
                WIN32sonsAvisos();
                ShellExecuteA(NULL, "open", URL3, NULL, NULL, SW_SHOWNORMAL);
                Sleep(j);
            }

            //Abre a pasta Imagens e toca um som de alerta do próprio Windows
            system(comandoAberturaImagens);
            WIN32sonsAvisos();

            //Diminui o tempo de espera entre uma abertura e outra da janela em 500ms, até um limite de j % 500
            if(j > 500) j -= 500;
            Sleep(j);
            i++;
            break;


        case 3:
            
            //Abre o link URL1 definido no inicio do programa na primeira iteração do laço
            if(i == 0)
            {
                WIN32sonsAvisos();
                ShellExecuteA(NULL, "open", URL1, NULL, NULL, SW_SHOWNORMAL);
                Sleep(5000);
            }

            //Abre o link URL2 definido no inicio do programa na segunda iteração do laço
            if(i == 1)
            {
                WIN32sonsAvisos();
                ShellExecuteA(NULL, "open", URL2, NULL, NULL, SW_SHOWNORMAL);
                Sleep(3000);
            }

            //Abre o link URL3 definido no início do programa repetitivamente
            if(i > 1)
            {
                WIN32sonsAvisos();
                ShellExecuteA(NULL, "open", URL3, NULL, NULL, SW_SHOWNORMAL);
                Sleep(j);
            }

            //Abre a pasta System32 e toca um som de alerta do próprio Windows
            system(comandoAberturaSystem32);
            WIN32sonsAvisos();

            //Diminui o tempo de espera entre uma abertura e outra da janela em 500ms, até um limite de j % 500
            if(j > 500) j -= 500;
            Sleep(j);
            i++;
            break;
        }
        
        memoriaRAM = WIN32verificaQuantidadeDisponivelMemoriaRAM();
    }

}



//Função que reinicia o computador
void WIN32reiniciaComputador()
{
    char comando[50];

    //Adiciona à string Comando o tempo desejado até a reinicialização do computador
    sprintf(comando, "shutdown /r /t %d", TEMPOREINICIALIZACAO);

    //Efetua o comando
    system(comando);
}