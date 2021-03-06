#ifndef EMOUS_H
#define EMOUS_H

#include <Eina.h>
#include <Eo.h>

#ifdef EAPI
# undef EAPI
#endif

#ifdef _WIN32
# ifdef EFL_ECORE_BUILD
#  ifdef DLL_EXPORT
#   define EAPI __declspec(dllexport)
#  else
#   define EAPI
#  endif /* ! DLL_EXPORT */
# else
#  define EAPI __declspec(dllimport)
# endif /* ! EFL_ECORE_BUILD */
#else
# ifdef __GNUC__
#  if __GNUC__ >= 4
#   define EAPI __attribute__ ((visibility("default")))
#  else
#   define EAPI
#  endif
# else
#  define EAPI
# endif
#endif /* ! _WIN32 */

#include "emous_device.eo.h"
#include "emous.eo.h"
#include "emous_type.eo.h"
#include "emous_manager.eo.h"

EAPI int emous_init(void);
EAPI void emous_shutdown(void);

#undef EAPI

#endif
