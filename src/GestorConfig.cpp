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
    //Serial.println("Dia: "+String(cf->diaActual));
    

    // Config Texto
    DisplayTexto* dspTxt =  (DisplayTexto*)mngr.GetDisplay(0);
    //dspTxt->setTexto(this->txtPpal);
    Serial.println(cf->textoMensajes);

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
   Serial.print(token);
   Serial.print("-->");
    cf->textoMensajes = String(token+'\0');
    Serial.println(cf->textoMensajes);

    /*****************  [textomensaje 2] *********************************/

    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [texto mensaje 2]");
        return;
    }
    Serial.print("textomensaje 2: ");
    Serial.println(token);
    cf->textoMensajes2 = String(token+'\0');
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
    cf->textoAlarma = String(token+'\0');

    /*****************  [textoDibujos] *********************************/
    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [textoDibujos]");
        return;
    }
    Serial.print("texto Dibujos: ");
    Serial.println(token);
    cf->textoDibujos = String(token+'\0');


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


    switch (token[0])
    {
    case 'L':
        cf->diaActual = 1; 
        break;
    case 'M':
        cf->diaActual = 2; 
        break;
    case 'X':
        cf->diaActual = 3; 
        break;
    case 'J':
        cf->diaActual = 4; 
        break;
    case 'V':
        cf->diaActual = 5; 
        break;
    case 'S':
        cf->diaActual = 6; 
        break;
    case 'D':
        cf->diaActual = 7; 
        break;
    }
    Serial.print("Dia Actual: ");
    Serial.println(token+String(cf->diaActual));

    /*****************  [HoraAlarma] *********************************/
    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [HoraAlarma]");
        return;
    }
    Serial.print("Alarma: ");
  //  Serial.println(token);

    //cf->horaAlarma->hours = atoi(token);
    u_int16_t horas;
    sscanf(token+'\0', "%d", &horas);
    cf->horaAlarma->hours =horas;
    
   // Serial.println(horas );
   // Serial.println(cf->horaAlarma->hours );

    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [m]");
        return;
    }
  //  Serial.println(token);
    // cf->horaAlarma->minutes = atoi(token+'\0');
       u_int16_t m;
    sscanf(token, "%d", &m);
    cf->horaAlarma->minutes =m;
  //  Serial.println(cf->horaAlarma->minutes );

    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [s]");
        return;
    }
    cf->horaAlarma = new HoraLocal(horas,m,0);
    // Serial.println(token);
    // cf->horaAlarma->seconds = atoi(token+'\0');
    // Serial.println(cf->horaAlarma->seconds );
    // extractedChars[0] = token[0]; // Posición 3 (índice 2)
    // extractedChars[1] = token[1]; // Posición 4 (índice 3)
    // extractedChars[2] = '\0'; // Terminador nulo para formar una cadena válida

    //   // Convertir los caracteres extraídos a un entero
    // cf->horaAlarma->hours = atoi(extractedChars);
    // Serial.println(extractedChars );
    // Serial.println(cf->horaAlarma->hours);

    // extractedChars[0] = token[3]; 
    // extractedChars[1] = token[4]; 
    // extractedChars[2] = '\0'; // Terminador nulo para formar una cadena válida
    // cf->horaAlarma->minutes = atoi(extractedChars);
    // Serial.println(extractedChars );
    // Serial.println(cf->horaAlarma->minutes );

    
    // extractedChars[0] = token[6]; 
    // extractedChars[1] = token[7]; 
    // extractedChars[2] = '\0'; // Terminador nulo para formar una cadena válida
    // cf->horaAlarma->seconds = atoi(extractedChars);
    // Serial.println(extractedChars );
    // Serial.println(cf->horaAlarma->seconds );

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
    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [HoraIniModoNoche]");
        return;
    }
    Serial.print("Mono Noche Empieza: ");
    Serial.println(token);
    cf->HoraIniNoche =  std::stoi(token);
            
    /*****************  [HoraFInModoNoche] *********************************/
    token = strtok(nullptr, "#");
    if(token==nullptr)
    {
        Serial.println("ERROR: no se enuentra info [HoraFInModoNoche]");
        return;
    }
    Serial.print("Mono Noche Acaba: ");
    Serial.println(token);
    cf->HoraFinNoche =  std::stoi(token);
}
