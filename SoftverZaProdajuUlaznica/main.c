#include <stdio.h>
#include <stdlib.h>

int main()
{
   char dane;
   printf("Da li vec imate kreiran nalog? Da:[D] Ne:[N]\n");
    do
    {
        scanf("%c",&dane);
        if(dane=='D')
        {
            printf("Prijava:");
        }
        else if(dane=='N')
        {
            printf("Registracija:");
        }
    }
    while(dane!='D' && dane !='N');

}
