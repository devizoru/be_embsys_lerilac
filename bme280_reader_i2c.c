#include "bme280.h"
struct bme280_dev dev;
int8_t rslt = BME280_OK;
uint8_t dev_addr = BME280_I2C_ADDR_PRIM;
dev.intf_ptr = &dev_addr;
dev.intf = BME280_I2C_INTF;
dev.read = user_i2c_read;
dev.write = user_i2c_write;
dev.delay_ms = user_delay_ms;

rslt = bme280_init(&dev);

int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev)
{
    int8_t rslt;
    uint8_t settings_sel;
    struct bme280_data comp_data;

    /* Recommended mode of operation: Indoor navigation */
    dev->settings.osr_h = BME280_OVERSAMPLING_1X;
    dev->settings.osr_p = BME280_OVERSAMPLING_16X;
    dev->settings.osr_t = BME280_OVERSAMPLING_2X;
    dev->settings.filter = BME280_FILTER_COEFF_16;
    dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

    settings_sel = BME280_OSR_PRESS_SEL;
    settings_sel |= BME280_OSR_TEMP_SEL;
    settings_sel |= BME280_OSR_HUM_SEL;
    settings_sel |= BME280_STANDBY_SEL;
    settings_sel |= BME280_FILTER_SEL;
    rslt = bme280_set_sensor_settings(settings_sel, dev);
    rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

    printf("Temperature, Pressure, Humidity\r\n");
    while (1)
    {
        /* Delay while the sensor completes a measurement */
        dev->delay_ms(70000, dev->intf_ptr);
        rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
        print_sensor_data(&comp_data);
    }

    return rslt;
}

void print_sensor_data(struct bme280_data *comp_data)
{
#ifdef BME280_FLOAT_ENABLE
    printf("%0.2f, %0.2f, %0.2f\r\n", comp_data->temperature, comp_data->pressure, comp_data->humidity);
#else
    printf("%ld, %ld, %ld\r\n", comp_data->temperature, comp_data->pressure, comp_data->humidity);
#endif
}

void user_delay_ms(uint32_t period, void *intf_ptr)
{
    /*
     * Return control or wait,
     * for a period amount of milliseconds
     */
}

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    /*
     * The parameter intf_ptr can be used as a variable to store the I2C address of the device
     */

    /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Stop       | -                   |
     * | Start      | -                   |
     * | Read       | (reg_data[0])       |
     * | Read       | (....)              |
     * | Read       | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */

    return rslt;
}

int8_t user_i2c_write(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    /*
     * The parameter intf_ptr can be used as a variable to store the I2C address of the device
     */

    /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Write      | (reg_data[0])       |
     * | Write      | (....)              |
     * | Write      | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */

    return rslt;
}