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

int nalogPostoji(char *korisnickoIme)
{
    FILE *fp;
    if(fp=fopen("nalozi.txt","r"))
    {
        NALOG n;
        while(fscanf(fp,"%s",n.korisnickoIme)!=EOF)
        if(strcmp(n.korisnickoIme,korisnickoIme)==0 )
        {
            return 1;
        }
        return 0;
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
                int opcija;
                do
                {
                    system("cls");
                    printf("Administrator:%s",korisnickoIme);
                    printf("\n\n\n");
                    printf("Odaberite jednu od ponudjenih opcija:\n 1 Kreiranje administratorskih naloga\n 2 Kreiranje klijentskih naloga\n 3 Pregled korisnickih naloga\n 4 Pregled klijentskih naloga\n 5 Aktivacije klijentskih i korisnickih naloga\n 6 Suspendovanje klijnetskih i korisnickih naloga\n 7 Blokiranje klijntskih dogadjaja\n 8 Ponistavanje sifre\n 9 Odjavljivanje\n ");
                    scanf("%d",&opcija);
                    if(opcija<1 || opcija>9)
                    {
                        do
                        {
                            printf("\nPonovo unesite opciju!");
                            scanf("%d",&opcija);
                        }
                        while(opcija>=1 && opcija<=9);
                    }

                    if(opcija==1)
                    {
                        system("cls");
                        printf("Administrator:%s",korisnickoIme);
                        printf("\nKreiranje administratorskih naloga");
                        printf("\n\n\n");

                        char korisnickoImeA[20],lozinkaA[20];
                        printf("Unesite korisnicko ime:");
                        scanf("%s",korisnickoImeA);
                        printf("Unesite lozinku:");
                        scanf("%s",lozinkaA);
                        if(nalogPostoji(korisnickoImeA))
                        {
                            printf("\nNalog vec postoji!");
                        }
                        else
                        {
                            FILE *fp;
                            if(fp=fopen("nalozi.txt","a"))
                            {
                                fprintf(fp,"\n%s %s A",korisnickoImeA,lozinkaA);
                                printf("\n Uspjesno je kreiran administratorski nalog!");
                            }
                            else("Greška prilikom otvaranja datoteke!");
                        }
                        int kraj;
                        printf("\nDa biste se vratili na pocetni meni unesite 0:");
                        do
                        {
                            scanf("%d",&kraj);
                        }
                        while(kraj!=0);
                    }

                    if(opcija==9)
                    {
                        system("cls");
                        printf("Odjavljivanje...");
                    }
                }
                while(opcija!=9);


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
