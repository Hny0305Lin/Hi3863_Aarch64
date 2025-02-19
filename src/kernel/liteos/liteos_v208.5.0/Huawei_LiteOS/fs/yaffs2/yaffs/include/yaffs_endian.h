/*
 * YAFFS: Yet Another Flash File System. A NAND-flash specific file system.
 *
 * Copyright (C) 2002-2015 Aleph One Ltd.
 *
 * Created by Charles Manning <charles@aleph1.co.uk>
 *
 * This software is the subject of a Licence Agreement between Aleph One Limited and Hi_Silicon_Huawei_DigiMedia.
 *
 */

#ifndef __YAFFS_ENDIAN_H__
#define __YAFFS_ENDIAN_H__
#include "yaffs_guts.h"
#include "yaffs_packedtags2.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


static inline u32 swap_u32(u32 val)
{
	return ((val >>24) & 0x000000ff) |
	       ((val >> 8) & 0x0000ff00) |
	       ((val << 8) & 0x00ff0000) |
	       ((val <<24) & 0xff000000);
}

static inline u64 swap_u64(u64 val)
{
	return ((val >> 56) & 0x00000000000000ff) |
		   ((val >> 40) & 0x000000000000ff00) |
		   ((val >> 24) & 0x0000000000ff0000) |
		   ((val >> 8)	& 0x00000000ff000000) |
		   ((val << 8)	& 0x000000ff00000000) |
		   ((val << 24) & 0x0000ff0000000000) |
		   ((val << 40) & 0x00ff000000000000) |
		   ((val << 56) & 0xff00000000000000);
}

static inline YTIME_T swap_ytime_t(YTIME_T val)
{

	if (sizeof(YTIME_T) == sizeof(u64))
		return swap_u64(val);
	else
		return swap_u32(val);
}

//swap a signed 32 bit integer.

#define swap_s32(val) \
	(s32)(swap_u32((u32)(val)))

static inline loff_t swap_loff_t(loff_t lval)
{
	u32 vall = swap_u32(FSIZE_LOW(lval));
	u32 valh;

	if (sizeof(loff_t) == sizeof(u32))
		return (loff_t) vall;

	valh = swap_u32(FSIZE_HIGH(lval));

	return FSIZE_COMBINE(vall, valh); /*NB: h and l are swapped. */
}



struct yaffs_dev;
void yaffs_do_endian_s32(struct yaffs_dev *dev, s32 *val);
void yaffs_do_endian_u32(struct yaffs_dev *dev, u32 *val);
void yaffs_do_endian_oh(struct yaffs_dev *dev, struct yaffs_obj_hdr *oh);
void yaffs_do_endian_packed_tags2(struct yaffs_dev *dev,
				struct yaffs_packed_tags2_tags_only *ptt);
int yaffs_endian_config(struct yaffs_dev *dev);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __YAFFS_ENDIAN_H__ */
