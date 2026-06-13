/*
 * Copyright (©) 2022, 2026 yejq <yejq.jiaqiang@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * ABOUT: Common Hash utility for C, based upon UTHASH
 */

#ifndef COMMON_HASH_H
#define COMMON_HASH_H 1

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* hash values types */
union cm_hval {
	int32_t               cm_int;
	uint32_t              cm_uint;
	int64_t               cm_int64;
	uint64_t              cm_uint64;
	long                  cm_long;
	unsigned long         cm_ulong;
	void *                cm_pointer;
};

static inline void cmval_zero(union cm_hval * cmp)
{
	/* set maximum size of all 8 bytes to zero */
	cmp->cm_uint64 = 0ull;
}

typedef void * cmhash_t;

int cmhash_get(cmhash_t chash,
	const void * cmkey, unsigned int cmlen,
	union cm_hval * valp);

int cmhash_add(cmhash_t * chash,
	const void * cmkey, unsigned int cmlen,
	const union cm_hval * valp, union cm_hval * oldval);

int cmhash_del(cmhash_t * chash,
	const void * cmkey, unsigned int cmlen,
	union cm_hval * oldval);

void cmhash_delete(cmhash_t * chash, void * ppriv,
	int (* free_func)(int, void *, const union cm_hval *));

unsigned int cmhash_count(cmhash_t chash);

/*
 * Iterate over the hash set WITHOUT MODIFYING,
 * JUST DO NOT MODIFY THE HASH TABLE.
 * Note that if `iter_func returns negative value,
 * the iteration will stop.
 */
int cmhash_iter(cmhash_t chash, void * ppriv,
	int (* iter_func)(int, void *, const union cm_hval *));

const void * cmhash_key(const union cm_hval * cval,
	unsigned int * key_len);

#ifdef __cplusplus
};
#endif
#endif
