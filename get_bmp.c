#include <stdio.h>
#include <malloc.h>
#include "BmpFormat.h"

BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;

void showBmpHead(BITMAPFILEHEADER pBmpHead) 
{  //定义显示信息的函数，传入文件头结构体
    printf("BMP文件大小：%dkb\n", fileHeader.bfSize/1024);
    printf("保留字必须为0：%d\n",  fileHeader.bfReserved1);
    printf("保留字必须为0：%d\n",  fileHeader.bfReserved2);
    printf("实际位图数据的偏移字节数: %d\n",  fileHeader.bfOffBits);
}
void showBmpInfoHead(BITMAPINFOHEADER pBmpinfoHead) 
{//定义显示信息的函数，传入的是信息头结构体
   printf("位图信息头:\n" );   
   printf("信息头的大小:%d\n" ,infoHeader.biSize);   
   printf("位图宽度:%d\n" ,infoHeader.biWidth);   
   printf("位图高度:%d\n" ,infoHeader.biHeight);   
   printf("图像的位面数(位面数是调色板的数量,默认为1个调色板):%d\n" ,infoHeader.biPlanes);   
   printf("每个像素的位数:%d\n" ,infoHeader.biBitCount);   
   printf("压缩方式:%d\n" ,infoHeader.biCompression);   
   printf("图像的大小:%d\n" ,infoHeader.biSizeImage);   
   printf("水平方向分辨率:%d\n" ,infoHeader.biXPelsPerMeter);   
   printf("垂直方向分辨率:%d\n" ,infoHeader.biYPelsPerMeter);   
   printf("使用的颜色数:%d\n" ,infoHeader.biClrUsed);   
   printf("重要颜色数:%d\n" ,infoHeader.biClrImportant);
}

int main()
{
    FILE* fp,*ff;    
    fp = fopen("1.bmp", "rb");//读取同目录下的image.bmp文件。
    if(fp == NULL)
    {
        printf("打开'image.bmp'失败！\n");
        return -1;
    }
    //如果不先读取bifType，根据C语言结构体Sizeof运算规则——整体大于部分之和，从而导致读文件错位
    unsigned short  fileType;
    printf("%d\n",sizeof(unsigned short));
    fread(&fileType,sizeof (unsigned short), 1,fp);  
    if (fileType = 0x4d42)   
    {   
        printf("文件类型标识正确!" );  
        printf("\n文件标识符：%d\n", fileType); 
        fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
        showBmpHead(fileHeader);
        fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
        showBmpInfoHead(infoHeader);
        PixelInfo **pix;
        int i,j;
        pix=(PixelInfo**)malloc(sizeof(PixelInfo*)*infoHeader.biHeight);
        for(i=0;i<infoHeader.biHeight;i++)
			*(pix+i)=(PixelInfo*)malloc(sizeof(PixelInfo)*infoHeader.biWidth);
		for(i=0;i<infoHeader.biHeight;i++)
			for(j=0;j<infoHeader.biWidth;j++)
				fread(*(pix+i)+j,sizeof(PixelInfo),1,fp);
		//pix[1][1].rgbBlue=~pix[1][1].rgbBlue;
		PixelInfo sta=pix[1][511];
		printf("%02x %02x %02x\n",sta.rgbBlue,sta.rgbGreen,sta.rgbRed);
		//printf("%d %d\n",infoHeader.biHeight,infoHeader.biWidth);
		for(i=0;i<infoHeader.biHeight;i++)
			for(j=0;j<infoHeader.biWidth;j++){ 
				if(pix[i][j].rgbBlue==sta.rgbBlue&&pix[i][j].rgbGreen==sta.rgbGreen&&pix[i][j].rgbRed==sta.rgbRed){
					pix[i][j].rgbBlue=~pix[i][j].rgbBlue;
					pix[i][j].rgbGreen=~pix[i][j].rgbGreen;
					pix[i][j].rgbRed=~pix[i][j].rgbRed;
				}
			}
		//printf("%02x %02x %02x\n",pix[1][1].rgbBlue,pix[1][1].rgbGreen,pix[1][1].rgbRed);
		ff=fopen("2.bmp","wb");
		fwrite(&fileType,sizeof(unsigned short),1,ff);
		fwrite(&fileHeader,sizeof(BITMAPFILEHEADER),1,ff);
		fwrite(&infoHeader,sizeof(BITMAPINFOHEADER),1,ff);
		for(i=0;i<infoHeader.biHeight;i++)
			for(j=0;j<infoHeader.biWidth;j++)
				fwrite(*(pix+i)+j,sizeof(PixelInfo),1,ff);
        fclose(fp);
        fclose(ff);
    }
}
