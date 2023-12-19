RM = del

CFLAGS = /nologo /MP /Gm- /O2
COMPSIMFLAGS =
CPPFLAGS = $(COMPSIMFLAGS) /DTABLE_SHARE /DHAVE_ZLIB=1 /DHAVE_STDARG_H=1 /DHAVE_MEMCPY /DNDEBUG
USERINFO =
OPTION_UNDEFINED =
OMPFLAGS =
BIGOBJFLAGS =
OPTFLAGS =
PLATFORMDIR = win64
INC = \
	/I . \
	/I ".\sundials\include" \
	/I "c:\users\public\documents\simulationx 4.2\modelica\modelica 3.2.2"
LDFLAGS =
LDLIBS =

OBJECTS = \
	".\iti_arrayfunctions.obj" \
	".\iti_functionsalloc.obj" \
	".\iti_functions.obj" \
	".\iti_linsolver.obj" \
	".\iti_big_uint.obj" \
	".\iti_memory.obj" \
	".\modelicautilities.obj" \
	".\snprintf.obj" \
	".\iti_allocclockinference.obj" \
	".\iti_clockinference.obj" \
	".\iti_clockeval.obj" \
	".\iti_partitioneval.obj" \
	".\iti_partitioninit.obj" \
	".\iti_partitionsolver.obj" \
	".\iti_partitioninterface.obj" \
	".\modelicastandardtables.obj" \
	".\modelicastandardtablesusertab.obj" \
	".\zlib.obj" \
	".\c_aes.obj" \
	".\modelicaio.obj" \
	".\modelicamatio.obj" \
	".\modelicastrings.obj" \
	".\iti_solverhelpers.obj" \
	".\iti_nonlinsolver.obj" \
	".\iti_cvode_fmi_cs.obj" \
	".\iti_fmicsfunctions.obj" \
	".\iti_tracing.obj" \
	".\iti_cvode_base.obj" \
	".\iti_cvode_model_if.obj" \
	".\iti_cvode_jac.obj" \
	".\iti_cvode_helpers.obj" \
	".\iti_cvode_sparse.obj" \
	".\ma_lequspar.obj" \
	".\ma_matspars.obj" \
	".\ma_serialization.obj" \
	".\cvode.obj" \
	".\cvode_dense.obj" \
	".\cvode_io.obj" \
	".\cvode_serialization.obj" \
	".\cvode_tracing.obj" \
	".\nvector_serial.obj" \
	".\sundials_dense.obj" \
	".\sundials_math.obj" \
	".\sundials_nvector.obj" \
	".\sundials_serialization.obj" \
	".\sundials_smalldense.obj" \
	".\cg_model_1919.obj" \
	".\cg_model_1919_init.obj" \
	".\cg_model_1919_functions.obj" \
	".\cg_model_1919_decl.obj" \
	".\cg_model_1919_initjac.obj" \
	".\cg_model_1919_jac.obj"

OBJECTS_WITH_PATH = \
	".\iti_arrayfunctions.obj" \
	".\iti_functionsalloc.obj" \
	".\iti_functions.obj" \
	".\iti_linsolver.obj" \
	".\iti_big_uint.obj" \
	".\iti_memory.obj" \
	".\modelicautilities.obj" \
	".\snprintf.obj" \
	".\iti_allocclockinference.obj" \
	".\iti_clockinference.obj" \
	".\iti_clockeval.obj" \
	".\iti_partitioneval.obj" \
	".\iti_partitioninit.obj" \
	".\iti_partitionsolver.obj" \
	".\iti_partitioninterface.obj" \
	".\modelicastandardtables.obj" \
	".\modelicastandardtablesusertab.obj" \
	".\zlib.obj" \
	".\c_aes.obj" \
	".\modelicaio.obj" \
	".\modelicamatio.obj" \
	".\modelicastrings.obj" \
	".\iti_solverhelpers.obj" \
	".\iti_nonlinsolver.obj" \
	".\iti_cvode_fmi_cs.obj" \
	".\iti_fmicsfunctions.obj" \
	".\iti_tracing.obj" \
	".\iti_cvode_base.obj" \
	".\iti_cvode_model_if.obj" \
	".\iti_cvode_jac.obj" \
	".\iti_cvode_helpers.obj" \
	".\iti_cvode_sparse.obj" \
	".\ma_lequspar.obj" \
	".\ma_matspars.obj" \
	".\ma_serialization.obj" \
	".\sundials\src\cvode\cvode.obj" \
	".\sundials\src\cvode\cvode_dense.obj" \
	".\sundials\src\cvode\cvode_io.obj" \
	".\sundials\src\cvode\cvode_serialization.obj" \
	".\sundials\src\cvode\cvode_tracing.obj" \
	".\sundials\src\nvec_ser\nvector_serial.obj" \
	".\sundials\src\sundials\sundials_dense.obj" \
	".\sundials\src\sundials\sundials_math.obj" \
	".\sundials\src\sundials\sundials_nvector.obj" \
	".\sundials\src\sundials\sundials_serialization.obj" \
	".\sundials\src\sundials\sundials_smalldense.obj" \
	".\cg_model_1919.obj" \
	".\cg_model_1919_init.obj" \
	".\cg_model_1919_functions.obj" \
	".\cg_model_1919_decl.obj" \
	".\cg_model_1919_initjac.obj" \
	".\cg_model_1919_jac.obj"



