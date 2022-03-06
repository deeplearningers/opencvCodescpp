#include "rectifyImage.h"

#define LUT_LEFT_X_PATH "F:/calibration/20180611/CalibFolder_NEXK0016/CalibrationOutput/Calibration_Latest"
#define LUT_LEFT_Y_PATH "F:/calibration/20180611/CalibFolder_NEXK0016/CalibrationOutput/Calibration_Latest/FusionRectifyParams.bin"
#define LUT_RIGHT_X_PATH "F:/calibration/20180611/CalibFolder_NEXK0016/CalibrationOutput/Calibration_Latest/FusionRectifyParams.bin"
#define LUT_RIGHT_Y_PATH "F:/calibration/20180611/CalibFolder_NEXK0016/CalibrationOutput/Calibration_Latest/FusionRectifyParams.bin"

#define IMAGE_ORIG_FOLDER_PATH "F:\calibration\20180611\CalibFolder_NEXK0016"

int main(){

	//clearFolder(IMAGE_RECT_FOLDER_PATH);

	rectifyImages(IMAGE_ORIG_FOLDER_PATH, LUT_LEFT_X_PATH, LUT_LEFT_Y_PATH, "L");

	rectifyImages(IMAGE_ORIG_FOLDER_PATH, LUT_RIGHT_X_PATH, LUT_RIGHT_Y_PATH, "R");
}
