#include <fstream>
#include <math.h>
#include <unistd.h>
#define thita 3.14/180*500

 using namespace std;
#pragma pack(2)
struct bitmapfileheader
{
    char header[2] = {'B','M'};
    int32_t filesize; 
    int32_t reserved = 0;
    int32_t dataoffset; 
 }fileheader;
 
 #pragma pack(2)
struct bitmapinfoheader
{
    int32_t headersize = 40;
    int32_t width;
    int32_t height;
    int16_t planes = 1;
    int32_t bitsperpixel = 24;
    int32_t compression = 0;
    int32_t datasize = 0;
    int32_t horizontalresolution = 2400;
    int32_t verticalresolution = 2400;
    int32_t colors =0;
    int32_t importantcolors = 0;
}infoheader;
#pragma pack(2)
struct rgb{
    int8_t b ;
    int8_t g ;
    int8_t r;
};

int main()
{
      
    ifstream file;
    file.open("tst.bmp",ios::in|ios::binary);
    file.read((char*)&fileheader,sizeof(fileheader));
    file.read((char*)&infoheader,sizeof(infoheader));
// the size of data array
    int height  = infoheader.height;
    int width = infoheader.width;
// the pixel data array 
    rgb pixel [height] [width] ;
    file.read((char*)&pixel,sizeof(pixel));
    ofstream outfile;
    int _height = 600;
    int _width = 600;
    rgb _pixel [_height][_width];
    float _cos = cos(thita) , _sin = sin(thita);
    
    for ( int x = 0 ; x < _height ; x++ )
    {
       for (int y = 0 ; y < _width ; y++ )
       {
            rgb temp ;
            temp.r = temp.g = temp.b = 0;
            _pixel[x][y] = temp;
       }
    }
    
    for ( float x = 0 ; x < height ; x+=0.01 )
    {
       for (float y = 0 ; y < width ; y+=0.01 )
       {
           _pixel[(int)(x*_cos - y*_sin) + 400 ][(int)(x*_sin + y*_cos) + 400 ] = pixel[(int)(x)][(int)y];
       }
    }
    infoheader.height = _height ;
    infoheader.width = _width ;
    fileheader.filesize = sizeof(fileheader) + sizeof(infoheader) + sizeof(_pixel);
    fileheader.dataoffset = sizeof(fileheader) + sizeof(infoheader);
   outfile.open("new_made_with_code.bmp",ios::out|ios::binary);
   outfile.write((char*)&fileheader ,sizeof(fileheader)) ;
   outfile.write ((char*)&infoheader ,sizeof(infoheader));
   outfile.write((char*)&_pixel,sizeof(_pixel));
   file.close();
   outfile.close();
    return 0;
}
