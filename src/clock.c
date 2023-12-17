#include "clock.h"
  
static void imx8mm_osc_init(T_PLL_SRC tPllSrc, T_OSC_TYPEDEF *ptOsc);

uint32_t_t imx8mm_clk_init(T_CLOCK_TYPEDEF *ptClk)
{
    if (NULL == ptClk)
    {
        return -1;
    }

    if (ptClk->tPllSrc == PLL_SRC_XTAL1 || PLL_SRC_XTAL2 == ptClk->tPllSrc)
    {
        imx8mm_osc_init(ptClk->tPllSrc, &ptClk->tOscTypeDef);
    }

    //sys_pll_init();

    return 0;
}

static void imx8mm_osc_init(T_PLL_SRC tPllSrc, T_OSC_TYPEDEF *ptOsc)
{
    T_OSC_REG *ptOscReg = NULL;
    uint32_t uiRegVal = 0;

    if (tPllSrc == PLL_SRC_XTAL1)
    {
        ptOscReg = (T_OSC_REG *)XTAL1_REG_BASE;
    }
    else
    {
        ptOscReg = (T_OSC_REG *)XTAL2_REG_BASE;
    }

    uiRegVal = ((ptOsc->tOscMode)<<31);

    ptOscReg->uiXtalCfg = uiRegVal;
}

void imx8mm_clk_ccgr_set(T_CCGR_INDEX eCcgrIdx, uint8_t ucIsEnable)
{
	volatile T_CCGR_TYPEDEF *ptCcgrReg = NULL;

	switch(eCcgrIdx)
	{
		case CCGR_UART1:
		{
			ptCcgrReg = (volatile T_CCGR_TYPEDEF * )0x30384490;
			break;
		}

		case CCGR_UART2:
		{
			ptCcgrReg = (volatile T_CCGR_TYPEDEF * )0x303844A0;
			break;
		}

		case CCGR_UART3:
		{
			ptCcgrReg = (volatile T_CCGR_TYPEDEF * )0x303844B0;
			break;
		}

		case CCGR_UART4:
		{
			ptCcgrReg = (volatile T_CCGR_TYPEDEF * )0x303844C0;
			break;
		}

		case CCGR_GIC:
		{
			ptCcgrReg = (volatile T_CCGR_TYPEDEF * )0x303845C0;
			break;
		}
			
		case CCGR_DRAM1:
		{
			ptCcgrReg = (volatile T_CCGR_TYPEDEF *)0x30384050;
			break;
		}
			
		default:
		{
			return;
		}
	}

	if (ucIsEnable == 0)
	{
		ptCcgrReg->uiCcgrClr = 0x03;
	}
	else
	{
		ptCcgrReg->uiCcgrSet = 0x03;
	}
}

static void imx8mm_clk_pll_set(T_PLL_INDEX ePllIdx, uint8_t ucIsEnable)
{
	volatile T_PLL_CTRL *ptPllCtrl = NULL;

	switch(ePllIdx)
	{
		case ARM_PLL_CLK:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x303808C0;
			break;
		}

		case SYS_PLL1_CLK:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x30380900;
			break;
		}

		case SYS_PLL1_DIV2:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x30380910;
			break;
		}

		case SYS_PLL1_DIV3:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x30380920;
			break;
		}

		case SYS_PLL1_DIV4:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380930;
			break;
	    }

		case SYS_PLL1_DIV5:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380940;
			break;
	    }

		case SYS_PLL1_DIV6:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380950;
			break;
	    }

		case SYS_PLL1_DIV8:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380960;
			break;
	    }

		case SYS_PLL1_DIV10:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380970;
			break;
	    }

		case SYS_PLL1_DIV20:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380980;
			break;
	    }

		case SYS_PLL2_CLK:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x30380990;
			break;
		}

		case SYS_PLL2_DIV2:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x303809a0;
			break;
		}

		case SYS_PLL2_DIV3:
		{
			ptPllCtrl = (volatile T_PLL_CTRL * )0x303809b0;
			break;
		}

		case SYS_PLL2_DIV4:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x303809c0;
			break;
	    }

		case SYS_PLL2_DIV5:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x303809d0;
			break;
	    }

		case SYS_PLL2_DIV6:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x303809e0;
			break;
	    }

		case SYS_PLL2_DIV8:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x303809F0;
			break;
	    }

		case SYS_PLL2_DIV10:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380A00;
			break;
	    }

		case SYS_PLL2_DIV20:
		{
			ptPllCtrl = (volatile T_PLL_CTRL*) 0x30380A10;
			break;
	    }

		default:
		{
			return;
		}
	}

	if (ucIsEnable == 0)
	{
		ptPllCtrl->uiPllCtrlClr = 0x03;
	}
	else
	{
		ptPllCtrl->uiPllCtrlSet = 0x03;
	}
}

