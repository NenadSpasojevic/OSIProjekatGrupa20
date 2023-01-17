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

typedef struct cvor
{
    NALOG n;
    struct cvor *sljedeci;
}CVOR;

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

            if(strcmp(dogadjaj.organizator,klijentskoIme)==0 && strcmp(nazivDogadjaja,dogadjaj.naziv)==0 && strcmp(dogadjaj.aktivan,"A")==0){
                    system("cls");
                printf("Broj prodatih ulaznica je %d",dogadjaj.brojZauzetihMjesta);break;

            }

            else if((strcmp(dogadjaj.organizator,klijentskoIme)!=0 && strcmp(nazivDogadjaja,dogadjaj.naziv)==0) || (strcmp(dogadjaj.organizator,klijentskoIme)!=0 && strcmp(nazivDogadjaja,dogadjaj.naziv) !=0)){
                system("cls");
                printf("Dogadjaj koji ste unijeli ne postoji ili ga niste vi kreirali");


            }
            }


}

    fclose(lista);


}

void pregledKupljenihUlaznica (char *korisnikTXT)
{
    FILE *korisnik;
    DOGADJAJ d;
    if(korisnik=fopen(korisnikTXT,"r"))
    {
        printf("==============================================================================================================================================\n");
        while(fscanf(korisnik,"%s %s %s %d %d %s",d.naziv,d.datum,d.vrijeme,&d.cijena,&d.sifra,d.organizator)!=EOF)
        {
            printf("Dogadjaj:%-20s Datum:%-15s Vrijeme:%-15s Cijena:%d.00KM      Sifra:%-10d Organizator:%-30s\n",d.naziv,d.datum,d.vrijeme,d.cijena,d.sifra,d.organizator);
            printf("==============================================================================================================================================\n");
        }
    }
}


void pregledKupljenihUlaznicaJedanOrganizator(char *korisnikTXT,char*organizator)
{
    FILE *korisnik;
    DOGADJAJ d;
    printf("Kupljene ulaznice za vase dogadjaje su : \n");

    if(korisnik=fopen(korisnikTXT,"r"))
    {

        while(fscanf(korisnik,"%s %s %s %d %d %s",d.naziv,d.datum,d.vrijeme,&d.cijena,&d.sifra,d.organizator)!=EOF)
        {
            if(strcmp(d.organizator,organizator)==0){
                    printf("==============================================================================================================================================\n");
                printf("Dogadjaj:%-20s Datum:%-15s Vrijeme:%-15s Cijena:%d.00KM      Sifra:%-10d Organizator:%-30s\n",d.naziv,d.datum,d.vrijeme,d.cijena,d.sifra,d.organizator);

            }


        }
                printf("==============================================================================================================================================\n");

    }

}
void pisiKarte(CVORD *glava, char* korisnikTXT)
{
    FILE *fp;
    if(fp=fopen(korisnikTXT,"w"))
    {
        while(glava)
        {
            fprintf(fp,"%s %s %s %d %d %s\n",glava->d.naziv,glava->d.datum,glava->d.vrijeme,glava->d.cijena,glava->d.sifra,glava->d.organizator);
            glava=glava->sljedeci;
        }

    }
    else("Greška prilikom otvaranja datoteke!");
    fclose(fp);

}
/*

void ponistavanjeUlaznice(char *korisnickoIme,char *organizator){


    FILE *lista;
    CVORD *glava=0,*glava2=0;
    char korisnikTXT[50]={0};
    strcat(korisnikTXT,korisnickoIme);
    strcat(korisnikTXT,".txt");
    int sifraD;
    FILE *korisnik;
    DOGADJAJ d,d2;
    pregledKupljenihUlaznicaJedanOrganizator(korisnikTXT,organizator);
    if(korisnik=fopen(korisnikTXT,"r"))
    {

        while(fscanf(korisnik,"%s %s %s %d %d %s",d.naziv,d.datum,d.vrijeme,&d.cijena,&d.sifra,d.organizator)!=EOF)
        {


                dodajd(&glava,&d);


        }
    }fclose(korisnik);
    printf("\n\nUnesite sifru dogadjaja za koji zelite ponistiti ulaznicu : ");
    scanf("%d",&sifraD);
    CVORD* p=0;
    p=trazid(glava,sifraD);
    if(p==0)
    {
        printf("Dogadjaj ne postoji");
    }
    else
    {
        char korisnikKredit[50]={0};
        strcat(korisnikKredit,korisnickoIme);
        strcat(korisnikKredit,"_kredit.txt");
        FILE *kredit;
        double trenutniKredit,ukupanKredit;
        if(kredit=fopen(korisnikKredit,"r"))
        {
            fscanf(kredit,"%lf",&trenutniKredit);
        }
        fclose(kredit);
        ukupanKredit=trenutniKredit+p->d.cijena;
        if(kredit=fopen(korisnikKredit,"w"))
        {
            fprintf(kredit,"%.2lf",ukupanKredit);
        }
        fclose(kredit);
        FILE *korisnik2;
        if(korisnik2=fopen(korisnikTXT,"r"))
        {
            while(fscanf(korisnik2,"%s %s %s %d %d %s",d2.naziv,d2.datum,d2.vrijeme,&d2.cijena,&d2.sifra,d2.organizator)!=EOF)
            {
                dodajd(&glava2,&d2);
            }
        }
        fclose(korisnik2);
        brisid(&glava2,sifraD);
        pisiKarte(glava2,korisnikTXT);
        FILE *fp;
        DOGADJAJ dogadjaj;
        CVORD *glavad=0;
        if(fp=fopen("listaDogadjaja.txt","r"))
        {
            while(fscanf(fp,"%s %d %s %s %d %d %s %s %d",dogadjaj.naziv,&dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,&dogadjaj.cijena,&dogadjaj.sifra,dogadjaj.organizator,dogadjaj.aktivan,&dogadjaj.brojZauzetihMjesta)!=EOF)
            {
                dodajd(&glavad,&dogadjaj);
            }
        }
        else printf("Greška prilikom otvaranja datoteke!");
        fclose(fp);
        CVORD *p=0;
        p=trazid(glavad,sifraD);
        p->d.brojZauzetihMjesta--;
        pisid(glavad);
        printf("Uspijesno ste ponistili ulaznicu.\n");
    }
}

*/



