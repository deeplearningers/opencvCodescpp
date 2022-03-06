int rectifyImages(const char* ImageOrigFolderPath, const char* LutXFolderPath, const char* LutYFolderPath, const char* Type);
int Number2FixedDigitChar(int num, int digitNum, char* fixedChar);
int saveData2Bmp(unsigned char* imageData, int width, int height, char* path);
int saveData2Hex(unsigned char* imageData, int width, int height, char* path);
int saveData2Raw(unsigned char* imageData, int width, int height, char* path);
int readDataFromBmp(unsigned char* imageData, int width, int height, char* path);
int readDataFromHex(unsigned char* imageData, int width, int height, char* path);
int readDataFromRaw(unsigned char* imageData, int width, int height, char* path);
int readLUTFromFile(double* lut, int width, int height, char* path);
double* readLUTFromBinFile(int* width, int* height, char* path);
double sign_vision(double inputNum);
double FP(double inputNum, int bitNum);
double PFP(double inputNum, int bitNum, int powerNum);
int  imageCorrection(unsigned char* srcImData, unsigned short width, unsigned short height,
	double* lut_X, double* lut_Y, unsigned char* dstImData);
int  imageCorrection_debug(unsigned char* srcImData, unsigned short width, unsigned short height,
	double* lut_X, double* lut_Y, unsigned char* dstImData);
int biLinear_3bit(unsigned char* srcImData, unsigned short width, unsigned short height, double idealX, double idealY, int* gt);
int biLinear(unsigned char* srcImData, unsigned short width, unsigned short height, float idealX, float idealY, int* gt);
int clearFolder(const char* folderPath);
int readLUTFromUbootBinFile(int* width, int* height, char* path, double* lut_X, double* lut_Y);
