void imprimeLCD(String linea1, String linea2)
{
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(linea1);
  lcd.setCursor(0,1);
  lcd.print(linea2);
}
