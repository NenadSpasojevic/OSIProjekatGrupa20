#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct nalog
{
    char korisnickoIme[20];
    char lozinka[20];
    char karakter[2];
}NALOG;





typedef struct dogadjaj{

char naziv[20];
int sifra;
int brojMjesta;
int cijena;
char datum[15];
char vrijeme[10];

}DOGADJAJ;

/*
int provjeraSifreDogadjaja(int sifra,DOGADJAJ *niz){

int i = 0;
while(strcmp(niz[i].sifra,sifra)!=0){ // PROVJERA UNESENE SIFRE DOGADJAJA
    i++;
    if(strcmp(niz[i].sifra,sifra)==0){
        return 1;
    }
}



}*/

void kreirajDogadjaj(char *korisnickoIme,DOGADJAJ dogadjaj){

    FILE *lista;
    printf("Unesite naziv dogadjaja : ");
    scanf("%s",dogadjaj.naziv);
    printf("Unesite broj mjesta : ");
    scanf("%d",&dogadjaj.brojMjesta);
    printf("Unesite cijenu : ");
    scanf("%d",&dogadjaj.cijena);
    printf("Unesite datum : ");
    scanf("%s",dogadjaj.datum);
    printf("Unesite vrijeme desavanja : ");
    scanf("%s",dogadjaj.vrijeme);
    printf("Unesite sifru dogadjaja (NAPOMENA:SIFRA MORA BITI JEDINSTVENA) : ");
    scanf("%d",&dogadjaj.sifra);

    if(lista=fopen("listaDogadjaja.txt","a+")){

        fprintf(lista,"Naziv dogadjaja : %s \n",dogadjaj.naziv);
        fprintf(lista,"Broj mjesta: %d \n",dogadjaj.brojMjesta);
        fprintf(lista,"Datum dogadjaja :%s \n",dogadjaj.datum);
        fprintf(lista,"Vrijeme dogadjaja :%s \n",dogadjaj.vrijeme);
        fprintf(lista,"Cijena jedne ulaznice :%d KM \n",dogadjaj.cijena);
        fprintf(lista,"Sifra dogadjaja :%d \n",dogadjaj.sifra);
        fprintf(lista,"Organizator ovog dogadjaja : %s",korisnickoIme);
        fprintf(lista,"\n\n");



    }

}












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
   int opcija;
   DOGADJAJ dogadjaj;
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
                else if(strcmp(karakter,"K")==0){


                do{

                        system("cls");

                    printf("Klijent:%s",korisnickoIme);
                    printf("\n\n\n");
                    printf("Odaberite jednu od ponudjenih opcija:\n 1.Kreiranje dogadjaja\n 2.Pregled kreiranih dogadjaja \n 3.Pristup izvjestaju o prodaji \n 4.Ponistavanje pojedinacne ulaznice \n 5.Odjavljivanje\n");
                     scanf("%d",&opcija);
                    if(opcija<1 || opcija>5)
                    {
                        do
                        {
                            printf("\nPonovo unesite opciju!");
                            scanf("%d",&opcija);
                        }
                        while(opcija>=1 && opcija<=5);
                    }

                            if(opcija==1){

                                system("cls");
                                printf("Kreiranje dogadjaja : \n");

                                kreirajDogadjaj(korisnickoIme,dogadjaj);

                            }





                        if(opcija==5)
                    {
                        system("cls");
                        printf("Odjavljivanje...");
                    }
                }while(opcija!=5);
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
