#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

int main()
{

int n;
int choice;
bool hasChoosen=false;



while(!(hasChoosen))
{
    printf("~~~~~Menu~~~~~\n");
    printf("1. 64 bit\n");
    printf("2. 128 bit\n");
    printf("3. 256 bit\n");
    printf("4. 512 bit\n");
    printf("5. 1024 bit\n");
    printf("6. 2048 bit\n");
    printf("Choose the size of encryption numbers: ");
    scanf("%d",&choice);

    switch(choice) {

    case 1:
        n=64;
        hasChoosen=true;
        break;



    case 2:
        n=128;
        hasChoosen=true;
        break;


    case 3:
        n=256;
        hasChoosen=true;
        break;


    case 4:
        n=512;
        hasChoosen=true;
        break;


    case 5:
        n=1014;
        hasChoosen=true;
        break;


    case 6:
        n=2048;
        hasChoosen=true;
        break;


    default :
       printf("Sorry this is not an available option\n\n");

    }
}
getchar();
//~~~~~~Initializations and declarations~~~~~~~//
 mpz_t g;
 mpz_init(g);

 mpz_t p;
 mpz_init(p);

 mpz_t x;
 mpz_init(x);

  mpz_t y;
  mpz_init(y);

  mpz_t k;
  mpz_init(k);

  mpz_t c1;
  mpz_init(c1);


 gmp_randstate_t state;
 gmp_randinit_default(state);


//~~~~~~~~~~~~~~~~~~~~~~Key Generation~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


 mpz_urandomb(p,state,n); //Random number n bit
 mpz_nextprime(p,p); //Make it prime number


 mpz_urandomb(g,state,n); //Random number n bit



 while( mpz_cmp(p,g)<0) //Ensure that p is greater than g                                                        p>g
 {
     mpz_urandomb(g,state,n);
 }


 gmp_printf("\nThe value of p is %Zd \n",p);                                                                     // p
 gmp_printf("The value of g is %Zd \n",g);                                                                       // g


mpz_urandomb(x,state,n);

 while( mpz_cmp(g,x)<0 )                                                                                        //g>x
 {
     mpz_urandomb(x,state,n);

 }

 gmp_printf("The value of x is %Zd \n",x);                                                                      //x


 mpz_powm(y,g,x,p);                                                                                          // y =g^x mod p

 gmp_printf("The value of y is %Zd \n",y);                                                                   //y


 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Encryption~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	char temp;
	char message[50];
	int count = 0;

    printf("\nGive message: ");

    fgets(message, sizeof(message), stdin);

    while(message[count]!='\n') //Counting the length of the message
    {

        count++;

    }


    mpz_urandomb(k,state,n);

    while( mpz_cmp(p,k)<0 ) //Ensure that p is greater than k                                            //p>k
    {
     mpz_urandomb(k,state,n);

    }

    gmp_printf("\nThe value of k is %Zd \n",k);                                                         //k

    mpz_powm(c1,g,k,p); //Calculate C1                                                                   // c1 = g^k mod p

    gmp_printf("\n\nThe value of C1 is %Zd \n",c1);                                                      // c1


    //~~~~~~~~~~Initialize the encrypted array~~~~~~~~//
    int i;
    mpz_t c2[count];

    for (i = 0; i < count; i++) {
        mpz_init2(c2[i], n);                                                                          //c2 array with n bits
    }



    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


    mpz_t temp2;
    mpz_init(temp2);                                                                            //temp2

    mpz_t temp3;                                                                                //temn3
    mpz_init(temp3);

    mpz_powm(temp2,y,k,p);                                                               //temp2 = (y^k)mod p

    gmp_printf("\n\ntemp2 = (y^k)mod p :%Zd \n",temp2);


    for(i=0; i<count; i++)
    {


        mpz_mul_si(c2[i],temp2,message[i]);

        gmp_printf("C2[%d] = %Zd\n",i,c2[i]);                                       //encrypt array with temp2 on each cell

    }

	mpz_clear(temp2);
	mpz_clear(temp3);
	mpz_clear(k);



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Decryption~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

    mpz_t temp4;
    mpz_init(temp4);

    mpz_t temp5;
    mpz_init(temp5);

    mpz_t temp6;
    mpz_init(temp6);

    mpz_t temp7;
    mpz_init(temp7);

    int result;

    mpz_set_si(temp7,1); //We need 1 to be a mpz variable in order to pass it to the mpz_pown() function

    printf("\nDecrypted: ");

    for(i=0; i<count; i++)//We decrypt the characters one by one in order to save space
    {


        mpz_powm(temp5,c1,x,p);                                                                 //temp5 = c1^x mod p


        mpz_cdiv_q(temp6,c2[i],temp5);                                   //c2[i] = temp5   --> temp6 = temp5 --? result = temp6

        result = mpz_get_ui (temp6);

        gmp_printf("%c",result);

    }

     printf("\n");


//Free space needed for the mpz variables

    mpz_clear(temp4);
	mpz_clear(temp5);
	mpz_clear(temp6);
	mpz_clear(temp7);;

    for (i = 0; i < count; i++) {
    mpz_clear(c2[i]);
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
}
