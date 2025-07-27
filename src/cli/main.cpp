#include "string_art/string_art.hpp"

using namespace string_art;

int main(int argc, char *argv[]) {
    Metadata meta;
    meta.pallete.push_back({{0, 0, 0, 255}, 10});
    meta.positions.push_back({500, 500});
    meta.positions.push_back({2000, 500});
    meta.positions.push_back({2000, 2000});
    meta.positions.push_back({500, 2000});
    StringArtPattern p;
    p.add_step({Action::CONNECT, 1});
    p.add_step({Action::CONNECT, 2});
    p.add_step({Action::CONNECT, 3});

    cv::imshow("lines", p.to_image(meta));
    cv::waitKey(0);
    return 0;
}