void _delay(uint32_t_t uiDelay)
{
	while(uiDelay--);
}

void sys_pll_init()
{
	volatile T_SYS_PLL_REG *ptPll1Reg = (volatile T_SYS_PLL_REG *)0x30360030;
    volatile T_SYS_PLL_REG *ptPll2Reg  = (volatile T_SYS_PLL_REG *)0x3036003C;
    volatile unsigned int *puiGpioData = (volatile unsigned int *)0x30220000;
	uint32_t_t uiValCfg0 = 0;
	int ret = 0;

    ptPll1Reg->uiSysCfg0 |= (1<<23)|(1<<21)|(1<<19)|(1<<17)|\
							 (1<<15)|(1<<13)|(1<<11)|(1<<9);
	 
	ptPll1Reg->uiSysCfg0 |= 0x20 | 0x10;
	ptPll1Reg->uiSysCfg2 = (3<<13)|(3<<7);
	ptPll1Reg->uiSysCfg1 =0;
	 
	uiValCfg0 =  (1<<25)|(1<<23)|(1<<21)|(1<<19)|(1<<17)|\
				  (1<<15)|(1<<13)|(1<<11)|(1<<9)| (1<<3);
	
	ptPll1Reg->uiSysCfg0 = uiValCfg0 | 0x10;

	
	ptPll1Reg->uiSysCfg0 = uiValCfg0;
	 
	while(1)
	{
		ret = ((ptPll1Reg->uiSysCfg0)>>31) & 0x01;
        if (ret)
        {
            break;
        }
	}	
	
//	my_printf("pll1 cfg0:0x%x\r\n",ptPll1Reg->uiSysCfg0);
	ptPll2Reg->uiSysCfg0 |= (1<<23)|(1<<21)|(1<<19)|(1<<17)|\
							(1<<15)|(1<<13)|(1<<11)|(1<<9);
	
	ptPll2Reg->uiSysCfg0 |= 0x20 | 0x10;
	ptPll2Reg->uiSysCfg2 = (3<<13)|(4<<7);
	ptPll2Reg->uiSysCfg1 =0;
	
	uiValCfg0 =  (1<<25)|(1<<23)|(1<<21)|(1<<19)|(1<<17)|\
				 (1<<15)|(1<<13)|(1<<11)|(1<<9)| (1<<3);
	
	ptPll2Reg->uiSysCfg0 = uiValCfg0 | 0x10;

	
	ptPll2Reg->uiSysCfg0 = uiValCfg0;
	
  
	
	while(1)
	{
		ret = ((ptPll2Reg->uiSysCfg0)>>31) & 0x01;
        if (ret)
        {
            break;
        }
	}	
//	my_printf("pll2 cfg0:0x%x\r\n",ptPll2Reg->uiSysCfg0);	
}

