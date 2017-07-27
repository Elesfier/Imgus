
#include "PNG-manually.h"

Image::PNG_MANUALLY::PNG_MANUALLY(Common::String declarationFileName)
: Image(declarationFileName, "png")
{
  tmpImg = nullptr;
  unsigned error;

  std::vector <unsigned char> buffer;
  std::ios::openmode fmode = std::ios::in | std::ios::binary | std::ios::ate;
  std::ifstream file( fileName.c_str(), fmode );

  std::streamsize file_size = 0;
  if( file.seekg(0, std::ios::end).good() ) file_size = file.tellg();
  if( file.seekg(0, std::ios::beg).good() ) file_size -= file.tellg();

  if(file_size > 0)
  {
    buffer.resize( (std::size_t)file_size );
    file.read( (char*)(&buffer[0]), file_size );
  }
  else
  {
    buffer.clear();
  }

  file.close();

  bitdepth = buffer[24];
  switch(int(buffer[25]))
  {
    case 0:
      colortype = LCT_GREY;
      break;
    case 2:
      colortype = LCT_RGB;
      break;
    default:
      throw ExceptionDecodePNG();
  }
       if (colortype == LCT_GREY && bitdepth == 1) types = "binary";
  else if (colortype == LCT_GREY && bitdepth == 8) types = "gray";
  else if (colortype == LCT_RGB  && bitdepth == 8) types = "color";
  else throw ExceptionDecodePNG();

  error = lodepng::decode(image, width, height, fileName, colortype, bitdepth);
  if(error) throw ExceptionDecodePNG();

  tmpImg = new TemporaryImage(height, width, this->type());

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      int i = (y * width + x);
      if (this->type() == Point::POINT_TYPES::BINARY)
      {
        Point::Binary* bin = dynamic_cast<Point::Binary*>((*tmpImg)(x, y));
        if (bin) bin->pixel = ((image[i/8] >> (7-i % 8)) & 1) ? false : true;
      }
      else if (this->type() == Point::POINT_TYPES::GRAY_SCALE)
      {
        Point::GrayScale* gray = dynamic_cast<Point::GrayScale*>((*tmpImg)(x, y));
        if (gray) gray->scale = (unsigned char)(image[i]);
      }
      else if (this->type() == Point::POINT_TYPES::RGB)
      {
        i = (y * width * 3 + x * 3);
        Point::RedGreenBlue* rgb = dynamic_cast<Point::RedGreenBlue*>((*tmpImg)(x, y));
        if (rgb)
        {
            rgb->red = (unsigned char)(image[i]);
            rgb->green = (unsigned char)(image[i+1]);
            rgb->blue = (unsigned char)(image[i+2]);
        }
      }
    }
  }
}

void Image::PNG_MANUALLY::save()
{
    this->fillImageContainer();
    lodepng::encode(fileName, image, width, height, colortype, bitdepth);
}

void Image::PNG_MANUALLY::save(Common::String declarationFileName)
{
    this->fillImageContainer();
    lodepng::encode(declarationFileName, image, width, height, colortype, bitdepth);
}

void Image::PNG_MANUALLY::fillImageContainer()
{
  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      int i = (y * width + x);
      if (this->type() == Point::POINT_TYPES::BINARY)
      {
        Point::Binary* bin = dynamic_cast<Point::Binary*>((*tmpImg)(x, y));
        if (bin) image[i/8] ^= (-(!bin->pixel) ^ image[i/8]) & (1 << (7-i % 8));
      }
      else if (this->type() == Point::POINT_TYPES::GRAY_SCALE)
      {
        Point::GrayScale* gray = dynamic_cast<Point::GrayScale*>((*tmpImg)(x, y));
        if (gray) image[i] = gray->scale;
      }
      else if (this->type() == Point::POINT_TYPES::RGB)
      {
        i = (y * width * 3 + x * 3);
        Point::RedGreenBlue* rgb = dynamic_cast<Point::RedGreenBlue*>((*tmpImg)(x, y));
        if (rgb)
        {
          image[i+0] = rgb->red;
          image[i+1] = rgb->green;
          image[i+2] = rgb->blue;
        }
      }
    }
  }
}
