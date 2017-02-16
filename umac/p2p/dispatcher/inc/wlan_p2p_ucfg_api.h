/*
 * Copyright (c) 2017 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/**
 * DOC: Contains p2p north bound interface definitions
 */

#ifndef _WLAN_P2P_UCFG_API_H_
#define _WLAN_P2P_UCFG_API_H_

#include <qdf_types.h>

struct wlan_objmgr_psoc;
struct p2p_roc_req;
struct p2p_event;
struct p2p_rx_mgmt_frame;
struct p2p_tx_cnf;
struct p2p_mgmt_tx;
struct p2p_ps_config;
struct p2p_lo_start;
struct p2p_lo_event;

/**
 * p2p_rx_callback() - Callback for rx mgmt frame
 * @user_data: user data associated to this rx mgmt frame.
 * @rx_frame: RX mgmt frame
 *
 * This callback will be used to give rx frames to hdd.
 *
 * Return: None
 */
typedef void (*p2p_rx_callback)(void *user_data,
	struct p2p_rx_mgmt_frame *rx_frame);

/**
 * p2p_action_tx_cnf_callback() - Callback for tx confirmation
 * @user_data: user data associated to this tx confirmation
 * @tx_cnf: tx confirmation information
 *
 * This callback will be used to give tx mgmt frame confirmation to
 * hdd.
 *
 * Return: None
 */
typedef void (*p2p_action_tx_cnf_callback)(void *user_data,
	struct p2p_tx_cnf *tx_cnf);

/**
 * p2p_lo_event_callback() - Callback for listen offload event
 * @user_data: user data associated to this lo event
 * @p2p_lo_event: listen offload event information
 *
 * This callback will be used to give listen offload event to hdd.
 *
 * Return: None
 */
typedef void (*p2p_lo_event_callback)(void *user_data,
	struct p2p_lo_event *p2p_lo_event);

/**
 * p2p_event_callback() - Callback for P2P event
 * @user_data: user data associated to this p2p event
 * @p2p_event: p2p event information
 *
 * This callback will be used to give p2p event to hdd.
 *
 * Return: None
 */
typedef void (*p2p_event_callback)(void *user_data,
	struct p2p_event *p2p_event);

/**
 * struct p2p_start_param - p2p soc start parameters. Below callbacks
 *                          will be registered by the HDD
 * @rx_callback:      Function pointer to hdd rx callback. This
 *                    function will be used to give rx frames to hdd
 * @rx_cb_data:       RX callback user data
 * @event_cb:         Founction pointer to hdd p2p event callback.
 *                    This function will be used to give p2p event
 *                    to hdd
 * @event_cb_data:    Pointer to p2p event callback user data
 * @tx_cnf_cb:        Function pointer to hdd tx confirm callback.
 *                    This function will be used to give tx confirm
 *                    to hdd
 * @tx_cnf_cb_data:   Pointer to p2p tx confirm callback user data
 * @lo_event_cb:      Founction pointer to p2p listen offload
 *                    callback. This function will be used to give
 *                    listen offload stopped event to hdd
 * @lo_event_cb_data: Pointer to p2p listen offload callback user data
 */
struct p2p_start_param {
	p2p_rx_callback rx_cb;
	void *rx_cb_data;
	p2p_event_callback event_cb;
	void *event_cb_data;
	p2p_action_tx_cnf_callback tx_cnf_cb;
	void *tx_cnf_cb_data;
	p2p_lo_event_callback lo_event_cb;
	void *lo_event_cb_data;
};

/**
 * ucfg_p2p_init() - P2P component initialization
 *
 * This function gets called when dispatcher initializing.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_init(void);

/**
 * ucfg_p2p_deinit() - P2P component de-init
 *
 * This function gets called when dispatcher de-init.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_deinit(void);

/**
 * ucfg_p2p_psoc_open() - Open P2P component
 * @soc: soc context
 *
 * This function gets called when dispatcher opening.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_psoc_open(struct wlan_objmgr_psoc *soc);

/**
 * ucfg_p2p_psoc_close() - Close P2P component
 * @soc: soc context
 *
 * This function gets called when dispatcher closing.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_psoc_close(struct wlan_objmgr_psoc *soc);

/**
 * ucfg_p2p_psoc_start() - Start P2P component
 * @soc: soc context
 * @req: P2P start parameters
 *
 * This function gets called when up layer starting up.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_psoc_start(struct wlan_objmgr_psoc *soc,
	struct p2p_start_param *req);

/**
 * ucfg_p2p_psoc_stop() - Stop P2P component
 * @soc: soc context
 *
 * This function gets called when up layer exit.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_psoc_stop(struct wlan_objmgr_psoc *soc);

/**
 * ucfg_p2p_roc_req() - Roc request
 * @soc: soc context
 * @roc_req: Roc request parameters
 * @cookie: return cookie to caller
 *
 * This function delivers roc request to P2P component.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_roc_req(struct wlan_objmgr_psoc *soc,
	struct p2p_roc_req *roc_req, uint64_t *cookie);

/**
 * ucfg_p2p_roc_cancel_req() - Cancel roc request
 * @soc: soc context
 * @cookie: Find out the roc request by cookie
 *
 * This function delivers cancel roc request to P2P component.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_roc_cancel_req(struct wlan_objmgr_psoc *soc,
	uint64_t cookie);

/**
 * ucfg_p2p_mgmt_tx() - Mgmt frame tx request
 * @soc: soc context
 * @mgmt_frm: TX mgmt frame parameters
 * @cookie: Return the cookie to caller
 *
 * This function delivers mgmt frame tx request to P2P component.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_mgmt_tx(struct wlan_objmgr_psoc *soc,
	struct p2p_mgmt_tx *mgmt_frm, uint64_t *cookie);

/**
 * ucfg_p2p_mgmt_tx_cancel() - Cancel mgmt frame tx request
 * @soc: soc context
 * @cookie: Find out the mgmt tx request by cookie
 *
 * This function delivers cancel mgmt frame tx request request to P2P
 * component.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_mgmt_tx_cancel(struct wlan_objmgr_psoc *soc,
	uint64_t cookie);

/**
 * ucfg_p2p_set_ps() - P2P set power save
 * @soc: soc context
 * @ps_config: power save configure
 *
 * This function delivers p2p power save request to P2P component.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_set_ps(struct wlan_objmgr_psoc *soc,
	struct p2p_ps_config *ps_config);

/**
 * ucfg_p2p_lo_start() - Listen offload start request
 * @soc: soc context
 * @p2p_lo_start: lo start parameters
 *
 * This function delivers listen offload start request to P2P
 * component.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_lo_start(struct wlan_objmgr_psoc *soc,
	struct p2p_lo_start *p2p_lo_start);

/**
 * ucfg_p2p_lo_stop() - Listen offload stop request
 * @soc: soc context
 * @vdev_id: vdev id
 *
 * This function delivers listen offload stop request to P2P component.
 *
 * Return: QDF_STATUS_SUCCESS - in case of success
 */
QDF_STATUS ucfg_p2p_lo_stop(struct wlan_objmgr_psoc *soc,
	uint32_t vdev_id);

#endif /* _WLAN_P2P_UCFG_API_H_ */
