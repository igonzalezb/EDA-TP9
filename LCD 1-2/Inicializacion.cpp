//
//Para inicializar en el modo de 4 bits debemos seguir esta secuencia :
//1. Enviar el nibble alto de �function set� con el modo en 8 bits
//2. Esperar 4 ms
//3. Enviar el nibble alto de �function set� con el modo en 8 bits
//4. Esperar 100 �s
//5. Enviar el nibble alto de �function set� con el modo en 8 bits
//6. Enviar el nibble alto de �function set� con el modo en 4 bits.
//(a partir de ahora enviamos las instrucciones separadas en dos nibbles)
//7. Enviar la instrucci�n �function set� con el modo en 4 bits, 2 l�neas y fuente de 5x8
//8. Enviar la instrucci�n �display on / off control� con todo apagado
//9. Enviar la instrucci�n �clear screen�
//10. Enviar la instrucci�n �entry mode set�
//Para referencias del fabricante, ver la hoja de datos(Figura 24).



//Inicializa el FTDI y el LCD
FT_HANDLE * deviceHandler lcdInit(int iDevice)
{

}