
 /***************************************************************************** 
 * FILE:         Buildver.h 
 * DESCRIPTION:  Feature customization file.  
 * CREATED BY:   Buildver.h was generated by BuildVerGen for project: max
 ****************************************************************************** 
 * Copyright (c) 2009 Autodesk, All Rights Reserved. 
 ******************************************************************************/ 

#ifndef BUILDVER_H
#define BUILDVER_H

//*****************************************************************************
// BUILD WARNINGS
//*****************************************************************************
#include "BuildWarnings.h"


#undef  ALPHABETA


#ifdef _WIN64
#undef  NO_SOFTLOCK
#undef  NO_OBJECT_DBX
#endif // #ifdef _WIN64



// These includes rely on symbols defined in this file. Don't move them at the
// top of the file. No need to include them in any other file.
#include "ProductFileSupport.h"
#include "ProductDefaults.h"
#endif // BUILDVER_H

