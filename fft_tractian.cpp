// fft_tractian.cpp
//g++ fft_tractian.cpp -lfftw3f -o fft_tractian

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <fftw3.h>
using namespace std;

#define N 4139 //numero de amostras de sinais
#define T 2715 //tempo da amostra em ms


//Funcao que abre arquivo txt e atribui a 3 vetores
void readData(fftwf_complex* ax, fftwf_complex* ay, fftwf_complex* az) {
    ifstream inFile;
    inFile.open("1602245833-2715-NAO7856.txt");
    string title, s, token;
    
    //le o x,y,z
    getline(inFile, title);

    //a partir daqui, tem apenas os dados do acelerometro
    for (int i = 0; i < N; i++){
        getline(inFile, s); //le linha do arquivo completo
        stringstream ss(s);

        //le cada numero separado por virgula
        getline(ss, token, ',');
        ax[i][0] = stof(token);
        getline(ss, token, ',');
        ay[i][0] = stof(token);
        getline(ss, token, ',');
        az[i][0] = stof(token);
    }
    inFile.close();
}

//Funcao que le os vetores construidos e executa a fft para cada um
void fft(fftwf_complex* inx, fftwf_complex* iny, fftwf_complex* inz, fftwf_complex* outx, fftwf_complex* outy, fftwf_complex* outz) {
    fftwf_plan plan = fftwf_plan_dft_1d(N, inx, outx, FFTW_FORWARD, FFTW_ESTIMATE);
    fftwf_execute(plan);
    fftwf_destroy_plan(plan);
    fftwf_cleanup();

    fftwf_plan plan2 = fftwf_plan_dft_1d(N, iny, outy, FFTW_FORWARD, FFTW_ESTIMATE);
    fftwf_execute(plan2);
    fftwf_destroy_plan(plan2);
    fftwf_cleanup();

    fftwf_plan plan3 = fftwf_plan_dft_1d(N, inz, outz, FFTW_FORWARD, FFTW_ESTIMATE);
    fftwf_execute(plan3);
    fftwf_destroy_plan(plan3);
    fftwf_cleanup();
}

//Funcao que escreve a parte real das FFTs calculadas + frequencia referente
void writeOutputData(fftwf_complex* ax_out, fftwf_complex* ay_out, fftwf_complex* az_out, double &fstep) {
    ofstream outFile;
    outFile.open("output.txt");
    for (int i = 0; i < N; i++) {
        outFile << ax_out[i][0] << "," << ay_out[i][0] << "," << az_out[i][0] << "," << i*fstep << endl; 
    }

    outFile.close();
}


int main() {
    //Declaracao de variaveis de operacao
    fftwf_complex ax[N], ay[N], az[N];
    fftwf_complex ax_out[N], ay_out[N], az_out[N];
    
    //Calculo do passo da frequencia
    double fstep = 1000/double(T); //em Hz 

    //Uso das funcoes 
    readData(ax, ay, az);
    fft(ax, ay, az, ax_out, ay_out, az_out);
    writeOutputData(ax_out, ay_out, az_out, fstep);

    return 0;
}