/**

  @Nom du fichier
    main.c

  @Auteur
    Sonia Michaud
   
  @Sommaire
    Programme qui écrit à l?écran I2C

*/

#include "mcc_generated_files/mcc.h"

#define ADDRESSE_I2C_ECRAN  40			//0x28
#define ADDRESSE_I2C_EEPROM  80			//0x50

/*
    Début de l'application principale
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    //message pour l'étape d'écriture sur l'écran
    uint8_t message[20];

    message[0]='0';
    message[1]='1';
    message[2]='2';
    
    //adresse pour le eeprom, et donnee d'écriture
    uint8_t addr[20];
    
    addr[0]=0x00;
    addr[1]=0x00;
    addr[2]=0x30;
    addr[3]=0x40;
    addr[4]=0x50;
    
    //tbleau de lecture
    uint8_t read[20];
    
    while (1)
    {
        /*
        //Code qui écrit 3 caractères sur l'écran
        while(I2C_Open(ADDRESSE_I2C_ECRAN) == I2C_BUSY);    //Passage de l'adresse
        I2C_SetBuffer(message, 3);                          //Passage des données
        I2C_MasterOperation(0);                             //Démarrer une opération d'écriture
        while (I2C_Close() == I2C_BUSY);                   	//Attendre que l'opération soit complète    

        __delay_ms(1000);
        */
        
        
        
        // Code qui lit 3 octets de la mémoire EEPROM
        __delay_ms(1000);
        // Écriture de deux octets de données à la EEPROM
        while(I2C_Open(ADDRESSE_I2C_EEPROM) == I2C_BUSY);   //passage de l?adresse I2C
        I2C_SetBuffer(addr, 5);				//passage de l?adresse interne sur 2 octets
        I2C_MasterOperation(0);				//opération d?écriture pour l?adresse interne
        while (I2C_Close() == I2C_BUSY);
        __delay_ms(5);

        // Lecture de 3 octets de la EEPROM
        while(I2C_Open(ADDRESSE_I2C_EEPROM) == I2C_BUSY);	//passage de l?adresse I2C
        I2C_SetBuffer(addr, 2);				//passage de l?adresse interne sur 2 octets
        I2C_MasterOperation(0);             //opération d?écriture pour l?adresse interne
        I2C_SetBuffer(read,3);			//lectures à faire dans le tableau de lecture
        I2C_MasterOperation(1);		//opération de lecture
        while (I2C_Close() == I2C_BUSY);
        __delay_ms(5);
        
        while(I2C_Open(ADDRESSE_I2C_ECRAN) == I2C_BUSY);    //Passage de l'adresse
        I2C_SetBuffer(read,3);                          //Passage des données
        I2C_MasterOperation(0);                             //Démarrer une opération d'écriture
        while (I2C_Close() == I2C_BUSY);                   	//Attendre que l'opération soit complète    
    }
    
}