void ponistavanjeUlaznice(char *organizator){


    FILE *lista;
    NALOG nalog;
    CVORD *glava=0,*glava2=0;

    int sifraD;
    FILE *korisnik;
    DOGADJAJ d,d2;

    if(lista=fopen("nalozi.txt","r+")){

        while(fscanf(lista,"%s %s %s %s",nalog.korisnickoIme,nalog.lozinka,nalog.karakter,nalog.aktivan)!=EOF){

            if(strcmp(nalog.karakter,"O")==0 && strcmp(nalog.aktivan,"A")==0 ){
            printf("==============================================================================================================================================\n");
                printf("%s\n",nalog.korisnickoIme);
            }

        }

            printf("==============================================================================================================================================\n");

    }
                            char korisnickoIme[20];
                            printf("Unesite ime korisnika kome ponistavate ulaznicu : ");
                            scanf("%s",korisnickoIme);
                            char korisnikTXT[50]={0};
                            strcat(korisnikTXT,korisnickoIme);
                            strcat(korisnikTXT,".txt");
                        pregledKupljenihUlaznicaJedanOrganizator(korisnikTXT,organizator);
    if(korisnik=fopen(korisnikTXT,"r"))
    {

        while(fscanf(korisnik,"%s %s %s %d %d %s",d.naziv,d.datum,d.vrijeme,&d.cijena,&d.sifra,d.organizator)!=EOF)
        {


                dodajd(&glava,&d);


        }
    }fclose(korisnik);
    printf("\n\nUnesite sifru dogadjaja za koji zelite ponistiti ulaznicu : ");
    scanf("%d",&sifraD);
    CVORD* p=0;
    p=trazid(glava,sifraD);
    if(p==0)
    {
        printf("Dogadjaj ne postoji");
    }
    else
    {
        char korisnikKredit[50]={0};
        strcat(korisnikKredit,korisnickoIme);
        strcat(korisnikKredit,"_kredit.txt");
        FILE *kredit;
        double trenutniKredit,ukupanKredit;
        if(kredit=fopen(korisnikKredit,"r"))
        {
            fscanf(kredit,"%lf",&trenutniKredit);
        }
        fclose(kredit);
        ukupanKredit=trenutniKredit+p->d.cijena;
        if(kredit=fopen(korisnikKredit,"w"))
        {
            fprintf(kredit,"%.2lf",ukupanKredit);
        }
        fclose(kredit);
        FILE *korisnik2;
        if(korisnik2=fopen(korisnikTXT,"r"))
        {
            while(fscanf(korisnik2,"%s %s %s %d %d %s",d2.naziv,d2.datum,d2.vrijeme,&d2.cijena,&d2.sifra,d2.organizator)!=EOF)
            {
                dodajd(&glava2,&d2);
            }
        }
        fclose(korisnik2);
        brisid(&glava2,sifraD);
        pisiKarte(glava2,korisnikTXT);
        FILE *fp;
        DOGADJAJ dogadjaj;
        CVORD *glavad=0;
        if(fp=fopen("listaDogadjaja.txt","r"))
        {
            while(fscanf(fp,"%s %d %s %s %d %d %s %s %d",dogadjaj.naziv,&dogadjaj.brojMjesta,dogadjaj.datum,dogadjaj.vrijeme,&dogadjaj.cijena,&dogadjaj.sifra,dogadjaj.organizator,dogadjaj.aktivan,&dogadjaj.brojZauzetihMjesta)!=EOF)
            {
                dodajd(&glavad,&dogadjaj);
            }
        }
        else printf("Greška prilikom otvaranja datoteke!");
        fclose(fp);
        CVORD *p=0;
        p=trazid(glavad,sifraD);
        p->d.brojZauzetihMjesta--;
        pisid(glavad);
        printf("Uspjesno ponistena ulaznica !\n");


    }
}


