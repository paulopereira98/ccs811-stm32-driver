# ccs811-stm32-driver
Driver for the ccs811 sensor for stm32.

&nbsp;
&nbsp;
&nbsp;

### [Open Documentation]( http://paulopereira98.github.io/ccs811-stm32-driver/ccs811_8h.html)
&nbsp;
### How to use:

##### Set the handler and I2C address for the sensor:
```c
/* ccs811.h */
#define CCS811_I2C_ADDR 0x5A
#define CCS811_I2C_HANDLER hi2c2
```

##### Call the ccs811_init() function on startup
```c
/* main.c */
int main(void)
{
  /* ... */
  
  ccs811_init();
  
  /* ... */
}
```


##### If possible calibrate the sensor using temperature and humidity measurements:
```c

  ccs811_temp_rh_compensation(temp, rh);

```
