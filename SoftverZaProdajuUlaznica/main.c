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
  while (glava && strcmp(glava->n.korisnickoIme, korisnickoIme) !=0)
    glava = glava->sljedeci;
  return glava == 0 ? 0 : glava;
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

void pisi2(CVOR *glava)
{

        while(glava)
        {
            printf("%s %s %s %s\n",glava->n.korisnickoIme,glava->n.lozinka,glava->n.karakter,glava->n.aktivan);
            glava=glava->sljedeci;
        }
}

int brisi(CVOR **pglava, char *korisnickoIme)
{
  if (*pglava == 0)
    return 0;

  CVOR *p = 0,*prev;
  if (strcmp((*pglava)->n.korisnickoIme, korisnickoIme) == 0)
  {
    p = (*pglava);
    (*pglava) = (*pglava)->sljedeci;
  }
   else
  {
    p = (*pglava);
    while(p && strcmp(p->n.korisnickoIme, korisnickoIme) != 0)
    {
        prev=p;
        p=p->sljedeci;
    }
  }

  if(p==0)
  return 0;

  prev->sljedeci=p->sljedeci;
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
            if(strcmp(korisnickoIme,n.korisnickoIme)==0 && strcmp(korisnickoIme,n.lozinka)==0 && strcmp(n.aktivan,"A")!=0)
            {
                   printf("Nalog je suspendovan!\n");
                   ime=0;
            }
            if(strcmp(n.korisnickoIme,korisnickoIme)==0 && strcmp(n.lozinka,lozinka)!=0)
            {
                ime=0;
                printf("Neispravna lozinka!\n");
            }
            if(strcmp(korisnickoIme,n.korisnickoIme)==0 && strcmp(n.lozinka,"obrisana")==0 && strcmp(n.aktivan,"A")==0)
            {
                char lozinka[20];
                system("cls");
                printf("Administrator je obrisao vasu lozinku! Unesite novu!");
                scanf("%s",lozinka);
                FILE *fp;
                NALOG na;
                CVOR *glava;
                if(fp=fopen("Nalozi.txt","r"))
                            {
                                  while(fscanf(fp,"%s %s %s %s",na.korisnickoIme,na.lozinka,na.karakter,na.aktivan)!=EOF)
                                  {
                                     dodaj(&glava,&na);
                                  }
                            }
                            else("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                            CVOR *p;
                            p=trazi(glava,korisnickoIme);
                            if(p==0)
                                printf("\nNepostojeci nalog!");
                            else
                            {
                                strcpy(p->n.lozinka,lozinka);
                            }

                            pisi(glava);
                            brisi_listu(&glava);
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
char aktivan[2];
int brojZauzetihMjesta;

}DOGADJAJ;

int provjeraSifreDogadjaja(int sifra){
FILE *lista;
DOGADJAJ dogadjaj;
int flag=0;
if(lista=fopen("listaDogadjaja.txt","r")){

            while(fscanf(lista,"%s %d %s %s %d %d %s %s %d",dogadjaj.naziv,&dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,&dogadjaj.cijena,&dogadjaj.sifra,dogadjaj.organizator,dogadjaj.aktivan,&dogadjaj.brojZauzetihMjesta)!=EOF){
              if(sifra==dogadjaj.sifra)
                {
                    printf("Sifra nije jedinstvena");
                    return 1;
                }
              }

}
fclose(lista);

return 0;
}

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
    int brojac=0;
    do
    {
        brojac++;
        if(brojac>1)printf("\nUnesite novu sifru: ");
        scanf("%d",&dogadjaj.sifra);

    }
    while(provjeraSifreDogadjaja(dogadjaj.sifra));

        dogadjaj.brojZauzetihMjesta=0;

    strcpy(dogadjaj.organizator,korisnickoIme);

    if(lista=fopen("listaDogadjaja.txt","a+")){

        fprintf(lista,"%s %d %s %s %d %d %s A %d\n",dogadjaj.naziv,dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,dogadjaj.cijena,dogadjaj.sifra,dogadjaj.organizator,dogadjaj.brojZauzetihMjesta);
        printf("Uspjesno kreiran dogadjaj!");

    }



    fclose(lista);

}


void pregledDogadjaja(char *klijentskoIme){

        FILE *lista;

        DOGADJAJ dogadjaj;
        char* korisnickoIme;
         printf("\n============================================================================\n");
        if(lista=fopen("listaDogadjaja.txt","r")){

            while(fscanf(lista,"%s %d %s %s %d %d %s %s %d",dogadjaj.naziv,&dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,&dogadjaj.cijena,&dogadjaj.sifra,korisnickoIme,dogadjaj.aktivan,&dogadjaj.brojZauzetihMjesta)!=EOF){

                if(strcmp(klijentskoIme,korisnickoIme)==0){

                printf("Naziv dogadjaja : %s \n",dogadjaj.naziv);
                printf("Broj mjesta: %d \n",dogadjaj.brojMjesta);
                printf("Broj zauzetih mjesta: %d \n",dogadjaj.brojZauzetihMjesta);
                printf("Datum dogadjaja :%s \n",dogadjaj.datum);
                printf("Vrijeme dogadjaja :%s \n",dogadjaj.vrijeme);
                printf("Cijena jedne ulaznice :%d KM \n",dogadjaj.cijena);
                printf("Sifra dogadjaja :%d \n",dogadjaj.sifra);
                printf("Organizator ovog dogadjaja : %s\n",korisnickoIme);
                if(strcmp(dogadjaj.aktivan,"A")==0)
                                        printf("Aktivan\n");
                                    else
                                        printf("Blokiran\n");
                printf("\n\n");
                 printf("\n============================================================================\n");
                }

            }
            fclose(lista);



        }else printf("nije uspjesno otvorena datoteka!");
}

void pregledSvihDogadjaja()
{
        FILE *lista;
        char korisnickoIme[20];
        DOGADJAJ dogadjaj;
        printf("\n============================================================================\n");
        if(lista=fopen("listaDogadjaja.txt","r")){

            while(fscanf(lista,"%s %d %s %s %d %d %s %s %d",dogadjaj.naziv,&dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,&dogadjaj.cijena,&dogadjaj.sifra,korisnickoIme,dogadjaj.aktivan,&dogadjaj.brojZauzetihMjesta)!=EOF){
                {
                printf("Naziv dogadjaja : %s \n",dogadjaj.naziv);
                printf("Broj mjesta: %d \n",dogadjaj.brojMjesta);
                printf("Broj zauzetih mjesta: %d \n",dogadjaj.brojZauzetihMjesta);
                printf("Datum dogadjaja :%s \n",dogadjaj.datum);
                printf("Vrijeme dogadjaja :%s \n",dogadjaj.vrijeme);
                printf("Cijena jedne ulaznice :%d KM \n",dogadjaj.cijena);
                printf("Sifra dogadjaja :%d \n",dogadjaj.sifra);
                printf("Organizator ovog dogadjaja : %s\n",korisnickoIme);
                if(strcmp(dogadjaj.aktivan,"A")==0)
                                        printf("Aktivan\n");
                                    else
                                        printf("Blokiran\n");
                printf("\n============================================================================\n");
                }

            }

        }else printf("nije uspjesno otvorena datoteka!");
}


void promjenaLozinke(char * korisnickoImeK,char *lozinka){

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
                            CVOR *p;
                            p=trazi(glava,korisnickoImeK);
                            if(p==0)
                                printf("\nNepostojeci nalog!");
                            else
                            {

                                strcpy(p->n.lozinka,lozinka);
                            }

                            pisi(glava);
                            brisi_listu(&glava);




}

void izvjestajProdaje(char *nazivDogadjaja,char *klijentskoIme){

FILE *lista;
DOGADJAJ dogadjaj;

if(lista=fopen("listaDogadjaja.txt","r")){

            while(fscanf(lista,"%s %d %s %s %d %d %s %s %d",dogadjaj.naziv,&dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,&dogadjaj.cijena,&dogadjaj.sifra,dogadjaj.organizator,dogadjaj.aktivan,&dogadjaj.brojZauzetihMjesta)!=EOF){

            if(strcmp(dogadjaj.organizator,klijentskoIme)==0 && strcmp(nazivDogadjaja,dogadjaj.naziv)==0){

                printf("Broj prodatih ulaznica je %d",dogadjaj.brojZauzetihMjesta);break;

            }
            if((strcmp(dogadjaj.organizator,klijentskoIme)!=0 && strcmp(nazivDogadjaja,dogadjaj.naziv)) || (strcmp(dogadjaj.organizator,klijentskoIme)!=0 && strcmp(nazivDogadjaja,dogadjaj.naziv) !=0)){
                printf("Dogadjaj koji ste unijeli ne postoji ili ga niste vi kreirali");

            }
            }


}

    fclose(lista);


}
/*

void ponistavanjeUlaznice(char *koriscnickoIme,char *nazivDogadjaja){


            FILE *korisnik;
            char korisnikTXT[50]={0};
            strcat(korisnikTXT,korisnickoIme);
            strcat(korisnikTXT,".txt");
            if(korisnik=fopen(koriscnickoIme,"r")){




            }




}

*/
//David Preradovic

typedef struct cvord
{
    DOGADJAJ d;
    struct cvord *sljedeci;
}CVORD;


void dodajd(CVORD **pglava, DOGADJAJ *d)
{
  CVORD *p,*novi = (CVORD *)malloc(sizeof(CVORD));
  novi->d = *d;
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

CVORD* trazid(CVORD *glava, int sifra)
{
  while (glava && glava->d.sifra!=sifra)
    glava = glava->sljedeci;
  return glava == 0 ? 0 : glava;
}

void pisid(CVORD *glava)
{
    FILE *fp;
    if(fp=fopen("listaDogadjaja.txt","w"))
    {
        while(glava)
        {
            fprintf(fp,"%s %d %s %s %d %d %s %s %d\n",glava->d.naziv,glava->d.brojMjesta,glava->d.datum,glava->d.vrijeme,glava->d.cijena,glava->d.sifra,glava->d.organizator,glava->d.aktivan,glava->d.brojZauzetihMjesta);
            glava=glava->sljedeci;
        }

    }
    else("Greška prilikom otvaranja datoteke!");
    fclose(fp);

}

void pisid2(CVORD *glava)
{

        while(glava)
        {
            printf("%s %d %s %s %d %d %s %s %d\n",glava->d.naziv,glava->d.brojMjesta,glava->d.datum,glava->d.vrijeme,glava->d.cijena,glava->d.sifra,glava->d.organizator,glava->d.aktivan,glava->d.brojZauzetihMjesta);
            glava=glava->sljedeci;
        }


}

int brisid(CVORD **pglava, int sifra)
{
  if (*pglava == 0)
    return 0;

  CVORD *p = 0,*prev;
  if ((*pglava)->d.sifra==sifra)
  {
    p = (*pglava);
    (*pglava) = (*pglava)->sljedeci;
  }
   else
  {

    p = (*pglava);
    while(p && p->d.sifra != sifra)
    {
        prev=p;
        p=p->sljedeci;
    }
  }

  if(p==0)
  return 0;

  prev->sljedeci=p->sljedeci;
  free(p);
  return 1;
}

void brisi_listud(CVORD **pglava)
{
  while (*pglava)
    {
        CVORD *p = (*pglava)->sljedeci;
        free(*pglava);
        *pglava = p;
    }
}

//Dejana Malinovic

void pregledKupljenihUlaznica (char *korisnikTXT)
{
    FILE *korisnik;
    char s[20];
    double p;
    if(korisnik=fopen(korisnikTXT,"r"))
    {
        fscanf(korisnik,"%s%lf",s,&p);
        printf("============================================\n");
        while(fscanf(korisnik,"%s%lf",s,&p)!=EOF)
        {
            printf("Dogadjaj:%-20s Cijena:%3.2lf\n",s,p);
            printf("============================================\n");
        }
    }
}




int main()
{
    int opcija;

   char dane;
   printf("\t\t\t\t\tSOFTVER ZA PRODAJU ULAZNICA\n");
   sleep(1);
   printf("\t\t\t\t\t\tDOBRODOSLI!\n");
   sleep(1);
   char *lozinkaK;
    do
    {
        if(dane=='D' || dane=='d')
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
                //David Preradovic
                do
                {
                    system("cls");
                    printf("Administrator:%s",korisnickoIme);
                    printf("\n\n\n");
                    printf("Odaberite jednu od ponudjenih opcija:\n 1 Kreiranje administratorskih naloga\n 2 Kreiranje klijentskih naloga\n 3 Pregled klijentskih naloga\n 4 Pregled korisnickih naloga\n 5 Aktivacije klijentskih i korisnickih naloga\n 6 Suspendovanje klijnetskih i korisnickih naloga\n 7 Pregled klijntskih dogadjaja\n 8 Ponistavanje lozinke\n 9 Rromjena lozinke \n10 Odjavljivanje\n ");
                    scanf("%d",&opcija);
                    if(opcija<1 || opcija>9)
                    {
                        do
                        {
                            printf("\nPonovo unesite opciju!");
                            scanf("%d",&opcija);
                        }
                        while(opcija<1 || opcija>9);
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
                                    if(strcmp(n.aktivan,"A")==0)
                                        printf(" Aktivan");
                                    else
                                        printf(" Suspendovan");
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

                        if(opcija==2)
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
                            else printf("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                            CVOR *p;
                            p=trazi(glava,korisnickoImeK);
                            if(p==0)
                                printf("\nNepostojeci nalog!");
                            else
                            {
                                printf("\nNalog je suspendovan!");
                                strcpy(p->n.aktivan,"S");
                            }

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
                         if(opcija==3)
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
                            CVOR *p;
                            p=trazi(glava,korisnickoImeK);
                            if(p==0)
                                printf("\nNepostojeci nalog!");
                            else
                            {
                                printf("\nNalog je aktiviran!");
                                strcpy(p->n.aktivan,"A");
                            }

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

                    if(opcija==4)
                    {
                        system("cls");
                        printf("Administrator:%s",korisnickoIme);
                        printf("\nPregled korisnickih naloga:");
                        printf("\n\n\n");

                        printf("============================================================================");

                        NALOG n;
                        {
                            FILE *fp;
                            int brojac=0;
                            if(fp=fopen("nalozi.txt","r"))
                            {
                                while(fscanf(fp,"%s %s %s %s",n.korisnickoIme,n.lozinka,n.karakter,n.aktivan)!=EOF)
                                if(strcmp(n.karakter,"O")==0)
                                {
                                    brojac++;
                                    printf("\n%d. %s",brojac,n.korisnickoIme);
                                    if(strcmp(n.aktivan,"A")==0)
                                        printf(" Aktivan");
                                    else
                                        printf(" Suspendovan");
                                    printf("\n============================================================================");
                                }
                            }
                            else printf("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                        }

                        int opcija;
                        printf("\nOdaberite jednu od ponudjenih opcija:\n 1 Brisanje korisnickih naloga\n 2 Suspendovanje korisnickih naloga\n 3 Aktivacija korisnickih naloga\n 4 Pocetni meni\n");
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

                        if(opcija==2)
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
                            else printf("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                            CVOR *p;
                            p=trazi(glava,korisnickoImeK);
                            if(p==0)
                                printf("\nNepostojeci nalog!");
                            else
                            {
                                printf("\nNalog je suspendovan!");
                                strcpy(p->n.aktivan,"S");
                            }

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
                         if(opcija==3)
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
                            else printf("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                            CVOR *p;
                            p=trazi(glava,korisnickoImeK);
                            if(p==0)
                                printf("\nNepostojeci nalog!");
                            else
                            {
                                printf("\nNalog je aktiviran!");
                                strcpy(p->n.aktivan,"A");
                            }

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

                     if(opcija==5)
                    {
                        system("cls");
                        printf("Administrator:%s",korisnickoIme);
                        printf("\nAktivacija klijentskih i korisnickih naloga:");
                        printf("\n\n\n");

                        printf("============================================================================");

                        NALOG n;
                        {
                            FILE *fp;
                            int brojac=0;
                            if(fp=fopen("nalozi.txt","r"))
                            {
                                while(fscanf(fp,"%s %s %s %s",n.korisnickoIme,n.lozinka,n.karakter,n.aktivan)!=EOF)
                                if(strcmp(n.karakter,"O")==0 || strcmp(n.karakter,"K")==0)
                                {
                                    brojac++;
                                    printf("\n%d. %s",brojac,n.korisnickoIme);
                                    if(strcmp(n.karakter,"K")==0)
                                        printf(" Klijent");
                                    else if (strcmp(n.karakter,"O")==0)
                                        printf(" Korisnik");
                                    if(strcmp(n.aktivan,"A")==0)
                                        printf(" Aktivan");
                                    else
                                        printf(" Suspendovan");
                                    printf("\n============================================================================");
                                }
                            }
                            else printf("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                        }
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
                            CVOR *p;
                            p=trazi(glava,korisnickoImeK);
                            if(p==0)
                                printf("\nNepostojeci nalog!");
                            else
                            {
                                printf("\nNalog je aktiviran!");
                                strcpy(p->n.aktivan,"A");
                            }

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
                    if(opcija==6)
                    {
                        system("cls");
                        printf("Administrator:%s",korisnickoIme);
                        printf("\nSuspendovanje klijentskih i korisnickih naloga:");
                        printf("\n\n\n");

                        printf("============================================================================");

                        NALOG n;
                        {
                            FILE *fp;
                            int brojac=0;
                            if(fp=fopen("nalozi.txt","r"))
                            {
                                while(fscanf(fp,"%s %s %s %s",n.korisnickoIme,n.lozinka,n.karakter,n.aktivan)!=EOF)
                                if(strcmp(n.karakter,"O")==0 || strcmp(n.karakter,"K")==0)
                                {
                                    brojac++;
                                    printf("\n%d. %s",brojac,n.korisnickoIme);
                                    if(strcmp(n.karakter,"K")==0)
                                        printf(" Klijent");
                                    else if (strcmp(n.karakter,"O")==0)
                                        printf(" Korisnik");
                                    if(strcmp(n.aktivan,"A")==0)
                                        printf(" Aktivan");
                                    else
                                        printf(" Suspendovan");
                                    printf("\n============================================================================");
                                }
                            }
                            else printf("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                        }
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
                            CVOR *p;
                            p=trazi(glava,korisnickoImeK);
                            if(p==0)
                                printf("\nNepostojeci nalog!");
                            else
                            {
                                printf("\nNalog je suspendovan!");
                                strcpy(p->n.aktivan,"S");
                            }

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

                    if(opcija==7)
                    {
                        system("cls");
                        printf("Administrator:%s",korisnickoIme);
                        printf("\nPregled klijentskih dogadjaja:");
                        printf("\n\n\n");

                        pregledSvihDogadjaja();

                        int opcija;
                        printf("\nOdaberite jednu od ponudjenih opcija:\n 1 Blokiranje  dogadjaja\n 2 Brisanje dogadjaja\n 3 Aktivacija dogadjaja\n 4 Pocetni meni\n");
                        do
                        {
                            scanf("%d",&opcija);
                        }
                        while(opcija<1 || opcija>4);

                        if(opcija==1)
                        {
                            int sifra;
                            printf("\nUnesite sifru dogadjaja:");
                            scanf("%d",&sifra);
                            FILE *fp;
                            DOGADJAJ dogadjaj;
                            CVORD *glava=0;
                            if(fp=fopen("listaDogadjaja.txt","r"))
                            {
                                  while(fscanf(fp,"%s %d %s %s %d %d %s %s %d",dogadjaj.naziv,&dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,&dogadjaj.cijena,&dogadjaj.sifra,dogadjaj.organizator,dogadjaj.aktivan,&dogadjaj.brojZauzetihMjesta)!=EOF)
                                  {
                                     dodajd(&glava,&dogadjaj);
                                  }
                            }
                            else printf("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                            CVORD *p=0;
                            p=trazid(glava,sifra);

                            if(p==0)
                                printf("\nNepostojeci dogadjaj!");
                            else
                            {
                                printf("\nDogadjaj je blokiran!");
                                strcpy(p->d.aktivan,"B");
                            }

                            pisid(glava);
                            brisi_listud(&glava);

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
                            int sifra;
                            printf("\nUnesite sifru dogadjaja:");
                            scanf("%d",&sifra);
                            FILE *fp;
                            DOGADJAJ dogadjaj;
                            CVORD *glava=0;
                            if(fp=fopen("listaDogadjaja.txt","r"))
                            {
                                  while(fscanf(fp,"%s %d %s %s %d %d %s %s %d",dogadjaj.naziv,&dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,&dogadjaj.cijena,&dogadjaj.sifra,dogadjaj.organizator,dogadjaj.aktivan,&dogadjaj.brojZauzetihMjesta)!=EOF)
                                  {
                                     dodajd(&glava,&dogadjaj);
                                  }
                            }
                            else printf("Greška prilikom otvaranja datoteke!");
                            fclose(fp);

                            if(brisid(&glava,sifra))
                            {
                                printf("Ujepjesno obrisan dogadjaj!");
                            }
                            else printf("Neposotjeci dogajdaj!");

                            pisid(glava);
                            brisi_listud(&glava);


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
                            int sifra;
                            printf("\nUnesite sifru dogadjaja:");
                            scanf("%d",&sifra);
                            FILE *fp;
                            DOGADJAJ dogadjaj;
                            CVORD *glava=0;
                            if(fp=fopen("listaDogadjaja.txt","r"))
                            {
                                  while(fscanf(fp,"%s %d %s %s %d %d %s %s %d",dogadjaj.naziv,&dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,&dogadjaj.cijena,&dogadjaj.sifra,dogadjaj.organizator,dogadjaj.aktivan,&dogadjaj.brojZauzetihMjesta)!=EOF)
                                  {
                                     dodajd(&glava,&dogadjaj);
                                  }
                            }
                            else printf("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                            CVORD *p=0;
                            p=trazid(glava,sifra);

                            if(p==0)
                                printf("\nNepostojeci dogadjaj!");
                            else
                            {
                                printf("\nDogadjaj je aktiviran!");
                                strcpy(p->d.aktivan,"A");
                            }

                            pisid(glava);
                            brisi_listud(&glava);

                            int kraj;
                            printf("\nDa biste se vratili na pocetni meni unesite 0:");
                            do
                            {
                                scanf("%d",&kraj);
                            }
                            while(kraj!=0);
                        }
                        while(opcija<1 || opcija>4);
                    }


                    if(opcija==8)
                    {
                        system("cls");
                        printf("Administrator:%s",korisnickoIme);
                        printf("\nPonistavanje lozinke:");
                        printf("\n\n\n");

                        printf("============================================================================");

                        NALOG n;
                        {
                            FILE *fp;
                            int brojac=0;
                            if(fp=fopen("nalozi.txt","r"))
                            {
                                while(fscanf(fp,"%s %s %s %s",n.korisnickoIme,n.lozinka,n.karakter,n.aktivan)!=EOF)
                                if(strcmp(n.korisnickoIme,korisnickoIme)!=0)
                                {
                                    brojac++;
                                    printf("\n%d. %s",brojac,n.korisnickoIme);
                                    if(strcmp(n.karakter,"K")==0)
                                        printf(" Klijent");
                                    else if (strcmp(n.karakter,"O")==0)
                                        printf(" Korisnik");
                                    else if (strcmp(n.karakter,"A")==0)
                                        printf(" Administrator");
                                    if(strcmp(n.aktivan,"A")==0)
                                        printf(" Aktivan");
                                    else
                                        printf(" Suspendovan");
                                    if(strcmp(n.lozinka,"obrisana")==0)
                                        printf(" Lozinka je ponistena!");
                                    printf("\n============================================================================");
                                }
                            }
                            else printf("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                        }
                            char korisnickoImeK[20];
                            printf("\nUnesite korisnicko ime:");
                            scanf("%s",korisnickoImeK);
                            FILE *fp;
                            NALOG na;
                            CVOR *glava=0;
                            if(fp=fopen("Nalozi.txt","r"))
                            {
                                  while(fscanf(fp,"%s %s %s %s",na.korisnickoIme,na.lozinka,na.karakter,na.aktivan)!=EOF)
                                  {
                                     dodaj(&glava,&na);
                                  }
                            }
                            else printf("Greška prilikom otvaranja datoteke!");
                            fclose(fp);
                            CVOR *p;
                            p=trazi(glava,korisnickoImeK);

                            if(p==0)
                                printf("\nNepostojeci nalog!");
                            else
                            {
                                printf("\nLozinka je obrisana!");
                                strcpy(p->n.lozinka,"obrisana");
                            }

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
                    if(opcija==9)
                    {
                        char novaLozinka[20];
                        system("cls");
                        printf("Promjena lozinke: \n\n");
                        printf("Unesite novu lozinku : ");
                        scanf("%s",novaLozinka);
                        promjenaLozinke(korisnickoIme,novaLozinka);
                        printf("Lozinka promijenjena...\n");
                        printf("\nDa biste se vratili na pocetni meni unesite 0:");
                        int kraj;
                        do
                        {
                            scanf("%d",&kraj);
                        }
                        while(kraj!=0);
                    }

                    if(opcija==10)
                    {
                        system("cls");
                        printf("Odjavljivanje...");break;
                    }
                }
                while(opcija>0 && opcija<11);


            }




            if(strcmp(karakter,"K")==0)
            {
                do{
                    // Nenad Spasojevic
                    system("cls");
                    printf("Klijent:%s",korisnickoIme);
                    printf("\n\n\n");
                    printf("Odaberite jednu od ponudjenih opcija:\n 1.Kreiranje dogadjaja\n 2.Pregled kreiranih dogadjaja \n 3.Pristup izvjestaju o prodaji \n 4.Ponistavanje pojedinacne ulaznice \n 5.Promjena lozinke\n 6.Odjavljivanje\n");
                     scanf("%d",&opcija);
                      if(opcija<1 || opcija>5)
                    {
                        do
                        {
                            printf("\nPonovo unesite opciju!");
                            scanf("%d",&opcija);
                        }
                        while(opcija<=1 && opcija>=5);
                    }


                            if(opcija==1){

                                system("cls");
                                printf("Kreiranje dogadjaja : \n");

                                kreirajDogadjaj(korisnickoIme);

                                 printf("\nDa biste se vratili na pocetni meni unesite 0:");

                                int kraj;
                                    do
                                    {
                                        scanf("%d",&kraj);
                                    }
                                    while(kraj!=0);
                                    }



                                if(opcija==2){
                                    system("cls");
                                    printf("Klijent:%s",korisnickoIme);
                                    printf("\n\n\nPregled dogadjaja: \n\n");
                                    pregledDogadjaja(korisnickoIme);
                                    printf("\nDa biste se vratili na pocetni meni unesite 0:");
                                    int kraj;
                                    do
                                    {
                                        scanf("%d",&kraj);
                                    }
                                    while(kraj!=0);
                                    }

                                    if(opcija==3){
                                        system("cls");
                                        char naziv[20];

                                        printf("Klijent : %s\n",korisnickoIme);
                                        printf("Pristup izvjestaju o prodaji : \n");
                                        printf("Unesite naziv dogadjaja : ");
                                        scanf("%s",naziv);
                                        izvjestajProdaje(naziv,korisnickoIme);
                                         printf("\nDa biste se vratili na pocetni meni unesite 0:");
                                        int kraj;
                                    do
                                    {
                                        scanf("%d",&kraj);
                                    }
                                    while(kraj!=0);


                                    }


/*
                        if(opcija==4){
                                char *nazivDogadjaja;
                                char *ImeKorisnika;
                            system("cls");
                            printf("Klijent : %s\n",korisnickoIme);
                            printf("Ponistavanje ulaznice : \n");
                            printf("Unesite naziv dogadjaja : ");
                            scanf("%s",nazivDogadjaja);
                            printf("Unesite ime korisnika kome ponistavate ulaznicu : ");
                            scanf("%s",ImeKorisnika);
                            ponistavanjeUlaznice(ImeKorisnika,nazivDogadjaja);



                               int kraj;
                                    do
                                    {
                                        scanf("%d",&kraj);
                                    }
                                    while(kraj!=0);


                        }

*/
                            if(opcija==5)
                    {
                        char novaLozinka[20];
                        system("cls");
                        printf("Promjena lozinke: \n\n");
                        printf("Unesite novu lozinku : ");
                        scanf("%s",novaLozinka);
                        promjenaLozinke(korisnickoIme,novaLozinka);
                        printf("Lozinka promijenjena...\n");
                        printf("\nDa biste se vratili na pocetni meni unesite 0:");
                        int kraj;
                        do
                        {
                            scanf("%d",&kraj);
                        }
                        while(kraj!=0);
                    }


                        if(opcija==6)
                    {
                        system("cls");
                        printf("Odjavljivanje...");
                    }
                }while(opcija!=6);

            }

            if(strcmp(karakter,"O")==0)
            {
                //Dejana Malinovic
                do
                {
                    system("cls");
                    char korisnikTXT[50]={0};
                    strcat(korisnikTXT,korisnickoIme);
                    strcat(korisnikTXT,".txt");
                    FILE *txt=fopen(korisnikTXT,"r");
                    if(txt==NULL)
                    {
                        FILE *noviTxt;
                        if(noviTxt=fopen(korisnikTXT,"w"))
                        {
                            fprintf(noviTxt,"%s\n%lf",korisnickoIme,50.00);
                        }
                        fclose(noviTxt);
                    }
                    printf("Korisnik:%s\n",korisnickoIme);
                    int opcija;
                    printf("Izaberite jednu od ponudjenih pocija:\n\n");
                    printf("1. Pregled dogadjaja.\n");
                    printf("2. Kupovina ulaznice.\n");
                    printf("3. Pregled kupljenih ulaznica.\n");
                    printf("4. Ponistavanje kupljene ulaznice.\n");
                    printf("5. Pregled kredita.\n");
                    printf("6. Promjena lozinke.\n");
                    printf("7. Odjava sa sistema.\n");
                    scanf("%d",&opcija);
                    if(opcija==1)
                    {
                        system("cls");
                        printf("Pregled svih dogadjaja: \n\n");
                        pregledSvihDogadjaja();
                        printf("\nDa biste se vratili na pocetni meni unesite 0:");
                        int kraj;
                        do
                        {
                            scanf("%d",&kraj);
                        }
                        while(kraj!=0);
                    }
                    if(opcija==2)
                    {
                        system("cls");
                        printf("Kupovina ulaznice: \n\n");
                        pregledSvihDogadjaja();
                        char nazivDogadjaja[50];
                        double dostupanKredit,potrebanKredit,preostaliKredit;
                        FILE* korisnik;
                        char s[30];
                        int p;
                        if(korisnik=fopen(korisnikTXT,"r"))
                        {
                            fscanf(korisnik,"%s%lf",s,&dostupanKredit);
                            fclose(korisnik);
                        }
                        printf("Unesite naziv dogadjaja za koji zelite da kupite ulaznicu:");
                        scanf("%s",nazivDogadjaja);
                        FILE* dogadjaji;
                        if(dogadjaji=fopen("listaDogadjaja.txt","r"))
                        {
                            int i;
                            int t=0;
                            do
                            {
                                char dogadjaj[30]={0};
                                i=fscanf(dogadjaji,"%s",dogadjaj);
                                if(strcmp(nazivDogadjaja,dogadjaj)==0)
                                {
                                    t++;
                                    break;
                                }
                            }
                            while(i!=EOF);
                            if (t==0)
                            {
                                printf("Dogadjaj sa tim nazivom ne postoji.\n");
                            }
                            else
                            {
                                fscanf(dogadjaji,"%d%s%lf",&p,s,&potrebanKredit);
                                if(potrebanKredit>dostupanKredit)
                                {
                                    printf("Nemate dovoljno kredita na racunu.");
                                }
                                else
                                {
                                    int k, sifra;
                                    char string[20];
                                    fscanf(dogadjaji,"%s%d",string,&sifra);
                                    FILE *fp;
                                    DOGADJAJ dogadjaj;
                                    CVORD *glava=0;
                                    if(fp=fopen("listaDogadjaja.txt","r"))
                                    {
                                          while(fscanf(fp,"%s %d %s %s %d %d %s %s %d",dogadjaj.naziv,&dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,&dogadjaj.cijena,&dogadjaj.sifra,dogadjaj.organizator,dogadjaj.aktivan,&dogadjaj.brojZauzetihMjesta)!=EOF)
                                          {
                                             dodajd(&glava,&dogadjaj);
                                          }
                                    }
                                    else printf("Greška prilikom otvaranja datoteke!");
                                    fclose(fp);
                                    CVORD *p=0;
                                    p=trazid(glava,sifra);
                                    if(p==0)
                                        printf("\nNepostojeci dogadjaj!");
                                    else
                                    {
                                        if(p->d.brojMjesta==p->d.brojZauzetihMjesta)
                                            printf("Sve ulaznice su rasprodane.\n");
                                        else
                                        {
                                            p->d.brojZauzetihMjesta++;
                                            /*FILE *fp;
                                            NALOG na;
                                            CVOR *glava;
                                            double kredit;
                                            if(fp=fopen("Nalozi.txt","r"))
                                            {
                                                while(fscanf(fp,"%s %s %s %s %lf",na.korisnickoIme,na.lozinka,na.karakter,na.aktivan,&na.kredit)!=EOF)
                                                {
                                                    dodaj(&glava,&na);
                                                }
                                            }
                                            else("Greška prilikom otvaranja datoteke!");
                                            fclose(fp);
                                            CVOR *p;
                                            p=trazi(glava,korisnickoIme);
                                            if(p==0)
                                                printf("\nNepostojeci nalog!");
                                            else
                                            {
                                                na.kredit=na.kredit-potrebanKredit;
                                            }
                                            pisi(glava);
                                            brisi_listu(&glava);*/
                                            printf("Uspijesno ste kupili kartu.");
                                            if(korisnik=fopen(korisnikTXT,"a+"))
                                            {
                                                fprintf(korisnik,"\n%s %lf",nazivDogadjaja,potrebanKredit);
                                                fclose(korisnik);
                                            }
                                        }
                                    }
                                    pisid(glava);
                                    brisi_listud(&glava);
                                }
                            }
                            fclose(dogadjaji);
                        }
                        printf("\nDa biste se vratili na pocetni meni unesite 0:");
                        int kraj;
                        do
                        {
                            scanf("%d",&kraj);
                        }
                        while(kraj!=0);
                    }
                    if(opcija==3)
                    {
                        system("cls");
                        printf("Pregled kupljenih ulaznica: \n\n");
                        pregledKupljenihUlaznica(korisnikTXT);
                        printf("\nDa biste se vratili na pocetni meni unesite 0:");
                        int kraj;
                        do
                        {
                            scanf("%d",&kraj);
                        }
                        while(kraj!=0);
                    }
                    if(opcija==4)
                    {
                        system("cls");
                        printf("Ponistavanje kupljene ulaznice: \n\n");
                        pregledKupljenihUlaznica(korisnikTXT);
                        char dogadjaj[30];
                        FILE *dogadjaji;
                        printf("Unesite naziv dogadjaja za koji zelite da ponistite ulaznicu:");
                        scanf("%s",dogadjaj);
                        if(dogadjaji=fopen("listaDogadjaja.txt","r"))
                        {
                            int i;
                            int t=0;
                            do
                            {
                                char dogadjajUListi[30]={0};
                                i=fscanf(dogadjaji,"%s",dogadjajUListi);
                                if(strcmp(dogadjaj,dogadjajUListi)==0)
                                {
                                    t++;
                                    break;
                                }
                            }
                            while(i!=EOF);
                            if (t==0)
                            {
                                printf("Dogadjaj sa tim nazivom ne postoji.\n");
                            }
                            else
                            {
                                printf("Uspijesno ste ponistili kupljenu ulaznicu.\n");
                            }
                            fclose(dogadjaji);
                        }
                        printf("\nDa biste se vratili na pocetni meni unesite 0:");
                        int kraj;
                        do
                        {
                            scanf("%d",&kraj);
                        }
                        while(kraj!=0);
                    }
                    if(opcija==5)
                    {
                        system("cls");
                        printf("Pregled kredita: \n\n");
                        FILE* korisnik;
                        double kredit;
                        char s[30];
                        if(korisnik=fopen(korisnikTXT,"r"))
                        {
                            fscanf(korisnik,"%s%lf",s,&kredit);
                            printf("Dostupan kredit na racunu:%.2lfKM\n",kredit);
                            fclose(korisnik);
                        }
                        printf("\nDa biste se vratili na pocetni meni unesite 0:");
                        int kraj;
                        do
                        {
                            scanf("%d",&kraj);
                        }
                        while(kraj!=0);
                    }
                    if(opcija==6)
                    {
                        char novaLozinka[20];
                        system("cls");
                        printf("Promjena lozinke: \n\n");
                        printf("Unesite novu lozinku : ");
                        scanf("%s",novaLozinka);
                        promjenaLozinke(korisnickoIme,novaLozinka);
                        printf("Lozinka promijenjena...\n");
                        printf("\nDa biste se vratili na pocetni meni unesite 0:");
                        int kraj;
                        do
                        {
                            scanf("%d",&kraj);
                        }
                        while(kraj!=0);
                    }
                    if(opcija==7)
                    {
                        system("cls");
                        printf("Odjava...");
                        break;
                    }
                }
                while(opcija!=7);
            }


        }
        else if(dane=='N')
        {
            system("cls");
            char korisnickoIme[20];
            char lozinka[20];
            printf("Registracija:\n\n\n");
            int brojac=0;
            do
            {
                if(brojac>0) printf("Korisnicko ime je u upotrebi!\n");
                printf("Unesite korisnicko ime:\n");
                scanf("%s",korisnickoIme);
                brojac++;
            }
            while(nalogPostoji(korisnickoIme));

            printf("Unsite lozinku:");
            scanf("%s",lozinka);

            FILE *fp;
            if(fp=fopen("nalozi.txt","a"))
            {
                fprintf(fp,"\n%s %s O A",korisnickoIme,lozinka);
            }
            else printf("Greska prilikom otvaranja datoteke!");
            fclose(fp);
            dane='d';
        }
        printf("Da li vec imate kreiran nalog? Da:[D] Ne:[N]\n");
        scanf("%c",&dane);
        system("cls");
    }
    while(dane!='0');

}
