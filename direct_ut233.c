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

#include "spdk/stdinc.h"

#include "spdk_cunit.h"

#include "direct.c"

#include "../../../../lib/nvme/nvme_internal.h"

SPDK_LOG_REGISTER_TRACE_FLAG("nvmf", SPDK_TRACE_NVMF)

uint32_t
spdk_env_get_current_core(void)
{
	return 0;
}

void
spdk_poller_register(struct spdk_poller **ppoller, spdk_poller_fn fn, void *arg,
		     uint32_t lcore, uint64_t period_microseconds)
{
	return;
}

void
spdk_poller_unregister(struct spdk_poller **ppoller, struct spdk_event *complete)
{
	return;
}

int32_t
spdk_nvme_ctrlr_process_admin_completions(struct spdk_nvme_ctrlr *ctrlr)
{
	return -1;
}

void
spdk_trace_record(uint16_t tpoint_id, uint16_t poller_id, uint32_t size, uint64_t object_id,
		  uint64_t arg1)
{
}

uint32_t
spdk_nvme_ctrlr_get_num_ns(struct spdk_nvme_ctrlr *ctrlr)
{
	return 1;
}

const struct spdk_nvme_ctrlr_data *
spdk_nvme_ctrlr_get_data(struct spdk_nvme_ctrlr *ctrlr)
{
	return NULL;
}

void
spdk_nvme_ctrlr_register_aer_callback(struct spdk_nvme_ctrlr *ctrlr,
				      spdk_nvme_aer_cb aer_cb_fn,
				      void *aer_cb_arg)
{
}

int
spdk_nvme_ctrlr_cmd_io_raw(struct spdk_nvme_ctrlr *ctrlr,
			   struct spdk_nvme_qpair *qpair,
			   struct spdk_nvme_cmd *cmd,
			   void *buf, uint32_t len,
			   spdk_nvme_cmd_cb cb_fn, void *cb_arg)
{
	if(buf == NULL)
	{
		return -1;
	}
	return 0;
}

struct spdk_nvme_ns *spdk_nvme_ctrlr_get_ns(struct spdk_nvme_ctrlr *ctrlr, uint32_t ns_id)
{
	return NULL;
}

bool
spdk_nvme_ns_is_active(struct spdk_nvme_ns *ns)
{
	return true;
}

int
spdk_nvme_ctrlr_cmd_admin_raw(struct spdk_nvme_ctrlr *ctrlr,
			      struct spdk_nvme_cmd *cmd,
			      void *buf, uint32_t len,
			      spdk_nvme_cmd_cb cb_fn, void *cb_arg)
{
	return -1;
}

union spdk_nvme_vs_register
	spdk_nvme_ctrlr_get_regs_vs(struct spdk_nvme_ctrlr *ctrlr)
{
	union spdk_nvme_vs_register vs;
	vs.raw = 0;
	return vs;
}

int
spdk_nvme_detach(struct spdk_nvme_ctrlr *ctrlr)
{
	return -1;
}

struct spdk_nvme_qpair *
spdk_nvme_ctrlr_alloc_io_qpair(struct spdk_nvme_ctrlr *ctrlr, enum spdk_nvme_qprio qprio)
{
	return NULL;
}

int32_t
spdk_nvme_qpair_process_completions(struct spdk_nvme_qpair *qpair, uint32_t max_completions)
{
	return -1;
}
int
spdk_nvmf_request_complete(struct spdk_nvmf_request *req)
{
	return -1;
}

int
spdk_nvmf_session_get_features_number_of_queues(struct spdk_nvmf_request *req)
{
	return -1;
}

int spdk_nvmf_session_set_features_number_of_queues(struct spdk_nvmf_request *req)
{
	return -1;
}

int
spdk_nvmf_session_set_features_host_identifier(struct spdk_nvmf_request *req)
{
	return -1;
}

int
spdk_nvmf_session_get_features_host_identifier(struct spdk_nvmf_request *req)
{
	return -1;
}
int
spdk_nvmf_session_set_features_keep_alive_timer(struct spdk_nvmf_request *req)
{
	return -1;
}

int
spdk_nvmf_session_get_features_keep_alive_timer(struct spdk_nvmf_request *req)
{
	return -1;
}

int
spdk_nvmf_session_set_features_async_event_configuration(struct spdk_nvmf_request *req)
{
	return -1;
}

