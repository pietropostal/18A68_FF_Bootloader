/*******************************************************************************
** Copyright (c) 2015 EMBITEL
**
** This software is the property of EMBITEL.
** It can not be used or duplicated without EMBITEL authorization.
**
** -----------------------------------------------------------------------------
** File Name    : compiler.h
** Module name  :  
** -----------------------------------------------------------------------------
** Description : Interrupt configuration
**
** -----------------------------------------------------------------------------
**
** Documentation reference :  
**
********************************************************************************
** R E V I S I O N  H I S T O R Y
********************************************************************************
** V01.00 20/07/2016
** - First release
** -----------------------------------------------------------------------------
** V01.01 : 28/03/2016
** - CR0038712: Change on micro-controller reference: from R5F1096C to R5F109BD
**
*******************************************************************************/
/* To avoid multi-inclusions */
#ifndef COMPILER_H
#define COMPILER_H
/*************************** Inclusion files **********************************/
//#include "Compiler_Cfg.h"
/**************** Declaration of global symbol and constants ******************/
#define AUTOMATIC auto
#define TYPEDEF typedef
#define STATIC static
#define EXTERN extern
#define BOOLEAN boolean
#define INLINE inline
#define CODETYPE
#define VARTYPE
#define CONSTTYPE
#define PTR2VARTYPE
#define PTRTYPE
/******************** Declaration of global macros ****************************/
#define FUNC(rettype, CODETYPE) rettype
#define VAR(vartype, VARTYPE) vartype
#define CONST(consttype, CONSTTYPE) const consttype
#define P2VAR(ptrtype, PTR2VARTYPE, PTRTYPE) ptrtype *
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const
#define P2FUNC(rettype, ptrclass, fctname) rettype (* fctname)
#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (*const fctname)

/********************* Declaration of global types ****************************/
//#define NULL ((void*) 0)

#endif /* COMPILER_H */
