# fft_tractian
## Hardware R&amp;D Challenge - Resolution

Neste repositório constam os arquivos utilizados para resolver o problema proposto pelo enunciado (FFT para um acelerômetro), assim como o arquivo output.txt gerado pela rotina. O enunciado foi resolvido no Ubuntu 20.04.

Para utilizar a rotina desenvolvida, primeiramente, é necessário instalar a biblioteca FFTW3. Para isso, siga o tutorial:
https://www.youtube.com/watch?v=oWsjHU2xHWU

Concluída a instalação, para compilar o programa, acesse a pasta pelo prompt de comando e digite:
> g++ fft_tractian.cpp -lfftw3f -o fft_tractian

Ao compilar, note que será gerado um executável no mesmo diretório do programa .cpp. Para executá-lo e, consequentemente, gerar o arquivo "output.txt", digite:
> ./fft_tractian

Ao fim destes comandos, o output.txt deve ser gerado.
