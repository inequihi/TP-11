/***************************************************************************//**
  @file     +simulacion.h+
  @author   +The commune+
 ******************************************************************************/

#ifndef _SIMULACION_H_
#define _SIMULACION_H_

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

 /**
  * @brief  getVar si lo que ha ingresado el usuario es correcto, lo devuelve y sino devuelve error
  * @param nothing
  * @return var, lo que el usuario ha ingresado
  **/

	int getVar (void);

 /**
  * @brief  turnOn_turnOff analiza si el usuario quiere prender o apagar un led y realiza la accion
  * @param puertoA, puertoA a analizar
  * @param entry es el bit que el usuario ha ingresado
  * @return nothing
  **/

	void turnOn_turnOff (char puertoA, int entry);

 /**
  * @brief  printPort imprime el estado de los leds del puerto
  * @param puertoA, puertoA a analizar
  * @return nothing
  **/

	void printPort (char puertoA);

/**
  * @brief  printInstructions imprime las instrucciones para utilizar el programa
  * @param nothing
  * @return nothing
  **/

	void printInstructions (void);




/*******************************************************************************
 ******************************************************************************/

#endif // _SIMULACION_H_
