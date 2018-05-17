//
//  picopng.h
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 18.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#ifndef picopng_h
#define picopng_h

#include <vector>
#include <cstddef>

int decodePNG(std::vector<unsigned char>& out_image,
                     unsigned long& image_width,
                     unsigned long& image_height,
                     const unsigned char* in_png, size_t in_size,
                     bool convert_to_rgba32 = true);

#endif /* picopng_h */
