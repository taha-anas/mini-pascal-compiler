#ifndef COMPILA_ERRORS_H
#define COMPILA_ERRORS_H

typedef enum {
    // Lexical errors
    ERR_CAR_INC,
    ERR_FICH_VID,
    ERR_IDF_LONG,
    ERR_IDF_INVAL,
    ERR_SYM_INCONNU,
    ERR_CONST_INVAL,

    // Syntactic errors
    ERR_BEGIN_MANQ,
    ERR_END_MANQ,
    ERR_POINT_VIRG_MANQ,
    ERR_POINT_MANQ,
    ERR_EG_MANQ,
    ERR_PAR_OUV_MANQ,
    ERR_PAR_FER_MANQ,
    ERR_PLUS_MANQ,
    ERR_MOINS_MANQ,
    ERR_MULT_MANQ,
    ERR_DIV_MANQ,
    ERR_DDOT_MANQ,
    ERR_AFF_MANQ,
    ERR_MOT_CLE_INATT,
    ERR_NUM_MANQ,
    ERR_STRUCT_INCORRECTE,
    ERR_FIN_FICHIER_INATT,
    ERR_OPERATOR_INCORRECT,

    // Semantic errors
    ERR_TYPE_INCOMPATIBLE,
    ERR_VAR_INDEF,
    ERR_NOMBRE_PARAM_INVAL,
    ERR_ID_USED,
    ERR_CONST_CANT_CHANGE,
    ERR_PROGRAM_ID,

    // Code generation errors
    ERR_PC_FULL,
    ERR_INST_PCODE,
} CodeErreur;

typedef struct {
    CodeErreur code;
    char message[40];
} ErreurType;

extern const char *MES_ERR[];
extern const char *CODE_ERR_strings[];

void printErreur(CodeErreur codeERR);

#endif // COMPILA_ERRORS_H