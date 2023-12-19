# Microsoft Developer Studio Project File - Name="model_1949" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=model_1949 - Win32 Debug
!MESSAGE Dies ist kein gueltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und fuehren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "model_1949.mak".
!MESSAGE 
!MESSAGE Sie koennen beim Ausfuehren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "model_1949.mak" CFG="model_1949 - Win32 Debug"
!MESSAGE 
!MESSAGE Fuer die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "model_1949 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "model_1949 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "model_1949 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_USRDLL" /D "_MBCS" /DTABLE_SHARE /DHAVE_ZLIB=1 /DHAVE_STDARG_H=1 /DHAVE_MEMCPY /D "_CRT_SECURE_NO_WARNINGS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\;.\sundials\include;c:\users\public\documents\simulationx 4.2\modelica\modelica 3.2.2\;"  /D "WIN32" /D "NDEBUG" /D "_USRDLL" /D "_MBCS" /DTABLE_SHARE /DHAVE_ZLIB=1 /DHAVE_STDARG_H=1 /DHAVE_MEMCPY /D "_CRT_SECURE_NO_WARNINGS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32  /dll /machine:IX86 

!ELSEIF  "$(CFG)" == "model_1949 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_USRDLL" /D "_MBCS" /DTABLE_SHARE /DHAVE_ZLIB=1 /DHAVE_STDARG_H=1 /DHAVE_MEMCPY /D "_CRT_SECURE_NO_WARNINGS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".\;.\sundials\include;c:\users\public\documents\simulationx 4.2\modelica\modelica 3.2.2\;"  /D "WIN32" /D "_DEBUG" /D "_USRDLL" /D "_MBCS" /DTABLE_SHARE /DHAVE_ZLIB=1 /DHAVE_STDARG_H=1 /DHAVE_MEMCPY /D "_CRT_SECURE_NO_WARNINGS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32  /dll /debug /machine:IX86 

!ENDIF 

# Begin Target

# Name "model_1949 - Win32 Release"
# Name "model_1949 - Win32 Debug"
# Begin Group "Source-Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ITI_ArrayFunctions.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_FunctionsAlloc.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_Functions.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_LinSolver.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_big_uint.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_Memory.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ModelicaUtilities.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\snprintf.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_AllocClockInference.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_ClockInference.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_ClockEval.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_PartitionEval.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_PartitionInit.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_PartitionSolver.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_PartitionInterface.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ModelicaStandardTables.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ModelicaStandardTablesUsertab.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\zlib.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\c_aes.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ModelicaIO.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ModelicaMatIO.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ModelicaStrings.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_SolverHelpers.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_NonLinSolver.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_Cvode_FMI_CS.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_fmiCSFunctions.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_Tracing.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_Cvode_base.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_Cvode_model_if.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_Cvode_jac.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_Cvode_helpers.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ITI_Cvode_sparse.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ma_lequspar.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ma_matspars.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\ma_serialization.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\sundials\src\cvode\cvode.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\sundials\src\cvode\cvode_dense.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\sundials\src\cvode\cvode_io.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\sundials\src\cvode\cvode_serialization.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\sundials\src\cvode\cvode_tracing.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\sundials\src\nvec_ser\nvector_serial.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\sundials\src\sundials\sundials_dense.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\sundials\src\sundials\sundials_math.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\sundials\src\sundials\sundials_nvector.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\sundials\src\sundials\sundials_serialization.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\sundials\src\sundials\sundials_smalldense.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_init.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_functions.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_decl.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_initjac.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_jac.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_init.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_decl.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_functions.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_initjac.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_jac.c
# SUBTRACT CPP /YX
# End Source File

# End Group
# Begin Group "Header-Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ITI_ArrayFunctions.h
# End Source File
# Begin Source File

SOURCE=.\ITI_FunctionsAlloc.h
# End Source File
# Begin Source File

SOURCE=.\ITI_Functions.h
# End Source File
# Begin Source File

SOURCE=.\ITI_LinSolver.h
# End Source File
# Begin Source File

SOURCE=.\ITI_big_uint.h
# End Source File
# Begin Source File

SOURCE=.\ITI_Memory.h
# End Source File
# Begin Source File

SOURCE=.\ITI_Types.h
# End Source File
# Begin Source File

SOURCE=.\ModelicaUtilities.h
# End Source File
# Begin Source File

SOURCE=.\ITI_BlockDeclarations.h
# End Source File
# Begin Source File

SOURCE=.\ITI_DeclarationsBase.h
# End Source File
# Begin Source File

