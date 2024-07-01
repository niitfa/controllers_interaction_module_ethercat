#ifndef COE_OBJECT_NAMES_H
#define COE_OBJECT_NAMES_H

#include <string>

namespace coe_object_names
{
    /* CoE Drive */
    const std::string kControlword = "Controlword";
    const std::string kModeOfOperation = "Mode of operation";
    const std::string kTargetPosition = "Target position";
    const std::string kStatusword = "Statusword";
    const std::string kModeOfOperationOut = "Mode of operation out";
    const std::string kActualPosition = "Actual position";
    const std::string kMaxProfileVelocity = "Max profile velocity";
    const std::string kProfileVelocity = "Profile velocity";
	const std::string kTargetVelocity = "Target velocity";
    const std::string kProfileAcceleration = "Profile acceleration";
    const std::string kProfileDeceleration = "Profile deceleration";
    const std::string kActualVelocity = "Actual velocity";
    const std::string kMicrostepResolution = "Microstep resolution";
	const std::string kPeakCurrent = "Peak current";
	const std::string kDigitalInputs = "Digital inputs";

    /* IO Module ODOT CT-3168 */
 	const std::string kCT3168_AI0 = "AI#0 CT-3168";
 	const std::string kCT3168_AI1 = "AI#1 CT-3168";
 	const std::string kCT3168_AI2 = "AI#2 CT-3168";
 	const std::string kCT3168_AI3 = "AI#3 CT-3168";
 	const std::string kCT3168_AI4 = "AI#4 CT-3168";
 	const std::string kCT3168_AI5 = "AI#5 CT-3168";
 	const std::string kCT3168_AI6 = "AI#6 CT-3168";
 	const std::string kCT3168_AI7 = "AI#7 CT-3168";

     /* IO Module ODOT CT-623F */
 	const std::string kCT632F_DI0 = "DI#0 CT-623F";  
 	const std::string kCT632F_DI1 = "DI#1 CT-623F";        
 	const std::string kCT632F_DI2 = "DI#2 CT-623F";  
 	const std::string kCT632F_DI3 = "DI#3 CT-623F"; 
    const std::string kCT632F_DI4 = "DI#4 CT-623F";  
 	const std::string kCT632F_DI5 = "DI#5 CT-623F";        
 	const std::string kCT632F_DI6 = "DI#6 CT-623F";  
 	const std::string kCT632F_DI7 = "DI#7 CT-623F";

    const std::string kCT632F_DO0 = "DO#0 CT-623F";  
 	const std::string kCT632F_DO1 = "DO#1 CT-623F";        
 	const std::string kCT632F_DO2 = "DO#2 CT-623F";  
 	const std::string kCT632F_DO3 = "DO#3 CT-623F"; 
    const std::string kCT632F_DO4 = "DO#4 CT-623F";  
 	const std::string kCT632F_DO5 = "DO#5 CT-623F";        
 	const std::string kCT632F_DO6 = "DO#6 CT-623F";  
 	const std::string kCT632F_DO7 = "DO#7 CT-623F";      
}

#endif