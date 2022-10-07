# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\HPz420\Documents\GitHub\land-boards\RasPi\RPI_PSOC5\RPI_PSOC5_CARD_TEST_STATION.cydsn\RPI_PSOC5_CARD_TEST_STATION.cyprj
# Date: Thu, 06 Oct 2022 23:10:58 GMT
#set_units -time ns
create_clock -name {Clock_1(routed)} -period 655360000 -waveform {0 327680000} [list [get_pins {ClockBlock/dclk_1}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 15.625 -waveform {0 7.8125} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 15.625 -waveform {0 7.8125} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/clk_sync}] -edges {1 11 21} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 41943041 83886081} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_clock -name {CyScBoostClk} -period 93.75 -waveform {0 46.875} [list [get_pins {ClockBlock/aclk_glb_0}]]


# Component constraints for C:\Users\HPz420\Documents\GitHub\land-boards\RasPi\RPI_PSOC5\RPI_PSOC5_CARD_TEST_STATION.cydsn\TopDesign\PSoC5\TopDesign.cysch
# Project: C:\Users\HPz420\Documents\GitHub\land-boards\RasPi\RPI_PSOC5\RPI_PSOC5_CARD_TEST_STATION.cydsn\RPI_PSOC5_CARD_TEST_STATION.cyprj
# Date: Thu, 06 Oct 2022 23:10:51 GMT
