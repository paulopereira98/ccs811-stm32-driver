#include "ccs811.h"
#include "i2c.h"
#include "cmsis_os.h"

/**
  * @brief  initialization process for the ccs811 sensor
  * @retval None
  */
void ccs811_init(void)
{
	uint8_t startup_conf = APP_START;
	uint8_t meas_mode_conf = 0;
	meas_mode_conf = DRIVE_MODE(DRIVE_MODE_MODE1);

	HAL_I2C_Master_Transmit(&CCS811_I2C_HANDLER, CCS811_I2C_ADDR<<1, &startup_conf, 1, 100);		//start application
	HAL_Delay(1);
	HAL_I2C_Mem_Write(&CCS811_I2C_HANDLER, CCS811_I2C_ADDR<<1, MEAS_MODE, I2C_MEMADD_SIZE_8BIT, &meas_mode_conf, 1, 100); //configure
	HAL_Delay(1);
	ccs811_temp_rh_compensation(20.0, 20.0);
}

/**
  * @brief  read sensor i2c co2 register
  * @retval CO2 concentration in ppb
  */
uint32_t ccs811_measureCO2(void)
{
	uint32_t co2 = 0;
	uint32_t tvoc = 0;
	ccs811_measure_CO2_TVOC(&co2, &tvoc);
	return co2;
}

/**
  * @brief  read sensor i2c tvoc register
  * @retval TVOC concentration in ppb
  */
uint32_t ccs811_measureTVOC(void)
{
	uint32_t co2 = 0;
	uint32_t tvoc = 0;
	ccs811_measure_CO2_TVOC(&co2, &tvoc);
	return tvoc;
}

/**
  * @brief  read sensor i2c co2 and tvoc registers
  * @retval None
  */
void ccs811_measure_CO2_TVOC(uint32_t *co2, uint32_t *tvoc)
{
		uint8_t alg_result[4] = {0};
		uint32_t aux_co2;
		uint32_t aux_tvoc;

		HAL_I2C_Mem_Read(&CCS811_I2C_HANDLER, CCS811_I2C_ADDR<<1, ALG_RESULT_DATA, I2C_MEMADD_SIZE_8BIT, alg_result, 4, 100);
		
		aux_co2 = alg_result[1] + (alg_result[0]<<8);		//co2 in ppm
		aux_tvoc = alg_result[2] + (alg_result[3]<<8);	//tvoc in ppb

		*co2 = aux_co2 * 1000;	//co2 in ppb
		*tvoc = aux_tvoc;				//tvoc in ppb
}

/**
  * @brief  write temperature and humidity in i2c registers for compensation
  * @retval None
  */
void ccs811_temp_rh_compensation(float temp, float rh)
{
		uint8_t env_data[4] = {0};
		
		env_data[0] = (( (uint32_t)(rh*512) ) & 0xFF00)>>8;		//humidity high byte
		env_data[1] = (( (uint32_t)(rh*512) ) & 0x00FF);		//humidity low byte
		
		env_data[2] = (( (uint32_t)(rh*512)-25 ) & 0xFF00)>>8;	//temperature high byte
		env_data[3] = (( (uint32_t)(rh*512)-25 ) & 0x00FF);		//temperature low byte
		
		HAL_I2C_Mem_Write(&CCS811_I2C_HANDLER, CCS811_I2C_ADDR<<1, ENV_DATA, I2C_MEMADD_SIZE_8BIT, env_data, 4, 100);
}
