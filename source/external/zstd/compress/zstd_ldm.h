/*
 * Copyright (c) 2016-present, Yann Collet, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under both the BSD-style license (found in the
 * LICENSE file in the root directory of this source tree) and the GPLv2 (found
 * in the COPYING file in the root directory of this source tree).
 */

#ifndef ZSTD_LDM_H
#define ZSTD_LDM_H

#if defined (__cplusplus)
extern "C" {
#endif

#include "zstd_compress_internal.h"   /* ldmParams_t, U32 */
#include "../zstd.h"   /* ZSTD_CCtx, size_t */

/*-*************************************
*  Long distance matching
***************************************/

#define ZSTD_LDM_DEFAULT_WINDOW_LOG ZSTD_WINDOWLOG_DEFAULTMAX
#define ZSTD_LDM_HASHEVERYLOG_NOTSET 9999

/** ZSTD_compressBlock_ldm_generic() :
 *
 *  This is a block compressor intended for long distance matching.
 *
 *  The function searches for matches of length at least
 *  ldmParams.minMatchLength using a hash table in cctx->ldmState.
 *  Matches can be at a distance of up to cParams.windowLog.
 *
 *  Upon finding a match, the unmatched literals are compressed using a
 *  ZSTD_blockCompressor (depending on the strategy in the compression
 *  parameters), which stores the matched sequences. The "long distance"
 *  match is then stored with the remaining literals from the
 *  ZSTD_blockCompressor. */
size_t ZSTD_compressBlock_ldm(
        ldmState_t* ldms, ZSTD_matchState_t* ms, seqStore_t* seqStore, U32 rep[ZSTD_REP_NUM],
        ZSTD_CCtx_params const* params, void const* src, size_t srcSize);

size_t ZSTD_compressBlock_ldm_extDict(
        ldmState_t* ldms, ZSTD_matchState_t* ms, seqStore_t* seqStore, U32 rep[ZSTD_REP_NUM],
        ZSTD_CCtx_params const* params, void const* src, size_t srcSize);

/** ZSTD_ldm_initializeParameters() :
 *  Initialize the long distance matching parameters to their default values. */
size_t ZSTD_ldm_initializeParameters(ldmParams_t* params, U32 enableLdm);

/** ZSTD_ldm_getTableSize() :
 *  Estimate the space needed for long distance matching tables. */
size_t ZSTD_ldm_getTableSize(U32 hashLog, U32 bucketSizeLog);

/** ZSTD_ldm_getTableSize() :
 *  Return prime8bytes^(minMatchLength-1) */
U64 ZSTD_ldm_getHashPower(U32 minMatchLength);

/** ZSTD_ldm_adjustParameters() :
 *  If the params->hashEveryLog is not set, set it to its default value based on
 *  windowLog and params->hashLog.
 *
 *  Ensures that params->bucketSizeLog is <= params->hashLog (setting it to
 *  params->hashLog if it is not). */
void ZSTD_ldm_adjustParameters(ldmParams_t* params, U32 windowLog);

#if defined (__cplusplus)
}
#endif

#endif /* ZSTD_FAST_H */
