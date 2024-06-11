#include "GestorConfig.h"

/// @brief Metodo para cargar la configuración desde un fichero, 
void GestorConfig::RefreshConfig(MngrDisplays mngr)
{
    // Realizamos la carga de refresco
    //...

    // Y ponemos la nueva config en los Displays
   // SetConfig(mngr);

}

GestorConfig::GestorConfig(HoraLocal* ahora) 
{
    cf = new ConfigGeneral(ahora);
}

GestorConfig::~GestorConfig()
{
}


void GestorConfig::setBrillo(u_int8_t b)
{
    brilloDisplay = b;
}

u_int8_t GestorConfig::getBrillo()
{
    return brilloDisplay;
}

void GestorConfig::SetConfig(MngrDisplays mngr, HoraLocal* ahora)
{
    

    // Config Texto
    DisplayTexto* dspTxt =  (DisplayTexto*)mngr.GetDisplay(0);
    //dspTxt->setTexto(this->txtPpal);
    dspTxt->setCnf(*cf);

    // Config Hora
    DisplayHora* dspH =  (DisplayHora*)mngr.GetDisplay(1);
    //dspH->setTexto("DESPIERTA!!");
    dspH->setCnf(*cf);

        // Config Dibujos
    DisplayDibujos* dspDib =  (DisplayDibujos*)mngr.GetDisplay(2);
    dspDib->setCnf(*cf);
        // Config Config
    DisplayConfig* dspCnf =  (DisplayConfig*)mngr.GetDisplay(3);
    dspCnf->setCnf(*cf);
    //
}

/// @brief A partir de la cadena enviada por Bluetooth se obtiene la configuración. El formato será:
///  [texto mensaje 1]#[texto mensaje 2]#[textoAlaram]#[textoDibujos]#horaActual[HH:mm:ss]#DiaActual#HoraAlarma[HH:mm:ss]#AlarmaActiva[1|0]#SonarFinSemana[1|0]#HoraIniModoNoche[21]#HoraFinModoNoche[7]#
/// @param cadenaLeida 
void GestorConfig::CargarConfig(char *cadenaLeida)
{

    /*****************  [textomensaje] *********************************/

    char* token = strtok(cadenaLeida, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [texto mensaje]");
        return;
    }
    Serial.print("textomensaje1: ");
    Serial.println(token);
    cf->textoMensajes = token+'\0';
    /*****************  [textomensaje 2] *********************************/

    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [texto mensaje 2]");
        return;
    }
    Serial.print("textomensaje 2: ");
    Serial.println(token);
    cf->textoMensajes2 = token+'\0';
    //[]
    /*****************  [textoAlaram] *********************************/
    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [textoAlaram]");
        return;
    }
    Serial.print("textoAlarma: ");
    Serial.println(token);
    cf->textoAlarma = token+'\0';

    /*****************  [textoDibujos] *********************************/
    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [textoDibujos]");
        return;
    }
    Serial.print("texto Dibujos: ");
    Serial.println(token);
    cf->textoDibujos = token+'\0';


    /*****************  [Hora Actual] *********************************/
    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [hora]");
        return;
    }
    Serial.print("Hora:  ");
    Serial.println(token);
    char extractedChars[3]; // Necesitamos 3 espacios: 2 caracteres + 1 para el terminador nulo
    extractedChars[0] = token[0]; // Posición 3 (índice 2)
    extractedChars[1] = token[1]; // Posición 4 (índice 3)
    extractedChars[2] = '\0'; // Terminador nulo para formar una cadena válida

      // Convertir los caracteres extraídos a un entero
    cf->horaActual->hours = atoi(extractedChars);

    extractedChars[0] = token[3]; 
    extractedChars[1] = token[4]; 
    extractedChars[2] = '\0'; // Terminador nulo para formar una cadena válida
    cf->horaActual->minutes = atoi(extractedChars);

    
    extractedChars[0] = token[6]; 
    extractedChars[1] = token[7]; 
    extractedChars[2] = '\0'; // Terminador nulo para formar una cadena válida
    cf->horaActual->seconds = atoi(extractedChars);
    Serial.println(cf->horaActual->getFormattedTime());

    /*****************  [DiaActual] *********************************/
    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [DiaActual]");
        return;
    }
    Serial.print("Dia Actual: ");
    Serial.println(token);
    //cf->diaActual = token+'\0';

    /*****************  [HoraAlarma] *********************************/
    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [HoraAlarma]");
        return;
    }
    Serial.print("Alarma: ");
    Serial.println(token);
    extractedChars[0] = token[0]; // Posición 3 (índice 2)
    extractedChars[1] = token[1]; // Posición 4 (índice 3)
    extractedChars[2] = '\0'; // Terminador nulo para formar una cadena válida

      // Convertir los caracteres extraídos a un entero
    cf->horaAlarma->hours = atoi(extractedChars);

    extractedChars[0] = token[3]; 
    extractedChars[1] = token[4]; 
    extractedChars[2] = '\0'; // Terminador nulo para formar una cadena válida
    cf->horaAlarma->minutes = atoi(extractedChars);

    
    extractedChars[0] = token[6]; 
    extractedChars[1] = token[7]; 
    extractedChars[2] = '\0'; // Terminador nulo para formar una cadena válida
    cf->horaAlarma->seconds = atoi(extractedChars);
    Serial.println(cf->horaAlarma->getFormattedTime());

    /*****************  [AlarmaActiva] *********************************/
    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [AlarmaActiva]");
        return;
    }
    Serial.print("Alarma ON/OFF: ");
    Serial.println(token);
    cf->AlarmaActiva = token[0]=='1';
    
    /*****************  [SonarFinSemana] *********************************/
    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [SonarFinSemana]");
        return;
    }
    Serial.print("Sonar FdS: ");
    Serial.println(token);
    //cf-> = token[0]=='1';;
        
    /*****************  [HoraIniModoNoche] *********************************/
    // token = strtok(nullptr, "#");
    // if(token==nullptr)
    // {
    //     Serial.println("ERROR: no se enuentra info [HoraIniModoNoche]");
    //     return;
    // }
    // Serial.print("Mono Noche Empieza: ");
    // Serial.println(token);
    // cf->HoraIniNoche =  std::stoi(token);
            
    // /*****************  [HoraFInModoNoche] *********************************/
    // token = strtok(nullptr, "#");
    // if(token==nullptr)
    // {
    //     Serial.println("ERROR: no se enuentra info [HoraFInModoNoche]");
    //     return;
    // }
    // Serial.print("Mono Noche Acaba: ");
    // Serial.println(token);
    // cf->HoraFinNoche =  std::stoi(token);
}
