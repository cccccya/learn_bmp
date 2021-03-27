# ifndef BMP_H
# define BMP_H
/*
BMP��ʽ
���ָ�ʽ�ڵ����ݷ�Ϊ�����ĸ����֣������ǣ�
�ļ���Ϣͷ ��14�ֽڣ��洢���ļ����ͣ��ļ���С����Ϣ
ͼƬ��Ϣͷ ��40�ֽڣ��洢��ͼ��ĳߴ磬��ɫ������λƽ��������Ϣ
��ɫ�� ������ɫ������������������û�д���Ϣ��
λͼ���� ����ͼ��ߴ������ÿһ�����ص���Ϣ������洢

һ���bmpͼ����24λ��Ҳ������ʡ�ÿ8λΪһ�ֽڣ�24λҲ����ʹ�����ֽ����洢ÿһ�����ص���Ϣ�������ֽڶ�Ӧ���r��g��b��ԭɫ�����ݣ�
ÿ���ֽڵĴ�����Χ����0-255����ô�Դ����ƣ�32λͼ��ÿ���ش洢r��g��b��a��Alphaͨ�����洢͸���ȣ��������ݡ�8λͼ����ֻ�лҶ���һ����Ϣ��
���ж�ֵͼ����ֻ��������ɫ���ڻ��߰ס�
*/
// �ļ���Ϣͷ�ṹ��
typedef struct tagBITMAPFILEHEADER 
{
    //unsigned short bfType;        // 19778��������BM�ַ�������Ӧ��ʮ������Ϊ0x4d42,ʮ����Ϊ19778��������bmp��ʽ�ļ�
    unsigned int   bfSize;        // �ļ���С ���ֽ�Ϊ��λ(2-5�ֽ�)
    unsigned short bfReserved1;   // ��������������Ϊ0 (6-7�ֽ�)
    unsigned short bfReserved2;   // ��������������Ϊ0 (8-9�ֽ�)
    unsigned int   bfOffBits;     // ���ļ�ͷ���������ݵ�ƫ��  (10-13�ֽ�)
} BITMAPFILEHEADER;

//ͼ����Ϣͷ�ṹ��
typedef struct tagBITMAPINFOHEADER 
{
    unsigned int    biSize;          // �˽ṹ��Ĵ�С (14-17�ֽ�)
    long            biWidth;         // ͼ��Ŀ�  (18-21�ֽ�)
    long            biHeight;        // ͼ��ĸ�  (22-25�ֽ�)
    unsigned short  biPlanes;        // ��ʾbmpͼƬ��ƽ��������Ȼ��ʾ��ֻ��һ��ƽ�棬���Ժ����1 (26-27�ֽ�)
    unsigned short  biBitCount;      // һ������ռ��λ����һ��Ϊ24   (28-29�ֽ�)
    unsigned int    biCompression;   // ˵��ͼ������ѹ�������ͣ�0Ϊ��ѹ���� (30-33�ֽ�)
    unsigned int    biSizeImage;     // ����������ռ��С, ���ֵӦ�õ��������ļ�ͷ�ṹ��bfSize-bfOffBits (34-37�ֽ�)
    long            biXPelsPerMeter; // ˵��ˮƽ�ֱ��ʣ�������/�ױ�ʾ��һ��Ϊ0 (38-41�ֽ�)
    long            biYPelsPerMeter; // ˵����ֱ�ֱ��ʣ�������/�ױ�ʾ��һ��Ϊ0 (42-45�ֽ�)
    unsigned int    biClrUsed;       // ˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ����������Ϊ0�Ļ�����˵��ʹ�����е�ɫ����� (46-49�ֽ�)
    unsigned int    biClrImportant;  // ˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ��(50-53�ֽ�)
} BITMAPINFOHEADER;

//24λͼ������Ϣ�ṹ��,����ɫ��
typedef struct _PixelInfo {
    unsigned char rgbBlue;   //����ɫ����ɫ����  (ֵ��ΧΪ0-255)
    unsigned char rgbGreen;  //����ɫ����ɫ����  (ֵ��ΧΪ0-255)
    unsigned char rgbRed;    //����ɫ�ĺ�ɫ����  (ֵ��ΧΪ0-255)
    //unsigned char rgbReserved;// ����������Ϊ0
} PixelInfo;

#endif
