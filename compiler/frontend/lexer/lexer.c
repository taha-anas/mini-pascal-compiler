#include "lexer.h"

void lireCar()
{
    carCour = fgetc(fichier);
    if(carCour == '\n') numLigne++;
}

void symSuiv()
{
    while (carCour == ' ' || carCour == '\n' || carCour == '\t')
    {
        lireCar();
    }
    if (isalpha(carCour))
    {
        lireMot();
    }
    else if (isdigit(carCour))
    {
        lireNombre();
    }
    else
    {
        switch (carCour)
        {
            case ';':
                symCour.code = PV_TOKEN;
                strcpy(symCour.nom , ";");
                lireCar();
                break;

            case '+':
                symCour.code = PLUS_TOKEN;
                strcpy(symCour.nom , "+");
                lireCar();
                break;

            case '-':
                symCour.code = MOINS_TOKEN;
                strcpy(symCour.nom , "-");
                lireCar();
                break;

            case '*':
                symCour.code = MULT_TOKEN;
                strcpy(symCour.nom , "*");
                lireCar();
                break;

            case '/':
                symCour.code = DIV_TOKEN;
                strcpy(symCour.nom , "/");
                lireCar();
                break;

            case ',':
                symCour.code = VIR_TOKEN;
                strcpy(symCour.nom , ",");
                lireCar();
                break;

            case ':':
                lireCar();
                switch (carCour) {
                    case '=':
                        symCour.code = AFF_TOKEN;
                        strcpy(symCour.nom, ":=");
                        lireCar();
                        break;
                    case ':':
                        symCour.code = DDOT_TOKEN;
                        strcpy(symCour.nom, "::");
                        lireCar();
                        break;
                    default:
                        break;
                }
                break;
                
            case '<':
                lireCar();
                if (carCour == '=')
                {
                    symCour.code = INFEG_TOKEN;
                    strcpy(symCour.nom, "<=");
                    lireCar();
                }
                else if (carCour == '>')
                {
                    symCour.code = DIFF_TOKEN;
                    strcpy(symCour.nom, "<>");
                    lireCar();
                }
                else
                {
                    symCour.code = INF_TOKEN;
                    strcpy(symCour.nom, "<");
                }
                break;

            case '>':
                lireCar();
                if (carCour == '=')
                {
                    symCour.code = SUPEG_TOKEN;
                    strcpy(symCour.nom, ">=");
                    lireCar();
                }
                else
                {
                    symCour.code = SUP_TOKEN;
                    strcpy(symCour.nom, ">");
                }
                break;

            case '(':
                symCour.code = PO_TOKEN;
                strcpy(symCour.nom, "(");
                lireCar();
                break;
                
            case '=':
                symCour.code = EG_TOKEN;
                strcpy(symCour.nom, "=");
                lireCar();
                break;

            case ')':
                symCour.code = PF_TOKEN;
                strcpy(symCour.nom, ")");
                lireCar();
                break;

            case '.':
                symCour.code = PT_TOKEN;
                strcpy(symCour.nom, ".");
                lireCar();
                break;

            case EOF:
                symCour.code = EOF_TOKEN;
                strcpy(symCour.nom, "EOF");
                break;

            default:
                symCour.code = ERREUR_TOKEN;
                strcpy(symCour.nom, "error");
                lireCar();
                break;
        }
    }
}

void lireMot()
{
    char mot[20];
    int indice = 0;

    mot[indice++] = carCour;
    lireCar();

    while (isalpha(carCour) || isdigit(carCour))
    {
        mot[indice++] = carCour;
        lireCar();
    }

    mot[indice] = '\0';

    if (strcmp(mot, "program") == 0) {
        symCour.code = PROGRAM_TOKEN;
    } else if (strcmp(mot, "const") == 0) {
        symCour.code = CONST_TOKEN;
    } else if (strcmp(mot, "var") == 0) {
        symCour.code = VAR_TOKEN;
    } else if (strcmp(mot, "begin") == 0) {
        symCour.code = BEGIN_TOKEN;
    } else if (strcmp(mot, "end") == 0) {
        symCour.code = END_TOKEN;
    } else if (strcmp(mot, "if") == 0) {
        symCour.code = IF_TOKEN;
    } else if (strcmp(mot, "then") == 0) {
        symCour.code = THEN_TOKEN;
    } else if (strcmp(mot, "while") == 0) {
        symCour.code = WHILE_TOKEN;
    } else if (strcmp(mot, "do") == 0) {
        symCour.code = DO_TOKEN;
    } else if (strcmp(mot, "read") == 0) {
        symCour.code = READ_TOKEN;
    } else if (strcmp(mot, "write") == 0) {
        symCour.code = WRITE_TOKEN;
    } else if (strcmp(mot, "else") == 0) {
        symCour.code = ELSE_TOKEN;
    } else if (strcmp(mot, "repeat") == 0) {
        symCour.code = REPEAT_TOKEN;
    } else if (strcmp(mot, "until") == 0) {
        symCour.code = UNTIL_TOKEN;
    } else if (strcmp(mot, "for") == 0) {
        symCour.code = FOR_TOKEN;
    } else if (strcmp(mot, "case") == 0) {
        symCour.code = CASE_TOKEN;
    } else if (strcmp(mot, "of") == 0) {
        symCour.code = OF_TOKEN;
    } else {
        symCour.code = ID_TOKEN;
    }

    strcpy(symCour.nom, mot);
}

void lireNombre(){
    char nombre[11];
    int indice = 0;

    nombre[indice++] = carCour;
    lireCar();

    while (isdigit(carCour)){
        nombre[indice++] = carCour;
        lireCar();
    }

    nombre[indice] = '\0';

    symCour.code = NUM_TOKEN;
    symCour.valeur = atoi(nombre);
    strcpy(symCour.nom, nombre);
}