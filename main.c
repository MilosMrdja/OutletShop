#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int brojProizvoda = 0;
typedef struct materijal{
    char ime[30];
}materijal;

typedef struct proizvod{
    char ime[30];
    int barkod;
    float cena;
    int brojMaterijala;
    int dan, mesec, godina;
    materijal* materijali;
}proizvod;
proizvod* proizvodi;

int PretragaBarKod(int barkod){
    for(int i = 0;i < brojProizvoda; i++){
        if(proizvodi[i].barkod == barkod){
            return i;
        }
    }
    return -1;

}

void dodavanjeNovogProizvoda(){
    fflush(stdin);
    int tip, provera;
    proizvodi = realloc(proizvodi, sizeof(proizvod)*(brojProizvoda));
    printf("Unesite naziv proizvoda: ");
    scanf("%[^\n]", proizvodi[brojProizvoda].ime);
    printf("Unesite barkod: ");
    do
    {
        scanf("%i", &proizvodi[brojProizvoda].barkod);
        provera=PretragaBarKod(proizvodi[brojProizvoda].barkod);
        if(provera!=-1)
            printf("Barkod mora biti jedinstven!!!\n");
    }while(provera!=-1);
    printf("Unesite cenu: ");
    scanf("%f", &proizvodi[brojProizvoda].cena);
    printf("Tip proizvoda(1-Gotov 2-Proizvod koji se pravi): ");
    scanf("%i", &tip);
    if(tip==2)
    {
        printf("Koliko ima materijala: ");
        scanf("%i", &proizvodi[brojProizvoda].brojMaterijala);
        proizvodi[brojProizvoda].materijali=malloc(sizeof(materijal)*proizvodi[brojProizvoda].brojMaterijala);
        for(int i=0; i<proizvodi[brojProizvoda].brojMaterijala; i++)
        {
            printf("Unesite ime %i. materijala: ", i+1);
            scanf("%s", proizvodi[brojProizvoda].materijali[i].ime);
        }
    }
    else
    {
        proizvodi[brojProizvoda].brojMaterijala=0;
    }
    printf("Unesite datum\nGodinu: ");
    scanf("%i", &proizvodi[brojProizvoda].godina);
    printf("\nMesec: ");
    scanf("%i", &proizvodi[brojProizvoda].mesec);
    printf("\nDan: ");
    scanf("%i", &proizvodi[brojProizvoda].dan);

    brojProizvoda++;

}
void PrikazSvih()
{
    if(brojProizvoda==0)
    {
        printf("Nema proizvoda\n");
        return;
    }
    for(int i=0; i<brojProizvoda; i++)
    {
        printf("Naziv proizvoda: %s\n", proizvodi[i].ime);
        printf("Barkod prizvoda: %d\n", proizvodi[i].barkod);
        printf("Cena prizvoda: %.2f\n", proizvodi[i].cena);
        printf("Broj materijala proizvoda: %d\n", proizvodi[i].brojMaterijala);
        for(int j=0; j<proizvodi[i].brojMaterijala; j++)
        {
            printf("\n Materijal %i: %s\n", j+1, proizvodi[i].materijali[j].ime);
        }
        printf("Datum: %i %i %i\n\n", proizvodi[i].dan, proizvodi[i].mesec, proizvodi[i].godina);
    }
}
int PretragaIme(char ime[30])
{
    for(int i=0;i<brojProizvoda;i++)
    {
        if(!strcmp(ime, proizvodi[i].ime))
        {
            return i;
        }
    }
    return -1;
}
void IzmenaProizvoda(int index)
{
    int izbor;
    printf("Promenite:\n1. Ime proizvoda\n2. Barkod\n3. Cena\n4. Datum\n>>>");
    do
    {
        scanf("%i", &izbor);
    }while(izbor<1||izbor>4);
    switch(izbor)
    {
    case 1:
        printf("Unesite novo ime proizvoda: ");
        scanf("%s", proizvodi[index].ime);
        break;
    case 2:
        printf("Unesite novi barkod: ");
        do
        {
            scanf("%i", &proizvodi[index].barkod);
        }while(PretragaBarKod(proizvodi[index].barkod)!=-1);
        break;
    case 3:
        printf("Unesite novu cenu: ");
        scanf("%f", &proizvodi[index].cena);
        break;
    case 4:
        printf("Unesite novi datum\n");
        printf("godina: ");
        scanf("%i", &proizvodi[index].godina);
        printf("mesec: ");
        scanf("%i", &proizvodi[index].mesec);
        printf("dan: ");
        scanf("%i", &proizvodi[index].dan);
        break;
    }
}
void BrisanjeProizvoda(int provera)
{
    proizvod* kopija=malloc(sizeof(proizvod)*brojProizvoda);
    for(int i=0; i<brojProizvoda; i++)
    {
        strcpy(kopija[i].ime, proizvodi[i].ime);
        kopija[i].cena=proizvodi[i].cena;
        kopija[i].barkod=proizvodi[i].barkod;
        kopija[i].brojMaterijala=proizvodi[i].brojMaterijala;
        if(kopija[i].brojMaterijala!=0)
            kopija[i].materijali=malloc(sizeof(materijal)*(kopija[i].brojMaterijala));
        for(int j=0; j<kopija[i].brojMaterijala; j++)
        {
            int b;
            for(b=0;proizvodi[i].materijali[j].ime[b]!='\0';b++)
            {
                kopija[i].materijali[j].ime[b]=proizvodi[i].materijali[j].ime[b];
            }
            kopija[i].materijali[j].ime[b]='\0';
        }
        kopija[i].dan=proizvodi[i].dan;
        kopija[i].mesec=proizvodi[i].mesec;
        kopija[i].godina=proizvodi[i].godina;
    }
    free(proizvodi);
    proizvodi=malloc(sizeof(proizvod)*(--brojProizvoda));
    for(int i=0, a=0; a<(brojProizvoda+1); i++, a++)
    {
        if(a==provera)
        {
            i--;
            continue;
        }
        strcpy(proizvodi[i].ime, kopija[a].ime);
        proizvodi[i].cena=kopija[a].cena;
        proizvodi[i].barkod=kopija[a].barkod;
        proizvodi[i].brojMaterijala=kopija[a].brojMaterijala;
        if(proizvodi[i].brojMaterijala!=0)
            proizvodi[i].materijali=malloc(sizeof(materijal)*(proizvodi[i].brojMaterijala));
        for(int j=0; j<proizvodi[i].brojMaterijala; j++)
        {
            int b;
            for(b=0;kopija[a].materijali[j].ime[b]!='\0';b++)
            {
                proizvodi[i].materijali[j].ime[b]=kopija[a].materijali[j].ime[b];
            }
            proizvodi[i].materijali[j].ime[b]='\0';
        }
        proizvodi[i].dan=kopija[a].dan;
        proizvodi[i].mesec=kopija[a].mesec;
        proizvodi[i].godina=kopija[a].godina;
    }
    free(kopija);
}

