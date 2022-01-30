// ���ܣ����� 4-2 ˫���Բ�ֵʵ��
// ���ߣ���ΰ zhu1988wei@163.com
// ��Դ����OpenCVͼ������ʵ����
// ���ͣ�http://blog.csdn.net/zhuwei1988
// ���£�2016-8-1
// ˵������Ȩ���У����û�ժ¼����ϵ���ߣ������������ʽע��������лл��// 
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 
// ʵ��˫���Բ�ֵͼ������
cv::Mat BilinearInterpolation(cv::Mat srcImage)
{
	CV_Assert(srcImage.data != NULL);
	int srcRows = srcImage.rows;
	int srcCols = srcImage.cols;
	int srcStep = srcImage.step;
	// ����Ŀ��ͼ��
	cv::Mat dstImage = cv::Mat(
		cv::Size(150, 150), srcImage.type(),
		cv::Scalar::all(0));
	int dstRows = dstImage.rows;
	int dstCols = dstImage.cols;
	int dstStep = dstImage.step;
	// ���ݶ��弰ת��
	IplImage src = srcImage;
	IplImage dst = dstImage;
	std::cout << "srcCols:" << srcCols << " srcRows:" <<
		srcRows << "srcStep:" << srcStep << std::endl;
	std::cout << "dstCols:" << dstCols << " dstRows:" <<
		dstRows << "dstStep:" << dstStep << std::endl;
	// ���궨��
	float srcX = 0, srcY = 0;
	float t1X = 0, t1Y = 0, t1Z = 0;
	float t2X = 0, t2Y = 0, t2Z = 0;
	for (int j = 0; j < dstRows - 1; j++)
	{
		for (int i = 0; i < dstCols - 1; i++)
		{
			// ����ӳ���ϵ 
			srcX = (i + 0.5)*((float)srcCols) / (dstCols)-0.5;
			srcY = (j + 0.5)*((float)srcRows) / (dstRows)-0.5;
			int iSrcX = (int)srcX;
			int iSrcY = (int)srcY;
			// ��ͨ���������Ȩֵ1
			t1X = ((uchar*)(src.imageData + srcStep*iSrcY))[
				iSrcX * 3 + 0] * (1 - std::abs(srcX - iSrcX)) +
					((uchar*)(src.imageData + srcStep*iSrcY))[
						(iSrcX + 1) * 3 + 0] * (srcX - iSrcX);
						t1Y = ((uchar*)(src.imageData + srcStep*iSrcY))[
							iSrcX * 3 + 1] * (1 - std::abs(srcX - iSrcX)) +
								((uchar*)(src.imageData + srcStep*iSrcY))[
									(iSrcX + 1) * 3 + 1] * (srcX - iSrcX);
									t1Z = ((uchar*)(src.imageData + srcStep*iSrcY))[
										iSrcX * 3 + 2] * (1 - std::abs(srcX - iSrcX)) +
											((uchar*)(src.imageData + srcStep*iSrcY))[
												(iSrcX + 1) * 3 + 2] * (srcX - iSrcX);
												// ��ͨ���������Ȩֵ2
												t2X = ((uchar*)(src.imageData + srcStep*(
													iSrcY + 1)))[iSrcX * 3] * (1 - std::abs(srcX - iSrcX))
													+ ((uchar*)(src.imageData + srcStep*(
													iSrcY + 1)))[(iSrcX + 1) * 3] * (srcX - iSrcX);
												t2Y = ((uchar*)(src.imageData + srcStep*(
													iSrcY + 1)))[iSrcX * 3 + 1] * (1 - std::abs(srcX - iSrcX))
													+ ((uchar*)(src.imageData + srcStep*(
													iSrcY + 1)))[(iSrcX + 1) * 3 + 1] * (srcX - iSrcX);
												t2Z = ((uchar*)(src.imageData + srcStep*(
													iSrcY + 1)))[iSrcX * 3 + 2] * (1 - std::abs(srcX - iSrcX))
													+ ((uchar*)(src.imageData + srcStep*(iSrcY + 1)))[(
													iSrcX + 1) * 3 + 2] * (srcX - iSrcX);
												// ���ݹ�ʽ���Ŀ��ͼ���Ȩ
												((uchar*)(dst.imageData + dstStep*j))[i * 3] =
													t1X*(1 - std::abs(srcY - iSrcY)) + t2X*(
													std::abs(srcY - iSrcY));
												((uchar*)(dst.imageData + dstStep*j))[i * 3 + 1] =
													t1Y*(1 - std::abs(srcY - iSrcY)) + t2Y*(
													std::abs(srcY - iSrcY));
												((uchar*)(dst.imageData + dstStep*j))[i * 3 + 2] =
													t1Z*(1 - std::abs(srcY - iSrcY)) + t2Z*(
													std::abs(srcY - iSrcY));
		}
		// �в���
		((uchar*)(dst.imageData + dstStep*j))[(dstCols - 1) * 3] =
			((uchar*)(dst.imageData + dstStep*j))[(dstCols - 2) * 3];
		((uchar*)(dst.imageData + dstStep*j))[(dstCols - 1) * 3 +
			1] = ((uchar*)(dst.imageData + dstStep*j))[(
			dstCols - 2) * 3 + 1];
		((uchar*)(dst.imageData + dstStep*j))[(dstCols - 1) * 3
			+ 2] = ((uchar*)(dst.imageData + dstStep*j))[(
			dstCols - 2) * 3 + 2];
	}
	// �в���
	for (int i = 0; i < dstCols * 3; i++)
	{
		((uchar*)(dst.imageData + dstStep*(dstRows - 1)))[i] =
			((uchar*)(dst.imageData + dstStep*(dstRows - 2)))[i];
	}
	return  dstImage;
}
int main()
{
	cv::Mat srcImage = cv::imread("..\\images\\flower3.jpg");
	if (!srcImage.data)
		return -1;
	cv::Mat dstImage = BilinearInterpolation(srcImage);
	cv::imshow("srcImage", srcImage);
	cv::imshow("dstImage", dstImage);
	cv::waitKey(0);
	return 0;
}
