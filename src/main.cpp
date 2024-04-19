#include <iostream>
#include "siren/bresenham_manager.hpp"
#include "siren/model_parser.hpp"

int main() {
    tga_color_t black = {0, 0, 0};
    tga_color_t white = {255, 255, 255};

    tga_image_t *image = tga_new(1024, 1024);
    if (!image) {
        std::cerr << "Failed to create image" << std::endl;
        return 1;
    }
    //tga_set_bg(image, black);

    BresenhamManager bresenhamManager(image);

    ModelParser modelParser("./obj/african_head.obj");

    modelParser.render(bresenhamManager, white);

    tga_write("new.tga", image);
    tga_free(image);

    return 0;
}
