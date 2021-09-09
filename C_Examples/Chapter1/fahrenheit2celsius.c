#include <stdio.h>

//converts fahrenheit into celsius
float convert(float fahr){
  float cel = (fahr -32)*5/9;
  return cel;
}

int main(){
	float fahr;
    float cel;
	//take user input as float
    printf("Enter a temperature in Fahrenheit: ");
    scanf("%f", &fahr);
    cel = convert(fahr);
    printf("\n %.2f Fahrenheit = %.2f Celsius", fahr, cel);
	printf("\n");
}