int
spdk_nvmf_session_get_features_async_event_configuration(struct spdk_nvmf_request *req)
{
	return -1;
}

int
spdk_nvmf_session_async_event_request(struct spdk_nvmf_request *req)
{
	return -1;
}
static void
test_direct_ctrlr_process_admin_cmd(struct spdk_nvmf_request * req)
{
	int ret;
	struct spdk_nvmf_request request={};
	union nvmf_h2c_msg		cmd = {};
	union nvmf_c2h_msg		rsp = {};
	struct spdk_nvme_cpl				nvme_cpl = {};
	struct spdk_nvme_cmd				nvme_cmd = {};
	struct spdk_nvmf_conn		conn = {};
	struct spdk_nvmf_session		sess ={};
	req.cmd = &cmd;
	req.cmd->nvme_cmd = &nvme_cmd;
	req.cmd->nvme_cmd->opc = 0x06;
	nvmf_direct_ctrlr_process_admin_cmd(&req);
	CU_ASSERT(ret == 1 )
	
}
static void
test_nvmf_ctrlr_process_io_cmd(void)
{
	int ret;
	struct spdk_nvmf_request req = {};
	struct spdk_nvmf_conn		conn={};
	struct spdk_nvmf_session  sess ={};
	struct spdk_nvme_ctrlr ctrlr ={};
	struct spdk_nvme_qpair	io_qpair = {};
	union nvmf_c2h_msg		rsp = {};
	struct spdk_nvmf_subsystem 	subsys = {
		.dev.direct.ctrlr = &ctrlr,
		.dev.direct.io_qpair = &io_qpair, 
	};
	req.conn =&conn;
	req.conn->sess = &sess;
	req.conn->sess->subsys = &subsys;	


	req.rsp = &rsp;
	req.rsp->nvme_cpl.status.sc = 0;
	ret = nvmf_direct_ctrlr_process_io_cmd(&req);
	CU_ASSERT(req.rsp->nvme_cpl.status.sc ==6)
	CU_ASSERT(ret == 0);
	req.data = "test";
	ret = nvmf_direct_ctrlr_process_io_cmd(&req);
	CU_ASSERT(ret == 1);
}
/* test suite function */
static void
nvmf_test_nvmf_direct_ctrlr_admin_identify_nslist(void)
{
    /*int ret;
	union nvmf_h2c_msg cmd;
	struct spdk_nvme_ns_list ns_list = {};
    struct spdk_nvme_ctrlr *ctrlr;
    ctrlr = (struct spdk_nvme_ctrlr *)malloc(sizeof(struct spdk_nvme_ctrlr));
    struct spdk_nvmf_request *req;
    req = (struct spdk_nvmf_request *)malloc(sizeof(struct spdk_nvmf_request));
	req->data = &ns_list;
    req->cmd = &cmd;
    (&req->cmd->nvme_cmd)->nsid = 0xfffffffeUL;
    ret = nvmf_direct_ctrlr_admin_identify_nslist(ctrlr,req);
    CU_ASSERT(ret == -1);

    (&req->cmd->nvme_cmd)->nsid = 0xfffffffdUL;
    ret = nvmf_direct_ctrlr_admin_identify_nslist(ctrlr,req);
    CU_ASSERT(ret == 0);

    req->cmd->nvme_cmd.nsid = 0;
    ctrlr->num_ns = 0xffffffffUL;//set num_ns is large than ns_id 
    ret = nvmf_direct_ctrlr_admin_identify_nslist(ctrlr,req);
    CU_ASSERT(ret == 0);   
    CU_ASSERT(ns_list.ns_list[0] == 1);    
    free(ctrlr);
    free(req);*/
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

	if (CU_add_test(suite, "direct_ctrlr_admin_identify_nslist",nvmf_test_nvmf_direct_ctrlr_admin_identify_nslist) == NULL || 
		CU_add_test(suite, "nvmf_ctrlr_process_io_cmd", test_nvmf_ctrlr_process_io_cmd) == NULL || 
		CU_add_test(suite, "nvmf_direct_ctrlr_process_admin_cmd", test_direct_ctrlr_process_admin_cmd) == NULL 
		){
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	num_failures = CU_get_number_of_failures();
	CU_cleanup_registry();
	return num_failures;
}
