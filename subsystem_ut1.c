/*-
 *   BSD LICENSE
 *
 *   Copyright (c) Intel Corporation.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "spdk_cunit.h"
#include "subsystem.h"

const struct spdk_nvmf_ctrlr_ops spdk_nvmf_direct_ctrlr_ops;
const struct spdk_nvmf_ctrlr_ops spdk_nvmf_virtual_ctrlr_ops;
const struct spdk_nvmf_ctrlr_ops spdk_nvmf_discovery_ctrlr_ops;

#include "subsystem.c"

SPDK_LOG_REGISTER_TRACE_FLAG("nvmf", SPDK_TRACE_NVMF)

struct spdk_nvmf_tgt g_nvmf_tgt;

struct spdk_nvmf_listen_addr *
spdk_nvmf_listen_addr_create(const char *trname, const char *traddr, const char *trsvcid)
{   
    if(!trname)
    {
        SPDK_ERRLOG("trname is NULL");
        return NULL;
    }

    if(!trname)
    {
        SPDK_ERRLOG("traddr is NULL");
        return NULL;
    }

    if(!trname)
    {
        SPDK_ERRLOG("trsvcid is NULL");
        return NULL;
    }
    
	struct spdk_nvmf_listen_addr *listen_addr;

	listen_addr = calloc(1, sizeof(*listen_addr));
	if (!listen_addr) {
		return NULL;
	}

	listen_addr->traddr = strdup(traddr);
	if (!listen_addr->traddr) {
		free(listen_addr);
		return NULL;
	}

	listen_addr->trsvcid = strdup(trsvcid);
	if (!listen_addr->trsvcid) {
		free(listen_addr->traddr);
		free(listen_addr);
		return NULL;
	}

	listen_addr->trname = strdup(trname);
	if (!listen_addr->trname) {
		free(listen_addr->traddr);
		free(listen_addr->trsvcid);
		free(listen_addr);
		return NULL;
	}

	return listen_addr;
}

void
spdk_nvmf_listen_addr_destroy(struct spdk_nvmf_listen_addr *addr)
{
	free(addr->trname);
	free(addr->trsvcid);
	free(addr->traddr);
	free(addr);
} 

void
spdk_nvmf_listen_addr_cleanup(struct spdk_nvmf_listen_addr *addr)
{
	return;
}

static int
test_transport1_listen_addr_add(struct spdk_nvmf_listen_addr *listen_addr)
{
	return 0;
}

static void
test_transport1_listen_addr_discover(struct spdk_nvmf_listen_addr *listen_addr,
				     struct spdk_nvmf_discovery_log_page_entry *entry)
{
	entry->trtype = 42;
}

static const struct spdk_nvmf_transport test_transport1 = {
	.listen_addr_add = test_transport1_listen_addr_add,
	.listen_addr_discover = test_transport1_listen_addr_discover,
};

const struct spdk_nvmf_transport *
spdk_nvmf_transport_get(const char *trname)
{
	if (!strcasecmp(trname, "test_transport1")) {
		return &test_transport1;
	}

	return NULL;
}

int32_t
spdk_nvme_ctrlr_process_admin_completions(struct spdk_nvme_ctrlr *ctrlr)
{
	return -1;
}

int32_t
spdk_nvme_qpair_process_completions(struct spdk_nvme_qpair *qpair, uint32_t max_completions)
{
	return -1;
}

int
spdk_nvme_detach(struct spdk_nvme_ctrlr *ctrlr)
{
	return -1;
}

void
spdk_nvmf_session_destruct(struct spdk_nvmf_session *session)
{
}

int
spdk_nvmf_session_poll(struct spdk_nvmf_session *session)
{
	return -1;
}

bool
spdk_bdev_claim(struct spdk_bdev *bdev, spdk_bdev_remove_cb_t remove_cb,
		void *remove_ctx)
{
	return true;
}
static void
test_spdk_nvmf_subsystem_exists(void)
{
    struct spdk_nvmf_subsystem subsystem = {};
    //struct spdk_nvmf_subsystem *subsystem ;

    //struct nvmf_subsystem *subsystem;
    /* subnqn is NULL */
    const char *nqn = NULL;
    CU_ASSERT_FALSE(spdk_nvmf_subsystem_exists(nqn));

    /* Not exists subnqn */
	char subnqn[256];
    strncpy(subnqn,"nqn.2016-06.io.spdk:subsystem1",sizeof(subnqn));
    CU_ASSERT_FALSE(spdk_nvmf_subsystem_exists(subnqn));

    /* Exists subnqn */
    strcpy(subsystem.subnqn,subnqn);
    //CU_ASSERT(strcmp(subsystem->subnqn,subnqn)==0);
    CU_ASSERT_TRUE(spdk_nvmf_subsystem_exists(subnqn));

}

