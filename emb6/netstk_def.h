/**
 * @file    netstk_def.h
 * @date    Oct 16, 2015
 * @author  PN
 * @brief   This header file contains defines, structure declarations and data
 *          types for all modules belonging to Netstack layers
 */

#ifndef NETSTK_PRESENT
#define NETSTK_PRESENT

/*
********************************************************************************
*                                   INCLUDES
********************************************************************************
*/
#include "netstk_cfg.h"
#include "emb6.h"

/*
********************************************************************************
*                               VERSION DECLARATION
********************************************************************************
*/
#define NETSTK_VERSION        000001u         /* Version format Vx.yy.zz */



/*
********************************************************************************
*                            DATA TYPES DECLARATIONS
********************************************************************************
*/
typedef uint16_t        NETSTK_DEV_ID;


/*
********************************************************************************
*                           ENUMERATION DECLARATIONS
********************************************************************************
*/

/**
 * @brief   Netstack error code enumeration declaration
 */
typedef enum netstk_err
{
    /*
     * Common error codes
     */
    NETSTK_ERR_NONE                         = 0U,
    NETSTK_ERR_INIT                         = 1U,
    NETSTK_ERR_BUSY                         = 2U,
    NETSTK_ERR_BUF_OVERFLOW                 = 3U,
    NETSTK_ERR_INVALID_ARGUMENT             = 4U,
    NETSTK_ERR_INVALID_FRAME                = 5U,
    NETSTK_ERR_TX_TIMEOUT                   = 6U,
    NETSTK_ERR_TX_NOACK                     = 7U,
    NETSTK_ERR_CMD_UNSUPPORTED              = 8U,
    NETSTK_ERR_CHANNEL_ACESS_FAILURE        = 9U,
    NETSTK_ERR_FATAL                        = 10U,

    /*
     * LLC error codes
     */
    NETSTK_ERR_LLC_XXX                      = 100U,

    /*
     * MAC error codes
     */
    NETSTK_ERR_MAC_XXX                      = 200U,

    /*
     * PHY error codes
     */
    NETSTK_ERR_PHY_XXX                      = 300U,


    /*
     * LPR error codes
     */
    NETSTK_ERR_LPR_XXX                      = 400U,
    NETSTK_ERR_LPR_UNSUPPORTED_FRAME        = 401U,
    NETSTK_ERR_LPR_BROADCAST_LAST_STROBE    = 402U,
    NETSTK_ERR_LPR_BROADCAST_NOACK          = 403U,
    NETSTK_ERR_LPR_INVALID_ADDR             = 404U,
    NETSTK_ERR_LPR_TX_COLLISION_SAME_DEST   = 405U,
    NETSTK_ERR_LPR_TX_COLLISION_DIFF_DEST   = 406U,
    NETSTK_ERR_LPR_INVALID_ACK              = 407U,


    /*
     * RF error codes
     */
    NETSTK_ERR_RF_XXX                       = 500U,
    NETSTK_ERR_RF_SEND                      = 501U,

}NETSTK_ERR;


/**
 * @brief   Netstack I/O Control command enumeration declaration
 */
typedef enum netstk_ioc_cmd
{
    /*
     * Common command codes
     */
    NETSTK_CMD_NONE = 0,
    NETSTK_CMD_TX_CBFNCT_SET,
    NETSTK_CMD_TX_CBARG_SET,
    NETSTK_CMD_RX_CBFNT_SET,

    /*
     * LLC command codes
     */
    NETSTK_CMD_LLC_XXX = 100U,

    /*
     * MAC command codes
     */
    NETSTK_CMD_MAC_XXX = 200U,
    NETSTK_CMD_MAC_DSN_SET,

    /*
     * PHY command codes
     */
    NETSTK_CMD_PHY_XXX = 300U,


    /*
     * LPR command codes
     */
    NETSTK_CMD_LPR_XXX = 400U,

    /*
     * RF command codes
     */
    NETSTK_CMD_RF_XXX = 500U,

    NETSTK_CMD_RF_TXPOWER_SET,
    NETSTK_CMD_RF_TXPOWER_GET,
    NETSTK_CMD_RF_SENS_SET,
    NETSTK_CMD_RF_SENS_GET,
    NETSTK_CMD_RF_RSSI_GET,
    NETSTK_CMD_RF_CCA_GET,
    NETSTK_CMD_RF_ANT_DIV_SET,
    NETSTK_CMD_RF_RF_SWITCH,
    NETSTK_CMD_RF_IS_RX_BUSY,
    NETSTK_CMD_RF_IS_TX_BUSY,

    NETSTK_CMD_RF_SYNC_SET,
    NETSTK_CMD_RF_SYNC_GET,

}NETSTK_IOC_CMD;


/*
********************************************************************************
*                           STRUCTURE DECLARATIONS
********************************************************************************
*/

/**
 * @brief   Netstack common API structure declaration
 */
typedef struct netstk_module_api     NETSTK_MODULE_DRV;

