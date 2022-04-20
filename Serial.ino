void leeSerial()
{
  String p; //variable en la que se guardará la lectura obtenida del puerto serie
  char instruccion; //instrucción a comprobar
  float valor;//valor numérico extraído del puerto serie
  //boolean inst_ok = false; //booleano para memorizar si la instrucción es válida o no

  if (Serial.available())
  {
    p=Serial.readString();
    //Se extrae la instrucción: primer caracter
    instruccion = toupper(p.charAt(0));//de esta manera se coge el primer caracter de la cadena por ejemplo si se recibe "a100"
    // se hace instruccion = 'A'. Nota: toupper convierte la letra en mayúscula
    //Se extrae el valor, a partir del primer caracter y se considera que es un número
    if (p.length()>1)//si la cadena es más larga que un caracter (es decir si lleva parte numérica)
      valor = p.substring(1,p.length()).toFloat();//se coge el valor y se convierte a real
     
    switch (instruccion){
      case 'D'://mueve rueda derecha un determinado número de "pasos"
//        if (valor>V_MIN && valor <V_MAX)//se comprueba si el valor obtenido está comprendido entre los valores 
//          {
//            SPT=valor;//establece el punto de consigna y establece el modo a control (por si no lo estaba)
//            modo='C';
//          }
        modo = instruccion;
        parametro = valor;
        break;
      case 'I'://mueve rueda izda un determinado número de "pasos"
        modo = instruccion;
        parametro = valor;
        break;
      case 'S'://para los motores
        modo = instruccion;
        break;
      case 'B'://mueve ambas ruedas un determinado número de "pasos"
        modo = instruccion;
        parametro = valor;//nº de pasos
        break;
      case 'Q'://mueve rueda izquierda a una velocidad determinada
        modo = instruccion; 
        parametro = valor;     
        break;
      case 'W'://mueve rueda derecha a una velocidad determinada
        modo = instruccion;   
        parametro = valor;    //velocidad
        break; 
      case 'C'://modo control indicando consigna
        modo = instruccion;
        consigna=valor;
        break;
      case 'K':
        ruedaIzda.SetK(valor);
        break;
      case 'T':
        ruedaIzda.SetKi(valor);
        break;
      case 'N':
        intervaloControl = valor;
        break;
      case 'H':
        Serial.print("Rueda Izda-K: ");
        Serial.print(ruedaIzda.GetK());
        Serial.print("; Ki: ");
        Serial.print(ruedaIzda.GetKi());
        Serial.print("; Kd: ");
        Serial.println(ruedaIzda.GetKd());       
        Serial.print("Rueda Dcha-K: ");
        Serial.print(ruedaDcha.GetK());
        Serial.print("; Ki: ");
        Serial.print(ruedaDcha.GetKi());
        Serial.print("; Kd: ");
        Serial.println(ruedaDcha.GetKd());            
        break;        
    }
  }
}
void leeBT()
{
  String p; //variable en la que se guardará la lectura obtenida del puerto serie
  char instruccion; //instrucción a comprobar
  float valor;//valor numérico extraído del puerto serie
  //boolean inst_ok = false; //booleano para memorizar si la instrucción es válida o no

  if (ConexionBT.available())
  {
    p=ConexionBT.readString();
    //Se extrae la instrucción: primer caracter
    instruccion = toupper(p.charAt(0));//de esta manera se coge el primer caracter de la cadena por ejemplo si se recibe "a100"
    // se hace instruccion = 'A'. Nota: toupper convierte la letra en mayúscula
    //Se extrae el valor, a partir del primer caracter y se considera que es un número
    if (p.length()>1)//si la cadena es más larga que un caracter (es decir si lleva parte numérica)
      valor = p.substring(1,p.length()).toFloat();//se coge el valor y se convierte a real
     
    switch (instruccion){
      case 'D'://mueve rueda derecha un determinado número de "pasos"
//        if (valor>V_MIN && valor <V_MAX)//se comprueba si el valor obtenido está comprendido entre los valores 
//          {
//            SPT=valor;//establece el punto de consigna y establece el modo a control (por si no lo estaba)
//            modo='C';
//          }
        modo = instruccion;
        parametro = valor;
        break;
      case 'I'://mueve rueda izda un determinado número de "pasos"
        modo = instruccion;
        parametro = valor;
        break;
      case 'S'://para los motores
        modo = instruccion;
        break;
      case 'B'://mueve ambas ruedas un determinado número de "pasos"
        modo = instruccion;
        parametro = valor;//nº de pasos
        break;
      case 'Q'://mueve rueda izquierda a una velocidad determinada
        modo = instruccion; 
        parametro = valor;     
        break;
      case 'W'://mueve rueda derecha a una velocidad determinada
        modo = instruccion;   
        parametro = valor;    //velocidad
        break; 
      case 'C'://modo control indicando consigna
        modo = instruccion;
        consigna=valor;
        break;
      case 'K':
        ruedaIzda.SetK(valor);
        break;
      case 'T':
        ruedaIzda.SetKi(valor);
        break;
      case 'N':
        intervaloControl = valor;
        break;
      case 'H':
        Serial.print("Rueda Izda-K: ");
        Serial.print(ruedaIzda.GetK());
        Serial.print("; Ki: ");
        Serial.print(ruedaIzda.GetKi());
        Serial.print("; Kd: ");
        Serial.println(ruedaIzda.GetKd());       
        Serial.print("Rueda Dcha-K: ");
        Serial.print(ruedaDcha.GetK());
        Serial.print("; Ki: ");
        Serial.print(ruedaDcha.GetKi());
        Serial.print("; Kd: ");
        Serial.println(ruedaDcha.GetKd());            
        break;        
    }
  }
}
