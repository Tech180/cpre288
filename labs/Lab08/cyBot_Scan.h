#ifndef CYBOT_SCAN_H_
#define CYBOT_SCAN_H_


// Scan value
typedef struct{
	float sound_dist;  // Distance from Ping Sensor
	int IR_raw_val;    // Raw ADC value from IR sensor
} cyBOT_Scan_t;


// Initialize cyBot Scan sensors and servo
void cyBOT_init_Scan(void);

// Rotate sensors to specified angle, and get a scan value 
//(Note: It is OK that this is not calabrated to 0 - 180 degrees)
// (You will calibrate your version in Lab 8)
void cyBOT_Scan(int angle, cyBOT_Scan_t* getScan);


#endif /* CYBOT_SCAN_H_ */