struct netstk_module_api
{
    char     *name;

    void    (*init  )(void *p_netstk, NETSTK_ERR *p_err);                       /*!< Initialization handler       */

#if 0
    void    (*deinit)(NETSTK_ERR *p_err);                                       /*!< Deinitialization handler     */
#endif

    void    (*on    )(NETSTK_ERR *p_err);

    void    (*off   )(NETSTK_ERR *p_err);

    void    (*send  )(uint8_t *p_data, uint16_t len, NETSTK_ERR *p_err);        /*!< Data transmission handler    */

    void    (*recv  )(uint8_t *p_data, uint16_t len, NETSTK_ERR *p_err);        /*!< Data reception handler       */

    void    (*ioctrl)(NETSTK_IOC_CMD cmd, void *p_val, NETSTK_ERR *p_err);      /*!< Miscellaneous functionality  */
};


/**
 * @brief   Netstack Stack API structure declaration
 */
typedef struct netstk_api    NETSTK_DRV;

struct netstk_api
{
    NETSTK_MODULE_DRV      *llc;           /*!< Pointer to Logical Link Control Driver     */

    NETSTK_MODULE_DRV      *mac;           /*!< Pointer to Medium Access Control Driver    */

    NETSTK_MODULE_DRV      *phy;           /*!< Pointer to Physical Driver                 */

    NETSTK_MODULE_DRV      *lpr;           /*!< Pointer to Low-Power Radio Driver          */

    NETSTK_MODULE_DRV      *rf;            /*!< Pointer to Radio Frequency Driver          */
};


/*
********************************************************************************
*                           STRUCTURE DECLARATIONS
********************************************************************************
*/
typedef void (*NETSTK_CBFNCT) (void *p_arg, NETSTK_ERR *p_err);

typedef void (*NETSTK_CBRXFNCT) (uint8_t *p_data, uint16_t len, NETSTK_ERR *p_err);

/*
********************************************************************************
*                           LLC DRIVERS DECLARATIONS
********************************************************************************
*/
#if NETSTK_CFG_LLC_NULL_EN
extern  NETSTK_MODULE_DRV   LLCDrvNull;
#endif

#if NETSTK_CFG_LLC_802154_EN
extern  NETSTK_MODULE_DRV   LLCDrv802154;
#endif


/*
********************************************************************************
*                           MAC DRIVERS DECLARATIONS
********************************************************************************
*/
#if NETSTK_CFG_MAC_NULL_EN
extern  NETSTK_MODULE_DRV   MACDrvNull;
#endif

#if NETSTK_CFG_MAC_802154_EN
extern  NETSTK_MODULE_DRV   MACDrv802154;
#endif


/*
********************************************************************************
*                           PHY DRIVERS DECLARATIONS
********************************************************************************
*/
#if NETSTK_CFG_PHY_NULL_EN
extern  NETSTK_MODULE_DRV   PHYDrvNull;
#endif


/*
********************************************************************************
*                           LPR DRIVERS DECLARATIONS
********************************************************************************
*/
#if NETSTK_CFG_LPR_APSS_EN
extern  NETSTK_MODULE_DRV   LPRDrvAPSS;
#endif

#if NETSTK_CFG_LPR_NULL_EN
extern  NETSTK_MODULE_DRV   LPRDrvNull;
#endif


/*
********************************************************************************
*                           RF DRIVERS DECLARATIONS
********************************************************************************
*/
#if NETSTK_CFG_RF_CC1120_EN
extern  NETSTK_MODULE_DRV   RFDrvCC1120;
#endif

#if NETSTK_CFG_RF_NULL_EN
extern  NETSTK_MODULE_DRV   RFDrvNull;
#endif


/*
********************************************************************************
*                           SUBMODULE EVENT ASSIGNMENTS
********************************************************************************
*/
#if 0   /* defined in evproc.h */
#define NETSTK_APP_EVENT_TX                         ( 1U )
#define NETSTK_MAC_EVENT_ACK_TX                     ( 2U )
#define NETSTK_MAC_EVENT_ACK_TIMEOUT                ( 3U )
#define NETSTK_MAC_EVENT_TX_DONE                    ( 4U )
#define NETSTK_LPR_EVENT                            ( 5U )
#define NETSTK_RF_EVENT                             ( 6U )
#endif

/*
********************************************************************************
*                                   MACROS
********************************************************************************
*/
#define NETSTK_EVENT_PEND(_event_, _fnct_)          evproc_regCallback(_event_, _fnct_)
#define NETSTK_EVENT_POST(_event_, _arg_)           evproc_putEvent(E_EVPROC_HEAD, _event_, _arg_)



#define LPR_CFG_REFACTOR_EN                             ( 0U )
#define RF_CFG_REFACTOR_EN                              ( 0U )


extern  NETSTK_ERR  NetstkLastErr;

/*
********************************************************************************
*                               END OF FILE
********************************************************************************
*/
#endif /* NETSTK_PRESENT */