SOURCE=.\ITI_AllocClockInference.h
# End Source File
# Begin Source File

SOURCE=.\ITI_ClockInference.h
# End Source File
# Begin Source File

SOURCE=.\ITI_ClockEval.h
# End Source File
# Begin Source File

SOURCE=.\ITI_PartitionEval.h
# End Source File
# Begin Source File

SOURCE=.\ITI_PartitionInit.h
# End Source File
# Begin Source File

SOURCE=.\ITI_PartitionSolver.h
# End Source File
# Begin Source File

SOURCE=.\ITI_PartitionInterface.h
# End Source File
# Begin Source File

SOURCE=.\gconstructor.h
# End Source File
# Begin Source File

SOURCE=.\uthash.h
# End Source File
# Begin Source File

SOURCE=.\ModelicaStandardTables.h
# End Source File
# Begin Source File

SOURCE=.\zlib.h
# End Source File
# Begin Source File

SOURCE=.\c_aes.h
# End Source File
# Begin Source File

SOURCE=.\ModelicaIO.h
# End Source File
# Begin Source File

SOURCE=.\ModelicaMatIO.h
# End Source File
# Begin Source File

SOURCE=.\ModelicaStrings.h
# End Source File
# Begin Source File

SOURCE=.\ITI_SolverHelpers.h
# End Source File
# Begin Source File

SOURCE=.\ITI_NonLinSolver.h
# End Source File
# Begin Source File

SOURCE=.\fmiPlatformTypes.h
# End Source File
# Begin Source File

SOURCE=.\fmiFunctions.h
# End Source File
# Begin Source File

SOURCE=.\ITI_crt.h
# End Source File
# Begin Source File

SOURCE=.\ITI_Cvode_FMI_CS.h
# End Source File
# Begin Source File

SOURCE=.\ITI_fmiCSTypes.h
# End Source File
# Begin Source File

SOURCE=.\ITI_Tracing.h
# End Source File
# Begin Source File

SOURCE=.\ITI_Declarations.h
# End Source File
# Begin Source File

SOURCE=.\ITI_Cvode_base.h
# End Source File
# Begin Source File

SOURCE=.\ITI_Cvode_model_if.h
# End Source File
# Begin Source File

SOURCE=.\ITI_Cvode_jac.h
# End Source File
# Begin Source File

SOURCE=.\ITI_ModelInclude.h
# End Source File
# Begin Source File

SOURCE=.\ITI_Cvode_helpers.h
# End Source File
# Begin Source File

SOURCE=.\ITI_Cvode_sparse.h
# End Source File
# Begin Source File

SOURCE=.\ma_serialization.h
# End Source File
# Begin Source File

SOURCE=.\ma_sparse.h
# End Source File
# Begin Source File

SOURCE=.\ma_typedef.h
# End Source File
# Begin Source File

SOURCE=.\sundials\include\cvode\cvode.h
# End Source File
# Begin Source File

SOURCE=.\sundials\include\cvode\cvode_dense.h
# End Source File
# Begin Source File

SOURCE=.\sundials\include\cvode\cvode_serialization.h
# End Source File
# Begin Source File

SOURCE=.\sundials\include\cvode\cvode_tracing.h
# End Source File
# Begin Source File

SOURCE=.\sundials\include\nvector\nvector_serial.h
# End Source File
# Begin Source File

SOURCE=.\sundials\include\sundials\sundials_config.h
# End Source File
# Begin Source File

SOURCE=.\sundials\include\sundials\sundials_dense.h
# End Source File
# Begin Source File

SOURCE=.\sundials\include\sundials\sundials_math.h
# End Source File
# Begin Source File

SOURCE=.\sundials\include\sundials\sundials_nvector.h
# End Source File
# Begin Source File

SOURCE=.\sundials\include\sundials\sundials_serialization.h
# End Source File
# Begin Source File

SOURCE=.\sundials\include\sundials\sundials_smalldense.h
# End Source File
# Begin Source File

SOURCE=.\sundials\include\sundials\sundials_types.h
# End Source File
# Begin Source File

SOURCE=.\sundials\src\cvode\cvode_dense_impl.h
# End Source File
# Begin Source File

SOURCE=.\sundials\src\cvode\cvode_impl.h
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949.h
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_functions.h
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_CurveData.h
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949.h
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_functions.h
# End Source File
# Begin Source File

SOURCE=.\cg_model_1949_CurveData.h
# End Source File

# End Group
# End Target
# End Project
