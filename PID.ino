PID::PID(float K, float Ki, float Kd)
{
  cK=K;
  cKi=Ki;
  cKd=Kd;
}
int PID::hazControl(float valoractual, float consigna)
{
    cyT=valoractual;
    crT=consigna;
    ceT=crT-cyT;  //cálculo del error
    cpT=cKi*ceT+cpT_1; //cálculo del término integral
    cqT=cKd*(ceT-ceT_1); // cálculo del término derivativo
    cuT=cK*ceT+cpT+cqT;  // valor de la acción de control
    if (cuT>cMax_uT)
      cuT=cMax_uT;
    if (cuT<cMin_uT)
      cuT=cMin_uT;
    cpT_1=cpT;
    //AntiWindUp
    //if (abs(pT)>100)
    //  pT_1=0;    
    ceT_1=ceT;
    return cuT;  
}
void PID::SetK(float K)
{
  cK=K;
}
float PID::GetK()
{
  return cK;
}
void PID::SetKi(float Ki)
{
  cKi=Ki;
}
float PID::GetKi()
{
  return cKi;
}
void PID::SetKd(float Kd)
{
  cKd=Kd;
}
float PID::GetKd()
{
  return cKd;
}
//int PID(float valoractual, float consigna)
//{
//    yT=valoractual;
//    rT=consigna;
//    eT=rT-yT;  //cálculo del error
//    pT=Ki*eT+pT_1; //cálculo del término integral
//    qT=Kd*(eT-eT_1); // cálculo del término derivativo
//    uT=K*eT+pT+qT;  // valor de la acción de control
//    if (uT>Max_uT)
//      uT=Max_uT;
//    if (uT<Min_uT)
//      uT=Min_uT;
//    pT_1=pT;
//    //AntiWindUp
//    //if (abs(pT)>100)
//    //  pT_1=0;    
//    eT_1=eT;
//    return uT;
//}
