#include <stdio.h>
#include <malloc.h>
#include "BmpFormat.h"

BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;

void showBmpHead(BITMAPFILEHEADER pBmpHead) 
{  //������ʾ��Ϣ�ĺ����������ļ�ͷ�ṹ��
    printf("BMP�ļ���С��%dkb\n", fileHeader.bfSize/1024);
    printf("�����ֱ���Ϊ0��%d\n",  fileHeader.bfReserved1);
    printf("�����ֱ���Ϊ0��%d\n",  fileHeader.bfReserved2);
    printf("ʵ��λͼ���ݵ�ƫ���ֽ���: %d\n",  fileHeader.bfOffBits);
}
void showBmpInfoHead(BITMAPINFOHEADER pBmpinfoHead) 
{//������ʾ��Ϣ�ĺ��������������Ϣͷ�ṹ��
   printf("λͼ��Ϣͷ:\n" );   
   printf("��Ϣͷ�Ĵ�С:%d\n" ,infoHeader.biSize);   
   printf("λͼ���:%d\n" ,infoHeader.biWidth);   
   printf("λͼ�߶�:%d\n" ,infoHeader.biHeight);   
   printf("ͼ���λ����(λ�����ǵ�ɫ�������,Ĭ��Ϊ1����ɫ��):%d\n" ,infoHeader.biPlanes);   
   printf("ÿ�����ص�λ��:%d\n" ,infoHeader.biBitCount);   
   printf("ѹ����ʽ:%d\n" ,infoHeader.biCompression);   
   printf("ͼ��Ĵ�С:%d\n" ,infoHeader.biSizeImage);   
   printf("ˮƽ����ֱ���:%d\n" ,infoHeader.biXPelsPerMeter);   
   printf("��ֱ����ֱ���:%d\n" ,infoHeader.biYPelsPerMeter);   
   printf("ʹ�õ���ɫ��:%d\n" ,infoHeader.biClrUsed);   
   printf("��Ҫ��ɫ��:%d\n" ,infoHeader.biClrImportant);
}

int main()
{
    FILE* fp,*ff;    
    fp = fopen("1.bmp", "rb");//��ȡͬĿ¼�µ�image.bmp�ļ���
    if(fp == NULL)
    {
        printf("��'image.bmp'ʧ�ܣ�\n");
        return -1;
    }
    //������ȶ�ȡbifType������C���Խṹ��Sizeof������򡪡�������ڲ���֮�ͣ��Ӷ����¶��ļ���λ
    unsigned short  fileType;
    printf("%d\n",sizeof(unsigned short));
    fread(&fileType,sizeof (unsigned short), 1,fp);  
    if (fileType = 0x4d42)   
    {   
        printf("�ļ����ͱ�ʶ��ȷ!" );  
        printf("\n�ļ���ʶ����%d\n", fileType); 
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
