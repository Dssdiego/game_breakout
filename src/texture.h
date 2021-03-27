//
// Created by Diego Santos Seabra on 26/03/21.
//

#ifndef BREAKOUT_TEXTURE_H
#define BREAKOUT_TEXTURE_H

class Texture2D
{
public:
    // Holds the id of the texture object, used for all texture operations
    // to reference to this particular texture
    unsigned int Id;

    // Image dimensions
    unsigned int Width, Height;

    // Formats
    unsigned int InternalFormat; // format of texture object
    unsigned int ImageFormat;    // format of loaded image

    // Configuration
    unsigned int WrapS;          // wrapping mode on S axis
    unsigned int WrapT;          // wrapping mode on T axis
    unsigned int FilterMin;      // filtering mode if texture pixels < screen pixels
    unsigned int FilterMax;      // filtering mode if texture pixels > screen pixels

    Texture2D();

    // Generate texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char *data);

    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
};

#endif //BREAKOUT_TEXTURE_H
