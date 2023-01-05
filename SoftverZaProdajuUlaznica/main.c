#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct nalog
{
    char korisnickoIme[20];
    char lozinka[20];
    char karakter[2];
}NALOG;

int provjera(char *korisnickoIme,char *lozinka,char *karakter)
{
    FILE *ulaz;


    if(ulaz=fopen("nalozi.txt","r"))
    {
        NALOG n;
        while(fscanf(ulaz,"%s %s %s",n.korisnickoIme,n.lozinka,n.karakter)!=EOF)
        {
             if(strcmp(n.korisnickoIme,korisnickoIme)==0 && strcmp(n.lozinka,lozinka)==0)
             {
                 strcpy(karakter,n.karakter);
                 return 0;
             }
        }
        return 1;
    }
    else printf("Greska prilikom otvaranja datoteke!");
}

int main()
{
   char dane;
   printf("Da li vec imate kreiran nalog? Da:[D] Ne:[N]\n");
    do
    {
        scanf("%c",&dane);
        if(dane=='D')
        {
            char korisnickoIme[20],lozinka[20],karakter[2];
            int brojac=0;
            do
            {
                brojac++;
                printf("Unesite korisnicko ime:");
                scanf("%s",korisnickoIme);
                printf("Unesite lozinku:");
                scanf("%s",lozinka);
                if (brojac==5)
                {
                    printf("Greska prilikom prijave!");break;
                }
            }
            while(provjera(korisnickoIme,lozinka,&karakter));

            if(strcmp(karakter,"A")==0)
            {
                system("cls");
                printf("Administrator:%s",korisnickoIme);
            }

            if(strcmp(karakter,"K")==0)
            {
                system("cls");
                printf("Klijent:%s",korisnickoIme);
            }

            if(strcmp(karakter,"O")==0)
            {
                system("cls");
                printf("Korisnik:%s",korisnickoIme);
            }

        }
        else if(dane=='N')
        {
            printf("Registracija:");
        }
    }
    while(dane!='D' && dane !='N');

}
