#include "lexical.h"

/*
 * we have already declare global variables such as:
 * extern FILE * file;
 * extern char current_char;
 * extern Symbol current_symbol;
*/
FILE * file;
char current_char;
Symbol current_symbol;


void read_char() {
    current_char = fgetc(file);
}

void read_string() {
    char string[20];
    int index = 0;

    // Lecture du premier caractère (lettre)
    string[index++] = current_char;
    read_char();

    // Lecture des caractères suivants (lettres ou chiffres)
    while (isalpha(current_char) || isdigit(current_char)) {
        string[index++] = current_char;
        read_char();
    }

    // Ajout du caractère de fin de chaîne
    string[index] = '\0';

    // Vérifier si le string est un string-clé
    if (strcmp(string, "program") == 0) {
        current_symbol.token = PROGRAM_TOKEN;
    } else if (strcmp(string, "const") == 0) {
        current_symbol.token = CONST_TOKEN;
    } else if (strcmp(string, "var") == 0) {
        current_symbol.token = VAR_TOKEN;
    } else if (strcmp(string, "begin") == 0) {
        current_symbol.token = BEGIN_TOKEN;
    } else if (strcmp(string, "end") == 0) {
        current_symbol.token = END_TOKEN;
    } else if (strcmp(string, "if") == 0) {
        current_symbol.token = IF_TOKEN;
    } else if (strcmp(string, "then") == 0) {
        current_symbol.token = THEN_TOKEN;
    } else if (strcmp(string, "while") == 0) {
        current_symbol.token = WHILE_TOKEN;
    } else if (strcmp(string, "do") == 0) {
        current_symbol.token = DO_TOKEN;
    } else if (strcmp(string, "read") == 0) {
        current_symbol.token = READ_TOKEN;
    } else if (strcmp(string, "write") == 0) {
        current_symbol.token = WRITE_TOKEN;
    } else {
        // Si ce n'est pas un string-clé, c'est un identifiant
        current_symbol.token = ID_TOKEN;
    }

    // Stockage du string dans le jeton
    strcpy(current_symbol.name, string);
}


void read_number() {
    char number[11];
    int index = 0;

    // Lecture du premier chiffre
    number[index++] = current_char;
    read_char();

    // Lecture des chiffres suivants
    while (isdigit(current_char)) {
        number[index++] = current_char;
        read_char();
    }

    // Ajout du caractère de fin de chaîne
    number[index] = '\0';

    // Stockage du number dans le jeton
    current_symbol.token = NUM_TOKEN;
    strcpy(current_symbol.name, number);
}

void next_symbol() {
    while (current_char == ' ' || current_char == '\n' || current_char == '\t') {
        read_char();
    }
    if (isalpha(current_char)) {
        read_string();
    } else if (isdigit(current_char)) {
        read_number();
    } else {
        switch (current_char) {
            case ';':
                current_symbol.token = PV_TOKEN;
                read_char();
                break;

            case '.':
                current_symbol.token = PT_TOKEN;
                read_char();
                break;

            case '+':
                current_symbol.token = PLUS_TOKEN;
                read_char();
                break;

            case '-':
                current_symbol.token = MOINS_TOKEN;
                read_char();
                break;

            case '*':
                current_symbol.token = MULT_TOKEN;
                read_char();
                break;

            case '/':
                current_symbol.token = DIV_TOKEN;
                read_char();
                break;

            case ',':
                current_symbol.token = VIR_TOKEN;
                read_char();
                break;

            case ':':
                read_char();
                if (current_char == '=') {
                    current_symbol.token = AFF_TOKEN;
                    read_char();
                } else {
                    current_symbol.token = ERREUR_TOKEN;
                }
                break;

            case '<':
                read_char();
                if (current_char == '=') {
                    current_symbol.token = INFEG_TOKEN;
                    read_char();
                } else if (current_char == '>') {
                    current_symbol.token = DIFF_TOKEN;
                    read_char();
                } else {
                    current_symbol.token = INF_TOKEN;
                }
                break;

            case '>':
                read_char();
                if (current_char == '=') {
                    current_symbol.token = SUPEG_TOKEN;
                    read_char();
                } else {
                    current_symbol.token = SUP_TOKEN;
                }
                break;

            case '(':
                current_symbol.token = PO_TOKEN;
                read_char();
                break;
            case '=':
                current_symbol.token = EG_TOKEN;
                read_char();
                break;

            case ')':
                current_symbol.token = PF_TOKEN;
                read_char();
                break;

            case EOF:
                current_symbol.token = FIN_TOKEN;
                break;

            default:
                current_symbol.token = ERREUR_TOKEN;
                read_char();
        }
    }

}


char* codeToString(Token code) {
    switch (code) {
        case EG_TOKEN: return "EG_TOKEN";
        case ID_TOKEN: return "ID_TOKEN";
        case PROGRAM_TOKEN: return "PROGRAM_TOKEN";
        case CONST_TOKEN: return "CONST_TOKEN";
        case VAR_TOKEN: return "VAR_TOKEN";
        case BEGIN_TOKEN: return "BEGIN_TOKEN";
        case END_TOKEN: return "END_TOKEN";
        case IF_TOKEN: return "IF_TOKEN";
        case THEN_TOKEN: return "THEN_TOKEN";
        case WHILE_TOKEN: return "WHILE_TOKEN";
        case DO_TOKEN: return "DO_TOKEN";
        case READ_TOKEN: return "READ_TOKEN";
        case WRITE_TOKEN: return "WRITE_TOKEN";
        case PV_TOKEN: return "PV_TOKEN";
        case PT_TOKEN: return "PT_TOKEN";
        case PLUS_TOKEN: return "PLUS_TOKEN";
        case MOINS_TOKEN: return "MOINS_TOKEN";
        case MULT_TOKEN: return "MULT_TOKEN";
        case DIV_TOKEN: return "DIV_TOKEN";
        case VIR_TOKEN: return "VIR_TOKEN";
        case AFF_TOKEN: return "AFF_TOKEN";
        case INF_TOKEN: return "INF_TOKEN";
        case INFEG_TOKEN: return "INFEG_TOKEN";
        case SUP_TOKEN: return "SUP_TOKEN";
        case SUPEG_TOKEN: return "SUPEG_TOKEN";
        case DIFF_TOKEN: return "DIFF_TOKEN";
        case PO_TOKEN: return "PO_TOKEN";
        case PF_TOKEN: return "PF_TOKEN";
        case FIN_TOKEN: return "FIN_TOKEN";
        case NUM_TOKEN: return "NUM_TOKEN";
        case ERREUR_TOKEN: return "ERREUR_TOKEN";
        case EOF_TOKEN: return "EOF_TOKEN";
        default: return "UNKNOWN_TOKEN";
    }
}

//
//int main() {
//
//    file = fopen("./test", "r");
//    if (file == NULL) {
//        perror("Erreur lors de l'ouverture du file");
//        return 1;
//    }
//    printf("Resulat:\n");
//    read_char();
//
//
//    do {
//        next_symbol();
//        //printf("%d\n", current_symbol.token);
//        printf("%s\n", codeToString(current_symbol.token));
//    } while (current_symbol.token != FIN_TOKEN && current_symbol.token != EOF_TOKEN);
//
//    fclose(file);
//
//    return 0;
//}