//David Preradovic



//Dejana Malinovic





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

            if(!provjera(korisnickoIme,lozinka,&karakter))
            {
                    system("cls");
                    printf("Administrator:%s",korisnickoIme);
                    printf("\n\n\n");
                    if(strcmp(lozinka,"prvalozinka")==0)
                    {
                        char novaLozinka[20];
                        system("cls");
                        printf("Promjena lozinke: \n\n");
                        printf("Unesite novu lozinku : ");
                        scanf("%s",novaLozinka);
                        promjenaLozinke(korisnickoIme,novaLozinka);
                        printf("Lozinka promijenjena...\n");
                    }
            }

            if(strcmp(karakter,"A")==0)
            {
                //David Preradovic
                do
                {

                    system("cls");
                    printf("Administrator:%s",korisnickoIme);
                    printf("\n\n\n");
                    printf("Odaberite jednu od ponudjenih opcija:\n 1 Kreiranje administratorskih naloga\n 2 Kreiranje klijentskih naloga\n 3 Pregled klijentskih naloga\n 4 Pregled korisnickih naloga\n 5 Aktivacije klijentskih i korisnickih naloga\n 6 Suspendovanje klijnetskih i korisnickih naloga\n 7 Pregled klijntskih dogadjaja\n 8 Ponistavanje lozinke\n 9 Promjena lozinke \n10 Odjavljivanje\n ");
                    scanf("%d",&opcija);
                    if(opcija<1 || opcija>11)
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
                        if(nalogPostoji(korisnickoImeA))
                        {
                            printf("\nNalog vec postoji!");
                        }
                        else
                        {
                            FILE *fp;
                            if(fp=fopen("nalozi.txt","a"))
                            {
                                fprintf(fp,"%s %s A A\n",korisnickoImeA,"prvalozinka");
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
                                fprintf(fp,"%s %s K A\n",korisnickoImeA,lozinkaA);
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
                      if(opcija<1 || opcija>6)
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

                                    if(opcija==4)
                            {
                                printf("Ponistavanje pojedinacne ulaznice:\n");
                                printf("Uneite ime korisnickog naloga kojem zelite ponistiti ulaznicu:");
                                char odabraniKorisnik[50];
                                scanf("%s",odabraniKorisnik);
                                //ako nije dobro korisnicko ime ukucano
                                ponistavanjeUlaznice(odabraniKorisnik,korisnickoIme);
                                printf("\nDa biste se vratili na pocetni meni unesite 0:");
                                int kraj;
                                do
                                {
                                    scanf("%d",&kraj);
                                }
                                while(kraj!=0);
                            }
                            */
                        if(opcija==4)
                            {
                                system("cls");
                                printf("Ponistavanje pojedinacne ulaznice:\n");
                                //ako nije dobro korisnicko ime ukucano
                                ponistavanjeUlaznice(korisnickoIme);
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
                        break;
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
                        }
                        fclose(noviTxt);
                    }
                    char korisnikKredit[50]={0};
                    strcat(korisnikKredit,korisnickoIme);
                    strcat(korisnikKredit,"_kredit.txt");
                    FILE *kredit=fopen(korisnikKredit,"r");
                    if(kredit==NULL)
                    {
                        FILE *noviTxt;
                        double pocetni=100;
                        if(noviTxt=fopen(korisnikKredit,"w"))
                        {
                            fprintf(noviTxt,"%.2lf\n",pocetni);
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
                        FILE* kreditFILE,*korisnik;
                        char s[30];
                        int p;
                        if(kreditFILE=fopen(korisnikKredit,"r"))
                        {
                            fscanf(kreditFILE,"%lf",&dostupanKredit);
                            fclose(kreditFILE);
                        }
                        fclose(kreditFILE);
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
                                char s1[30],s2[30];
                                char a[2];
                                int sifra;
                                fscanf(dogadjaji,"%d%s%s%lf%d%s%s",&p,s,s1,&potrebanKredit,&sifra,s2,a);
                                if(potrebanKredit>dostupanKredit)
                                {
                                    printf("Nemate dovoljno kredita na racunu.");
                                }
                                else if(a[0]=='B' && potrebanKredit<dostupanKredit)
                                {
                                    printf("Nije moguce kupiti ulaznicu, dogadjaj je blokiran.\n");
                                }
                                else
                                {
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
					    int preuzimanje;
					    do
					    {
				           	 printf("Kako zelite da preuzmete ulaznicu?\n1. Elektronski.\n2. Licno.\n");
						 scanf("%d",&preuzimanje);
						 if(preuzimanje==1)
						 	printf("Ulaznica ce Vam biti poslana putem elektronske poste.\n");
						 else
						 	printf("Ulaznica Vam je rezervisana. Mozete je preuzeti na nasem prodajnom mjestu.\n");
					    }while(preuzimanje<1 || preuzimanje>2);
                                            p->d.brojZauzetihMjesta++;
                                            printf("Uspijesno ste kupili ulaznicu.");
                                            if(korisnik=fopen(korisnikTXT,"a+"))
                                            {
                                                fprintf(korisnik,"%s %s %s %d %d %s\n",p->d.naziv,p->d.datum,p->d.vrijeme,p->d.cijena,p->d.sifra,p->d.organizator);
                                                fclose(korisnik);
                                            }
                                            FILE *noviTxt;
                                            preostaliKredit=dostupanKredit-potrebanKredit;
                                            if(noviTxt=fopen(korisnikKredit,"w"))
                                            {
                                                fprintf(noviTxt,"%.2lf\n",preostaliKredit);
                                            }
                                            fclose(noviTxt);
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
                        int sifra;
                        printf("Unesite sifru ulaznice koju zelite da ponistite:");
                        scanf("%d",&sifra);
                        FILE *fp2;
                        DOGADJAJ dogadjaj2;
                        CVORD *glava4=0;
                        if(fp2=fopen("listaDogadjaja.txt","r"))
                        {
                            while(fscanf(fp2,"%s %d %s %s %d %d %s %s %d",dogadjaj2.naziv,&dogadjaj2.brojMjesta,dogadjaj2.datum,dogadjaj2.vrijeme,&dogadjaj2.cijena,&dogadjaj2.sifra,dogadjaj2.organizator,dogadjaj2.aktivan,&dogadjaj2.brojZauzetihMjesta)!=EOF)
                            {
                                dodajd(&glava4,&dogadjaj2);
                            }
                        }
                        else printf("Greška prilikom otvaranja datoteke!");
                        fclose(fp2);
                        CVORD *p3=0;
                        p3=trazid(glava4,sifra);
                        if (p3==NULL)
                        {
                            printf("Unijeli ste nevazecu sifru.\n");
                        }
                        else
                        {
                        if(p3->d.aktivan[0]=='B')
                        {
                            printf("Nije moguce ponistiti ulaznicu, dogadjaj vise nije aktivan.\n");
                        }
                        else
                        {
                            FILE *fp;
                            DOGADJAJ d;
                            CVORD *glava=0;
                            double trenutniKredit,rezultatKredit;
                            if(fp=fopen(korisnikTXT,"r"))
                            {
                                while(fscanf(fp,"%s %s %s %d %d %s",d.naziv,d.datum,d.vrijeme,&d.cijena,&d.sifra,d.organizator)!=EOF)
                                {
                                    dodajd(&glava,&d);
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
                                FILE *kreditFILE;
                                if(kreditFILE=fopen(korisnikKredit,"r"))
                                {
                                    fscanf(kreditFILE,"%lf",&trenutniKredit);
                                }
                                fclose(kreditFILE);
                                FILE *noviTxt;
                                rezultatKredit=trenutniKredit+p->d.cijena;
                                brisi_listud(&glava);
                                if(noviTxt=fopen(korisnikKredit,"w"))
                                {
                                    fprintf(noviTxt,"%.2lf\n",rezultatKredit);
                                }
                                fclose(noviTxt);
                                CVORD *glava2=0;
                                double trenutniKredit,rezultatKredit;
                                if(fp=fopen(korisnikTXT,"r"))
                                {
                                    while(fscanf(fp,"%s %s %s %d %d %s",d.naziv,d.datum,d.vrijeme,&d.cijena,&d.sifra,d.organizator)!=EOF)
                                    {
                                        dodajd(&glava2,&d);
                                    }
                                }
                                else printf("Greška prilikom otvaranja datoteke!");
                                fclose(fp);
                                if(brisid(&glava2,sifra))
                                {
                                    char korisnikTXT2[50]={0};
                                    strcat(korisnikTXT2,korisnickoIme);
                                    strcat(korisnikTXT2,".txt");
                                    pisiKarte(glava2,korisnikTXT2);
                                }
                                printf("Uspijesno ste ponistili ulaznicu.\nOdradjen je povrat novca.\n");
                                FILE *fp1;
                                DOGADJAJ dogadjaj1;
                                CVORD *glava3=0;
                                if(fp1=fopen("listaDogadjaja.txt","r"))
                                {
                                    while(fscanf(fp1,"%s %d %s %s %d %d %s %s %d",dogadjaj1.naziv,&dogadjaj1.brojMjesta,dogadjaj1.datum,dogadjaj1.vrijeme,&dogadjaj1.cijena,&dogadjaj1.sifra,dogadjaj1.organizator,dogadjaj1.aktivan,&dogadjaj1.brojZauzetihMjesta)!=EOF)
                                    {
                                        dodajd(&glava3,&dogadjaj1);
                                    }
                                }
                                else printf("Greška prilikom otvaranja datoteke!");
                                fclose(fp1);
                                CVORD *p=0;
                                p=trazid(glava3,sifra);
                                if(p==0)
                                    printf("\nNepostojeci dogadjaj!");
                                else
                                {
                                    p->d.brojZauzetihMjesta--;
                                    pisid(glava3);
                                }

                            }}}
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
                        FILE *kreditFILE;
                        double dostupanKredit;
                        if(kreditFILE=fopen(korisnikKredit,"r"))
                        {
                            fscanf(kreditFILE,"%lf",&dostupanKredit);
                            fclose(kreditFILE);
                        }
                        fclose(kreditFILE);
                        printf("Iznos kredita na vasem racunu: %.2lfKM\n",dostupanKredit);
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
                while(opcija>0 && opcija<8);

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

            printf("Unesite lozinku:");
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
        printf("Da li vec imate kreiran nalog? Da:[D] Ne:[N] Kraj:[K]\n");
        scanf("%c",&dane);
        system("cls");
    }
    while(dane!='K');

}