all : check_option model_1919.dll clean

check_option :
	@$(OPTION_UNDEFINED)

model_1919.dll : $(OBJECTS_WITH_PATH)
	link /dll /nologo /FORCE /INCREMENTAL:NO /OPT:NOREF $(LDFLAGS) $(LDLIBS) $(OMPLIBS) /OUT:"model_1919.dll" $(OBJECTS)

.c.obj::
	$(CC) $(CPPFLAGS) $(CFLAGS) $(BIGOBJFLAGS) $(OMPFLAGS) $(OPTFLAGS) $(INC) /c $<

clean:
	@echo "clean intermediate binaries"
	$(RM) ".\iti_arrayfunctions.obj" ".\iti_functionsalloc.obj" ".\iti_functions.obj" ".\iti_linsolver.obj" ".\iti_big_uint.obj" 
	$(RM) ".\iti_memory.obj" ".\modelicautilities.obj" ".\snprintf.obj" ".\iti_allocclockinference.obj" 
	$(RM) ".\iti_clockinference.obj" ".\iti_clockeval.obj" ".\iti_partitioneval.obj" ".\iti_partitioninit.obj" 
	$(RM) ".\iti_partitionsolver.obj" ".\iti_partitioninterface.obj" ".\modelicastandardtables.obj" 
	$(RM) ".\modelicastandardtablesusertab.obj" ".\zlib.obj" ".\c_aes.obj" ".\modelicaio.obj" ".\modelicamatio.obj" 
	$(RM) ".\modelicastrings.obj" ".\iti_solverhelpers.obj" ".\iti_nonlinsolver.obj" ".\iti_cvode_fmi_cs.obj" 
	$(RM) ".\iti_fmicsfunctions.obj" ".\iti_tracing.obj" ".\iti_cvode_base.obj" ".\iti_cvode_model_if.obj" ".\iti_cvode_jac.obj" 
	$(RM) ".\iti_cvode_helpers.obj" ".\iti_cvode_sparse.obj" ".\ma_lequspar.obj" ".\ma_matspars.obj" ".\ma_serialization.obj" 
	$(RM) ".\cvode.obj" ".\cvode_dense.obj" ".\cvode_io.obj" ".\cvode_serialization.obj" ".\cvode_tracing.obj" 
	$(RM) ".\nvector_serial.obj" ".\sundials_dense.obj" ".\sundials_math.obj" ".\sundials_nvector.obj" 
	$(RM) ".\sundials_serialization.obj" ".\sundials_smalldense.obj" ".\cg_model_1919.obj" ".\cg_model_1919_init.obj" 
	$(RM) ".\cg_model_1919_functions.obj" ".\cg_model_1919_decl.obj" ".\cg_model_1919_initjac.obj" ".\cg_model_1919_jac.obj" 

distclean : clean
	$(RM) model_1919.dll

info :
	@echo "This Nmakefile is generated from SimulationX for a Microsoft compiler on a Windows platform."

help :
	@echo "usage: nmake /f model_1919.mak all"
	@echo "nmake targets are:"
	@echo "- all - Build Executable and remove intermediate object files"
	@echo "- clean - Delete intermadiate object files"
	@echo "- distclean - Delete all compiled binary files"
	@echo "- info - Get information over target platform and compiler"
	@echo "- help - print this text for help"
