Tarefa Sinal - 85%

O feixe de luz produzido pelo diodo laser será analisado por outro dispositivo. Para que o feixe de luz seja identificado como um sinal de tiro UIPM, deve se seguir diversas regras, essas regras são impostas para que na eletrônica de destino consiga identificar um sinal que não é um UIPM de um sinal UIPM.

{"A forma do Código é definida como uma sequência de tempo para obter

um Sinal Exclusivo de Código A estático que deve ser diferente de outros Sinais nos arredores. A identificação como um sinal de tiro UIPM válido é realizada analisando o

forma de código de um sinal recebido pela eletrônica de destino." Retirado e traduzido da memória descritiva}

Regras:

Sobre o duty cycle:

Numa onda quadrada de duty cycle de 50%, significa que o pulso deve ter 50% de seu tempo em estado HIGH (VCC), e 50% do seu pulso em LOW(GND).

Sobre a frequência:

Foi estabelecido que o sinal tenha uma frequencia de 40Khz, podendo ter variação de +ou- 2Khz.

Numa frequência de 40khz, tendo um 1 segundo 1.000.000 de microssegundos, temos 40.000 pulsos. Logo cada pulso terá a duração de 25(us) microssegundos. Como o duty cycle é de 50%, temos 12,5(us) microssegundos em HIGH e 12,5(us) microssegundos para LOW.

Sobre a correspondência do sinal previsto com o avaliado:

Devido a diversos fatores, como o clima, temperatura, umidade, intensidade luminosa do ambiente, pode se prejudicar o recebimento do sinal no dispositivo de avaliação, logo, e aceitável que o sinal avaliado corresponda a 80% do sinal previsto.

UIPM:

O sinal deve ter a duração total de 15.6(ms) milissegundos, e com a seguinte sequência:

S-11010111

**S -\>** Pulso de sinal inicial que informa ao dispositivo receptor que os próximos pulsos é um sinal UIPM, é uma sequência de duração total de 3.0(ms) milissegundos, sendo:

2,4(ms) milissegundos de uma onda quadrada de 96 pulsos de 25(us) microssegundos \*(12,5(us) microssegundos em HIGH e 12,5(us) microssegundos em LOW)\*

0,6(ms) milissegundos em LOW

**1-** Lógica "1", é uma sequência de duração total de 1,8(ms) milissegundos, sendo:

1,2(ms) de uma onda quadrada com 48 pulsos de 25(us) microssegundos \*(12,5(us) microssegundos em HIGH e 12,5(us) microssegundos em LOW) \*

0,6(ms) milissegundos em LOW.

**0-** Lógica "0", é uma sequência de duração total de 1,2(ms) milissegundos, sendo:

0,6(ms) de uma onda quadrada com 24 pulsos de 25(us) microssegundos \*(12,5(us) microssegundos em HIGH e 12,5(us) microssegundos em LOW)\*

0,6(ms) milissegundos em LOW

{Se 80% ou mais da forma do sinal (código do sinal) forem detectados, o sinal deve ser aceito como um

sinal UIPM correto e deve causar uma indicação de "acerto". Retirado e traduzido da memória descritiva}

Regras ademais da memória descritiva referem-se a potência do led, campo de dissipação, entre outros fatores que não podem ser ajustados via codigo pois se referem ao hardware (diodo laser). O diodo laser deve ser escolhido de acordo com as regras selecionadas a hardware.

**Explicação do código em relação ao UIPM.**

O código fornecido é um programa para o Arduino que implementa o sinal Laser UIPM de acordo com as regras descritas na memória descritiva fornecida. Vou explicar a parte relevante do código que se refere à sequência do sinal UIPM.

Antes de explicar o código, é importante observar que o valor de onTime é definido em 7.1 microssegundos, que é um valor simulado para a duração do pulso do laser, este valor foi definido após diversos testes na plataforma Proteus, que devido a suas limitações técnicas não produz o resultado como a prática. Conforme mencionado no texto, o valor real seria de 12.5 microssegundos, que na prática também deverá ser ajustado, pois os microcontroladores sofrem diversos atrasos.

O sinal Laser UIPM é composto por uma sequência de pulsos e espaços definidos em microssegundos. A função uIPMSignal() é responsável por enviar essa sequência:

void uIPMSignal() {

sequenciaInicial(); //2.4ms + 0.6ms = 3ms

umLogico(true); //1.2ms + 0.6ms = 1.8ms

umLogico(true); //1.2ms + 0.6ms = 1.8ms

zeroLogico(); //0.6ms + 0.6ms = 1.2ms

umLogico(true); //1.2ms + 0.6ms = 1.8ms

zeroLogico(); //0.6ms + 0.6ms = 1.2ms

umLogico(true); //1.2ms + 0.6ms = 1.8ms

umLogico(true); //1.2ms + 0.6ms = 1.8ms

umLogico(false); //1.2ms = 1.2ms

//TOTAL: 15.6ms

}

A função uIPMSignal() chama várias outras funções para formar o sinal Laser UIPM:

sequenciaInicial(): Gera a sequência inicial do sinal, que consiste em 96 pulsos com duração de 2.4ms, seguidos de um espaço de 0.6ms. Esse trecho totaliza 3ms.

umLogico(true): Gera um 'um' lógico. A função gera 48 pulsos, cada um com 1.2ms de duração, seguidos de um espaço de 0.6ms. Neste caso, também há um atraso de 0.6ms após o espaço para corresponder à regra descrita na memória descritiva. Isso totaliza 1.8ms de duração.

zeroLogico(): Gera um 'zero' lógico. A função gera 24 pulsos, cada um com 0.6ms de duração, seguidos de um espaço de 0.6ms. Isso totaliza 1.2ms de duração.

A sequência completa de sinal gerada pela função uIPMSignal() terá a duração total de 15.6ms, conforme especificado na memória descritiva.

**Algumas Imagens:**

Duração total do sinal UIPM no osciloscópio do Proteus:

![](RackMultipart20230802-1-8hlb9c_html_4c79bc0f6a9dbfb5.png)

![](RackMultipart20230802-1-8hlb9c_html_e8a58bbcc0f0071b.png)

Duração de cada pulso em HIGH e LOW do sinal UIPM no osciloscópio do Proteus:

![](RackMultipart20230802-1-8hlb9c_html_889fd90ba976b9b8.png)

![](RackMultipart20230802-1-8hlb9c_html_a47a5f476e7cb76e.png)
