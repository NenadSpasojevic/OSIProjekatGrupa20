#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//David Preradovic
typedef struct nalog
{
    char korisnickoIme[20];
    char lozinka[20];
    char karakter[2];
    char aktivan[2];
}NALOG;

typedef struct cvor
{
    NALOG n;
    struct cvor *sljedeci;
}CVOR;


void dodaj(CVOR **pglava, NALOG *n)
{
  CVOR *p,*novi = (CVOR *)malloc(sizeof(CVOR));
  novi->n = *n;
   if (*pglava == 0)
  {
    novi->sljedeci = *pglava;
    *pglava = novi;
  }
  else
  {
    for (p = *pglava; p->sljedeci;p = p->sljedeci);
    novi->sljedeci = p->sljedeci;
    p->sljedeci = novi;
  }
}

CVOR* trazi(CVOR *glava, char *korisnickoIme)
{
  while (glava && strcmp(glava->n.korisnickoIme, korisnickoIme) < 0)
    glava = glava->sljedeci;
  return glava == 0 || strcmp(glava->n.korisnickoIme, korisnickoIme) > 0 ? 0 : glava;
}

void pisi(CVOR *glava)
{
    FILE *fp;
    if(fp=fopen("nalozi.txt","w"))
    {
        while(glava)
        {
            fprintf(fp,"%s %s %s %s\n",glava->n.korisnickoIme,glava->n.lozinka,glava->n.karakter,glava->n.aktivan);
            glava=glava->sljedeci;
        }

    }
    else("Greška prilikom otvaranja datoteke!");
    fclose(fp);
}
int brisi(CVOR **pglava, char *korisnickoIme)
{
  if (*pglava == 0)
    return 0;

  CVOR *p = 0;
  if (strcmp((*pglava)->n.korisnickoIme, korisnickoIme) == 0)
  {
    p = (*pglava);
    (*pglava) = (*pglava)->sljedeci;
  }
  else
  {
    CVOR *pr = (*pglava);
    for (p = (*pglava)->sljedeci; p && strcmp(p->n.korisnickoIme, korisnickoIme) < 0;
      p = p->sljedeci)
    pr = p;

    if (p == 0 || strcmp(p->n.korisnickoIme, korisnickoIme) > 0)
      return 0;
    pr->sljedeci = p->sljedeci;
  }
  free(p);
  return 1;
}

void brisi_listu(CVOR **pglava)
{
  while (*pglava)
    {
        CVOR *p = (*pglava)->sljedeci;
        free(*pglava);
        *pglava = p;
    }
}


int provjera(char *korisnickoIme,char *lozinka,char *karakter)
{
    FILE *ulaz;


    if(ulaz=fopen("nalozi.txt","r"))
    {
        NALOG n;
        int ime=1;
        while(fscanf(ulaz,"%s %s %s %s",n.korisnickoIme,n.lozinka,n.karakter,n.aktivan)!=EOF)
        {
            if(strcmp(n.aktivan,"A")!=0)
                    printf("Nalog je suspendovan!\n");
            if(strcmp(n.korisnickoIme,korisnickoIme)==0 && strcmp(n.lozinka,lozinka)!=0)
            {
                ime=0;
                printf("Neispravna lozinka!\n");
            }

             if(strcmp(n.korisnickoIme,korisnickoIme)==0 && strcmp(n.lozinka,lozinka)==0 &&  strcmp(n.aktivan,"A")==0)
             {
                 strcpy(karakter,n.karakter);
                return 0;
             }
        }
        if(ime)
        printf("Neispravno korisnicko ime!\n");
        return 1;
    }
    else printf("Greska prilikom otvaranja datoteke!");
    fclose(ulaz);
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
    fclose(fp);
}

//Nenad Spasojevic
typedef struct dogadjaj{

char naziv[20];
int sifra;
int brojMjesta;
int cijena;
char datum[15];
char vrijeme[10];
char organizator[20];

}DOGADJAJ;

void kreirajDogadjaj(char *korisnickoIme){

    DOGADJAJ dogadjaj;
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
    strcpy(dogadjaj.organizator,korisnickoIme);
    if(lista=fopen("listaDogadjaja.txt","a+")){

        fprintf(lista,"%s %d %s %s %d %d %s",dogadjaj.naziv,dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,dogadjaj.cijena,dogadjaj.sifra,dogadjaj.organizator);



    }

}


void pregledDogadjaja(char *klijentskoIme){

        FILE *lista;

        DOGADJAJ dogadjaj;
        char* korisnickoIme;
        if(lista=fopen("listaDogadjaja.txt","r")){

            while(fscanf(lista,"%s %d %s %s %d %d %s",dogadjaj.naziv,&dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,&dogadjaj.cijena,&dogadjaj.sifra,korisnickoIme)!=EOF){

                if(strcmp(klijentskoIme,korisnickoIme)==0){

                printf("Naziv dogadjaja : %s \n",dogadjaj.naziv);
                printf("Broj mjesta: %d \n",dogadjaj.brojMjesta);
                printf("Datum dogadjaja :%s \n",dogadjaj.datum);
                printf("Vrijeme dogadjaja :%s \n",dogadjaj.vrijeme);
                printf("Cijena jedne ulaznice :%d KM \n",dogadjaj.cijena);
                printf("Sifra dogadjaja :%d \n",dogadjaj.sifra);
                printf("Organizator ovog dogadjaja : %s",korisnickoIme);
                printf("\n\n");

                }

            }



        }else printf("nije uspjesno otvorena datoteka!");




}


