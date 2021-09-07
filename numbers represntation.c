#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef union{
float f;
unsigned char array[sizeof(float)];
}uni;

typedef struct{
          unsigned int mantissa :23;
          int exponent :8;
          char sign :1;
}stru;

typedef union{
stru s;
float fl;
}unio;

typedef union{
            double x;
            int xbin;
}un;

typedef union{
            long double xld;
            int xint;
}last;

int get_command();
void question1();
void question2();
void question3();
void print_binary_char(char c);
void print_binary_float(float f);
float get_smallest_positive_float();
double get_double_epsilon();
long double get_longdouble_exponent_bias();

int main(){

            printf("\nQuestion 1 answer: negative numbers are represented in 2's complement\n");
            printf("\nQuestion 2 answer: numbers are stored in little Endian on my machine\n");
//int choice;
while(1){
    switch(get_command()){
    case 1:
        question1();
        break;
    case 2:
        question2();
        break;
    case 3:
        question3();
        break;
    default:
        printf("Invalid Choice. Exiting...\n");
        exit(1);
    }
}
    return 0;
}
int get_command(){
int choice;
printf("\n\n");
printf("*********************************************\n");
printf("* Enter 1 for Signed Integer Representation *\n");
printf("* Enter 2 for Floating-Point Endianness *\n");
printf("* Enter 3 for Floating-Point Representation *\n");
printf("* Enter anything else to exit *\n");
printf("*********************************************\n");
printf("Your choice: ");
scanf("%d", &choice);
fseek(stdin, 0, SEEK_END);
printf("\n");
return choice;
}
void print_binary_char(char c){
char end=7;
 while(end>=0){
            if ( (c & (1<<end) ) ==0 ){
        printf("0");
            }
    else {
        printf("1");
    }
    end--;
    }
 }
void print_binary_float(float f){
uni x;
int i;
 x.f=f;
for(i=3;i>=0;i--){
            printf("%.2x",x.array[i]);
}

}
void question1(){
    printf("printing from -16 to 15 in binary\n");
    char c;
    for(c=-16;c<16;c++){
        printf("%d\t",c);
        print_binary_char(c);
        printf("\n");

    }
}
void question2(){
float numbers[] = {0.0f, 1.0f, 2.0f, 0.1f};
int count = sizeof(numbers) / sizeof(numbers[0]);
int i;
for(i=0; i<count; i++) {
printf("%.2f is represented as: ", numbers[i]);
print_binary_float(numbers[i]);
printf("\n");
}
}

float get_smallest_positive_float() {
unio u;
u.s.sign=0;
u.s.exponent=0x01;
u.s.mantissa=0x01;
return u.fl;
}

double get_double_epsilon() {
            un uno;
            uno.x =1.0;
            uno.xbin=(uno.xbin | 31>>1);
            uno.x=uno.x-1.0;
            return uno.x;
}


long double get_longdouble_exponent_bias() {
long double d=1.0L;
int counter=0;
char end=95;
//need to use union of long double and int
last f;
 while(end>=0){
      if ( (f.xint & (1<<end) ) !=0 ){
          counter++;
         }
    end--;
    }
    printf("%d",counter);
return pow(2,counter-1)-1;
}

void question3(){
printf("The smallest positive 'float' is: %e\n",get_smallest_positive_float());
printf("Epsilon for 'double' is: %le\n", get_double_epsilon());
printf("'long double' has a bias of %d for its exponent\n",get_longdouble_exponent_bias());
}
