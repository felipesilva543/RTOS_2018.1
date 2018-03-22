#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /home/felipe/ti/bios_6_52_00_12/packages;/home/felipe/ti/pdk_am335x_1_0_9/packages;/home/felipe/ti/edma3_lld_2_12_05_30B/packages;/home/felipe/ti/ndk_2_26_00_08/packages;/home/felipe/ti/ccsv7/ccs_base
override XDCROOT = /home/felipe/ti/xdctools_3_50_03_33_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /home/felipe/ti/bios_6_52_00_12/packages;/home/felipe/ti/pdk_am335x_1_0_9/packages;/home/felipe/ti/edma3_lld_2_12_05_30B/packages;/home/felipe/ti/ndk_2_26_00_08/packages;/home/felipe/ti/ccsv7/ccs_base;/home/felipe/ti/xdctools_3_50_03_33_core/packages;..
HOSTOS = Linux
endif