void Cenovnik()
{
    for(int i=0;i<brojProizvoda;i++)
    {
        printf("Sifra: %i\nCena:%.2f\nDatum: %i %i %i\n\n", proizvodi[i].barkod, proizvodi[i].cena, proizvodi[i].dan, proizvodi[i].mesec, proizvodi[i].godina);
    }
}

FILE *fp;
void pisanje()
{
    int i=0;
    fp=fopen("Proizvodi.txt", "w");
    fprintf(fp, "%i\n", brojProizvoda);
    while(i<brojProizvoda)
    {
        fprintf(fp,"%s;", proizvodi[i].ime);
        fprintf(fp,"%i;", proizvodi[i].barkod);
        fprintf(fp,"%.2f;", proizvodi[i].cena);
        fprintf(fp,"%i;%i;%i;", proizvodi[i].dan, proizvodi[i].mesec, proizvodi[i].godina);
        fprintf(fp,"%i\n", proizvodi[i].brojMaterijala);
        for(int j=0;j<proizvodi[i].brojMaterijala;j++)
        {
            fprintf(fp,"%s;", proizvodi[i].materijali[j].ime);
        }
        fprintf(fp,"\n");
        i++;
    }
    fclose(fp);
}
void citanje()
{
    fp=fopen("Proizvodi.txt", "r");
    fscanf(fp, "%i%*c", &brojProizvoda);
    if(brojProizvoda==0)
    {
        fclose(fp);
        return;
    }
    proizvodi=malloc(sizeof(proizvod)*brojProizvoda);
    for(int i=0;i<brojProizvoda;i++)
    {
        fscanf(fp, "%[^;]%*c", proizvodi[i].ime);
        fscanf(fp, "%i%*c", &proizvodi[i].barkod);
        fscanf(fp, "%f%*c", &proizvodi[i].cena);
        fscanf(fp, "%i%*c", &proizvodi[i].dan);
        fscanf(fp, "%i%*c", &proizvodi[i].mesec);
        fscanf(fp, "%i%*c", &proizvodi[i].godina);
        fscanf(fp, "%i%*c", &proizvodi[i].brojMaterijala);
        proizvodi[i].materijali=malloc(sizeof(materijal)*proizvodi[i].brojMaterijala);
        for(int j=0;j<proizvodi[i].brojMaterijala;j++)
        {
            fscanf(fp, "%[^;]%*c", proizvodi[i].materijali[j].ime);
        }
        fscanf(fp, "%*c");
    }
}
int main()
{
        citanje();
    int izbor;
    do
    {
        printf("1. Dodavanje novog proizvoda\n");
        printf("2. Prikaz svih\n");
        printf("3. Pretraga proizvoda\n");
        printf("4. Izmena proizvoda\n");
        printf("5. Brisanje proizvoda\n");
        printf("6. Cenovnik\n");
        printf("7. Exit\n");
        printf(">>>");
        fflush(stdin);
        scanf("%i", &izbor);
        if(izbor>7||izbor<1)
            printf("\nOperacija ne postoji!!!\n\n");
        switch(izbor)
        {
        case 1:
            dodavanjeNovogProizvoda();
            break;
        case 2:
            PrikazSvih();
            break;
        case 3:
            printf("Nacin pretrage(1-ime 2-barkod): ");
            do
            {
                scanf("%i", &izbor);
            }while(izbor!=1&&izbor!=2);
            if(izbor==1)
            {
                printf("Unesite ime: ");
                char ime[20];
                scanf("%s", ime);
                izbor=PretragaIme(ime);
            }
            else
            {
                printf("Unesite barkod: ");
                int barkod;
                scanf("%i", &barkod);
                izbor=PretragaBarKod(barkod);
            }
            if(izbor==-1)
            {
                printf("proizvod nije pronadjen\n");
                break;
            }
            printf("Naziv proizvoda: %s\n", proizvodi[izbor].ime);
            printf("Barkod proizvoda: %d\n", proizvodi[izbor].barkod);
            printf("Cena proizvoda: %.2f\n", proizvodi[izbor].cena);
            printf("Broj materijala proizvoda: %d\n", proizvodi[izbor].brojMaterijala);
            for(int j=0; j<proizvodi[izbor].brojMaterijala; j++)
            {
                printf("\n    Materijal %i: %s\n", j+1, proizvodi[izbor].materijali[j].ime);
            }
            printf("Datum: %i/%i/%i\n\n", proizvodi[izbor].dan, proizvodi[izbor].mesec, proizvodi[izbor].godina);
            break;
        case 4:
            printf("Nacin pretrage(1-ime 2-barkod): ");
            do
            {
                scanf("%i", &izbor);
            }while(izbor!=1&&izbor!=2);
            if(izbor==1)
            {
                printf("Unesite ime: ");
                char ime[20];
                scanf("%s", ime);
                izbor=PretragaIme(ime);
            }
            else
            {
                printf("Unesite barkod: ");
                int barkod;
                scanf("%i", &barkod);
                izbor=PretragaBarKod(barkod);
            }
            if(izbor==-1)
            {
                printf("Proizvod nije pronadjen\n");
                break;
            }
            IzmenaProizvoda(izbor);
            break;
        case 5:
            printf("Nacin brisanja(1-ime 2-barkod): ");
            do
            {
                scanf("%i", &izbor);
            }while(izbor!=1&&izbor!=2);
            if(izbor==1)
            {
                printf("Unesite ime: ");
                char ime[20];
                scanf("%s", ime);
                izbor=PretragaIme(ime);
            }
            else
            {
                printf("Unesite barkod: ");
                int barkod;
                scanf("%i", &barkod);
                izbor=PretragaBarKod(barkod);
            }
            if(izbor==-1)
            {
                printf("Proizvod nije pronadjen\n");
                break;
            }
            BrisanjeProizvoda(izbor);
            printf("Proizvod uspesno obrisan\n");
            break;
        case 6:
            Cenovnik();
            break;
        }
    }
    while(izbor!=7);
    pisanje();
    return 0;
}
