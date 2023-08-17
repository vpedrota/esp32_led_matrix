#include <FastLED.h>
#include <string.h>

#define WIDTH 16
#define HEIGHT 8
#define CHAR_WIDTH 3
#define CHAR_HEIGHT 5
#define NUM_LEDS 128 
#define DATA_PIN 13 

CRGB leds[NUM_LEDS];

typedef struct {
    bool leds[HEIGHT][WIDTH];
} LedMatrix;

LedMatrix matrix;


int ALPHABET_3x5[27][5][3] = {
    // A
    {
        {0, 1, 0},
        {1, 0, 1},
        {1, 1, 1},
        {1, 0, 1},
        {1, 0, 1}
    },
    // B
    {
        {1, 1, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 0, 1},
        {1, 1, 0}
    },
    // C
    {
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {0, 1, 1}
    },
    // D
    {
        {1, 1, 0},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 0}
    },
    // E
    {
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1}
    },
    // F
    {
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1},
        {1, 0, 0},
        {1, 0, 0}
    },
    // G
    {
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 1},
        {1, 0, 1},
        {0, 1, 1}
    },
    // H
    {
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {1, 0, 1},
        {1, 0, 1}
    },
    // I
    {
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
    },
    // J
    {
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1},
        {1, 0, 1},
        {0, 1, 0}
    },
    // K
    {
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 0},
        {1, 0, 1},
        {1, 0, 1}
    },
    // L
    {
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 1, 1}
    },
    // M
    {
        {1, 0, 1},
        {1, 1, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1}
    },
    // N
    {
        {1, 0, 1},
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1},
        {1, 0, 1}
    },
    // O
    {
        {0, 1, 0},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {0, 1, 0}
    },
    // P
    {
        {1, 1, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 0, 0},
        {1, 0, 0}
    },
    // Q
    {
        {0, 1, 0},
        {1, 0, 1},
        {1, 0, 1},
        {0, 1, 0},
        {0, 0, 1}
    },
    // R
    {
        {1, 1, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 0, 1},
        {1, 0, 1}
    },
    // S
    {
        {0, 1, 1},
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 0}
    },
    // T
    {
        {1, 1, 1},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
    },
    // U
    {
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1}
    },
    // V
    {
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {0, 1, 0},
        {0, 1, 0}
    },
    // W
    {
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {1, 1, 1},
        {1, 0, 1}
    },
    // X
    {
        {1, 0, 1},
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1},
        {1, 0, 1}
    },
    // Y
    {
        {1, 0, 1},
        {1, 0, 1},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
    },
    // Z
    {
        {1, 1, 1},
        {0, 0, 1},
        {0, 1, 0},
        {1, 0, 0},
        {1, 1, 1}
    }
};

void initializeLedMatrix(LedMatrix *matrix) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      matrix->leds[y][x] = false;
    }
  }
}

void displayCharacterOnLedMatrix(LedMatrix *matrix, int c[][3], int offsetX, int offsetY) {

  for (int y = 0; y < CHAR_HEIGHT; y++) {
    for (int x = 0; x < CHAR_WIDTH; x++) {
      int matrixX = x + offsetX;
      int matrixY = y + offsetY;
      
      if (matrixX >= 0 && matrixX < WIDTH && matrixY >= 0 && matrixY < HEIGHT) {
        matrix->leds[matrixY][matrixX] = c[CHAR_HEIGHT - y - 1][x];
      }
    }
  }
}

int return_led_position(int x, int y) {

  int compensation = 0;
  if (y >= 8) {
      y -= 8;
      compensation = 64;
  }

  if (x % 2) y = 7 - y;

  return x * 8 + y + compensation;
}


void printPhrase(char *phrase){

  int positionX = WIDTH; 
  int positionY = (HEIGHT - CHAR_HEIGHT) / 2; 
  int i, j, space = 0;
  
  while (positionX >= -(CHAR_WIDTH+1) * ((int) strlen(phrase))) {

    initializeLedMatrix(&matrix);  

    
    space = 0;
    for(i = 0; i < strlen(phrase); i++){
        if(phrase[i] == ' ') {
            space+=2;
            continue;
        };

        if(phrase[i] == 'i'){
            space-=1;
        }
        
        displayCharacterOnLedMatrix(&matrix,  ALPHABET_3x5[phrase[i] - 'a'], positionX + space, positionY);

        if(phrase[i] == 'i'){
            space-=1;
        }

        space+=4;
    }
   
    for(i = 0; i < HEIGHT; i++){
      for ( j = 0; j < WIDTH; j++) {
        leds[return_led_position(i, j)] =  matrix.leds[i][j] ? CRGB::Green : CRGB::Pink;
      }
    }

    FastLED.show();
    
    positionX--;

    delay(100);
  }

}

void setup(){
  initializeLedMatrix(&matrix);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
}

void loop() {
    char* teste = "o palmeiras nao tem mundial";
    printPhrase(teste);
  
}