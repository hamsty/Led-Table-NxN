# Driver de Mesas de Led NxN


## Introdução

Esse driver permite controlar uma mesa de led NxN, usando a biblioteca [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) para gerar os desenhos e a biblioteca [Adafruit Neopixel](https://github.com/adafruit/Adafruit_NeoPixel) para endereçá-los na mesa. 

## Funções

Todas as funções de desenho da biblioteca da Adafruit estão disponíveis para esse Driver. O construtor publico se comporta como o do Adafruit Neopixel, sendo que N ao invés de ser o numero de pixels é o numero do quadrado de pixels. Existem duas funções adicionais: 

- `uint32_t getPixel(int n);` 

    É usada para uso principalmente na virtualização da mesa de led

- `void show(void);`

    É usada para tornar publico o show da Adafruit Neopixel, pois a variável que guarda ela é privada. 

## Casos de Uso

É utilizada nos projetos [Hello_Kitty](https://github.com/hamsty/HelloKitty/), [Jogo_da_Memoria](https://github.com/hamsty/Jogo_da_Memoria/) e [Cursor_12x12](https://github.com/hamsty/Cursor_12x12/).