//Dejana Malinovic
int main()
{
    int opcija;
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
                printf("\nUnesite korisnicko ime:");
                scanf("%s",korisnickoIme);
                printf("\nUnesite lozinku:");
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
                    printf("Odaberite jednu od ponudjenih opcija:\n 1 Kreiranje administratorskih naloga\n 2 Kreiranje klijentskih naloga\n 3 Pregled klijentskih naloga\n 4 Pregled korisnickih naloga\n 5 Aktivacije klijentskih i korisnickih naloga\n 6 Suspendovanje klijnetskih i korisnickih naloga\n 7 Blokiranje klijntskih dogadjaja\n 8 Ponistavanje sifre\n 9 Odjavljivanje\n ");
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
                            fclose(fp);
                        }
                        int kraj;
                        printf("\nDa biste se vratili na pocetni meni unesite 0:");
                        do
                        {
                            scanf("%d",&kraj);
                        }
                        while(kraj!=0);
                    }

                     if(opcija==2)
                    {
                        system("cls");
                        printf("Administrator:%s",korisnickoIme);
                        printf("\nKreiranje klijentskih naloga");
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
                                fprintf(fp,"\n%s %s K",korisnickoImeA,lozinkaA);
                                printf("\n Uspjesno je kreiran klijentski nalog!");
                            }
                            else("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                        }
                        int kraj;
                        printf("\nDa biste se vratili na pocetni meni unesite 0:");
                        do
                        {
                            scanf("%d",&kraj);
                        }
                        while(kraj!=0);
                    }

                    if(opcija==3)
                    {
                        system("cls");
                        printf("Administrator:%s",korisnickoIme);
                        printf("\nPregled klijentskih naloga:");
                        printf("\n\n\n");

                        printf("============================================================================");

                        NALOG n;
                        {
                            FILE *fp;
                            int brojac=0;
                            if(fp=fopen("nalozi.txt","r"))
                            {
                                while(fscanf(fp,"%s %s %s %s",n.korisnickoIme,n.lozinka,n.karakter,n.aktivan)!=EOF)
                                if(strcmp(n.karakter,"K")==0)
                                {
                                    brojac++;
                                    printf("\n%d. %s",brojac,n.korisnickoIme);
                                    printf("\n============================================================================");
                                }
                            }
                            else("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                        }

                        int opcija;
                        printf("\nOdaberite jednu od ponudjenih opcija:\n 1 Brisanje klijentskih naloga\n 2 Suspendovanje klijentskih naloga\n 3 Aktivacija klijntskih naloga\n 4 Pocetni meni\n");
                        do
                        {
                            scanf("%d",&opcija);
                        }
                        while(opcija<1 || opcija>4);

                        if(opcija==1)
                        {
                            char korisnickoImeK[20];
                            printf("\nUnesite korisnicko ime:");
                            scanf("%s",korisnickoImeK);
                            FILE *fp;
                            NALOG na;
                            CVOR *glava=0;
                            if(fp=fopen("Nalozi.txt","r+"))
                            {
                                  while(fscanf(fp,"%s %s %s %s",na.korisnickoIme,na.lozinka,na.karakter,na.aktivan)!=EOF)
                                  {
                                     dodaj(&glava,&na);
                                  }
                            }
                            else("Greška prilikom otvaranja datoteke!");
                            fclose(fp);

                            if(brisi(&glava,korisnickoImeK))
                            {
                                printf("Ujepjesno obrisan nalog!");
                            }
                            else printf("Neposotjeci nalog!");
                            pisi(glava);
                            brisi_listu(&glava);
                            int kraj;
                            printf("\nDa biste se vratili na pocetni meni unesite 0:");
                            do
                            {
                                scanf("%d",&kraj);
                            }
                            while(kraj!=0);
                        }
                    }


                    if(opcija==9)
                    {
                        system("cls");
                        printf("Odjavljivanje...");break;
                    }
                }
                while(opcija>0 && opcija<10);


            }




            if(strcmp(karakter,"K")==0)
            {
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

                                kreirajDogadjaj(korisnickoIme);
                                printf("Uspjesno kreiran dogadjaj!");

                            }

                                if(opcija==2){

                                    printf("Pregled dogadjaja: \n");
                                    pregledDogadjaja(korisnickoIme);
                                }



                        if(opcija==5)
                    {
                        system("cls");
                        printf("Odjavljivanje...");
                    }
                }while(opcija!=5);

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
