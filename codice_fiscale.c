#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define file_name "comuni.txt"
#define LEN 16
#define lel 100
#define D 4

// variables
char CF[LEN];
FILE *fp;
char sur[lel], name[lel], day[D], year[D], sex, com[lel];
int month;
char months[] = "ABCDEHLMPRST";

// prototypes
void cognome();
void nome();
void nascita();
int comune();
int codice_verifica();
int codice_inverso();
void print_cf();

// main
void main()
{
    // program
    int scelta;
    printf("Calcola: \n");
    printf("1. CODICE FISCALE\n");
    printf("2. CODICE FISCALE INVERSO\n");
    scanf("%d", &scelta);
    if(scelta == 1)
    {
        printf("Inserisci il cognome: ");
        scanf("%s", sur);
        cognome();
        printf("Inserisci il nome: ");
        scanf("%s", name);
        nome();
        printf("Inserisci il giorno di nascita: ");
        scanf("%s", day);
        printf("Inserisci il mese di nascita: ");
        scanf("%d", &month);
        printf("Inserisci l'anno di nascita: ");
        scanf("%s", year);
        nascita();
        printf("Inserisci il comune di nascita: ");
        scanf("%s", com);
        int com_len = strlen(com);
        for(int i = 0; i < com_len; i++)
            com[i] = toupper(com[i]);
        comune();
        codice_verifica();
        print_cf();
    }
    else
        codice_inverso();
}

// functions
// CALCOLO COGNOME
void cognome()
{
    // variables
    int stlen, cont = 0, contv = 0;
    char vowels[lel];
    char cons[lel];

    // function
    stlen = strlen(sur);

    for(int i = 0; i < stlen; i++)
        sur[i] = toupper(sur[i]);

    for(int i = 0; i < stlen; i++)
    {
        switch(sur[i])
        {
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                vowels[contv] = sur[i];
                contv++;
                break;
            default:
                cons[cont] = sur[i];
                cont++;
        }
    }

    if(cont >= 3)
    {
        for(int i = 0; i < 3; i++)
            CF[i] = cons[i];
    }
    
    if(cont == 2)
    {
        for(int i = 0; i < 2; i++)
            CF[i] = cons[i];
        CF[2] = vowels[0];
    }

    if(cont == 1)
    {
        CF[0] = cons[0];
        for(int i = 1; i < 3; i++)
            CF[i] = vowels[i];
    }

    if(cont == 0)
    {
        for(int i = 0; i < 2; i++)
            CF[i] = vowels[i];
        CF[3] == 'x';
    }
}

// CALCOLO NOME
void nome()
{   // variables
    char cons[lel], vowels[lel];
    int stlen, cont = 0, contv = 0;

    // function
    stlen = strlen(name);
    for(int i = 0; i < stlen; i++)
        name[i] = toupper(name[i]);

    for(int i = 0; i < stlen; i++)
    {
        switch(name[i])
        {
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                vowels[contv] = name[i];
                contv++;
                break;
            default:
                cons[cont] = name[i];
                cont++;
        }
    }

    if(cont >= 4)
    {
        CF[3] = cons[0];
        CF[4] = cons[2];
        CF[5] = cons[3];
    }

    if(cont == 3)
    {
        CF[3] = cons[0];
        CF[4] = cons[1];
        CF[5] = cons[2]; 
    }

    if(cont == 2)
    {
        CF[3] = cons[0];
        CF[4] = cons[1];
        CF[5] = vowels[0];
    }

    if(cont == 1 && contv >= 2)
    {
        CF[3] = cons[0];
        CF[4] = vowels[0];
        CF[5] = vowels[1];
    }

    if(cont == 1 && contv == 1)
    {
        CF[3] = cons[0];
        CF[4] = vowels[0];
        CF[5] = 'X';
    }

    if(cont == 0 && contv == 2)
    {
        CF[3] = vowels[0];
        CF[4] = vowels[1];
        CF[5] = 'X';
    }
}

// CALCOLO DATA DI NASCITA
void nascita()
{
    // variables
    int gio = atoi(day);

    // program
    printf("Inserisci il sesso: ");
    scanf(" %c", &sex);
    CF[6] = year[2];
    CF[7] = year[3];

    CF[8] = months[month - 1];

    if(toupper(sex) == 'F')
        day[0] += 4; //sono passato di qui (ps. sono BATMAN)
    if(gio < 10)
    {
        CF[9] = '0';
        CF[10] = day[0];
    }
    CF[9] = day[0];
    CF[10] = day[1];
}