static void 
test_spdk_nvmf_tgt_listen(void)
{
    struct spdk_nvmf_listen_addr *listen_addr;
    const struct spdk_nvmf_transport *transport;
    int rc;

    /* listern addr is already create */
    const char *trname = "test_transport1";
    const char *traddr = "192.168.100.1";
    const char *trsvcid = "4420";
    strcpy(listen_addr->trname,trname);
    strcpy(listen_addr->traddr,traddr);
    strcpy(listen_addr->trsvcid,trsvcid);
    listen_addr = spdk_nvmf_tgt_listen(trname,traddr,trsvcid);
    SPDK_CU_ASSERT_FATAL(listen_addr != NULL);
    CU_ASSERT_PTR_EQUAL(listen_addr,spdk_nvmf_tgt_listen(trname,traddr,trsvcid));

    /* listen addr is not create and trname can't find */
    const char *trname1  = "test_transport2";
    const char *traddr1  = "192.168.100.1";
    const char *trsvcid1 = "4420";
    listen_addr = spdk_nvmf_tgt_listen(trname1,traddr1,trsvcid2);
    SPDK_CU_ASSERT_FATAL(listen_addr == NULL);
    
    /* listen addr is not create and find trname success */
    const char *trname2  = "test_transport1";
    const char *traddr2  = "192.168.3.11";
    const char *trsvcid2 = "4420";
    listen_addr = spdk_nvmf_tgt_listen(trname2,traddr2,trsvcid2);
    CU_ASSERT_PTR_NOT_NULL(listen_addr);
    CU_ASSERT(listen_addr->traddr == traddr);

    /* listen addr is not create and traddr is not in g_transports*/
    const char *trname3  = "test_transport1";
    const char *traddr3  = "192.168.1.100";
    const char *trsvcid3 = NULL;
    listen_addr = spdk_nvmf_tgt_listen(trname3,traddr3,trsvcid3);
    SPDK_CU_ASSERT_FATAL(listen_addr == NULL);
    
     
}
static void
nvmf_test_create_subsystem(void)
{
	char nqn[256];
	struct spdk_nvmf_subsystem *subsystem;
	TAILQ_INIT(&g_nvmf_tgt.subsystems);

	strncpy(nqn, "nqn.2016-06.io.spdk:subsystem1", sizeof(nqn));
	subsystem = spdk_nvmf_create_subsystem(nqn, SPDK_NVMF_SUBTYPE_NVME,
					       NVMF_SUBSYSTEM_MODE_DIRECT, NULL, NULL, NULL);
	SPDK_CU_ASSERT_FATAL(subsystem != NULL);
	CU_ASSERT_STRING_EQUAL(subsystem->subnqn, nqn);
	spdk_nvmf_delete_subsystem(subsystem);

	/* Longest valid name */
	strncpy(nqn, "nqn.2016-06.io.spdk:", sizeof(nqn));
	memset(nqn + strlen(nqn), 'a', 222 - strlen(nqn));
	nqn[222] = '\0';
	CU_ASSERT(strlen(nqn) == 222);
	subsystem = spdk_nvmf_create_subsystem(nqn, SPDK_NVMF_SUBTYPE_NVME,
					       NVMF_SUBSYSTEM_MODE_DIRECT, NULL, NULL, NULL);
	SPDK_CU_ASSERT_FATAL(subsystem != NULL);
	CU_ASSERT_STRING_EQUAL(subsystem->subnqn, nqn);
	spdk_nvmf_delete_subsystem(subsystem);

	/* Name that is one byte longer than allowed */
	strncpy(nqn, "nqn.2016-06.io.spdk:", sizeof(nqn));
	memset(nqn + strlen(nqn), 'a', 223 - strlen(nqn));
	nqn[223] = '\0';
	CU_ASSERT(strlen(nqn) == 223);
	subsystem = spdk_nvmf_create_subsystem(nqn, SPDK_NVMF_SUBTYPE_NVME,
					       NVMF_SUBSYSTEM_MODE_DIRECT, NULL, NULL, NULL);
	CU_ASSERT(subsystem == NULL);
}

static void
nvmf_test_find_subsystem(void)
{
	CU_ASSERT_PTR_NULL(nvmf_find_subsystem(NULL));
	CU_ASSERT_PTR_NULL(nvmf_find_subsystem("fake"));
}

int main(int argc, char **argv)
{
	CU_pSuite	suite = NULL;
	unsigned int	num_failures;

	if (CU_initialize_registry() != CUE_SUCCESS) {
		return CU_get_error();
	}

	suite = CU_add_suite("nvmf", NULL, NULL);
	if (suite == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (
		CU_add_test(suite, "subsystem_exists", test_spdk_nvmf_subsystem_exists) == NULL || 
		CU_add_test(suite, "create_subsystem", nvmf_test_create_subsystem) == NULL ||
		CU_add_test(suite, "find_subsystem", nvmf_test_find_subsystem) == NULL ||
		CU_add_test(suite, "test_spdk_nvmf_tgt_listen", test_spdk_nvmf_tgt_listen) == NULL)
    {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	num_failures = CU_get_number_of_failures();
	CU_cleanup_registry();
	return num_failures;
}
