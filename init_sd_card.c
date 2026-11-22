#include "constants.h"
esp_err_t init_sd_card(void)
{
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };

    sdmmc_card_t *card;

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = 23,
        .miso_io_num = 19,
        .sclk_io_num = 18,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000
    };

    ESP_ERROR_CHECK(spi_bus_initialize(
        SPI2_HOST,
        &bus_cfg,
        SPI_DMA_CH_AUTO));

    sdspi_device_config_t slot_config =
        SDSPI_DEVICE_CONFIG_DEFAULT();

    slot_config.gpio_cs = 13;
    slot_config.host_id = SPI2_HOST;

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();

    esp_err_t ret = esp_vfs_fat_sdspi_mount(
        "/sdcard",
        &host,
        &slot_config,
        &mount_config,
        &card);

    if (ret == ESP_OK)
    {
        printf("SD card mounted\n");
        sdmmc_card_print_info(stdout, card);
    }

    return ret;
}