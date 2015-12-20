#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include <Ecore.h>

#include "efm_priv.h"

typedef struct {
    struct {
        const char *path; //the path where the archive is
        const char *find_path; //the path where you can find what is in the archive
    } archive;
    const char *file; //the file in the archive
    const char *real_path;//< the file which _really_ exists its archive.find_path+file
    const char *fake_path;
} Efm_Archive_File_Data;


EOLIAN static void
_efm_archive_file_generate(Eo *obj, Efm_Archive_File_Data *pd, const char *archive, const char *internal)
{
   char fakepath_buf[PATH_MAX];
   char realpath_buf[PATH_MAX];

   pd->archive.find_path = archive_access(archive, EINA_TRUE);
   if (!pd->archive.find_path) return;

   snprintf(fakepath_buf, sizeof(fakepath_buf), "%s/%s", archive, internal);
   snprintf(realpath_buf, sizeof(realpath_buf), "%s/%s", pd->archive.find_path, internal);

   pd->fake_path = strdup(fakepath_buf);
   pd->real_path = strdup(realpath_buf);

   printf("%s\n", pd->real_path);

   eo_do_super(obj, EFM_ARCHIVE_FILE_CLASS, efm_fs_file_generate(eina_file_path_sanitize(pd->real_path)));
}

EOLIAN static const char *
_efm_archive_file_efm_file_path_get(Eo *obj EINA_UNUSED, Efm_Archive_File_Data *pd)
{
   return pd->fake_path;
}

EOLIAN static void
_efm_archive_file_eo_base_destructor(Eo *obj, Efm_Archive_File_Data *pd)
{
   if (!pd->archive.find_path) archive_unref(pd->archive.find_path);
   eo_do_super(obj, EFM_ARCHIVE_FILE_CLASS, eo_destructor());
}

EOLIAN static Eo_Base *
_efm_archive_file_eo_base_finalize(Eo *obj, Efm_Archive_File_Data *pd)
{
    Eo_Base *ret;

    if (!pd->archive.find_path) return NULL;

    eo_do_super_ret(obj, EFM_ARCHIVE_FILE_CLASS, ret, eo_finalize());
    return ret;
}

#include "efm_archive_file.eo.x"