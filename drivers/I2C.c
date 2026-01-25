#include drivers/I2C.h

//------------------------------------------------------------------------------
//-------------------------Inicializar I2C--------------------------------------
//------------------------------------------------------------------------------
void I2C_Initialize(void)                                                       //Begin IIC as master
{
  TRISBbits.RB0 = 1;                                                            //Set SDA and SCL pins as input pins
  TRISBbits.RB1 = 1;                                                            //Set SDA and SCL pins as input pins
  
  SSPCON1  = 0x28;                                                              //pg84/234 
  SSPCON2 = 0x00;                                                               //pg85/234
  
  SSPADD = 0x77;
  SSPSTAT = 0x80;                                                               //pg83/234
}
//------------------------------------------------------------------------------
//---------------------------I2C chequeo----------------------------------------
//------------------------------------------------------------------------------
void I2C_Check(void) 
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F))
    {
    }
}
//------------------------------------------------------------------------------
//-----------------------------I2C CFG------------------------------------------
//------------------------------------------------------------------------------
void I2C_Cmd(unsigned char Dir,unsigned char Cfg,unsigned char Cmd)
{
    I2C_Check();
    SSPCON2bits.SEN = 1;                                                        //Activo el start
    while (SSPCON2bits.SEN)                                                     //verifico el start
    {
    }
    I2C_Check();
    SSPBUF = Dir;                                                               //ingreso direccion esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT)                                                 //verifico reconocimiento
    {
        
    }
    I2C_Check();                                                                //verifico el bus
    SSPBUF = Cfg;                                                               //ingreso configuracion para esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT)                                                 //verifico reconocimiento
    {

    }
    I2C_Check();                                                                //verifico el bus
    SSPBUF = Cmd;                                                               //ingreso comando para esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT)                                                 //verifico reconocimiento
    {

    }
//********************************Stop******************************************
    I2C_Check();
    SSPCON2bits.PEN = 1;                                                        //activo stop
    while (!SSPSTATbits.P)                                                      //verifico si termino el stop
    {
    }    
}
//------------------------------------------------------------------------------
//-----------------------------I2C WRITE----------------------------------------
//------------------------------------------------------------------------------
void I2C_Write(uint8_t DirW,uint8_t CmdW,uint8_t DirW2)
{
    I2C_Check();
    SSPCON2bits.SEN = 1;                                                        //Activo el start
    while (SSPCON2bits.SEN)                                                     //verifico el start
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPBUF = DirW;                                                              //ingreso direccion esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT)                                                 //verifico reconocimiento
    {

    }   
//******************************************************************************    
    I2C_Check();                                                                //verifico el bus
    SSPBUF = CmdW;                                                              //ingreso comando para esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT)                                                 //verifico reconocimiento
    {
    }
//******************************************************************************    
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RSEN = 1;                                                       //reinicio start
    while (!SSPCON2bits.RSEN)                                                   //verifico el restart
    {
    }
//******************************************************************************    
    I2C_Check();                                                                //verifico el bus
    SSPBUF = DirW2;                                                             //ingreso direccion esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
    I2C_Check();                                                                //verifico el bus
    while (SSPCON2bits.ACKSTAT)                                                 //verifico reconocimiento
    {
    }   
}
//------------------------------------------------------------------------------
//---------------------------I2C READ 8 BITS------------------------------------
//------------------------------------------------------------------------------
int8_t I2C_Read_8bits(void)
{ 
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    while(!SSPSTATbits.BF)                                                      //verifico si termino la recepcion
    {
    }
    DATO_I2C_8bits = SSPBUF;    
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT = 1;                                                      // 1 = NACK (NOACK)
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      // Inicia la secuencia
    while(SSPCON2bits.ACKEN);                                                   // Esperar hasta que termino  
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.PEN = 1;                                                        //activo stop
    while (!SSPSTATbits.P)                                                      //verifico si termino el stop
    {
    }
    return DATO_I2C_8bits;
}    
//------------------------------------------------------------------------------
//---------------------------I2C READ 8 BITS 3 bytes----------------------------
//------------------------------------------------------------------------------
void I2C_Read_8bits_3bytes(void)
{
    // Leer MSB (primer byte)
    I2C_Check();
    SSPCON2bits.RCEN = 1;                                                       //Habilito al master como receptor
    while (SSPCON2bits.RCEN);                                                   //Espero
    DATO_READ_8b_3 = SSPBUF;                                                    //Se guarda dato en el byte MSB
    I2C_Check();
    SSPCON2bits.ACKDT = 0;   // ACK para seguir leyendo
    I2C_Check();
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    I2C_Check();

    // Leer LSB (segundo byte)
    SSPCON2bits.RCEN = 1;
    while (SSPCON2bits.RCEN);
    DATO_READ_8b_2 = SSPBUF;  // ? temp_lsb    
    I2C_Check();
    SSPCON2bits.ACKDT = 0;   // ACK para seguir leyendo
    I2C_Check();
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    I2C_Check();

    // Leer XLSB (tercer byte)
    SSPCON2bits.RCEN = 1;
    while (SSPCON2bits.RCEN);
    DATO_READ_8b_1 = SSPBUF;  // ? temp_xlsb    
    I2C_Check();
    SSPCON2bits.ACKDT = 1;   // NACK para terminar lectura
    I2C_Check();
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    I2C_Check();

    // Stop condition
    SSPCON2bits.PEN = 1;
    while (!SSPSTATbits.P);
}
//------------------------------------------------------------------------------
//---------------------------I2C READ 8 BITS N bytes----------------------------
//------------------------------------------------------------------------------
void I2C_Read_8bits_Nbytes(uint8_t Nbytes)
{
    uint8_t i;

    for (i = 0; i < Nbytes; i++)
    {
        SSPCON2bits.RCEN = 1;                   // Habilita recepci�n
        while(!SSPSTATbits.BF);                 // Esperar byte recibido
        read_datos[i] = SSPBUF;                 // Leer dato

        // ACK o NACK
        if (i < (Nbytes - 1))
            SSPCON2bits.ACKDT = 0;              // ACK
        else
            SSPCON2bits.ACKDT = 1;              // NACK (�ltimo byte)

        SSPCON2bits.ACKEN = 1;                  // Enviar ACK/NACK
        while(SSPCON2bits.ACKEN);
    }

    // STOP
    SSPCON2bits.PEN = 1;
    while(SSPCON2bits.PEN);
}
//------------------------------------------------------------------------------
//--------------------------------I2C Write-------------------------------------
//------------------------------------------------------------------------------
void I2C_Write_(uint8_t direccion)
{
        I2C_Check();                                                            //verifico el bus
        SSPBUF = direccion;                                                     //ingreso direccion esclavo        
        while (SSPSTATbits.BF)                                                  //verifico si termino la transmision
            {
            }       
        I2C_Check();   
        while (SSPCON2bits.ACKSTAT)                                             //verifico reconocimiento
            {
            }
}
//------------------------------------------------------------------------------
//--------------------------------I2C STOP--------------------------------------
//------------------------------------------------------------------------------
void I2C_Stop(void)
{
    I2C_Check();
    SSPCON2bits.PEN = 1;
    while (!SSPSTATbits.P);
}
//------------------------------------------------------------------------------
//--------------------------------I2C START-------------------------------------
//------------------------------------------------------------------------------
void I2C_Start(void)
{
    I2C_Check();
    SSPCON2bits.SEN = 1;                                                        //Activo el start
    while (SSPCON2bits.SEN)                                                     //verifico el start
    {
    }    
}
//------------------------------------------------------------------------------
//--------------------------------I2C Re-START----------------------------------
//------------------------------------------------------------------------------
void I2C_Rstart(void)
{
    I2C_Check();
    SSPCON2bits.RSEN = 1;
    while (SSPCON2bits.RSEN);
}
//------------------------------------------------------------------------------
//--------------------------------I2C RCEP--------------------------------------
//------------------------------------------------------------------------------
uint8_t I2C_RCEP(void)
{
    I2C_Check();
    SSPCON2bits.RCEN = 1;                                                       // Habilita la recepción
    while (!SSPSTATbits.BF);
    DATO_I2C_8bits = SSPBUF;
    return DATO_I2C_8bits;
}
//------------------------------------------------------------------------------
//--------------------------------I2C Lec_fin-----------------------------------
//------------------------------------------------------------------------------
void I2C_Lec_fin(void)
{
    I2C_Check();    
    SSPCON2bits.ACKDT = 1;                                                      // NACK
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
}
//------------------------------------------------------------------------------
//--------------------------------I2C Lec_Seg-----------------------------------
//------------------------------------------------------------------------------
void I2C_Lec_seg(void)
{
    I2C_Check();
    SSPCON2bits.ACKDT = 0;
    I2C_Check();
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
}
//------------------------------------------------------------------------------
//-----------------------------I2C CFG REG--------------------------------------
//------------------------------------------------------------------------------
void I2C_CFG_REG(unsigned char address,unsigned char registro,unsigned char dataM,unsigned char dataL)
{
    I2C_Check();
    SSPCON2bits.SEN = 1;                                                        //Activo el start
    while (SSPCON2bits.SEN)                                                     //verifico el start
    {
    }
    I2C_Check();
    SSPBUF = address;                                                           //ingreso direccion esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT)                                                 //verifico reconocimiento
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPBUF = registro;                                                          //ingreso configuracion para esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
    while (SSPCON2bits.ACKSTAT)                                                 //verifico reconocimiento
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPBUF = dataM;                                                             //ingreso comando para esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
    while (SSPCON2bits.ACKSTAT)                                                 //verifico reconocimiento
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPBUF = dataL;                                                             //ingreso comando para esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
    while (SSPCON2bits.ACKSTAT)                                                 //verifico reconocimiento
    {
    }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-----------------------------I2C puntero--------------------------------------
//------------------------------------------------------------------------------
void I2C_PUNTERO(unsigned char address, unsigned char puntero)
{
    I2C_Check();
    SSPCON2bits.SEN = 1;                                                        //Activo el start
    while (SSPCON2bits.SEN)                                                     //verifico el start
    {
    }
    I2C_Check();
    SSPBUF = address;                                                           //ingreso direccion esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT)                                                 //verifico reconocimiento
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPBUF = puntero;                                                           //ingreso configuracion para esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
    while (SSPCON2bits.ACKSTAT)                                                 //verifico reconocimiento
    {
    }
    I2C_Check();                                                                //verifico el bus
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-----------------------------I2C lectura----------------------------------------
//------------------------------------------------------------------------------
void I2C_Lectura(uint8_t address)
{
    I2C_Check();
    SSPCON2bits.SEN = 1;                                                        //Activo el start
    while (SSPCON2bits.SEN)                                                     //verifico el start
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPBUF = address;                                                           //ingreso direccion esclavo
    while (SSPSTATbits.BF)                                                      //verifico si termino la transmision
    {
    }
//--------------------------------MSB-------------------------------------------    
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    while (SSPCON2bits.RCEN)                                                    //verifico si termino la recepcion
    {
    }
    I2CDATOMSB = SSPBUF;
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT =0;                                                       //acknowledge
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      //Acknowledge secuencia
    while (SSPCON2bits.ACKEN)   
    {  
    }
//-------------------------------LSB--------------------------------------------
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    while (SSPCON2bits.RCEN)                                                    //verifico si termino la recepcion
    {
    }
    I2CDATOLSB = SSPBUF;
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT =1;                                                       //acknowledge
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      //Acknowledge secuencia
    while (SSPCON2bits.ACKEN)   
    { 
    }
}    
