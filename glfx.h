#include <GL/glew.h>
#include <GL/freeglut.h>

#if defined(__MINGW32__) || defined(__CYGWIN__)
#   define GLFX_APIENTRY __cdecl
#elif (_MSC_VER >= 800)
#   define GLFX_APIENTRY __cdecl
#else
#   define GLFX_APIENTRY
#endif

#ifndef GLFX_STATIC
#   ifdef GLFX_BUILD
#       ifdef _MSC_VER
#           define GLFXAPI extern __declspec(dllexport)
#       else
#           define GLFXAPI __attribute__((__visibility__("default")))
#       endif
#   else
#       ifdef _MSC_VER
#           define GLFXAPI extern __declspec(dllimport)
#       else
#           define GLFXAPI
#       endif
#   endif
#else
#   define GLFXAPI extern
#endif

extern "C" {

	/**************************************************
	* glfxGenEffect
	* Return value: Effect id
	**************************************************/
	GLFXAPI int GLFX_APIENTRY glfxGenEffect();

	//! Set a directory that should be used to cache compiled shader files.
	GLFXAPI void GLFX_APIENTRY glfxSetCacheDirectory(const char* dir);

	/**************************************************
	* glfxCreateEffectFromFile
	* Input:
	*   effect				-- GLFX effect id
	*   file				-- File name
	*   shaderPathsUtf8		-- NULL-terminated list of paths for include files.
	*   macros				-- NULL-terminated list of macros to be predefined
	*   defs				-- list of corresponding macro definitions
	* Return value: Status
	**************************************************/
	GLFXAPI bool GLFX_APIENTRY glfxParseEffectFromFile(int effect, const char* file, const char** shaderPathsUtf8, const char** macros, const char** defs);

	/**************************************************
	* glfxCreateEffectFromMemory
	* Input:
	*   effect  -- GLFX effect id
	*   src    -- Source
	* Return value: Status
	**************************************************/
	GLFXAPI bool GLFX_APIENTRY glfxParseEffectFromMemory(int effect, const char* src, const char* filename = 0);

	/**************************************************
	* glfxCompileProgram
	* Input:
	*   effect  -- GLFX effect id
	*   program -- Program name
	* Return value: GL program id if success, 0 otherwise
	**************************************************/
	GLFXAPI GLuint GLFX_APIENTRY glfxCompileProgram(int effect, const char* technique, const char* pass);
	/*! This function gets a variant of the specified program, depending on the currently assigned writeable textures.
	This is required because GLSL needs an image (writeable texture) to be explicitly specified as 16-bit or 32-bit, so
	to avoid requiring developers to create 16- and 32-bit versions of shaders, we just create variants automatically.
	*/
	//GLFXAPI GLuint GLFX_APIENTRY glfxGetProgramVariant(int effect,GLuint main_program);

	GLFXAPI const char* GLFX_APIENTRY glfxGetCacheDirectory();
	GLFXAPI bool GLFX_APIENTRY glfxIsGlslangValidationEnabled();
	GLFXAPI void GLFX_APIENTRY glfxSetGlslangValidationEnabled(bool);
	GLFXAPI void glfxApply(int effect, GLuint pass);
	GLFXAPI void glfxReapply(int effect, GLuint pass);
	GLFXAPI void glfxUnapply(int effect);
	GLFXAPI int glfxGetEffectTextureNumber(int effect, const char* name);
	GLFXAPI int glfxGetEffectImageNumber(int effect, const char* name);
	// TODO: really we should just assume that the texture is of the type specified in the shader.
	GLFXAPI void glfxSetEffectTexture(int effect, int texture_number, GLuint tex, int dims, int depth, GLenum format, bool write, int write_mip, bool layered, int layer, bool cubemap);
	GLFXAPI void glfxSetEffectSamplerState(int effect, const char* name, GLuint sampler);

	//! Get the number of techniques in the effect
	GLFXAPI size_t GLFX_APIENTRY glfxGetTechniqueCount(int effect);
	GLFXAPI size_t GLFX_APIENTRY glfxGetTechniqueGroupCount(int effect);
	GLFXAPI const char* GLFX_APIENTRY glfxGetTechniqueGroupName(int effect, int g);
	GLFXAPI void GLFX_APIENTRY glfxUseTechniqueGroup(int effect, int g);

	//! Get the name of the technique at the given index.
	GLFXAPI const char* GLFX_APIENTRY glfxGetTechniqueName(int effect, int technum);
	//! Get the number of passes in the technique
	GLFXAPI size_t GLFX_APIENTRY glfxGetPassCount(int effect, const char* tech_name);
	//! Get the name of the pass at the given index.
	GLFXAPI const char* GLFX_APIENTRY glfxGetPassName(int effect, const char* tech_name, int pass_num);
	//! Compile the pass and return its GLSL program identifier.
	GLFXAPI GLuint GLFX_APIENTRY glfxCompilePass(int effect, const char* tech_name, const char* pass_name);
	GLFXAPI void GLFX_APIENTRY glfxApplyPassState(int effect, GLuint pass);


	/**************************************************
	* glfxGetEffectLog
	* Input:
	*   effect  -- GLFX effect id
	*   log     -- Destination address
	*   bufSize -- Size of the buffer
	**************************************************/
	GLFXAPI void GLFX_APIENTRY glfxGetEffectLog(int effect, char* log, int bufSize);


	/**************************************************
	* glfxDeleteEffect
	* Input:
	*   effect  -- GLFX effect id
	**************************************************/
	GLFXAPI void GLFX_APIENTRY glfxDeleteEffect(int effect);

}

#ifdef __cplusplus

/**************************************************
* glfxGetProgramName
* Input:
*   effect  -- GLFX effect id
*   program -- Index of program
**************************************************/
GLFXAPI const char* GLFX_APIENTRY glfxGetProgramName(int effect, int program);

/**************************************************
* glfxGetProgramIndex
* Input:
*   effect  -- GLFX effect id
*   name -- name of program
**************************************************/
GLFXAPI size_t GLFX_APIENTRY glfxGetTechniqueIndex(int effect, const char* name);

/**************************************************
* glfxGetEffectLog
* Input:
*   effect  -- GLFX effect id
* Return value: Log string
**************************************************/
GLFXAPI const char* GLFX_APIENTRY glfxGetEffectLog(int effect);

#endif