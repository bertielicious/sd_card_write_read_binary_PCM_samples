idf_component_register(SRCS "init_sd_card.c" "main.c"
                    REQUIRES fatfs sdmmc driver
                    INCLUDE_DIRS ".")
