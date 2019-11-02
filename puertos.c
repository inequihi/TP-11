#include<stdio.h>
#include<stdint.h>
#include"puertos.h"

/*************************************ESTRUCTURAS*******************************/
struct Reg_D
{
    uint16_t d;
} ;
struct Reg_AyB
{
    uint8_t b;
    uint8_t a;
};

struct Reg_Bit
{
    uint16_t b0  :1 ;
    uint16_t b1  :1 ;
    uint16_t b2  :1 ;
    uint16_t b3  :1 ;
    uint16_t b4  :1 ;
    uint16_t b5  :1 ;
    uint16_t b6  :1 ;
    uint16_t b7  :1 ;
    uint16_t b8  :1 ;
    uint16_t b9  :1 ;
    uint16_t b10 :1 ;
    uint16_t b11 :1 ;
    uint16_t b12 :1 ;
    uint16_t b13 :1 ;
    uint16_t b14 :1 ;
    uint16_t b15 :1 ;
} ;

typedef union
{
	struct Reg_D rd;
	struct Reg_AyB ab;
	struct Reg_Bit bi;
} port_t;

static port_t PORT;

/*********************              FUNCIONES               ********************/


/*****************************Funcion: BitSet***********************************/
void bitSet(char puerto, int bit){
  if(puerto == 'd'&& (bit>=0) && (bit<16)){
    uint16_t mask = 0x0001;
    mask <<= (bit);
    PORT.rd.d = (PORT.rd.d) | (mask);
  }
  else if((bit>=0) && (bit<8)){
    if (puerto == 'a'){
      uint8_t mask = 0x01;
      mask <<= (bit);
      PORT.ab.a = (PORT.ab.a) | (mask);

    }
    else if (puerto == 'b'){
      uint8_t mask = 0x01;
      mask <<= (bit);
      PORT.ab.b = (PORT.ab.b) | (mask);
    }
  }
  else
    printf("Error, dato mal ingresado.\n");
}

/*****************************Funcion: BitClr***********************************/
void bitClr(char puerto, int bit){
  if(puerto == 'd'&& (bit>=0) && (bit<16)){
    uint16_t mask = 0x0001;
    mask <<= (bit);
    mask = ~mask;
    PORT.rd.d = (PORT.rd.d) & (mask);
  }
  else if((bit>=0) && (bit<8)){
    if (puerto == 'a'){
      uint8_t mask = 0x01;
      mask <<= (bit);
      mask = ~mask;
      PORT.ab.a = (PORT.ab.a) & (mask);
    }
    else if (puerto == 'b'){
      uint8_t mask = 0x01;
      mask <<= (bit);
      mask = ~mask;
      PORT.ab.b = (PORT.ab.b) & (mask);
    }
  }
  else
    printf("Error, dato mal ingresado.\n");
}

/*****************************Funcion: BitGet***********************************/
int bitGet(char puerto, int bit){
  int bitGive = -1;

  if(puerto == 'd'&& (bit>=0) && (bit<16)){
    uint16_t mask = 0x0001;
    mask <<= (bit);
    if((PORT.rd.d) & mask){                  //Si el resultado es != 0, entonces el bit es 1
      bitGive =1;
    }
    else
      bitGive = 0;
  }
  else if((bit>=0) && (bit<8)){
        if (puerto == 'a'){
          uint8_t mask = 0x01;                  //Haremos mascara con ceros y un 1 en bit a buscar
          mask <<= (bit);
          if((PORT.ab.a) & mask){             //Si el resultado es diferente != 0, entonces el bit es 1
            bitGive = 1;
          }
          else
            bitGive = 0;
        }
        else if (puerto == 'b'){
          uint8_t mask = 0x01;
          mask <<= (bit);
          if((PORT.ab.b) & mask){             //Si el resultado es 1, entonces el bit esta activado por lo que lo cambiamos a 0
            bitGive = 1;
          }
          else
            bitGive = 0;
        }
      }
  else
  {
    printf("Error, dato mal ingresado.\n");
  }
  return bitGive;

}

/*****************************Funcion: BitToggle********************************/
void bitToggle(char puerto, int bit){

    if(puerto == 'd'&& (bit>=0) && (bit<16)){
      uint16_t mask = 0x0001;
      mask <<= (bit);
      if((PORT.rd.d) & mask){             //Si el resultado es 1, entonces el bit esta activado por lo que lo cambiamos a 0
        mask = ~mask;
        PORT.rd.d = (PORT.rd.d) & (mask);
      }
      else
        PORT.rd.d = (PORT.rd.d) | (mask);
    }

    if((bit>=0) && (bit<8)){
          if (puerto == 'a'){
            uint8_t mask = 0x01;
            mask <<= (bit);
            if((PORT.ab.a) & mask){             //Si el resultado es 1, entonces el bit esta activado por lo que lo cambiamos a 0
              mask = ~mask;
              PORT.ab.a = (PORT.ab.a) & (mask);
            }
            else
              PORT.ab.a = (PORT.ab.a) | (mask);
          }
          else if (puerto == 'b'){
            uint8_t mask = 0x01;
            mask <<= (bit);
            if((PORT.ab.b) & mask){             //Si el resultado es 1, entonces el bit esta activado por lo que lo cambiamos a 0
              mask = ~mask;
              PORT.ab.b = (PORT.ab.b) & (mask);
            }
            else
              PORT.ab.b = (PORT.ab.b) | (mask);
          }
        }
        else
          printf("Error, dato mal ingresado.\n");
}

/*****************************Funcion: maskOn********************************/
void maskOn(char puerto, int mask){

    if(puerto == 'd'){
        PORT.rd.d = (PORT.rd.d) | mask;
      }
    else if (puerto == 'a'){
              PORT.ab.a = (PORT.ab.a) | mask;
            }
    else if (puerto == 'b'){
              PORT.ab.b = (PORT.ab.b) | mask;
            }
    else
          printf("Error, dato mal ingresado.\n");
}


/*****************************Funcion: maskOff********************************/
void maskOff(char puerto, int mask){

    if(puerto == 'd'){
        PORT.rd.d = (PORT.rd.d) & (~mask);
      }
    else if (puerto == 'a'){
              PORT.ab.a = (PORT.ab.a) & (~mask);
            }
    else if (puerto == 'b'){
              PORT.ab.b = (PORT.ab.b) & (~mask);
            }
    else
          printf("error, ha ingresado un dato erroneo");
}

/*****************************Funcion: maskToggle********************************/
void maskToggle(char puerto, int mask){

    if(puerto == 'd'){
        PORT.rd.d = (PORT.rd.d) ^ mask;
      }
    else if (puerto == 'a'){
              PORT.ab.a = (PORT.ab.a) ^ mask;
            }
    else if (puerto == 'b'){
              PORT.ab.b = (PORT.ab.b) ^ mask;
            }
    else
          printf("Error, dato mal ingresado.\n");
}