// CALCOLO COMUNE
int comune()
{
    fp = fopen(file_name, "r");
    char codice_catastale[D];
    char comune[lel];

    if(fopen(file_name, "r") == NULL)
    {
        printf("Errore ad aprire il file dei comuni.\n");
        return EXIT_FAILURE;
    }

    while(fscanf(fp, "%s %s", codice_catastale, comune) != EOF)
    {
        if(strcmp(comune, com) == 0)
            break;
    }
    CF[11] = codice_catastale[0];
    CF[12] = codice_catastale[1];
    CF[13] = codice_catastale[2];
    CF[14] = codice_catastale[3];
    fclose(fp);
}

// CALCOLO CODICE DI VERIFICA
int codice_verifica()
{
    char even_numbers[] = "0123456789lllllllllllllll";
    char odd_numbers[] = "10lll2l3l4lll5l6l7l8l9lll";
    char even_letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char odd_letters[] = "BAKPLCQDREVOSFTGUHMINJWZYX";
    int sum = 0;

    for(int i = 0; i < 16; i++)
    {
        if(i % 2 != 0)
        {
            for(int j = 0; j < strlen(even_letters); j++)
            {
                if(toupper(CF[i]) == even_letters[j] || toupper(CF[i]) == even_numbers[j])
                {
                    sum += j;
                    break;
                }
            }
        }
        else if(i % 2 == 0)
        {
            for(int j = 0; j < strlen(even_letters); j++)
            {
                if(toupper(CF[i]) == odd_letters[j] || toupper(CF[i]) == odd_numbers[j])
                {
                    sum += j;
                    break;
                }
            }
        }
    }
    sum %= 26;
    CF[15] = even_letters[sum + 1];
}

// STAMPA CODICE FISCALE
void print_cf()
{
    // program
    for(int i = 0; i < 16; i++)
        printf("%c", CF[i]);
    printf("\n");
}

// CALCOLO CODICE FISCALE INVERSO
int codice_inverso()
{
    printf("Inserisci il tuo codice fiscale: ");
    scanf("%s", CF);

    // CALCOLO COGNOME
    printf("Il tuo cognome e': ");
    for(int i = 0; i < 3; i++)
        printf("%c", CF[i]);

    // CALCOLO NOME
    printf("\n");
    printf("Il tuo nome e': ");
    for(int i = 3; i < 6; i++)
        printf("%c", CF[i]);
    printf("\n");

    // CALCOLO DATA DI NASCITA
    if(CF[9] <= 51)
    {
        printf("Il tuo sesso e': maschio\n");
        printf("La tua data di nascita e': ");
        for(int i = 9; i <= 10; i++)
            printf("%c", CF[i]);
    }
    else
    {
        printf("Il tuo sesso e': femmina\n");
        printf("La tua data di nascita e': ");
        CF[9] -= 4;
        printf("%c", CF[9]);
        printf("%c", CF[10]);
    }
    printf("/");

    for(int i = 0; i < strlen(months); i++)
    {
        if(CF[8] == months[i])
        {
            if(i < 10)
                printf("0");
            printf("%d", i + 1);
        }
    }
    printf("/");

    if(CF[6] > 50)
        printf("19");
    else
        printf("20");
    for(int i = 6; i <= 7; i++)
        printf("%c", CF[i]);

    printf("\n");

    // calcolo comune
    fp = fopen(file_name, "r");
    char codice_catastale[5], comune[lel];
    char com[5] = {CF[11], CF[12], CF[13], CF[14], '\0'};
    int c = 0;

    /*for(int i = 0; i < 5; i++)
        printf("%c", com[i]);*/

    if(fopen(file_name, "r") == NULL)
    {
        printf("Errore ad aprire il file dei comuni.\n");
        return EXIT_FAILURE;
    }
    
    printf("Il tuo comune di nascita e': ");

    while(fscanf(fp, "%s %s", codice_catastale, comune) != EOF)
    {
        if(strncmp(com, codice_catastale, 4) == 0)
            break;
    }

    printf("%s\n", comune);
    fclose(fp);
    return 0;
}