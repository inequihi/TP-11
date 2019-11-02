/***************************************************************************//**
  @file     +puertos.h+
  @author   +The commune+
 ******************************************************************************/

#ifndef _PUERTOS_H_
#define _PUERTOS_H_

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

 /**
  * @brief  BitSet cambia el estado de un bit a 1
  * @param puerto, puerto a analizar
  * @param bit, bit a analizar
  * @return nothing
  **/
  void bitSet(char puerto, int bit);

/**
 * @brief  BitClr cambia el estado de un bit a 0
 * @param puerto, puerto a analizar
 * @param bit, bit a analizar
 * @return nothing
 **/
void bitClr(char puerto, int bit);

 /**
  * @brief  BitGet devuelve el valor de determinado bit de un puerto
  * @param puerto, puerto a analizar
  * @param bit, bit a devolver
  * @return bit, (1, 0 o -1)
  **/
  int bitGet(char puerto, int bit);

  /**
   * @brief  BitToggle cambia el estado de un bit al en el que está
   * (si está en 0 pasar a 1, y si está en 1 pasar a 0).
   * @param puerto, puerto a analizar
   * @param bit, bit a analizar
   * @return entero
   **/
   void bitToggle(char puerto, int bit);

  /**
   * @brief  maskOn prende todos aquellos bits que estén prendidos en la máscara,
   * sin cambiar el estado de los restantes.
   * @param puerto, puero a analizar
   * @param mask, mascara a aplicar sobre valor del puerto
   * @return nothing
   **/
    void maskOn(char puerto, int mask);

  /**
   * @brief  maskOff apaga todos aquellos bits que estén prendidos en la máscara,
   * sin cambiar el estado de los restantes.
   * @param puerto, puero a analizar
   * @param mask, mascara a aplicar sobre valor del puerto
   * @return nothing
   **/
    void maskOff(char puerto, int mask);

  /**
   * @brief maskToggle cambiar el estado de todos
   * aquellos bits que estén prendidos en la máscara al opuesto, sin cambiar el
   * estado de los restantes.
   * @param puerto, puero a analizar
   * @param mask, mascara a aplicar sobre valor del puerto
   * @return nothing
   **/
    void maskToggle(char puerto, int mask);

/*******************************************************************************
 ******************************************************************************/

#endif // _PUERTOS_H_