void ahb_ipg_clk_init()
{
	volatile uint32_t *puiAhbClkTarget = (volatile uint32_t *) 0x30389000;

	//imx8mm_clk_ccgr_set(tCcgrIdx, 0);
	*puiAhbClkTarget = (1<<28)|(4<<24); //0<<24
	//imx8mm_clk_ccgr_set(tCcgrIdx, 0);
}

void uart_clk_init(E_IMX8M_UART eUart)
{
	volatile uint32_t *puiUartClkTarget = NULL;
	T_CCGR_INDEX tCcgrIdx;

	switch(eUart)
	{
		case UART1:
		{
			puiUartClkTarget = (volatile uint32_t *)0x3038AF00;
			tCcgrIdx = CCGR_UART1;
			break;
		}

		case UART2:
		{
			puiUartClkTarget = (volatile uint32_t *)0x3038AF80;
			tCcgrIdx = CCGR_UART2;
			break;
		}

		case UART3:
		{
			puiUartClkTarget = (volatile uint32_t *)0x3038B000;
			tCcgrIdx = CCGR_UART3;
			break;
		}

		case UART4:
		{
			puiUartClkTarget = (volatile uint32_t *)0x3038B080;
			tCcgrIdx = CCGR_UART4;
			break;
		}

		default:
		{
			return;
		}
	}

	imx8mm_clk_ccgr_set(tCcgrIdx, 0);
	*puiUartClkTarget = (1<<28)|(1<<24); //(0<<24);//
	imx8mm_clk_ccgr_set(tCcgrIdx, 1);
}

void gic_clk_init()
{
	volatile uint32_t *puiGicClkTarget = (volatile uint32_t *)0x3038B200;
	/* targer 100,selcect 1:pll2_div5 200M */
	imx8mm_clk_ccgr_set(CCGR_GIC, 0);
	*puiGicClkTarget = (1<<28)|(1<<24);
	imx8mm_clk_ccgr_set(CCGR_GIC, 1);
}



static void osc_init(void)
{
    volatile unsigned int *ptXtal1Cfg = (volatile unsigned int *)0x30270000;//XTALOSC_OSC25M_CTL_CFG
    *ptXtal1Cfg &= (~(0<<31)); // Oscillator output is used as root clock.
    *ptXtal1Cfg |= (0xff<<16); 
}

static void arm_clock_init(unsigned int src_freq)
{
    /* pllout=1000MHZ 
       pllout = src_freq/DIVR_VAL * 8 * (1+DIVFI+(DIVFF/2^24))/DIVQ_VAL
       src_freq=24MHZ
       DIVR_VAL=12
       DIVFI=124
    */
    int ret = 0;
    
    volatile unsigned int *ptPllCfg0 = (volatile unsigned int *)0x30360028; //ARM PLL Configuration 0 Register
    volatile unsigned int *ptPllCfg1 = (volatile unsigned int *)0x3036002c; //ARM PLL Configuration 1 Register
    volatile unsigned int *puiArmTarget = (volatile unsigned int *)0x30388000; //Target Register (CCM_TARGET_ROOT0)

    imx8mm_clk_ccgr_set(CCGR_SCTR, 1);

    *ptPllCfg1 = 0x7c;
    *ptPllCfg0 = (1<<21)|(0<<16)|(1<<15)|(1<<12)|(12<<5)|(0<<0);
#if 1
    while(1)
    {
        ret = ((*ptPllCfg0)>>31) & 0x01;
        if (ret)
        {
            break;
        }
    }
#endif

    *ptPllCfg0 &= ~(1<<12);

    *puiArmTarget = (1<<28)|(1<<24);
    
}



void Delay(unsigned int delay)
{
	while(delay--);
}

void clk_init(void)
{
volatile unsigned int *puiCcgrSctrSet = (volatile unsigned int *)0x30384394;

	osc_init();
    arm_clock_init(25000000);
 

	sys_pll_init();

	ahb_ipg_clk_init();

	uart_clk_init(UART1);

	puiCcgrSctrSet = 0x03;	
}