/**
 * \usergroup{SceModulemgr}
 * \usage{psp2/kernel/modulemgr.h}
 */


#ifndef _PSP2_KERNEL_MODULEMGR_H_
#define _PSP2_KERNEL_MODULEMGR_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief      Return values for plugins `module_start` and `module_stop`
 */
/** @{ */
#define SCE_KERNEL_START_SUCCESS      (0)
#define SCE_KERNEL_START_RESIDENT     SCE_KERNEL_START_SUCCESS
#define SCE_KERNEL_START_NO_RESIDENT  (1)
#define SCE_KERNEL_START_FAILED       (2)

#define SCE_KERNEL_STOP_SUCCESS       (0)
#define SCE_KERNEL_STOP_FAIL          (1)
#define SCE_KERNEL_STOP_CANCEL        SCE_KERNEL_STOP_FAIL
/** @} */

typedef struct SceKernelSegmentInfo {
	SceUInt size;   //!< sizeof(SceKernelSegmentInfo)
	SceUInt perms;  //!< probably rwx in low bits
	void *vaddr;    //!< address in memory
	SceUInt memsz;  //!< size in memory
	SceUInt flags;  //!< meaning unknown
	SceUInt res;    //!< unused?
} SceKernelSegmentInfo;

typedef struct SceKernelModuleInfo {
	SceUInt size;                       //!< 0x1B8 for Vita 1.x
	SceUInt handle;                     //!< kernel module handle?
	SceUInt flags;                      //!< some bits. could be priority or whatnot
	char module_name[28];
	SceUInt unk28;
	void *module_start;
	void *module_stop;
	void *module_exit;
	void *exidxTop;
	void *exidxBtm;
	SceUInt unk40;
	SceUInt unk44;
	void *tlsInit;
	SceSize tlsInitSize;
	SceSize tlsAreaSize;
	char path[256];
	SceKernelSegmentInfo segments[4];
	SceUInt type;                       //!< 6 = user-mode PRX?
} SceKernelModuleInfo;

typedef struct SceKernelLMOption {
	SceSize size;
} SceKernelLMOption;

typedef struct SceKernelULMOption {
	SceSize size;
} SceKernelULMOption;

int sceKernelGetModuleList(int flags, SceUID *modids, int *num);
int sceKernelGetModuleInfo(SceUID modid, SceKernelModuleInfo *info);

SceUID sceKernelLoadModule(const char *path, int flags, SceKernelLMOption *option);
int sceKernelUnloadModule(SceUID modid, int flags, SceKernelULMOption *option);

int sceKernelStartModule(SceUID modid, SceSize args, void *argp, int flags, void *option, int *status);
int sceKernelStopModule(SceUID modid, SceSize args, void *argp, int flags, void *option, int *status);

SceUID sceKernelLoadStartModule(const char *path, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status);
int sceKernelStopUnloadModule(SceUID modid, SceSize args, void *argp, int flags, SceKernelULMOption *option, int *status);

typedef struct SceKernelFwInfo {
  SceSize size;
  char versionString[0x1C];
  SceUInt version;
  SceUInt unk_24;
} SceKernelFwInfo;

int sceKernelGetSystemSwVersion(SceKernelFwInfo *data);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_MODULEMGR_H_ */

