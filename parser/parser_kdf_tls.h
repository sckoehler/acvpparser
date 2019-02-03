/*
 * Copyright (C) 2018 - 2019, Stephan Mueller <smueller@chronox.de>
 *
 * License: see LICENSE file
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ALL OF
 * WHICH ARE HEREBY DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF NOT ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#ifndef _PARSER_KDF_TLS_H
#define _PARSER_KDF_TLS_H

#include "parser.h"
#include "parser_flags.h"

/**
 * @brief TLS PRF testing context
 *
 * @param hashalg [in] Hash algorithm to be used for PRF. ACVP_SHA1
 *		       implies TLS v1.0 / v1.1 testing with SHA-1 / MD5 based
 *		       PRF. References to SHA-2 implies TLS v1.2 with the given
 *		       hash to be used for the PRF.
 * @param pre_master_secret_length [in] Length of pre-master secret in bits
 *					(information only as the
 *					@param pre_master_secret contains the
 *					full data).
 * @param key_block_length [in] Length of the key block to be generated in bits.
 * @param client_hello_random [in] Client hello random number
 * @param server_hello_random [in] Server hello random number
 * @param client_random [in] Client random number
 * @param server_random [in] Server random number
 * @param pre_master_secret [in] Pre-master secret for the TLS operation.
 * @param master_secret [out] Master secret generated by the PRF -- the length
 *			      is equal to the @param pre_master_secret.
 * @param key_block [out] Generated key block of the length given with
 *			  @param key_block_length.
 */
struct kdf_tls_data {
	uint64_t hashalg;
	uint32_t pre_master_secret_length;
	uint32_t key_block_length;
	struct buffer client_hello_random;
	struct buffer server_hello_random;
	struct buffer client_random;
	struct buffer server_random;
	struct buffer pre_master_secret;

	struct buffer master_secret;
	struct buffer key_block;
};

/**
 * @brief Callback data structure that must be implemented by the backend.
 *
 * All functions return 0 on success or != 0 on error.
 *
 * @param kdf_tls Invoke the TLS PRF testing.
 */

struct kdf_tls_backend {
	int (*kdf_tls)(struct kdf_tls_data *data, flags_t parsed_flags);
};

void register_kdf_tls_impl(struct kdf_tls_backend *implementation);

#endif /* _PARSER_KDF_TLS_H */
