#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

#include "mi_sys.h"
#include "sstardisp.h"
#include "mi_panel_datatype.h"
#include "mi_panel.h"
#include "mi_disp_datatype.h"
#include "mi_disp.h"


#if defined(__cplusplus)||defined(c_plusplus)
extern "C"{
#endif

#define DISP_INPUT_WIDTH    1024
#define DISP_INPUT_HEIGHT   600

#define MAKE_YUYV_VALUE(y,u,v) ((y) << 24) | ((u) << 16) | ((y) << 8) | (v)
#define YUYV_BLACK MAKE_YUYV_VALUE(0,128,128)

int sstar_disp_init()
{
    MI_DISP_PubAttr_t stPubAttr;
    MI_DISP_VideoLayerAttr_t stLayerAttr;
    MI_DISP_RotateConfig_t stRotateConfig;
    MI_DISP_InputPortAttr_t stInputPortAttr;
    MI_DISP_VidWinRect_t stWinRect;
    MI_PANEL_IntfType_e eIntfType;
    MI_PANEL_ParamConfig_t pstParamCfg;

    MI_SYS_Init();

    //init panel
    eIntfType = E_MI_PNL_INTF_TTL;
    MI_PANEL_Init(eIntfType);

    // while (1)
    //     usleep(300000);

    MI_PANEL_GetPanelParam(eIntfType, &pstParamCfg);

    //config disp
    memset(&stPubAttr, 0, sizeof(MI_DISP_PubAttr_t));
    stPubAttr.u32BgColor = YUYV_BLACK;
    stPubAttr.eIntfSync = E_MI_DISP_OUTPUT_USER;
    stPubAttr.eIntfType = E_MI_DISP_INTF_TTL;
    MI_DISP_SetPubAttr(0, &stPubAttr);
    MI_DISP_Enable(0);

    memset(&stLayerAttr, 0, sizeof(MI_DISP_VideoLayerAttr_t));
    memset(&stRotateConfig, 0, sizeof(MI_DISP_RotateConfig_t));
    stLayerAttr.stVidLayerDispWin.u16X = 0;
    stLayerAttr.stVidLayerDispWin.u16Y = 0;
    stLayerAttr.stVidLayerDispWin.u16Width = pstParamCfg.u16Width;
    stLayerAttr.stVidLayerDispWin.u16Height = pstParamCfg.u16Height;
    MI_DISP_BindVideoLayer(0, 0);
    MI_DISP_SetVideoLayerAttr(0, &stLayerAttr);
    MI_DISP_EnableVideoLayer(0);

    stRotateConfig.eRotateMode = E_MI_DISP_ROTATE_NONE;
    MI_DISP_SetVideoLayerRotateMode(0, &stRotateConfig);

    memset(&stInputPortAttr, 0, sizeof(MI_DISP_InputPortAttr_t));
    stInputPortAttr.u16SrcWidth = DISP_INPUT_WIDTH;
    stInputPortAttr.u16SrcHeight = DISP_INPUT_HEIGHT;
    stInputPortAttr.stDispWin.u16X = 0;
    stInputPortAttr.stDispWin.u16Y = 0;
    stInputPortAttr.stDispWin.u16Width = pstParamCfg.u16Width;
    stInputPortAttr.stDispWin.u16Height = pstParamCfg.u16Height;
    MI_DISP_SetInputPortAttr(0, 0, &stInputPortAttr);
    MI_DISP_EnableInputPort(0, 0);

    return 0;
}

int sstar_disp_Deinit()
{
    MI_DISP_DisableInputPort(0, 0);
    MI_DISP_DisableVideoLayer(0);
    MI_DISP_UnBindVideoLayer(0, 0);
    MI_DISP_Disable(0);
    MI_PANEL_DeInit();
    MI_SYS_Exit();
    printf("sstar_disp_Deinit...\n");

    return 0;
}

#if defined(__cplusplus)||defined(c_plusplus)
}
#endif

