#include <iostream>
#include <fstream>
using namespace std;

using BYTE = uint8_t;
using DWORD = uint32_t;
using LONG = int32_t;
using WORD = uint16_t;

#pragma pack(push, 1)
using BITMAPFILEHEADER = struct {
WORD bfType;
DWORD bfSize;
WORD bfReserved1;
WORD bfReserved2;
DWORD bfOffBits; };
#pragma pack(pop)


#pragma pack(push, 1)
using BITMAPINFOHEADER = struct {
DWORD biSize;
LONG biWidth;
LONG biHeight;
WORD biPlanes;
WORD biBitCount;
DWORD biCompression;
DWORD biSizeImage;
LONG biXPelsPerMeter;
LONG biYPelsPerMeter;
DWORD biClrUsed;
DWORD biClrImportant;  };
#pragma pack(pop)

#pragma pack(push, 1)
using pixel = struct{
BYTE B;
BYTE G;
BYTE R;
};
#pragma pack(pop)
void free_element(char** c, int h);
void create_array(char*** c, int h, int w);
void pixel2char(ifstream *input, char** c, int h, int w);
void write_chars(ofstream *output, char** c, int h, int w);

int main(int argc, char *argv[]){
    BITMAPINFOHEADER binfo;
    BITMAPFILEHEADER bheader;
    char **c;
    int h = 0, w = 0, i, j;
    ifstream input(argv[1], ios::binary);
	ofstream output(argv[2], ios::binary);
	input.read((char*) &bheader, sizeof(BITMAPFILEHEADER));
	input.read((char*) &binfo, sizeof(BITMAPINFOHEADER));
	w = abs(binfo.biWidth);
	h = abs(binfo.biHeight);
    create_array(&c, h, w);
    int s = (bheader.bfOffBits - sizeof(BITMAPFILEHEADER));
    input.seekg(bheader.bfOffBits, ios::beg);
    pixel2char(&input, c, h, w);
    write_chars(&output, c, h, w);
    free_element(c, h);
	input.close();
	output.close();
	return 0;
}

void free_element(char** c, int h){
    for (int i = 0; i < h; i++){
        delete[] *(c + i);
    }
    delete[] c;
    return;

}
void create_array(char*** c, int h, int w){
    *(c) = new char*[h];
    for (int i = 0; i < h; i++){
        *(*(c) + i) = new char[w + 2];
    }

    return;

}
void pixel2char(ifstream *input, char** c, int h, int w){
	WORD gray;
    pixel p;
    for(int i = 0; i < h ; i++){
		for(int j = 0; j < w; j++){
			input->read((char*)&p, sizeof(pixel));
			gray = (p.G + p.B + p.R) / 3;
			if(gray <= 25){
                *(*(c + i) + j) = '@';
            }else if(gray <= 50){
                *(*(c + i) + j) = '%';
            }else if(gray <= 75){
                *(*(c + i) + j) = '#';
            }else if(gray <= 100){
                *(*(c + i) + j) = '*';
            }else if(gray <= 125){
                *(*(c + i) + j) = '+';
            }else if(gray <= 150){
                *(*(c + i) + j) = '=';
            }else if(gray <= 175){
                *(*(c + i) + j) = '-';
            }else if(gray <= 200){
                *(*(c + i) + j) = ':';
            }else if(gray <= 225){
                *(*(c + i) + j) = '.';
            }else{
                *(*(c + i) + j) = ' ';
            }
 
		}
        *(*(c + i) + w) = '\n';
	}
    return ;

}
void write_chars(ofstream *output, char** c, int h, int w){
    for (int i = h-1; i >= 0; i--){
        for (int j = 0; j <= w; j++){
           output->put(*(*(c + i) + j));
        }
    }
    return ;
}